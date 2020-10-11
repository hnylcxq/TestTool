#include"dpu/dpu.h"
#include"util.h"
#include"types.h"
#include<stdio.h>
#include<string.h>

//所有call cbios 的interface 都需要走这里下去，相当于disp层，做参数转换的。


void dm_set_callback()
{
    struct dpu_cb_funs_t   cb_funs;

    memset(&cb_funs, 0, sizeof (struct dpu_cb_funs_t));

    cb_funs.cb_print = (void*)dpu_info;
    cb_funs.cb_delay_us = (void*)tt_delay_micro_seconds;
    cb_funs.cb_read_u8  = (void*)tt_read_u8;  
    cb_funs.cb_read_u16 = (void*)tt_read_u16;
    cb_funs.cb_read_u32 = (void*)tt_read_u32;
    cb_funs.cb_write_u8 = (void*)tt_write_u8;
    cb_funs.cb_write_u16 = (void*)tt_write_u16;
    cb_funs.cb_write_u32 = (void*)tt_write_u32;
    cb_funs.cb_alloc_mem = (void*)tt_malloc_mem;
    cb_funs.cb_free_mem = (void*)tt_free_mem;
    cb_funs.cb_spin_lock = NULL;
    cb_funs.cb_spin_unlock = NULL;
    cb_funs.cb_mutex_lock = NULL;
    cb_funs.cb_mutex_unlock = NULL;
    cb_funs.cb_strcmp = (void*)strcmp;
    cb_funs.cb_strcpy = (void*)strcpy;
    cb_funs.cb_strncmp = (void*)strncmp;
    cb_funs.cb_memset = (void*)memset;
    cb_funs.cb_memcpy = (void*)memcpy;
    cb_funs.cb_memcmp = (void*)memcmp;
    cb_funs.cb_do_div = NULL;
    cb_funs.cb_vsprintf = (void*)vsprintf;
    cb_funs.cb_vsnprintf = (void*)vsnprintf;

    dpu_set_cb(&cb_funs);
 
}



void dm_query_crtc_info(struct dpu_adapter_t * dpu_adapter)
{
    //dpu_query_crtc_info() from dpu.c
    //crtc_num,  plane num of each crtc

    dpu_adapter->num_crtc = 3;
    dpu_adapter->num_plane[0] = 2;
    dpu_adapter->num_plane[1] = 2;
    dpu_adapter->num_plane[2] = 2;

}


void dm_init_sw(struct dpu_adapter_t *dpu_adapter)
{
    void *p = NULL;

    
    dm_set_callback();

    p = dpu_init_sw();

    if (p)
    {
        dpu_adapter->dpu_manager = p;
    }
}

void dm_init_hw(struct dpu_adapter_t *dpu_adapter)
{
    dpu_init_hw(dpu_adapter->dpu_manager);
}

void dm_init_crtc(struct dpu_adapter_t *dpu_adapter)
{
    u32 i = 0;

    dm_query_crtc_info(dpu_adapter);
    
    for (i = 0; i < dpu_adapter->num_crtc; i++)
    {
        dpu_adapter->current_crtc_info[i].index = i;
        dpu_adapter->current_crtc_info[i].output = 0;
        memset(&dpu_adapter->current_crtc_info[i].src_mode, 0 , sizeof(struct mode_info_t));
        memset(&dpu_adapter->current_crtc_info[i].dst_mode, 0 , sizeof(struct mode_info_t));
    }

}

void dm_init_plane(struct dpu_adapter_t *dpu_adapter)
{

    u8  i,j, total_plane = 0;

    for (i = 0; i < dpu_adapter->num_crtc; i++)
    {
        for (j = 0; j < dpu_adapter->num_plane[i]; j++)
        {
            memset(&dpu_adapter->current_plane_info[i][j], 0 , sizeof(struct plane_info_t));
            dpu_adapter->current_plane_info[i][j].crtc_index = i;
            dpu_adapter->current_plane_info[i][j].plane_type = PRIMARY_PLANE + j;
            dpu_adapter->current_plane_info[i][j].csc_para.op = 1;
            dpu_adapter->current_plane_info[i][j].plane_state = PLANE_DISABLED;
            
        }
    }
}

void dm_init_output(struct dpu_adapter_t *dpu_adapter)
{
    u8 i = 0;

    dpu_adapter->support_device = PORT_0 | PORT_1 | PORT_2;
    dpu_adapter->active_output[0] = 0;


    for (i = 0; i < PORT_NUM; i++)
    {
        memset(&dpu_adapter->current_output_info[i], 0 , sizeof(struct output_info_t));
        dpu_adapter->current_output_info[i].connect_status = DISCONNECTED_STATUS;
        dpu_adapter->current_output_info[i].power_status = POWER_OFF;
    }
   

    //TODO: need detect para
    dpu_detect_device(dpu_adapter->dpu_manager);

    dpu_adapter->active_output[0] = PORT_0 | PORT_1 | PORT_2;
}



void dm_init_surfaces(struct dpu_adapter_t *dpu_adapter)
{
    u32 i;

    dpu_adapter->surface_manager.num = 0;

    for (i = 0; i < MAX_SURFACE_NUM; i++)
    {
        //dpu_adapter->surface_manager.surfaces[i].valid = 0;
        memset(&dpu_adapter->surface_manager.surfaces[i], 0, sizeof(dpu_adapter->surface_manager.surfaces[i]));
    }

}

void dm_init_cached_cmd(struct dpu_adapter_t *dpu_adapter)
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

    mode->output_signal = RGB_SIGNAL;


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
    plane->overlay_cmd.k_valid = 0;
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

void init_dm(struct dpu_adapter_t *dpu_adapter)
{
    dm_init_sw(dpu_adapter);

    dm_init_hw(dpu_adapter);

    dm_init_crtc(dpu_adapter);

    dm_init_plane(dpu_adapter);

    dm_init_output(dpu_adapter);

    dm_init_surfaces(dpu_adapter);

    dm_init_cached_cmd(dpu_adapter);


    dpu_adapter->width_alignment = 64;   //surface width is 256bit aligment   cursor need 512bit aligment ?
    dpu_adapter->offset_alignment = 0x8000; // 
}


void deinit_dm()
{
    //All sw state ?
}
