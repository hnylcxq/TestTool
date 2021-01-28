#include "../reg.h"

struct reg_field itg2_reg_field_0 = {
	.name = "Reserved_1",
	.bits_num = 22,
	.shift = 0,
	.reg_addr = 0x81c0,
};
struct reg_field itg2_reg_field_1 = {
	.name = "Sw_Flip_Pipe_Dither",
	.bits_num = 1,
	.shift = 22,
	.reg_addr = 0x81c0,
};
struct reg_field itg2_reg_field_2 = {
	.name = "Sw_Flip_Pipe_Ocsc",
	.bits_num = 1,
	.shift = 23,
	.reg_addr = 0x81c0,
};
struct reg_field itg2_reg_field_3 = {
	.name = "Sw_Flip_Pipe_Pus",
	.bits_num = 1,
	.shift = 24,
	.reg_addr = 0x81c0,
};
struct reg_field itg2_reg_field_4 = {
	.name = "Sw_Flip_Pipe_Lut",
	.bits_num = 1,
	.shift = 25,
	.reg_addr = 0x81c0,
};
struct reg_field itg2_reg_field_5 = {
	.name = "Sw_Flip_Pipe_Ovl1",
	.bits_num = 1,
	.shift = 26,
	.reg_addr = 0x81c0,
};
struct reg_field itg2_reg_field_6 = {
	.name = "Sw_Flip_Pipe_Ovl0",
	.bits_num = 1,
	.shift = 27,
	.reg_addr = 0x81c0,
};
struct reg_field itg2_reg_field_7 = {
	.name = "Sw_Flip_Itg_Cur",
	.bits_num = 1,
	.shift = 28,
	.reg_addr = 0x81c0,
};
struct reg_field itg2_reg_field_8 = {
	.name = "Sw_Flip_Itg_Spl1",
	.bits_num = 1,
	.shift = 29,
	.reg_addr = 0x81c0,
};
struct reg_field itg2_reg_field_9 = {
	.name = "Sw_Flip_Itg_Spl0",
	.bits_num = 1,
	.shift = 30,
	.reg_addr = 0x81c0,
};
struct reg_field itg2_reg_field_10 = {
	.name = "Sw_Itg_Flip_En",
	.bits_num = 1,
	.shift = 31,
	.reg_addr = 0x81c0,
};
struct reg_info itg2_reg_0 = {
	.reg_block_name = "itg2",
	.reg_mmio_addr = 0x81c0,
	.reg_sub_index = 0x0,
	.field_num = 11,
	.reg_in_bytes = 4,
};
struct reg_field itg2_reg_field_11 = {
	.name = "Req_Pre_4l",
	.bits_num = 1,
	.shift = 0,
	.reg_addr = 0x81c4,
};
struct reg_field itg2_reg_field_12 = {
	.name = "Reserved_1",
	.bits_num = 31,
	.shift = 1,
	.reg_addr = 0x81c4,
};
struct reg_info itg2_reg_1 = {
	.reg_block_name = "itg2",
	.reg_mmio_addr = 0x81c4,
	.reg_sub_index = 0x1,
	.field_num = 2,
	.reg_in_bytes = 4,
};
struct reg_field itg2_reg_field_13 = {
	.name = "Cur_Ref_Iwin",
	.bits_num = 1,
	.shift = 0,
	.reg_addr = 0x81c8,
};
struct reg_field itg2_reg_field_14 = {
	.name = "Spl_Ref_Iwin",
	.bits_num = 1,
	.shift = 1,
	.reg_addr = 0x81c8,
};
struct reg_field itg2_reg_field_15 = {
	.name = "Reserved_1",
	.bits_num = 30,
	.shift = 2,
	.reg_addr = 0x81c8,
};
struct reg_info itg2_reg_2 = {
	.reg_block_name = "itg2",
	.reg_mmio_addr = 0x81c8,
	.reg_sub_index = 0x2,
	.field_num = 3,
	.reg_in_bytes = 4,
};
struct reg_field itg2_reg_field_16 = {
	.name = "Spl_Stride",
	.bits_num = 12,
	.shift = 0,
	.reg_addr = 0x81cc,
};
struct reg_field itg2_reg_field_17 = {
	.name = "Spl_Fb",
	.bits_num = 1,
	.shift = 12,
	.reg_addr = 0x81cc,
};
struct reg_field itg2_reg_field_18 = {
	.name = "Spl_Vir",
	.bits_num = 1,
	.shift = 13,
	.reg_addr = 0x81cc,
};
struct reg_field itg2_reg_field_19 = {
	.name = "Spl_Snoop",
	.bits_num = 1,
	.shift = 14,
	.reg_addr = 0x81cc,
};
struct reg_field itg2_reg_field_20 = {
	.name = "Spl_Pxl_Off",
	.bits_num = 5,
	.shift = 15,
	.reg_addr = 0x81cc,
};
struct reg_field itg2_reg_field_21 = {
	.name = "Spl_Share_Lb",
	.bits_num = 1,
	.shift = 20,
	.reg_addr = 0x81cc,
};
struct reg_field itg2_reg_field_22 = {
	.name = "Spl_Crycb",
	.bits_num = 1,
	.shift = 21,
	.reg_addr = 0x81cc,
};
struct reg_field itg2_reg_field_23 = {
	.name = "Spl_Cbycry",
	.bits_num = 1,
	.shift = 22,
	.reg_addr = 0x81cc,
};
struct reg_field itg2_reg_field_24 = {
	.name = "Spl_Abgr",
	.bits_num = 1,
	.shift = 23,
	.reg_addr = 0x81cc,
};
struct reg_field itg2_reg_field_25 = {
	.name = "Spl_Fmt",
	.bits_num = 4,
	.shift = 24,
	.reg_addr = 0x81cc,
};
struct reg_field itg2_reg_field_26 = {
	.name = "Spl_Rlen",
	.bits_num = 2,
	.shift = 28,
	.reg_addr = 0x81cc,
};
struct reg_field itg2_reg_field_27 = {
	.name = "Spl_Sec",
	.bits_num = 1,
	.shift = 30,
	.reg_addr = 0x81cc,
};
struct reg_field itg2_reg_field_28 = {
	.name = "Spl_En",
	.bits_num = 1,
	.shift = 31,
	.reg_addr = 0x81cc,
};
struct reg_info itg2_reg_3 = {
	.reg_block_name = "itg2",
	.reg_mmio_addr = 0x81cc,
	.reg_sub_index = 0x3,
	.field_num = 13,
	.reg_in_bytes = 4,
};
struct reg_field itg2_reg_field_29 = {
	.name = "Spl_Comp_Type",
	.bits_num = 6,
	.shift = 0,
	.reg_addr = 0x81d0,
};
struct reg_field itg2_reg_field_30 = {
	.name = "Reserved_2",
	.bits_num = 2,
	.shift = 6,
	.reg_addr = 0x81d0,
};
struct reg_field itg2_reg_field_31 = {
	.name = "Spl_Comp_En",
	.bits_num = 1,
	.shift = 8,
	.reg_addr = 0x81d0,
};
struct reg_field itg2_reg_field_32 = {
	.name = "Reserved_1",
	.bits_num = 23,
	.shift = 9,
	.reg_addr = 0x81d0,
};
struct reg_info itg2_reg_4 = {
	.reg_block_name = "itg2",
	.reg_mmio_addr = 0x81d0,
	.reg_sub_index = 0x4,
	.field_num = 4,
	.reg_in_bytes = 4,
};
struct reg_field itg2_reg_field_33 = {
	.name = "Spl_Ystart",
	.bits_num = 13,
	.shift = 0,
	.reg_addr = 0x81d4,
};
struct reg_field itg2_reg_field_34 = {
	.name = "Reserved_2",
	.bits_num = 3,
	.shift = 13,
	.reg_addr = 0x81d4,
};
struct reg_field itg2_reg_field_35 = {
	.name = "Spl_Xstart",
	.bits_num = 14,
	.shift = 16,
	.reg_addr = 0x81d4,
};
struct reg_field itg2_reg_field_36 = {
	.name = "Reserved_1",
	.bits_num = 2,
	.shift = 30,
	.reg_addr = 0x81d4,
};
struct reg_info itg2_reg_5 = {
	.reg_block_name = "itg2",
	.reg_mmio_addr = 0x81d4,
	.reg_sub_index = 0x5,
	.field_num = 4,
	.reg_in_bytes = 4,
};
struct reg_field itg2_reg_field_37 = {
	.name = "Spl_Src_H",
	.bits_num = 13,
	.shift = 0,
	.reg_addr = 0x81d8,
};
struct reg_field itg2_reg_field_38 = {
	.name = "Reserved_2",
	.bits_num = 3,
	.shift = 13,
	.reg_addr = 0x81d8,
};
struct reg_field itg2_reg_field_39 = {
	.name = "Spl_Src_W",
	.bits_num = 14,
	.shift = 16,
	.reg_addr = 0x81d8,
};
struct reg_field itg2_reg_field_40 = {
	.name = "Reserved_1",
	.bits_num = 2,
	.shift = 30,
	.reg_addr = 0x81d8,
};
struct reg_info itg2_reg_6 = {
	.reg_block_name = "itg2",
	.reg_mmio_addr = 0x81d8,
	.reg_sub_index = 0x6,
	.field_num = 4,
	.reg_in_bytes = 4,
};
struct reg_field itg2_reg_field_41 = {
	.name = "Spl_Dst_H",
	.bits_num = 13,
	.shift = 0,
	.reg_addr = 0x81dc,
};
struct reg_field itg2_reg_field_42 = {
	.name = "Reserved_2",
	.bits_num = 3,
	.shift = 13,
	.reg_addr = 0x81dc,
};
struct reg_field itg2_reg_field_43 = {
	.name = "Spl_Dst_W",
	.bits_num = 14,
	.shift = 16,
	.reg_addr = 0x81dc,
};
struct reg_field itg2_reg_field_44 = {
	.name = "Reserved_1",
	.bits_num = 2,
	.shift = 30,
	.reg_addr = 0x81dc,
};
struct reg_info itg2_reg_7 = {
	.reg_block_name = "itg2",
	.reg_mmio_addr = 0x81dc,
	.reg_sub_index = 0x7,
	.field_num = 4,
	.reg_in_bytes = 4,
};
struct reg_field itg2_reg_field_45 = {
	.name = "Spl1_Hacc",
	.bits_num = 21,
	.shift = 0,
	.reg_addr = 0x81e0,
};
struct reg_field itg2_reg_field_46 = {
	.name = "Reserved_1",
	.bits_num = 9,
	.shift = 21,
	.reg_addr = 0x81e0,
};
struct reg_field itg2_reg_field_47 = {
	.name = "Spl_Vtap",
	.bits_num = 1,
	.shift = 30,
	.reg_addr = 0x81e0,
};
struct reg_field itg2_reg_field_48 = {
	.name = "Spl_Htap",
	.bits_num = 1,
	.shift = 31,
	.reg_addr = 0x81e0,
};
struct reg_info itg2_reg_8 = {
	.reg_block_name = "itg2",
	.reg_mmio_addr = 0x81e0,
	.reg_sub_index = 0x8,
	.field_num = 4,
	.reg_in_bytes = 4,
};
struct reg_field itg2_reg_field_49 = {
	.name = "Spl_Vacc",
	.bits_num = 21,
	.shift = 0,
	.reg_addr = 0x81e4,
};
struct reg_field itg2_reg_field_50 = {
	.name = "Reserved_1",
	.bits_num = 9,
	.shift = 21,
	.reg_addr = 0x81e4,
};
struct reg_field itg2_reg_field_51 = {
	.name = "Spl_Alpha_Ups",
	.bits_num = 1,
	.shift = 30,
	.reg_addr = 0x81e4,
};
struct reg_field itg2_reg_field_52 = {
	.name = "Spl_Vdup",
	.bits_num = 1,
	.shift = 31,
	.reg_addr = 0x81e4,
};
struct reg_info itg2_reg_9 = {
	.reg_block_name = "itg2",
	.reg_mmio_addr = 0x81e4,
	.reg_sub_index = 0x9,
	.field_num = 4,
	.reg_in_bytes = 4,
};
struct reg_field itg2_reg_field_53 = {
	.name = "Spl_Base_Adr",
	.bits_num = 31,
	.shift = 0,
	.reg_addr = 0x81e8,
};
struct reg_field itg2_reg_field_54 = {
	.name = "Reserved_1",
	.bits_num = 1,
	.shift = 31,
	.reg_addr = 0x81e8,
};
struct reg_info itg2_reg_10 = {
	.reg_block_name = "itg2",
	.reg_mmio_addr = 0x81e8,
	.reg_sub_index = 0xa,
	.field_num = 2,
	.reg_in_bytes = 4,
};
struct reg_field itg2_reg_field_55 = {
	.name = "Spl_Base_Off",
	.bits_num = 31,
	.shift = 0,
	.reg_addr = 0x81ec,
};
struct reg_field itg2_reg_field_56 = {
	.name = "Reserved_1",
	.bits_num = 1,
	.shift = 31,
	.reg_addr = 0x81ec,
};
struct reg_info itg2_reg_11 = {
	.reg_block_name = "itg2",
	.reg_mmio_addr = 0x81ec,
	.reg_sub_index = 0xb,
	.field_num = 2,
	.reg_in_bytes = 4,
};
struct reg_field itg2_reg_field_57 = {
	.name = "Spl_Bl_Idx",
	.bits_num = 18,
	.shift = 0,
	.reg_addr = 0x81f0,
};
struct reg_field itg2_reg_field_58 = {
	.name = "Reserved_1",
	.bits_num = 14,
	.shift = 18,
	.reg_addr = 0x81f0,
};
struct reg_info itg2_reg_12 = {
	.reg_block_name = "itg2",
	.reg_mmio_addr = 0x81f0,
	.reg_sub_index = 0xc,
	.field_num = 2,
	.reg_in_bytes = 4,
};
struct reg_field itg2_reg_field_59 = {
	.name = "Spl_Keyl",
	.bits_num = 30,
	.shift = 0,
	.reg_addr = 0x81f4,
};
struct reg_field itg2_reg_field_60 = {
	.name = "Reserved_1",
	.bits_num = 2,
	.shift = 30,
	.reg_addr = 0x81f4,
};
struct reg_info itg2_reg_13 = {
	.reg_block_name = "itg2",
	.reg_mmio_addr = 0x81f4,
	.reg_sub_index = 0xd,
	.field_num = 2,
	.reg_in_bytes = 4,
};
struct reg_field itg2_reg_field_61 = {
	.name = "Spl_Keyh",
	.bits_num = 30,
	.shift = 0,
	.reg_addr = 0x81f8,
};
struct reg_field itg2_reg_field_62 = {
	.name = "Reserved_1",
	.bits_num = 2,
	.shift = 30,
	.reg_addr = 0x81f8,
};
struct reg_info itg2_reg_14 = {
	.reg_block_name = "itg2",
	.reg_mmio_addr = 0x81f8,
	.reg_sub_index = 0xe,
	.field_num = 2,
	.reg_in_bytes = 4,
};
struct reg_field itg2_reg_field_63 = {
	.name = "Spl_Csc_Bright",
	.bits_num = 9,
	.shift = 0,
	.reg_addr = 0x81fc,
};
struct reg_field itg2_reg_field_64 = {
	.name = "Reserved_4",
	.bits_num = 11,
	.shift = 9,
	.reg_addr = 0x81fc,
};
struct reg_field itg2_reg_field_65 = {
	.name = "Spl_Csc_Bypass",
	.bits_num = 1,
	.shift = 20,
	.reg_addr = 0x81fc,
};
struct reg_field itg2_reg_field_66 = {
	.name = "Spl_Csc_Prog",
	.bits_num = 1,
	.shift = 21,
	.reg_addr = 0x81fc,
};
struct reg_field itg2_reg_field_67 = {
	.name = "Reserved_3",
	.bits_num = 2,
	.shift = 22,
	.reg_addr = 0x81fc,
};
struct reg_field itg2_reg_field_68 = {
	.name = "Spl_Csc_Outfmt",
	.bits_num = 3,
	.shift = 24,
	.reg_addr = 0x81fc,
};
struct reg_field itg2_reg_field_69 = {
	.name = "Reserved_2",
	.bits_num = 1,
	.shift = 27,
	.reg_addr = 0x81fc,
};
struct reg_field itg2_reg_field_70 = {
	.name = "Spl_Csc_Infmt",
	.bits_num = 3,
	.shift = 28,
	.reg_addr = 0x81fc,
};
struct reg_field itg2_reg_field_71 = {
	.name = "Reserved_1",
	.bits_num = 1,
	.shift = 31,
	.reg_addr = 0x81fc,
};
struct reg_info itg2_reg_15 = {
	.reg_block_name = "itg2",
	.reg_mmio_addr = 0x81fc,
	.reg_sub_index = 0xf,
	.field_num = 9,
	.reg_in_bytes = 4,
};
struct reg_field itg2_reg_field_72 = {
	.name = "Spl_Csc_Coef2",
	.bits_num = 14,
	.shift = 0,
	.reg_addr = 0x8200,
};
struct reg_field itg2_reg_field_73 = {
	.name = "Reserved_2",
	.bits_num = 2,
	.shift = 14,
	.reg_addr = 0x8200,
};
struct reg_field itg2_reg_field_74 = {
	.name = "Spl_Csc_Coef1",
	.bits_num = 14,
	.shift = 16,
	.reg_addr = 0x8200,
};
struct reg_field itg2_reg_field_75 = {
	.name = "Reserved_1",
	.bits_num = 2,
	.shift = 30,
	.reg_addr = 0x8200,
};
struct reg_info itg2_reg_16 = {
	.reg_block_name = "itg2",
	.reg_mmio_addr = 0x8200,
	.reg_sub_index = 0x10,
	.field_num = 4,
	.reg_in_bytes = 4,
};
struct reg_field itg2_reg_field_76 = {
	.name = "Spl_Csc_Coef4",
	.bits_num = 14,
	.shift = 0,
	.reg_addr = 0x8204,
};
struct reg_field itg2_reg_field_77 = {
	.name = "Reserved_2",
	.bits_num = 2,
	.shift = 14,
	.reg_addr = 0x8204,
};
struct reg_field itg2_reg_field_78 = {
	.name = "Spl_Csc_Coef3",
	.bits_num = 14,
	.shift = 16,
	.reg_addr = 0x8204,
};
struct reg_field itg2_reg_field_79 = {
	.name = "Reserved_1",
	.bits_num = 2,
	.shift = 30,
	.reg_addr = 0x8204,
};
struct reg_info itg2_reg_17 = {
	.reg_block_name = "itg2",
	.reg_mmio_addr = 0x8204,
	.reg_sub_index = 0x11,
	.field_num = 4,
	.reg_in_bytes = 4,
};
struct reg_field itg2_reg_field_80 = {
	.name = "Spl_Csc_Coef6",
	.bits_num = 14,
	.shift = 0,
	.reg_addr = 0x8208,
};
struct reg_field itg2_reg_field_81 = {
	.name = "Reserved_2",
	.bits_num = 2,
	.shift = 14,
	.reg_addr = 0x8208,
};
struct reg_field itg2_reg_field_82 = {
	.name = "Spl_Csc_Coef5",
	.bits_num = 14,
	.shift = 16,
	.reg_addr = 0x8208,
};
struct reg_field itg2_reg_field_83 = {
	.name = "Reserved_1",
	.bits_num = 2,
	.shift = 30,
	.reg_addr = 0x8208,
};
struct reg_info itg2_reg_18 = {
	.reg_block_name = "itg2",
	.reg_mmio_addr = 0x8208,
	.reg_sub_index = 0x12,
	.field_num = 4,
	.reg_in_bytes = 4,
};
struct reg_field itg2_reg_field_84 = {
	.name = "Spl_Csc_Coef8",
	.bits_num = 14,
	.shift = 0,
	.reg_addr = 0x820c,
};
struct reg_field itg2_reg_field_85 = {
	.name = "Reserved_2",
	.bits_num = 2,
	.shift = 14,
	.reg_addr = 0x820c,
};
struct reg_field itg2_reg_field_86 = {
	.name = "Spl_Csc_Coef7",
	.bits_num = 14,
	.shift = 16,
	.reg_addr = 0x820c,
};
struct reg_field itg2_reg_field_87 = {
	.name = "Reserved_1",
	.bits_num = 2,
	.shift = 30,
	.reg_addr = 0x820c,
};
struct reg_info itg2_reg_19 = {
	.reg_block_name = "itg2",
	.reg_mmio_addr = 0x820c,
	.reg_sub_index = 0x13,
	.field_num = 4,
	.reg_in_bytes = 4,
};
struct reg_field itg2_reg_field_88 = {
	.name = "Spl_Csc_Coef9",
	.bits_num = 30,
	.shift = 0,
	.reg_addr = 0x8210,
};
struct reg_field itg2_reg_field_89 = {
	.name = "Reserved_1",
	.bits_num = 2,
	.shift = 30,
	.reg_addr = 0x8210,
};
struct reg_info itg2_reg_20 = {
	.reg_block_name = "itg2",
	.reg_mmio_addr = 0x8210,
	.reg_sub_index = 0x14,
	.field_num = 2,
	.reg_in_bytes = 4,
};
struct reg_field itg2_reg_field_90 = {
	.name = "Cur_Yoffset",
	.bits_num = 7,
	.shift = 0,
	.reg_addr = 0x8214,
};
struct reg_field itg2_reg_field_91 = {
	.name = "Reserved_4",
	.bits_num = 1,
	.shift = 7,
	.reg_addr = 0x8214,
};
struct reg_field itg2_reg_field_92 = {
	.name = "Cur_Xoffset",
	.bits_num = 7,
	.shift = 8,
	.reg_addr = 0x8214,
};
struct reg_field itg2_reg_field_93 = {
	.name = "Reserved_3",
	.bits_num = 1,
	.shift = 15,
	.reg_addr = 0x8214,
};
struct reg_field itg2_reg_field_94 = {
	.name = "Cur_Fb",
	.bits_num = 1,
	.shift = 16,
	.reg_addr = 0x8214,
};
struct reg_field itg2_reg_field_95 = {
	.name = "Cur_Vir",
	.bits_num = 1,
	.shift = 17,
	.reg_addr = 0x8214,
};
struct reg_field itg2_reg_field_96 = {
	.name = "Cur_Snoop",
	.bits_num = 1,
	.shift = 18,
	.reg_addr = 0x8214,
};
struct reg_field itg2_reg_field_97 = {
	.name = "Reserved_2",
	.bits_num = 5,
	.shift = 19,
	.reg_addr = 0x8214,
};
struct reg_field itg2_reg_field_98 = {
	.name = "Cur_Size",
	.bits_num = 2,
	.shift = 24,
	.reg_addr = 0x8214,
};
struct reg_field itg2_reg_field_99 = {
	.name = "Reserved_1",
	.bits_num = 2,
	.shift = 26,
	.reg_addr = 0x8214,
};
struct reg_field itg2_reg_field_100 = {
	.name = "Cur_Pos_Type",
	.bits_num = 1,
	.shift = 28,
	.reg_addr = 0x8214,
};
struct reg_field itg2_reg_field_101 = {
	.name = "Cur_Type",
	.bits_num = 2,
	.shift = 29,
	.reg_addr = 0x8214,
};
struct reg_field itg2_reg_field_102 = {
	.name = "Cur_En",
	.bits_num = 1,
	.shift = 31,
	.reg_addr = 0x8214,
};
struct reg_info itg2_reg_21 = {
	.reg_block_name = "itg2",
	.reg_mmio_addr = 0x8214,
	.reg_sub_index = 0x15,
	.field_num = 13,
	.reg_in_bytes = 4,
};
struct reg_field itg2_reg_field_103 = {
	.name = "Cur_Ystart",
	.bits_num = 13,
	.shift = 0,
	.reg_addr = 0x8218,
};
struct reg_field itg2_reg_field_104 = {
	.name = "Reserved_2",
	.bits_num = 3,
	.shift = 13,
	.reg_addr = 0x8218,
};
struct reg_field itg2_reg_field_105 = {
	.name = "Cur_Xstart",
	.bits_num = 14,
	.shift = 16,
	.reg_addr = 0x8218,
};
struct reg_field itg2_reg_field_106 = {
	.name = "Reserved_1",
	.bits_num = 2,
	.shift = 30,
	.reg_addr = 0x8218,
};
struct reg_info itg2_reg_22 = {
	.reg_block_name = "itg2",
	.reg_mmio_addr = 0x8218,
	.reg_sub_index = 0x16,
	.field_num = 4,
	.reg_in_bytes = 4,
};
struct reg_field itg2_reg_field_107 = {
	.name = "Cur_Base",
	.bits_num = 31,
	.shift = 0,
	.reg_addr = 0x821c,
};
struct reg_field itg2_reg_field_108 = {
	.name = "Reserved_1",
	.bits_num = 1,
	.shift = 31,
	.reg_addr = 0x821c,
};
struct reg_info itg2_reg_23 = {
	.reg_block_name = "itg2",
	.reg_mmio_addr = 0x821c,
	.reg_sub_index = 0x17,
	.field_num = 2,
	.reg_in_bytes = 4,
};
struct reg_field itg2_reg_field_109 = {
	.name = "Cur_Csc_Outfmt",
	.bits_num = 3,
	.shift = 0,
	.reg_addr = 0x8220,
};
struct reg_field itg2_reg_field_110 = {
	.name = "Reserved_1",
	.bits_num = 29,
	.shift = 3,
	.reg_addr = 0x8220,
};
struct reg_info itg2_reg_24 = {
	.reg_block_name = "itg2",
	.reg_mmio_addr = 0x8220,
	.reg_sub_index = 0x18,
	.field_num = 2,
	.reg_in_bytes = 4,
};
struct reg_info * itg2_reg_info[25] = {
&itg2_reg_0,
&itg2_reg_1,
&itg2_reg_2,
&itg2_reg_3,
&itg2_reg_4,
&itg2_reg_5,
&itg2_reg_6,
&itg2_reg_7,
&itg2_reg_8,
&itg2_reg_9,
&itg2_reg_10,
&itg2_reg_11,
&itg2_reg_12,
&itg2_reg_13,
&itg2_reg_14,
&itg2_reg_15,
&itg2_reg_16,
&itg2_reg_17,
&itg2_reg_18,
&itg2_reg_19,
&itg2_reg_20,
&itg2_reg_21,
&itg2_reg_22,
&itg2_reg_23,
&itg2_reg_24,
};
struct reg_field * itg2_reg_field_info[111] = {
&itg2_reg_field_0,
&itg2_reg_field_1,
&itg2_reg_field_2,
&itg2_reg_field_3,
&itg2_reg_field_4,
&itg2_reg_field_5,
&itg2_reg_field_6,
&itg2_reg_field_7,
&itg2_reg_field_8,
&itg2_reg_field_9,
&itg2_reg_field_10,
&itg2_reg_field_11,
&itg2_reg_field_12,
&itg2_reg_field_13,
&itg2_reg_field_14,
&itg2_reg_field_15,
&itg2_reg_field_16,
&itg2_reg_field_17,
&itg2_reg_field_18,
&itg2_reg_field_19,
&itg2_reg_field_20,
&itg2_reg_field_21,
&itg2_reg_field_22,
&itg2_reg_field_23,
&itg2_reg_field_24,
&itg2_reg_field_25,
&itg2_reg_field_26,
&itg2_reg_field_27,
&itg2_reg_field_28,
&itg2_reg_field_29,
&itg2_reg_field_30,
&itg2_reg_field_31,
&itg2_reg_field_32,
&itg2_reg_field_33,
&itg2_reg_field_34,
&itg2_reg_field_35,
&itg2_reg_field_36,
&itg2_reg_field_37,
&itg2_reg_field_38,
&itg2_reg_field_39,
&itg2_reg_field_40,
&itg2_reg_field_41,
&itg2_reg_field_42,
&itg2_reg_field_43,
&itg2_reg_field_44,
&itg2_reg_field_45,
&itg2_reg_field_46,
&itg2_reg_field_47,
&itg2_reg_field_48,
&itg2_reg_field_49,
&itg2_reg_field_50,
&itg2_reg_field_51,
&itg2_reg_field_52,
&itg2_reg_field_53,
&itg2_reg_field_54,
&itg2_reg_field_55,
&itg2_reg_field_56,
&itg2_reg_field_57,
&itg2_reg_field_58,
&itg2_reg_field_59,
&itg2_reg_field_60,
&itg2_reg_field_61,
&itg2_reg_field_62,
&itg2_reg_field_63,
&itg2_reg_field_64,
&itg2_reg_field_65,
&itg2_reg_field_66,
&itg2_reg_field_67,
&itg2_reg_field_68,
&itg2_reg_field_69,
&itg2_reg_field_70,
&itg2_reg_field_71,
&itg2_reg_field_72,
&itg2_reg_field_73,
&itg2_reg_field_74,
&itg2_reg_field_75,
&itg2_reg_field_76,
&itg2_reg_field_77,
&itg2_reg_field_78,
&itg2_reg_field_79,
&itg2_reg_field_80,
&itg2_reg_field_81,
&itg2_reg_field_82,
&itg2_reg_field_83,
&itg2_reg_field_84,
&itg2_reg_field_85,
&itg2_reg_field_86,
&itg2_reg_field_87,
&itg2_reg_field_88,
&itg2_reg_field_89,
&itg2_reg_field_90,
&itg2_reg_field_91,
&itg2_reg_field_92,
&itg2_reg_field_93,
&itg2_reg_field_94,
&itg2_reg_field_95,
&itg2_reg_field_96,
&itg2_reg_field_97,
&itg2_reg_field_98,
&itg2_reg_field_99,
&itg2_reg_field_100,
&itg2_reg_field_101,
&itg2_reg_field_102,
&itg2_reg_field_103,
&itg2_reg_field_104,
&itg2_reg_field_105,
&itg2_reg_field_106,
&itg2_reg_field_107,
&itg2_reg_field_108,
&itg2_reg_field_109,
&itg2_reg_field_110,
};
unsigned int itg2_reg_count = 25;
unsigned int itg2_reg_start = 0x81c0;
unsigned int itg2_reg_end = 0x8220;
unsigned int itg2_reg_in_bytes = 0x4;
unsigned int itg2_reg_total_field_count = 111;
char * itg2_reg_block_name = "itg2";
