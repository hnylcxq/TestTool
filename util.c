#include<stdio.h>
#include<string.h>
#include<stdarg.h>

//#include"types.h"
#include"util.h"

#define LOG_BUFFER_SIZE     256


struct platform_funcs_t   *platform_funcs = NULL;

extern struct dpu_adapter_t  *g_dpu_adapter;


u32 tt_strhash(u8 *str)
{
    u32 i,l;
    u32 ret=0;
    u16 *s;


    if (str == NULL)
    {
        return 0;
    }

    l=(strlen(str)+1)/2;                    

    s=(u16 *)str;

    for (i=0; i<l;i++)
    {
        ret^=(s[i] << (i & 0x0f));
    }
    return ret;
} 


BOOL tt_is_same_str(u8 *str1, u8 *str2)
{
    if (tt_strhash(str1) == tt_strhash(str2))
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}


u32  tt_get_bit_index(u32 value)
{
    u32 last_bit = GET_LAST_BIT(value);
    u32 count = 0;

    while(last_bit)
    {
        last_bit = last_bit >> 1;
        count ++;
    }

    return count;

}


u8 tt_get_bit_num(u32 value)
{
    u8 num;
    
    for(num = 0; value != 0; num++)
    {
        value &= ~(GET_LAST_BIT(value));
    }
    
    return num;
}

TT_STATUS tt_get_words(u8* cmd_line, u32 *word_num, u8 str[][MAX_CMD_OPTION_NAME_SIZE])
{
    u32 i;
	u8   *word;
    u8   filter[] = " ,\t\n";
	TT_STATUS ret = TT_PASS;

	word = strtok(cmd_line, filter);
	if(word != NULL)
	{
		strcpy(str[0], word);
	}
	else
	{
		*word_num = 0;
		ret = TT_PASS;
		goto end;
	}

	if (str[0][0] == 'q' || str[0][0] == 'Q')
	{
		ret = TT_FAIL;
		goto end;
	}

	i = 1;
	while(word != NULL)
	{
		word = strtok(NULL, filter);
		if(word != NULL)
		{
			strcpy(str[i], word);
			i++;
		}
	}
	*word_num = i;

end:
	return ret;
	
}

BOOL tt_is_comment(u8 words[][SCRIPT_MAX_WORD_SIZE])
{
    BOOL ret = FALSE;
    
    if (words[0][0] == '#')
    {
        ret = TRUE;
    }

    return ret;
    
}

BOOL tt_is_end_with(const u8 *str1, u8 *str2)
{
	u32 len1 = strlen(str1);
	u32 len2 = strlen(str2);

    if(str1 == NULL || str2 == NULL)
    {
        return FALSE;
    }
	
    if((len1 < len2) ||  (len1 == 0 || len2 == 0))
	{
		return FALSE;
	}

    while(len2 >= 1)
    {
        if(str2[len2 - 1] != str1[len1 - 1])
        {
			return FALSE;
		}
        len2--;
        len1--;
    }
    return TRUE;
}



struct format_info_t g_format_info[FORMAT_NUM] = {
        {1, "FORMAT_INVALID"},//FORMAT_INVALID
        {8, "RGB8"},         //FORMAT_P8
        {16, "RGB565"},      //FORMAT_R5G6B5
        {16, "ARGB1555"},    //FORMAT_A1R5G5B5
        {32, "ARGB8888"},    //FORMAT_A8R8G8B8
        {32, "ABGR8888"},    //FORMAT_A8B8G8R8
        {32, "XRGB8888"},    //FORMAT_X8R8G8B8
        {32, "XBGR8888"},    //FORMAT_X8B8G8R8
        {32, "ARGB2101010"}, //FORMAT_A2R10G10B10
        {32, "ABGR2101010"}, //FORMAT_A2B10G10R10
        {16, "CRYCBY422_16"},//FORMAT_CRYCBY422_16
        {16, "YCRYCB422_16"},//FORMAT_YCRYCB422_16
        {32, "CRYCBY422_32"},//FORMAT_CRYCBY422_32
        {32, "YCRYCB422_32"},//FORMAT_YCRYCB422_32
        {32, "CRYCB8888"},   //FORMAT_CRYCB8888_32
        {32, "YCBCR2101010_32"},//FORMAT_YCBCR2101010_32
};


//used for de cb

extern u32 g_output_uart;
void dpu_info(int level, u8 *fmt, ...)
{
	va_list args;
	u8 buff[LOG_BUFFER_SIZE];
	
	if (level > g_dpu_adapter->log_level)
	{
		return;
	}

	memset(buff, 0, LOG_BUFFER_SIZE);  
	va_start(args, fmt);
	vsnprintf(buff, LOG_BUFFER_SIZE -1, fmt, args); 
	va_end(args); 
	

	if (g_output_uart)
	{
		platform_funcs->platform_print(buff);
	}
	else 
	{
		printf("%s", buff);
		fflush(stdout);
	}
}

void tt_get_system_time(u64 * time)
{
    platform_funcs->platform_get_system_time(time);
}


void tt_delay_micro_seconds(u32 value)
{
	platform_funcs->platform_delay_micro_seconds(value);
}


//need handle cache state ?
#if 0
TT_CACHE_FLAG tt_get_cache_state()
{
	u32 cache_state = 0;
	
	cache_state = bios_get_cache_state();
	
	return cache_state ? CACHE_ENABLE : CACHE_DISABLE;
}

