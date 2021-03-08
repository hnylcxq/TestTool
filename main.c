#include"types.h"
#include"util.h"
#include<stdlib.h>
#include<string.h>
#include"dm.h"
#include"mem.h"

struct dpu_adapter_t  *g_dpu_adapter = NULL;



static u32	g_real_chip = 0;
static u32  g_de_test = 1;
u32  g_output_uart = 0;
u8  g_script_name[SCRIPT_MAX_WORD_SIZE];



void deinit_adapter()
{
    if (g_dpu_adapter)
    {
        free(g_dpu_adapter);
        g_dpu_adapter = NULL;
    }
}


struct dpu_adapter_t* create_adapter()
{
	u32 test_domain = 0;
	u32 i = 0;


	g_dpu_adapter = (struct dpu_adapter_t*)malloc( sizeof(struct dpu_adapter_t));
	
	if(g_dpu_adapter == NULL)
	{
		dpu_info(ERROR_LEVEL,"%s failed to alloc mem space for dpu adapter\n",__FUNCTION__);
		return NULL;
	}
	
	memset(g_dpu_adapter, 0, sizeof(struct dpu_adapter_t));
	
	g_dpu_adapter->flags.run_on_qt = g_real_chip ? 0: 1;

	test_domain = g_de_test ?  TEST_DE : TEST_WITHOUT_DE;

	if (test_domain & TEST_DE)
	{
		test_domain |= g_real_chip ? TEST_DE_WITH_REAL_CHIP : 0;
	}

	g_dpu_adapter->test_domain = test_domain;
	g_dpu_adapter->log_level = DEBUG_LEVEL;

    g_dpu_adapter->cmd_num = 0;

	if (strlen(g_script_name) != 0)
	{
		g_dpu_adapter->script_name = g_script_name;
	}

    for (i = 0; i < MAX_INPUT_HISTORY_NUM; i++)
    {
        memset(g_dpu_adapter->cmd_history[i], '\0', MAX_CMD_STRING_NUM);
    }
	
	return g_dpu_adapter;
	
}

TT_STATUS tt_enable_card(struct base_adapter_t * base_adapter)
{
    //TODO change to set 850c[1] = 1

#if 0    
    u8 mm850c = 0;
    TT_STATUS ret = TT_PASS;

    mm850c = tt_read_mmio_byte(base_adapter->mmio_base, 0x850c);

    if (!(mm850c & 0x2))
    {
        tt_write_mmio_byte(base_adapter->mmio_base, 0x850c, mm850c | 0x02, 0);

        tt_delay_micro_seconds(1);
        
        mm850c = tt_read_mmio_byte(base_adapter->mmio_base, 0x850c);
        if (!(mm850c & 0x02))
        {
            dpu_info(ERROR_LEVEL,"fatal error:  enable card failed !!!\n");
            ret = TT_FAIL;
        }
    }

    return ret;
#endif
}

TT_STATUS find_adapter()
{
	u32 found = 0;
    TT_STATUS ret = TT_PASS;
	
	found = tt_get_pci_info(&g_dpu_adapter->base);

	if (!found)
	{
        ret = TT_FAIL;
        return ret;
	}

    if (!g_dpu_adapter->base.flags.is_primary)
    {
        tt_enable_pci_bridge(&g_dpu_adapter->base);
        tt_enable_mmio_access(&g_dpu_adapter->base);
        ret = tt_enable_card(&g_dpu_adapter->base);
    }
	

    return ret;
}


void init_surfaces(struct dpu_adapter_t *dpu_adapter)
{
    u32 i;

    dpu_adapter->width_alignment = 64;   //surface width is 256bit aligment   cursor need 512bit aligment ?
    dpu_adapter->offset_alignment = 0x8000; // 

    dpu_adapter->surface_manager.num = 0;

    for (i = 0; i < MAX_SURFACE_NUM; i++)
    {
        //dpu_adapter->surface_manager.surfaces[i].valid = 0;
        memset(&dpu_adapter->surface_manager.surfaces[i], 0, sizeof(dpu_adapter->surface_manager.surfaces[i]));
    }

}

void init_cached_cmd(struct dpu_adapter_t *dpu_adapter)
{

    struct mode_cmd_t *mode;
    struct plane_cmd_t *plane;
    struct device_cmd_t *device;

    mode = &dpu_adapter->cached_cmd[MODE_CMD][0].mode_cmd;

    dpu_adapter->cached_cmd[MODE_CMD][0].valid = 1;
    mode->crtc_index = 0;
    mode->output = PORT_0;

    mode->src_xres = 1920;
    mode->src_yres = 1080;

    mode->dst_xres = 1920;
    mode->dst_yres = 1080;

    mode->rr = 6000;

    mode->output_signal = DPU_RGB_SIGNAL;


    plane = &dpu_adapter->cached_cmd[PLANE_CMD][0].plane_cmd;
    dpu_adapter->cached_cmd[PLANE_CMD][0].valid = 1;

    plane->crtc_index = 0;
    plane->surface_index = 0;
    plane->src_x = 0;
    plane->src_y = 0;

    plane->src_w = 1920;
    plane->src_h = 1080;

    plane->dst_x = 0;
    plane->dst_y = 0;
    plane->dst_w = 1920;
    plane->dst_h = 1080;
    plane->plane_type = PRIMARY_PLANE;
    plane->disable_plane = 0;

    //plane->overlay_info_valid = 0;
   // plane->overlay_cmd.k_valid = 0;
    plane->overlay_cmd.m_valid = 0;

    device = &dpu_adapter->cached_cmd[DEVICE_CMD][0].device_cmd;
    dpu_adapter->cached_cmd[DEVICE_CMD][0].valid = 1;


    //TODO: need check later
    device->bit_depth = 8;
    device->async_clk = 1;
    device->cea = 0;
    device->coef = 1;
    device->color_format = 0;
    device->lane_count = 4;
    device->link_rate = 1;
    device->disable = 0;
}

