#include "../reg.h"

struct reg_field sr_reg_field_0 = {
	.name = "Vga_Arsr",
	.bits_num = 1,
	.shift = 0,
	.reg_addr = 0x8600,
};
struct reg_field sr_reg_field_1 = {
	.name = "Vga_Sr",
	.bits_num = 1,
	.shift = 1,
	.reg_addr = 0x8600,
};
struct reg_field sr_reg_field_2 = {
	.name = "Reserved",
	.bits_num = 6,
	.shift = 2,
	.reg_addr = 0x8600,
};
struct reg_info sr_reg_0 = {
	.reg_block_name = "sr",
	.reg_mmio_addr = 0x8600,
	.reg_sub_index = 0x0,
	.field_num = 3,
	.reg_in_bytes = 1,
};
struct reg_field sr_reg_field_3 = {
	.name = "Vga_8dot",
	.bits_num = 1,
	.shift = 0,
	.reg_addr = 0x8601,
};
struct reg_field sr_reg_field_4 = {
	.name = "Vga_Bw_Reserve",
	.bits_num = 1,
	.shift = 1,
	.reg_addr = 0x8601,
};
struct reg_field sr_reg_field_5 = {
	.name = "Vga_Sl",
	.bits_num = 1,
	.shift = 2,
	.reg_addr = 0x8601,
};
struct reg_field sr_reg_field_6 = {
	.name = "Vga_Dc",
	.bits_num = 1,
	.shift = 3,
	.reg_addr = 0x8601,
};
struct reg_field sr_reg_field_7 = {
	.name = "Vga_S4",
	.bits_num = 1,
	.shift = 4,
	.reg_addr = 0x8601,
};
struct reg_field sr_reg_field_8 = {
	.name = "Vga_So",
	.bits_num = 1,
	.shift = 5,
	.reg_addr = 0x8601,
};
struct reg_field sr_reg_field_9 = {
	.name = "Reserved",
	.bits_num = 2,
	.shift = 6,
	.reg_addr = 0x8601,
};
struct reg_info sr_reg_1 = {
	.reg_block_name = "sr",
	.reg_mmio_addr = 0x8601,
	.reg_sub_index = 0x1,
	.field_num = 7,
	.reg_in_bytes = 1,
};
struct reg_field sr_reg_field_10 = {
	.name = "Vga_Mmp",
	.bits_num = 4,
	.shift = 0,
	.reg_addr = 0x8602,
};
struct reg_field sr_reg_field_11 = {
	.name = "Reserved",
	.bits_num = 4,
	.shift = 4,
	.reg_addr = 0x8602,
};
struct reg_info sr_reg_2 = {
	.reg_block_name = "sr",
	.reg_mmio_addr = 0x8602,
	.reg_sub_index = 0x2,
	.field_num = 2,
	.reg_in_bytes = 1,
};
struct reg_field sr_reg_field_12 = {
	.name = "Vga_Scb",
	.bits_num = 2,
	.shift = 0,
	.reg_addr = 0x8603,
};
struct reg_field sr_reg_field_13 = {
	.name = "Vga_Sca",
	.bits_num = 2,
	.shift = 2,
	.reg_addr = 0x8603,
};
struct reg_field sr_reg_field_14 = {
	.name = "Vga_Scbh",
	.bits_num = 1,
	.shift = 4,
	.reg_addr = 0x8603,
};
struct reg_field sr_reg_field_15 = {
	.name = "Vga_Scah",
	.bits_num = 1,
	.shift = 5,
	.reg_addr = 0x8603,
};
struct reg_field sr_reg_field_16 = {
	.name = "Reserved",
	.bits_num = 2,
	.shift = 6,
	.reg_addr = 0x8603,
};
struct reg_info sr_reg_3 = {
	.reg_block_name = "sr",
	.reg_mmio_addr = 0x8603,
	.reg_sub_index = 0x3,
	.field_num = 5,
	.reg_in_bytes = 1,
};
struct reg_field sr_reg_field_17 = {
	.name = "Vga_Ag",
	.bits_num = 1,
	.shift = 0,
	.reg_addr = 0x8604,
};
struct reg_field sr_reg_field_18 = {
	.name = "Vga_Em",
	.bits_num = 1,
	.shift = 1,
	.reg_addr = 0x8604,
};
struct reg_field sr_reg_field_19 = {
	.name = "Vga_Oe",
	.bits_num = 1,
	.shift = 2,
	.reg_addr = 0x8604,
};
struct reg_field sr_reg_field_20 = {
	.name = "Vga_C4",
	.bits_num = 1,
	.shift = 3,
	.reg_addr = 0x8604,
};
struct reg_field sr_reg_field_21 = {
	.name = "Reserved",
	.bits_num = 4,
	.shift = 4,
	.reg_addr = 0x8604,
};
struct reg_info sr_reg_4 = {
	.reg_block_name = "sr",
	.reg_mmio_addr = 0x8604,
	.reg_sub_index = 0x4,
	.field_num = 5,
	.reg_in_bytes = 1,
};
struct reg_field sr_reg_field_22 = {
	.name = "Reserved",
	.bits_num = 8,
	.shift = 0,
	.reg_addr = 0x8605,
};
struct reg_info sr_reg_5 = {
	.reg_block_name = "sr",
	.reg_mmio_addr = 0x8605,
	.reg_sub_index = 0x5,
	.field_num = 1,
	.reg_in_bytes = 1,
};
struct reg_field sr_reg_field_23 = {
	.name = "Reserved",
	.bits_num = 8,
	.shift = 0,
	.reg_addr = 0x8606,
};
struct reg_info sr_reg_6 = {
	.reg_block_name = "sr",
	.reg_mmio_addr = 0x8606,
	.reg_sub_index = 0x6,
	.field_num = 1,
	.reg_in_bytes = 1,
};
struct reg_field sr_reg_field_24 = {
	.name = "Reserved",
	.bits_num = 8,
	.shift = 0,
	.reg_addr = 0x8607,
};
struct reg_info sr_reg_7 = {
	.reg_block_name = "sr",
	.reg_mmio_addr = 0x8607,
	.reg_sub_index = 0x7,
	.field_num = 1,
	.reg_in_bytes = 1,
};
struct reg_field sr_reg_field_25 = {
	.name = "Htotal_0",
	.bits_num = 8,
	.shift = 0,
	.reg_addr = 0x8608,
};
struct reg_info sr_reg_8 = {
	.reg_block_name = "sr",
	.reg_mmio_addr = 0x8608,
	.reg_sub_index = 0x8,
	.field_num = 1,
	.reg_in_bytes = 1,
};
struct reg_field sr_reg_field_26 = {
	.name = "Htotal_1",
	.bits_num = 6,
	.shift = 0,
	.reg_addr = 0x8609,
};
struct reg_field sr_reg_field_27 = {
	.name = "Reserved",
	.bits_num = 2,
	.shift = 6,
	.reg_addr = 0x8609,
};
struct reg_info sr_reg_9 = {
	.reg_block_name = "sr",
	.reg_mmio_addr = 0x8609,
	.reg_sub_index = 0x9,
	.field_num = 2,
	.reg_in_bytes = 1,
};
struct reg_field sr_reg_field_28 = {
	.name = "Hde_0",
	.bits_num = 8,
	.shift = 0,
	.reg_addr = 0x860a,
};
struct reg_info sr_reg_10 = {
	.reg_block_name = "sr",
	.reg_mmio_addr = 0x860a,
	.reg_sub_index = 0xa,
	.field_num = 1,
	.reg_in_bytes = 1,
};
struct reg_field sr_reg_field_29 = {
	.name = "Hde_1",
	.bits_num = 6,
	.shift = 0,
	.reg_addr = 0x860b,
};
struct reg_field sr_reg_field_30 = {
	.name = "Reserved",
	.bits_num = 2,
	.shift = 6,
	.reg_addr = 0x860b,
};
struct reg_info sr_reg_11 = {
	.reg_block_name = "sr",
	.reg_mmio_addr = 0x860b,
	.reg_sub_index = 0xb,
	.field_num = 2,
	.reg_in_bytes = 1,
};
struct reg_field sr_reg_field_31 = {
	.name = "Hblk_Beg_0",
	.bits_num = 8,
	.shift = 0,
	.reg_addr = 0x860c,
};
struct reg_info sr_reg_12 = {
	.reg_block_name = "sr",
	.reg_mmio_addr = 0x860c,
	.reg_sub_index = 0xc,
	.field_num = 1,
	.reg_in_bytes = 1,
};
struct reg_field sr_reg_field_32 = {
	.name = "Hblk_End_1",
	.bits_num = 6,
	.shift = 0,
	.reg_addr = 0x860d,
};
struct reg_field sr_reg_field_33 = {
	.name = "Hblk_Beg_1",
	.bits_num = 2,
	.shift = 6,
	.reg_addr = 0x860d,
};
struct reg_info sr_reg_13 = {
	.reg_block_name = "sr",
	.reg_mmio_addr = 0x860d,
	.reg_sub_index = 0xd,
	.field_num = 2,
	.reg_in_bytes = 1,
};
struct reg_field sr_reg_field_34 = {
	.name = "Hblk_End_0",
	.bits_num = 8,
	.shift = 0,
	.reg_addr = 0x860e,
};
struct reg_info sr_reg_14 = {
	.reg_block_name = "sr",
	.reg_mmio_addr = 0x860e,
	.reg_sub_index = 0xe,
	.field_num = 1,
	.reg_in_bytes = 1,
};
struct reg_field sr_reg_field_35 = {
	.name = "Hsync_Beg_0",
	.bits_num = 8,
	.shift = 0,
	.reg_addr = 0x860f,
};
struct reg_info sr_reg_15 = {
	.reg_block_name = "sr",
	.reg_mmio_addr = 0x860f,
	.reg_sub_index = 0xf,
	.field_num = 1,
	.reg_in_bytes = 1,
};
struct reg_field sr_reg_field_36 = {
	.name = "Hsync_End_1",
	.bits_num = 2,
	.shift = 0,
	.reg_addr = 0x8610,
};
struct reg_field sr_reg_field_37 = {
	.name = "Hsync_Beg_1",
	.bits_num = 6,
	.shift = 2,
	.reg_addr = 0x8610,
};
struct reg_info sr_reg_16 = {
	.reg_block_name = "sr",
	.reg_mmio_addr = 0x8610,
	.reg_sub_index = 0x10,
	.field_num = 2,
	.reg_in_bytes = 1,
};
struct reg_field sr_reg_field_38 = {
	.name = "Hsync_End_0",
	.bits_num = 8,
	.shift = 0,
	.reg_addr = 0x8611,
};
struct reg_info sr_reg_17 = {
	.reg_block_name = "sr",
	.reg_mmio_addr = 0x8611,
	.reg_sub_index = 0x11,
	.field_num = 1,
	.reg_in_bytes = 1,
};
struct reg_field sr_reg_field_39 = {
	.name = "Vtotal_0",
	.bits_num = 8,
	.shift = 0,
	.reg_addr = 0x8612,
};
struct reg_info sr_reg_18 = {
	.reg_block_name = "sr",
	.reg_mmio_addr = 0x8612,
	.reg_sub_index = 0x12,
	.field_num = 1,
	.reg_in_bytes = 1,
};
struct reg_field sr_reg_field_40 = {
	.name = "Vtotal_1",
	.bits_num = 5,
	.shift = 0,
	.reg_addr = 0x8613,
};
struct reg_field sr_reg_field_41 = {
	.name = "Reserved",
	.bits_num = 3,
	.shift = 5,
	.reg_addr = 0x8613,
};
struct reg_info sr_reg_19 = {
	.reg_block_name = "sr",
	.reg_mmio_addr = 0x8613,
	.reg_sub_index = 0x13,
	.field_num = 2,
	.reg_in_bytes = 1,
};
struct reg_field sr_reg_field_42 = {
	.name = "Vde_0",
	.bits_num = 8,
	.shift = 0,
	.reg_addr = 0x8614,
};
struct reg_info sr_reg_20 = {
	.reg_block_name = "sr",
	.reg_mmio_addr = 0x8614,
	.reg_sub_index = 0x14,
	.field_num = 1,
	.reg_in_bytes = 1,
};
struct reg_field sr_reg_field_43 = {
	.name = "Vde_1",
	.bits_num = 5,
	.shift = 0,
	.reg_addr = 0x8615,
};
struct reg_field sr_reg_field_44 = {
	.name = "Reserved",
	.bits_num = 3,
	.shift = 5,
	.reg_addr = 0x8615,
};
struct reg_info sr_reg_21 = {
	.reg_block_name = "sr",
	.reg_mmio_addr = 0x8615,
	.reg_sub_index = 0x15,
	.field_num = 2,
	.reg_in_bytes = 1,
};
struct reg_field sr_reg_field_45 = {
	.name = "Vblk_Beg_0",
	.bits_num = 8,
	.shift = 0,
	.reg_addr = 0x8616,
};
struct reg_info sr_reg_22 = {
	.reg_block_name = "sr",
	.reg_mmio_addr = 0x8616,
	.reg_sub_index = 0x16,
	.field_num = 1,
	.reg_in_bytes = 1,
};
struct reg_field sr_reg_field_46 = {
	.name = "Vblk_End_1",
	.bits_num = 1,
	.shift = 0,
	.reg_addr = 0x8617,
};
struct reg_field sr_reg_field_47 = {
	.name = "Reserved",
	.bits_num = 2,
	.shift = 1,
	.reg_addr = 0x8617,
};
struct reg_field sr_reg_field_48 = {
	.name = "Vblk_Beg_1",
	.bits_num = 5,
	.shift = 3,
	.reg_addr = 0x8617,
};
struct reg_info sr_reg_23 = {
	.reg_block_name = "sr",
	.reg_mmio_addr = 0x8617,
	.reg_sub_index = 0x17,
	.field_num = 3,
	.reg_in_bytes = 1,
};
struct reg_field sr_reg_field_49 = {
	.name = "Vblk_End_0",
	.bits_num = 8,
	.shift = 0,
	.reg_addr = 0x8618,
};
struct reg_info sr_reg_24 = {
	.reg_block_name = "sr",
	.reg_mmio_addr = 0x8618,
	.reg_sub_index = 0x18,
	.field_num = 1,
	.reg_in_bytes = 1,
};
struct reg_field sr_reg_field_50 = {
	.name = "Vsync_Beg_0",
	.bits_num = 8,
	.shift = 0,
	.reg_addr = 0x8619,
};
struct reg_info sr_reg_25 = {
	.reg_block_name = "sr",
	.reg_mmio_addr = 0x8619,
	.reg_sub_index = 0x19,
	.field_num = 1,
	.reg_in_bytes = 1,
};
struct reg_field sr_reg_field_51 = {
	.name = "Reserved",
	.bits_num = 3,
	.shift = 0,
	.reg_addr = 0x861a,
};
struct reg_field sr_reg_field_52 = {
	.name = "Vsync_Beg_1",
	.bits_num = 5,
	.shift = 3,
	.reg_addr = 0x861a,
};
struct reg_info sr_reg_26 = {
	.reg_block_name = "sr",
	.reg_mmio_addr = 0x861a,
	.reg_sub_index = 0x1a,
	.field_num = 2,
	.reg_in_bytes = 1,
};
struct reg_field sr_reg_field_53 = {
	.name = "Reserved",
	.bits_num = 2,
	.shift = 0,
	.reg_addr = 0x861b,
};
struct reg_field sr_reg_field_54 = {
	.name = "Vsync_End",
	.bits_num = 6,
	.shift = 2,
	.reg_addr = 0x861b,
};
struct reg_info sr_reg_27 = {
	.reg_block_name = "sr",
	.reg_mmio_addr = 0x861b,
	.reg_sub_index = 0x1b,
	.field_num = 2,
	.reg_in_bytes = 1,
};
struct reg_field sr_reg_field_55 = {
	.name = "Iwinw_0",
	.bits_num = 8,
	.shift = 0,
	.reg_addr = 0x861c,
};
struct reg_info sr_reg_28 = {
	.reg_block_name = "sr",
	.reg_mmio_addr = 0x861c,
	.reg_sub_index = 0x1c,
	.field_num = 1,
	.reg_in_bytes = 1,
};
struct reg_field sr_reg_field_56 = {
	.name = "Iwin_En",
	.bits_num = 1,
	.shift = 0,
	.reg_addr = 0x861d,
};
struct reg_field sr_reg_field_57 = {
	.name = "Reserved",
	.bits_num = 1,
	.shift = 1,
	.reg_addr = 0x861d,
};
struct reg_field sr_reg_field_58 = {
	.name = "Iwinw_1",
	.bits_num = 6,
	.shift = 2,
	.reg_addr = 0x861d,
};
struct reg_info sr_reg_29 = {
	.reg_block_name = "sr",
	.reg_mmio_addr = 0x861d,
	.reg_sub_index = 0x1d,
	.field_num = 3,
	.reg_in_bytes = 1,
};
struct reg_field sr_reg_field_59 = {
	.name = "Iwinh_0",
	.bits_num = 8,
	.shift = 0,
	.reg_addr = 0x861e,
};
struct reg_info sr_reg_30 = {
	.reg_block_name = "sr",
	.reg_mmio_addr = 0x861e,
	.reg_sub_index = 0x1e,
	.field_num = 1,
	.reg_in_bytes = 1,
};
struct reg_field sr_reg_field_60 = {
	.name = "Iwinh_1",
	.bits_num = 5,
	.shift = 0,
	.reg_addr = 0x861f,
};
struct reg_field sr_reg_field_61 = {
	.name = "Reserved",
	.bits_num = 3,
	.shift = 5,
	.reg_addr = 0x861f,
};
struct reg_info sr_reg_31 = {
	.reg_block_name = "sr",
	.reg_mmio_addr = 0x861f,
	.reg_sub_index = 0x1f,
	.field_num = 2,
	.reg_in_bytes = 1,
};
struct reg_field sr_reg_field_62 = {
	.name = "Iwinx_0",
	.bits_num = 8,
	.shift = 0,
	.reg_addr = 0x8620,
};
struct reg_info sr_reg_32 = {
	.reg_block_name = "sr",
	.reg_mmio_addr = 0x8620,
	.reg_sub_index = 0x20,
	.field_num = 1,
	.reg_in_bytes = 1,
};
struct reg_field sr_reg_field_63 = {
	.name = "Iwinx_1",
	.bits_num = 6,
	.shift = 0,
	.reg_addr = 0x8621,
};
struct reg_field sr_reg_field_64 = {
	.name = "Reserved",
	.bits_num = 2,
	.shift = 6,
	.reg_addr = 0x8621,
};
struct reg_info sr_reg_33 = {
	.reg_block_name = "sr",
	.reg_mmio_addr = 0x8621,
	.reg_sub_index = 0x21,
	.field_num = 2,
	.reg_in_bytes = 1,
};
struct reg_field sr_reg_field_65 = {
	.name = "Iwiny_0",
	.bits_num = 8,
	.shift = 0,
	.reg_addr = 0x8622,
};
struct reg_info sr_reg_34 = {
	.reg_block_name = "sr",
	.reg_mmio_addr = 0x8622,
	.reg_sub_index = 0x22,
	.field_num = 1,
	.reg_in_bytes = 1,
};
struct reg_field sr_reg_field_66 = {
	.name = "Reserved",
	.bits_num = 3,
	.shift = 0,
	.reg_addr = 0x8623,
};
struct reg_field sr_reg_field_67 = {
	.name = "Iwiny_1",
	.bits_num = 5,
	.shift = 3,
	.reg_addr = 0x8623,
};
struct reg_info sr_reg_35 = {
	.reg_block_name = "sr",
	.reg_mmio_addr = 0x8623,
	.reg_sub_index = 0x23,
	.field_num = 2,
	.reg_in_bytes = 1,
};
struct reg_field sr_reg_field_68 = {
	.name = "Sync_Adj",
	.bits_num = 4,
	.shift = 0,
	.reg_addr = 0x8624,
};
struct reg_field sr_reg_field_69 = {
	.name = "De_Adj",
	.bits_num = 4,
	.shift = 4,
	.reg_addr = 0x8624,
};
struct reg_info sr_reg_36 = {
	.reg_block_name = "sr",
	.reg_mmio_addr = 0x8624,
	.reg_sub_index = 0x24,
	.field_num = 2,
	.reg_in_bytes = 1,
};
struct reg_field sr_reg_field_70 = {
	.name = "Blk_Adj",
	.bits_num = 4,
	.shift = 0,
	.reg_addr = 0x8625,
};
struct reg_field sr_reg_field_71 = {
	.name = "Reserved",
	.bits_num = 3,
	.shift = 4,
	.reg_addr = 0x8625,
};
struct reg_field sr_reg_field_72 = {
	.name = "Blk_Src",
	.bits_num = 1,
	.shift = 7,
	.reg_addr = 0x8625,
};
struct reg_info sr_reg_37 = {
	.reg_block_name = "sr",
	.reg_mmio_addr = 0x8625,
	.reg_sub_index = 0x25,
	.field_num = 3,
	.reg_in_bytes = 1,
};
struct reg_field sr_reg_field_73 = {
	.name = "Vga_Mmio_En",
	.bits_num = 1,
	.shift = 0,
	.reg_addr = 0x8626,
};
struct reg_field sr_reg_field_74 = {
	.name = "Vga_Map_Bxx",
	.bits_num = 1,
	.shift = 1,
	.reg_addr = 0x8626,
};
struct reg_field sr_reg_field_75 = {
	.name = "Vga_Map_Abxx",
	.bits_num = 1,
	.shift = 2,
	.reg_addr = 0x8626,
};
struct reg_info sr_reg_38 = {
	.reg_block_name = "sr",
	.reg_mmio_addr = 0x8626,
	.reg_sub_index = 0x26,
	.field_num = 3,
	.reg_in_bytes = 1,
};
struct reg_field sr_reg_field_76 = {
	.name = "Sr_Unlock",
	.bits_num = 8,
	.shift = 0,
	.reg_addr = 0x8627,
};
struct reg_info sr_reg_39 = {
	.reg_block_name = "sr",
	.reg_mmio_addr = 0x8627,
	.reg_sub_index = 0x27,
	.field_num = 1,
	.reg_in_bytes = 1,
};
struct reg_field sr_reg_field_77 = {
	.name = "Vint_Rsel",
	.bits_num = 2,
	.shift = 0,
	.reg_addr = 0x8628,
};
struct reg_field sr_reg_field_78 = {
	.name = "Iga_Io_Sel",
	.bits_num = 2,
	.shift = 2,
	.reg_addr = 0x8628,
};
struct reg_field sr_reg_field_79 = {
	.name = "Reserved",
	.bits_num = 4,
	.shift = 4,
	.reg_addr = 0x8628,
};
struct reg_info sr_reg_40 = {
	.reg_block_name = "sr",
	.reg_mmio_addr = 0x8628,
	.reg_sub_index = 0x28,
	.field_num = 3,
	.reg_in_bytes = 1,
};
struct reg_field sr_reg_field_80 = {
	.name = "Lut_Info_Sel",
	.bits_num = 4,
	.shift = 0,
	.reg_addr = 0x8629,
};
struct reg_field sr_reg_field_81 = {
	.name = "Reserved",
	.bits_num = 4,
	.shift = 4,
	.reg_addr = 0x8629,
};
struct reg_info sr_reg_41 = {
	.reg_block_name = "sr",
	.reg_mmio_addr = 0x8629,
	.reg_sub_index = 0x29,
	.field_num = 2,
	.reg_in_bytes = 1,
};
struct reg_field sr_reg_field_82 = {
	.name = "Timer_Step_Setting",
	.bits_num = 7,
	.shift = 0,
	.reg_addr = 0x862a,
};
struct reg_field sr_reg_field_83 = {
	.name = "Timer_Status_Sw",
	.bits_num = 1,
	.shift = 7,
	.reg_addr = 0x862a,
};
struct reg_info sr_reg_42 = {
	.reg_block_name = "sr",
	.reg_mmio_addr = 0x862a,
	.reg_sub_index = 0x2a,
	.field_num = 2,
	.reg_in_bytes = 1,
};
struct reg_field sr_reg_field_84 = {
	.name = "Pmustatus",
	.bits_num = 8,
	.shift = 0,
	.reg_addr = 0x862b,
};
struct reg_info sr_reg_43 = {
	.reg_block_name = "sr",
	.reg_mmio_addr = 0x862b,
	.reg_sub_index = 0x2b,
	.field_num = 1,
	.reg_in_bytes = 1,
};
struct reg_field sr_reg_field_85 = {
	.name = "Sbytimeout",
	.bits_num = 6,
	.shift = 0,
	.reg_addr = 0x862c,
};
struct reg_field sr_reg_field_86 = {
	.name = "Sbytimres",
	.bits_num = 2,
	.shift = 6,
	.reg_addr = 0x862c,
};
struct reg_info sr_reg_44 = {
	.reg_block_name = "sr",
	.reg_mmio_addr = 0x862c,
	.reg_sub_index = 0x2c,
	.field_num = 2,
	.reg_in_bytes = 1,
};
struct reg_field sr_reg_field_87 = {
	.name = "Reserved",
	.bits_num = 1,
	.shift = 0,
	.reg_addr = 0x862d,
};
struct reg_field sr_reg_field_88 = {
	.name = "Sel_16ms",
	.bits_num = 1,
	.shift = 1,
	.reg_addr = 0x862d,
};
struct reg_field sr_reg_field_89 = {
	.name = "Sel_Msclk",
	.bits_num = 2,
	.shift = 2,
	.reg_addr = 0x862d,
};
struct reg_field sr_reg_field_90 = {
	.name = "Pmstate_Sbyen",
	.bits_num = 1,
	.shift = 4,
	.reg_addr = 0x862d,
};
struct reg_field sr_reg_field_91 = {
	.name = "Pmstate_Suspen",
	.bits_num = 1,
	.shift = 5,
	.reg_addr = 0x862d,
};
struct reg_field sr_reg_field_92 = {
	.name = "Softsby_En",
	.bits_num = 1,
	.shift = 6,
	.reg_addr = 0x862d,
};
struct reg_field sr_reg_field_93 = {
	.name = "Softsusp_En",
	.bits_num = 1,
	.shift = 7,
	.reg_addr = 0x862d,
};
struct reg_info sr_reg_45 = {
	.reg_block_name = "sr",
	.reg_mmio_addr = 0x862d,
	.reg_sub_index = 0x2d,
	.field_num = 7,
	.reg_in_bytes = 1,
};
struct reg_field sr_reg_field_94 = {
	.name = "Pwrup_Fpve",
	.bits_num = 3,
	.shift = 0,
	.reg_addr = 0x862e,
};
struct reg_field sr_reg_field_95 = {
	.name = "Pwrup_Vdfp",
	.bits_num = 3,
	.shift = 3,
	.reg_addr = 0x862e,
};
struct reg_field sr_reg_field_96 = {
	.name = "Dsusp_Poff_En",
	.bits_num = 1,
	.shift = 6,
	.reg_addr = 0x862e,
};
struct reg_field sr_reg_field_97 = {
	.name = "Display_On",
	.bits_num = 1,
	.shift = 7,
	.reg_addr = 0x862e,
};
struct reg_info sr_reg_46 = {
	.reg_block_name = "sr",
	.reg_mmio_addr = 0x862e,
	.reg_sub_index = 0x2e,
	.field_num = 4,
	.reg_in_bytes = 1,
};
struct reg_field sr_reg_field_98 = {
	.name = "Pwrdn_Fpvd",
	.bits_num = 3,
	.shift = 0,
	.reg_addr = 0x862f,
};
struct reg_field sr_reg_field_99 = {
	.name = "Pwrdn_Vefp",
	.bits_num = 3,
	.shift = 3,
	.reg_addr = 0x862f,
};
struct reg_field sr_reg_field_100 = {
	.name = "Envee_Disen",
	.bits_num = 1,
	.shift = 6,
	.reg_addr = 0x862f,
};
struct reg_field sr_reg_field_101 = {
	.name = "Envdd_Disen",
	.bits_num = 1,
	.shift = 7,
	.reg_addr = 0x862f,
};
struct reg_info sr_reg_47 = {
	.reg_block_name = "sr",
	.reg_mmio_addr = 0x862f,
	.reg_sub_index = 0x2f,
	.field_num = 4,
	.reg_in_bytes = 1,
};
struct reg_field sr_reg_field_102 = {
	.name = "Reserved",
	.bits_num = 7,
	.shift = 0,
	.reg_addr = 0x8630,
};
struct reg_field sr_reg_field_103 = {
	.name = "Dpll_Pwdn",
	.bits_num = 1,
	.shift = 7,
	.reg_addr = 0x8630,
};
struct reg_info sr_reg_48 = {
	.reg_block_name = "sr",
	.reg_mmio_addr = 0x8630,
	.reg_sub_index = 0x30,
	.field_num = 2,
	.reg_in_bytes = 1,
};
struct reg_field sr_reg_field_104 = {
	.name = "Sel_Hdmiclk",
	.bits_num = 1,
	.shift = 0,
	.reg_addr = 0x8631,
};
struct reg_field sr_reg_field_105 = {
	.name = "Sel_Dpclk",
	.bits_num = 1,
	.shift = 1,
	.reg_addr = 0x8631,
};
struct reg_field sr_reg_field_106 = {
	.name = "Pl1en_Gate_En",
	.bits_num = 1,
	.shift = 2,
	.reg_addr = 0x8631,
};
struct reg_field sr_reg_field_107 = {
	.name = "Sby_Gate_En_Pl1",
	.bits_num = 1,
	.shift = 3,
	.reg_addr = 0x8631,
};
struct reg_field sr_reg_field_108 = {
	.name = "Susp_Gate_En_Pl1",
	.bits_num = 1,
	.shift = 4,
	.reg_addr = 0x8631,
};
struct reg_field sr_reg_field_109 = {
	.name = "Pl0en_Gate_En",
	.bits_num = 1,
	.shift = 5,
	.reg_addr = 0x8631,
};
struct reg_field sr_reg_field_110 = {
	.name = "Sby_Gate_En_Pl0",
	.bits_num = 1,
	.shift = 6,
	.reg_addr = 0x8631,
};
struct reg_field sr_reg_field_111 = {
	.name = "Susp_Gate_En_Pl0",
	.bits_num = 1,
	.shift = 7,
	.reg_addr = 0x8631,
};
struct reg_info sr_reg_49 = {
	.reg_block_name = "sr",
	.reg_mmio_addr = 0x8631,
	.reg_sub_index = 0x31,
	.field_num = 8,
	.reg_in_bytes = 1,
};
struct reg_field sr_reg_field_112 = {
	.name = "Vgaen_Gate_En",
	.bits_num = 1,
	.shift = 0,
	.reg_addr = 0x8632,
};
struct reg_field sr_reg_field_113 = {
	.name = "Sby_Gate_En_Vga",
	.bits_num = 1,
	.shift = 1,
	.reg_addr = 0x8632,
};
struct reg_field sr_reg_field_114 = {
	.name = "Susp_Gate_En_Vga",
	.bits_num = 1,
	.shift = 2,
	.reg_addr = 0x8632,
};
struct reg_field sr_reg_field_115 = {
	.name = "Reserved",
	.bits_num = 5,
	.shift = 3,
	.reg_addr = 0x8632,
};
struct reg_info sr_reg_50 = {
	.reg_block_name = "sr",
	.reg_mmio_addr = 0x8632,
	.reg_sub_index = 0x32,
	.field_num = 4,
	.reg_in_bytes = 1,
};
struct reg_field sr_reg_field_116 = {
	.name = "Pipe_Rept",
	.bits_num = 2,
	.shift = 0,
	.reg_addr = 0x8633,
};
struct reg_field sr_reg_field_117 = {
	.name = "Sel_Extdclk",
	.bits_num = 1,
	.shift = 2,
	.reg_addr = 0x8633,
};
struct reg_field sr_reg_field_118 = {
	.name = "Gate_En",
	.bits_num = 1,
	.shift = 3,
	.reg_addr = 0x8633,
};
struct reg_field sr_reg_field_119 = {
	.name = "Sby_Gate_En",
	.bits_num = 1,
	.shift = 4,
	.reg_addr = 0x8633,
};
struct reg_field sr_reg_field_120 = {
	.name = "Susp_Gate_En",
	.bits_num = 1,
	.shift = 5,
	.reg_addr = 0x8633,
};
struct reg_field sr_reg_field_121 = {
	.name = "Crten",
	.bits_num = 1,
	.shift = 6,
	.reg_addr = 0x8633,
};
struct reg_field sr_reg_field_122 = {
	.name = "Reserved",
	.bits_num = 1,
	.shift = 7,
	.reg_addr = 0x8633,
};
struct reg_info sr_reg_51 = {
	.reg_block_name = "sr",
	.reg_mmio_addr = 0x8633,
	.reg_sub_index = 0x33,
	.field_num = 7,
	.reg_in_bytes = 1,
};
struct reg_info * sr_reg_info[52] = {
&sr_reg_0,
&sr_reg_1,
&sr_reg_2,
&sr_reg_3,
&sr_reg_4,
&sr_reg_5,
&sr_reg_6,
&sr_reg_7,
&sr_reg_8,
&sr_reg_9,
&sr_reg_10,
&sr_reg_11,
&sr_reg_12,
&sr_reg_13,
&sr_reg_14,
&sr_reg_15,
&sr_reg_16,
&sr_reg_17,
&sr_reg_18,
&sr_reg_19,
&sr_reg_20,
&sr_reg_21,
&sr_reg_22,
&sr_reg_23,
&sr_reg_24,
&sr_reg_25,
&sr_reg_26,
&sr_reg_27,
&sr_reg_28,
&sr_reg_29,
&sr_reg_30,
&sr_reg_31,
&sr_reg_32,
&sr_reg_33,
&sr_reg_34,
&sr_reg_35,
&sr_reg_36,
&sr_reg_37,
&sr_reg_38,
&sr_reg_39,
&sr_reg_40,
&sr_reg_41,
&sr_reg_42,
&sr_reg_43,
&sr_reg_44,
&sr_reg_45,
&sr_reg_46,
&sr_reg_47,
&sr_reg_48,
&sr_reg_49,
&sr_reg_50,
&sr_reg_51,
};
struct reg_field * sr_reg_field_info[123] = {
&sr_reg_field_0,
&sr_reg_field_1,
&sr_reg_field_2,
&sr_reg_field_3,
&sr_reg_field_4,
&sr_reg_field_5,
&sr_reg_field_6,
&sr_reg_field_7,
&sr_reg_field_8,
&sr_reg_field_9,
&sr_reg_field_10,
&sr_reg_field_11,
&sr_reg_field_12,
&sr_reg_field_13,
&sr_reg_field_14,
&sr_reg_field_15,
&sr_reg_field_16,
&sr_reg_field_17,
&sr_reg_field_18,
&sr_reg_field_19,
&sr_reg_field_20,
&sr_reg_field_21,
&sr_reg_field_22,
&sr_reg_field_23,
&sr_reg_field_24,
&sr_reg_field_25,
&sr_reg_field_26,
&sr_reg_field_27,
&sr_reg_field_28,
&sr_reg_field_29,
&sr_reg_field_30,
&sr_reg_field_31,
&sr_reg_field_32,
&sr_reg_field_33,
&sr_reg_field_34,
&sr_reg_field_35,
&sr_reg_field_36,
&sr_reg_field_37,
&sr_reg_field_38,
&sr_reg_field_39,
&sr_reg_field_40,
&sr_reg_field_41,
&sr_reg_field_42,
&sr_reg_field_43,
&sr_reg_field_44,
&sr_reg_field_45,
&sr_reg_field_46,
&sr_reg_field_47,
&sr_reg_field_48,
&sr_reg_field_49,
&sr_reg_field_50,
&sr_reg_field_51,
&sr_reg_field_52,
&sr_reg_field_53,
&sr_reg_field_54,
&sr_reg_field_55,
&sr_reg_field_56,
&sr_reg_field_57,
&sr_reg_field_58,
&sr_reg_field_59,
&sr_reg_field_60,
&sr_reg_field_61,
&sr_reg_field_62,
&sr_reg_field_63,
&sr_reg_field_64,
&sr_reg_field_65,
&sr_reg_field_66,
&sr_reg_field_67,
&sr_reg_field_68,
&sr_reg_field_69,
&sr_reg_field_70,
&sr_reg_field_71,
&sr_reg_field_72,
&sr_reg_field_73,
&sr_reg_field_74,
&sr_reg_field_75,
&sr_reg_field_76,
&sr_reg_field_77,
&sr_reg_field_78,
&sr_reg_field_79,
&sr_reg_field_80,
&sr_reg_field_81,
&sr_reg_field_82,
&sr_reg_field_83,
&sr_reg_field_84,
&sr_reg_field_85,
&sr_reg_field_86,
&sr_reg_field_87,
&sr_reg_field_88,
&sr_reg_field_89,
&sr_reg_field_90,
&sr_reg_field_91,
&sr_reg_field_92,
&sr_reg_field_93,
&sr_reg_field_94,
&sr_reg_field_95,
&sr_reg_field_96,
&sr_reg_field_97,
&sr_reg_field_98,
&sr_reg_field_99,
&sr_reg_field_100,
&sr_reg_field_101,
&sr_reg_field_102,
&sr_reg_field_103,
&sr_reg_field_104,
&sr_reg_field_105,
&sr_reg_field_106,
&sr_reg_field_107,
&sr_reg_field_108,
&sr_reg_field_109,
&sr_reg_field_110,
&sr_reg_field_111,
&sr_reg_field_112,
&sr_reg_field_113,
&sr_reg_field_114,
&sr_reg_field_115,
&sr_reg_field_116,
&sr_reg_field_117,
&sr_reg_field_118,
&sr_reg_field_119,
&sr_reg_field_120,
&sr_reg_field_121,
&sr_reg_field_122,
};
unsigned int sr_reg_count = 52;
unsigned int sr_reg_start = 0x8600;
unsigned int sr_reg_end = 0x8633;
unsigned int sr_reg_in_bytes = 0x1;
unsigned int sr_reg_total_field_count = 123;
char * sr_reg_block_name = "sr";