void tt_set_cache(TT_CACHE_FLAG flag)
{
	u32 cache_state = 0 ;
	
	if (flag == CACHE_ENABLE)
	{
		cache_state = 1;
	}
	else
	{
		cache_state = 0;
	}
	
	bios_set_cache_state(cache_state);
}

#endif


void tt_write_u8(void * adapter, u32 register_port, u8 value)
{
	struct dpu_adapter_t * dpu_adapter = (struct dpu_adapter_t *)adapter;
	volatile u8 * port = NULL;
	
	port = (u8 *)((u8*)dpu_adapter->base.mmio_base+ register_port);
	*port = value;
}


void tt_write_u32(void * adapter, u32 register_port, u32 value)
{
	struct dpu_adapter_t * dpu_adapter = (struct dpu_adapter_t *)adapter;
	volatile u32 * port = NULL;
	u32 ul_align_mask = sizeof(u32) - 1;
	
	port = (u32 *)((u8*)dpu_adapter->base.mmio_base + register_port);
	if ((u32)port & ul_align_mask)
	{
		dpu_info(ERROR_LEVEL,"The port address 0x%x is not aligned \n",register_port);
	}
	*port = value;
	
}

u32 tt_read_u32(void * adapter, u32 register_port)
{
	struct dpu_adapter_t * dpu_adapter = (struct dpu_adapter_t *)adapter;
	volatile u32 * port = NULL;
	u32  ul_align_mask = sizeof(u32) - 1;
	u32  value = 0;

	//printf("dpu_adapter, 0x%x dpu_adapter->base.mmio_base is 0x%x 0x%x\n",dpu_adapter, dpu_adapter->base.mmio_base, register_port);
	port = (u32 *)((u8*)dpu_adapter->base.mmio_base + register_port);
	if ((u32)port & ul_align_mask)
	{
		dpu_info(ERROR_LEVEL,"The port address 0x%x is not aligned  %p mask 0x%x\n",register_port,port,ul_align_mask);
	}
	
	value = *port;
	return value;
	
}

u8 tt_read_u8(void * adapter, u32 register_port)
{
	struct dpu_adapter_t * dpu_adapter = (struct dpu_adapter_t *)adapter;
	volatile u8 * port = NULL;
	u8 value = 0 ;
	
	port = (u8 *)((u8*)dpu_adapter->base.mmio_base + register_port);
	
	value = *port;
	return value;
}

void tt_read_u16(void * adapter, u32 register_port)
{
	struct dpu_adapter_t * dpu_adapter = (struct dpu_adapter_t *)adapter; 
	volatile u16 * port = NULL;
	u16 value;
	u16  ul_align_mask = sizeof(u16) - 1;
	
	port = (u16 *)((u8*)dpu_adapter->base.mmio_base + register_port);
	if ((u32)port & ul_align_mask)
	{
		dpu_info(ERROR_LEVEL,"The port address 0x%x is not aligned \n",register_port);
	}
	value = *port;
}

void tt_write_u16(void * adapter, u32 register_port, u16 value)
{
	struct dpu_adapter_t * dpu_adapter = (struct dpu_adapter_t *)adapter; 
	volatile u16 * port = NULL;
	u32  ul_align_mask = sizeof(u16) - 1;
	
	port = (u16 *)((u8*)dpu_adapter->base.mmio_base + register_port);
	if ((u16)port & ul_align_mask)
	{
		dpu_info(ERROR_LEVEL,"The port address 0x%x is not aligned \n",register_port);
	}
	*port = value;
}

u32 tt_read_buffer_u32(volatile u32 *register_port)
{
	u32 value = 0;
	u32 ul_align_mask = sizeof(u32) - 1;
	
	if ((u32)register_port & ul_align_mask)
	{
		dpu_info(ERROR_LEVEL,"The mem address 0x%x is not aligned \n",register_port);
	}
	value = *register_port;
	return value;
}

void tt_write_buffer_u32(volatile u32 * register_port, u32 value)
{
	u32 ul_align_mask = sizeof(u32) - 1;
	
	if ((u32)register_port & ul_align_mask)
	{
		dpu_info(ERROR_LEVEL,"The mem address 0x%x is not aligned \n",register_port);
	}
	*register_port = value;
}


u8 tt_read_io_byte(u16 register_port)
{
	return platform_funcs->platform_read_io_byte(register_port);
}

void tt_write_io_byte(u16 register_port, u8 value)
{
	platform_funcs->platform_write_io_byte(register_port, value);
}

u32 tt_read_io_dword(u16 register_port)
{
	return platform_funcs->platform_read_io_dword(register_port);
}

void tt_write_io_dword(u16 register_port, u32 value)
{
	platform_funcs->platform_write_io_dword(register_port, value);
}


u8 tt_read_mmio_byte(u32 base, u32 port)
{
    u8 value = 0;

    value = *((u8 *)(base + port));
    return value;
}

void tt_write_mmio_byte(u32 base, u32 port, u8 value, u8 mask)
{
    u8 temp = 0;

    temp = *((u8 *)(base + port));
    temp = temp & mask;
    temp = temp | value;

    *((u8 *)(base + port)) = temp;
}

u32 tt_read_mmio(u32 base , u32 port)
{
    return *((u32*)(base + port));
}

void tt_write_mmio(u32 base, u32 port, u32 value, u32 mask)
{
    u32 temp;

    temp = *((u32*)(base + port));
    temp = temp & mask;
    value = value & ~mask;
    temp = temp | value;
    *((u32*)(base + port)) = temp;
}

