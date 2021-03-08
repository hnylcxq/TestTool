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
#define  PCI_MAX_DEVICE_NUM  	8
#define  PCI_MAX_FUNCTION_NUM  	2


//io to config pci space
#define CONFIG_ADDRESS          0x0CF8
#define CONFIG_DATA             0x0CFC


//log level
#define ERROR_LEVEL    0
#define INFO_LEVEL     1
#define WARNING_LEVEL  2
#define DEBUG_LEVEL    3
#define TRACE_LEVEL	   4


#define tt_align(size, align)  ((size + align - 1) & (~(align - 1)))

typedef enum _TT_CACHE_FLAG
{
	CACHE_ENABLE = 1,
	CACHE_DISABLE = 2,
}TT_CACHE_FLAG;


void dpu_info(int level, u8 *fmt, ...);

typedef TT_STATUS (*platform_init_fn)();
typedef TT_STATUS (*platform_deinit_fn)(struct dpu_adapter_t *dpu_adapter);
typedef void (*platform_print_fn)(u8 * string);


typedef u16 (*platform_read_pci_config_word_fn)(u8 bus, u8 dev, u8 func, u16 reg, u16 *data);
typedef u16 (*platform_read_pci_config_byte_fn)(u8 bus, u8 dev, u8 func, u16 reg, u8 *data);
typedef u16 (*platform_read_pci_config_dword_fn)(u8 bus, u8 dev, u8 func, u16 reg, u32 *data);

typedef u16 (*platform_write_pci_config_dword_fn)(u8 bus, u8 dev, u8 func, u16 reg, u32 data);
typedef u16 (*platform_write_pci_config_word_fn)(u8 bus, u8 dev, u8 func,u16 reg,  u16 data);
typedef u16 (*platform_write_pci_config_byte_fn)(u8 bus, u8 dev, u8 func,u16 reg, u8 data);


typedef u8 (*platform_read_io_byte_fn)(u16 register_port);
typedef void (*platform_write_io_byte_fn)(u16 register_port, u8 value);
typedef u32 (*platform_read_io_dword_fn)(u16 register_port);
typedef void (*platform_write_io_dword_fn)(u16 register_port, u32 value);


typedef void (*platform_get_system_time_fn)(u64 *time);
typedef void (*platform_delay_micro_seconds_fn)(u32 value);

typedef TT_STATUS (*platform_get_linear_addr_fn)(u64 phy_addr, u32 size, void **linear_addr);


struct platform_funcs_t {
	platform_init_fn						platform_init;
	platform_deinit_fn						platform_deinit;
	platform_print_fn						platform_print;    //used for uart output
	
    platform_read_io_byte_fn				platform_read_io_byte;
	platform_write_io_byte_fn				platform_write_io_byte;

	platform_read_io_dword_fn               platform_read_io_dword;
	platform_write_io_dword_fn 				platform_write_io_dword;

	platform_read_pci_config_byte_fn		platform_read_pci_config_byte;
	platform_read_pci_config_word_fn		platform_read_pci_config_word;
	platform_read_pci_config_dword_fn       platform_read_pci_config_dword;
	platform_write_pci_config_byte_fn		platform_write_pci_config_byte;
	platform_write_pci_config_word_fn		platform_write_pci_config_word;
	platform_write_pci_config_dword_fn      platform_write_pci_config_dword;

	platform_get_linear_addr_fn				platform_get_linear_addr;
	platform_get_system_time_fn				platform_get_system_time;
	platform_delay_micro_seconds_fn			platform_delay_micro_seconds;
};



void 	dpu_info(int level, u8 *fmt, ...);

u32 	tt_strhash(u8 *str);
BOOL 	tt_is_same_str(u8 *str1, u8 *str2);
BOOL 	tt_is_end_with(const u8 *str1, u8 *str2);
BOOL 	tt_is_comment(u8 words[][SCRIPT_MAX_WORD_SIZE]);

TT_STATUS tt_get_words(u8* cmd_line, u32 *word_num, u8 str[][MAX_CMD_OPTION_NAME_SIZE]);

u32 	tt_get_last_bit(u32  value);
u32  	tt_get_bit_index(u32 value);
u8 		tt_get_bit_num(u32 value);

void 	tt_get_system_time(u64 * time);
void 	tt_delay_micro_seconds(u32 value);

//TT_CACHE_FLAG tt_get_cache_state(void);
//void tt_set_cache(TT_CACHE_FLAG flag);

void 	tt_write_u8(void * adapter, u32 register_port, u8 value);
void 	tt_write_u32(void * adapter, u32 register_port, u32 value);
u32 	tt_read_u32(void * adapter, u32 register_port);
u8 		tt_read_u8(void * adapter, u32 register_port);
void 	tt_read_u16(void * adapter, u32 register_port);
void 	tt_write_u16(void * adapter, u32 register_port, u16 value);
u32 	tt_read_buffer_u32(volatile u32 *register_port);
void 	tt_write_buffer_u32(volatile u32 * register_port, u32 value);

u8 		tt_read_io_byte(u16 register_port);
void 	tt_write_io_byte(u16 register_port, u8 value);

u32 	tt_read_io_dword(u16 register_port);
void 	tt_write_io_dword(u16 register_port, u32 value);

u32 	tt_read_mmio(u32 base , u32 port);
void 	tt_write_mmio(u32 base, u32 port, u32 value, u32 mask);

void * 	tt_malloc_mem(u32 bytes);
void * 	tt_free_mem(void *p);

static u32 get_bar_size(u32 bus, u32 dev, u32 func, u32 fb);
void 	tt_read_pci_config_byte(u8 bus, u8 dev, u8 func, u16 reg, u8* data);
void 	tt_read_pci_config_word(u8 bus, u8 dev, u8 func, u16 reg, u16 *data);
void 	tt_read_pci_config_dword(u8 bus, u8 dev, u8 func, u16 reg, u32 *data);

void 	tt_write_pci_config_byte(u8 bus, u8 dev, u8 func, u16 reg, u8 data);
void 	tt_write_pci_config_word(u8 bus, u8 dev, u8 func, u16 reg, u16 data);
void 	tt_write_pci_config_dword(u8 bus, u8 dev, u8 func, u16 reg, u32 data);

TT_STATUS 	tt_get_linear_addr(u64 phy_addr, u32 size, void **linear_addr);

u32 	tt_get_pci_info(struct base_adapter_t *base_adapter);
void 	tt_enable_pci_bridge(struct base_adapter_t *base_adapter);
void 	tt_enable_mmio_access(struct base_adapter_t *base_adapter);
void 	tt_init_card(struct dpu_adapter_t *dpu_adapter);

u32  	tt_alloc_video_mem(struct dpu_adapter_t *dpu_adapter, u32 size, u32 aligment);
void  	tt_free_video_mem(struct dpu_adapter_t *dpu_adapter, u32 aligned_offset);

struct surface_info_t* alloc_surface(struct dpu_adapter_t *dpu_adapter);
TT_STATUS 	free_surface(struct dpu_adapter_t *dpu_adapter, u32 index);

TT_STATUS 	tt_draw_surface(struct surface_info_t  *surface);
TT_STATUS  	tt_create_surface(struct dpu_adapter_t *dpu_adapter, struct surface_cmd_t *surface_cmd);


TT_STATUS tt_init_platform();
TT_STATUS tt_deinit_platform(struct dpu_adapter_t * dpu_adapter);
TT_STATUS init_platform_funcs();

#endif
