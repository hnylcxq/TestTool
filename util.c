#include<stdio.h>
#include<string.h>
#include<stdarg.h>

//#include"types.h"
#include"util.h"

#define LOG_BUFFER_SIZE     256

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



struct format_info_t g_format_info[FORMAT_NUM] = {
        {2, "Monochrome"},   //FORMAT_MONO
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
        {32, "YCBCR8888"},   //FORMAT_YCBCR8888_32
        {32, "CRYCB8888"},   //FORMAT_CRYCB8888_32
        {32, "YCBCR2101010_32"},//FORMAT_YCBCR2101010_32
        {32, "CRYCB2101010_32"},//FORMAT_CRYCB2101010_32
        {1,  "INVALID_FORMAT"}, //FORMAT_NUM
};




void tt_print(char * string, ...)
{
	va_list args;
	u8 buff[LOG_BUFFER_SIZE];

    #if 0
	if (level  > g_dpu_adapter->log_level)
	{
		return ;
	}

    #endif
	memset(buff, 0, LOG_BUFFER_SIZE);
	
	va_start(args, string);
	vsnprintf(buff, LOG_BUFFER_SIZE -1, string, args);
	va_end(args);
	
	bios_print(buff);
}



void tt_get_system_time(u64 * time)
{
	bios_get_system_time(time);
}


void tt_delay_micro_seconds(u32 value)
{
	bios_delay_micro_seconds(value);
}


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

void tt_write_u8(void * adapter, u32 register_port, u8 value)
{
	struct dpu_adapter_t * dpu_adapter = (struct dpu_adapter_t *)adapter;
	volatile u8 * port = NULL;
	
	port = (u8 *)(dpu_adapter->base.mmio_base+ register_port);
	*port = value;
}


void tt_write_u32(void * adapter, u32 register_port, u32 value)
{
	struct dpu_adapter_t * dpu_adapter = (struct dpu_adapter_t *)adapter;
	volatile u32 * port = NULL;
	u32 ul_align_mask = sizeof(u32) - 1;
	
	port = (u32 *)(dpu_adapter->base.mmio_base + register_port);
	if ((u32)port & ul_align_mask)
	{
		dpu_error("The port address 0x%x is not aligned \n",register_port);
	}
	*port = value;
	
}

u32 tt_read_u32(void * adapter, u32 register_port)
{
	struct dpu_adapter_t * dpu_adapter = (struct dpu_adapter_t *)adapter;
	volatile u32 * port = NULL;
	u32  ul_align_mask = sizeof(u32) - 1;
	u32  value = 0;
	
	port = (u32 *)(dpu_adapter->base.mmio_base + register_port);
	if ((u32)port & ul_align_mask)
	{
		dpu_error("The port address 0x%x is not aligned \n",register_port);
	}
	
	value = *port;
	return value;
	
}

u8 tt_read_u8(void * adapter, u32 register_port)
{
	struct dpu_adapter_t * dpu_adapter = (struct dpu_adapter_t *)adapter;
	volatile u8 * port = NULL;
	u8 value = 0 ;
	
	port = (u8 *)(dpu_adapter->base.mmio_base + register_port);
	
	value = *port;
	return value;
}

void tt_read_u16(void * adapter, u32 register_port)
{
	struct dpu_adapter_t * dpu_adapter = (struct dpu_adapter_t *)adapter; 
	volatile u16 * port = NULL;
	u16 value;
	u16  ul_align_mask = sizeof(u16) - 1;
	
	port = (u16 *)(dpu_adapter->base.mmio_base + register_port);
	if ((u32)port & ul_align_mask)
	{
		dpu_error("The port address 0x%x is not aligned \n",register_port);
	}
	value = *port;
}