void * tt_malloc_mem(u32 bytes)
{
	void * p = malloc(bytes);
	
	if (!p)
	{
		dpu_info(ERROR_LEVEL," malloc memory failed \n");
	}
	memset(p, 0, bytes);
	return p;
}

void * tt_free_mem(void *p)
{
	if (p)
	{
		free(p);
	}
}

u32  tt_get_last_bit(u32  value)
{
    u32  result = 0;
    if( value)
    {
        result = value & ~(value -1);
    }
    return result;
}

void tt_read_pci_config_byte(u8 bus, u8 dev, u8 func, u16 reg, u8* data)
{
    platform_funcs->platform_read_pci_config_byte(bus, dev, func, reg, data);
}

void tt_read_pci_config_word(u8 bus, u8 dev, u8 func, u16 reg, u16 *data)
{
	platform_funcs->platform_read_pci_config_word(bus, dev, func, reg, data);
}

void tt_read_pci_config_dword(u8 bus, u8 dev, u8 func, u16 reg, u32 *data)
{
	platform_funcs->platform_read_pci_config_dword(bus, dev, func, reg, data);
}

void tt_write_pci_config_byte(u8 bus, u8 dev, u8 func, u16 reg, u8 data)
{
    platform_funcs->platform_write_pci_config_byte(bus, dev, func, reg, data);
}

void tt_write_pci_config_word(u8 bus, u8 dev, u8 func, u16 reg, u16 data)
{
    platform_funcs->platform_write_pci_config_word(bus, dev, func, reg, data);
}

void tt_write_pci_config_dword(u8 bus, u8 dev, u8 func, u16 reg, u32 data)
{
    platform_funcs->platform_write_pci_config_dword(bus, dev, func, reg, data);
}

TT_STATUS tt_get_linear_addr(u64 phy_addr, u32 size, void **linear_addr)
{
	return platform_funcs->platform_get_linear_addr(phy_addr, size, linear_addr);
}
static u32 get_bar_size(u32 bus, u32 dev, u32 func,u32 fb)
{
    u32 temp, value, size;
	u32 offset = 0x10;

	if (fb == 1)
	{
		offset = 0x14;
	}

    tt_read_pci_config_dword(bus, dev, func, offset, &temp);
    value = temp;
    tt_write_pci_config_dword(bus, dev, func, offset, 0xFFFFFFFF);
    tt_read_pci_config_dword(bus, dev, func, offset, &temp);

    size = (~temp | 0xF) + 1;
    tt_write_pci_config_dword(bus, dev, func, offset, value);

    return size;

}


u32 tt_get_pci_info(struct base_adapter_t *base_adapter)
{
	u32 found = 0;
	u32 bus, dev, func;
	u32 data_out, data_in;
	u8 i, j, k, bcid, scid, sbn;
	u16 vendor_id, device_id;
	u32 value,size;
	void* temp;

	for (bus = 0; bus < PCI_MAX_BUS_NUM; ++bus)
	{
		for (dev = 0; dev < PCI_MAX_DEVICE_NUM; ++dev)
		{
			for (func = 0; func < PCI_MAX_FUNCTION_NUM; ++func)
            {
                data_out = (bus << 16) + (dev << 11) + (func << 8);
                data_out |= 0x80000000;

                tt_write_io_dword(CONFIG_ADDRESS, data_out);
                data_in = tt_read_io_dword(CONFIG_DATA);

                //dpu_info(INFO_LEVEL,"data_in is 0x%x\n",data_in);

                if ((data_in & 0xFFFF) == VENDER_XX)
                {
                    tt_write_io_dword(CONFIG_ADDRESS, data_out + 0x8);
                    if ((tt_read_io_dword(CONFIG_DATA) & 0xFF000000) == 0x03000000)
                    {
                        base_adapter->vender_id = (u16)(data_in & 0xFFFF);
                        base_adapter->device_id = (u16)((data_in & 0xFFFF0000)>>16);
                        base_adapter->revision_id = (u16)(tt_read_io_dword(CONFIG_DATA) & 0xFF);
                        base_adapter->bus_num= bus;
                        base_adapter->dev_num = dev;
                        base_adapter->func_num = func;

                        tt_write_io_dword(CONFIG_ADDRESS, data_out + 4);
                        if (tt_read_io_dword(CONFIG_DATA) & 0x01)
                        {
                            base_adapter->flags.is_primary = 1;
                        }
                        else
                        {
                            base_adapter->flags.is_primary = 0;
                        }

                        found = 1;
                        goto done_1;
                        
                    }
                }
                
            }         
		}
	}
	
done_1:

    if (found == 0)
    {
        dpu_info(INFO_LEVEL,"couldn't found card \n");
        return 0;
    }

    
	for (i = 0; i < PCI_MAX_BUS_NUM; ++i)
    {
        for (j = 0; j < PCI_MAX_DEVICE_NUM; ++j)
        {
            for (k = 0; k < PCI_MAX_FUNCTION_NUM; ++k)
            {
                tt_read_pci_config_word(i, j, k, PCI_VENDOR_ID_OFFSET, &vendor_id);
                if (vendor_id == 0xFFFF)
                {
                    continue;
                }
                tt_read_pci_config_word(i, j, k, PCI_DEVICE_ID_OFFSET, &device_id);
                tt_read_pci_config_byte(i, j, k, PCI_CLASS_DEVICE_OFFSET, &scid);
                tt_read_pci_config_byte(i, j, k, PCI_BASE_CLASEE_OFFEST, &bcid);

                if (scid != 0x04 || bcid != 0x06)
                {
                    continue;
                }
                
                tt_read_pci_config_byte(i, j, k, 0x19, &sbn);

                if(sbn == base_adapter->bus_num)
                {
                    base_adapter->bridge_info.bus_num = i;
                    base_adapter->bridge_info.dev_num = j;
                    base_adapter->bridge_info.func_num = k;
                    goto done_2;
                }
            }
        }
    }   
	
done_2:
    //bar0 info
    tt_read_pci_config_dword(base_adapter->bus_num, base_adapter->dev_num, base_adapter->func_num, 0x10, &value);
	size = get_bar_size(base_adapter->bus_num, base_adapter->dev_num, base_adapter->func_num, 0);
    value = value & ~0xf; //mask flag bit
	if (TT_PASS == tt_get_linear_addr((u64)value, size, &temp))
    {
        base_adapter->mmio_base = temp;
		base_adapter->mmio_size = size;
		base_adapter->mmio_phy = value;

		dpu_info(INFO_LEVEL, "mmio phy_addr is 0x%x size 0x%x mmio vir_addr 0x%x\n", value, size, temp);
    }
    else
    {
        base_adapter->mmio_base = 0;
		base_adapter->mmio_size = 0;
        found = 0;
        goto exit;
    }
	
	//bar1 info

    tt_read_pci_config_dword(base_adapter->bus_num, base_adapter->dev_num, base_adapter->func_num, 0x14, &value);
    size = get_bar_size(base_adapter->bus_num, base_adapter->dev_num, base_adapter->func_num, 1);
	value = value & ~0xF;
    if (TT_PASS == tt_get_linear_addr((u64)value, size, &temp))
    {
        base_adapter->fb_base = temp;
        base_adapter->fb_size = size;
		base_adapter->fb_phy = value;
		dpu_info(INFO_LEVEL, "fb   phy_addr is 0x%x size 0x%x fb   vir_addr 0x%x\n", value, size, temp);
    }

exit:	

	return found;
	
}


