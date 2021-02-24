#include"dpu.h"
#include"util.h"
#include"types.h"
#include<stdio.h>
#include<string.h>

//所有call cbios 的interface 都需要走这里下去，相当于disp层，做参数转换的。
//display manager is a simple layer


i32 dm_set_callback()
{

#if 0
   // DPU_STATUS  status = DPU_OK;
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
    #if 0 //no need
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
    #endif
    cb_funs.cb_vsprintf = (void*)vsprintf;
    cb_funs.cb_vsnprintf = (void*)vsnprintf;

   // status = dpu_set_cb(&cb_funs);

    return 1;
 #endif
}

i32 dm_init_sw(struct dpu_adapter_t *dpu_adapter)
{
    i32 ret = 0;
    void *p = NULL;
    struct dpu_init_sw_para_t sw_init_para = {0};

    memset(&sw_init_para, 0, sizeof(struct dpu_init_sw_para_t));

    sw_init_para.dpu_cb.cb_print                  	= (void*)dpu_info;
    sw_init_para.dpu_cb.cb_delay_us         		= (void*)tt_delay_micro_seconds;
    sw_init_para.dpu_cb.cb_read_u8                 	= (void*)tt_read_u8;
    sw_init_para.dpu_cb.cb_read_u16                	= (void*)tt_read_u16;
    sw_init_para.dpu_cb.cb_read_u32                	= (void*)tt_read_u32;
    sw_init_para.dpu_cb.cb_write_u8               	= (void*)tt_write_u8;
    sw_init_para.dpu_cb.cb_write_u16               	= (void*)tt_write_u16;
    sw_init_para.dpu_cb.cb_write_u32                = (void*)tt_write_u32;
    //sw_init_para.dpu_cb.cb_read_io             		= (void*)tt_read_io;
    //sw_init_para.dpu_cb.cb_write_io            		= (void*)tt_write_io;
    sw_init_para.dpu_cb.cb_alloc_mem   	            = (void*)tt_malloc_mem;
    sw_init_para.dpu_cb.cb_free_mem                 = (void*)tt_free_mem;
    sw_init_para.dpu_cb.cb_create_spin_lock 		= NULL;
    sw_init_para.dpu_cb.cb_destory_spin_lock 		= NULL;
    sw_init_para.dpu_cb.cb_spin_lock 				= NULL;
    sw_init_para.dpu_cb.cb_spin_unlock 				= NULL;
    sw_init_para.dpu_cb.cb_create_mutex 			= NULL;
    sw_init_para.dpu_cb.cb_destory_mutex 			= NULL;
    sw_init_para.dpu_cb.cb_mutex_lock 				= NULL;
    sw_init_para.dpu_cb.cb_mutex_unlock 			= NULL;

    sw_init_para.dpu_cb.cb_strcmp                   = (void*)strcmp;
    sw_init_para.dpu_cb.cb_strcpy                   = (void*)strcpy;
    sw_init_para.dpu_cb.cb_strncmp                  = (void*)strncmp;
    sw_init_para.dpu_cb.cb_memset                   = (void*)memset;
    sw_init_para.dpu_cb.cb_memcpy                   = (void*)memcpy;
    sw_init_para.dpu_cb.cb_memcmp                   = (void*)memcmp;
    sw_init_para.dpu_cb.cb_do_div 					= NULL;
    sw_init_para.dpu_cb.cb_vsprintf                 = (void*)vsprintf;
    sw_init_para.dpu_cb.cb_vsnprintf                = (void*)vsnprintf;

    sw_init_para.chip_revision          = dpu_adapter->base.revision_id;
    sw_init_para.device_id             	= 0x5348;//dpu_adapter->base.device_id;
    sw_init_para.vender_id            	= dpu_adapter->base.vender_id;
    sw_init_para.is_mamm_primary 		= dpu_adapter->base.flags.is_primary; 
	sw_init_para.dpu_adapter 			= dpu_adapter;

    sw_init_para.mmio_base = dpu_adapter->base.mmio_base;

    sw_init_para.is_qt_test = dpu_adapter->flags.run_on_qt;

    dpu_adapter->dpu_manager = dpu_mgr_init(&sw_init_para);
	printf("dpu_adapter->dpu_manager  is %p \n",dpu_adapter->dpu_manager );

    return 0;
}

void dm_deinit_sw(struct dpu_adapter_t *dpu_adapter)
{
	dpu_mgr_deinit(dpu_adapter->dpu_manager);
}

void dm_init_hw(struct dpu_adapter_t *dpu_adapter)
{
    dpu_hw_init(dpu_adapter->dpu_manager);
}

void dm_deinit_hw(struct dpu_adapter_t *dpu_adapter)
{
	dpu_hw_deinit(dpu_adapter->dpu_manager);
}

void dm_init_crtc(struct dpu_adapter_t *dpu_adapter)
{
    u32 i = 0;
	struct dpu_crtc_caps_t *crtc_caps = &dpu_adapter->crtc_caps;

    dpu_query_crtc_info(dpu_adapter->dpu_manager, crtc_caps);

    for (i = 0; i < crtc_caps->crtc_num; i++)
    {
        dpu_adapter->current_crtc_info[i].index = i;
        dpu_adapter->current_crtc_info[i].output = 0;
        memset(&dpu_adapter->current_crtc_info[i].hw_mode, 0 , sizeof(struct dpu_display_mode_t));
        memset(&dpu_adapter->current_crtc_info[i].adjust_mode, 0 , sizeof(struct dpu_display_mode_t));
    }

}

