#include<stdio.h>
#include<stdlib.h>
#include<string.h>


#include"list.h"
#include"types.h"
#include"util.h"
#include"script.h"





typedef enum
{
    VAR_SCOPE_NONE = 0,
    VAR_SCOPE_GLOBAL,
    VAR_SCOPE_LOCAL,    //out of the scope, will be destoryed
    
}VAR_SCOPE;


typedef enum
{
    VAR_TYPE_NONE = 0,
    VAR_TYPE_INT,
    VAR_TYPE_ARRAY,

}VAR_TYPE;

struct variant_node_t
{
    struct list_head  node;
    u8   name[SCRIPT_MAX_WORD_SIZE];
    VAR_SCOPE scope;
    VAR_TYPE  type; 

    union
    {
        u8   origin_string[SCRIPT_ARRAY_MAX_NUM][SCRIPT_MAX_WORD_SIZE];
        i32  value;
    };
    u32  num;
};

typedef enum
{
    CODE_TYPE_NONE = 0,
    CODE_TYPE_NORMAL,
    CODE_TYPE_LOOP_START,
    CODE_TYPE_LOOP_END,

}CODE_TYPE;

struct  code_node_t
{
    struct list_head node;
    CODE_TYPE type;
    
    u8   code[SCRIPT_LINE_MAX_WORD_NUM][SCRIPT_MAX_WORD_SIZE];

    u32  word_num;
    u8   count_name[SCRIPT_MAX_WORD_SIZE];

    i32  start;
    i32  end;
    u32  depth;
};


struct script_manager_t
{

    struct list_head  exec_list;

    struct list_head  var_list;

};




BOOL is_assignment(u8 words[][SCRIPT_MAX_WORD_SIZE])
{
    BOOL ret = FALSE;
   
    if (words[1][0] == '=')     //assigment code:     crtc = 4   or  crtc[2] = { },  so '=' must at second word
    {
        ret = TRUE;
    }
  
    return ret;
}


BOOL is_array(u8 * word)
{
    u8 * temp = word;
    u32 i = 0;
    u32 find_1 = 0, find_2 = 0;
    BOOL ret = FALSE;

    while(temp[i])
    {
        if (temp[i] == '[')
        {
            find_1 = 1;
        }

        if (temp[i] == ']')
        {
            find_2 = 1;
        }

        i ++;
    }

    if (find_1 && find_2)
    {
        ret = TRUE;
    }


    return ret;  
}

u32 get_array_noi(u8 *word)  //num or index
{
    u8* temp = word;
    u32 i = 0;
    u32 num = 0;
    u32 value = 0;
    
    while (temp[i] != '[')
    {
        i++;
    }

    i += 1;
    while (temp[i] != ']')
    {
        
        num *= 10;
        value = temp[i] - '0';
        num += value;

        i++;
    }
    
    return num;
}

void get_var_name(u8* name, u8 *word)
{
    u32 i = 0;

    while (word[i] && (word[i] != '[') && (word[i] != ']'))
    {
        name[i] = word[i];
        i++;
    }
    name[i] = '\0';
}


BOOL do_assignment(struct script_manager_t *sm, u8 words[][SCRIPT_MAX_WORD_SIZE], u32 word_num)
{
    struct variant_node_t *node = NULL;
    u32 num = 0;
    u32 i = 0;
    i32 value = 0;
    BOOL ret = TRUE;

    if (word_num < 3)
    {
        dpu_info(ERROR_LEVEL," please help check assignment code about %s %d\n", words[0], word_num);
        ret = FALSE;
        goto end;
    }

    node = calloc(1, sizeof(struct variant_node_t));

    if (!is_array(words[0]))
    {
        strcpy((i8*)node->name, (i8*)words[0]);
        strcpy(node->origin_string[0], words[2]);
        
        node->num = 1;
        node->scope = VAR_SCOPE_GLOBAL;
        node->type = VAR_TYPE_INT;

        list_add_tail(&node->node, &sm->var_list);

        //dpu_info(DEBUG_LEVEL,"get var  %s = %s\n",words[0], node->origin_string[0]);

    }
    else
    {
        num = get_array_noi(words[0]);

        //dpu_info(DEBUG_LEVEL,"array num is %d\n",num);

        node->type = VAR_TYPE_ARRAY;
        node->scope = VAR_SCOPE_GLOBAL;
        node->num = num;
        get_var_name(node->name, words[0]);

        if (word_num != (2 + num))  //array name  and " = "
        {
            ret = FALSE;
            dpu_info(ERROR_LEVEL,"array's num is mismatch with it's values \n");
            goto end;
        }

        //dpu_info(DEBUG_LEVEL,"get array %s, member num is %d value is :\n", words[0], num);

        for (i = 0; i < num; i ++)
        {
            strcpy(node->origin_string[i], words[i + 2]);
            //dpu_info(DEBUG_LEVEL,"%s ",node->origin_string[i]);
        }

        //dpu_info(INFO_LEVEL,"\n");

        list_add_tail(&node->node, &sm->var_list);
    }

    return ret;
end:
    if(node)
    {
        free(node);
    }

    return ret;
    
}