void tt_enable_pci_bridge(struct base_adapter_t *base_adapter)
{
    u8 command, temp;

    //check weather the bridge is host bridge or not
    //we can't change host bridge pci space.

    if (!((base_adapter->bridge_info.bus_num == 0) && (base_adapter->bridge_info.dev_num ==0)))
    {
        do
        {
            tt_read_pci_config_byte(base_adapter->bridge_info.bus_num, 
                base_adapter->bridge_info.dev_num, base_adapter->bridge_info.func_num, PCI_COMMAND_OFFSET, &command);

            command |=0x07;
            tt_write_pci_config_byte(base_adapter->bridge_info.bus_num,
                base_adapter->bridge_info.dev_num, base_adapter->bridge_info.func_num, PCI_COMMAND_OFFSET, command);
            tt_read_pci_config_byte(base_adapter->bridge_info.bus_num, 
                base_adapter->bridge_info.dev_num, base_adapter->bridge_info.func_num, PCI_COMMAND_OFFSET, &temp);

        }while (command != temp);
    }
}


void tt_enable_mmio_access(struct base_adapter_t *base_adapter)
{
    u8 command;

    tt_read_pci_config_byte(base_adapter->bridge_info.bus_num, base_adapter->bridge_info.dev_num, base_adapter->bridge_info.func_num, PCI_COMMAND_OFFSET, &command);

    if ((command & 0x02) == 0)
    {
        command = command | 0x02;
        tt_write_pci_config_byte(base_adapter->bridge_info.bus_num,
                                   base_adapter->bridge_info.dev_num,
                                   base_adapter->bridge_info.func_num,
                                   PCI_COMMAND_OFFSET,
                                   command);
    }
}





u32  tt_alloc_video_mem(struct dpu_adapter_t *dpu_adapter, u32 size, u32 aligment)
{
    struct mem_segment_t * p_seg = NULL;
    u32    aligned_offset = 0;

    //dpu just support local memory 
    p_seg = &dpu_adapter->vidmm_mgr.mem_segments[LOCAL_SEGMENT];

    if (p_seg->init_done)
    {
        aligned_offset =  alloc_video_mem(p_seg, size, aligment);
    }

    return aligned_offset;

    
}

void  tt_free_video_mem(struct dpu_adapter_t *dpu_adapter, u32 aligned_offset)
{
    struct mem_segment_t * p_seg = NULL;

    p_seg = &dpu_adapter->vidmm_mgr.mem_segments[LOCAL_SEGMENT];

    if (p_seg->init_done)
    {
        free_video_mem(p_seg, aligned_offset);
    }
}


struct surface_info_t* alloc_surface(struct dpu_adapter_t *dpu_adapter)
{
    u32 i = 0;

    struct surface_info_t *surface = NULL;


    if (dpu_adapter->surface_manager.num >= MAX_SURFACE_NUM)
    {

        dpu_info(INFO_LEVEL,"please increase macro MAX_SURFACE_NUM \n");
        surface = NULL;
        return surface;
    }

    for (i = 0; i < MAX_SURFACE_NUM; i ++)
    {
        if (dpu_adapter->surface_manager.surfaces[i].valid == 0)
        {
            surface = &dpu_adapter->surface_manager.surfaces[i].surface;
            break;
        }
    }

