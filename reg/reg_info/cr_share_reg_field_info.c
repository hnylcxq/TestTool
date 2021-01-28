#include "../reg.h"

struct reg_field crs_reg_field_0 = {
	.name = "Vga_Ht",
	.bits_num = 8,
	.shift = 0,
	.reg_addr = 0x8800,
};
struct reg_info crs_reg_0 = {
	.reg_block_name = "crs",
	.reg_mmio_addr = 0x8800,
	.reg_sub_index = 0x0,
	.field_num = 1,
	.reg_in_bytes = 1,
};
struct reg_field crs_reg_field_1 = {
	.name = "Vga_Hde",
	.bits_num = 8,
	.shift = 0,
	.reg_addr = 0x8801,
};
struct reg_info crs_reg_1 = {
	.reg_block_name = "crs",
	.reg_mmio_addr = 0x8801,
	.reg_sub_index = 0x1,
	.field_num = 1,
	.reg_in_bytes = 1,
};
struct reg_field crs_reg_field_2 = {
	.name = "Vga_Shb",
	.bits_num = 8,
	.shift = 0,
	.reg_addr = 0x8802,
};
struct reg_info crs_reg_2 = {
	.reg_block_name = "crs",
	.reg_mmio_addr = 0x8802,
	.reg_sub_index = 0x2,
	.field_num = 1,
	.reg_in_bytes = 1,
};
struct reg_field crs_reg_field_3 = {
	.name = "Vga_Shb",
	.bits_num = 5,
	.shift = 0,
	.reg_addr = 0x8803,
};
struct reg_field crs_reg_field_4 = {
	.name = "Vga_Shb",
	.bits_num = 2,
	.shift = 5,
	.reg_addr = 0x8803,
};
struct reg_field crs_reg_field_5 = {
	.name = "Vga_Shb",
	.bits_num = 1,
	.shift = 7,
	.reg_addr = 0x8803,
};
struct reg_info crs_reg_3 = {
	.reg_block_name = "crs",
	.reg_mmio_addr = 0x8803,
	.reg_sub_index = 0x3,
	.field_num = 3,
	.reg_in_bytes = 1,
};
struct reg_field crs_reg_field_6 = {
	.name = "Vga_Shr",
	.bits_num = 8,
	.shift = 0,
	.reg_addr = 0x8804,
};
struct reg_info crs_reg_4 = {
	.reg_block_name = "crs",
	.reg_mmio_addr = 0x8804,
	.reg_sub_index = 0x4,
	.field_num = 1,
	.reg_in_bytes = 1,
};
struct reg_field crs_reg_field_7 = {
	.name = "Vga_Ehr",
	.bits_num = 5,
	.shift = 0,
	.reg_addr = 0x8805,
};
struct reg_field crs_reg_field_8 = {
	.name = "Vga_Hrd",
	.bits_num = 2,
	.shift = 5,
	.reg_addr = 0x8805,
};
struct reg_field crs_reg_field_9 = {
	.name = "Vga_Ehb_1",
	.bits_num = 1,
	.shift = 7,
	.reg_addr = 0x8805,
};
struct reg_info crs_reg_5 = {
	.reg_block_name = "crs",
	.reg_mmio_addr = 0x8805,
	.reg_sub_index = 0x5,
	.field_num = 3,
	.reg_in_bytes = 1,
};
struct reg_field crs_reg_field_10 = {
	.name = "Vga_Vt_0",
	.bits_num = 8,
	.shift = 0,
	.reg_addr = 0x8806,
};
struct reg_info crs_reg_6 = {
	.reg_block_name = "crs",
	.reg_mmio_addr = 0x8806,
	.reg_sub_index = 0x6,
	.field_num = 1,
	.reg_in_bytes = 1,
};
struct reg_field crs_reg_field_11 = {
	.name = "Vga_Vt_1",
	.bits_num = 1,
	.shift = 0,
	.reg_addr = 0x8807,
};
struct reg_field crs_reg_field_12 = {
	.name = "Vga_Vde_1",
	.bits_num = 1,
	.shift = 1,
	.reg_addr = 0x8807,
};
struct reg_field crs_reg_field_13 = {
	.name = "Vga_Vrs_1",
	.bits_num = 1,
	.shift = 2,
	.reg_addr = 0x8807,
};
struct reg_field crs_reg_field_14 = {
	.name = "Vga_Vbs_1",
	.bits_num = 1,
	.shift = 3,
	.reg_addr = 0x8807,
};
struct reg_field crs_reg_field_15 = {
	.name = "Vga_Lc_1",
	.bits_num = 1,
	.shift = 4,
	.reg_addr = 0x8807,
};
struct reg_field crs_reg_field_16 = {
	.name = "Vga_Vt_2",
	.bits_num = 1,
	.shift = 5,
	.reg_addr = 0x8807,
};
struct reg_field crs_reg_field_17 = {
	.name = "Vga_Vde_2",
	.bits_num = 1,
	.shift = 6,
	.reg_addr = 0x8807,
};
struct reg_field crs_reg_field_18 = {
	.name = "Vga_Vrs_2",
	.bits_num = 1,
	.shift = 7,
	.reg_addr = 0x8807,
};
struct reg_info crs_reg_7 = {
	.reg_block_name = "crs",
	.reg_mmio_addr = 0x8807,
	.reg_sub_index = 0x7,
	.field_num = 8,
	.reg_in_bytes = 1,
};
struct reg_field crs_reg_field_19 = {
	.name = "Vga_Prs",
	.bits_num = 5,
	.shift = 0,
	.reg_addr = 0x8808,
};
struct reg_field crs_reg_field_20 = {
	.name = "Vga_Bp",
	.bits_num = 2,
	.shift = 5,
	.reg_addr = 0x8808,
};
struct reg_field crs_reg_field_21 = {
	.name = "Reserved",
	.bits_num = 1,
	.shift = 7,
	.reg_addr = 0x8808,
};
struct reg_info crs_reg_8 = {
	.reg_block_name = "crs",
	.reg_mmio_addr = 0x8808,
	.reg_sub_index = 0x8,
	.field_num = 3,
	.reg_in_bytes = 1,
};
struct reg_field crs_reg_field_22 = {
	.name = "Vga_Msl",
	.bits_num = 5,
	.shift = 0,
	.reg_addr = 0x8809,
};
struct reg_field crs_reg_field_23 = {
	.name = "Vga_Vbs_2",
	.bits_num = 1,
	.shift = 5,
	.reg_addr = 0x8809,
};
struct reg_field crs_reg_field_24 = {
	.name = "Vga_Lc_2",
	.bits_num = 1,
	.shift = 6,
	.reg_addr = 0x8809,
};
struct reg_field crs_reg_field_25 = {
	.name = "Vga_2t4",
	.bits_num = 1,
	.shift = 7,
	.reg_addr = 0x8809,
};
struct reg_info crs_reg_9 = {
	.reg_block_name = "crs",
	.reg_mmio_addr = 0x8809,
	.reg_sub_index = 0x9,
	.field_num = 4,
	.reg_in_bytes = 1,
};
struct reg_field crs_reg_field_26 = {
	.name = "Vga_Cs",
	.bits_num = 5,
	.shift = 0,
	.reg_addr = 0x880a,
};
struct reg_field crs_reg_field_27 = {
	.name = "Vga_Coo",
	.bits_num = 1,
	.shift = 5,
	.reg_addr = 0x880a,
};
struct reg_field crs_reg_field_28 = {
	.name = "Reserved",
	.bits_num = 2,
	.shift = 6,
	.reg_addr = 0x880a,
};
struct reg_info crs_reg_10 = {
	.reg_block_name = "crs",
	.reg_mmio_addr = 0x880a,
	.reg_sub_index = 0xa,
	.field_num = 3,
	.reg_in_bytes = 1,
};
struct reg_field crs_reg_field_29 = {
	.name = "Vga_Ce",
	.bits_num = 5,
	.shift = 0,
	.reg_addr = 0x880b,
};
struct reg_field crs_reg_field_30 = {
	.name = "Vga_Csk",
	.bits_num = 2,
	.shift = 5,
	.reg_addr = 0x880b,
};
struct reg_field crs_reg_field_31 = {
	.name = "Reserved",
	.bits_num = 1,
	.shift = 7,
	.reg_addr = 0x880b,
};
struct reg_info crs_reg_11 = {
	.reg_block_name = "crs",
	.reg_mmio_addr = 0x880b,
	.reg_sub_index = 0xb,
	.field_num = 3,
	.reg_in_bytes = 1,
};
struct reg_field crs_reg_field_32 = {
	.name = "Vga_Sa_1",
	.bits_num = 8,
	.shift = 0,
	.reg_addr = 0x880c,
};
struct reg_info crs_reg_12 = {
	.reg_block_name = "crs",
	.reg_mmio_addr = 0x880c,
	.reg_sub_index = 0xc,
	.field_num = 1,
	.reg_in_bytes = 1,
};
struct reg_field crs_reg_field_33 = {
	.name = "Vga_Sa_0",
	.bits_num = 8,
	.shift = 0,
	.reg_addr = 0x880d,
};
struct reg_info crs_reg_13 = {
	.reg_block_name = "crs",
	.reg_mmio_addr = 0x880d,
	.reg_sub_index = 0xd,
	.field_num = 1,
	.reg_in_bytes = 1,
};
struct reg_field crs_reg_field_34 = {
	.name = "Vga_Cl_1",
	.bits_num = 8,
	.shift = 0,
	.reg_addr = 0x880e,
};
struct reg_info crs_reg_14 = {
	.reg_block_name = "crs",
	.reg_mmio_addr = 0x880e,
	.reg_sub_index = 0xe,
	.field_num = 1,
	.reg_in_bytes = 1,
};
struct reg_field crs_reg_field_35 = {
	.name = "Vga_Cl_0",
	.bits_num = 8,
	.shift = 0,
	.reg_addr = 0x880f,
};
struct reg_info crs_reg_15 = {
	.reg_block_name = "crs",
	.reg_mmio_addr = 0x880f,
	.reg_sub_index = 0xf,
	.field_num = 1,
	.reg_in_bytes = 1,
};
struct reg_field crs_reg_field_36 = {
	.name = "Vga_Vrs_0",
	.bits_num = 8,
	.shift = 0,
	.reg_addr = 0x8810,
};
struct reg_info crs_reg_16 = {
	.reg_block_name = "crs",
	.reg_mmio_addr = 0x8810,
	.reg_sub_index = 0x10,
	.field_num = 1,
	.reg_in_bytes = 1,
};
struct reg_field crs_reg_field_37 = {
	.name = "Vga_Evr",
	.bits_num = 4,
	.shift = 0,
	.reg_addr = 0x8811,
};
struct reg_field crs_reg_field_38 = {
	.name = "Vga_Cvi",
	.bits_num = 1,
	.shift = 4,
	.reg_addr = 0x8811,
};
struct reg_field crs_reg_field_39 = {
	.name = "Vga_Dvi",
	.bits_num = 1,
	.shift = 5,
	.reg_addr = 0x8811,
};
struct reg_field crs_reg_field_40 = {
	.name = "Vga_Bw",
	.bits_num = 1,
	.shift = 6,
	.reg_addr = 0x8811,
};
struct reg_field crs_reg_field_41 = {
	.name = "Vga_Pr",
	.bits_num = 1,
	.shift = 7,
	.reg_addr = 0x8811,
};
struct reg_info crs_reg_17 = {
	.reg_block_name = "crs",
	.reg_mmio_addr = 0x8811,
	.reg_sub_index = 0x11,
	.field_num = 5,
	.reg_in_bytes = 1,
};
struct reg_field crs_reg_field_42 = {
	.name = "Vga_Vde_0",
	.bits_num = 8,
	.shift = 0,
	.reg_addr = 0x8812,
};
struct reg_info crs_reg_18 = {
	.reg_block_name = "crs",
	.reg_mmio_addr = 0x8812,
	.reg_sub_index = 0x12,
	.field_num = 1,
	.reg_in_bytes = 1,
};
struct reg_field crs_reg_field_43 = {
	.name = "Vga_Off",
	.bits_num = 8,
	.shift = 0,
	.reg_addr = 0x8813,
};
struct reg_info crs_reg_19 = {
	.reg_block_name = "crs",
	.reg_mmio_addr = 0x8813,
	.reg_sub_index = 0x13,
	.field_num = 1,
	.reg_in_bytes = 1,
};
struct reg_field crs_reg_field_44 = {
	.name = "Vga_Ul",
	.bits_num = 5,
	.shift = 0,
	.reg_addr = 0x8814,
};
struct reg_field crs_reg_field_45 = {
	.name = "Vga_Cb4",
	.bits_num = 1,
	.shift = 5,
	.reg_addr = 0x8814,
};
struct reg_field crs_reg_field_46 = {
	.name = "Vga_Dw",
	.bits_num = 1,
	.shift = 6,
	.reg_addr = 0x8814,
};
struct reg_field crs_reg_field_47 = {
	.name = "Reserved",
	.bits_num = 1,
	.shift = 7,
	.reg_addr = 0x8814,
};
struct reg_info crs_reg_20 = {
	.reg_block_name = "crs",
	.reg_mmio_addr = 0x8814,
	.reg_sub_index = 0x14,
	.field_num = 4,
	.reg_in_bytes = 1,
};
struct reg_field crs_reg_field_48 = {
	.name = "Vga_Vbs_0",
	.bits_num = 8,
	.shift = 0,
	.reg_addr = 0x8815,
};
struct reg_info crs_reg_21 = {
	.reg_block_name = "crs",
	.reg_mmio_addr = 0x8815,
	.reg_sub_index = 0x15,
	.field_num = 1,
	.reg_in_bytes = 1,
};
struct reg_field crs_reg_field_49 = {
	.name = "Vga_Vbe",
	.bits_num = 8,
	.shift = 0,
	.reg_addr = 0x8816,
};
struct reg_info crs_reg_22 = {
	.reg_block_name = "crs",
	.reg_mmio_addr = 0x8816,
	.reg_sub_index = 0x16,
	.field_num = 1,
	.reg_in_bytes = 1,
};
struct reg_field crs_reg_field_50 = {
	.name = "Vga_Cms",
	.bits_num = 1,
	.shift = 0,
	.reg_addr = 0x8817,
};
struct reg_field crs_reg_field_51 = {
	.name = "Vga_Srsc",
	.bits_num = 1,
	.shift = 1,
	.reg_addr = 0x8817,
};
struct reg_field crs_reg_field_52 = {
	.name = "Vga_Hrs",
	.bits_num = 1,
	.shift = 2,
	.reg_addr = 0x8817,
};
struct reg_field crs_reg_field_53 = {
	.name = "Vga_Cbt",
	.bits_num = 1,
	.shift = 3,
	.reg_addr = 0x8817,
};
struct reg_field crs_reg_field_54 = {
	.name = "Vga_Oc",
	.bits_num = 1,
	.shift = 4,
	.reg_addr = 0x8817,
};
struct reg_field crs_reg_field_55 = {
	.name = "Vga_Aw",
	.bits_num = 1,
	.shift = 5,
	.reg_addr = 0x8817,
};
struct reg_field crs_reg_field_56 = {
	.name = "Vga_Wb",
	.bits_num = 1,
	.shift = 6,
	.reg_addr = 0x8817,
};
struct reg_field crs_reg_field_57 = {
	.name = "Vga_Hr",
	.bits_num = 1,
	.shift = 7,
	.reg_addr = 0x8817,
};
struct reg_info crs_reg_23 = {
	.reg_block_name = "crs",
	.reg_mmio_addr = 0x8817,
	.reg_sub_index = 0x17,
	.field_num = 8,
	.reg_in_bytes = 1,
};
struct reg_field crs_reg_field_58 = {
	.name = "Vga_Lc_0",
	.bits_num = 8,
	.shift = 0,
	.reg_addr = 0x8818,
};
struct reg_info crs_reg_24 = {
	.reg_block_name = "crs",
	.reg_mmio_addr = 0x8818,
	.reg_sub_index = 0x18,
	.field_num = 1,
	.reg_in_bytes = 1,
};
struct reg_field crs_reg_field_59 = {
	.name = "Dac_Lock",
	.bits_num = 1,
	.shift = 0,
	.reg_addr = 0x8819,
};
struct reg_field crs_reg_field_60 = {
	.name = "Lock_Sr01_B0",
	.bits_num = 1,
	.shift = 1,
	.reg_addr = 0x8819,
};
struct reg_field crs_reg_field_61 = {
	.name = "Lock_Srgr",
	.bits_num = 1,
	.shift = 2,
	.reg_addr = 0x8819,
};
struct reg_field crs_reg_field_62 = {
	.name = "Lock_Vde_H",
	.bits_num = 1,
	.shift = 3,
	.reg_addr = 0x8819,
};
struct reg_field crs_reg_field_63 = {
	.name = "Lock_Vde",
	.bits_num = 1,
	.shift = 4,
	.reg_addr = 0x8819,
};
struct reg_field crs_reg_field_64 = {
	.name = "Lock_Hde",
	.bits_num = 1,
	.shift = 5,
	.reg_addr = 0x8819,
};
struct reg_field crs_reg_field_65 = {
	.name = "Lock_Vp",
	.bits_num = 1,
	.shift = 6,
	.reg_addr = 0x8819,
};
struct reg_field crs_reg_field_66 = {
	.name = "Lock_Hp",
	.bits_num = 1,
	.shift = 7,
	.reg_addr = 0x8819,
};
struct reg_info crs_reg_25 = {
	.reg_block_name = "crs",
	.reg_mmio_addr = 0x8819,
	.reg_sub_index = 0x19,
	.field_num = 8,
	.reg_in_bytes = 1,
};
struct reg_field crs_reg_field_67 = {
	.name = "Reserved",
	.bits_num = 5,
	.shift = 0,
	.reg_addr = 0x881a,
};
struct reg_field crs_reg_field_68 = {
	.name = "Vga_Palette_Lock",
	.bits_num = 1,
	.shift = 5,
	.reg_addr = 0x881a,
};
struct reg_field crs_reg_field_69 = {
	.name = "Vga_Freq_Lock",
	.bits_num = 1,
	.shift = 6,
	.reg_addr = 0x881a,
};
struct reg_field crs_reg_field_70 = {
	.name = "Vga_Vsp_En",
	.bits_num = 1,
	.shift = 7,
	.reg_addr = 0x881a,
};
struct reg_info crs_reg_26 = {
	.reg_block_name = "crs",
	.reg_mmio_addr = 0x881a,
	.reg_sub_index = 0x1a,
	.field_num = 4,
	.reg_in_bytes = 1,
};
struct reg_field crs_reg_field_71 = {
	.name = "Vga_Sa_2",
	.bits_num = 8,
	.shift = 0,
	.reg_addr = 0x881b,
};
struct reg_info crs_reg_27 = {
	.reg_block_name = "crs",
	.reg_mmio_addr = 0x881b,
	.reg_sub_index = 0x1b,
	.field_num = 1,
	.reg_in_bytes = 1,
};
struct reg_field crs_reg_field_72 = {
	.name = "Vga_Sa_3",
	.bits_num = 8,
	.shift = 0,
	.reg_addr = 0x881c,
};
struct reg_info crs_reg_28 = {
	.reg_block_name = "crs",
	.reg_mmio_addr = 0x881c,
	.reg_sub_index = 0x1c,
	.field_num = 1,
	.reg_in_bytes = 1,
};
struct reg_field crs_reg_field_73 = {
	.name = "Slot_Num_0",
	.bits_num = 8,
	.shift = 0,
	.reg_addr = 0x881d,
};
struct reg_info crs_reg_29 = {
	.reg_block_name = "crs",
	.reg_mmio_addr = 0x881d,
	.reg_sub_index = 0x1d,
	.field_num = 1,
	.reg_in_bytes = 1,
};
struct reg_field crs_reg_field_74 = {
	.name = "Vga_Sa_4",
	.bits_num = 2,
	.shift = 0,
	.reg_addr = 0x881e,
};
struct reg_field crs_reg_field_75 = {
	.name = "Reserved",
	.bits_num = 2,
	.shift = 2,
	.reg_addr = 0x881e,
};
struct reg_field crs_reg_field_76 = {
	.name = "Slot_Num_1",
	.bits_num = 4,
	.shift = 4,
	.reg_addr = 0x881e,
};
struct reg_info crs_reg_30 = {
	.reg_block_name = "crs",
	.reg_mmio_addr = 0x881e,
	.reg_sub_index = 0x1e,
	.field_num = 3,
	.reg_in_bytes = 1,
};
struct reg_field crs_reg_field_77 = {
	.name = "Cr_Unlock",
	.bits_num = 8,
	.shift = 0,
	.reg_addr = 0x881f,
};
struct reg_info crs_reg_31 = {
	.reg_block_name = "crs",
	.reg_mmio_addr = 0x881f,
	.reg_sub_index = 0x1f,
	.field_num = 1,
	.reg_in_bytes = 1,
};
struct reg_field crs_reg_field_78 = {
	.name = "Vga_Hsftw",
	.bits_num = 1,
	.shift = 0,
	.reg_addr = 0x8820,
};
struct reg_field crs_reg_field_79 = {
	.name = "Vga_Tme",
	.bits_num = 1,
	.shift = 1,
	.reg_addr = 0x8820,
};
struct reg_field crs_reg_field_80 = {
	.name = "Vga_Hspd",
	.bits_num = 1,
	.shift = 2,
	.reg_addr = 0x8820,
};
struct reg_field crs_reg_field_81 = {
	.name = "Vga_Enhmm",
	.bits_num = 1,
	.shift = 3,
	.reg_addr = 0x8820,
};
struct reg_field crs_reg_field_82 = {
	.name = "Vga_Adbase",
	.bits_num = 1,
	.shift = 4,
	.reg_addr = 0x8820,
};
struct reg_field crs_reg_field_83 = {
	.name = "Vga_Whostd",
	.bits_num = 1,
	.shift = 5,
	.reg_addr = 0x8820,
};
struct reg_field crs_reg_field_84 = {
	.name = "Vga_Lndaten",
	.bits_num = 1,
	.shift = 6,
	.reg_addr = 0x8820,
};
struct reg_field crs_reg_field_85 = {
	.name = "Vga_Laen",
	.bits_num = 1,
	.shift = 7,
	.reg_addr = 0x8820,
};
struct reg_info crs_reg_32 = {
	.reg_block_name = "crs",
	.reg_mmio_addr = 0x8820,
	.reg_sub_index = 0x20,
	.field_num = 8,
	.reg_in_bytes = 1,
};
struct reg_field crs_reg_field_86 = {
	.name = "Vga_Base_0",
	.bits_num = 8,
	.shift = 0,
	.reg_addr = 0x8821,
};
struct reg_info crs_reg_33 = {
	.reg_block_name = "crs",
	.reg_mmio_addr = 0x8821,
	.reg_sub_index = 0x21,
	.field_num = 1,
	.reg_in_bytes = 1,
};
struct reg_field crs_reg_field_87 = {
	.name = "Vga_Base_1",
	.bits_num = 8,
	.shift = 0,
	.reg_addr = 0x8822,
};
struct reg_info crs_reg_34 = {
	.reg_block_name = "crs",
	.reg_mmio_addr = 0x8822,
	.reg_sub_index = 0x22,
	.field_num = 1,
	.reg_in_bytes = 1,
};
struct reg_field crs_reg_field_88 = {
	.name = "Vga_Base_2",
	.bits_num = 6,
	.shift = 0,
	.reg_addr = 0x8823,
};
struct reg_field crs_reg_field_89 = {
	.name = "Reserved",
	.bits_num = 2,
	.shift = 6,
	.reg_addr = 0x8823,
};
struct reg_info crs_reg_35 = {
	.reg_block_name = "crs",
	.reg_mmio_addr = 0x8823,
	.reg_sub_index = 0x23,
	.field_num = 2,
	.reg_in_bytes = 1,
};
struct reg_field crs_reg_field_90 = {
	.name = "Vga_Enable",
	.bits_num = 1,
	.shift = 0,
	.reg_addr = 0x8824,
};
struct reg_field crs_reg_field_91 = {
	.name = "Vga_16bmp",
	.bits_num = 1,
	.shift = 1,
	.reg_addr = 0x8824,
};
struct reg_field crs_reg_field_92 = {
	.name = "Reserved",
	.bits_num = 6,
	.shift = 2,
	.reg_addr = 0x8824,
};
struct reg_info crs_reg_36 = {
	.reg_block_name = "crs",
	.reg_mmio_addr = 0x8824,
	.reg_sub_index = 0x24,
	.field_num = 3,
	.reg_in_bytes = 1,
};
struct reg_info * crs_reg_info[37] = {
&crs_reg_0,
&crs_reg_1,
&crs_reg_2,
&crs_reg_3,
&crs_reg_4,
&crs_reg_5,
&crs_reg_6,
&crs_reg_7,
&crs_reg_8,
&crs_reg_9,
&crs_reg_10,
&crs_reg_11,
&crs_reg_12,
&crs_reg_13,
&crs_reg_14,
&crs_reg_15,
&crs_reg_16,
&crs_reg_17,
&crs_reg_18,
&crs_reg_19,
&crs_reg_20,
&crs_reg_21,
&crs_reg_22,
&crs_reg_23,
&crs_reg_24,
&crs_reg_25,
&crs_reg_26,
&crs_reg_27,
&crs_reg_28,
&crs_reg_29,
&crs_reg_30,
&crs_reg_31,
&crs_reg_32,
&crs_reg_33,
&crs_reg_34,
&crs_reg_35,
&crs_reg_36,
};
struct reg_field * crs_reg_field_info[93] = {
&crs_reg_field_0,
&crs_reg_field_1,
&crs_reg_field_2,
&crs_reg_field_3,
&crs_reg_field_4,
&crs_reg_field_5,
&crs_reg_field_6,
&crs_reg_field_7,
&crs_reg_field_8,
&crs_reg_field_9,
&crs_reg_field_10,
&crs_reg_field_11,
&crs_reg_field_12,
&crs_reg_field_13,
&crs_reg_field_14,
&crs_reg_field_15,
&crs_reg_field_16,
&crs_reg_field_17,
&crs_reg_field_18,
&crs_reg_field_19,
&crs_reg_field_20,
&crs_reg_field_21,
&crs_reg_field_22,
&crs_reg_field_23,
&crs_reg_field_24,
&crs_reg_field_25,
&crs_reg_field_26,
&crs_reg_field_27,
&crs_reg_field_28,
&crs_reg_field_29,
&crs_reg_field_30,
&crs_reg_field_31,
&crs_reg_field_32,
&crs_reg_field_33,
&crs_reg_field_34,
&crs_reg_field_35,
&crs_reg_field_36,
&crs_reg_field_37,
&crs_reg_field_38,
&crs_reg_field_39,
&crs_reg_field_40,
&crs_reg_field_41,
&crs_reg_field_42,
&crs_reg_field_43,
&crs_reg_field_44,
&crs_reg_field_45,
&crs_reg_field_46,
&crs_reg_field_47,
&crs_reg_field_48,
&crs_reg_field_49,
&crs_reg_field_50,
&crs_reg_field_51,
&crs_reg_field_52,
&crs_reg_field_53,
&crs_reg_field_54,
&crs_reg_field_55,
&crs_reg_field_56,
&crs_reg_field_57,
&crs_reg_field_58,
&crs_reg_field_59,
&crs_reg_field_60,
&crs_reg_field_61,
&crs_reg_field_62,
&crs_reg_field_63,
&crs_reg_field_64,
&crs_reg_field_65,
&crs_reg_field_66,
&crs_reg_field_67,
&crs_reg_field_68,
&crs_reg_field_69,
&crs_reg_field_70,
&crs_reg_field_71,
&crs_reg_field_72,
&crs_reg_field_73,
&crs_reg_field_74,
&crs_reg_field_75,
&crs_reg_field_76,
&crs_reg_field_77,
&crs_reg_field_78,
&crs_reg_field_79,
&crs_reg_field_80,
&crs_reg_field_81,
&crs_reg_field_82,
&crs_reg_field_83,
&crs_reg_field_84,
&crs_reg_field_85,
&crs_reg_field_86,
&crs_reg_field_87,
&crs_reg_field_88,
&crs_reg_field_89,
&crs_reg_field_90,
&crs_reg_field_91,
&crs_reg_field_92,
};
unsigned int crs_reg_count = 37;
unsigned int crs_reg_start = 0x8800;
unsigned int crs_reg_end = 0x8824;
unsigned int crs_reg_in_bytes = 0x1;
unsigned int crs_reg_total_field_count = 93;
char * crs_reg_block_name = "crs";
