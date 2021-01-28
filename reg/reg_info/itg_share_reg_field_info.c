#include "../reg.h"

struct reg_field itgs_reg_field_0 = {
	.name = "Itg_Spl0_Stopreq",
	.bits_num = 1,
	.shift = 0,
	.reg_addr = 0x83a0,
};
struct reg_field itgs_reg_field_1 = {
	.name = "Itg_Spl1_Stopreq",
	.bits_num = 1,
	.shift = 1,
	.reg_addr = 0x83a0,
};
struct reg_field itgs_reg_field_2 = {
	.name = "Itg_Cur_Stopreq",
	.bits_num = 1,
	.shift = 2,
	.reg_addr = 0x83a0,
};
struct reg_field itgs_reg_field_3 = {
	.name = "Reserved_3",
	.bits_num = 1,
	.shift = 3,
	.reg_addr = 0x83a0,
};
struct reg_field itgs_reg_field_4 = {
	.name = "Itgb_Spl0_Stopreq",
	.bits_num = 1,
	.shift = 4,
	.reg_addr = 0x83a0,
};
struct reg_field itgs_reg_field_5 = {
	.name = "Itgb_Spl1_Stopreq",
	.bits_num = 1,
	.shift = 5,
	.reg_addr = 0x83a0,
};
struct reg_field itgs_reg_field_6 = {
	.name = "Itgb_Cur_Stopreq",
	.bits_num = 1,
	.shift = 6,
	.reg_addr = 0x83a0,
};
struct reg_field itgs_reg_field_7 = {
	.name = "Reserved_2",
	.bits_num = 1,
	.shift = 7,
	.reg_addr = 0x83a0,
};
struct reg_field itgs_reg_field_8 = {
	.name = "Itgc_Spl0_Stopreq",
	.bits_num = 1,
	.shift = 8,
	.reg_addr = 0x83a0,
};
struct reg_field itgs_reg_field_9 = {
	.name = "Itgc_Spl1_Stopreq",
	.bits_num = 1,
	.shift = 9,
	.reg_addr = 0x83a0,
};
struct reg_field itgs_reg_field_10 = {
	.name = "Itgc_Cur_Stopreq",
	.bits_num = 1,
	.shift = 10,
	.reg_addr = 0x83a0,
};
struct reg_field itgs_reg_field_11 = {
	.name = "Reserved_1",
	.bits_num = 21,
	.shift = 11,
	.reg_addr = 0x83a0,
};
struct reg_info itgs_reg_0 = {
	.reg_block_name = "itgs",
	.reg_mmio_addr = 0x83a0,
	.reg_sub_index = 0x0,
	.field_num = 12,
	.reg_in_bytes = 4,
};
struct reg_info * itgs_reg_info[1] = {
&itgs_reg_0,
};
struct reg_field * itgs_reg_field_info[12] = {
&itgs_reg_field_0,
&itgs_reg_field_1,
&itgs_reg_field_2,
&itgs_reg_field_3,
&itgs_reg_field_4,
&itgs_reg_field_5,
&itgs_reg_field_6,
&itgs_reg_field_7,
&itgs_reg_field_8,
&itgs_reg_field_9,
&itgs_reg_field_10,
&itgs_reg_field_11,
};
unsigned int itgs_reg_count = 1;
unsigned int itgs_reg_start = 0x83a0;
unsigned int itgs_reg_end = 0x83a0;
unsigned int itgs_reg_in_bytes = 0x4;
unsigned int itgs_reg_total_field_count = 12;
char * itgs_reg_block_name = "itgs";