    if (i == MAX_SURFACE_NUM)
    {
        dpu_info(ERROR_LEVEL,"Some wrong, please help check\n");
        surface = NULL;
    }
    else
    {
        dpu_adapter->surface_manager.surfaces[i].valid = 1;
        dpu_adapter->surface_manager.num++;
        
        surface->index = i;        
    }

    return surface;

}


TT_STATUS free_surface(struct dpu_adapter_t *dpu_adapter, u32 index)
{

    if (index >= MAX_SURFACE_NUM || dpu_adapter->surface_manager.surfaces[index].valid == 0)
    {
        dpu_info(ERROR_LEVEL,"%s:  invalid para \n",__func__);
        return TT_FAIL;
    }

    tt_free_video_mem(dpu_adapter, dpu_adapter->surface_manager.surfaces[index].surface.gpu_addr);

    dpu_adapter->surface_manager.surfaces[index].valid = 0;
    memset(&dpu_adapter->surface_manager.surfaces[index].surface, 0 , sizeof(struct surface_info_t));
    dpu_adapter->surface_manager.num--;
    
    return TT_PASS;
}



//color is 10bit RGB data, need translate to the format pixel
//if format is ycbcr422  pixel_1 is even pixel,  pixel_2 is odd pixel
//if format is rgb/ycbcr444, only pixel is valid.
TT_STATUS get_color_pixel(SURFACE_FORMAT format, u32 color, u32 *pixel_1, u32 *pixel_2)
{
    u32 temp = 0;
    u32 temp_2 = 0;
    u32 Y,CB,CR;
    TT_STATUS ret = TT_PASS;


    // 10bit RGB -> YCBCR 10bit formula ?

    //temp use 8bit
    Y  = RGB2Y(R_CHANNEL(color)>>2, G_CHANNEL(color)>>2, B_CHANNEL(color)>>2);
    CB = RGB2CB(R_CHANNEL(color)>>2, G_CHANNEL(color)>>2, B_CHANNEL(color)>>2);
    CR = RGB2CR(R_CHANNEL(color)>>2, G_CHANNEL(color)>>2, B_CHANNEL(color)>>2);


   // dpu_info(ERROR_LEVEL,"color is 0x%x, R 0x%x G 0x%x  B 0x%x \n",color,R_CHANNEL(color),G_CHANNEL(color),B_CHANNEL(color));
    
    //dpu_info(ERROR_LEVEL,"Y 0x%x CB 0x%x CR 0x%x \n",Y,CB,CR);

    
    switch(format)
    {
        case FORMAT_P8:
            *pixel_1 = ((R_CHANNEL(color) & 0x380) >> 1) |     //sample high 3bit
                       ((G_CHANNEL(color) & 0x380) >> 5) |
                       ((B_CHANNEL(color) & 0x300) >> 8);
            break;
        case FORMAT_R5G6B5:
            *pixel_1 = ((R_CHANNEL(color) & 0x3e0) << 6)|
                       ((G_CHANNEL(color) & 0x3f0) << 1) |
                       ((B_CHANNEL(color) & 0x3e0) >> 5);
            break;
#if 0
        case FORMAT_A1R5G5B5:   //hw no this format right ?

            *pixel_1 = ((R_CHANNEL(color) & 0x3e0) << 5) |
                       ((G_CHANNEL(color) & 0x3e0))|
                       ((B_CHANNEL(color) & 0x3e0) >> 5);
            break;
#endif
        case FORMAT_A8R8G8B8:
        case FORMAT_X8R8G8B8:

            *pixel_1 = ((R_CHANNEL(color) & 0x3fc) << 14) |
                       ((G_CHANNEL(color) & 0x3fc) << 6) |
                       ((B_CHANNEL(color) & 0x3fc) >> 2);
            break;
        case FORMAT_A8B8G8R8:
        case FORMAT_X8B8G8R8:

            *pixel_1 = ((B_CHANNEL(color) & 0x3fc) << 14) |
                       ((G_CHANNEL(color) & 0x3fc) << 6) |
                       ((R_CHANNEL(color) & 0x3fc) >> 2);
            break;
        case FORMAT_A2B10G10R10:

            *pixel_1 = ((B_CHANNEL(color) & 0x3ff) << 20)|
                       ((G_CHANNEL(color) & 0x3ff) << 10)|
                       ((R_CHANNEL(color) & 0x3ff));

            break;
        case FORMAT_A2R10G10B10:

            *pixel_1 = ((R_CHANNEL(color) & 0x3ff) << 20)|
                       ((G_CHANNEL(color) & 0x3ff) << 10)|
                       ((B_CHANNEL(color) & 0x3ff));

            break;
        case FORMAT_CRYCBY422_16:

            *pixel_1 = ((CR & 0xff) << 8) | (Y & 0xff);
            *pixel_2 = ((CB & 0xff) << 8) | (Y & 0xff);
            break;
        case FORMAT_YCRYCB422_16:

            *pixel_1 = ((Y & 0xff) << 8) | (CR & 0xff);
            *pixel_2 = ((Y & 0xff) << 8) | (CB & 0xff);
            break;

        //DPU don't support 16bit path
#if 0           
        case FORMAT_CRYCBY422_32:

            *pixel_1 = ((CR & 0xff) << 16) | ((Y & 0xff));
            *pixel_2 = ((CB & 0xff) << 22) | ((Y & 0xff));
            break;
        case FORMAT_YCRYCB422_32:

            *pixel_1 = ((Y & 0xff) << 22) | ((CR & 0xff) << 6);
            *pixel_2 = ((Y & 0xff) << 22) | ((CB & 0xff) << 6);
            break;
#endif
#if 0
        case FORMAT_YCBCR8888_32:

            *pixel_1 = ((Y & 0x3fc) << 14 )|
                       ((CB & 0x3fc) << 6) |
                       ((CR & 0x3fc) >> 2);
            break;
#endif
        case FORMAT_CRYCB8888_32:

            *pixel_1 =  ((CR & 0xff) << 16) |
                        ((Y  & 0xff) << 8) |
                        ((CB & 0xff) );
            break;
        //bit map is crycb
        case FORMAT_YCBCR2101010_32:

            *pixel_1 = ((CR & 0xff) << 22) |
                       ((Y & 0xff) << 12) |
                       (CB & 0xff)<< 2;
            break;
#if 0            
        case FORMAT_CRYCB2101010_32:
            *pixel_1 =  ((CR & 0x3ff) << 20) |
                        ((Y & 0x3ff) << 10) |
                        (CB & 0x3ff);
            break;
#endif            
        default:

            dpu_info(ERROR_LEVEL,"unknow format \n");
            ret = TT_FAIL;
            break;
    }
    return ret;
}



