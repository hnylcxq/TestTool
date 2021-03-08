
#include <stdio.h>
#include <sys/io.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <sys/time.h>


#include"util.h"
//used for locate test 
#if 0

typedef enum _TT_STATUS_
{
    TT_PASS = 0,
    TT_FAIL = 1,
    TT_INVALID_PARAM,
}TT_STATUS;


typedef		unsigned char       BOOL;

typedef     unsigned char       u8;
typedef     unsigned short      u16;
typedef     unsigned int        u32;
typedef     unsigned long long  u64;

typedef     char                i8;
typedef     short               i16;
typedef     int                 i32;
typedef     long long           i64;


typedef void (*platform_init_fn)();
typedef void (*platform_deinit_fn)();

typedef u16 (*platform_read_pci_config_word_fn)(u8 bus, u8 dev, u8 func, u16 reg, u16 *data);
typedef u16 (*platform_read_pci_config_byte_fn)(u8 bus, u8 dev, u8 func, u16 reg, u8 *data);

typedef u16 (*platform_read_pci_config_dword_fn)(u8 bus, u8 dev, u8 func, u16 reg, u32 *data);
typedef u16 (*platform_write_pci_config_dword_fn)(u8 bus, u8 dev, u8 func, u16 reg, u32 data);

typedef u16 (*platform_write_pci_config_word_fn)(u8 bus, u8 dev, u8 func,u16 reg,  u16 data);
typedef u16 (*platform_write_pci_config_byte_fn)(u8 bus, u8 dev, u8 func,u16 reg, u8 data);

typedef TT_STATUS (*platform_get_linear_addr_fn)(u64 phy_addr, u32 size, void **linear_addr);

typedef u8 (*platform_read_io_byte_fn)(u16 register_port);
typedef void (*platform_write_io_byte_fn)(u16 register_port, u8 value);

typedef u32 (*platform_read_io_dword_fn)(u16 register_port);
typedef void (*platform_write_io_dword_fn)(u16 register_port, u32 value);

typedef void (*platform_get_system_time_fn)(u64 *time);
typedef void (*platform_delay_micro_seconds_fn)(u32 value);
typedef void (*platform_print_fn)(u8 * string);


struct platform_funcs_t {
	platform_init_fn						platform_init;
	platform_print_fn						platform_print;
	
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

#endif

TT_STATUS linux_helper_init()
{
	//printf("in linux_helper_init \n");

	iopl(3);
	return TT_PASS;
}


TT_STATUS linux_helper_deinit(struct dpu_adapter_t *dpu_adapter)
{

	if(dpu_adapter->base.mmio_base)
	{
		munmap(dpu_adapter->base.mmio_base, 0x80000);
	}

	if (dpu_adapter->base.fb_base)
	{
		munmap(dpu_adapter->base.fb_base, dpu_adapter->base.fb_size);
	}

    iopl(0);

	return TT_PASS;

}

//uart output, no need now
void linux_print(u8* string)
{
	//printf("%s", string);
}

u8 linux_read_io_byte(u16 register_port)
{
	return inb(register_port);
}

void  linux_write_io_byte(u16 register_port, u8 value)
{
	outb(value,register_port);
}


u32 linux_read_io_dword(u16 register_port)
{
  	return inl(register_port);
}

void linux_write_io_dword(u16 register_port, u32 value)
{
	outl(value, register_port);
}

u16 linux_read_pci_config_word(u8 bus, u8 dev, u8 func, u16 reg, u16 *data)
{
    outl(0x80000000 | (bus << 16) | (dev << 11) | (func << 8) | reg, 0xcf8);  
    *data = inw(0xcfc + (reg & 2));  
    return 0;  
}
u16 linux_read_pci_config_byte(u8 bus, u8 dev, u8 func, u16 reg, u8 *data)
{
    outl(0x80000000 | (bus << 16) | (dev << 11) | ( func<< 8) | reg, 0xcf8);  
    *data = inb(0xcfc + (reg & 3));  
    return 0;  
}
u16	linux_read_pci_config_dword(u8 bus, u8 dev, u8 func, u16 reg, u32 *data)
{
    outl(0x80000000 | (bus << 16) | (dev << 11) | (func << 8) | reg, 0xcf8);  
    *data = inl(0xcfc);  
    return 0; 
}


u16 linux_write_pci_config_word(u8 bus, u8 dev, u8 func, u16 reg, u16 data)
{
    outl(0x80000000 | (bus << 16) | (dev << 11) | (func << 8) | reg, 0xcf8);  
    outw(data, 0xcfc + (reg & 2)); 
	return 0;
}
u16 linux_write_pci_config_byte(u8 bus, u8 dev, u8 func, u16 reg, u8 data)
{
    outl(0x80000000 | (bus << 16) | (dev << 11) | (func << 8) | reg, 0xcf8);  
    outb(data, 0xcfc + (reg & 3));

	return 0;
}
u16	linux_write_pci_config_dword(u8 bus, u8 dev, u8 func, u16 reg, u32 data)
{
    outl(0x80000000 | (bus << 16) | (dev << 11) | (func << 8) | reg, 0xcf8);  
    outl(data, 0xcfc);  

	return 0;
}

TT_STATUS linux_get_linear_addr(u64 phy_addr, u32 size, void **linear_addr)
{
	TT_STATUS ret = TT_PASS;
	i32 	fd = -1;


	fd = open("/dev/tt_device", O_RDWR, 0);

	printf("phy addr is 0x%llx ,size is 0x%x\n", phy_addr, size);

	if(fd >= 0)
	{
		*linear_addr = mmap(0, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, phy_addr);

		if(*linear_addr == MAP_FAILED)
		{
			printf("fatal error ,cann't get linear addr \n");
			ret = TT_FAIL;
			goto end;
		}
	}
	else
	{
		printf("fatal error, cann't open tt_dev \n ");
		ret =  TT_FAIL;
		goto end;
	}

end:
	if (fd >= 0)
	{
		close(fd);
	}

	return ret;
}

void linux_get_system_time(u64 *time)
{
	struct timeval tv;
    gettimeofday(&tv,NULL);

	*time = tv.tv_sec*1000000 + tv.tv_usec;
}

void linux_delay_micro_seconds(u32 value)
{
	usleep(value);
}

struct platform_funcs_t  linux_funcs = {

	linux_helper_init,
	linux_helper_deinit,
	linux_print,

	linux_read_io_byte,
	linux_write_io_byte,

	linux_read_io_dword,
	linux_write_io_dword,

	linux_read_pci_config_byte,
	linux_read_pci_config_word,
	linux_read_pci_config_dword,
	linux_write_pci_config_byte,
	linux_write_pci_config_word,
	linux_write_pci_config_dword,

	linux_get_linear_addr,
	linux_get_system_time,
	linux_delay_micro_seconds
};


#if 0
void main(int argc,char * * argv)
{
	printf("hello test tool \n");
}

#endif
