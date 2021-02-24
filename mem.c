#include "types.h"
#include "config.h"
#include "util.h"


/*
    video memory layout( local framebuffer only)

    -------------------  offset 0
    -                 -
    -                 -    
    -                 -
    -                 -
    ------------------- cpu visiable size (bar 1)
    -                 -
    -                 -
    -                 - cpu unvisiable size 
    -                 -    
    -                 -
    ------------------- mxu boundary 
    -                 -
    -                 - 
    -                 - unsnoop 
    -                 -
    -------------------
    -                 -
    -                 -
    -                 - snoop 
    -                 - 
    -------------------
    
*/






void delete_node(struct list_header *head, struct list_block* delete_node);

void add_node(struct list_header *head, struct list_block *new_node, u32 could_merge)
{
    struct list_block *temp = NULL, *temp_1;
    struct list_block *prev = NULL, *next = NULL;
    u32 found = 0;


    if (could_merge)
    {
        list_for_each_entry(temp, struct list_block, &head->list, list_item)
        {
            if (temp->offset + temp->size == new_node->offset)
            {
                temp->size += new_node->size;
                prev = temp;
            }
                    
            if (new_node->offset + new_node->size == temp->offset)
            {
                temp->offset = new_node->offset;
                temp->size += new_node->size;
                next = temp;
            }
        }

        if(prev && next)
        {
            prev->size += next->size - new_node->size;  //need recorrect node size
            head->size += new_node->size;

            head->num -= 1;
            list_del(&next->list_item);

            free(next);
            free(new_node);
        }
        else if (!prev && !next)
        {
            head->size += new_node->size;
            head->num ++;
            list_for_each_entry(temp, struct list_block, &head->list, list_item)
            {
                if (temp->offset > new_node->offset)
                {
                    list_add(&new_node->list_item, temp->list_item.prev);
                    found = 1;
                    break;
                }
            }

            if (!found)
            {
                list_add(&new_node->list_item, head->list.prev);
            }
        }
        else
        {
            head->size += new_node->size;
            free(new_node);
        }
    }
    else
    {
        found = 0;
        head->size += new_node->size;
        head->num ++;
        list_for_each_entry(temp, struct list_block, &head->list, list_item)
        {
           if (temp->offset > new_node->offset)
           {
               list_add(&new_node->list_item, temp->list_item.prev);
               found = 1;
               break;
           }
        }
        if (!found)
        {
            list_add(&new_node->list_item, head->list.prev);
        }
    }
}

void delete_node(struct list_header *head, struct list_block* delete_node)
{
    list_del(&delete_node->list_item);

    head->size -= delete_node->size;
    head->num --;
}

void video_heap_init(struct mem_segment_t * segment)
{
    struct list_block   *node = NULL;

    INIT_LIST_HEAD(&segment->free.list);
    INIT_LIST_HEAD(&segment->busy.list);

    node = (struct list_block *)malloc(sizeof(struct list_block));

    if (node)
    {
        node->size = segment->available_size;
        node->offset = segment->offset;

        segment->free.size = node->size;
        segment->free.num = 1;
        list_add(&node->list_item, &segment->free.list);
    }
    else
    {
        dpu_info(ERROR_LEVEL,"%s: fatal error ,mem allocate faild\n",__func__);
    }
}


u32  alloc_video_mem(struct mem_segment_t *segment, u32 size, u32 aligment)
{
    struct list_block *temp = NULL, *temp_1 = NULL;
    u32   offset = 0;
    u8    found = 0;

    if (segment->free.size < size)
    {
        dpu_info(ERROR_LEVEL,"%s: no enough video memory \n", __func__);
        return 0;
    }

    if (!aligment)
    {
        aligment = 0x8000; //default value
    }

    list_for_each_entry(temp, struct list_block, &segment->free.list, list_item)
    {
        if (size > temp->size)
        {
            continue;
        }

        offset = (temp->offset + aligment - 1) & (~(aligment - 1));

        if (offset - temp->offset + size == temp->size)
        {
            delete_node(&segment->free, temp);
            add_node(&segment->busy, temp, 0);

            temp->aligned_offset = offset;
            break;
        }
        else if (offset - temp->offset + size < temp->size)
        {
            
            delete_node(&segment->free, temp);
            
            temp_1 = (struct list_block*)malloc(sizeof(struct list_block));
            if (!temp_1)
            {
                dpu_info(ERROR_LEVEL,"%s: allocate list node failed \n",__func__);
                offset = 0;
                break;
            }

            temp_1->size = temp->size - (offset - temp->offset + size);
            temp_1->offset = offset + size;

            temp->size = offset - temp->offset + size;
            temp->aligned_offset = offset;

            add_node(&segment->free, temp_1, 1);
            add_node(&segment->busy, temp, 0);

            break;
        }
        else
        {
            continue;
        }
    }

    return offset;
}