//draw_point, draw_rect width = 1, height = 1, draw one point
void draw_rect(struct surface_info_t *surface, struct rect_t *rect, u32 color)
{
    u32 pixel_1, pixel_2;
    TT_STATUS ret;
    u32 i,j;
    u32 draw_8bit = 0;
    u32 draw_16bit = 0;
    u32 draw_32bit = 0;
    u32 draw_two_pixel = 0;

    u8 *base = NULL;

    if (surface->format == FORMAT_YCRYCB422_16 ||
        surface->format == FORMAT_CRYCBY422_16)
    {
        if (rect->pos_x % 2 || rect->width % 2)  //right ?
        {
            dpu_info(ERROR_LEVEL,"for ycbcr422 start point and width must be even \n");
            return;
        }
    }

    ret = get_color_pixel(surface->format, color, &pixel_1, &pixel_2);

    if (ret != TT_PASS)
    {
        dpu_info(ERROR_LEVEL,"unkown format, cann't draw rect\n");
        return;
    }

    if (surface->bit_cnt == 8)
    {
        draw_8bit = 1;
    }
    else if (surface->bit_cnt == 16)
    {
        if (surface->format == FORMAT_YCRYCB422_16 ||
            surface->format == FORMAT_CRYCBY422_16)
        {
            draw_two_pixel = 1;
        }
        draw_16bit = 1;
    }
    else if (surface->bit_cnt == 32)
    {
        if (surface->format == FORMAT_YCRYCB422_32 ||
            surface->format == FORMAT_CRYCBY422_32)
        {
            draw_two_pixel = 1;
        }
        draw_32bit = 1;
    }
    else 
    {
        dpu_info(ERROR_LEVEL,"why bit_cnt is %d, cann't draw rect\n",surface->bit_cnt);
        return;
    }
    
    //base = (u8*)(surface->cpu_addr + surface->pitch * rect->pos_y + rect->pos_x * surface->bit_cnt / 8);
    for (i = rect->pos_y; i < rect->height + rect->pos_y; i++)
    {
        for (j = rect->pos_x; j < rect->width + rect->pos_x; j++)
        {
            //base += i * surface->pitch + j * surface->bit_cnt / 8;

            base = (u8*)((u8*)surface->cpu_addr + surface->pitch * i + j * surface->bit_cnt / 8);
            
            if (draw_8bit)
            {
                *(u8*)base = (u8)pixel_1;
            }
            else if (draw_16bit)
            {
                if(draw_two_pixel)
                {
                    *(u16*)base = (u16)pixel_1;
                    *(u16*)(base + 2) = (u16)pixel_2;
                    j++;
                }
                else
                {
                    *(u16*)base = (u16)pixel_1;
                }
            }
            else if (draw_32bit)
            {
                if(draw_two_pixel)
                {
                    *(u32*)base = (u32)pixel_1;
                    *(u32*)(base + 4) = (u32)pixel_2;
                    j++;
                }
                else
                {

                    if (surface->need_premult)
                    {
                        if (!surface->alpha)
                        {
                            dpu_info(WARNING_LEVEL,"need do premult ,why alpha is 0 ?\n");
                        }
                        else
                        {
                            *(u32*)base = (u32)pixel_1 * surface->alpha / 255;
                        }
                    }
                    else
                    {
                        *(u32*)base = (u32)pixel_1;
                    }
                }
            }
        }
    }

}


/******************************************

color_bar pattern

(0,0)
...........................................
.               Pure Red                  .
...........................................
.               Pure Green                .
...........................................
.               Pure BLUE                 .
...........................................
.               Pure Black                .
...........................................
.               Pure White                .
...........................................(surface->width, surface->height)

******************************************/


