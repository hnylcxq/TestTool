#include "../reg.h"

struct reg_field pipe3_reg_field_0 = {
	.name = "Lut_Bitwidth",
	.bits_num = 2,
	.shift = 0,
	.reg_addr = 0x84c0,
};
struct reg_field pipe3_reg_field_1 = {
	.name = "Lut_Intp_On",
	.bits_num = 1,
	.shift = 2,
	.reg_addr = 0x84c0,
};
struct reg_field pipe3_reg_field_2 = {
	.name = "Lut_Lut_En",
	.bits_num = 1,
	.shift = 3,
	.reg_addr = 0x84c0,
};
struct reg_field pipe3_reg_field_3 = {
	.name = "Reserved_1",
	.bits_num = 28,
	.shift = 4,
	.reg_addr = 0x84c0,
};
struct reg_info pipe3_reg_0 = {
	.reg_block_name = "pipe3",
	.reg_mmio_addr = 0x84c0,
	.reg_sub_index = 0x0,
	.field_num = 4,
	.reg_in_bytes = 4,
};
struct reg_field pipe3_reg_field_4 = {
	.name = "Bg_Color",
	.bits_num = 30,
	.shift = 0,
	.reg_addr = 0x84c4,
};
struct reg_field pipe3_reg_field_5 = {
	.name = "Bg_Ycbcr",
	.bits_num = 1,
	.shift = 30,
	.reg_addr = 0x84c4,
};
struct reg_field pipe3_reg_field_6 = {
	.name = "Reserved_1",
	.bits_num = 1,
	.shift = 31,
	.reg_addr = 0x84c4,
};
struct reg_info pipe3_reg_1 = {
	.reg_block_name = "pipe3",
	.reg_mmio_addr = 0x84c4,
	.reg_sub_index = 0x1,
	.field_num = 3,
	.reg_in_bytes = 4,
};
struct reg_field pipe3_reg_field_7 = {
	.name = "Reserved_6",
	.bits_num = 3,
	.shift = 0,
	.reg_addr = 0x84c8,
};
struct reg_field pipe3_reg_field_8 = {
	.name = "Ovl0_Alpha_Rang",
	.bits_num = 1,
	.shift = 3,
	.reg_addr = 0x84c8,
};
struct reg_field pipe3_reg_field_9 = {
	.name = "Ovl0_Color_Key_Sel",
	.bits_num = 2,
	.shift = 4,
	.reg_addr = 0x84c8,
};
struct reg_field pipe3_reg_field_10 = {
	.name = "Ovl0_Alpha_Key_Sel",
	.bits_num = 2,
	.shift = 6,
	.reg_addr = 0x84c8,
};
struct reg_field pipe3_reg_field_11 = {
	.name = "Ovl0_Plane_Alpha",
	.bits_num = 8,
	.shift = 8,
	.reg_addr = 0x84c8,
};
struct reg_field pipe3_reg_field_12 = {
	.name = "Ovl0_Inv_Alpha",
	.bits_num = 1,
	.shift = 16,
	.reg_addr = 0x84c8,
};
struct reg_field pipe3_reg_field_13 = {
	.name = "Ovl0_Alpha_Blend_Mode",
	.bits_num = 1,
	.shift = 17,
	.reg_addr = 0x84c8,
};
struct reg_field pipe3_reg_field_14 = {
	.name = "Reserved_3",
	.bits_num = 2,
	.shift = 18,
	.reg_addr = 0x84c8,
};
struct reg_field pipe3_reg_field_15 = {
	.name = "Ovl0_Plb_Fct",
	.bits_num = 4,
	.shift = 20,
	.reg_addr = 0x84c8,
};
struct reg_field pipe3_reg_field_16 = {
	.name = "Ovl0_Pla_Fct",
	.bits_num = 4,
	.shift = 24,
	.reg_addr = 0x84c8,
};
struct reg_field pipe3_reg_field_17 = {
	.name = "Ovl0_Key_Mode",
	.bits_num = 4,
	.shift = 28,
	.reg_addr = 0x84c8,
};
struct reg_info pipe3_reg_2 = {
	.reg_block_name = "pipe3",
	.reg_mmio_addr = 0x84c8,
	.reg_sub_index = 0x2,
	.field_num = 11,
	.reg_in_bytes = 4,
};
struct reg_field pipe3_reg_field_18 = {
	.name = "Reserved_4",
	.bits_num = 8,
	.shift = 0,
	.reg_addr = 0x84cc,
};
struct reg_field pipe3_reg_field_19 = {
	.name = "Ovl1_Plane_Alpha",
	.bits_num = 8,
	.shift = 8,
	.reg_addr = 0x84cc,
};
struct reg_field pipe3_reg_field_20 = {
	.name = "Ovl1_Inv_Alpha",
	.bits_num = 1,
	.shift = 16,
	.reg_addr = 0x84cc,
};
struct reg_field pipe3_reg_field_21 = {
	.name = "Ovl1_Alpha_Blend_Mode",
	.bits_num = 1,
	.shift = 17,
	.reg_addr = 0x84cc,
};
struct reg_field pipe3_reg_field_22 = {
	.name = "Reserved_3",
	.bits_num = 2,
	.shift = 18,
	.reg_addr = 0x84cc,
};
struct reg_field pipe3_reg_field_23 = {
	.name = "Ovl1_Plb_Fct",
	.bits_num = 4,
	.shift = 20,
	.reg_addr = 0x84cc,
};
struct reg_field pipe3_reg_field_24 = {
	.name = "Ovl1_Pla_Fct",
	.bits_num = 4,
	.shift = 24,
	.reg_addr = 0x84cc,
};
struct reg_field pipe3_reg_field_25 = {
	.name = "Ovl1_Key_Mode",
	.bits_num = 4,
	.shift = 28,
	.reg_addr = 0x84cc,
};
struct reg_info pipe3_reg_3 = {
	.reg_block_name = "pipe3",
	.reg_mmio_addr = 0x84cc,
	.reg_sub_index = 0x3,
	.field_num = 8,
	.reg_in_bytes = 4,
};
struct reg_field pipe3_reg_field_26 = {
	.name = "Pus_Height_Dst",
	.bits_num = 12,
	.shift = 0,
	.reg_addr = 0x84d0,
};
struct reg_field pipe3_reg_field_27 = {
	.name = "Pus_Width_Dst",
	.bits_num = 13,
	.shift = 12,
	.reg_addr = 0x84d0,
};
struct reg_field pipe3_reg_field_28 = {
	.name = "Reserved_1",
	.bits_num = 3,
	.shift = 25,
	.reg_addr = 0x84d0,
};
struct reg_field pipe3_reg_field_29 = {
	.name = "Pus_Cos2tap",
	.bits_num = 1,
	.shift = 28,
	.reg_addr = 0x84d0,
};
struct reg_field pipe3_reg_field_30 = {
	.name = "Pus_Ven",
	.bits_num = 1,
	.shift = 29,
	.reg_addr = 0x84d0,
};
struct reg_field pipe3_reg_field_31 = {
	.name = "Pus_Hen",
	.bits_num = 1,
	.shift = 30,
	.reg_addr = 0x84d0,
};
struct reg_field pipe3_reg_field_32 = {
	.name = "Pus_En",
	.bits_num = 1,
	.shift = 31,
	.reg_addr = 0x84d0,
};
struct reg_info pipe3_reg_4 = {
	.reg_block_name = "pipe3",
	.reg_mmio_addr = 0x84d0,
	.reg_sub_index = 0x4,
	.field_num = 7,
	.reg_in_bytes = 4,
};
struct reg_field pipe3_reg_field_33 = {
	.name = "Pus_Ratio_V",
	.bits_num = 20,
	.shift = 0,
	.reg_addr = 0x84d4,
};
struct reg_field pipe3_reg_field_34 = {
	.name = "Pus_Vsync_Dlyval",
	.bits_num = 6,
	.shift = 20,
	.reg_addr = 0x84d4,
};
struct reg_field pipe3_reg_field_35 = {
	.name = "Reserved_2",
	.bits_num = 2,
	.shift = 26,
	.reg_addr = 0x84d4,
};
struct reg_field pipe3_reg_field_36 = {
	.name = "Pus_Ratio_Plus",
	.bits_num = 1,
	.shift = 28,
	.reg_addr = 0x84d4,
};
struct reg_field pipe3_reg_field_37 = {
	.name = "Pus_Ratio_Mode",
	.bits_num = 1,
	.shift = 29,
	.reg_addr = 0x84d4,
};
struct reg_field pipe3_reg_field_38 = {
	.name = "Reserved_1",
	.bits_num = 2,
	.shift = 30,
	.reg_addr = 0x84d4,
};
struct reg_info pipe3_reg_5 = {
	.reg_block_name = "pipe3",
	.reg_mmio_addr = 0x84d4,
	.reg_sub_index = 0x5,
	.field_num = 6,
	.reg_in_bytes = 4,
};
struct reg_field pipe3_reg_field_39 = {
	.name = "Pus_Ratio_H",
	.bits_num = 20,
	.shift = 0,
	.reg_addr = 0x84d8,
};
struct reg_field pipe3_reg_field_40 = {
	.name = "Pus_Hsync_Dlyval",
	.bits_num = 8,
	.shift = 20,
	.reg_addr = 0x84d8,
};
struct reg_field pipe3_reg_field_41 = {
	.name = "Reserved_1",
	.bits_num = 4,
	.shift = 28,
	.reg_addr = 0x84d8,
};
struct reg_info pipe3_reg_6 = {
	.reg_block_name = "pipe3",
	.reg_mmio_addr = 0x84d8,
	.reg_sub_index = 0x6,
	.field_num = 3,
	.reg_in_bytes = 4,
};
struct reg_field pipe3_reg_field_42 = {
	.name = "Outcsc_Coef_F1",
	.bits_num = 14,
	.shift = 0,
	.reg_addr = 0x84dc,
};
struct reg_field pipe3_reg_field_43 = {
	.name = "Reserved_1",
	.bits_num = 1,
	.shift = 14,
	.reg_addr = 0x84dc,
};
struct reg_field pipe3_reg_field_44 = {
	.name = "Outcsc_Bypass",
	.bits_num = 1,
	.shift = 15,
	.reg_addr = 0x84dc,
};
struct reg_field pipe3_reg_field_45 = {
	.name = "Outcsc_Bright",
	.bits_num = 9,
	.shift = 16,
	.reg_addr = 0x84dc,
};
struct reg_field pipe3_reg_field_46 = {
	.name = "Outcsc_Prog",
	.bits_num = 1,
	.shift = 25,
	.reg_addr = 0x84dc,
};
struct reg_field pipe3_reg_field_47 = {
	.name = "Outcsc_Dout_Fmt",
	.bits_num = 3,
	.shift = 26,
	.reg_addr = 0x84dc,
};
struct reg_field pipe3_reg_field_48 = {
	.name = "Outcsc_Din_Fmt",
	.bits_num = 3,
	.shift = 29,
	.reg_addr = 0x84dc,
};
struct reg_info pipe3_reg_7 = {
	.reg_block_name = "pipe3",
	.reg_mmio_addr = 0x84dc,
	.reg_sub_index = 0x7,
	.field_num = 7,
	.reg_in_bytes = 4,
};
struct reg_field pipe3_reg_field_49 = {
	.name = "Outcsc_Coef_F3",
	.bits_num = 14,
	.shift = 0,
	.reg_addr = 0x84e0,
};
struct reg_field pipe3_reg_field_50 = {
	.name = "Reserved_2",
	.bits_num = 2,
	.shift = 14,
	.reg_addr = 0x84e0,
};
struct reg_field pipe3_reg_field_51 = {
	.name = "Outcsc_Coef_F2",
	.bits_num = 14,
	.shift = 16,
	.reg_addr = 0x84e0,
};
struct reg_field pipe3_reg_field_52 = {
	.name = "Reserved_1",
	.bits_num = 2,
	.shift = 30,
	.reg_addr = 0x84e0,
};
struct reg_info pipe3_reg_8 = {
	.reg_block_name = "pipe3",
	.reg_mmio_addr = 0x84e0,
	.reg_sub_index = 0x8,
	.field_num = 4,
	.reg_in_bytes = 4,
};
struct reg_field pipe3_reg_field_53 = {
	.name = "Outcsc_Coef_F5",
	.bits_num = 14,
	.shift = 0,
	.reg_addr = 0x84e4,
};
struct reg_field pipe3_reg_field_54 = {
	.name = "Reserved_2",
	.bits_num = 2,
	.shift = 14,
	.reg_addr = 0x84e4,
};
struct reg_field pipe3_reg_field_55 = {
	.name = "Outcsc_Coef_F4",
	.bits_num = 14,
	.shift = 16,
	.reg_addr = 0x84e4,
};
struct reg_field pipe3_reg_field_56 = {
	.name = "Reserved_1",
	.bits_num = 2,
	.shift = 30,
	.reg_addr = 0x84e4,
};
struct reg_info pipe3_reg_9 = {
	.reg_block_name = "pipe3",
	.reg_mmio_addr = 0x84e4,
	.reg_sub_index = 0x9,
	.field_num = 4,
	.reg_in_bytes = 4,
};
struct reg_field pipe3_reg_field_57 = {
	.name = "Outcsc_Coef_F7",
	.bits_num = 14,
	.shift = 0,
	.reg_addr = 0x84e8,
};
struct reg_field pipe3_reg_field_58 = {
	.name = "Reserved_2",
	.bits_num = 2,
	.shift = 14,
	.reg_addr = 0x84e8,
};
struct reg_field pipe3_reg_field_59 = {
	.name = "Outcsc_Coef_F6",
	.bits_num = 14,
	.shift = 16,
	.reg_addr = 0x84e8,
};
struct reg_field pipe3_reg_field_60 = {
	.name = "Reserved_1",
	.bits_num = 2,
	.shift = 30,
	.reg_addr = 0x84e8,
};
struct reg_info pipe3_reg_10 = {
	.reg_block_name = "pipe3",
	.reg_mmio_addr = 0x84e8,
	.reg_sub_index = 0xa,
	.field_num = 4,
	.reg_in_bytes = 4,
};
struct reg_field pipe3_reg_field_61 = {
	.name = "Outcsc_Coef_F9",
	.bits_num = 14,
	.shift = 0,
	.reg_addr = 0x84ec,
};
struct reg_field pipe3_reg_field_62 = {
	.name = "Reserved_2",
	.bits_num = 2,
	.shift = 14,
	.reg_addr = 0x84ec,
};
struct reg_field pipe3_reg_field_63 = {
	.name = "Outcsc_Coef_F8",
	.bits_num = 14,
	.shift = 16,
	.reg_addr = 0x84ec,
};
struct reg_field pipe3_reg_field_64 = {
	.name = "Reserved_1",
	.bits_num = 2,
	.shift = 30,
	.reg_addr = 0x84ec,
};
struct reg_info pipe3_reg_11 = {
	.reg_block_name = "pipe3",
	.reg_mmio_addr = 0x84ec,
	.reg_sub_index = 0xb,
	.field_num = 4,
	.reg_in_bytes = 4,
};
struct reg_field pipe3_reg_field_65 = {
	.name = "Reserved_2",
	.bits_num = 26,
	.shift = 0,
	.reg_addr = 0x84f0,
};
struct reg_field pipe3_reg_field_66 = {
	.name = "Dither_Dist_En",
	.bits_num = 1,
	.shift = 26,
	.reg_addr = 0x84f0,
};
struct reg_field pipe3_reg_field_67 = {
	.name = "Dither_Bitsel",
	.bits_num = 1,
	.shift = 27,
	.reg_addr = 0x84f0,
};
struct reg_field pipe3_reg_field_68 = {
	.name = "Dither_Base",
	.bits_num = 3,
	.shift = 28,
	.reg_addr = 0x84f0,
};
struct reg_field pipe3_reg_field_69 = {
	.name = "Dither_En",
	.bits_num = 1,
	.shift = 31,
	.reg_addr = 0x84f0,
};
struct reg_info pipe3_reg_12 = {
	.reg_block_name = "pipe3",
	.reg_mmio_addr = 0x84f0,
	.reg_sub_index = 0xc,
	.field_num = 5,
	.reg_in_bytes = 4,
};
struct reg_info * pipe3_reg_info[13] = {
&pipe3_reg_0,
&pipe3_reg_1,
&pipe3_reg_2,
&pipe3_reg_3,
&pipe3_reg_4,
&pipe3_reg_5,
&pipe3_reg_6,
&pipe3_reg_7,
&pipe3_reg_8,
&pipe3_reg_9,
&pipe3_reg_10,
&pipe3_reg_11,
&pipe3_reg_12,
};
struct reg_field * pipe3_reg_field_info[70] = {
&pipe3_reg_field_0,
&pipe3_reg_field_1,
&pipe3_reg_field_2,
&pipe3_reg_field_3,
&pipe3_reg_field_4,
&pipe3_reg_field_5,
&pipe3_reg_field_6,
&pipe3_reg_field_7,
&pipe3_reg_field_8,
&pipe3_reg_field_9,
&pipe3_reg_field_10,
&pipe3_reg_field_11,
&pipe3_reg_field_12,
&pipe3_reg_field_13,
&pipe3_reg_field_14,
&pipe3_reg_field_15,
&pipe3_reg_field_16,
&pipe3_reg_field_17,
&pipe3_reg_field_18,
&pipe3_reg_field_19,
&pipe3_reg_field_20,
&pipe3_reg_field_21,
&pipe3_reg_field_22,
&pipe3_reg_field_23,
&pipe3_reg_field_24,
&pipe3_reg_field_25,
&pipe3_reg_field_26,
&pipe3_reg_field_27,
&pipe3_reg_field_28,
&pipe3_reg_field_29,
&pipe3_reg_field_30,
&pipe3_reg_field_31,
&pipe3_reg_field_32,
&pipe3_reg_field_33,
&pipe3_reg_field_34,
&pipe3_reg_field_35,
&pipe3_reg_field_36,
&pipe3_reg_field_37,
&pipe3_reg_field_38,
&pipe3_reg_field_39,
&pipe3_reg_field_40,
&pipe3_reg_field_41,
&pipe3_reg_field_42,
&pipe3_reg_field_43,
&pipe3_reg_field_44,
&pipe3_reg_field_45,
&pipe3_reg_field_46,
&pipe3_reg_field_47,
&pipe3_reg_field_48,
&pipe3_reg_field_49,
&pipe3_reg_field_50,
&pipe3_reg_field_51,
&pipe3_reg_field_52,
&pipe3_reg_field_53,
&pipe3_reg_field_54,
&pipe3_reg_field_55,
&pipe3_reg_field_56,
&pipe3_reg_field_57,
&pipe3_reg_field_58,
&pipe3_reg_field_59,
&pipe3_reg_field_60,
&pipe3_reg_field_61,
&pipe3_reg_field_62,
&pipe3_reg_field_63,
&pipe3_reg_field_64,
&pipe3_reg_field_65,
&pipe3_reg_field_66,
&pipe3_reg_field_67,
&pipe3_reg_field_68,
&pipe3_reg_field_69,
};
unsigned int pipe3_reg_count = 13;
unsigned int pipe3_reg_start = 0x84c0;
unsigned int pipe3_reg_end = 0x84f0;
unsigned int pipe3_reg_in_bytes = 0x4;
unsigned int pipe3_reg_total_field_count = 70;
char * pipe3_reg_block_name = "pipe3";