u32  free_video_mem(struct mem_segment_t *segment, u32 aligned_offset)
{
    struct list_block *temp = NULL;
    u32 ret = 1;

    list_for_each_entry(temp, struct list_block, &segment->busy.list, list_item)
    {
        if (temp->aligned_offset == aligned_offset)
        {
            break;
        }
    }

    if (temp)
    {
        delete_node(&segment->busy, temp);
        add_node(&segment->free, temp, 1);

        ret = 0;
    }
    return ret;
}


void dump_segment(struct mem_segment_t *segment)
{

    struct list_block* temp = NULL;
    u32 i = 0;

    dpu_info(INFO_LEVEL,"\n free list : size is 0x%x ,num is 0x%x \n",segment->free.size,segment->free.num);

    list_for_each_entry(temp, struct list_block, &segment->free.list, list_item)
    {
        i++;
        dpu_info(ERROR_LEVEL,"Note%d:  offset is 0x%x aligned_offset is 0x%x size is 0x%x\n", i, temp->offset, temp->aligned_offset, temp->size);
    }

    dpu_info(INFO_LEVEL,"\n busy list : size is 0x%x ,num is 0x%x \n",segment->busy.size,segment->busy.num);

    i = 0;
    list_for_each_entry(temp, struct list_block, &segment->busy.list, list_item)
    {
        i++;
        dpu_info(INFO_LEVEL,"Note%d:  offset is 0x%x aligned_offset is 0x%x size is 0x%x\n", i, temp->offset, temp->aligned_offset, temp->size);
    }

    dpu_info(INFO_LEVEL,"\n");
}


void init_video_memory(struct dpu_adapter_t *dpu_adapter)
{
    struct mem_segment_t * p_seg = NULL;

   // tt_set_cache(CACHE_DISABLE);// here set uncached ???? 没有必要开cache ?

    //dpu just support local memory 
    p_seg = &dpu_adapter->vidmm_mgr.mem_segments[LOCAL_SEGMENT];

    
    p_seg->segment_id = LOCAL_SEGMENT;
    p_seg->mem_size = dpu_adapter->base.fb_size;  //the real size need read from pmp ?

    p_seg->reserved_mem_size = RESERVED_MEM_SIZE;
    p_seg->offset =  p_seg->reserved_mem_size;
    p_seg->available_size = dpu_adapter->base.fb_size - p_seg->reserved_mem_size;

    video_heap_init(p_seg);

    p_seg->init_done = 1;
}



void video_heap_deinit(struct mem_segment_t * segment)
{
    struct list_block   *temp = NULL;

    INIT_LIST_HEAD(&segment->free.list);
    INIT_LIST_HEAD(&segment->busy.list);

    list_for_each_entry(temp, struct list_block, &segment->free.list, list_item)
    {
        delete_node(&segment->free, temp);
        free(temp);
    }

    list_for_each_entry(temp, struct list_block, &segment->busy.list, list_item)
    {
        delete_node(&segment->busy, temp);
        free(temp);
    }
    memset(segment, 0 ,sizeof(struct mem_segment_t));
}

void deinit_video_memory(struct dpu_adapter_t *dpu_adapter)
{
    struct mem_segment_t * p_seg = NULL;
    
    p_seg = &dpu_adapter->vidmm_mgr.mem_segments[LOCAL_SEGMENT];

    video_heap_deinit(p_seg);
    p_seg->init_done = 0;
}