void tt_write_u16(void * adapter, u32 register_port, u16 value)
{
	struct dpu_adapter_t * dpu_adapter = (struct dpu_adapter_t *)adapter; 
	volatile u16 * port = NULL;
	u32  ul_align_mask = sizeof(u16) - 1;
	
	port = (u16 *)(dpu_adapter->base.mmio_base + register_port);
	if ((u16)port & ul_align_mask)
	{
		dpu_error("The port address 0x%x is not aligned \n",register_port);
	}
	*port = value;
}

u32 tt_read_buffer_u32(volatile u32 *register_port)
{
	u32 value = 0;
	u32 ul_align_mask = sizeof(u32) - 1;
	
	if ((u32)register_port & ul_align_mask)
	{
		dpu_error("The mem address 0x%x is not aligned \n",register_port);
	}
	value = *register_port;
	return value;
}

void tt_write_buffer_u32(volatile u32 * register_port, u32 value)
{
	u32 ul_align_mask = sizeof(u32) - 1;
	
	if ((u32 ) register_port & ul_align_mask)
	{
		dpu_error("The mem address 0x%x is not aligned \n",register_port);
	}
	*register_port = value;
}


u8 tt_read_io(u8 * register_port)
{
	return bios_read_io(register_port);
}

void tt_write_io(u8 * register_port, u8 value)
{
	bios_write_io(register_port, value);
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
	
	if (p)
	{
		dpu_error(" malloc memory failed \n");
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



static u32 get_fb_size(u32 bus, u32 dev, u32 func)
{
    u32 temp, value, size;

    bios_read_pci_config_dword(bus, dev, func, 0x14, &temp);
    value = temp;
    bios_write_pci_config_dword(bus, dev, func, 0x14, 0xFFFFFFFF);
    bios_read_pci_config_dword(bus, dev, func, 0x14, &temp);

    size = (~temp | 0xF) + 1;
    bios_write_pci_config_dword(bus, dev, func, 0x14, value);

    return size;

}

void tt_read_pci_config_byte(u8 bus, u8 dev, u8 func, u16 reg, u8* data)
{
    bios_read_pci_config_byte(bus,dev,func, reg, data);
}

void tt_write_pci_config_byte(u8 bus, u8 dev, u8 func, u16 reg, u8 data)
{
    bios_write_pci_config_byte(bus, dev, func, reg, data);
}

u32 tt_get_pci_info(struct base_adapter_t *base_adapter)
{
	u32 found = 0;
	u32 bus, dev, func;
	u32 data_out, data_in;
    u8 i, j, k, bcid, scid, sbn;
    u16 vendor_id, device_id;
    u32 value, fb_size;
	
	for (bus = 0; bus < PCI_MAX_BUS_NUM; ++bus)
	{
		for (dev = 0; dev < PCI_MAX_DEVICE_NUM; ++dev)
		{
			for (func = 0; func < PCI_MAX_FUNCTION_NUM; ++func)
            {
                data_out = (bus << 16) + (dev << 11) + (func << 8);
                data_out |= 0x80000000;

                OUTPD(CONFIG_ADDRESS, data_out);
                data_in = INPD(CONFIG_DATA);

                //dpu_info("data_in is 0x%x\n",data_in);

                if ((data_in & 0xFFFF) == VENDER_XX)
                {
                    OUTPD(CONFIG_ADDRESS, data_out + 0x8);
                    if ((INPD(CONFIG_DATA) & 0xFF000000) == 0x03000000)
                    {
                        base_adapter->vender_id = (u16)(data_in & 0xFFFF);
                        base_adapter->device_id = (u16)((data_in & 0xFFFF0000)>>16);
                        base_adapter->revision_id = (u16)(INPD(CONFIG_DATA) & 0xFF);
                        base_adapter->bus_num= bus;
                        base_adapter->dev_num = dev;
                        base_adapter->func_num = func;

                        OUTPD(CONFIG_ADDRESS, data_out + 4);
                        if (INPD(CONFIG_DATA) & 0x01)
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
        dpu_info("couldn't found card \n");
        return 0;
    }

   // dpu_info("lei found card \n");
    
	for (i = 0; i < PCI_MAX_BUS_NUM; ++i)
    {
        for (j = 0; j < PCI_MAX_DEVICE_NUM; ++j)
        {
            for (k = 0; k < PCI_MAX_FUNCTION_NUM; ++k)
            {
                bios_read_pci_config_word(i, j, k, PCI_VENDOR_ID_OFFSET, &vendor_id);
                if (vendor_id == 0xFFFF)
                {
                    continue;
                }
                bios_read_pci_config_word(i, j, k, PCI_DEVICE_ID_OFFSET, &device_id);
                bios_read_pci_config_byte(i, j, k, PCI_CLASS_DEVICE_OFFSET, &scid);
                bios_read_pci_config_byte(i, j, k, PCI_BASE_CLASEE_OFFEST, &bcid);

                if (scid != 0x04 || bcid != 0x06)
                {
                    continue;
                }
                
                bios_read_pci_config_byte(i, j, k, 0x19, &sbn);

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
    bios_read_pci_config_dword(base_adapter->bus_num, base_adapter->dev_num, base_adapter->func_num, 0x10, &value);

    value = value & ~0xf; //mask flag bit
	if (bios_get_linear_addr(value, 0x80000, &value))
    {
        base_adapter->mmio_base = value;
    }
    else
    {
        base_adapter->mmio_base = 0;
        found = 0;
        goto exit;
    }
	
	//bar1 info

    bios_read_pci_config_dword(base_adapter->bus_num, base_adapter->dev_num, base_adapter->func_num, 0x14, &value);
    fb_size = get_fb_size(base_adapter->bus_num, base_adapter->dev_num, base_adapter->func_num);
	value = value & ~0xF;
    if (bios_get_linear_addr(value, fb_size, &value))
    {
        base_adapter->fb_base = value;
        base_adapter->fb_size = fb_size;
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
            bios_read_pci_config_byte(base_adapter->bridge_info.bus_num, 
                base_adapter->bridge_info.dev_num, base_adapter->bridge_info.func_num, PCI_COMMAND_OFFSET, &command);

            command |=0x07;
            bios_write_pci_config_byte(base_adapter->bridge_info.bus_num,
                base_adapter->bridge_info.dev_num, base_adapter->bridge_info.func_num, PCI_COMMAND_OFFSET, command);
            bios_read_pci_config_byte(base_adapter->bridge_info.bus_num, 
                base_adapter->bridge_info.dev_num, base_adapter->bridge_info.func_num, PCI_COMMAND_OFFSET, &temp);

        }while (command != temp);
    }
}


void tt_enable_mmio_access(struct base_adapter_t *base_adapter)
{
    u8 command;

    bios_read_pci_config_byte(base_adapter->bridge_info.bus_num, base_adapter->bridge_info.dev_num, base_adapter->bridge_info.func_num, PCI_COMMAND_OFFSET, &command);

    if ((command & 0x02) == 0)
    {
        command = command | 0x02;
        bios_write_pci_config_byte(base_adapter->bridge_info.bus_num,
                                   base_adapter->bridge_info.dev_num,
                                   base_adapter->bridge_info.func_num,
                                   PCI_COMMAND_OFFSET,
                                   command);
    }
}



void tt_init_card(struct base_adapter_t *base_adapter)
{

    //set mxu boundary / snoop boundary   490a0 ?

    //mxu boundary need local memory size , need pmp info ?
    //maybe could set mxu boundary to bar1 size for convenience
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


static struct surface_info_t* alloc_surface(struct dpu_adapter_t *dpu_adapter)
{
    u32 i = 0;

    struct surface_info_t *surface = NULL;


    if (dpu_adapter->surface_manager.num >= MAX_SURFACE_NUM)
    {

        dpu_info("please increase macro MAX_SURFACE_NUM \n");
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
        dpu_error("Some wrong, please help check\n");
        surface = NULL;
    }
    else
    {
        dpu_adapter->surface_manager.surfaces[i].valid = 1;
        dpu_adapter->surface_manager.num++;
    }

    return surface;

}


static TT_STATUS free_surface(struct dpu_adapter_t *dpu_adapter, u32 index)
{

    if (index >= MAX_SURFACE_NUM || dpu_adapter->surface_manager.surfaces[index].valid == 0)
    {
        dpu_error("%s:  invalid para \n",__func__);
        return TT_FAIL;
    }

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


    Y  = RGB2Y(R_CHANNEL(color), G_CHANNEL(color), B_CHANNEL(color));
    CB = RGB2CB(R_CHANNEL(color), G_CHANNEL(color), B_CHANNEL(color));
    CR = RGB2CR(R_CHANNEL(color), G_CHANNEL(color), B_CHANNEL(color));
    
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
        case FORMAT_A1R5G5B5:

            *pixel_1 = ((R_CHANNEL(color) & 0x3e0) << 5) |
                       ((G_CHANNEL(color) & 0x3e0))|
                       ((B_CHANNEL(color) & 0x3e0) >> 5);
            break;
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
        case FORMAT_CRYCBY422_16:

            *pixel_1 = ((CR & 0x3fc) << 6) | ((Y & 0x3fc) >> 2);
            *pixel_2 = ((CB & 0x3fc) << 6) | ((Y & 0x3fc) >> 2);
            break;
        case FORMAT_YCRYCB422_16:

            *pixel_1 = ((Y & 0x3fc) << 6) | ((CR & 0x3fc) >> 2);
            *pixel_2 = ((Y & 0x3fc) << 6) | ((CB & 0x3fc) >> 2);
            break;
        case FORMAT_CRYCBY422_32:

            *pixel_1 = ((CR & 0x3ff) << 22) | ((Y & 0x3ff) << 6);
            *pixel_2 = ((CB & 0x3ff) << 22) | ((Y & 0x3ff) << 6);
            break;
        case FORMAT_YCRYCB422_32:

            *pixel_1 = ((Y & 0x3ff) << 22) | ((CR & 0x3ff) << 6);
            *pixel_2 = ((Y & 0x3ff) << 22) | ((CB & 0x3ff) << 6);
            break;
        case FORMAT_YCBCR8888_32:

            *pixel_1 = ((Y & 0x3fc) << 14 )|
                       ((CB & 0x3fc) << 6) |
                       ((CR & 0x3fc) >> 2);
            break;
        case FORMAT_CRYCB8888_32:

            *pixel_1 =  ((CR & 0x3fc) << 14) |
                        ((Y  & 0x3fc) << 6) |
                        ((CB & 0x3fc) >> 2);
            break;
        case FORMAT_YCBCR2101010_32:

            *pixel_1 = ((Y & 0x3ff) << 20) |
                       ((CB & 0x3ff) << 10) |
                       (CR & 0x3ff);
            break;
        case FORMAT_CRYCB2101010_32:
            *pixel_1 =  ((CR & 0x3ff) << 20) |
                        ((Y & 0x3ff) << 10) |
                        (CB & 0x3ff);
            break;
        default:

            dpu_error("unknow format \n");
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
        surface->format == FORMAT_CRYCBY422_16 ||
        surface->format == FORMAT_CRYCBY422_32 ||
        surface->format == FORMAT_YCRYCB422_32)
    {
        if (rect->pos_x % 2 || rect->width % 2)  //right ?
        {
            dpu_error("for ycbcr422 start point and width must be even \n");
            return;
        }
    }

    ret = get_color_pixel(surface->format, color, &pixel_1, &pixel_2);

    if (ret != TT_PASS)
    {
        dpu_error("unkown format, cann't draw rect\n");
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
        dpu_error("why bit_cnt is %d, cann't draw rect\n",surface->bit_cnt);
        return;
    }
    
    base = (u8*)(surface->cpu_addr + surface->pitch * rect->pos_y + rect->pos_x * surface->bit_cnt / 8);
    for (i = 0; i < rect->hight; i++)
    {
        for (j = 0; j < rect->width; j++)
        {
            base += i * surface->pitch + j * surface->bit_cnt / 8;
            
            if (draw_8bit)
            {
                *(u8*)base = (u8)pixel_1;
            }
            else if (draw_16bit)
            {
                if(draw_two_pixel)
                {
                    *(u16*)base = (u16)pixel_1;
                    *(u16*)((u8)base + 2) = (u16)pixel_2;
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
                    *(u32*)((u8)base + 4) = (u32)pixel_2;
                    j++;
                }
                else
                {

                    if (surface->need_premult)
                    {
                        if (!surface->alpha)
                        {
                            dpu_warning("need do premult ,why alpha is 0 ?\n");
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
    rect.hight = surface->height / 5;

    draw_rect(surface, &rect, RED_COLOR);

    rect.pos_y = surface->height / 5;
    draw_rect(surface, &rect, GREEN_COLOR);
    
    rect.pos_y = surface->height * 2 / 5;
    draw_rect(surface, &rect, BLUE_COLOR);

    rect.pos_y = surface->height * 3 / 5;
    draw_rect(surface, &rect, BLACK_COLOR);

    rect.pos_y = surface->height * 4 / 5;
    draw_rect(surface, &rect, WHITE_COLOR);
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

//https://tool.oschina.net/commons?type=3
static TT_STATUS draw_color_circle(struct surface_info_t *surface)
{
    u32 i,j,k;
    u32 *temp = 0;
    u8  R = 255;
    u8  G = 62;
    u8  B = 150;
    u8  alpha = surface->alpha;

    u32 x,y,w,h;

    if (surface->need_premult)
    {
        R = (R * surface->alpha)/255;
        G = (G * surface->alpha)/255;
        B = (B * surface->alpha)/255;
    }

    if (surface->format != FORMAT_A8R8G8B8)
    {
        dpu_info("arrow is used for cursor, just support ARGB8888 ? \n");
        return TT_FAIL;
    }

    h = surface->height / 2;
    w = surface->width / 2;
    x = w /2;
    y = h / 2;

    for (i = 0; i < h; i++)
    {
        for (j = 0; j < w; j++)
        {
            if (((h * h)*(i - w / 4)*(i - w / 4) + (w * w) *(j - h / 4)*(j - h / 4)) <= w * w * h * h)
            {
                temp = (u32*)(surface->cpu_addr + i * surface->pitch + j);
                *temp = alpha << 24 | R << 16 | G << 8 | B;
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

    rect.pos_x = 0;
    rect.pos_y = 0;
    rect.width = 1;
    rect.hight = 1;

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
            rect.hight = 1;

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
            rect.hight = 1;

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
            rect.hight = 1;

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


    if (surface->format == FORMAT_INVALID ||
        surface->format == FORMAT_P8 ||
        surface->format == FORMAT_MONO ||
        surface->format >=FORMAT_NUM)
    {
        dpu_error("Unsupport format 0x%x\n",surface->format);
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

            dpu_error("unknow color pattern \n");
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
        goto end_video_mem;
    }

    surface->gpu_addr = offset;
    surface->cpu_addr = dpu_adapter->base.mmio_base + offset;

    //TODO:
    //draw surface with alpha & color pattern & format

    if (!surface_cmd->no_draw)
    {
        if (TT_FAIL == tt_draw_surface(surface))
        {
            dpu_info("draw surface faild, please help check \n");
            status = TT_FAIL;
        }
    }


    return status;

end_video_mem:

    free_surface(dpu_adapter, surface->index);
    
end_surface:
    
    return status;
    
}
   