static TT_STATUS draw_color_bar(struct surface_info_t* surface)
{
    u32 i = 0, j = 0;
    u32 *temp = NULL;
    struct rect_t  rect = {0};

    rect.pos_x = 0;
    rect.pos_y = 0;
    rect.width = surface->width;
    rect.height = surface->height / 5;

    draw_rect(surface, &rect, RED_COLOR);

    rect.pos_y = surface->height / 5;
    draw_rect(surface, &rect, GREEN_COLOR);

    rect.pos_y = surface->height * 2 / 5;
    draw_rect(surface, &rect, BLUE_COLOR);

    rect.pos_y = surface->height * 3 / 5;
    draw_rect(surface, &rect, BLACK_COLOR);

    rect.pos_y = surface->height * 4 / 5;
    draw_rect(surface, &rect, WHITE_COLOR);


    rect.pos_x = 0;
    rect.pos_y = 0;
    rect.width = 2;
    rect.height = surface->height;
    draw_rect(surface, &rect, WHITE_COLOR);

    rect.pos_x = 0;
    rect.pos_y = 0;
    rect.width = surface->width;
    rect.height = 2;
    draw_rect(surface, &rect, WHITE_COLOR);

    rect.pos_x = surface->width - 2;
    rect.pos_y = 0;
    rect.width = 2;
    rect.height = surface->height;
    draw_rect(surface, &rect, WHITE_COLOR);

    rect.pos_x = 0;
    rect.pos_y = surface->height - 2 ;
    rect.width = surface->width;
    rect.height = 2;
    draw_rect(surface, &rect, WHITE_COLOR);

    return TT_PASS;
}


