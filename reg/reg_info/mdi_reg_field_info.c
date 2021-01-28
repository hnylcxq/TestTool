#include "../reg.h"

struct reg_field mdi_reg_field_0 = {
	.name = "Mdi_Hda_Timeout",
	.bits_num = 8,
	.shift = 0,
	.reg_addr = 0x8300,
};
struct reg_field mdi_reg_field_1 = {
	.name = "Mdi_Hda_Timeout_Dis",
	.bits_num = 1,
	.shift = 8,
	.reg_addr = 0x8300,
};
struct reg_field mdi_reg_field_2 = {
	.name = "Reserved_2",
	.bits_num = 7,
	.shift = 9,
	.reg_addr = 0x8300,
};
struct reg_field mdi_reg_field_3 = {
	.name = "Mdi_Req_Method",
	.bits_num = 1,
	.shift = 16,
	.reg_addr = 0x8300,
};
struct reg_field mdi_reg_field_4 = {
	.name = "Mdi_Const_Hprio",
	.bits_num = 1,
	.shift = 17,
	.reg_addr = 0x8300,
};
struct reg_field mdi_reg_field_5 = {
	.name = "Mdi_Hreq_Arb_Dis",
	.bits_num = 1,
	.shift = 18,
	.reg_addr = 0x8300,
};
struct reg_field mdi_reg_field_6 = {
	.name = "Mdi_Idle_Round_En",
	.bits_num = 1,
	.shift = 19,
	.reg_addr = 0x8300,
};
struct reg_field mdi_reg_field_7 = {
	.name = "Reserved_1",
	.bits_num = 12,
	.shift = 20,
	.reg_addr = 0x8300,
};
struct reg_info mdi_reg_0 = {
	.reg_block_name = "mdi",
	.reg_mmio_addr = 0x8300,
	.reg_sub_index = 0x0,
	.field_num = 8,
	.reg_in_bytes = 4,
};
struct reg_field mdi_reg_field_8 = {
	.name = "Mdi_A_Spl1_Timeout",
	.bits_num = 8,
	.shift = 0,
	.reg_addr = 0x8304,
};
struct reg_field mdi_reg_field_9 = {
	.name = "Mdi_A_Spl0_Timeout",
	.bits_num = 8,
	.shift = 8,
	.reg_addr = 0x8304,
};
struct reg_field mdi_reg_field_10 = {
	.name = "Mdi_A_Vga_Timeout",
	.bits_num = 8,
	.shift = 16,
	.reg_addr = 0x8304,
};
struct reg_field mdi_reg_field_11 = {
	.name = "Mdi_A_Spl1_Timeout_Dis",
	.bits_num = 1,
	.shift = 24,
	.reg_addr = 0x8304,
};
struct reg_field mdi_reg_field_12 = {
	.name = "Mdi_A_Spl0_Timeout_Dis",
	.bits_num = 1,
	.shift = 25,
	.reg_addr = 0x8304,
};
struct reg_field mdi_reg_field_13 = {
	.name = "Mdi_A_Vga_Timeout_Dis",
	.bits_num = 1,
	.shift = 26,
	.reg_addr = 0x8304,
};
struct reg_field mdi_reg_field_14 = {
	.name = "Reserved_1",
	.bits_num = 5,
	.shift = 27,
	.reg_addr = 0x8304,
};
struct reg_info mdi_reg_1 = {
	.reg_block_name = "mdi",
	.reg_mmio_addr = 0x8304,
	.reg_sub_index = 0x1,
	.field_num = 7,
	.reg_in_bytes = 4,
};
struct reg_field mdi_reg_field_15 = {
	.name = "Mdi_A_Vga_Hthrhld",
	.bits_num = 9,
	.shift = 0,
	.reg_addr = 0x8308,
};
struct reg_field mdi_reg_field_16 = {
	.name = "Reserved_2",
	.bits_num = 3,
	.shift = 9,
	.reg_addr = 0x8308,
};
struct reg_field mdi_reg_field_17 = {
	.name = "Mdi_A_Vga_Lthrhld",
	.bits_num = 9,
	.shift = 12,
	.reg_addr = 0x8308,
};
struct reg_field mdi_reg_field_18 = {
	.name = "Reserved_1",
	.bits_num = 11,
	.shift = 21,
	.reg_addr = 0x8308,
};
struct reg_info mdi_reg_2 = {
	.reg_block_name = "mdi",
	.reg_mmio_addr = 0x8308,
	.reg_sub_index = 0x2,
	.field_num = 4,
	.reg_in_bytes = 4,
};
struct reg_field mdi_reg_field_19 = {
	.name = "Mdi_A_Spl0_Hthrhld",
	.bits_num = 10,
	.shift = 0,
	.reg_addr = 0x830c,
};
struct reg_field mdi_reg_field_20 = {
	.name = "Reserved_4",
	.bits_num = 2,
	.shift = 10,
	.reg_addr = 0x830c,
};
struct reg_field mdi_reg_field_21 = {
	.name = "Mdi_A_Spl0_Lthrhld",
	.bits_num = 10,
	.shift = 12,
	.reg_addr = 0x830c,
};
struct reg_field mdi_reg_field_22 = {
	.name = "Reserved_3",
	.bits_num = 2,
	.shift = 22,
	.reg_addr = 0x830c,
};
struct reg_field mdi_reg_field_23 = {
	.name = "Mdi_A_Spl0_Ff_Depth",
	.bits_num = 3,
	.shift = 24,
	.reg_addr = 0x830c,
};
struct reg_field mdi_reg_field_24 = {
	.name = "Reserved_1",
	.bits_num = 5,
	.shift = 27,
	.reg_addr = 0x830c,
};
struct reg_info mdi_reg_3 = {
	.reg_block_name = "mdi",
	.reg_mmio_addr = 0x830c,
	.reg_sub_index = 0x3,
	.field_num = 6,
	.reg_in_bytes = 4,
};
struct reg_field mdi_reg_field_25 = {
	.name = "Mdi_A_Spl1_Hthrhld",
	.bits_num = 10,
	.shift = 0,
	.reg_addr = 0x8310,
};
struct reg_field mdi_reg_field_26 = {
	.name = "Reserved_4",
	.bits_num = 2,
	.shift = 10,
	.reg_addr = 0x8310,
};
struct reg_field mdi_reg_field_27 = {
	.name = "Mdi_A_Spl1_Lthrhld",
	.bits_num = 10,
	.shift = 12,
	.reg_addr = 0x8310,
};
struct reg_field mdi_reg_field_28 = {
	.name = "Reserved_3",
	.bits_num = 2,
	.shift = 22,
	.reg_addr = 0x8310,
};
struct reg_field mdi_reg_field_29 = {
	.name = "Mdi_A_Spl1_Ff_Depth",
	.bits_num = 3,
	.shift = 24,
	.reg_addr = 0x8310,
};
struct reg_field mdi_reg_field_30 = {
	.name = "Reserved_1",
	.bits_num = 5,
	.shift = 27,
	.reg_addr = 0x8310,
};
struct reg_info mdi_reg_4 = {
	.reg_block_name = "mdi",
	.reg_mmio_addr = 0x8310,
	.reg_sub_index = 0x4,
	.field_num = 6,
	.reg_in_bytes = 4,
};
struct reg_field mdi_reg_field_31 = {
	.name = "Mdi_B_Spl1_Timeout",
	.bits_num = 8,
	.shift = 0,
	.reg_addr = 0x8314,
};
struct reg_field mdi_reg_field_32 = {
	.name = "Mdi_B_Spl0_Timeout",
	.bits_num = 8,
	.shift = 8,
	.reg_addr = 0x8314,
};
struct reg_field mdi_reg_field_33 = {
	.name = "Mdi_B_Vga_Timeout",
	.bits_num = 8,
	.shift = 16,
	.reg_addr = 0x8314,
};
struct reg_field mdi_reg_field_34 = {
	.name = "Mdi_B_Spl1_Timeout_Dis",
	.bits_num = 1,
	.shift = 24,
	.reg_addr = 0x8314,
};
struct reg_field mdi_reg_field_35 = {
	.name = "Mdi_B_Spl0_Timeout_Dis",
	.bits_num = 1,
	.shift = 25,
	.reg_addr = 0x8314,
};
struct reg_field mdi_reg_field_36 = {
	.name = "Mdi_B_Vga_Timeout_Dis",
	.bits_num = 1,
	.shift = 26,
	.reg_addr = 0x8314,
};
struct reg_field mdi_reg_field_37 = {
	.name = "Reserved_1",
	.bits_num = 5,
	.shift = 27,
	.reg_addr = 0x8314,
};
struct reg_info mdi_reg_5 = {
	.reg_block_name = "mdi",
	.reg_mmio_addr = 0x8314,
	.reg_sub_index = 0x5,
	.field_num = 7,
	.reg_in_bytes = 4,
};
struct reg_field mdi_reg_field_38 = {
	.name = "Mdi_B_Vga_Hthrhld",
	.bits_num = 9,
	.shift = 0,
	.reg_addr = 0x8318,
};
struct reg_field mdi_reg_field_39 = {
	.name = "Reserved_2",
	.bits_num = 3,
	.shift = 9,
	.reg_addr = 0x8318,
};
struct reg_field mdi_reg_field_40 = {
	.name = "Mdi_B_Vga_Lthrhld",
	.bits_num = 9,
	.shift = 12,
	.reg_addr = 0x8318,
};
struct reg_field mdi_reg_field_41 = {
	.name = "Reserved_1",
	.bits_num = 11,
	.shift = 21,
	.reg_addr = 0x8318,
};
struct reg_info mdi_reg_6 = {
	.reg_block_name = "mdi",
	.reg_mmio_addr = 0x8318,
	.reg_sub_index = 0x6,
	.field_num = 4,
	.reg_in_bytes = 4,
};
struct reg_field mdi_reg_field_42 = {
	.name = "Mdi_B_Spl0_Hthrhld",
	.bits_num = 10,
	.shift = 0,
	.reg_addr = 0x831c,
};
struct reg_field mdi_reg_field_43 = {
	.name = "Reserved_4",
	.bits_num = 2,
	.shift = 10,
	.reg_addr = 0x831c,
};
struct reg_field mdi_reg_field_44 = {
	.name = "Mdi_B_Spl0_Lthrhld",
	.bits_num = 10,
	.shift = 12,
	.reg_addr = 0x831c,
};
struct reg_field mdi_reg_field_45 = {
	.name = "Reserved_3",
	.bits_num = 2,
	.shift = 22,
	.reg_addr = 0x831c,
};
struct reg_field mdi_reg_field_46 = {
	.name = "Mdi_B_Spl0_Ff_Depth",
	.bits_num = 3,
	.shift = 24,
	.reg_addr = 0x831c,
};
struct reg_field mdi_reg_field_47 = {
	.name = "Reserved_1",
	.bits_num = 5,
	.shift = 27,
	.reg_addr = 0x831c,
};
struct reg_info mdi_reg_7 = {
	.reg_block_name = "mdi",
	.reg_mmio_addr = 0x831c,
	.reg_sub_index = 0x7,
	.field_num = 6,
	.reg_in_bytes = 4,
};
struct reg_field mdi_reg_field_48 = {
	.name = "Mdi_B_Spl1_Hthrhld",
	.bits_num = 10,
	.shift = 0,
	.reg_addr = 0x8320,
};
struct reg_field mdi_reg_field_49 = {
	.name = "Reserved_4",
	.bits_num = 2,
	.shift = 10,
	.reg_addr = 0x8320,
};
struct reg_field mdi_reg_field_50 = {
	.name = "Mdi_B_Spl1_Lthrhld",
	.bits_num = 10,
	.shift = 12,
	.reg_addr = 0x8320,
};
struct reg_field mdi_reg_field_51 = {
	.name = "Reserved_3",
	.bits_num = 2,
	.shift = 22,
	.reg_addr = 0x8320,
};
struct reg_field mdi_reg_field_52 = {
	.name = "Mdi_B_Spl1_Ff_Depth",
	.bits_num = 3,
	.shift = 24,
	.reg_addr = 0x8320,
};
struct reg_field mdi_reg_field_53 = {
	.name = "Reserved_1",
	.bits_num = 5,
	.shift = 27,
	.reg_addr = 0x8320,
};
struct reg_info mdi_reg_8 = {
	.reg_block_name = "mdi",
	.reg_mmio_addr = 0x8320,
	.reg_sub_index = 0x8,
	.field_num = 6,
	.reg_in_bytes = 4,
};
struct reg_field mdi_reg_field_54 = {
	.name = "Mdi_C_Spl1_Timeout",
	.bits_num = 8,
	.shift = 0,
	.reg_addr = 0x8324,
};
struct reg_field mdi_reg_field_55 = {
	.name = "Mdi_C_Spl0_Timeout",
	.bits_num = 8,
	.shift = 8,
	.reg_addr = 0x8324,
};
struct reg_field mdi_reg_field_56 = {
	.name = "Mdi_C_Vga_Timeout",
	.bits_num = 8,
	.shift = 16,
	.reg_addr = 0x8324,
};
struct reg_field mdi_reg_field_57 = {
	.name = "Mdi_C_Spl1_Timeout_Dis",
	.bits_num = 1,
	.shift = 24,
	.reg_addr = 0x8324,
};
struct reg_field mdi_reg_field_58 = {
	.name = "Mdi_C_Spl0_Timeout_Dis",
	.bits_num = 1,
	.shift = 25,
	.reg_addr = 0x8324,
};
struct reg_field mdi_reg_field_59 = {
	.name = "Mdi_C_Vga_Timeout_Dis",
	.bits_num = 1,
	.shift = 26,
	.reg_addr = 0x8324,
};
struct reg_field mdi_reg_field_60 = {
	.name = "Reserved_1",
	.bits_num = 5,
	.shift = 27,
	.reg_addr = 0x8324,
};
struct reg_info mdi_reg_9 = {
	.reg_block_name = "mdi",
	.reg_mmio_addr = 0x8324,
	.reg_sub_index = 0x9,
	.field_num = 7,
	.reg_in_bytes = 4,
};
struct reg_field mdi_reg_field_61 = {
	.name = "Mdi_C_Vga_Hthrhld",
	.bits_num = 9,
	.shift = 0,
	.reg_addr = 0x8328,
};
struct reg_field mdi_reg_field_62 = {
	.name = "Reserved_2",
	.bits_num = 3,
	.shift = 9,
	.reg_addr = 0x8328,
};
struct reg_field mdi_reg_field_63 = {
	.name = "Mdi_C_Vga_Lthrhld",
	.bits_num = 9,
	.shift = 12,
	.reg_addr = 0x8328,
};
struct reg_field mdi_reg_field_64 = {
	.name = "Reserved_1",
	.bits_num = 11,
	.shift = 21,
	.reg_addr = 0x8328,
};
struct reg_info mdi_reg_10 = {
	.reg_block_name = "mdi",
	.reg_mmio_addr = 0x8328,
	.reg_sub_index = 0xa,
	.field_num = 4,
	.reg_in_bytes = 4,
};
struct reg_field mdi_reg_field_65 = {
	.name = "Mdi_C_Spl0_Hthrhld",
	.bits_num = 10,
	.shift = 0,
	.reg_addr = 0x832c,
};
struct reg_field mdi_reg_field_66 = {
	.name = "Reserved_4",
	.bits_num = 2,
	.shift = 10,
	.reg_addr = 0x832c,
};
struct reg_field mdi_reg_field_67 = {
	.name = "Mdi_C_Spl0_Lthrhld",
	.bits_num = 10,
	.shift = 12,
	.reg_addr = 0x832c,
};
struct reg_field mdi_reg_field_68 = {
	.name = "Reserved_3",
	.bits_num = 2,
	.shift = 22,
	.reg_addr = 0x832c,
};
struct reg_field mdi_reg_field_69 = {
	.name = "Mdi_C_Spl0_Ff_Depth",
	.bits_num = 3,
	.shift = 24,
	.reg_addr = 0x832c,
};
struct reg_field mdi_reg_field_70 = {
	.name = "Reserved_1",
	.bits_num = 5,
	.shift = 27,
	.reg_addr = 0x832c,
};
struct reg_info mdi_reg_11 = {
	.reg_block_name = "mdi",
	.reg_mmio_addr = 0x832c,
	.reg_sub_index = 0xb,
	.field_num = 6,
	.reg_in_bytes = 4,
};
struct reg_field mdi_reg_field_71 = {
	.name = "Mdi_C_Spl1_Hthrhld",
	.bits_num = 10,
	.shift = 0,
	.reg_addr = 0x8330,
};
struct reg_field mdi_reg_field_72 = {
	.name = "Reserved_4",
	.bits_num = 2,
	.shift = 10,
	.reg_addr = 0x8330,
};
struct reg_field mdi_reg_field_73 = {
	.name = "Mdi_C_Spl1_Lthrhld",
	.bits_num = 10,
	.shift = 12,
	.reg_addr = 0x8330,
};
struct reg_field mdi_reg_field_74 = {
	.name = "Reserved_3",
	.bits_num = 2,
	.shift = 22,
	.reg_addr = 0x8330,
};
struct reg_field mdi_reg_field_75 = {
	.name = "Mdi_C_Spl1_Ff_Depth",
	.bits_num = 3,
	.shift = 24,
	.reg_addr = 0x8330,
};
struct reg_field mdi_reg_field_76 = {
	.name = "Reserved_1",
	.bits_num = 5,
	.shift = 27,
	.reg_addr = 0x8330,
};
struct reg_info mdi_reg_12 = {
	.reg_block_name = "mdi",
	.reg_mmio_addr = 0x8330,
	.reg_sub_index = 0xc,
	.field_num = 6,
	.reg_in_bytes = 4,
};
struct reg_field mdi_reg_field_77 = {
	.name = "Mdi_A_Spl1_Chk_Ffadr",
	.bits_num = 10,
	.shift = 0,
	.reg_addr = 0x8334,
};
struct reg_field mdi_reg_field_78 = {
	.name = "Mdi_A_Spl0_Chk_Ffadr",
	.bits_num = 10,
	.shift = 10,
	.reg_addr = 0x8334,
};
struct reg_field mdi_reg_field_79 = {
	.name = "Mdi_A_Vga_Chk_Ffadr",
	.bits_num = 9,
	.shift = 20,
	.reg_addr = 0x8334,
};
struct reg_field mdi_reg_field_80 = {
	.name = "Reserved_1",
	.bits_num = 1,
	.shift = 29,
	.reg_addr = 0x8334,
};
struct reg_field mdi_reg_field_81 = {
	.name = "Mdi_Cnt_Rst",
	.bits_num = 1,
	.shift = 30,
	.reg_addr = 0x8334,
};
struct reg_field mdi_reg_field_82 = {
	.name = "Mdi_Req_Checken",
	.bits_num = 1,
	.shift = 31,
	.reg_addr = 0x8334,
};
struct reg_info mdi_reg_13 = {
	.reg_block_name = "mdi",
	.reg_mmio_addr = 0x8334,
	.reg_sub_index = 0xd,
	.field_num = 6,
	.reg_in_bytes = 4,
};
struct reg_field mdi_reg_field_83 = {
	.name = "Mdi_B_Spl1_Chk_Ffadr",
	.bits_num = 10,
	.shift = 0,
	.reg_addr = 0x8338,
};
struct reg_field mdi_reg_field_84 = {
	.name = "Mdi_B_Spl0_Chk_Ffadr",
	.bits_num = 10,
	.shift = 10,
	.reg_addr = 0x8338,
};
struct reg_field mdi_reg_field_85 = {
	.name = "Mdi_B_Vga_Chk_Ffadr",
	.bits_num = 9,
	.shift = 20,
	.reg_addr = 0x8338,
};
struct reg_field mdi_reg_field_86 = {
	.name = "Reserved_1",
	.bits_num = 3,
	.shift = 29,
	.reg_addr = 0x8338,
};
struct reg_info mdi_reg_14 = {
	.reg_block_name = "mdi",
	.reg_mmio_addr = 0x8338,
	.reg_sub_index = 0xe,
	.field_num = 4,
	.reg_in_bytes = 4,
};
struct reg_field mdi_reg_field_87 = {
	.name = "Mdi_C_Spl1_Chk_Ffadr",
	.bits_num = 10,
	.shift = 0,
	.reg_addr = 0x833c,
};
struct reg_field mdi_reg_field_88 = {
	.name = "Mdi_C_Spl0_Chk_Ffadr",
	.bits_num = 10,
	.shift = 10,
	.reg_addr = 0x833c,
};
struct reg_field mdi_reg_field_89 = {
	.name = "Mdi_C_Vga_Chk_Ffadr",
	.bits_num = 9,
	.shift = 20,
	.reg_addr = 0x833c,
};
struct reg_field mdi_reg_field_90 = {
	.name = "Reserved_1",
	.bits_num = 3,
	.shift = 29,
	.reg_addr = 0x833c,
};
struct reg_info mdi_reg_15 = {
	.reg_block_name = "mdi",
	.reg_mmio_addr = 0x833c,
	.reg_sub_index = 0xf,
	.field_num = 4,
	.reg_in_bytes = 4,
};
struct reg_field mdi_reg_field_91 = {
	.name = "Mdi_Strobe_Tag",
	.bits_num = 18,
	.shift = 0,
	.reg_addr = 0x8340,
};
struct reg_field mdi_reg_field_92 = {
	.name = "Mdi_Strobe_Rst",
	.bits_num = 1,
	.shift = 18,
	.reg_addr = 0x8340,
};
struct reg_field mdi_reg_field_93 = {
	.name = "Mdi_Strobe_En",
	.bits_num = 1,
	.shift = 19,
	.reg_addr = 0x8340,
};
struct reg_field mdi_reg_field_94 = {
	.name = "Reserved_2",
	.bits_num = 4,
	.shift = 20,
	.reg_addr = 0x8340,
};
struct reg_field mdi_reg_field_95 = {
	.name = "Mdi_Burst_Chk_Id",
	.bits_num = 6,
	.shift = 24,
	.reg_addr = 0x8340,
};
struct reg_field mdi_reg_field_96 = {
	.name = "Mdi_Burst_Chk_Ffadr",
	.bits_num = 1,
	.shift = 30,
	.reg_addr = 0x8340,
};
struct reg_field mdi_reg_field_97 = {
	.name = "Reserved_1",
	.bits_num = 1,
	.shift = 31,
	.reg_addr = 0x8340,
};
struct reg_info mdi_reg_16 = {
	.reg_block_name = "mdi",
	.reg_mmio_addr = 0x8340,
	.reg_sub_index = 0x10,
	.field_num = 7,
	.reg_in_bytes = 4,
};
struct reg_field mdi_reg_field_98 = {
	.name = "Mdi_A_Vga_Max_Ltc",
	.bits_num = 13,
	.shift = 0,
	.reg_addr = 0x8344,
};
struct reg_field mdi_reg_field_99 = {
	.name = "Reserved_2",
	.bits_num = 3,
	.shift = 13,
	.reg_addr = 0x8344,
};
struct reg_field mdi_reg_field_100 = {
	.name = "Mdi_Burst_Max_Ltc",
	.bits_num = 13,
	.shift = 16,
	.reg_addr = 0x8344,
};
struct reg_field mdi_reg_field_101 = {
	.name = "Reserved_1",
	.bits_num = 3,
	.shift = 29,
	.reg_addr = 0x8344,
};
struct reg_info mdi_reg_17 = {
	.reg_block_name = "mdi",
	.reg_mmio_addr = 0x8344,
	.reg_sub_index = 0x11,
	.field_num = 4,
	.reg_in_bytes = 4,
};
struct reg_field mdi_reg_field_102 = {
	.name = "Mdi_A_Spl1_Max_Ltc",
	.bits_num = 13,
	.shift = 0,
	.reg_addr = 0x8348,
};
struct reg_field mdi_reg_field_103 = {
	.name = "Reserved_2",
	.bits_num = 3,
	.shift = 13,
	.reg_addr = 0x8348,
};
struct reg_field mdi_reg_field_104 = {
	.name = "Mdi_A_Spl0_Max_Ltc",
	.bits_num = 13,
	.shift = 16,
	.reg_addr = 0x8348,
};
struct reg_field mdi_reg_field_105 = {
	.name = "Reserved_1",
	.bits_num = 3,
	.shift = 29,
	.reg_addr = 0x8348,
};
struct reg_info mdi_reg_18 = {
	.reg_block_name = "mdi",
	.reg_mmio_addr = 0x8348,
	.reg_sub_index = 0x12,
	.field_num = 4,
	.reg_in_bytes = 4,
};
struct reg_field mdi_reg_field_106 = {
	.name = "Mdi_B_Vga_Max_Ltc",
	.bits_num = 13,
	.shift = 0,
	.reg_addr = 0x834c,
};
struct reg_field mdi_reg_field_107 = {
	.name = "Reserved_1",
	.bits_num = 19,
	.shift = 13,
	.reg_addr = 0x834c,
};
struct reg_info mdi_reg_19 = {
	.reg_block_name = "mdi",
	.reg_mmio_addr = 0x834c,
	.reg_sub_index = 0x13,
	.field_num = 2,
	.reg_in_bytes = 4,
};
struct reg_field mdi_reg_field_108 = {
	.name = "Mdi_B_Spl1_Max_Ltc",
	.bits_num = 13,
	.shift = 0,
	.reg_addr = 0x8350,
};
struct reg_field mdi_reg_field_109 = {
	.name = "Reserved_2",
	.bits_num = 3,
	.shift = 13,
	.reg_addr = 0x8350,
};
struct reg_field mdi_reg_field_110 = {
	.name = "Mdi_B_Spl0_Max_Ltc",
	.bits_num = 13,
	.shift = 16,
	.reg_addr = 0x8350,
};
struct reg_field mdi_reg_field_111 = {
	.name = "Reserved_1",
	.bits_num = 3,
	.shift = 29,
	.reg_addr = 0x8350,
};
struct reg_info mdi_reg_20 = {
	.reg_block_name = "mdi",
	.reg_mmio_addr = 0x8350,
	.reg_sub_index = 0x14,
	.field_num = 4,
	.reg_in_bytes = 4,
};
struct reg_field mdi_reg_field_112 = {
	.name = "Mdi_C_Vga_Max_Ltc",
	.bits_num = 13,
	.shift = 0,
	.reg_addr = 0x8354,
};
struct reg_field mdi_reg_field_113 = {
	.name = "Reserved_1",
	.bits_num = 19,
	.shift = 13,
	.reg_addr = 0x8354,
};
struct reg_info mdi_reg_21 = {
	.reg_block_name = "mdi",
	.reg_mmio_addr = 0x8354,
	.reg_sub_index = 0x15,
	.field_num = 2,
	.reg_in_bytes = 4,
};
struct reg_field mdi_reg_field_114 = {
	.name = "Mdi_C_Spl1_Max_Ltc",
	.bits_num = 13,
	.shift = 0,
	.reg_addr = 0x8358,
};
struct reg_field mdi_reg_field_115 = {
	.name = "Reserved_2",
	.bits_num = 3,
	.shift = 13,
	.reg_addr = 0x8358,
};
struct reg_field mdi_reg_field_116 = {
	.name = "Mdi_C_Spl0_Max_Ltc",
	.bits_num = 13,
	.shift = 16,
	.reg_addr = 0x8358,
};
struct reg_field mdi_reg_field_117 = {
	.name = "Reserved_1",
	.bits_num = 3,
	.shift = 29,
	.reg_addr = 0x8358,
};
struct reg_info mdi_reg_22 = {
	.reg_block_name = "mdi",
	.reg_mmio_addr = 0x8358,
	.reg_sub_index = 0x16,
	.field_num = 4,
	.reg_in_bytes = 4,
};
struct reg_field mdi_reg_field_118 = {
	.name = "Mdi_Strobe_Rdat_0",
	.bits_num = 32,
	.shift = 0,
	.reg_addr = 0x835c,
};
struct reg_info mdi_reg_23 = {
	.reg_block_name = "mdi",
	.reg_mmio_addr = 0x835c,
	.reg_sub_index = 0x17,
	.field_num = 1,
	.reg_in_bytes = 4,
};
struct reg_field mdi_reg_field_119 = {
	.name = "Mdi_Strobe_Rdat_1",
	.bits_num = 32,
	.shift = 0,
	.reg_addr = 0x8360,
};
struct reg_info mdi_reg_24 = {
	.reg_block_name = "mdi",
	.reg_mmio_addr = 0x8360,
	.reg_sub_index = 0x18,
	.field_num = 1,
	.reg_in_bytes = 4,
};
struct reg_field mdi_reg_field_120 = {
	.name = "Mdi_Strobe_Rdat_2",
	.bits_num = 32,
	.shift = 0,
	.reg_addr = 0x8364,
};
struct reg_info mdi_reg_25 = {
	.reg_block_name = "mdi",
	.reg_mmio_addr = 0x8364,
	.reg_sub_index = 0x19,
	.field_num = 1,
	.reg_in_bytes = 4,
};
struct reg_field mdi_reg_field_121 = {
	.name = "Mdi_Strobe_Rdat_3",
	.bits_num = 32,
	.shift = 0,
	.reg_addr = 0x8368,
};
struct reg_info mdi_reg_26 = {
	.reg_block_name = "mdi",
	.reg_mmio_addr = 0x8368,
	.reg_sub_index = 0x1a,
	.field_num = 1,
	.reg_in_bytes = 4,
};
struct reg_field mdi_reg_field_122 = {
	.name = "Mdi_Strobe_Rdat_4",
	.bits_num = 32,
	.shift = 0,
	.reg_addr = 0x836c,
};
struct reg_info mdi_reg_27 = {
	.reg_block_name = "mdi",
	.reg_mmio_addr = 0x836c,
	.reg_sub_index = 0x1b,
	.field_num = 1,
	.reg_in_bytes = 4,
};
struct reg_field mdi_reg_field_123 = {
	.name = "Mdi_Strobe_Rdat_5",
	.bits_num = 32,
	.shift = 0,
	.reg_addr = 0x8370,
};
struct reg_info mdi_reg_28 = {
	.reg_block_name = "mdi",
	.reg_mmio_addr = 0x8370,
	.reg_sub_index = 0x1c,
	.field_num = 1,
	.reg_in_bytes = 4,
};
struct reg_field mdi_reg_field_124 = {
	.name = "Mdi_Strobe_Rdat_6",
	.bits_num = 32,
	.shift = 0,
	.reg_addr = 0x8374,
};
struct reg_info mdi_reg_29 = {
	.reg_block_name = "mdi",
	.reg_mmio_addr = 0x8374,
	.reg_sub_index = 0x1d,
	.field_num = 1,
	.reg_in_bytes = 4,
};
struct reg_field mdi_reg_field_125 = {
	.name = "Mdi_Strobe_Rdat_7",
	.bits_num = 32,
	.shift = 0,
	.reg_addr = 0x8378,
};
struct reg_info mdi_reg_30 = {
	.reg_block_name = "mdi",
	.reg_mmio_addr = 0x8378,
	.reg_sub_index = 0x1e,
	.field_num = 1,
	.reg_in_bytes = 4,
};
struct reg_field mdi_reg_field_126 = {
	.name = "Mdi_C_Cur_Uflow",
	.bits_num = 1,
	.shift = 0,
	.reg_addr = 0x837c,
};
struct reg_field mdi_reg_field_127 = {
	.name = "Mdi_C_Spl1_Uflow",
	.bits_num = 1,
	.shift = 1,
	.reg_addr = 0x837c,
};
struct reg_field mdi_reg_field_128 = {
	.name = "Mdi_C_Spl0_Uflow",
	.bits_num = 1,
	.shift = 2,
	.reg_addr = 0x837c,
};
struct reg_field mdi_reg_field_129 = {
	.name = "Mdi_C_Vga_Uflow",
	.bits_num = 1,
	.shift = 3,
	.reg_addr = 0x837c,
};
struct reg_field mdi_reg_field_130 = {
	.name = "Mdi_B_Cur_Uflow",
	.bits_num = 1,
	.shift = 4,
	.reg_addr = 0x837c,
};
struct reg_field mdi_reg_field_131 = {
	.name = "Mdi_B_Spl1_Uflow",
	.bits_num = 1,
	.shift = 5,
	.reg_addr = 0x837c,
};
struct reg_field mdi_reg_field_132 = {
	.name = "Mdi_B_Spl0_Uflow",
	.bits_num = 1,
	.shift = 6,
	.reg_addr = 0x837c,
};
struct reg_field mdi_reg_field_133 = {
	.name = "Mdi_B_Vga_Uflow",
	.bits_num = 1,
	.shift = 7,
	.reg_addr = 0x837c,
};
struct reg_field mdi_reg_field_134 = {
	.name = "Mdi_A_Cur_Uflow",
	.bits_num = 1,
	.shift = 8,
	.reg_addr = 0x837c,
};
struct reg_field mdi_reg_field_135 = {
	.name = "Mdi_A_Spl1_Uflow",
	.bits_num = 1,
	.shift = 9,
	.reg_addr = 0x837c,
};
struct reg_field mdi_reg_field_136 = {
	.name = "Mdi_A_Spl0_Uflow",
	.bits_num = 1,
	.shift = 10,
	.reg_addr = 0x837c,
};
struct reg_field mdi_reg_field_137 = {
	.name = "Mdi_A_Vga_Uflow",
	.bits_num = 1,
	.shift = 11,
	.reg_addr = 0x837c,
};
struct reg_field mdi_reg_field_138 = {
	.name = "Reserved_1",
	.bits_num = 19,
	.shift = 12,
	.reg_addr = 0x837c,
};
struct reg_field mdi_reg_field_139 = {
	.name = "Mdi_Strobe_Status",
	.bits_num = 1,
	.shift = 31,
	.reg_addr = 0x837c,
};
struct reg_info mdi_reg_31 = {
	.reg_block_name = "mdi",
	.reg_mmio_addr = 0x837c,
	.reg_sub_index = 0x1f,
	.field_num = 14,
	.reg_in_bytes = 4,
};
struct reg_info * mdi_reg_info[32] = {
&mdi_reg_0,
&mdi_reg_1,
&mdi_reg_2,
&mdi_reg_3,
&mdi_reg_4,
&mdi_reg_5,
&mdi_reg_6,
&mdi_reg_7,
&mdi_reg_8,
&mdi_reg_9,
&mdi_reg_10,
&mdi_reg_11,
&mdi_reg_12,
&mdi_reg_13,
&mdi_reg_14,
&mdi_reg_15,
&mdi_reg_16,
&mdi_reg_17,
&mdi_reg_18,
&mdi_reg_19,
&mdi_reg_20,
&mdi_reg_21,
&mdi_reg_22,
&mdi_reg_23,
&mdi_reg_24,
&mdi_reg_25,
&mdi_reg_26,
&mdi_reg_27,
&mdi_reg_28,
&mdi_reg_29,
&mdi_reg_30,
&mdi_reg_31,
};
struct reg_field * mdi_reg_field_info[140] = {
&mdi_reg_field_0,
&mdi_reg_field_1,
&mdi_reg_field_2,
&mdi_reg_field_3,
&mdi_reg_field_4,
&mdi_reg_field_5,
&mdi_reg_field_6,
&mdi_reg_field_7,
&mdi_reg_field_8,
&mdi_reg_field_9,
&mdi_reg_field_10,
&mdi_reg_field_11,
&mdi_reg_field_12,
&mdi_reg_field_13,
&mdi_reg_field_14,
&mdi_reg_field_15,
&mdi_reg_field_16,
&mdi_reg_field_17,
&mdi_reg_field_18,
&mdi_reg_field_19,
&mdi_reg_field_20,
&mdi_reg_field_21,
&mdi_reg_field_22,
&mdi_reg_field_23,
&mdi_reg_field_24,
&mdi_reg_field_25,
&mdi_reg_field_26,
&mdi_reg_field_27,
&mdi_reg_field_28,
&mdi_reg_field_29,
&mdi_reg_field_30,
&mdi_reg_field_31,
&mdi_reg_field_32,
&mdi_reg_field_33,
&mdi_reg_field_34,
&mdi_reg_field_35,
&mdi_reg_field_36,
&mdi_reg_field_37,
&mdi_reg_field_38,
&mdi_reg_field_39,
&mdi_reg_field_40,
&mdi_reg_field_41,
&mdi_reg_field_42,
&mdi_reg_field_43,
&mdi_reg_field_44,
&mdi_reg_field_45,
&mdi_reg_field_46,
&mdi_reg_field_47,
&mdi_reg_field_48,
&mdi_reg_field_49,
&mdi_reg_field_50,
&mdi_reg_field_51,
&mdi_reg_field_52,
&mdi_reg_field_53,
&mdi_reg_field_54,
&mdi_reg_field_55,
&mdi_reg_field_56,
&mdi_reg_field_57,
&mdi_reg_field_58,
&mdi_reg_field_59,
&mdi_reg_field_60,
&mdi_reg_field_61,
&mdi_reg_field_62,
&mdi_reg_field_63,
&mdi_reg_field_64,
&mdi_reg_field_65,
&mdi_reg_field_66,
&mdi_reg_field_67,
&mdi_reg_field_68,
&mdi_reg_field_69,
&mdi_reg_field_70,
&mdi_reg_field_71,
&mdi_reg_field_72,
&mdi_reg_field_73,
&mdi_reg_field_74,
&mdi_reg_field_75,
&mdi_reg_field_76,
&mdi_reg_field_77,
&mdi_reg_field_78,
&mdi_reg_field_79,
&mdi_reg_field_80,
&mdi_reg_field_81,
&mdi_reg_field_82,
&mdi_reg_field_83,
&mdi_reg_field_84,
&mdi_reg_field_85,
&mdi_reg_field_86,
&mdi_reg_field_87,
&mdi_reg_field_88,
&mdi_reg_field_89,
&mdi_reg_field_90,
&mdi_reg_field_91,
&mdi_reg_field_92,
&mdi_reg_field_93,
&mdi_reg_field_94,
&mdi_reg_field_95,
&mdi_reg_field_96,
&mdi_reg_field_97,
&mdi_reg_field_98,
&mdi_reg_field_99,
&mdi_reg_field_100,
&mdi_reg_field_101,
&mdi_reg_field_102,
&mdi_reg_field_103,
&mdi_reg_field_104,
&mdi_reg_field_105,
&mdi_reg_field_106,
&mdi_reg_field_107,
&mdi_reg_field_108,
&mdi_reg_field_109,
&mdi_reg_field_110,
&mdi_reg_field_111,
&mdi_reg_field_112,
&mdi_reg_field_113,
&mdi_reg_field_114,
&mdi_reg_field_115,
&mdi_reg_field_116,
&mdi_reg_field_117,
&mdi_reg_field_118,
&mdi_reg_field_119,
&mdi_reg_field_120,
&mdi_reg_field_121,
&mdi_reg_field_122,
&mdi_reg_field_123,
&mdi_reg_field_124,
&mdi_reg_field_125,
&mdi_reg_field_126,
&mdi_reg_field_127,
&mdi_reg_field_128,
&mdi_reg_field_129,
&mdi_reg_field_130,
&mdi_reg_field_131,
&mdi_reg_field_132,
&mdi_reg_field_133,
&mdi_reg_field_134,
&mdi_reg_field_135,
&mdi_reg_field_136,
&mdi_reg_field_137,
&mdi_reg_field_138,
&mdi_reg_field_139,
};
unsigned int mdi_reg_count = 32;
unsigned int mdi_reg_start = 0x8300;
unsigned int mdi_reg_end = 0x837c;
unsigned int mdi_reg_in_bytes = 0x4;
unsigned int mdi_reg_total_field_count = 140;
char * mdi_reg_block_name = "mdi";
