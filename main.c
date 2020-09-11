#include"types.h"
#include"util.h"




struct dpu_adapter_t  *g_dpu_adapter = NULL;

void help(void)
{
	dpu_info();

}


void deinit_adapter()
{

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
    u8 mm850c = 0;
    TT_STATUS ret = TT_PASS;

    mm850c = tt_read_mmio_byte(base_adapter->mmio_base, 0x850c);

    if (!(mm850c & 0x2))
    {
        tt_write_mmio_byte(base_adapter->mmio_base, 0x850c, mm850c | 0x02, 0);

        tt_delay_micro_seconds(1);
        
        mm850c = tt_read_mmio_byte(base_adapter->mmio_base£¬ 0x850c);
        if (!(mm850c & 0x02))
        {
            dpu_error("fatal error:  enable card failed !!!\n");
            ret = TT_FAIL;
        }
    }

    return ret;
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


    tt_init_card();

    return ret;
}

void main(int argc, char** argv)
{
	u32 run_on_qt = 0 ;
	struct dpu_adapter_t *p;
    TT_STATUS ret = TT_PASS;
	
	run_on_qt = 0;
	if (argc == 2)
	{
		if (strcmp(argv[1], "QT") == 0)
		{
			run_on_qt = 1;
		}
	}
	
    bios_helper_init();

	p = init_adapter(run_on_qt);
	if (!p)
	{
		dpu_error("init adapter failed \n");
		goto end;
	}
	
	ret = init_card_info();
    if (ret == TT_FAIL)
    {
        dpu_error("init card info faild ");
    }

    init_dm(p);

   	init_video_memory(p);


    process_cmd(p);
    


    deinit_dm(p);
    deinit_video_memory();

end:
	deinit_adapter();
	
}