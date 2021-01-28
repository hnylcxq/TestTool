#include "../reg.h"

struct reg_field intg_reg_field_0 = {
	.name = "Reserved",
	.bits_num = 19,
	.shift = 0,
	.reg_addr = 0x4000,
};
struct reg_field intg_reg_field_1 = {
	.name = "Dp_Link_Training",
	.bits_num = 1,
	.shift = 19,
	.reg_addr = 0x4000,
};
struct reg_field intg_reg_field_2 = {
	.name = "Dp_Ephy",
	.bits_num = 1,
	.shift = 20,
	.reg_addr = 0x4000,
};
struct reg_field intg_reg_field_3 = {
	.name = "Cec",
	.bits_num = 1,
	.shift = 21,
	.reg_addr = 0x4000,
};
struct reg_field intg_reg_field_4 = {
	.name = "Scdc_Wait_Sw_Tt",
	.bits_num = 1,
	.shift = 22,
	.reg_addr = 0x4000,
};
struct reg_field intg_reg_field_5 = {
	.name = "Scdc_Rr",
	.bits_num = 1,
	.shift = 23,
	.reg_addr = 0x4000,
};
struct reg_field intg_reg_field_6 = {
	.name = "Dp_Hpd",
	.bits_num = 1,
	.shift = 24,
	.reg_addr = 0x4000,
};
struct reg_field intg_reg_field_7 = {
	.name = "Hdmi_Hpd",
	.bits_num = 1,
	.shift = 25,
	.reg_addr = 0x4000,
};
struct reg_field intg_reg_field_8 = {
	.name = "Codec2",
	.bits_num = 1,
	.shift = 26,
	.reg_addr = 0x4000,
};
struct reg_field intg_reg_field_9 = {
	.name = "Codec1",
	.bits_num = 1,
	.shift = 27,
	.reg_addr = 0x4000,
};
struct reg_field intg_reg_field_10 = {
	.name = "Vsync3",
	.bits_num = 1,
	.shift = 28,
	.reg_addr = 0x4000,
};
struct reg_field intg_reg_field_11 = {
	.name = "Vsync2",
	.bits_num = 1,
	.shift = 29,
	.reg_addr = 0x4000,
};
struct reg_field intg_reg_field_12 = {
	.name = "Vsync1",
	.bits_num = 1,
	.shift = 30,
	.reg_addr = 0x4000,
};
struct reg_field intg_reg_field_13 = {
	.name = "Virq",
	.bits_num = 1,
	.shift = 31,
	.reg_addr = 0x4000,
};
struct reg_info intg_reg_0 = {
	.reg_block_name = "intg",
	.reg_mmio_addr = 0x4000,
	.reg_sub_index = 0x0,
	.field_num = 14,
	.reg_in_bytes = 4,
};
struct reg_field intg_reg_field_14 = {
	.name = "Reserved",
	.bits_num = 19,
	.shift = 0,
	.reg_addr = 0x4004,
};
struct reg_field intg_reg_field_15 = {
	.name = "Dp_Link_Training",
	.bits_num = 1,
	.shift = 19,
	.reg_addr = 0x4004,
};
struct reg_field intg_reg_field_16 = {
	.name = "Dp_Ephy",
	.bits_num = 1,
	.shift = 20,
	.reg_addr = 0x4004,
};
struct reg_field intg_reg_field_17 = {
	.name = "Cec",
	.bits_num = 1,
	.shift = 21,
	.reg_addr = 0x4004,
};
struct reg_field intg_reg_field_18 = {
	.name = "Scdc_Wait_Sw_Tt",
	.bits_num = 1,
	.shift = 22,
	.reg_addr = 0x4004,
};
struct reg_field intg_reg_field_19 = {
	.name = "Scdc_Rr",
	.bits_num = 1,
	.shift = 23,
	.reg_addr = 0x4004,
};
struct reg_field intg_reg_field_20 = {
	.name = "Dp_Hpd",
	.bits_num = 1,
	.shift = 24,
	.reg_addr = 0x4004,
};
struct reg_field intg_reg_field_21 = {
	.name = "Hdmi_Hpd",
	.bits_num = 1,
	.shift = 25,
	.reg_addr = 0x4004,
};
struct reg_field intg_reg_field_22 = {
	.name = "Codec2",
	.bits_num = 1,
	.shift = 26,
	.reg_addr = 0x4004,
};
struct reg_field intg_reg_field_23 = {
	.name = "Codec1",
	.bits_num = 1,
	.shift = 27,
	.reg_addr = 0x4004,
};
struct reg_field intg_reg_field_24 = {
	.name = "Vsync3",
	.bits_num = 1,
	.shift = 28,
	.reg_addr = 0x4004,
};
struct reg_field intg_reg_field_25 = {
	.name = "Vsync2",
	.bits_num = 1,
	.shift = 29,
	.reg_addr = 0x4004,
};
struct reg_field intg_reg_field_26 = {
	.name = "Vsync1",
	.bits_num = 1,
	.shift = 30,
	.reg_addr = 0x4004,
};
struct reg_field intg_reg_field_27 = {
	.name = "Virq",
	.bits_num = 1,
	.shift = 31,
	.reg_addr = 0x4004,
};
struct reg_info intg_reg_1 = {
	.reg_block_name = "intg",
	.reg_mmio_addr = 0x4004,
	.reg_sub_index = 0x1,
	.field_num = 14,
	.reg_in_bytes = 4,
};
struct reg_field intg_reg_field_28 = {
	.name = "Reserved",
	.bits_num = 19,
	.shift = 0,
	.reg_addr = 0x4008,
};
struct reg_field intg_reg_field_29 = {
	.name = "Dp_Link_Training",
	.bits_num = 1,
	.shift = 19,
	.reg_addr = 0x4008,
};
struct reg_field intg_reg_field_30 = {
	.name = "Dp_Ephy",
	.bits_num = 1,
	.shift = 20,
	.reg_addr = 0x4008,
};
struct reg_field intg_reg_field_31 = {
	.name = "Cec",
	.bits_num = 1,
	.shift = 21,
	.reg_addr = 0x4008,
};
struct reg_field intg_reg_field_32 = {
	.name = "Scdc_Wait_Sw_Tt",
	.bits_num = 1,
	.shift = 22,
	.reg_addr = 0x4008,
};
struct reg_field intg_reg_field_33 = {
	.name = "Scdc_Rr",
	.bits_num = 1,
	.shift = 23,
	.reg_addr = 0x4008,
};
struct reg_field intg_reg_field_34 = {
	.name = "Dp_Hpd",
	.bits_num = 1,
	.shift = 24,
	.reg_addr = 0x4008,
};
struct reg_field intg_reg_field_35 = {
	.name = "Hdmi_Hpd",
	.bits_num = 1,
	.shift = 25,
	.reg_addr = 0x4008,
};
struct reg_field intg_reg_field_36 = {
	.name = "Codec2",
	.bits_num = 1,
	.shift = 26,
	.reg_addr = 0x4008,
};
struct reg_field intg_reg_field_37 = {
	.name = "Codec1",
	.bits_num = 1,
	.shift = 27,
	.reg_addr = 0x4008,
};
struct reg_field intg_reg_field_38 = {
	.name = "Vsync3",
	.bits_num = 1,
	.shift = 28,
	.reg_addr = 0x4008,
};
struct reg_field intg_reg_field_39 = {
	.name = "Vsync2",
	.bits_num = 1,
	.shift = 29,
	.reg_addr = 0x4008,
};
struct reg_field intg_reg_field_40 = {
	.name = "Vsync1",
	.bits_num = 1,
	.shift = 30,
	.reg_addr = 0x4008,
};
struct reg_field intg_reg_field_41 = {
	.name = "Virq",
	.bits_num = 1,
	.shift = 31,
	.reg_addr = 0x4008,
};
struct reg_info intg_reg_2 = {
	.reg_block_name = "intg",
	.reg_mmio_addr = 0x4008,
	.reg_sub_index = 0x2,
	.field_num = 14,
	.reg_in_bytes = 4,
};
struct reg_info * intg_reg_info[3] = {
&intg_reg_0,
&intg_reg_1,
&intg_reg_2,
};
struct reg_field * intg_reg_field_info[42] = {
&intg_reg_field_0,
&intg_reg_field_1,
&intg_reg_field_2,
&intg_reg_field_3,
&intg_reg_field_4,
&intg_reg_field_5,
&intg_reg_field_6,
&intg_reg_field_7,
&intg_reg_field_8,
&intg_reg_field_9,
&intg_reg_field_10,
&intg_reg_field_11,
&intg_reg_field_12,
&intg_reg_field_13,
&intg_reg_field_14,
&intg_reg_field_15,
&intg_reg_field_16,
&intg_reg_field_17,
&intg_reg_field_18,
&intg_reg_field_19,
&intg_reg_field_20,
&intg_reg_field_21,
&intg_reg_field_22,
&intg_reg_field_23,
&intg_reg_field_24,
&intg_reg_field_25,
&intg_reg_field_26,
&intg_reg_field_27,
&intg_reg_field_28,
&intg_reg_field_29,
&intg_reg_field_30,
&intg_reg_field_31,
&intg_reg_field_32,
&intg_reg_field_33,
&intg_reg_field_34,
&intg_reg_field_35,
&intg_reg_field_36,
&intg_reg_field_37,
&intg_reg_field_38,
&intg_reg_field_39,
&intg_reg_field_40,
&intg_reg_field_41,
};
unsigned int intg_reg_count = 3;
unsigned int intg_reg_start = 0x4000;
unsigned int intg_reg_end = 0x4008;
unsigned int intg_reg_in_bytes = 0x4;
unsigned int intg_reg_total_field_count = 42;
char * intg_reg_block_name = "intg";
