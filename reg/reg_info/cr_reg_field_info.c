#include "../reg.h"

struct reg_field cr_reg_field_0 = {
	.name = "Load_Hcnt_0",
	.bits_num = 8,
	.shift = 0,
	.reg_addr = 0x8830,
};
struct reg_info cr_reg_0 = {
	.reg_block_name = "cr",
	.reg_mmio_addr = 0x8830,
	.reg_sub_index = 0x0,
	.field_num = 1,
	.reg_in_bytes = 1,
};
struct reg_field cr_reg_field_1 = {
	.name = "Reserved",
	.bits_num = 2,
	.shift = 0,
	.reg_addr = 0x8831,
};
struct reg_field cr_reg_field_2 = {
	.name = "Load_Hcnt_1",
	.bits_num = 6,
	.shift = 2,
	.reg_addr = 0x8831,
};
struct reg_info cr_reg_1 = {
	.reg_block_name = "cr",
	.reg_mmio_addr = 0x8831,
	.reg_sub_index = 0x1,
	.field_num = 2,
	.reg_in_bytes = 1,
};
struct reg_field cr_reg_field_3 = {
	.name = "Load_Vcnt_0",
	.bits_num = 8,
	.shift = 0,
	.reg_addr = 0x8832,
};
struct reg_info cr_reg_2 = {
	.reg_block_name = "cr",
	.reg_mmio_addr = 0x8832,
	.reg_sub_index = 0x2,
	.field_num = 1,
	.reg_in_bytes = 1,
};
struct reg_field cr_reg_field_4 = {
	.name = "Reserved",
	.bits_num = 3,
	.shift = 0,
	.reg_addr = 0x8833,
};
struct reg_field cr_reg_field_5 = {
	.name = "Load_Vcnt_1",
	.bits_num = 5,
	.shift = 3,
	.reg_addr = 0x8833,
};
struct reg_info cr_reg_3 = {
	.reg_block_name = "cr",
	.reg_mmio_addr = 0x8833,
	.reg_sub_index = 0x3,
	.field_num = 2,
	.reg_in_bytes = 1,
};
struct reg_field cr_reg_field_6 = {
	.name = "Reserved",
	.bits_num = 6,
	.shift = 0,
	.reg_addr = 0x8834,
};
struct reg_field cr_reg_field_7 = {
	.name = "Vlock_En",
	.bits_num = 1,
	.shift = 6,
	.reg_addr = 0x8834,
};
struct reg_field cr_reg_field_8 = {
	.name = "Hlock_En",
	.bits_num = 1,
	.shift = 7,
	.reg_addr = 0x8834,
};
struct reg_info cr_reg_4 = {
	.reg_block_name = "cr",
	.reg_mmio_addr = 0x8834,
	.reg_sub_index = 0x4,
	.field_num = 3,
	.reg_in_bytes = 1,
};
struct reg_field cr_reg_field_9 = {
	.name = "Max_Istlnum_0",
	.bits_num = 8,
	.shift = 0,
	.reg_addr = 0x8835,
};
struct reg_info cr_reg_5 = {
	.reg_block_name = "cr",
	.reg_mmio_addr = 0x8835,
	.reg_sub_index = 0x5,
	.field_num = 1,
	.reg_in_bytes = 1,
};
struct reg_field cr_reg_field_10 = {
	.name = "Sldfr_En",
	.bits_num = 1,
	.shift = 0,
	.reg_addr = 0x8836,
};
struct reg_field cr_reg_field_11 = {
	.name = "Dynfr_En",
	.bits_num = 1,
	.shift = 1,
	.reg_addr = 0x8836,
};
struct reg_field cr_reg_field_12 = {
	.name = "Reserved",
	.bits_num = 1,
	.shift = 2,
	.reg_addr = 0x8836,
};
struct reg_field cr_reg_field_13 = {
	.name = "Max_Istlnum_1",
	.bits_num = 5,
	.shift = 3,
	.reg_addr = 0x8836,
};
struct reg_info cr_reg_6 = {
	.reg_block_name = "cr",
	.reg_mmio_addr = 0x8836,
	.reg_sub_index = 0x6,
	.field_num = 4,
	.reg_in_bytes = 1,
};
struct reg_field cr_reg_field_14 = {
	.name = "Reserved",
	.bits_num = 7,
	.shift = 0,
	.reg_addr = 0x8837,
};
struct reg_field cr_reg_field_15 = {
	.name = "Vsync_On_Flip",
	.bits_num = 1,
	.shift = 7,
	.reg_addr = 0x8837,
};
struct reg_info cr_reg_7 = {
	.reg_block_name = "cr",
	.reg_mmio_addr = 0x8837,
	.reg_sub_index = 0x7,
	.field_num = 2,
	.reg_in_bytes = 1,
};
struct reg_field cr_reg_field_16 = {
	.name = "Vga_En",
	.bits_num = 1,
	.shift = 0,
	.reg_addr = 0x8838,
};
struct reg_field cr_reg_field_17 = {
	.name = "Reserved",
	.bits_num = 3,
	.shift = 1,
	.reg_addr = 0x8838,
};
struct reg_field cr_reg_field_18 = {
	.name = "Vga_Screen_Off",
	.bits_num = 1,
	.shift = 4,
	.reg_addr = 0x8838,
};
struct reg_field cr_reg_field_19 = {
	.name = "Vga_So_Sel",
	.bits_num = 1,
	.shift = 5,
	.reg_addr = 0x8838,
};
struct reg_field cr_reg_field_20 = {
	.name = "Linerst_Sel",
	.bits_num = 1,
	.shift = 6,
	.reg_addr = 0x8838,
};
struct reg_field cr_reg_field_21 = {
	.name = "Vgareg_By_Vsync",
	.bits_num = 1,
	.shift = 7,
	.reg_addr = 0x8838,
};
struct reg_info cr_reg_8 = {
	.reg_block_name = "cr",
	.reg_mmio_addr = 0x8838,
	.reg_sub_index = 0x8,
	.field_num = 6,
	.reg_in_bytes = 1,
};
struct reg_field cr_reg_field_22 = {
	.name = "Vga_Ftbeg_0",
	.bits_num = 8,
	.shift = 0,
	.reg_addr = 0x8839,
};
struct reg_info cr_reg_9 = {
	.reg_block_name = "cr",
	.reg_mmio_addr = 0x8839,
	.reg_sub_index = 0x9,
	.field_num = 1,
	.reg_in_bytes = 1,
};
struct reg_field cr_reg_field_23 = {
	.name = "Df_Trig_Sel",
	.bits_num = 2,
	.shift = 0,
	.reg_addr = 0x883a,
};
struct reg_field cr_reg_field_24 = {
	.name = "Vga_Ftbeg_1",
	.bits_num = 6,
	.shift = 2,
	.reg_addr = 0x883a,
};
struct reg_info cr_reg_10 = {
	.reg_block_name = "cr",
	.reg_mmio_addr = 0x883a,
	.reg_sub_index = 0xa,
	.field_num = 2,
	.reg_in_bytes = 1,
};
struct reg_field cr_reg_field_25 = {
	.name = "Reserved",
	.bits_num = 5,
	.shift = 0,
	.reg_addr = 0x883b,
};
struct reg_field cr_reg_field_26 = {
	.name = "Blcur_Sel",
	.bits_num = 2,
	.shift = 5,
	.reg_addr = 0x883b,
};
struct reg_field cr_reg_field_27 = {
	.name = "Bldot_Sel",
	.bits_num = 1,
	.shift = 7,
	.reg_addr = 0x883b,
};
struct reg_info cr_reg_11 = {
	.reg_block_name = "cr",
	.reg_mmio_addr = 0x883b,
	.reg_sub_index = 0xb,
	.field_num = 3,
	.reg_in_bytes = 1,
};
struct reg_info * cr_reg_info[12] = {
&cr_reg_0,
&cr_reg_1,
&cr_reg_2,
&cr_reg_3,
&cr_reg_4,
&cr_reg_5,
&cr_reg_6,
&cr_reg_7,
&cr_reg_8,
&cr_reg_9,
&cr_reg_10,
&cr_reg_11,
};
struct reg_field * cr_reg_field_info[28] = {
&cr_reg_field_0,
&cr_reg_field_1,
&cr_reg_field_2,
&cr_reg_field_3,
&cr_reg_field_4,
&cr_reg_field_5,
&cr_reg_field_6,
&cr_reg_field_7,
&cr_reg_field_8,
&cr_reg_field_9,
&cr_reg_field_10,
&cr_reg_field_11,
&cr_reg_field_12,
&cr_reg_field_13,
&cr_reg_field_14,
&cr_reg_field_15,
&cr_reg_field_16,
&cr_reg_field_17,
&cr_reg_field_18,
&cr_reg_field_19,
&cr_reg_field_20,
&cr_reg_field_21,
&cr_reg_field_22,
&cr_reg_field_23,
&cr_reg_field_24,
&cr_reg_field_25,
&cr_reg_field_26,
&cr_reg_field_27,
};
unsigned int cr_reg_count = 12;
unsigned int cr_reg_start = 0x8830;
unsigned int cr_reg_end = 0x883b;
unsigned int cr_reg_in_bytes = 0x1;
unsigned int cr_reg_total_field_count = 28;
char * cr_reg_block_name = "cr";