BOOL is_loop_start(u8 words[][SCRIPT_MAX_WORD_SIZE])
{
    BOOL ret = FALSE;

    if (!strcmp(words[0], "for"))
    {
        ret = TRUE;
    }

    return ret;
}


//loop control code in script like this :   for  i   0   2     


BOOL handle_loop_start(struct script_manager_t* sm, u8 words[][SCRIPT_MAX_WORD_SIZE], u32 word_num, u32 depth)
{
    struct variant_node_t *var = NULL;
    struct code_node_t * code = NULL;


    if (word_num != 4)
    {
        dpu_info(ERROR_LEVEL,"please check for loop control \n");
        return FALSE;
    }

    var = calloc(1, sizeof(struct variant_node_t));
    if (!var)
    {
        dpu_info(ERROR_LEVEL,"failed to malloc var node\n");
        goto end_1;
    }

    code = calloc(1, sizeof(struct code_node_t));
    if (!code)
    {
        dpu_info(ERROR_LEVEL,"failed to malloc code node\n");
        goto end;
    }


    //handle count var       
    strcpy(var->name, words[1]);

    dpu_info(DEBUG_LEVEL,"add count %s\n",var->name);

    var->num = 2;
    var->scope = VAR_SCOPE_LOCAL;

    var->type = VAR_TYPE_INT;
    var->value = strtoul(words[2], NULL, 10);
    strcpy(var->origin_string[0], words[2]);

  
    list_add_tail(&var->node, &sm->var_list);


    //handle code

    code->type = CODE_TYPE_LOOP_START;
    strcpy(code->count_name, words[1]);
    code->depth = depth;
    code->start = strtoul(words[2], NULL, 10);
    code->end = strtoul(words[3], NULL, 10);

    if (code->start > code->end)
    {
        dpu_info(ERROR_LEVEL,"error loop counter setting \n");
        while(1);
    }

    //dpu_info(DEBUG_LEVEL,"%s start %d  end %d \n",code->count_name, code->start, code->end);

    list_add_tail(&code->node, &sm->exec_list);


    return TRUE;

end:

    if (var)
    {
        free(var);
    }

end_1:

    return FALSE;

}


BOOL is_loop_end(u8 words[][SCRIPT_MAX_WORD_SIZE])
{
    BOOL ret = FALSE;

    if (!strcmp(words[0], "done"))
    {
        ret = TRUE;
    }

    return ret;
}


struct variant_node_t * find_var(struct script_manager_t* sm, u8* var_name)
{
    u8 find = 0;
    struct variant_node_t * temp = NULL;

    //dpu_info(DEBUG_LEVEL,"try to find %s \n",var_name); 
    
    list_for_each_entry(temp, struct variant_node_t, &sm->var_list, node)
    {
        if (!strcmp(temp->name, var_name))
        {
            find = 1;
            break;
        }
    }

    if (find)
    {
        return temp;
    }
    else
    {
        return NULL;
    }
}


void int_to_ascii(u32 num, u8* str)
{
    u8 index[]="0123456789";
    u32 unum = num;
    i32 i=0,j,k = 0;
    u8 temp;

    do
    {
        str[i++] = index[unum % (u32)10];
        unum /= 10;

    }while(unum);
    
    str[i] = '\0';

    for(j = k; j <= (i -1 ) / 2; j++)
    {       
        temp = str[j];
        str[j] = str[i - 1 + k - j];
        str[i - 1 + k - j] = temp;
    }
}

