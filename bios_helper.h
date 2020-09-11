#ifndef _BIOS_HELPER_H_
#define _BIOS_HELPER_H_




#define OUTPD(a,b)  outpd((a),(b))
#define INPD(a)     inpd((a))



void bios_helper_init();
void bios_write_io(u8 * register_port, u8 value);
unsigned char bios_read_io(u8 * register_port);
void bios_set_cache_state(u32 value);
unsigned int bios_get_cache_state();
void bios_print(u8 * string);
void bios_delay_micro_seconds(u32 value);
void bios_get_system_time(u64 *time);


#endif
