#ifndef _UTIL_H_
#define _UTIL_H

#include"types.h"

#define GET_LAST_BIT(N) ((~((N)-1))&(N))

//pci space offset
#define  PCI_VENDOR_ID_OFFSET		0x00
#define  PCI_DEVICE_ID_OFFSET       0x02
#define  PCI_COMMAND_OFFSET         0x04
#define  PCI_CLASS_DEVICE_OFFSET    0x0A
#define  PCI_BASE_CLASEE_OFFEST     0x0B
#define  PCI_BAR0_OFFSET            0x10
#define  PCI_BAR1_OFFSET            0x14
#define  PCI_SUBVENDOR_ID_OFFSET    0x2C
#define  PCI_SUBSYSTEM_ID_OFFSET    0x2E
#define  PCI_ROM_BASE_OFFSET        0x30

#define  PCI_MAX_BUS_NUM     	0x86
#define  PCI_MAX_DEVICE_NUM  	2
#define  PCI_MAX_FUNCTION_NUM  	2


//io to config pci space
#define CONFIG_ADDRESS          0x0CF8
#define CONFIG_DATA             0x0CFC

#define OUTPD(a,b)  outpd((a),(b))
#define INPD(a)     inpd((a))


//log level
#define ERROR_LEVEL    0
#define INFO_LEVEL     1
#define WARNING_LEVEL  2
#define DEBUG_LEVEL    3

#define OUTPUT_UART

#ifdef OUTPUT_UART

#define dpu_error	    tt_print
#define dpu_info   	    tt_print
#define dpu_warning     tt_print
#define dpu_debug       tt_print


#else

#define dpu_error	    printf
#define dpu_info   	    printf
#define dpu_warning     printf
#define dpu_debug       printf

#endif

#ifdef DEBUG
#define dpu_trace       printf
#else
#define dpu_trace
#endif


typedef enum _TT_CACHE_FLAG
{
	CACHE_ENABLE = 1,
	CACHE_DISABLE = 2,
}TT_CACHE_FLAG;



#define tt_align(size, align)  ((size + align - 1) & (~(align - 1)))



void tt_print(char * string, ...);


u32 tt_strhash(u8 *str);
u32  tt_get_last_bit(u32  value);
u32  tt_get_bit_index(u32 value);
u8 tt_get_bit_num(u32 value);

void tt_get_system_time(u64 * time);
void tt_delay_micro_seconds(u32 value);

TT_CACHE_FLAG tt_get_cache_state(void);
void tt_set_cache(TT_CACHE_FLAG flag);

void tt_write_u8(void * adapter, u32 register_port, u8 value);
void tt_write_u32(void * adapter, u32 register_port, u32 value);
u32 tt_read_u32(void * adapter, u32 register_port);
u8 tt_read_u8(void * adapter, u32 register_port);
void tt_read_u16(void * adapter, u32 register_port);
void tt_write_u16(void * adapter, u32 register_port, u16 value);
u32 tt_read_buffer_u32(volatile u32 *register_port);
void tt_write_buffer_u32(volatile u32 * register_port, u32 value);

u8 tt_read_io(u8 * register_port);
void tt_write_io(u8 * register_port, u8 value);

u8 tt_read_mmio_byte(u32 base, u32 port);
void tt_write_mmio_byte(u32 base, u32 port, u8 value, u8 mask);
u32 tt_read_mmio(u32 base , u32 port);
void tt_write_mmio(u32 base, u32 port, u32 value, u32 mask);

void * tt_malloc_mem(u32 bytes);
void * tt_free_mem(void *p);

static u32 get_fb_size(u32 bus, u32 dev, u32 func);
void tt_read_pci_config_byte(u8 bus, u8 dev, u8 func, u16 reg, u8* data);
void tt_write_pci_config_byte(u8 bus, u8 dev, u8 func, u16 reg, u8 data);
u32 tt_get_pci_info(struct base_adapter_t *base_adapter);
void tt_enable_pci_bridge(struct base_adapter_t *base_adapter);
void tt_enable_mmio_access(struct base_adapter_t *base_adapter);

void tt_init_card(struct base_adapter_t *base_adapter);

u32  tt_alloc_video_mem(struct dpu_adapter_t *dpu_adapter, u32 size, u32 aligment);
void  tt_free_video_mem(struct dpu_adapter_t *dpu_adapter, u32 aligned_offset);

static struct surface_info_t* alloc_surface(struct dpu_adapter_t *dpu_adapter);
static TT_STATUS free_surface(struct dpu_adapter_t *dpu_adapter, u32 index);

TT_STATUS tt_draw_surface(struct surface_info_t  *surface);
TT_STATUS  tt_create_surface(struct dpu_adapter_t *dpu_adapter, struct surface_cmd_t *surface_cmd);


#endif
