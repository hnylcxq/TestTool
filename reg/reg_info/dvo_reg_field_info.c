#include "../reg.h"

struct reg_field dvo_reg_field_0 = {
	.name = "Source_Sel",
	.bits_num = 2,
	.shift = 0,
	.reg_addr = 0x4020,
};
struct reg_field dvo_reg_field_1 = {
	.name = "Hsync_Inv",
	.bits_num = 1,
	.shift = 2,
	.reg_addr = 0x4020,
};
struct reg_field dvo_reg_field_2 = {
	.name = "Vsync_Inv",
	.bits_num = 1,
	.shift = 3,
	.reg_addr = 0x4020,
};
struct reg_field dvo_reg_field_3 = {
	.name = "Dat_Format",
	.bits_num = 4,
	.shift = 4,
	.reg_addr = 0x4020,
};
struct reg_field dvo_reg_field_4 = {
	.name = "422_Aver",
	.bits_num = 1,
	.shift = 8,
	.reg_addr = 0x4020,
};
struct reg_field dvo_reg_field_5 = {
	.name = "Sdr_Ind",
	.bits_num = 1,
	.shift = 9,
	.reg_addr = 0x4020,
};
struct reg_field dvo_reg_field_6 = {
	.name = "Bypass_Ctl",
	.bits_num = 2,
	.shift = 10,
	.reg_addr = 0x4020,
};
struct reg_field dvo_reg_field_7 = {
	.name = "Reserved_2",
	.bits_num = 2,
	.shift = 12,
	.reg_addr = 0x4020,
};
struct reg_field dvo_reg_field_8 = {
	.name = "Clk_Inv_Ctl",
	.bits_num = 1,
	.shift = 14,
	.reg_addr = 0x4020,
};
struct reg_field dvo_reg_field_9 = {
	.name = "Clk_Out_Inv_Ctl",
	.bits_num = 1,
	.shift = 15,
	.reg_addr = 0x4020,
};
struct reg_field dvo_reg_field_10 = {
	.name = "Clk_Delay",
	.bits_num = 4,
	.shift = 16,
	.reg_addr = 0x4020,
};
struct reg_field dvo_reg_field_11 = {
	.name = "Reserved_1",
	.bits_num = 12,
	.shift = 20,
	.reg_addr = 0x4020,
};
struct reg_info dvo_reg_0 = {
	.reg_block_name = "dvo",
	.reg_mmio_addr = 0x4020,
	.reg_sub_index = 0x0,
	.field_num = 12,
	.reg_in_bytes = 4,
};
struct reg_info * dvo_reg_info[1] = {
&dvo_reg_0,
};
struct reg_field * dvo_reg_field_info[12] = {
&dvo_reg_field_0,
&dvo_reg_field_1,
&dvo_reg_field_2,
&dvo_reg_field_3,
&dvo_reg_field_4,
&dvo_reg_field_5,
&dvo_reg_field_6,
&dvo_reg_field_7,
&dvo_reg_field_8,
&dvo_reg_field_9,
&dvo_reg_field_10,
&dvo_reg_field_11,
};
unsigned int dvo_reg_count = 1;
unsigned int dvo_reg_start = 0x4020;
unsigned int dvo_reg_end = 0x4020;
unsigned int dvo_reg_in_bytes = 0x4;
unsigned int dvo_reg_total_field_count = 12;
char * dvo_reg_block_name = "dvo";
