#include "../reg.h"

struct reg_field cr2_reg_field_0 = {
	.name = "Load_Hcnt_0",
	.bits_num = 8,
	.shift = 0,
	.reg_addr = 0x8930,
};
struct reg_info cr2_reg_0 = {
	.reg_block_name = "cr2",
	.reg_mmio_addr = 0x8930,
	.reg_sub_index = 0x0,
	.field_num = 1,
	.reg_in_bytes = 1,
};
struct reg_field cr2_reg_field_1 = {
	.name = "Reserved",
	.bits_num = 2,
	.shift = 0,
	.reg_addr = 0x8931,
};
struct reg_field cr2_reg_field_2 = {
	.name = "Load_Hcnt_1",
	.bits_num = 6,
	.shift = 2,
	.reg_addr = 0x8931,
};
struct reg_info cr2_reg_1 = {
	.reg_block_name = "cr2",
	.reg_mmio_addr = 0x8931,
	.reg_sub_index = 0x1,
	.field_num = 2,
	.reg_in_bytes = 1,
};
struct reg_field cr2_reg_field_3 = {
	.name = "Load_Vcnt_0",
	.bits_num = 8,
	.shift = 0,
	.reg_addr = 0x8932,
};
struct reg_info cr2_reg_2 = {
	.reg_block_name = "cr2",
	.reg_mmio_addr = 0x8932,
	.reg_sub_index = 0x2,
	.field_num = 1,
	.reg_in_bytes = 1,
};
struct reg_field cr2_reg_field_4 = {
	.name = "Reserved",
	.bits_num = 3,
	.shift = 0,
	.reg_addr = 0x8933,
};
struct reg_field cr2_reg_field_5 = {
	.name = "Load_Vcnt_1",
	.bits_num = 5,
	.shift = 3,
	.reg_addr = 0x8933,
};
struct reg_info cr2_reg_3 = {
	.reg_block_name = "cr2",
	.reg_mmio_addr = 0x8933,
	.reg_sub_index = 0x3,
	.field_num = 2,
	.reg_in_bytes = 1,
};
struct reg_field cr2_reg_field_6 = {
	.name = "Reserved",
	.bits_num = 6,
	.shift = 0,
	.reg_addr = 0x8934,
};
struct reg_field cr2_reg_field_7 = {
	.name = "Vlock_En",
	.bits_num = 1,
	.shift = 6,
	.reg_addr = 0x8934,
};
struct reg_field cr2_reg_field_8 = {
	.name = "Hlock_En",
	.bits_num = 1,
	.shift = 7,
	.reg_addr = 0x8934,
};
struct reg_info cr2_reg_4 = {
	.reg_block_name = "cr2",
	.reg_mmio_addr = 0x8934,
	.reg_sub_index = 0x4,
	.field_num = 3,
	.reg_in_bytes = 1,
};
struct reg_field cr2_reg_field_9 = {
	.name = "Max_Istlnum_0",
	.bits_num = 8,
	.shift = 0,
	.reg_addr = 0x8935,
};
struct reg_info cr2_reg_5 = {
	.reg_block_name = "cr2",
	.reg_mmio_addr = 0x8935,
	.reg_sub_index = 0x5,
	.field_num = 1,
	.reg_in_bytes = 1,
};
struct reg_field cr2_reg_field_10 = {
	.name = "Sldfr_En",
	.bits_num = 1,
	.shift = 0,
	.reg_addr = 0x8936,
};
struct reg_field cr2_reg_field_11 = {
	.name = "Dynfr_En",
	.bits_num = 1,
	.shift = 1,
	.reg_addr = 0x8936,
};
struct reg_field cr2_reg_field_12 = {
	.name = "Reserved",
	.bits_num = 1,
	.shift = 2,
	.reg_addr = 0x8936,
};
struct reg_field cr2_reg_field_13 = {
	.name = "Max_Istlnum_1",
	.bits_num = 5,
	.shift = 3,
	.reg_addr = 0x8936,
};
struct reg_info cr2_reg_6 = {
	.reg_block_name = "cr2",
	.reg_mmio_addr = 0x8936,
	.reg_sub_index = 0x6,
	.field_num = 4,
	.reg_in_bytes = 1,
};
struct reg_field cr2_reg_field_14 = {
	.name = "Reserved",
	.bits_num = 7,
	.shift = 0,
	.reg_addr = 0x8937,
};
struct reg_field cr2_reg_field_15 = {
	.name = "Vsync_On_Flip",
	.bits_num = 1,
	.shift = 7,
	.reg_addr = 0x8937,
};
struct reg_info cr2_reg_7 = {
	.reg_block_name = "cr2",
	.reg_mmio_addr = 0x8937,
	.reg_sub_index = 0x7,
	.field_num = 2,
	.reg_in_bytes = 1,
};
struct reg_field cr2_reg_field_16 = {
	.name = "Vga_En",
	.bits_num = 1,
	.shift = 0,
	.reg_addr = 0x8938,
};
struct reg_field cr2_reg_field_17 = {
	.name = "Reserved",
	.bits_num = 3,
	.shift = 1,
	.reg_addr = 0x8938,
};
struct reg_field cr2_reg_field_18 = {
	.name = "Vga_Screen_Off",
	.bits_num = 1,
	.shift = 4,
	.reg_addr = 0x8938,
};
struct reg_field cr2_reg_field_19 = {
	.name = "Vga_So_Sel",
	.bits_num = 1,
	.shift = 5,
	.reg_addr = 0x8938,
};
struct reg_field cr2_reg_field_20 = {
	.name = "Linerst_Sel",
	.bits_num = 1,
	.shift = 6,
	.reg_addr = 0x8938,
};
struct reg_field cr2_reg_field_21 = {
	.name = "Vgareg_By_Vsync",
	.bits_num = 1,
	.shift = 7,
	.reg_addr = 0x8938,
};
struct reg_info cr2_reg_8 = {
	.reg_block_name = "cr2",
	.reg_mmio_addr = 0x8938,
	.reg_sub_index = 0x8,
	.field_num = 6,
	.reg_in_bytes = 1,
};
struct reg_field cr2_reg_field_22 = {
	.name = "Vga_Ftbeg_0",
	.bits_num = 8,
	.shift = 0,
	.reg_addr = 0x8939,
};
struct reg_info cr2_reg_9 = {
	.reg_block_name = "cr2",
	.reg_mmio_addr = 0x8939,
	.reg_sub_index = 0x9,
	.field_num = 1,
	.reg_in_bytes = 1,
};
struct reg_field cr2_reg_field_23 = {
	.name = "Df_Trig_Sel",
	.bits_num = 2,
	.shift = 0,
	.reg_addr = 0x893a,
};
struct reg_field cr2_reg_field_24 = {
	.name = "Vga_Ftbeg_1",
	.bits_num = 6,
	.shift = 2,
	.reg_addr = 0x893a,
};
struct reg_info cr2_reg_10 = {
	.reg_block_name = "cr2",
	.reg_mmio_addr = 0x893a,
	.reg_sub_index = 0xa,
	.field_num = 2,
	.reg_in_bytes = 1,
};
struct reg_field cr2_reg_field_25 = {
	.name = "Reserved",
	.bits_num = 5,
	.shift = 0,
	.reg_addr = 0x893b,
};
struct reg_field cr2_reg_field_26 = {
	.name = "Blcur_Sel",
	.bits_num = 2,
	.shift = 5,
	.reg_addr = 0x893b,
};
struct reg_field cr2_reg_field_27 = {
	.name = "Bldot_Sel",
	.bits_num = 1,
	.shift = 7,
	.reg_addr = 0x893b,
};
struct reg_info cr2_reg_11 = {
	.reg_block_name = "cr2",
	.reg_mmio_addr = 0x893b,
	.reg_sub_index = 0xb,
	.field_num = 3,
	.reg_in_bytes = 1,
};
struct reg_info * cr2_reg_info[12] = {
&cr2_reg_0,
&cr2_reg_1,
&cr2_reg_2,
&cr2_reg_3,
&cr2_reg_4,
&cr2_reg_5,
&cr2_reg_6,
&cr2_reg_7,
&cr2_reg_8,
&cr2_reg_9,
&cr2_reg_10,
&cr2_reg_11,
};
struct reg_field * cr2_reg_field_info[28] = {
&cr2_reg_field_0,
&cr2_reg_field_1,
&cr2_reg_field_2,
&cr2_reg_field_3,
&cr2_reg_field_4,
&cr2_reg_field_5,
&cr2_reg_field_6,
&cr2_reg_field_7,
&cr2_reg_field_8,
&cr2_reg_field_9,
&cr2_reg_field_10,
&cr2_reg_field_11,
&cr2_reg_field_12,
&cr2_reg_field_13,
&cr2_reg_field_14,
&cr2_reg_field_15,
&cr2_reg_field_16,
&cr2_reg_field_17,
&cr2_reg_field_18,
&cr2_reg_field_19,
&cr2_reg_field_20,
&cr2_reg_field_21,
&cr2_reg_field_22,
&cr2_reg_field_23,
&cr2_reg_field_24,
&cr2_reg_field_25,
&cr2_reg_field_26,
&cr2_reg_field_27,
};
unsigned int cr2_reg_count = 12;
unsigned int cr2_reg_start = 0x8930;
unsigned int cr2_reg_end = 0x893b;
unsigned int cr2_reg_in_bytes = 0x1;
unsigned int cr2_reg_total_field_count = 28;
char * cr2_reg_block_name = "cr2";
