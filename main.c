#include"types.h"
#include"util.h"


struct dpu_adapter_t  *g_dpu_adapter = NULL;

void deinit_adapter()
{
    if (g_dpu_adapter)
    {
        free(g_dpu_adapter);
        g_dpu_adapter = NULL;
    }
}

struct dpu_adapter_t* init_adapter(int run_on_qt)
{
	g_dpu_adapter = (struct dpu_adapter_t*)malloc( sizeof(struct dpu_adapter_t));
	
	if(g_dpu_adapter == NULL)
	{
		dpu_error("%s failed to alloc mem space for dpu adapter\n",__FUNCTION__);
		return NULL;
	}
	
	memset(g_dpu_adapter, 0, sizeof(struct dpu_adapter_t));
	
	g_dpu_adapter->flags.run_on_qt = run_on_qt ? 1: 0;
	
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
            dpu_error("fatal error:  enable card failed !!!\n");
            ret = TT_FAIL;
        }
    }

    return ret;
#endif
}

TT_STATUS init_card_info()
{
	u32 found = 0;
    TT_STATUS ret = TT_PASS;
	
	found = tt_get_pci_info(&g_dpu_adapter->base);
	
	if (!found)
	{
		dpu_error("couldn't found video card \n");
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

void init_card(struct dpu_adapter_t *dpu_adapter)
{

    if (dpu_adapter->test_domain & TEST_DOS_ONLY)
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




extern void process_cmd(struct dpu_adapter_t *dpu_adapter);


u32 handle_param(int argc, char** argv)
{
    u32 ret = 0;


    if (argc < 2)
    {
        ret |= TEST_DOS_ONLY;
    }

	if (argc >= 2)
	{
		if (strcmp(argv[1], "de") == 0)
		{
			ret |= TEST_DE ;
		}
	}


	if (argc >= 3)
	{
		if (strcmp(argv[2], "qt") == 0)
		{
			ret |= TEST_DE_WITH_QT ;
		}
	}

    return ret;
    
}

void main(int argc, char** argv)
{
	u32 run_on_qt = 0 ;
	struct dpu_adapter_t *p;
	TT_STATUS ret = TT_PASS;
    u32 test_domain = 0;


    test_domain = handle_param(argc, argv);

    run_on_qt = test_domain & TEST_DE_WITH_QT;

#ifdef OUTPUT_UART
	bios_helper_init();
#endif

	p = init_adapter(run_on_qt);
	if (!p)
	{
		dpu_error("init adapter failed \n");
		goto end;
	}

    p->test_domain = test_domain;

	ret = init_card_info();
    if (ret == TT_FAIL)
    {
        dpu_error("init card info faild ");
        //goto end;//we use DOS box to test pure software logic, comment here temperary, restore it after board ready
    }

    dpu_info("mmio base is 0x%x   fb base is 0x%x  size 0x%x\n", p->base.mmio_base, p->base.fb_base, p->base.fb_size);

    init_card(p);

    init_dm(p);

    init_surfaces(p);
    
    init_cached_cmd(p);
    
    init_video_memory(p);

    process_cmd(p);



    deinit_dm(p);

    deinit_video_memory();

end:
	deinit_adapter();
	return;
}