static u8 is_support_premult(struct surface_info_t *surface)
{

    u32 support_format = 1 << FORMAT_A8R8G8B8 | 1 <<  FORMAT_A8B8G8R8 | 1 <<  FORMAT_A2R10G10B10 | 1 << FORMAT_A2B10G10R10;


    if (support_format & (1 << surface->format))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
#define abs(a) ((a) > 0 ? (a) : -(a))

//https://tool.oschina.net/commons?type=3
static TT_STATUS draw_color_circle(struct surface_info_t *surface)
{
    u32 i,j,k;
    u32 *temp = 0;
    u8  R = 255;
    u8  G = 62;
    u8  B = 150;
    u8  alpha = surface->alpha;

    u64 w,h;


    if (surface->format != FORMAT_A8R8G8B8)
    {
       dpu_info(INFO_LEVEL,"arrow is used for cursor, just support ARGB8888 ? \n");
       return TT_FAIL;
    }

    if (surface->need_premult)
    {
        R = (R * surface->alpha)/255;
        G = (G * surface->alpha)/255;
        B = (B * surface->alpha)/255;
    }


    h = surface->height;
    w = surface->width;

    for (i = 0; i < surface->height; i++)
    {
        for (j = 0; j < surface->width; j++)
        {
            temp = (u32*)((u8*)surface->cpu_addr + i * surface->pitch + j * surface->bit_cnt / 8);
            if ((4*(h * h)*abs(j - w / 2)*abs(j - w / 2) + 4*(w * w) *abs(i - h / 2)*abs(i - h / 2)) <= w * w * h * h)
            {
               
                *temp = alpha << 24 | R << 16 | G << 8 | B;
            }
            else
            {
                *temp = 0xffffff;
            }
        }
    }

    return TT_PASS;
}

/******************************************

color_bar_1 pattern

(0,0)
..................................................
.  Red(0x3ff decrease to 0) step is 1            .
..................................................
.  Green (0x3ff decrease to 0) step is 1         .
..................................................
.  Blue (0x3ff decrease to 0) step is 1          .
..................................................(surface->width, surface->height)

******************************************/

//Used for A2R10G10B10 format  to test bitfile
TT_STATUS draw_color_1(struct surface_info_t *surface)
{
    struct rect_t  rect = {0};
    u32 i = 0,j = 0;
    u32 color = 0 ,temp;



    if (surface->format != FORMAT_A2R10G10B10)
    {
        dpu_info(INFO_LEVEL,"color bar 1 just support A2R10G10B10 format \n");
        return TT_FAIL;
    }


    rect.pos_x = 0;
    rect.pos_y = 0;
    rect.width = 1;
    rect.height = 1;

    for (i = 0; i < surface->height / 3; i++)
    {
        color = RED_COLOR;
        for (j = 0; j < surface->width; j++)
        {
            temp = j % R_CHANNEL(color);
            temp = temp << (2*CHANNEL_BIT);
            temp = color - temp;

            rect.pos_x = j;
            rect.pos_y = i;
            rect.width = 1;
            rect.height = 1;

            draw_rect(surface, &rect, temp);
        }
    }

    for (i = surface->height / 3; i < surface->height * 2 / 3; i++)
    {
        color = GREEN_COLOR;
        for (j = 0; j < surface->width; j++)
        {
            temp = j % G_CHANNEL(color);
            temp = temp << (CHANNEL_BIT);
            temp = color - temp;

            rect.pos_x = j;
            rect.pos_y = i;
            rect.width = 1;
            rect.height = 1;

            draw_rect(surface, &rect, temp);
        }
    }


    for (i = surface->height * 2 / 3; i < surface->height; i++)
    {
        color = BLUE_COLOR;
        for (j = 0; j < surface->width; j++)
        {
            temp = j % B_CHANNEL(color);
            temp = color - temp;

            rect.pos_x = j;
            rect.pos_y = i;
            rect.width = 1;
            rect.height = 1;

            draw_rect(surface, &rect, temp);
        }
    }
}


/**************************************************

color 2 what ?

***************************************************/

TT_STATUS draw_color_2(struct surface_info_t *surface)
{
    //TODO
}

TT_STATUS tt_draw_surface(struct surface_info_t  *surface)
{
    TT_STATUS ret = TT_PASS;

    
    if (surface->compressed) //don't support draw compress surface
    {
        return TT_FAIL;
    }


    //Note P8,need config gamma

    if (surface->format == FORMAT_INVALID ||
        surface->format == FORMAT_P8 || 
        surface->format == FORMAT_A1R5G5B5 ||
        surface->format == FORMAT_CRYCBY422_32 ||
        surface->format == FORMAT_YCRYCB422_32 ||
        surface->format >=FORMAT_NUM)
    {
        dpu_info(ERROR_LEVEL,"Unsupport format 0x%x\n",surface->format);
        return TT_FAIL;
    }
    
    switch(surface->pattern)
    {
        case PATTERN_COLOR_BAR:
            draw_color_bar(surface);
            break;
        case PATTERN_COLOR_1:
            draw_color_1(surface);
            break;
        case PATTERN_COLOR_2:
            draw_color_2(surface);
            break;
        case PATTERN_CIRCLE:
            draw_color_circle(surface);
            break;
        default:

            dpu_info(ERROR_LEVEL,"unknow color pattern \n");
            ret = TT_FAIL;
            break;
    }

    return ret;
}


TT_STATUS  tt_create_surface(struct dpu_adapter_t *dpu_adapter, struct surface_cmd_t *surface_cmd)
{
    u32  width = 0, aligned_width = 0;
    u32  size = 0;
    TT_STATUS status = TT_PASS;
    struct surface_info_t  *surface = NULL;
    u32 offset = 0;

    if (surface_cmd->width == 0 || surface_cmd->height == 0 || surface_cmd->format >= FORMAT_NUM)
    {
        status = TT_INVALID_PARAM;
        return status;
    }

    surface = alloc_surface(dpu_adapter);

    if (!surface)
    {
        status = TT_FAIL;
        goto end_surface;
    }


    surface->width = surface_cmd->width;
    surface->height = surface_cmd->height;
    surface->format = surface_cmd->format;
    surface->compressed = surface_cmd->compressed;
    surface->need_premult = surface_cmd->premult;
    surface->pattern = surface_cmd->pattern;
    surface->alpha = surface_cmd->alpha;
    surface->aligned_width = tt_align(surface->width, dpu_adapter->width_alignment);


    surface->bit_cnt = g_format_info[surface->format].bit_cnt;
    memcpy(surface->format_name, g_format_info[surface->format].format_name, FORMAT_NAME_LENGTH);
    
    surface->size = surface->aligned_width * surface->height * surface->bit_cnt / 8;
    surface->pitch = surface->aligned_width * surface->bit_cnt / 8;

    

    offset = tt_alloc_video_mem(dpu_adapter, surface->size, dpu_adapter->width_alignment);

    if (offset == 0)
    {
       // goto end_video_mem;
    }

    surface->gpu_addr = offset;
    surface->cpu_addr = (u8*)dpu_adapter->base.fb_base + offset;



    dpu_info(INFO_LEVEL,"width is %d, height is %d, format is %d, compressed is %d, need_pre is %d, pattern %d pitch is %d \n",
        surface->width,
        surface->height,
        surface->format,
        surface->compressed,
        surface->need_premult,
        surface->pattern,
        surface->pitch
        );

    dpu_info(INFO_LEVEL,"gpu_addr is 0x%x, cpu_addr is 0x%x, fb base is 0x%x\n",surface->gpu_addr, surface->cpu_addr, dpu_adapter->base.fb_base);

    //TODO:
    //draw surface with alpha & color pattern & format

    if (!surface_cmd->no_draw)
    {
        if (TT_FAIL == tt_draw_surface(surface))
        {
            dpu_info(INFO_LEVEL,"draw surface faild, please help check \n");
            status = TT_FAIL;
        }
    }


    return status;

end_video_mem:

    free_surface(dpu_adapter, surface->index);
    
end_surface:
    
    return status;
    
}




extern struct platform_funcs_t dos_funcs;
extern struct platform_funcs_t linux_funcs;




TT_STATUS init_platform_funcs()
{
	TT_STATUS ret = TT_PASS;

#ifdef __DOS__

	platform_funcs = &dos_funcs; 
	
#elif defined  __DPU_LINUX_KERNEL__

	platform_funcs = &linux_funcs;
	
#endif


	if (!platform_funcs ||
		!platform_funcs->platform_init ||
		!platform_funcs->platform_delay_micro_seconds ||
		!platform_funcs->platform_get_linear_addr ||
		!platform_funcs->platform_get_system_time ||
		!platform_funcs->platform_print ||
		!platform_funcs->platform_read_io_byte ||
		!platform_funcs->platform_write_io_byte ||
		!platform_funcs->platform_read_io_dword ||
		!platform_funcs->platform_write_io_dword ||
		!platform_funcs->platform_read_pci_config_byte ||
		!platform_funcs->platform_read_pci_config_word ||
		!platform_funcs->platform_write_pci_config_byte ||
		!platform_funcs->platform_write_pci_config_word
		)
	{
		ret == TT_FAIL;
	}

	return ret;
}


TT_STATUS tt_init_platform()
{
	TT_STATUS ret = TT_PASS;

	ret = platform_funcs->platform_init();
	
	return ret;
}

TT_STATUS tt_deinit_platform(struct dpu_adapter_t * dpu_adapter)
{
	TT_STATUS ret = TT_PASS;

	ret = platform_funcs->platform_deinit(dpu_adapter);
	
	return ret;
}