//do init adapter hw here
void init_adapter(struct dpu_adapter_t *dpu_adapter)
{

    if (dpu_adapter->test_domain & TEST_WITHOUT_DE)
    {
        return;
    }

    //set mxu boundary / snoop boundary   490a0 ?

    //mxu boundary need local memory size , need pmp info ?
    //maybe could set mxu boundary to bar1 size for convenience

    tt_write_u32(dpu_adapter,  0x49000, 0x801);
    tt_write_u32(dpu_adapter,  0x49004, 0x80);
    tt_write_u32(dpu_adapter,  0x49008, 0x0);
    tt_write_u32(dpu_adapter,  0x490a0, 0x3f1f1f1f);
}


void parse_config(u8 words[][SCRIPT_MAX_WORD_SIZE], u32 word_num)
{
	FILE *fp = NULL;

	if (tt_is_same_str(words[0], "REAL_CHIP"))
	{
		g_real_chip = strtoul(words[1], NULL, 10);
		printf("g_real_chip is %d \n", g_real_chip);
	}
	else if (tt_is_same_str(words[0], "DE_TEST"))
	{
		g_de_test = strtoul(words[1], NULL, 10);
		printf("g_de_test is %d\n", g_de_test);
	}
	else if (tt_is_same_str(words[0], "UART_OUTPUT"))
	{
		g_output_uart = strtoul(words[1], NULL, 10);
		printf("g_output_uart is %d\n", g_output_uart);
	}
	else if (tt_is_same_str(words[0], "SCRIPT_NAME"))
	{
		fp = fopen(words[1], "rt");
		if (!fp)
		{
			printf("script %s is not exit \n",words[1]);
		}
		else
		{
			strcpy(g_script_name, words[1]);
			printf("g_script_name is %s\n",	g_script_name);

			fclose(fp);
		}
	}


}


extern void process_cmd(struct dpu_adapter_t *dpu_adapter);


static u8* g_config_file = "testtool.cfg";

void load_config(int argc, char** argv)
{
    u32 ret = 0;
	FILE *fp = NULL;
    u8 *line_str = NULL;
	u32 has_config = 1;
	u8   words[SCRIPT_LINE_MAX_WORD_NUM][SCRIPT_MAX_WORD_SIZE] = {0};
    u32    word_num = 0;

	fp = fopen(g_config_file, "rt");
	if (!fp)
	{
		printf("open %s failed \n", g_config_file);

		g_real_chip = 0;
		g_de_test = 1;
	}
	else
	{
		line_str = malloc(SCRIPT_LINE_MAX_NUM);

		if (!line_str)
		{
			printf("malloc failed ????\n");
			fclose(fp);
			return;
		}

		printf("********** %s info start ********\n", g_config_file);


	    while (!feof(fp))
	    {
	        memset(line_str, '\0', SCRIPT_LINE_MAX_NUM);
	        
	        fgets(line_str, SCRIPT_LINE_MAX_NUM, fp);

	        if (TT_PASS != tt_get_words(line_str, &word_num, words))
	        {
	            continue;
	        }

			if (tt_is_comment(words) || word_num < 2)  //use <key,value> do config
	        {
	            continue;
	        }
			parse_config(words, word_num);
		}
		printf("********** %s info end ********\n", g_config_file);

		fclose(fp);
	}

	//see whether user input script 
	if ((argc >= 2) && tt_is_end_with(argv[1], ".sh"))
	{
		if (strlen(argv[1]) < SCRIPT_MAX_WORD_SIZE)
		{
			fp = fopen(argv[1], "rt");
			if (!fp)
			{
				printf("cmdline script %s is not exit \n",argv[1]);

				if (strlen(g_script_name) != 0)
				{
					printf("will run script %s\n", g_script_name);
				}
			}
			else
			{
				strcpy(g_script_name, argv[1]);
				printf("will run cmdline script %s\n", g_script_name);

				fclose(fp);
			}
		}
		else
		{
			printf("ERROR, script name is too long \n");
		}
	}

}

int main(int argc, char** argv)
{
	struct dpu_adapter_t *p;
	TT_STATUS ret = TT_PASS;

	load_config(argc, argv);

	ret = init_platform_funcs();
	if (ret != TT_PASS)
	{
		goto end;
	}

	ret = tt_init_platform();
	if(ret != TT_PASS)
	{
		dpu_info(ERROR_LEVEL,"init platform env failed \n");
		goto end;
	}

	p = create_adapter();
	if (!p)
	{
		dpu_info(ERROR_LEVEL,"create adapter failed \n");
		goto end;
	}

	ret = find_adapter();
	if (ret == TT_FAIL)
	{
		dpu_info(ERROR_LEVEL,"no supported adapters found\n ");
		//goto end;//we use DOS box to test pure software logic, comment here temperary, restore it after board ready
	}

	init_adapter(p);

	init_dm(p);

	init_surfaces(p);

	init_cached_cmd(p);

	init_video_memory(p);

	process_cmd(p);

	deinit_dm(p);

	deinit_video_memory(p);

	tt_deinit_platform(p);

end:
	deinit_adapter();
	return ret;
}