void replace_string(u8* dst, u8 *src, u32 name_size, u8 is_array)
{
    u32 length = 0, length_2 = 0;
    i32 i = 0;

    length = strlen(src);

    //$array[5]  replace with abc, need handle "$  [ ] index_num(5) "
    if (is_array)
    {
        name_size += 4;
    }
    else //$var need handle "$"
    {
        name_size += 1;
    }
    
    if (name_size >= length)
    {
        for (i = 0; i < length; i++)
        {
            dst[i] = src[i];
        }

       // dpu_info(DEBUG_LEVEL,"length is %d name_size is %d\n",length, name_size);

        i = 0;
        while (dst[name_size + i])
        {
          //  dpu_info(DEBUG_LEVEL,"i is %d dst is %c\n",i,dst[name_size +i]);
            dst[length + i] = dst[name_size + i];
            i++;
        }
        dst[length + i ] = '\0';
    }
    else
    {
        length_2 = strlen(dst);

        for (i = length_2; i >= name_size; i--)
        {
            dst[i + length - name_size] = dst[i];
        }

        for (i = 0; i < length; i++)
        {
            dst[i] = src[i];
        }
    }
}

BOOL replace_var(struct script_manager_t* sm, u8 words[][SCRIPT_MAX_WORD_SIZE], u32 word_num)
{
    i32 i = 0, j = 0, k = 0;
    u8* temp = NULL;
    BOOL ret = TRUE;
    u32 index = 0;
    i32 size = 0;
    struct variant_node_t *var = NULL;
    u8 var_name[SCRIPT_MAX_WORD_SIZE];

    //the most complex case: $array1[$array[5]]
    //dpu_info(DEBUG_LEVEL,"in replace var word_num is %d\n", word_num);

    for (i = 0; i < word_num; i++)
    {
        j = 0;
        size = strlen(words[i]);

        if (!size)
        {
            continue;
        }
       // dpu_info(DEBUG_LEVEL,"i is %d size is %d\n",i, size);
        memset(var_name, '\0', SCRIPT_MAX_WORD_SIZE);
        
        for(j = size - 1; j >= 0; j--)
        {
            if(words[i][j] == '$')
            {
                temp = &words[i][j + 1];

                if (is_array(temp))
                {
                    get_var_name(var_name, temp);
                    index = get_array_noi(temp);

                    //dpu_info(DEBUG_LEVEL,"find array var : %s\n",var_name);

                    var = find_var(sm, var_name);

                    replace_string(&words[i][j], var->origin_string[index], strlen(var_name), 1);
                }
                else
                {
                    get_var_name(var_name, temp);
                    var = find_var(sm, var_name);

                    //dpu_info(DEBUG_LEVEL,"find int var : %s\n",var_name);

                    replace_string(&words[i][j], var->origin_string[0], strlen(var->name), 0); 
                }
            }
        }
    }
}

extern TT_STATUS do_exec_cmd(struct dpu_adapter_t *dpu_adapter, u8 str[][MAX_CMD_OPTION_NAME_SIZE], u32 word_num);


TT_STATUS do_normal_exec(struct dpu_adapter_t *dpu_adapter, struct script_manager_t* sm, u8 words[][SCRIPT_MAX_WORD_SIZE], u32 word_num, u32 depth, u32 exec)
{
    struct code_node_t *node;
    i32 i = 0;
	TT_STATUS ret = TT_PASS;

    if (exec)
    {
        replace_var(sm, words, word_num);

#if 0
        for (i = 0; i < word_num; i ++)
        {
            dpu_info(INFO_LEVEL,"%s ",words[i]);
        }
       // dpu_info(INFO_LEVEL,"depth is %d \n",depth);
        dpu_info(INFO_LEVEL,"\n");

#else 

		ret = do_exec_cmd(dpu_adapter, words, word_num);

		if (ret != TT_PASS)
		{
			dpu_info(ERROR_LEVEL, "script exec failed, please help check\n"); 
			return ret;
		}
#endif

    }
    else
    {
        node = calloc(1, sizeof(struct code_node_t));

        if (!node)
        {
            dpu_info(ERROR_LEVEL,"malloc code node faild \n");
            while(1);
        }

        node->depth = depth;
        node->type = CODE_TYPE_NORMAL;
        node->word_num = word_num;

        for (i = 0; i < word_num; i++)
        {
            strcpy(node->code[i], words[i]);
        }

        list_add_tail(&node->node, &sm->exec_list);
    }

	return ret;

}

