#include "../reg.h"

struct reg_field itg_reg_field_0 = {
	.name = "Reserved_1",
	.bits_num = 22,
	.shift = 0,
	.reg_addr = 0x8100,
};
struct reg_field itg_reg_field_1 = {
	.name = "Sw_Flip_Pipe_Dither",
	.bits_num = 1,
	.shift = 22,
	.reg_addr = 0x8100,
};
struct reg_field itg_reg_field_2 = {
	.name = "Sw_Flip_Pipe_Ocsc",
	.bits_num = 1,
	.shift = 23,
	.reg_addr = 0x8100,
};
struct reg_field itg_reg_field_3 = {
	.name = "Sw_Flip_Pipe_Pus",
	.bits_num = 1,
	.shift = 24,
	.reg_addr = 0x8100,
};
struct reg_field itg_reg_field_4 = {
	.name = "Sw_Flip_Pipe_Lut",
	.bits_num = 1,
	.shift = 25,
	.reg_addr = 0x8100,
};
struct reg_field itg_reg_field_5 = {
	.name = "Sw_Flip_Pipe_Ovl1",
	.bits_num = 1,
	.shift = 26,
	.reg_addr = 0x8100,
};
struct reg_field itg_reg_field_6 = {
	.name = "Sw_Flip_Pipe_Ovl0",
	.bits_num = 1,
	.shift = 27,
	.reg_addr = 0x8100,
};
struct reg_field itg_reg_field_7 = {
	.name = "Sw_Flip_Itg_Cur",
	.bits_num = 1,
	.shift = 28,
	.reg_addr = 0x8100,
};
struct reg_field itg_reg_field_8 = {
	.name = "Sw_Flip_Itg_Spl1",
	.bits_num = 1,
	.shift = 29,
	.reg_addr = 0x8100,
};
struct reg_field itg_reg_field_9 = {
	.name = "Sw_Flip_Itg_Spl0",
	.bits_num = 1,
	.shift = 30,
	.reg_addr = 0x8100,
};
struct reg_field itg_reg_field_10 = {
	.name = "Sw_Itg_Flip_En",
	.bits_num = 1,
	.shift = 31,
	.reg_addr = 0x8100,
};
struct reg_info itg_reg_0 = {
	.reg_block_name = "itg",
	.reg_mmio_addr = 0x8100,
	.reg_sub_index = 0x0,
	.field_num = 11,
	.reg_in_bytes = 4,
};
struct reg_field itg_reg_field_11 = {
	.name = "Req_Pre_4l",
	.bits_num = 1,
	.shift = 0,
	.reg_addr = 0x8104,
};
struct reg_field itg_reg_field_12 = {
	.name = "Reserved_1",
	.bits_num = 31,
	.shift = 1,
	.reg_addr = 0x8104,
};
struct reg_info itg_reg_1 = {
	.reg_block_name = "itg",
	.reg_mmio_addr = 0x8104,
	.reg_sub_index = 0x1,
	.field_num = 2,
	.reg_in_bytes = 4,
};
struct reg_field itg_reg_field_13 = {
	.name = "Cur_Ref_Iwin",
	.bits_num = 1,
	.shift = 0,
	.reg_addr = 0x8108,
};
struct reg_field itg_reg_field_14 = {
	.name = "Spl_Ref_Iwin",
	.bits_num = 1,
	.shift = 1,
	.reg_addr = 0x8108,
};
struct reg_field itg_reg_field_15 = {
	.name = "Reserved_1",
	.bits_num = 30,
	.shift = 2,
	.reg_addr = 0x8108,
};
struct reg_info itg_reg_2 = {
	.reg_block_name = "itg",
	.reg_mmio_addr = 0x8108,
	.reg_sub_index = 0x2,
	.field_num = 3,
	.reg_in_bytes = 4,
};
struct reg_field itg_reg_field_16 = {
	.name = "Spl_Stride",
	.bits_num = 12,
	.shift = 0,
	.reg_addr = 0x810c,
};
struct reg_field itg_reg_field_17 = {
	.name = "Spl_Fb",
	.bits_num = 1,
	.shift = 12,
	.reg_addr = 0x810c,
};
struct reg_field itg_reg_field_18 = {
	.name = "Spl_Vir",
	.bits_num = 1,
	.shift = 13,
	.reg_addr = 0x810c,
};
struct reg_field itg_reg_field_19 = {
	.name = "Spl_Snoop",
	.bits_num = 1,
	.shift = 14,
	.reg_addr = 0x810c,
};
struct reg_field itg_reg_field_20 = {
	.name = "Spl_Pxl_Off",
	.bits_num = 5,
	.shift = 15,
	.reg_addr = 0x810c,
};
struct reg_field itg_reg_field_21 = {
	.name = "Spl_Share_Lb",
	.bits_num = 1,
	.shift = 20,
	.reg_addr = 0x810c,
};
struct reg_field itg_reg_field_22 = {
	.name = "Spl_Crycb",
	.bits_num = 1,
	.shift = 21,
	.reg_addr = 0x810c,
};
struct reg_field itg_reg_field_23 = {
	.name = "Spl_Cbycry",
	.bits_num = 1,
	.shift = 22,
	.reg_addr = 0x810c,
};
struct reg_field itg_reg_field_24 = {
	.name = "Spl_Abgr",
	.bits_num = 1,
	.shift = 23,
	.reg_addr = 0x810c,
};
struct reg_field itg_reg_field_25 = {
	.name = "Spl_Fmt",
	.bits_num = 4,
	.shift = 24,
	.reg_addr = 0x810c,
};
struct reg_field itg_reg_field_26 = {
	.name = "Spl_Rlen",
	.bits_num = 2,
	.shift = 28,
	.reg_addr = 0x810c,
};
struct reg_field itg_reg_field_27 = {
	.name = "Spl_Sec",
	.bits_num = 1,
	.shift = 30,
	.reg_addr = 0x810c,
};
struct reg_field itg_reg_field_28 = {
	.name = "Spl_En",
	.bits_num = 1,
	.shift = 31,
	.reg_addr = 0x810c,
};
struct reg_info itg_reg_3 = {
	.reg_block_name = "itg",
	.reg_mmio_addr = 0x810c,
	.reg_sub_index = 0x3,
	.field_num = 13,
	.reg_in_bytes = 4,
};
struct reg_field itg_reg_field_29 = {
	.name = "Spl_Comp_Type",
	.bits_num = 6,
	.shift = 0,
	.reg_addr = 0x8110,
};
struct reg_field itg_reg_field_30 = {
	.name = "Reserved_2",
	.bits_num = 2,
	.shift = 6,
	.reg_addr = 0x8110,
};
struct reg_field itg_reg_field_31 = {
	.name = "Spl_Comp_En",
	.bits_num = 1,
	.shift = 8,
	.reg_addr = 0x8110,
};
struct reg_field itg_reg_field_32 = {
	.name = "Reserved_1",
	.bits_num = 23,
	.shift = 9,
	.reg_addr = 0x8110,
};
struct reg_info itg_reg_4 = {
	.reg_block_name = "itg",
	.reg_mmio_addr = 0x8110,
	.reg_sub_index = 0x4,
	.field_num = 4,
	.reg_in_bytes = 4,
};
struct reg_field itg_reg_field_33 = {
	.name = "Spl_Ystart",
	.bits_num = 13,
	.shift = 0,
	.reg_addr = 0x8114,
};
struct reg_field itg_reg_field_34 = {
	.name = "Reserved_2",
	.bits_num = 3,
	.shift = 13,
	.reg_addr = 0x8114,
};
struct reg_field itg_reg_field_35 = {
	.name = "Spl_Xstart",
	.bits_num = 14,
	.shift = 16,
	.reg_addr = 0x8114,
};
struct reg_field itg_reg_field_36 = {
	.name = "Reserved_1",
	.bits_num = 2,
	.shift = 30,
	.reg_addr = 0x8114,
};
struct reg_info itg_reg_5 = {
	.reg_block_name = "itg",
	.reg_mmio_addr = 0x8114,
	.reg_sub_index = 0x5,
	.field_num = 4,
	.reg_in_bytes = 4,
};
struct reg_field itg_reg_field_37 = {
	.name = "Spl_Src_H",
	.bits_num = 13,
	.shift = 0,
	.reg_addr = 0x8118,
};
struct reg_field itg_reg_field_38 = {
	.name = "Reserved_2",
	.bits_num = 3,
	.shift = 13,
	.reg_addr = 0x8118,
};
struct reg_field itg_reg_field_39 = {
	.name = "Spl_Src_W",
	.bits_num = 14,
	.shift = 16,
	.reg_addr = 0x8118,
};
struct reg_field itg_reg_field_40 = {
	.name = "Reserved_1",
	.bits_num = 2,
	.shift = 30,
	.reg_addr = 0x8118,
};
struct reg_info itg_reg_6 = {
	.reg_block_name = "itg",
	.reg_mmio_addr = 0x8118,
	.reg_sub_index = 0x6,
	.field_num = 4,
	.reg_in_bytes = 4,
};
struct reg_field itg_reg_field_41 = {
	.name = "Spl_Dst_H",
	.bits_num = 13,
	.shift = 0,
	.reg_addr = 0x811c,
};
struct reg_field itg_reg_field_42 = {
	.name = "Reserved_2",
	.bits_num = 3,
	.shift = 13,
	.reg_addr = 0x811c,
};
struct reg_field itg_reg_field_43 = {
	.name = "Spl_Dst_W",
	.bits_num = 14,
	.shift = 16,
	.reg_addr = 0x811c,
};
struct reg_field itg_reg_field_44 = {
	.name = "Reserved_1",
	.bits_num = 2,
	.shift = 30,
	.reg_addr = 0x811c,
};
struct reg_info itg_reg_7 = {
	.reg_block_name = "itg",
	.reg_mmio_addr = 0x811c,
	.reg_sub_index = 0x7,
	.field_num = 4,
	.reg_in_bytes = 4,
};
struct reg_field itg_reg_field_45 = {
	.name = "Spl1_Hacc",
	.bits_num = 21,
	.shift = 0,
	.reg_addr = 0x8120,
};
struct reg_field itg_reg_field_46 = {
	.name = "Reserved_1",
	.bits_num = 9,
	.shift = 21,
	.reg_addr = 0x8120,
};
struct reg_field itg_reg_field_47 = {
	.name = "Spl_Vtap",
	.bits_num = 1,
	.shift = 30,
	.reg_addr = 0x8120,
};
struct reg_field itg_reg_field_48 = {
	.name = "Spl_Htap",
	.bits_num = 1,
	.shift = 31,
	.reg_addr = 0x8120,
};
struct reg_info itg_reg_8 = {
	.reg_block_name = "itg",
	.reg_mmio_addr = 0x8120,
	.reg_sub_index = 0x8,
	.field_num = 4,
	.reg_in_bytes = 4,
};
struct reg_field itg_reg_field_49 = {
	.name = "Spl_Vacc",
	.bits_num = 21,
	.shift = 0,
	.reg_addr = 0x8124,
};
struct reg_field itg_reg_field_50 = {
	.name = "Reserved_1",
	.bits_num = 9,
	.shift = 21,
	.reg_addr = 0x8124,
};
struct reg_field itg_reg_field_51 = {
	.name = "Spl_Alpha_Ups",
	.bits_num = 1,
	.shift = 30,
	.reg_addr = 0x8124,
};
struct reg_field itg_reg_field_52 = {
	.name = "Spl_Vdup",
	.bits_num = 1,
	.shift = 31,
	.reg_addr = 0x8124,
};
struct reg_info itg_reg_9 = {
	.reg_block_name = "itg",
	.reg_mmio_addr = 0x8124,
	.reg_sub_index = 0x9,
	.field_num = 4,
	.reg_in_bytes = 4,
};
struct reg_field itg_reg_field_53 = {
	.name = "Spl_Base_Adr",
	.bits_num = 31,
	.shift = 0,
	.reg_addr = 0x8128,
};
struct reg_field itg_reg_field_54 = {
	.name = "Reserved_1",
	.bits_num = 1,
	.shift = 31,
	.reg_addr = 0x8128,
};
struct reg_info itg_reg_10 = {
	.reg_block_name = "itg",
	.reg_mmio_addr = 0x8128,
	.reg_sub_index = 0xa,
	.field_num = 2,
	.reg_in_bytes = 4,
};
struct reg_field itg_reg_field_55 = {
	.name = "Spl_Base_Off",
	.bits_num = 31,
	.shift = 0,
	.reg_addr = 0x812c,
};
struct reg_field itg_reg_field_56 = {
	.name = "Reserved_1",
	.bits_num = 1,
	.shift = 31,
	.reg_addr = 0x812c,
};
struct reg_info itg_reg_11 = {
	.reg_block_name = "itg",
	.reg_mmio_addr = 0x812c,
	.reg_sub_index = 0xb,
	.field_num = 2,
	.reg_in_bytes = 4,
};
struct reg_field itg_reg_field_57 = {
	.name = "Spl_Bl_Idx",
	.bits_num = 18,
	.shift = 0,
	.reg_addr = 0x8130,
};
struct reg_field itg_reg_field_58 = {
	.name = "Reserved_1",
	.bits_num = 14,
	.shift = 18,
	.reg_addr = 0x8130,
};
struct reg_info itg_reg_12 = {
	.reg_block_name = "itg",
	.reg_mmio_addr = 0x8130,
	.reg_sub_index = 0xc,
	.field_num = 2,
	.reg_in_bytes = 4,
};
struct reg_field itg_reg_field_59 = {
	.name = "Spl_Keyl",
	.bits_num = 30,
	.shift = 0,
	.reg_addr = 0x8134,
};
struct reg_field itg_reg_field_60 = {
	.name = "Reserved_1",
	.bits_num = 2,
	.shift = 30,
	.reg_addr = 0x8134,
};
struct reg_info itg_reg_13 = {
	.reg_block_name = "itg",
	.reg_mmio_addr = 0x8134,
	.reg_sub_index = 0xd,
	.field_num = 2,
	.reg_in_bytes = 4,
};
struct reg_field itg_reg_field_61 = {
	.name = "Spl_Keyh",
	.bits_num = 30,
	.shift = 0,
	.reg_addr = 0x8138,
};
struct reg_field itg_reg_field_62 = {
	.name = "Reserved_1",
	.bits_num = 2,
	.shift = 30,
	.reg_addr = 0x8138,
};
struct reg_info itg_reg_14 = {
	.reg_block_name = "itg",
	.reg_mmio_addr = 0x8138,
	.reg_sub_index = 0xe,
	.field_num = 2,
	.reg_in_bytes = 4,
};
struct reg_field itg_reg_field_63 = {
	.name = "Spl_Csc_Bright",
	.bits_num = 9,
	.shift = 0,
	.reg_addr = 0x813c,
};
struct reg_field itg_reg_field_64 = {
	.name = "Reserved_4",
	.bits_num = 11,
	.shift = 9,
	.reg_addr = 0x813c,
};
struct reg_field itg_reg_field_65 = {
	.name = "Spl_Csc_Bypass",
	.bits_num = 1,
	.shift = 20,
	.reg_addr = 0x813c,
};
struct reg_field itg_reg_field_66 = {
	.name = "Spl_Csc_Prog",
	.bits_num = 1,
	.shift = 21,
	.reg_addr = 0x813c,
};
struct reg_field itg_reg_field_67 = {
	.name = "Reserved_3",
	.bits_num = 2,
	.shift = 22,
	.reg_addr = 0x813c,
};
struct reg_field itg_reg_field_68 = {
	.name = "Spl_Csc_Outfmt",
	.bits_num = 3,
	.shift = 24,
	.reg_addr = 0x813c,
};
struct reg_field itg_reg_field_69 = {
	.name = "Reserved_2",
	.bits_num = 1,
	.shift = 27,
	.reg_addr = 0x813c,
};
struct reg_field itg_reg_field_70 = {
	.name = "Spl_Csc_Infmt",
	.bits_num = 3,
	.shift = 28,
	.reg_addr = 0x813c,
};
struct reg_field itg_reg_field_71 = {
	.name = "Reserved_1",
	.bits_num = 1,
	.shift = 31,
	.reg_addr = 0x813c,
};
struct reg_info itg_reg_15 = {
	.reg_block_name = "itg",
	.reg_mmio_addr = 0x813c,
	.reg_sub_index = 0xf,
	.field_num = 9,
	.reg_in_bytes = 4,
};
struct reg_field itg_reg_field_72 = {
	.name = "Spl_Csc_Coef2",
	.bits_num = 14,
	.shift = 0,
	.reg_addr = 0x8140,
};
struct reg_field itg_reg_field_73 = {
	.name = "Reserved_2",
	.bits_num = 2,
	.shift = 14,
	.reg_addr = 0x8140,
};
struct reg_field itg_reg_field_74 = {
	.name = "Spl_Csc_Coef1",
	.bits_num = 14,
	.shift = 16,
	.reg_addr = 0x8140,
};
struct reg_field itg_reg_field_75 = {
	.name = "Reserved_1",
	.bits_num = 2,
	.shift = 30,
	.reg_addr = 0x8140,
};
struct reg_info itg_reg_16 = {
	.reg_block_name = "itg",
	.reg_mmio_addr = 0x8140,
	.reg_sub_index = 0x10,
	.field_num = 4,
	.reg_in_bytes = 4,
};
struct reg_field itg_reg_field_76 = {
	.name = "Spl_Csc_Coef4",
	.bits_num = 14,
	.shift = 0,
	.reg_addr = 0x8144,
};
struct reg_field itg_reg_field_77 = {
	.name = "Reserved_2",
	.bits_num = 2,
	.shift = 14,
	.reg_addr = 0x8144,
};
struct reg_field itg_reg_field_78 = {
	.name = "Spl_Csc_Coef3",
	.bits_num = 14,
	.shift = 16,
	.reg_addr = 0x8144,
};
struct reg_field itg_reg_field_79 = {
	.name = "Reserved_1",
	.bits_num = 2,
	.shift = 30,
	.reg_addr = 0x8144,
};
struct reg_info itg_reg_17 = {
	.reg_block_name = "itg",
	.reg_mmio_addr = 0x8144,
	.reg_sub_index = 0x11,
	.field_num = 4,
	.reg_in_bytes = 4,
};
struct reg_field itg_reg_field_80 = {
	.name = "Spl_Csc_Coef6",
	.bits_num = 14,
	.shift = 0,
	.reg_addr = 0x8148,
};
struct reg_field itg_reg_field_81 = {
	.name = "Reserved_2",
	.bits_num = 2,
	.shift = 14,
	.reg_addr = 0x8148,
};
struct reg_field itg_reg_field_82 = {
	.name = "Spl_Csc_Coef5",
	.bits_num = 14,
	.shift = 16,
	.reg_addr = 0x8148,
};
struct reg_field itg_reg_field_83 = {
	.name = "Reserved_1",
	.bits_num = 2,
	.shift = 30,
	.reg_addr = 0x8148,
};
struct reg_info itg_reg_18 = {
	.reg_block_name = "itg",
	.reg_mmio_addr = 0x8148,
	.reg_sub_index = 0x12,
	.field_num = 4,
	.reg_in_bytes = 4,
};
struct reg_field itg_reg_field_84 = {
	.name = "Spl_Csc_Coef8",
	.bits_num = 14,
	.shift = 0,
	.reg_addr = 0x814c,
};
struct reg_field itg_reg_field_85 = {
	.name = "Reserved_2",
	.bits_num = 2,
	.shift = 14,
	.reg_addr = 0x814c,
};
struct reg_field itg_reg_field_86 = {
	.name = "Spl_Csc_Coef7",
	.bits_num = 14,
	.shift = 16,
	.reg_addr = 0x814c,
};
struct reg_field itg_reg_field_87 = {
	.name = "Reserved_1",
	.bits_num = 2,
	.shift = 30,
	.reg_addr = 0x814c,
};
struct reg_info itg_reg_19 = {
	.reg_block_name = "itg",
	.reg_mmio_addr = 0x814c,
	.reg_sub_index = 0x13,
	.field_num = 4,
	.reg_in_bytes = 4,
};
struct reg_field itg_reg_field_88 = {
	.name = "Spl_Csc_Coef9",
	.bits_num = 30,
	.shift = 0,
	.reg_addr = 0x8150,
};
struct reg_field itg_reg_field_89 = {
	.name = "Reserved_1",
	.bits_num = 2,
	.shift = 30,
	.reg_addr = 0x8150,
};
struct reg_info itg_reg_20 = {
	.reg_block_name = "itg",
	.reg_mmio_addr = 0x8150,
	.reg_sub_index = 0x14,
	.field_num = 2,
	.reg_in_bytes = 4,
};
struct reg_field itg_reg_field_90 = {
	.name = "Cur_Yoffset",
	.bits_num = 7,
	.shift = 0,
	.reg_addr = 0x8154,
};
struct reg_field itg_reg_field_91 = {
	.name = "Reserved_4",
	.bits_num = 1,
	.shift = 7,
	.reg_addr = 0x8154,
};
struct reg_field itg_reg_field_92 = {
	.name = "Cur_Xoffset",
	.bits_num = 7,
	.shift = 8,
	.reg_addr = 0x8154,
};
struct reg_field itg_reg_field_93 = {
	.name = "Reserved_3",
	.bits_num = 1,
	.shift = 15,
	.reg_addr = 0x8154,
};
struct reg_field itg_reg_field_94 = {
	.name = "Cur_Fb",
	.bits_num = 1,
	.shift = 16,
	.reg_addr = 0x8154,
};
struct reg_field itg_reg_field_95 = {
	.name = "Cur_Vir",
	.bits_num = 1,
	.shift = 17,
	.reg_addr = 0x8154,
};
struct reg_field itg_reg_field_96 = {
	.name = "Cur_Snoop",
	.bits_num = 1,
	.shift = 18,
	.reg_addr = 0x8154,
};
struct reg_field itg_reg_field_97 = {
	.name = "Reserved_2",
	.bits_num = 5,
	.shift = 19,
	.reg_addr = 0x8154,
};
struct reg_field itg_reg_field_98 = {
	.name = "Cur_Size",
	.bits_num = 2,
	.shift = 24,
	.reg_addr = 0x8154,
};
struct reg_field itg_reg_field_99 = {
	.name = "Reserved_1",
	.bits_num = 2,
	.shift = 26,
	.reg_addr = 0x8154,
};
struct reg_field itg_reg_field_100 = {
	.name = "Cur_Pos_Type",
	.bits_num = 1,
	.shift = 28,
	.reg_addr = 0x8154,
};
struct reg_field itg_reg_field_101 = {
	.name = "Cur_Type",
	.bits_num = 2,
	.shift = 29,
	.reg_addr = 0x8154,
};
struct reg_field itg_reg_field_102 = {
	.name = "Cur_En",
	.bits_num = 1,
	.shift = 31,
	.reg_addr = 0x8154,
};
struct reg_info itg_reg_21 = {
	.reg_block_name = "itg",
	.reg_mmio_addr = 0x8154,
	.reg_sub_index = 0x15,
	.field_num = 13,
	.reg_in_bytes = 4,
};
struct reg_field itg_reg_field_103 = {
	.name = "Cur_Ystart",
	.bits_num = 13,
	.shift = 0,
	.reg_addr = 0x8158,
};
struct reg_field itg_reg_field_104 = {
	.name = "Reserved_2",
	.bits_num = 3,
	.shift = 13,
	.reg_addr = 0x8158,
};
struct reg_field itg_reg_field_105 = {
	.name = "Cur_Xstart",
	.bits_num = 14,
	.shift = 16,
	.reg_addr = 0x8158,
};
struct reg_field itg_reg_field_106 = {
	.name = "Reserved_1",
	.bits_num = 2,
	.shift = 30,
	.reg_addr = 0x8158,
};
struct reg_info itg_reg_22 = {
	.reg_block_name = "itg",
	.reg_mmio_addr = 0x8158,
	.reg_sub_index = 0x16,
	.field_num = 4,
	.reg_in_bytes = 4,
};
struct reg_field itg_reg_field_107 = {
	.name = "Cur_Base",
	.bits_num = 31,
	.shift = 0,
	.reg_addr = 0x815c,
};
struct reg_field itg_reg_field_108 = {
	.name = "Reserved_1",
	.bits_num = 1,
	.shift = 31,
	.reg_addr = 0x815c,
};
struct reg_info itg_reg_23 = {
	.reg_block_name = "itg",
	.reg_mmio_addr = 0x815c,
	.reg_sub_index = 0x17,
	.field_num = 2,
	.reg_in_bytes = 4,
};
struct reg_field itg_reg_field_109 = {
	.name = "Cur_Csc_Outfmt",
	.bits_num = 3,
	.shift = 0,
	.reg_addr = 0x8160,
};
struct reg_field itg_reg_field_110 = {
	.name = "Reserved_1",
	.bits_num = 29,
	.shift = 3,
	.reg_addr = 0x8160,
};
struct reg_info itg_reg_24 = {
	.reg_block_name = "itg",
	.reg_mmio_addr = 0x8160,
	.reg_sub_index = 0x18,
	.field_num = 2,
	.reg_in_bytes = 4,
};
struct reg_info * itg_reg_info[25] = {
&itg_reg_0,
&itg_reg_1,
&itg_reg_2,
&itg_reg_3,
&itg_reg_4,
&itg_reg_5,
&itg_reg_6,
&itg_reg_7,
&itg_reg_8,
&itg_reg_9,
&itg_reg_10,
&itg_reg_11,
&itg_reg_12,
&itg_reg_13,
&itg_reg_14,
&itg_reg_15,
&itg_reg_16,
&itg_reg_17,
&itg_reg_18,
&itg_reg_19,
&itg_reg_20,
&itg_reg_21,
&itg_reg_22,
&itg_reg_23,
&itg_reg_24,
};
struct reg_field * itg_reg_field_info[111] = {
&itg_reg_field_0,
&itg_reg_field_1,
&itg_reg_field_2,
&itg_reg_field_3,
&itg_reg_field_4,
&itg_reg_field_5,
&itg_reg_field_6,
&itg_reg_field_7,
&itg_reg_field_8,
&itg_reg_field_9,
&itg_reg_field_10,
&itg_reg_field_11,
&itg_reg_field_12,
&itg_reg_field_13,
&itg_reg_field_14,
&itg_reg_field_15,
&itg_reg_field_16,
&itg_reg_field_17,
&itg_reg_field_18,
&itg_reg_field_19,
&itg_reg_field_20,
&itg_reg_field_21,
&itg_reg_field_22,
&itg_reg_field_23,
&itg_reg_field_24,
&itg_reg_field_25,
&itg_reg_field_26,
&itg_reg_field_27,
&itg_reg_field_28,
&itg_reg_field_29,
&itg_reg_field_30,
&itg_reg_field_31,
&itg_reg_field_32,
&itg_reg_field_33,
&itg_reg_field_34,
&itg_reg_field_35,
&itg_reg_field_36,
&itg_reg_field_37,
&itg_reg_field_38,
&itg_reg_field_39,
&itg_reg_field_40,
&itg_reg_field_41,
&itg_reg_field_42,
&itg_reg_field_43,
&itg_reg_field_44,
&itg_reg_field_45,
&itg_reg_field_46,
&itg_reg_field_47,
&itg_reg_field_48,
&itg_reg_field_49,
&itg_reg_field_50,
&itg_reg_field_51,
&itg_reg_field_52,
&itg_reg_field_53,
&itg_reg_field_54,
&itg_reg_field_55,
&itg_reg_field_56,
&itg_reg_field_57,
&itg_reg_field_58,
&itg_reg_field_59,
&itg_reg_field_60,
&itg_reg_field_61,
&itg_reg_field_62,
&itg_reg_field_63,
&itg_reg_field_64,
&itg_reg_field_65,
&itg_reg_field_66,
&itg_reg_field_67,
&itg_reg_field_68,
&itg_reg_field_69,
&itg_reg_field_70,
&itg_reg_field_71,
&itg_reg_field_72,
&itg_reg_field_73,
&itg_reg_field_74,
&itg_reg_field_75,
&itg_reg_field_76,
&itg_reg_field_77,
&itg_reg_field_78,
&itg_reg_field_79,
&itg_reg_field_80,
&itg_reg_field_81,
&itg_reg_field_82,
&itg_reg_field_83,
&itg_reg_field_84,
&itg_reg_field_85,
&itg_reg_field_86,
&itg_reg_field_87,
&itg_reg_field_88,
&itg_reg_field_89,
&itg_reg_field_90,
&itg_reg_field_91,
&itg_reg_field_92,
&itg_reg_field_93,
&itg_reg_field_94,
&itg_reg_field_95,
&itg_reg_field_96,
&itg_reg_field_97,
&itg_reg_field_98,
&itg_reg_field_99,
&itg_reg_field_100,
&itg_reg_field_101,
&itg_reg_field_102,
&itg_reg_field_103,
&itg_reg_field_104,
&itg_reg_field_105,
&itg_reg_field_106,
&itg_reg_field_107,
&itg_reg_field_108,
&itg_reg_field_109,
&itg_reg_field_110,
};
unsigned int itg_reg_count = 25;
unsigned int itg_reg_start = 0x8100;
unsigned int itg_reg_end = 0x8160;
unsigned int itg_reg_in_bytes = 0x4;
unsigned int itg_reg_total_field_count = 111;
char * itg_reg_block_name = "itg";
