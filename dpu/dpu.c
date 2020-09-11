
#include<stdio.h>
#include"dpu.h"

struct dpu_cb_funs_t*  g_dpu_cb_funs = NULL;


#define dpu_printf  printf




DPU_STATUS dpu_set_cb(struct dpu_cb_funs_t *dpu_cb)
{
    //do some check 

   //set to  callback func.c

    //
}

#if 0

void* dpu_init_sw()
{
    struct dpu_manager_t *dpu_manager;

    dpu_manager = (struct dpu_manager_t*) malloc(sizeof(struct dpu_manager_t));
    
    return dpu_manager;
}



void dpu_detect_device()
{
    
}


void de_ip_init()
{
	dpm->crtc_manager.hw_init();   // use chip releated func here     set bg color here ?
	dpm->conn_manager.hw_init();   // use chipshare func here          Port Init 
	dpm->plane_manager.hw_init();                                      //disable stream , call chip func ,chose mmio path etc.
	dpm->encoder_manager.hw_init();
    dpm->init_i2c_manager.hw_init();  
    dpm->init_mdi_manager.hw_init();	//timeout, threshold, proprity,
		
}


void dpu_init_hw()
{
    u8 need_post;
    
    de_wait_memory_done();
	
	need_post = need_de_post();
	do_de_post(need_post);
	de_ip_init();
}


#endif

DPU_STATUS dpu_set_virt_mode(struct dpu_manager_t *dpu_manager, struct dpu_virt_mode_t *mode)
{

    dpu_printf("in %s\n",__func__);
    return DPU_OK;

}

DPU_STATUS dpu_set_real_mode(struct dpu_manager_t *dpu_manager, struct dpu_real_mode_t *mode)
{
    dpu_printf("in %s\n",__func__);
    return DPU_OK;
}


DPU_STATUS dpu_update_plane(struct dpu_manager_t* dpu_manager, struct dpu_plane_t* plane_info)
{

    dpu_printf("in %s\n",__func__);
    return DPU_OK;
}

DPU_STATUS dpu_set_device(struct dpu_manager_t *dpu_manager ,struct dpu_device_set_t* device_set)
{
    dpu_printf("in %s\n",__func__);
    return DPU_OK;
}


DPU_STATUS dpu_set_i2c(struct dpu_manager_t *dpu_manager, struct dpu_i2c_para_t *i2c_para)
{
    dpu_printf("in %s\n",__func__);
    return DPU_OK;
}

DPU_STATUS dpu_set_aux(struct dpu_manager_t *dpu_manager, struct dpu_aux_para_t *aux_para)
{
    dpu_printf("in %s\n",__func__);
    return DPU_OK;
}


DPU_STATUS dpu_set_cursor(struct dpu_manager_t *dpu_manager, struct dpu_cursor_para_t  *cursor_para)
{
    dpu_printf("in %s\n",__func__);
    return DPU_OK;
}