void dm_init_plane(struct dpu_adapter_t *dpu_adapter)
{

    u8  i,j, total_plane = 0, crtc_index = 0;

    for (i = 0; i < dpu_adapter->crtc_caps.crtc_num; i++)
    {
        crtc_index = i;
        if (crtc_index >= CRTC_NUM)
            return;
        for (j = 0; j < dpu_adapter->crtc_caps.plane_num[crtc_index]; j++)
        {
            memset(&dpu_adapter->current_plane_info[crtc_index][j], 0 , sizeof(struct plane_info_t));
            dpu_adapter->current_plane_info[crtc_index][j].crtc_index = crtc_index;
            dpu_adapter->current_plane_info[crtc_index][j].plane_type = PRIMARY_PLANE + j;
            dpu_adapter->current_plane_info[crtc_index][j].csc_para.op = 1;
            dpu_adapter->current_plane_info[crtc_index][j].plane_state = PLANE_DISABLED;
            
        }
    }
}

void dm_init_output(struct dpu_adapter_t *dpu_adapter)
{
    u32 i = 0;
    u32 device = 0, temp = 0;
    struct dpu_detect_para_t            devDetect;
    u32                               ulDeviceType;
    //CIP_ACTIVE_DEVICES                active_device = {0};
    u32 dwBufferSize = 0;
    u32 mode_num = 0;
	struct output_info_t *output_info;

    dpu_adapter->support_device = DPU_PORT_0 | DPU_PORT_1 | DPU_PORT_2;

    //refine this logic later, set these when detect
    dpu_adapter->active_output[0] = 0;
    dpu_adapter->active_output[1] = 0;
    dpu_adapter->active_output[2] = 0;

    for (i = 0; i < PORT_NUM; i++)
    {
        memset(&dpu_adapter->current_output_info[i], 0 , sizeof(struct output_info_t));
        dpu_adapter->current_output_info[i].connect_status = DISCONNECTED;
        dpu_adapter->current_output_info[i].power_status = POWER_OFF;
    }

    memset(&devDetect, 0, sizeof(devDetect));
    devDetect.detect_device = dpu_adapter->support_device;
    devDetect.fake_device = DPU_PORT_0;

    DPU_OK == dpu_detect_device(dpu_adapter->dpu_manager, &devDetect);

    device = devDetect.connected_device;
    while (device)
    {
        temp = tt_get_last_bit(device);

        device &= ~temp;

		output_info = &dpu_adapter->current_output_info[tt_get_bit_index(temp)];

        dpu_get_modes(dpu_adapter->dpu_manager, &output_info->mode_list, temp);

        mode_num = output_info->mode_list.num;

		if (output_info->mode_list.modes != NULL)
		{
			free(output_info->mode_list.modes);
			output_info->mode_list.modes = NULL;
		}

        output_info->mode_list.modes = 
            (struct dpu_display_mode_t*)malloc(mode_num * sizeof(struct dpu_display_mode_t));

        memset(output_info->mode_list.modes, 0, mode_num * sizeof(struct dpu_display_mode_t));
        dpu_get_modes(dpu_adapter->dpu_manager, &output_info->mode_list, temp);

		output_info->display_caps.device = temp;
		dpu_query_display_info(dpu_adapter->dpu_manager, &output_info->display_caps);

        output_info->device = temp;
		output_info->connect_status = CONNECTED;
    }

	device = dpu_adapter->support_device;
	while (device) {
		temp = tt_get_last_bit(device);
		device &= ~temp;
		dpu_info(INFO_LEVEL,"device 0x%x %s\n", temp, (devDetect.connected_device & temp) ? "connected" : "not detect");
	}
}

void_t dm_deinit_output(struct dpu_adapter_t *dpu_adapter)
{
	int i;
	struct output_info_t *output_info;

	for (i = 0; i < PORT_NUM; i++)
	{
		output_info = &dpu_adapter->current_output_info[i];

		if (output_info->mode_list.modes != NULL)
		{
			free(output_info->mode_list.modes);
			output_info->mode_list.modes = NULL;
		}
	}

}

void init_dm(struct dpu_adapter_t *dpu_adapter)
{

    if (dpu_adapter->test_domain & TEST_WITHOUT_DE)
    {
        return;
    }

    dm_init_sw(dpu_adapter);

    dm_init_hw(dpu_adapter);

    dm_init_crtc(dpu_adapter);

    dm_init_plane(dpu_adapter);

    dm_init_output(dpu_adapter);
}


void deinit_dm(struct dpu_adapter_t *dpu_adapter)
{
	if (dpu_adapter->test_domain & TEST_WITHOUT_DE)
	{
		return;
	}

	dm_deinit_output(dpu_adapter);
	dm_deinit_hw(dpu_adapter);
	dm_deinit_sw(dpu_adapter);
}
