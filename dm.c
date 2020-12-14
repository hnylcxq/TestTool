#include"dpu/dpu.h"
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



void dm_query_crtc_info(struct dpu_adapter_t * dpu_adapter)
{
    //dpu_query_crtc_info() from dpu.c
    //crtc_num,  plane num of each crtc

    dpu_adapter->num_crtc = 3;
    dpu_adapter->num_plane[0] = 2;
    dpu_adapter->num_plane[1] = 2;
    dpu_adapter->num_plane[2] = 2;

}


i32 dm_init_sw(struct dpu_adapter_t *dpu_adapter)
{
    i32 ret = 0;
    void *p = NULL;

    CBIOS_INITIALIZATION_PARA       CBiosInitPara = {0};
    memset(&CBiosInitPara.CBiosCallbacks, 0, sizeof(CBIOS_CALLBACK_FUNCTIONS));

    CBiosInitPara.CBiosCallbacks.Size                         = sizeof(CBIOS_CALLBACK_FUNCTIONS);
    CBiosInitPara.CBiosCallbacks.pFnDbgPrint                  = (void*)temp_print;
    CBiosInitPara.CBiosCallbacks.pFnDelayMicroSeconds         = (void*)tt_delay_micro_seconds;
    CBiosInitPara.CBiosCallbacks.pFnReadUchar                 = (void*)tt_read_u8;
    CBiosInitPara.CBiosCallbacks.pFnReadUshort                = (void*)tt_read_u16;
    CBiosInitPara.CBiosCallbacks.pFnReadUlong                 = (void*)tt_read_u32;
    CBiosInitPara.CBiosCallbacks.pFnWriteUchar                = (void*)tt_write_u8;
    CBiosInitPara.CBiosCallbacks.pFnWriteUshort               = (void*)tt_write_u16;
    CBiosInitPara.CBiosCallbacks.pFnWriteUlong                = (void*)tt_write_u32;
    CBiosInitPara.CBiosCallbacks.pFnReadBufferUlong           = (void*)tt_read_buffer_u32;
    CBiosInitPara.CBiosCallbacks.pFnWriteBufferUlong          = (void*)tt_write_buffer_u32;
    CBiosInitPara.CBiosCallbacks.pFnQuerySystemTime           = NULL;
    CBiosInitPara.CBiosCallbacks.pFnAllocateNonpagedMemory    = (void*)tt_malloc_mem;
    CBiosInitPara.CBiosCallbacks.pFnAllocatePagedMemory        = (void*)tt_malloc_mem;
    CBiosInitPara.CBiosCallbacks.pFnFreePool                  = (void*)tt_free_mem;
    CBiosInitPara.CBiosCallbacks.pFnReadPortUchar             = (void*)tt_read_io;
    CBiosInitPara.CBiosCallbacks.pFnWritePortUchar            = (void*)tt_write_io;
    CBiosInitPara.CBiosCallbacks.pFnGetRegistryParameters     = NULL;
    CBiosInitPara.CBiosCallbacks.pFnSetRegistryParameters     = NULL;
    CBiosInitPara.CBiosCallbacks.pFnStrcmp                    = (void*)strcmp;
    CBiosInitPara.CBiosCallbacks.pFnStrcpy                    = (void*)strcpy;
    CBiosInitPara.CBiosCallbacks.pFnStrncmp                   = (void*)strncmp;
    CBiosInitPara.CBiosCallbacks.pFnMemset                    = (void*)memset;
    CBiosInitPara.CBiosCallbacks.pFnMemcpy                    = (void*)memcpy;
    CBiosInitPara.CBiosCallbacks.pFnMemcmp                    = (void*)memcmp;
    CBiosInitPara.CBiosCallbacks.pFnVsprintf                  = (void*)vsprintf;
    CBiosInitPara.CBiosCallbacks.pFnVsnprintf                 = (void*)vsnprintf;

    memset(&CBiosInitPara.CBiosParamInit, 0, sizeof(CBIOS_PARAM_INIT));
    CBiosInitPara.CBiosParamInit.pAdapterContext = dpu_adapter;


    dpu_info("dpu_adapter is %p\n",dpu_adapter);
    CBiosInitPara.CBiosParamInit.MAMMPrimaryAdapter = dpu_adapter->base.flags.is_primary; 

    CBiosInitPara.CBiosParamInit.GeneralChipID   = 0x3A04;
    CBiosInitPara.CBiosParamInit.ChipID          = CHIPID_CHX002;

    CBiosInitPara.CBiosParamInit.bRunOnQT = FALSE;
    
    CBiosInitPara.CBiosParamInit.PCIDeviceID             = dpu_adapter->base.device_id;
    CBiosInitPara.CBiosParamInit.ChipRevision            = dpu_adapter->base.revision_id;
    CBiosInitPara.CBiosParamInit.RomImage                = NULL; 
    CBiosInitPara.CBiosParamInit.RomImageLength          = 0;
    CBiosInitPara.CBiosParamInit.pSpinLock               = NULL;
    CBiosInitPara.CBiosParamInit.Size                    = sizeof(CBIOS_PARAM_INIT);

    CBiosInitialize(&CBiosInitPara);
    dpu_adapter->dpu_manager = CBiosInitPara.pCBiosExtension;

    dpu_info("init cbios init , pcbe is %p\n", dpu_adapter->dpu_manager);


//    sw_para.dm_adapter = dpu_adapter;
//    sw_para.board_version = 0;
//    sw_para.chip_revision = 0;
//    sw_para.device_id = 0;
//    sw_para.vender_id = 0;
//    sw_para.sub_device_id = 0;
//    sw_para.sub_vender_id = 0;
//    sw_para.is_mamm_primary = 0;
//    sw_para.is_qt_test = 0;

   // p = dpu_mgr_init(&sw_para);

    return 0;
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
        memset(&dpu_adapter->current_crtc_info[i].hw_mode, 0 , sizeof(struct mode_info_t));
        memset(&dpu_adapter->current_crtc_info[i].adjust_mode, 0 , sizeof(struct mode_info_t));
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
    u32 i = 0;
    u32 device = 0, temp = 0;
    CIP_DEVICES_DETECT_PARAM            devDetect;
    u32                               ulDeviceType;
    CIP_ACTIVE_DEVICES                active_device = {0};
    u32 dwBufferSize = 0;

    dpu_adapter->support_device = 0x18001;    //hard code CBIOS_TYPE_CRT | CBIOS_TYPE_DP5 | CBIOS_TYPE_DP6;
    dpu_adapter->active_output[0] = 0;


    for (i = 0; i < PORT_NUM; i++)
    {
        memset(&dpu_adapter->current_output_info[i], 0 , sizeof(struct output_info_t));
        dpu_adapter->current_output_info[i].connect_status = DISCONNECTED_STATUS;
        dpu_adapter->current_output_info[i].power_status = POWER_OFF;
    }
   

    //TODO: need detect para
   // dpu_detect_device(dpu_adapter->dpu_manager);



    memset(&devDetect, 0, sizeof(CIP_DEVICES_DETECT_PARAM));
    devDetect.Size = sizeof(CIP_DEVICES_DETECT_PARAM);
    devDetect.DevicesToDetect = dpu_adapter->support_device;
 //   devDetect.FullDetect = 1;

    if(CBIOS_OK == CBiosDetectAttachedDisplayDevices(dpu_adapter->dpu_manager, &devDetect))
    {
        dpu_info("detect device is 0x%x\n", devDetect.DetectedDevices);
    }

    device = devDetect.DetectedDevices;
    while (device)
    {
        temp = tt_get_last_bit(device);
        //i  = tt_get_bit_index(device);

        //hardcode here

        if (temp & 0x1)
        {
            i = 0;
        }
        else if (temp & 0x8000)
        {
            i = 1;
        }
        else if (temp & 0x10000)
        {
            i = 2;
        }
            

        device &= ~temp;

        CBiosGetDeviceModeListBufferSize(dpu_adapter->dpu_manager, temp, &dwBufferSize);
       // dpu_adapter->current_output_info[i].num_modes = dwBufferSize;

        dpu_adapter->current_output_info[i].modes = (PCBiosModeInfoExt)malloc(dwBufferSize);
        dpu_adapter->current_output_info[i].device = temp;
        memset(dpu_adapter->current_output_info[i].modes, 0, dwBufferSize);
        CBiosGetDeviceModeList(dpu_adapter->dpu_manager, temp, dpu_adapter->current_output_info[i].modes, &dwBufferSize);
        dpu_adapter->current_output_info[i].num_modes = dwBufferSize/sizeof(CBiosModeInfoExt);
    }
    

    
    dpu_adapter->active_output[0] = 0x8000 & devDetect.DetectedDevices;
    dpu_adapter->active_output[1] = 0x10000 & devDetect.DetectedDevices;
    dpu_adapter->active_output[2] = 0x1 & devDetect.DetectedDevices;

    active_device.DeviceId[0] = dpu_adapter->active_output[0];
    active_device.DeviceId[1] = dpu_adapter->active_output[1];
    active_device.DeviceId[2] = dpu_adapter->active_output[2];

    dpu_info("active is %d %d %d\n",active_device.DeviceId[0],active_device.DeviceId[1],active_device.DeviceId[2]);    

    CBiosSetActiveDevice(dpu_adapter->dpu_manager, &active_device);
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
