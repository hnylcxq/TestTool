#include "../reg.h"

struct reg_field pwm_reg_field_0 = {
	.name = "Backlight_Value",
	.bits_num = 16,
	.shift = 0,
	.reg_addr = 0x4010,
};
struct reg_field pwm_reg_field_1 = {
	.name = "Pwm_Frequency_Counter",
	.bits_num = 16,
	.shift = 16,
	.reg_addr = 0x4010,
};
struct reg_info pwm_reg_0 = {
	.reg_block_name = "pwm",
	.reg_mmio_addr = 0x4010,
	.reg_sub_index = 0x0,
	.field_num = 2,
	.reg_in_bytes = 4,
};
struct reg_field pwm_reg_field_2 = {
	.name = "Reg_Pwm_En",
	.bits_num = 1,
	.shift = 0,
	.reg_addr = 0x4014,
};
struct reg_field pwm_reg_field_3 = {
	.name = "Reg_Pwm_Ctrl",
	.bits_num = 2,
	.shift = 1,
	.reg_addr = 0x4014,
};
struct reg_info pwm_reg_1 = {
	.reg_block_name = "pwm",
	.reg_mmio_addr = 0x4014,
	.reg_sub_index = 0x1,
	.field_num = 2,
	.reg_in_bytes = 4,
};
struct reg_field pwm_reg_field_4 = {
	.name = "Backlight_Value",
	.bits_num = 16,
	.shift = 0,
	.reg_addr = 0x4018,
};
struct reg_field pwm_reg_field_5 = {
	.name = "Pwm_Frequency_Counter",
	.bits_num = 16,
	.shift = 16,
	.reg_addr = 0x4018,
};
struct reg_info pwm_reg_2 = {
	.reg_block_name = "pwm",
	.reg_mmio_addr = 0x4018,
	.reg_sub_index = 0x2,
	.field_num = 2,
	.reg_in_bytes = 4,
};
struct reg_field pwm_reg_field_6 = {
	.name = "Reg_Pwm_En",
	.bits_num = 1,
	.shift = 0,
	.reg_addr = 0x401c,
};
struct reg_field pwm_reg_field_7 = {
	.name = "Reg_Pwm_Ctrl",
	.bits_num = 2,
	.shift = 1,
	.reg_addr = 0x401c,
};
struct reg_info pwm_reg_3 = {
	.reg_block_name = "pwm",
	.reg_mmio_addr = 0x401c,
	.reg_sub_index = 0x3,
	.field_num = 2,
	.reg_in_bytes = 4,
};
struct reg_info * pwm_reg_info[4] = {
&pwm_reg_0,
&pwm_reg_1,
&pwm_reg_2,
&pwm_reg_3,
};
struct reg_field * pwm_reg_field_info[8] = {
&pwm_reg_field_0,
&pwm_reg_field_1,
&pwm_reg_field_2,
&pwm_reg_field_3,
&pwm_reg_field_4,
&pwm_reg_field_5,
&pwm_reg_field_6,
&pwm_reg_field_7,
};
unsigned int pwm_reg_count = 4;
unsigned int pwm_reg_start = 0x4010;
unsigned int pwm_reg_end = 0x401c;
unsigned int pwm_reg_in_bytes = 0x4;
unsigned int pwm_reg_total_field_count = 8;
char * pwm_reg_block_name = "pwm";