void  print_codes(struct script_manager_t* sm)
{
    struct code_node_t *node = NULL;
    u8 i = 0;


    dpu_info(INFO_LEVEL,"\nprint all the code in exec_list \n\n");
    list_for_each_entry(node, struct code_node_t, &sm->exec_list, node)
    {

        if (node->type == CODE_TYPE_LOOP_START)
        {
            dpu_info(INFO_LEVEL,"addr %p: depth %d,  for %s %d %d\n", node, node->depth, node->count_name, node->start, node->end);
        }

        if (node->type == CODE_TYPE_LOOP_END)
        {
            dpu_info(INFO_LEVEL,"addr %p: depth %d,  done \n",node, node->depth);
        }

        if (node->type == CODE_TYPE_NORMAL)
        {
            dpu_info(INFO_LEVEL,"addr %p: depth %d,  ", node, node->depth);
            for(i = 0; i < node->word_num; i++)
            {
                dpu_info(INFO_LEVEL,"%s ", node->code[i]);
            }
            dpu_info(INFO_LEVEL,"\n");
        }
    }
}


struct code_node_t* find_end(struct script_manager_t *sm, struct code_node_t* start)
{
    struct code_node_t * temp = start;
    i32 i = 0;
    list_for_each_entry_from(temp, struct code_node_t, &sm->exec_list, node)
    {
        if (temp->type == CODE_TYPE_LOOP_START)
        {
            i++;
        }

        if (temp->type == CODE_TYPE_LOOP_END)
        {
            i--;
        }

        if (i == 0)
        {
            return temp;
        }
            
    }
}   

TT_STATUS exec_loop_body(struct dpu_adapter_t *dpu_adapter, struct script_manager_t* sm, struct code_node_t *start, struct code_node_t *end, u32 depth)
{
    struct code_node_t *temp = NULL;
    struct variant_node_t * var = NULL;
    u8  temp_cmd[SCRIPT_LINE_MAX_WORD_NUM][SCRIPT_MAX_WORD_SIZE];
	TT_STATUS ret = TT_PASS;

    i32 i = 0, j = 0;

    for(i = start->start; i <= start->end; i++)
    {
        if (start->type != CODE_TYPE_LOOP_START)
        {
            dpu_info(ERROR_LEVEL,"why loop start type error\n");
            while(1);
        }
    
        if (end->type != CODE_TYPE_LOOP_END)
        {
            dpu_info(DEBUG_LEVEL,"why loop end type error \n");
            while(1);
        }
    
        var = find_var(sm, start->count_name);
        //dpu_info(DEBUG_LEVEL,"start %d end %d i %d\n",start->start, start->end, i);
        int_to_ascii(i, var->origin_string[0]);
        for(temp = start; (temp != end) && (temp->node.next != &sm->exec_list);  temp = list_entry(temp->node.next, struct code_node_t, node))
        {
          //  dpu_info(DEBUG_LEVEL,"i is %d, here  start is %p  end is %p temp is %p\n",i, start, end,  temp);

            if ((start->depth + 1 ==  temp->depth) && (temp->type == CODE_TYPE_LOOP_START))
            {
                exec_loop_body(dpu_adapter, sm, temp, find_end(sm, temp), temp->depth);
            }

            if (start->depth == temp->depth && temp->type == CODE_TYPE_NORMAL)
            {
                memset(temp_cmd, '\0', SCRIPT_LINE_MAX_WORD_NUM * SCRIPT_MAX_WORD_SIZE);
                for (j = 0; j < temp->word_num;j++)
                {
                    strcpy(temp_cmd[j], temp->code[j]);
                }
                ret = do_normal_exec(dpu_adapter, sm, temp_cmd, temp->word_num, temp->depth, 1);
				if (ret != TT_PASS)
				{
					printf("exec failed here 3 \n");
					return ret;
				}
            }

            if (start->depth == temp->depth && temp->type == CODE_TYPE_LOOP_END)
            {
                return TT_PASS;;
            }
        }
    }

	return ret;
}

void clear_execed_code(struct script_manager_t* sm)
{
    //delete code
    struct code_node_t *node = NULL, *node2 = NULL;
    struct variant_node_t *var = NULL, *var2 = NULL;
    
    list_for_each_entry_safe(node, struct code_node_t, node2, &sm->exec_list, node)
    {
        list_del(&node->node);
        free(node);
    }

    //delete local var

    list_for_each_entry_safe(var, struct variant_node_t, var2, &sm->var_list, node)
    {
        if (var->scope == VAR_SCOPE_LOCAL)
        {
            //dpu_info(DEBUG_LEVEL,"var name is %s\n",var->name);
      
            list_del(&var->node);
            free(var);
            
        }
    }

}


TT_STATUS handle_loop_end(struct dpu_adapter_t *dpu_adapter ,struct script_manager_t* sm, u8 words[][SCRIPT_MAX_WORD_SIZE], u32 word_num, u32 depth)
{
	TT_STATUS ret = TT_PASS;
    struct code_node_t *node = NULL, *start = NULL;
    struct variant_node_t *var = NULL;
    
    i32 j = 0;

    node = calloc(1, sizeof(struct code_node_t));

    if (node)
    {
        node->type = CODE_TYPE_LOOP_END;
        node->depth = depth;

        list_add_tail(&node->node, &sm->exec_list);
    }


    list_for_each_entry(var, struct variant_node_t, &sm->var_list, node)
    {
       // dpu_info(DEBUG_LEVEL,"var->name is %s scope is %d\n",var->name, var->scope);
    }

    if (depth == 1)
    {
        start = list_entry(sm->exec_list.next,struct code_node_t, node);

 
        //print_codes(sm);

        ret = exec_loop_body(dpu_adapter, sm, start, node, depth);

        clear_execed_code(sm);
        //print_codes(sm);
    }

	return ret;

}


#if 1
BOOL pre_handle_line(u8 *line_str, u8 words[][SCRIPT_MAX_WORD_SIZE], u32 *word_num)
{
    u8      filter[] = " ,\t\n";
    u32        i = 0;
    u8      *word = NULL;


    word = strtok(line_str, filter);

    if(word != NULL)
    {
        strcpy(words[0], word);
    }
    else
    {
        return FALSE;
    }

    i = 1;
    while(word != NULL)
    {
        word = strtok(NULL, filter);
        if(word != NULL)
        {
            strcpy(words[i], word);
            i++;
        }
    }
    *word_num = i;

    return TRUE;
}

#endif

void do_script_exec(struct dpu_adapter_t *dpu_adapter)
{
    FILE *fp = NULL;
    u8 *line_str = NULL;
    struct script_manager_t sm = {0};
    u8   words[SCRIPT_LINE_MAX_WORD_NUM][SCRIPT_MAX_WORD_SIZE] = {0};
    u32    word_num = 0;
    u32  depth = 0;
    BOOL ret = FALSE;
    u32 exec = 0;


	if (!dpu_adapter->script_name)
	{
		return ;
	}

    INIT_LIST_HEAD(&sm.exec_list);
    INIT_LIST_HEAD(&sm.var_list);

    fp = fopen(dpu_adapter->script_name, "rt");

    if (!fp)
    {
        dpu_info(ERROR_LEVEL,"open script %s failed \n",dpu_adapter->script_name);
        return ;
    }

    line_str = malloc(SCRIPT_LINE_MAX_NUM);

    if (!line_str)
    {
        dpu_info(ERROR_LEVEL,"malloc failed \n");
        goto end;
    }


    while (!feof(fp))
    {
        memset(line_str, '\0', SCRIPT_LINE_MAX_NUM);
        
        fgets(line_str, SCRIPT_LINE_MAX_NUM, fp);


        if (TT_PASS != tt_get_words(line_str, &word_num, words))
        {
            continue;
        }
		
        if (tt_is_comment(words) || word_num == 0)
        {
            continue;
        }

        if (is_assignment(words))
        {
            do_assignment(&sm, words, word_num);
			//printf("%s %d\n",line_str, word_num);
            continue;
        }

        if (is_loop_start(words))
        {
            depth ++;
            handle_loop_start(&sm, words, word_num, depth);

            continue;
        }

        if (is_loop_end(words))
        {
            ret = handle_loop_end(dpu_adapter, &sm, words, word_num, depth);
			if (ret != TT_PASS)
			{
				printf("exec failed here 2 \n");
				goto end;
			}
            depth --;
            
            continue;
        }

        if (depth)
        {
            exec = 0;
        }
        else
        {
            exec = 1;
        }
        ret = do_normal_exec(dpu_adapter, &sm, words, word_num, depth, exec);
		if (ret != TT_PASS)
		{
			printf("exec failed here \n");
			goto end;
		}
    }

end:

    clear_execed_code(&sm);
    if (fp)
    {
        fclose(fp);
        fp = NULL;
    }
}




