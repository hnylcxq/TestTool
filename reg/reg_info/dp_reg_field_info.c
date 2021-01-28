#include "../reg.h"

struct reg_field dp_reg_field_0 = {
	.name = "Dp_En",
	.bits_num = 1,
	.shift = 0,
	.reg_addr = 0x4200,
};
struct reg_field dp_reg_field_1 = {
	.name = "Hbr_M_Gen_Mod",
	.bits_num = 1,
	.shift = 1,
	.reg_addr = 0x4200,
};
struct reg_field dp_reg_field_2 = {
	.name = "Hw_Gen_Video_M_En",
	.bits_num = 1,
	.shift = 2,
	.reg_addr = 0x4200,
};
struct reg_field dp_reg_field_3 = {
	.name = "Hw_Gen_Audio_M_En",
	.bits_num = 1,
	.shift = 3,
	.reg_addr = 0x4200,
};
struct reg_field dp_reg_field_4 = {
	.name = "Num_Of_Lane",
	.bits_num = 3,
	.shift = 4,
	.reg_addr = 0x4200,
};
struct reg_field dp_reg_field_5 = {
	.name = "Hw_N_Mode",
	.bits_num = 1,
	.shift = 7,
	.reg_addr = 0x4200,
};
struct reg_field dp_reg_field_6 = {
	.name = "En_Video",
	.bits_num = 1,
	.shift = 8,
	.reg_addr = 0x4200,
};
struct reg_field dp_reg_field_7 = {
	.name = "En_Defer_Lt8",
	.bits_num = 1,
	.shift = 9,
	.reg_addr = 0x4200,
};
struct reg_field dp_reg_field_8 = {
	.name = "En_Audio",
	.bits_num = 1,
	.shift = 10,
	.reg_addr = 0x4200,
};
struct reg_field dp_reg_field_9 = {
	.name = "Edp_Mode",
	.bits_num = 1,
	.shift = 11,
	.reg_addr = 0x4200,
};
struct reg_field dp_reg_field_10 = {
	.name = "Enh_Mod",
	.bits_num = 1,
	.shift = 12,
	.reg_addr = 0x4200,
};
struct reg_field dp_reg_field_11 = {
	.name = "Reduced_Aux_Mod",
	.bits_num = 1,
	.shift = 13,
	.reg_addr = 0x4200,
};
struct reg_field dp_reg_field_12 = {
	.name = "Scramble_En",
	.bits_num = 1,
	.shift = 14,
	.reg_addr = 0x4200,
};
struct reg_field dp_reg_field_13 = {
	.name = "Hw_Link_Clear_Dpcd102",
	.bits_num = 1,
	.shift = 15,
	.reg_addr = 0x4200,
};
struct reg_field dp_reg_field_14 = {
	.name = "Hw_Write_Dpcd101",
	.bits_num = 1,
	.shift = 16,
	.reg_addr = 0x4200,
};
struct reg_field dp_reg_field_15 = {
	.name = "Cr2eq_Wr02_Only",
	.bits_num = 1,
	.shift = 17,
	.reg_addr = 0x4200,
};
struct reg_field dp_reg_field_16 = {
	.name = "Eq_Failed_Sel",
	.bits_num = 1,
	.shift = 18,
	.reg_addr = 0x4200,
};
struct reg_field dp_reg_field_17 = {
	.name = "Lanex_Cr_Done_Fail",
	.bits_num = 1,
	.shift = 19,
	.reg_addr = 0x4200,
};
struct reg_field dp_reg_field_18 = {
	.name = "Eq_Pattern_Type",
	.bits_num = 2,
	.shift = 20,
	.reg_addr = 0x4200,
};
struct reg_field dp_reg_field_19 = {
	.name = "Crc_En",
	.bits_num = 1,
	.shift = 22,
	.reg_addr = 0x4200,
};
struct reg_field dp_reg_field_20 = {
	.name = "Bit_Rate",
	.bits_num = 2,
	.shift = 23,
	.reg_addr = 0x4200,
};
struct reg_field dp_reg_field_21 = {
	.name = "Lt",
	.bits_num = 2,
	.shift = 25,
	.reg_addr = 0x4200,
};
struct reg_field dp_reg_field_22 = {
	.name = "Lt_En",
	.bits_num = 1,
	.shift = 27,
	.reg_addr = 0x4200,
};
struct reg_field dp_reg_field_23 = {
	.name = "Start_Linkrate",
	.bits_num = 2,
	.shift = 28,
	.reg_addr = 0x4200,
};
struct reg_field dp_reg_field_24 = {
	.name = "Lt_Rst",
	.bits_num = 1,
	.shift = 30,
	.reg_addr = 0x4200,
};
struct reg_field dp_reg_field_25 = {
	.name = "Start_Linktraining",
	.bits_num = 1,
	.shift = 31,
	.reg_addr = 0x4200,
};
struct reg_info dp_reg_0 = {
	.reg_block_name = "dp",
	.reg_mmio_addr = 0x4200,
	.reg_sub_index = 0x0,
	.field_num = 26,
	.reg_in_bytes = 4,
};
struct reg_field dp_reg_field_26 = {
	.name = "Dur_Htotal",
	.bits_num = 16,
	.shift = 0,
	.reg_addr = 0x4204,
};
struct reg_field dp_reg_field_27 = {
	.name = "Reserved_1",
	.bits_num = 3,
	.shift = 16,
	.reg_addr = 0x4204,
};
struct reg_field dp_reg_field_28 = {
	.name = "Dur_Hblank",
	.bits_num = 13,
	.shift = 19,
	.reg_addr = 0x4204,
};
struct reg_info dp_reg_1 = {
	.reg_block_name = "dp",
	.reg_mmio_addr = 0x4204,
	.reg_sub_index = 0x1,
	.field_num = 3,
	.reg_in_bytes = 4,
};
struct reg_field dp_reg_field_29 = {
	.name = "Second_Id",
	.bits_num = 8,
	.shift = 0,
	.reg_addr = 0x4208,
};
struct reg_field dp_reg_field_30 = {
	.name = "Reserved_1",
	.bits_num = 1,
	.shift = 8,
	.reg_addr = 0x4208,
};
struct reg_field dp_reg_field_31 = {
	.name = "Hpd_Mode",
	.bits_num = 1,
	.shift = 9,
	.reg_addr = 0x4208,
};
struct reg_field dp_reg_field_32 = {
	.name = "Sdp_Version",
	.bits_num = 6,
	.shift = 10,
	.reg_addr = 0x4208,
};
struct reg_field dp_reg_field_33 = {
	.name = "Cr_Done_Clr",
	.bits_num = 1,
	.shift = 16,
	.reg_addr = 0x4208,
};
struct reg_field dp_reg_field_34 = {
	.name = "Dpcd_Ver",
	.bits_num = 2,
	.shift = 17,
	.reg_addr = 0x4208,
};
struct reg_field dp_reg_field_35 = {
	.name = "H_Width",
	.bits_num = 13,
	.shift = 19,
	.reg_addr = 0x4208,
};
struct reg_info dp_reg_2 = {
	.reg_block_name = "dp",
	.reg_mmio_addr = 0x4208,
	.reg_sub_index = 0x2,
	.field_num = 7,
	.reg_in_bytes = 4,
};
struct reg_field dp_reg_field_36 = {
	.name = "Reserved_5",
	.bits_num = 1,
	.shift = 0,
	.reg_addr = 0x420c,
};
struct reg_field dp_reg_field_37 = {
	.name = "Reserved_4",
	.bits_num = 3,
	.shift = 1,
	.reg_addr = 0x420c,
};
struct reg_field dp_reg_field_38 = {
	.name = "Field_Inv",
	.bits_num = 1,
	.shift = 4,
	.reg_addr = 0x420c,
};
struct reg_field dp_reg_field_39 = {
	.name = "Field_Flag_Inv",
	.bits_num = 1,
	.shift = 5,
	.reg_addr = 0x420c,
};
struct reg_field dp_reg_field_40 = {
	.name = "Reserved_3",
	.bits_num = 2,
	.shift = 6,
	.reg_addr = 0x420c,
};
struct reg_field dp_reg_field_41 = {
	.name = "Reserved_2",
	.bits_num = 2,
	.shift = 8,
	.reg_addr = 0x420c,
};
struct reg_field dp_reg_field_42 = {
	.name = "Tu_Size",
	.bits_num = 6,
	.shift = 10,
	.reg_addr = 0x420c,
};
struct reg_field dp_reg_field_43 = {
	.name = "Reserved_1",
	.bits_num = 1,
	.shift = 16,
	.reg_addr = 0x420c,
};
struct reg_field dp_reg_field_44 = {
	.name = "Tu_Ratio",
	.bits_num = 15,
	.shift = 17,
	.reg_addr = 0x420c,
};
struct reg_info dp_reg_3 = {
	.reg_block_name = "dp",
	.reg_mmio_addr = 0x420c,
	.reg_sub_index = 0x3,
	.field_num = 9,
	.reg_in_bytes = 4,
};
struct reg_field dp_reg_field_45 = {
	.name = "Attr_Hoffset",
	.bits_num = 16,
	.shift = 0,
	.reg_addr = 0x4210,
};
struct reg_field dp_reg_field_46 = {
	.name = "Attr_Hden",
	.bits_num = 16,
	.shift = 16,
	.reg_addr = 0x4210,
};
struct reg_info dp_reg_4 = {
	.reg_block_name = "dp",
	.reg_mmio_addr = 0x4210,
	.reg_sub_index = 0x4,
	.field_num = 2,
	.reg_in_bytes = 4,
};
struct reg_field dp_reg_field_47 = {
	.name = "Attr_Htotal",
	.bits_num = 16,
	.shift = 0,
	.reg_addr = 0x4214,
};
struct reg_field dp_reg_field_48 = {
	.name = "Attr_Hsync",
	.bits_num = 16,
	.shift = 16,
	.reg_addr = 0x4214,
};
struct reg_info dp_reg_5 = {
	.reg_block_name = "dp",
	.reg_mmio_addr = 0x4214,
	.reg_sub_index = 0x5,
	.field_num = 2,
	.reg_in_bytes = 4,
};
struct reg_field dp_reg_field_49 = {
	.name = "Attr_Mvid",
	.bits_num = 24,
	.shift = 0,
	.reg_addr = 0x4218,
};
struct reg_field dp_reg_field_50 = {
	.name = "Attr_Misc1",
	.bits_num = 8,
	.shift = 24,
	.reg_addr = 0x4218,
};
struct reg_info dp_reg_6 = {
	.reg_block_name = "dp",
	.reg_mmio_addr = 0x4218,
	.reg_sub_index = 0x6,
	.field_num = 2,
	.reg_in_bytes = 4,
};
struct reg_field dp_reg_field_51 = {
	.name = "Attr_Nvid",
	.bits_num = 24,
	.shift = 0,
	.reg_addr = 0x421c,
};
struct reg_field dp_reg_field_52 = {
	.name = "Attr_Misc2",
	.bits_num = 8,
	.shift = 24,
	.reg_addr = 0x421c,
};
struct reg_info dp_reg_7 = {
	.reg_block_name = "dp",
	.reg_mmio_addr = 0x421c,
	.reg_sub_index = 0x7,
	.field_num = 2,
	.reg_in_bytes = 4,
};
struct reg_field dp_reg_field_53 = {
	.name = "Attr_Voffset",
	.bits_num = 16,
	.shift = 0,
	.reg_addr = 0x4220,
};
struct reg_field dp_reg_field_54 = {
	.name = "Attr_Vden",
	.bits_num = 16,
	.shift = 16,
	.reg_addr = 0x4220,
};
struct reg_info dp_reg_8 = {
	.reg_block_name = "dp",
	.reg_mmio_addr = 0x4220,
	.reg_sub_index = 0x8,
	.field_num = 2,
	.reg_in_bytes = 4,
};
struct reg_field dp_reg_field_55 = {
	.name = "Attr_Vtotal",
	.bits_num = 16,
	.shift = 0,
	.reg_addr = 0x4224,
};
struct reg_field dp_reg_field_56 = {
	.name = "Attr_Vsync",
	.bits_num = 16,
	.shift = 16,
	.reg_addr = 0x4224,
};
struct reg_info dp_reg_9 = {
	.reg_block_name = "dp",
	.reg_mmio_addr = 0x4224,
	.reg_sub_index = 0x9,
	.field_num = 2,
	.reg_in_bytes = 4,
};
struct reg_field dp_reg_field_57 = {
	.name = "Vsc_Head",
	.bits_num = 8,
	.shift = 0,
	.reg_addr = 0x4228,
};
struct reg_field dp_reg_field_58 = {
	.name = "Maud",
	.bits_num = 24,
	.shift = 8,
	.reg_addr = 0x4228,
};
struct reg_info dp_reg_10 = {
	.reg_block_name = "dp",
	.reg_mmio_addr = 0x4228,
	.reg_sub_index = 0xa,
	.field_num = 2,
	.reg_in_bytes = 4,
};
struct reg_field dp_reg_field_59 = {
	.name = "Vsc_Db0",
	.bits_num = 8,
	.shift = 0,
	.reg_addr = 0x422c,
};
struct reg_field dp_reg_field_60 = {
	.name = "Naud",
	.bits_num = 24,
	.shift = 8,
	.reg_addr = 0x422c,
};
struct reg_info dp_reg_11 = {
	.reg_block_name = "dp",
	.reg_mmio_addr = 0x422c,
	.reg_sub_index = 0xb,
	.field_num = 2,
	.reg_in_bytes = 4,
};
struct reg_field dp_reg_field_61 = {
	.name = "Force_Bs",
	.bits_num = 1,
	.shift = 0,
	.reg_addr = 0x4230,
};
struct reg_field dp_reg_field_62 = {
	.name = "Vsc_Support_3d_Field",
	.bits_num = 1,
	.shift = 1,
	.reg_addr = 0x4230,
};
struct reg_field dp_reg_field_63 = {
	.name = "Video_Sync_Mod",
	.bits_num = 1,
	.shift = 2,
	.reg_addr = 0x4230,
};
struct reg_field dp_reg_field_64 = {
	.name = "Dpcd102_32",
	.bits_num = 2,
	.shift = 3,
	.reg_addr = 0x4230,
};
struct reg_field dp_reg_field_65 = {
	.name = "Link_Rate_Use_Dpcp115",
	.bits_num = 1,
	.shift = 5,
	.reg_addr = 0x4230,
};
struct reg_field dp_reg_field_66 = {
	.name = "Link_Qual_Set_Lane",
	.bits_num = 3,
	.shift = 6,
	.reg_addr = 0x4230,
};
struct reg_field dp_reg_field_67 = {
	.name = "Link_Qual_Set_En",
	.bits_num = 1,
	.shift = 9,
	.reg_addr = 0x4230,
};
struct reg_field dp_reg_field_68 = {
	.name = "Min_Sync_Num",
	.bits_num = 6,
	.shift = 10,
	.reg_addr = 0x4230,
};
struct reg_field dp_reg_field_69 = {
	.name = "Hbr2_Scrambler_Reset",
	.bits_num = 16,
	.shift = 16,
	.reg_addr = 0x4230,
};
struct reg_info dp_reg_12 = {
	.reg_block_name = "dp",
	.reg_mmio_addr = 0x4230,
	.reg_sub_index = 0xc,
	.field_num = 9,
	.reg_in_bytes = 4,
};
struct reg_field dp_reg_field_70 = {
	.name = "Custom_80bit_Pat_0",
	.bits_num = 32,
	.shift = 0,
	.reg_addr = 0x4234,
};
struct reg_info dp_reg_13 = {
	.reg_block_name = "dp",
	.reg_mmio_addr = 0x4234,
	.reg_sub_index = 0xd,
	.field_num = 1,
	.reg_in_bytes = 4,
};
struct reg_field dp_reg_field_71 = {
	.name = "Custom_80bit_Pat_1",
	.bits_num = 32,
	.shift = 0,
	.reg_addr = 0x4238,
};
struct reg_info dp_reg_14 = {
	.reg_block_name = "dp",
	.reg_mmio_addr = 0x4238,
	.reg_sub_index = 0xe,
	.field_num = 1,
	.reg_in_bytes = 4,
};
struct reg_field dp_reg_field_72 = {
	.name = "Timer_En",
	.bits_num = 1,
	.shift = 0,
	.reg_addr = 0x423c,
};
struct reg_field dp_reg_field_73 = {
	.name = "Timer_Clr",
	.bits_num = 6,
	.shift = 1,
	.reg_addr = 0x423c,
};
struct reg_field dp_reg_field_74 = {
	.name = "Delay_Value",
	.bits_num = 1,
	.shift = 7,
	.reg_addr = 0x423c,
};
struct reg_field dp_reg_field_75 = {
	.name = "Force_Idle",
	.bits_num = 1,
	.shift = 8,
	.reg_addr = 0x423c,
};
struct reg_field dp_reg_field_76 = {
	.name = "Force_Hpgin",
	.bits_num = 1,
	.shift = 9,
	.reg_addr = 0x423c,
};
struct reg_field dp_reg_field_77 = {
	.name = "Idle_Fifo_Info_Send_En",
	.bits_num = 1,
	.shift = 10,
	.reg_addr = 0x423c,
};
struct reg_field dp_reg_field_78 = {
	.name = "Audioinfo_Sel",
	.bits_num = 1,
	.shift = 11,
	.reg_addr = 0x423c,
};
struct reg_field dp_reg_field_79 = {
	.name = "Audioinfo_From_Hdaudio",
	.bits_num = 1,
	.shift = 12,
	.reg_addr = 0x423c,
};
struct reg_field dp_reg_field_80 = {
	.name = "Audio_Out_En",
	.bits_num = 1,
	.shift = 13,
	.reg_addr = 0x423c,
};
struct reg_field dp_reg_field_81 = {
	.name = "Audio_Mute_Mode",
	.bits_num = 1,
	.shift = 14,
	.reg_addr = 0x423c,
};
struct reg_field dp_reg_field_82 = {
	.name = "Audio_Mute",
	.bits_num = 1,
	.shift = 15,
	.reg_addr = 0x423c,
};
struct reg_field dp_reg_field_83 = {
	.name = "Custom_80bit_Pat_2",
	.bits_num = 16,
	.shift = 16,
	.reg_addr = 0x423c,
};
struct reg_info dp_reg_15 = {
	.reg_block_name = "dp",
	.reg_mmio_addr = 0x423c,
	.reg_sub_index = 0xf,
	.field_num = 12,
	.reg_in_bytes = 4,
};
struct reg_field dp_reg_field_84 = {
	.name = "Extension_Head",
	.bits_num = 24,
	.shift = 0,
	.reg_addr = 0x4240,
};
struct reg_field dp_reg_field_85 = {
	.name = "Extension_Byte_Num",
	.bits_num = 4,
	.shift = 24,
	.reg_addr = 0x4240,
};
struct reg_field dp_reg_field_86 = {
	.name = "Reserved_1",
	.bits_num = 2,
	.shift = 28,
	.reg_addr = 0x4240,
};
struct reg_field dp_reg_field_87 = {
	.name = "Avl_Extension",
	.bits_num = 1,
	.shift = 30,
	.reg_addr = 0x4240,
};
struct reg_field dp_reg_field_88 = {
	.name = "Enable_Extension",
	.bits_num = 1,
	.shift = 31,
	.reg_addr = 0x4240,
};
struct reg_info dp_reg_16 = {
	.reg_block_name = "dp",
	.reg_mmio_addr = 0x4240,
	.reg_sub_index = 0x10,
	.field_num = 5,
	.reg_in_bytes = 4,
};
struct reg_field dp_reg_field_89 = {
	.name = "Extension_Payload_0",
	.bits_num = 32,
	.shift = 0,
	.reg_addr = 0x4244,
};
struct reg_info dp_reg_17 = {
	.reg_block_name = "dp",
	.reg_mmio_addr = 0x4244,
	.reg_sub_index = 0x11,
	.field_num = 1,
	.reg_in_bytes = 4,
};
struct reg_field dp_reg_field_90 = {
	.name = "Extension_Payload_1",
	.bits_num = 32,
	.shift = 0,
	.reg_addr = 0x4248,
};
struct reg_info dp_reg_18 = {
	.reg_block_name = "dp",
	.reg_mmio_addr = 0x4248,
	.reg_sub_index = 0x12,
	.field_num = 1,
	.reg_in_bytes = 4,
};
struct reg_field dp_reg_field_91 = {
	.name = "Extension_Payload_2",
	.bits_num = 32,
	.shift = 0,
	.reg_addr = 0x424c,
};
struct reg_info dp_reg_19 = {
	.reg_block_name = "dp",
	.reg_mmio_addr = 0x424c,
	.reg_sub_index = 0x13,
	.field_num = 1,
	.reg_in_bytes = 4,
};
struct reg_field dp_reg_field_92 = {
	.name = "Extension_Payload_3",
	.bits_num = 32,
	.shift = 0,
	.reg_addr = 0x4250,
};
struct reg_info dp_reg_20 = {
	.reg_block_name = "dp",
	.reg_mmio_addr = 0x4250,
	.reg_sub_index = 0x14,
	.field_num = 1,
	.reg_in_bytes = 4,
};
struct reg_field dp_reg_field_93 = {
	.name = "Reserved_2",
	.bits_num = 1,
	.shift = 0,
	.reg_addr = 0x4254,
};
struct reg_field dp_reg_field_94 = {
	.name = "Reserved_1",
	.bits_num = 1,
	.shift = 1,
	.reg_addr = 0x4254,
};
struct reg_field dp_reg_field_95 = {
	.name = "Lt_Done_Flag",
	.bits_num = 1,
	.shift = 2,
	.reg_addr = 0x4254,
};
struct reg_field dp_reg_field_96 = {
	.name = "Lt_Aux_Fail_Flag",
	.bits_num = 1,
	.shift = 3,
	.reg_addr = 0x4254,
};
struct reg_field dp_reg_field_97 = {
	.name = "Sync_Cnt_Check",
	.bits_num = 1,
	.shift = 4,
	.reg_addr = 0x4254,
};
struct reg_field dp_reg_field_98 = {
	.name = "Sw_Use_Aux",
	.bits_num = 1,
	.shift = 5,
	.reg_addr = 0x4254,
};
struct reg_field dp_reg_field_99 = {
	.name = "Aux_Rd_Interval",
	.bits_num = 3,
	.shift = 6,
	.reg_addr = 0x4254,
};
struct reg_field dp_reg_field_100 = {
	.name = "Ff_Nu",
	.bits_num = 1,
	.shift = 9,
	.reg_addr = 0x4254,
};
struct reg_field dp_reg_field_101 = {
	.name = "Info_Pkt_Rdy_Ff2",
	.bits_num = 1,
	.shift = 10,
	.reg_addr = 0x4254,
};
struct reg_field dp_reg_field_102 = {
	.name = "Info_Pkt_Rdy_Ff1",
	.bits_num = 1,
	.shift = 11,
	.reg_addr = 0x4254,
};
struct reg_field dp_reg_field_103 = {
	.name = "Ff2_Start_Add",
	.bits_num = 4,
	.shift = 12,
	.reg_addr = 0x4254,
};
struct reg_field dp_reg_field_104 = {
	.name = "Ff2_Legth",
	.bits_num = 4,
	.shift = 16,
	.reg_addr = 0x4254,
};
struct reg_field dp_reg_field_105 = {
	.name = "Ff1_Start_Add",
	.bits_num = 4,
	.shift = 20,
	.reg_addr = 0x4254,
};
struct reg_field dp_reg_field_106 = {
	.name = "Ff1_Legth",
	.bits_num = 4,
	.shift = 24,
	.reg_addr = 0x4254,
};
struct reg_field dp_reg_field_107 = {
	.name = "Extension_Packet_Type",
	.bits_num = 4,
	.shift = 28,
	.reg_addr = 0x4254,
};
struct reg_info dp_reg_21 = {
	.reg_block_name = "dp",
	.reg_mmio_addr = 0x4254,
	.reg_sub_index = 0x15,
	.field_num = 15,
	.reg_in_bytes = 4,
};
struct reg_field dp_reg_field_108 = {
	.name = "Reserved_2",
	.bits_num = 4,
	.shift = 0,
	.reg_addr = 0x4258,
};
struct reg_field dp_reg_field_109 = {
	.name = "Psr_Entry_Vcount",
	.bits_num = 12,
	.shift = 4,
	.reg_addr = 0x4258,
};
struct reg_field dp_reg_field_110 = {
	.name = "Reserved_1",
	.bits_num = 5,
	.shift = 16,
	.reg_addr = 0x4258,
};
struct reg_field dp_reg_field_111 = {
	.name = "Psr_Update_Mode",
	.bits_num = 1,
	.shift = 21,
	.reg_addr = 0x4258,
};
struct reg_field dp_reg_field_112 = {
	.name = "Psr_Ml_On",
	.bits_num = 1,
	.shift = 22,
	.reg_addr = 0x4258,
};
struct reg_field dp_reg_field_113 = {
	.name = "Psr_Ml_Auto_Off",
	.bits_num = 1,
	.shift = 23,
	.reg_addr = 0x4258,
};
struct reg_field dp_reg_field_114 = {
	.name = "Psr_Update",
	.bits_num = 1,
	.shift = 24,
	.reg_addr = 0x4258,
};
struct reg_field dp_reg_field_115 = {
	.name = "Psr_Sleep",
	.bits_num = 1,
	.shift = 25,
	.reg_addr = 0x4258,
};
struct reg_field dp_reg_field_116 = {
	.name = "Psr_Exit",
	.bits_num = 1,
	.shift = 26,
	.reg_addr = 0x4258,
};
struct reg_field dp_reg_field_117 = {
	.name = "Psr_Enter_Mode",
	.bits_num = 1,
	.shift = 27,
	.reg_addr = 0x4258,
};
struct reg_field dp_reg_field_118 = {
	.name = "Psr_Enter",
	.bits_num = 1,
	.shift = 28,
	.reg_addr = 0x4258,
};
struct reg_field dp_reg_field_119 = {
	.name = "Psr_En",
	.bits_num = 1,
	.shift = 29,
	.reg_addr = 0x4258,
};
struct reg_field dp_reg_field_120 = {
	.name = "Psr_Csc_Mode",
	.bits_num = 1,
	.shift = 30,
	.reg_addr = 0x4258,
};
struct reg_field dp_reg_field_121 = {
	.name = "Psr_Burst_Update",
	.bits_num = 1,
	.shift = 31,
	.reg_addr = 0x4258,
};
struct reg_info dp_reg_22 = {
	.reg_block_name = "dp",
	.reg_mmio_addr = 0x4258,
	.reg_sub_index = 0x16,
	.field_num = 14,
	.reg_in_bytes = 4,
};
struct reg_field dp_reg_field_122 = {
	.name = "Sw_Crc_0",
	.bits_num = 32,
	.shift = 0,
	.reg_addr = 0x425c,
};
struct reg_info dp_reg_23 = {
	.reg_block_name = "dp",
	.reg_mmio_addr = 0x425c,
	.reg_sub_index = 0x17,
	.field_num = 1,
	.reg_in_bytes = 4,
};
struct reg_field dp_reg_field_123 = {
	.name = "Aux_Rst",
	.bits_num = 1,
	.shift = 0,
	.reg_addr = 0x4260,
};
struct reg_field dp_reg_field_124 = {
	.name = "Aux_Req",
	.bits_num = 1,
	.shift = 1,
	.reg_addr = 0x4260,
};
struct reg_field dp_reg_field_125 = {
	.name = "Aux_Timeout_Flag",
	.bits_num = 1,
	.shift = 2,
	.reg_addr = 0x4260,
};
struct reg_field dp_reg_field_126 = {
	.name = "Aux_Drdy_Flag",
	.bits_num = 1,
	.shift = 3,
	.reg_addr = 0x4260,
};
struct reg_field dp_reg_field_127 = {
	.name = "Reserved_1",
	.bits_num = 11,
	.shift = 4,
	.reg_addr = 0x4260,
};
struct reg_field dp_reg_field_128 = {
	.name = "Sw_Crc_En",
	.bits_num = 1,
	.shift = 15,
	.reg_addr = 0x4260,
};
struct reg_field dp_reg_field_129 = {
	.name = "Sw_Crc_1",
	.bits_num = 16,
	.shift = 16,
	.reg_addr = 0x4260,
};
struct reg_info dp_reg_24 = {
	.reg_block_name = "dp",
	.reg_mmio_addr = 0x4260,
	.reg_sub_index = 0x18,
	.field_num = 7,
	.reg_in_bytes = 4,
};
struct reg_field dp_reg_field_130 = {
	.name = "Aux_Len",
	.bits_num = 8,
	.shift = 0,
	.reg_addr = 0x4264,
};
struct reg_field dp_reg_field_131 = {
	.name = "Aux_Com",
	.bits_num = 4,
	.shift = 8,
	.reg_addr = 0x4264,
};
struct reg_field dp_reg_field_132 = {
	.name = "Aux_Add",
	.bits_num = 20,
	.shift = 12,
	.reg_addr = 0x4264,
};
struct reg_info dp_reg_25 = {
	.reg_block_name = "dp",
	.reg_mmio_addr = 0x4264,
	.reg_sub_index = 0x19,
	.field_num = 3,
	.reg_in_bytes = 4,
};
struct reg_field dp_reg_field_133 = {
	.name = "Aux_Dat_0",
	.bits_num = 32,
	.shift = 0,
	.reg_addr = 0x4268,
};
struct reg_info dp_reg_26 = {
	.reg_block_name = "dp",
	.reg_mmio_addr = 0x4268,
	.reg_sub_index = 0x1a,
	.field_num = 1,
	.reg_in_bytes = 4,
};
struct reg_field dp_reg_field_134 = {
	.name = "Aux_Dat_1",
	.bits_num = 32,
	.shift = 0,
	.reg_addr = 0x426c,
};
struct reg_info dp_reg_27 = {
	.reg_block_name = "dp",
	.reg_mmio_addr = 0x426c,
	.reg_sub_index = 0x1b,
	.field_num = 1,
	.reg_in_bytes = 4,
};
struct reg_field dp_reg_field_135 = {
	.name = "Aux_Dat_2",
	.bits_num = 32,
	.shift = 0,
	.reg_addr = 0x4270,
};
struct reg_info dp_reg_28 = {
	.reg_block_name = "dp",
	.reg_mmio_addr = 0x4270,
	.reg_sub_index = 0x1c,
	.field_num = 1,
	.reg_in_bytes = 4,
};
struct reg_field dp_reg_field_136 = {
	.name = "Aux_Dat_3",
	.bits_num = 32,
	.shift = 0,
	.reg_addr = 0x4274,
};
struct reg_info dp_reg_29 = {
	.reg_block_name = "dp",
	.reg_mmio_addr = 0x4274,
	.reg_sub_index = 0x1d,
	.field_num = 1,
	.reg_in_bytes = 4,
};
struct reg_field dp_reg_field_137 = {
	.name = "Ephy_Aux_Power_Swctrl",
	.bits_num = 1,
	.shift = 0,
	.reg_addr = 0x4278,
};
struct reg_field dp_reg_field_138 = {
	.name = "Sw_Bg_En",
	.bits_num = 1,
	.shift = 1,
	.reg_addr = 0x4278,
};
struct reg_field dp_reg_field_139 = {
	.name = "Sw_Decap_En",
	.bits_num = 1,
	.shift = 2,
	.reg_addr = 0x4278,
};
struct reg_field dp_reg_field_140 = {
	.name = "Ctrl_Bg_Tx_Time",
	.bits_num = 2,
	.shift = 3,
	.reg_addr = 0x4278,
};
struct reg_field dp_reg_field_141 = {
	.name = "Decap_Del_Ctrl",
	.bits_num = 2,
	.shift = 5,
	.reg_addr = 0x4278,
};
struct reg_field dp_reg_field_142 = {
	.name = "Ephy_Sw_Atbsel",
	.bits_num = 1,
	.shift = 7,
	.reg_addr = 0x4278,
};
struct reg_field dp_reg_field_143 = {
	.name = "Ephy_Sw_Atbsel_Onehot",
	.bits_num = 3,
	.shift = 8,
	.reg_addr = 0x4278,
};
struct reg_field dp_reg_field_144 = {
	.name = "Term_Seg_En",
	.bits_num = 5,
	.shift = 11,
	.reg_addr = 0x4278,
};
struct reg_field dp_reg_field_145 = {
	.name = "Term_Highz_En",
	.bits_num = 1,
	.shift = 16,
	.reg_addr = 0x4278,
};
struct reg_field dp_reg_field_146 = {
	.name = "Tx_Cur_Ctrl",
	.bits_num = 5,
	.shift = 17,
	.reg_addr = 0x4278,
};
struct reg_field dp_reg_field_147 = {
	.name = "Tx_Slew",
	.bits_num = 2,
	.shift = 22,
	.reg_addr = 0x4278,
};
struct reg_field dp_reg_field_148 = {
	.name = "Tx_Reduced_Swing",
	.bits_num = 1,
	.shift = 24,
	.reg_addr = 0x4278,
};
struct reg_field dp_reg_field_149 = {
	.name = "Rx_Hyst_Lvl",
	.bits_num = 3,
	.shift = 25,
	.reg_addr = 0x4278,
};
struct reg_field dp_reg_field_150 = {
	.name = "Rx_Deglitch_Filter",
	.bits_num = 1,
	.shift = 28,
	.reg_addr = 0x4278,
};
struct reg_field dp_reg_field_151 = {
	.name = "Rx_Offset_Disable",
	.bits_num = 1,
	.shift = 29,
	.reg_addr = 0x4278,
};
struct reg_field dp_reg_field_152 = {
	.name = "Bg_Start_Adj",
	.bits_num = 2,
	.shift = 30,
	.reg_addr = 0x4278,
};
struct reg_info dp_reg_30 = {
	.reg_block_name = "dp",
	.reg_mmio_addr = 0x4278,
	.reg_sub_index = 0x1e,
	.field_num = 16,
	.reg_in_bytes = 4,
};
struct reg_field dp_reg_field_153 = {
	.name = "Reserved_1",
	.bits_num = 12,
	.shift = 0,
	.reg_addr = 0x427c,
};
struct reg_field dp_reg_field_154 = {
	.name = "Lane3_Pre_Pp",
	.bits_num = 2,
	.shift = 12,
	.reg_addr = 0x427c,
};
struct reg_field dp_reg_field_155 = {
	.name = "Lane3_Swing_Level",
	.bits_num = 2,
	.shift = 14,
	.reg_addr = 0x427c,
};
struct reg_field dp_reg_field_156 = {
	.name = "Lane2_Pre_Pp",
	.bits_num = 2,
	.shift = 16,
	.reg_addr = 0x427c,
};
struct reg_field dp_reg_field_157 = {
	.name = "Lane2_Swing_Level",
	.bits_num = 2,
	.shift = 18,
	.reg_addr = 0x427c,
};
struct reg_field dp_reg_field_158 = {
	.name = "Lane1_Pre_Pp",
	.bits_num = 2,
	.shift = 20,
	.reg_addr = 0x427c,
};
struct reg_field dp_reg_field_159 = {
	.name = "Lane1_Swing_Level",
	.bits_num = 2,
	.shift = 22,
	.reg_addr = 0x427c,
};
struct reg_field dp_reg_field_160 = {
	.name = "Lane0_Pre_Pp",
	.bits_num = 2,
	.shift = 24,
	.reg_addr = 0x427c,
};
struct reg_field dp_reg_field_161 = {
	.name = "Lane0_Swing_Level",
	.bits_num = 2,
	.shift = 26,
	.reg_addr = 0x427c,
};
struct reg_field dp_reg_field_162 = {
	.name = "Max_Pre_Emphasis",
	.bits_num = 2,
	.shift = 28,
	.reg_addr = 0x427c,
};
struct reg_field dp_reg_field_163 = {
	.name = "Max_Voltage_Swing",
	.bits_num = 2,
	.shift = 30,
	.reg_addr = 0x427c,
};
struct reg_info dp_reg_31 = {
	.reg_block_name = "dp",
	.reg_mmio_addr = 0x427c,
	.reg_sub_index = 0x1f,
	.field_num = 11,
	.reg_in_bytes = 4,
};
struct reg_field dp_reg_field_164 = {
	.name = "Ephy_Apb_Rdata_Out",
	.bits_num = 16,
	.shift = 0,
	.reg_addr = 0x4280,
};
struct reg_field dp_reg_field_165 = {
	.name = "Ephy_Apb_Read",
	.bits_num = 1,
	.shift = 16,
	.reg_addr = 0x4280,
};
struct reg_field dp_reg_field_166 = {
	.name = "Ephy_Apb_Write",
	.bits_num = 1,
	.shift = 17,
	.reg_addr = 0x4280,
};
struct reg_field dp_reg_field_167 = {
	.name = "Reserved_1",
	.bits_num = 2,
	.shift = 18,
	.reg_addr = 0x4280,
};
struct reg_field dp_reg_field_168 = {
	.name = "Linktraining_Ephy_Config_Finish",
	.bits_num = 1,
	.shift = 20,
	.reg_addr = 0x4280,
};
struct reg_field dp_reg_field_169 = {
	.name = "Linktraining_Sw_Setting",
	.bits_num = 1,
	.shift = 21,
	.reg_addr = 0x4280,
};
struct reg_field dp_reg_field_170 = {
	.name = "Ephy_Power_State",
	.bits_num = 6,
	.shift = 22,
	.reg_addr = 0x4280,
};
struct reg_field dp_reg_field_171 = {
	.name = "Ephy_Pllclk_En",
	.bits_num = 1,
	.shift = 28,
	.reg_addr = 0x4280,
};
struct reg_field dp_reg_field_172 = {
	.name = "Ephy_Power_Ctrl",
	.bits_num = 1,
	.shift = 29,
	.reg_addr = 0x4280,
};
struct reg_field dp_reg_field_173 = {
	.name = "Apb_Preset_N",
	.bits_num = 1,
	.shift = 30,
	.reg_addr = 0x4280,
};
struct reg_field dp_reg_field_174 = {
	.name = "Phy_Reset",
	.bits_num = 1,
	.shift = 31,
	.reg_addr = 0x4280,
};
struct reg_info dp_reg_32 = {
	.reg_block_name = "dp",
	.reg_mmio_addr = 0x4280,
	.reg_sub_index = 0x20,
	.field_num = 11,
	.reg_in_bytes = 4,
};
struct reg_field dp_reg_field_175 = {
	.name = "Ephy_Apb_Addr",
	.bits_num = 16,
	.shift = 0,
	.reg_addr = 0x4284,
};
struct reg_field dp_reg_field_176 = {
	.name = "Ephy_Apb_Wdata",
	.bits_num = 16,
	.shift = 16,
	.reg_addr = 0x4284,
};
struct reg_info dp_reg_33 = {
	.reg_block_name = "dp",
	.reg_mmio_addr = 0x4284,
	.reg_sub_index = 0x21,
	.field_num = 2,
	.reg_in_bytes = 4,
};
struct reg_field dp_reg_field_177 = {
	.name = "Link_Rate_Value_4",
	.bits_num = 8,
	.shift = 0,
	.reg_addr = 0x4288,
};
struct reg_field dp_reg_field_178 = {
	.name = "Link_Rate_Value_3",
	.bits_num = 8,
	.shift = 8,
	.reg_addr = 0x4288,
};
struct reg_field dp_reg_field_179 = {
	.name = "Link_Rate_Value_2",
	.bits_num = 8,
	.shift = 16,
	.reg_addr = 0x4288,
};
struct reg_field dp_reg_field_180 = {
	.name = "Link_Rate_Value_1",
	.bits_num = 8,
	.shift = 24,
	.reg_addr = 0x4288,
};
struct reg_info dp_reg_34 = {
	.reg_block_name = "dp",
	.reg_mmio_addr = 0x4288,
	.reg_sub_index = 0x22,
	.field_num = 4,
	.reg_in_bytes = 4,
};
struct reg_field dp_reg_field_181 = {
	.name = "Reg_Vsc_Crc_Out_0",
	.bits_num = 32,
	.shift = 0,
	.reg_addr = 0x428c,
};
struct reg_info dp_reg_35 = {
	.reg_block_name = "dp",
	.reg_mmio_addr = 0x428c,
	.reg_sub_index = 0x23,
	.field_num = 1,
	.reg_in_bytes = 4,
};
struct reg_field dp_reg_field_182 = {
	.name = "Reg_Mainlink_Turn_Off",
	.bits_num = 1,
	.shift = 0,
	.reg_addr = 0x4290,
};
struct reg_field dp_reg_field_183 = {
	.name = "Reserved_1",
	.bits_num = 3,
	.shift = 1,
	.reg_addr = 0x4290,
};
struct reg_field dp_reg_field_184 = {
	.name = "Reg_Count_Idle",
	.bits_num = 9,
	.shift = 4,
	.reg_addr = 0x4290,
};
struct reg_field dp_reg_field_185 = {
	.name = "Reg_Psr_St",
	.bits_num = 3,
	.shift = 13,
	.reg_addr = 0x4290,
};
struct reg_field dp_reg_field_186 = {
	.name = "Reg_Vsc_Crc_Out_1",
	.bits_num = 16,
	.shift = 16,
	.reg_addr = 0x4290,
};
struct reg_info dp_reg_36 = {
	.reg_block_name = "dp",
	.reg_mmio_addr = 0x4290,
	.reg_sub_index = 0x24,
	.field_num = 5,
	.reg_in_bytes = 4,
};
struct reg_field dp_reg_field_187 = {
	.name = "Aux_Reg_Len",
	.bits_num = 5,
	.shift = 0,
	.reg_addr = 0x4294,
};
struct reg_field dp_reg_field_188 = {
	.name = "Aux_Reg_Com",
	.bits_num = 4,
	.shift = 5,
	.reg_addr = 0x4294,
};
struct reg_field dp_reg_field_189 = {
	.name = "Reserved_1",
	.bits_num = 1,
	.shift = 9,
	.reg_addr = 0x4294,
};
struct reg_field dp_reg_field_190 = {
	.name = "Ephy_Lane3_Swing_Level",
	.bits_num = 2,
	.shift = 10,
	.reg_addr = 0x4294,
};
struct reg_field dp_reg_field_191 = {
	.name = "Ephy_Lane2_Swing_Level",
	.bits_num = 2,
	.shift = 12,
	.reg_addr = 0x4294,
};
struct reg_field dp_reg_field_192 = {
	.name = "Ephy_Lane1_Swing_Level",
	.bits_num = 2,
	.shift = 14,
	.reg_addr = 0x4294,
};
struct reg_field dp_reg_field_193 = {
	.name = "Ephy_Lane0_Swing_Level",
	.bits_num = 2,
	.shift = 16,
	.reg_addr = 0x4294,
};
struct reg_field dp_reg_field_194 = {
	.name = "Reg_Attro_Misc1_B21",
	.bits_num = 2,
	.shift = 18,
	.reg_addr = 0x4294,
};
struct reg_field dp_reg_field_195 = {
	.name = "Reg_Current_Bit_Rate",
	.bits_num = 2,
	.shift = 20,
	.reg_addr = 0x4294,
};
struct reg_field dp_reg_field_196 = {
	.name = "Reg_Training_State",
	.bits_num = 2,
	.shift = 22,
	.reg_addr = 0x4294,
};
struct reg_field dp_reg_field_197 = {
	.name = "Reg_Link_Bit_Rate",
	.bits_num = 2,
	.shift = 24,
	.reg_addr = 0x4294,
};
struct reg_field dp_reg_field_198 = {
	.name = "Dp_Hpd_Status",
	.bits_num = 2,
	.shift = 26,
	.reg_addr = 0x4294,
};
struct reg_field dp_reg_field_199 = {
	.name = "Reg_Lane3_Cr_Done",
	.bits_num = 1,
	.shift = 28,
	.reg_addr = 0x4294,
};
struct reg_field dp_reg_field_200 = {
	.name = "Reg_Lane2_Cr_Done",
	.bits_num = 1,
	.shift = 29,
	.reg_addr = 0x4294,
};
struct reg_field dp_reg_field_201 = {
	.name = "Reg_Lane1_Cr_Done",
	.bits_num = 1,
	.shift = 30,
	.reg_addr = 0x4294,
};
struct reg_field dp_reg_field_202 = {
	.name = "Reg_Lane0_Cr_Done",
	.bits_num = 1,
	.shift = 31,
	.reg_addr = 0x4294,
};
struct reg_info dp_reg_37 = {
	.reg_block_name = "dp",
	.reg_mmio_addr = 0x4294,
	.reg_sub_index = 0x25,
	.field_num = 16,
	.reg_in_bytes = 4,
};
struct reg_field dp_reg_field_203 = {
	.name = "Aux_Reg_Dat_0",
	.bits_num = 32,
	.shift = 0,
	.reg_addr = 0x4298,
};
struct reg_info dp_reg_38 = {
	.reg_block_name = "dp",
	.reg_mmio_addr = 0x4298,
	.reg_sub_index = 0x26,
	.field_num = 1,
	.reg_in_bytes = 4,
};
struct reg_field dp_reg_field_204 = {
	.name = "Aux_Reg_Dat_1",
	.bits_num = 32,
	.shift = 0,
	.reg_addr = 0x429c,
};
struct reg_info dp_reg_39 = {
	.reg_block_name = "dp",
	.reg_mmio_addr = 0x429c,
	.reg_sub_index = 0x27,
	.field_num = 1,
	.reg_in_bytes = 4,
};
struct reg_field dp_reg_field_205 = {
	.name = "Aux_Reg_Dat_2",
	.bits_num = 32,
	.shift = 0,
	.reg_addr = 0x42a0,
};
struct reg_info dp_reg_40 = {
	.reg_block_name = "dp",
	.reg_mmio_addr = 0x42a0,
	.reg_sub_index = 0x28,
	.field_num = 1,
	.reg_in_bytes = 4,
};
struct reg_field dp_reg_field_206 = {
	.name = "Aux_Reg_Dat_3",
	.bits_num = 32,
	.shift = 0,
	.reg_addr = 0x42a4,
};
struct reg_info dp_reg_41 = {
	.reg_block_name = "dp",
	.reg_mmio_addr = 0x42a4,
	.reg_sub_index = 0x29,
	.field_num = 1,
	.reg_in_bytes = 4,
};
struct reg_field dp_reg_field_207 = {
	.name = "Ephy_Lane3_Pre_Pp",
	.bits_num = 2,
	.shift = 0,
	.reg_addr = 0x42a8,
};
struct reg_field dp_reg_field_208 = {
	.name = "Ephy_Lane2_Pre_Pp",
	.bits_num = 2,
	.shift = 2,
	.reg_addr = 0x42a8,
};
struct reg_field dp_reg_field_209 = {
	.name = "Ephy_Lane1_Pre_Pp",
	.bits_num = 2,
	.shift = 4,
	.reg_addr = 0x42a8,
};
struct reg_field dp_reg_field_210 = {
	.name = "Ephy_Lane0_Pre_Pp",
	.bits_num = 2,
	.shift = 6,
	.reg_addr = 0x42a8,
};
struct reg_field dp_reg_field_211 = {
	.name = "Reserved_1",
	.bits_num = 4,
	.shift = 8,
	.reg_addr = 0x42a8,
};
struct reg_field dp_reg_field_212 = {
	.name = "Reg_Timer_Cnt",
	.bits_num = 20,
	.shift = 12,
	.reg_addr = 0x42a8,
};
struct reg_info dp_reg_42 = {
	.reg_block_name = "dp",
	.reg_mmio_addr = 0x42a8,
	.reg_sub_index = 0x2a,
	.field_num = 6,
	.reg_in_bytes = 4,
};
struct reg_field dp_reg_field_213 = {
	.name = "Drv_Diag_Tx_Drv",
	.bits_num = 16,
	.shift = 0,
	.reg_addr = 0x42ac,
};
struct reg_field dp_reg_field_214 = {
	.name = "Tx_Txcc_Ctrl",
	.bits_num = 16,
	.shift = 16,
	.reg_addr = 0x42ac,
};
struct reg_info dp_reg_43 = {
	.reg_block_name = "dp",
	.reg_mmio_addr = 0x42ac,
	.reg_sub_index = 0x2b,
	.field_num = 2,
	.reg_in_bytes = 4,
};
struct reg_field dp_reg_field_215 = {
	.name = "Swing0_De0_Txcc",
	.bits_num = 32,
	.shift = 0,
	.reg_addr = 0x42b0,
};
struct reg_info dp_reg_44 = {
	.reg_block_name = "dp",
	.reg_mmio_addr = 0x42b0,
	.reg_sub_index = 0x2c,
	.field_num = 1,
	.reg_in_bytes = 4,
};
struct reg_field dp_reg_field_216 = {
	.name = "Swing0_De1_Txcc",
	.bits_num = 32,
	.shift = 0,
	.reg_addr = 0x42b4,
};
struct reg_info dp_reg_45 = {
	.reg_block_name = "dp",
	.reg_mmio_addr = 0x42b4,
	.reg_sub_index = 0x2d,
	.field_num = 1,
	.reg_in_bytes = 4,
};
struct reg_field dp_reg_field_217 = {
	.name = "Swing0_De2_Txcc",
	.bits_num = 32,
	.shift = 0,
	.reg_addr = 0x42b8,
};
struct reg_info dp_reg_46 = {
	.reg_block_name = "dp",
	.reg_mmio_addr = 0x42b8,
	.reg_sub_index = 0x2e,
	.field_num = 1,
	.reg_in_bytes = 4,
};
struct reg_field dp_reg_field_218 = {
	.name = "Swing0_De3_Txcc",
	.bits_num = 32,
	.shift = 0,
	.reg_addr = 0x42bc,
};
struct reg_info dp_reg_47 = {
	.reg_block_name = "dp",
	.reg_mmio_addr = 0x42bc,
	.reg_sub_index = 0x2f,
	.field_num = 1,
	.reg_in_bytes = 4,
};
struct reg_field dp_reg_field_219 = {
	.name = "Swing1_De0_Txcc",
	.bits_num = 32,
	.shift = 0,
	.reg_addr = 0x42c0,
};
struct reg_info dp_reg_48 = {
	.reg_block_name = "dp",
	.reg_mmio_addr = 0x42c0,
	.reg_sub_index = 0x30,
	.field_num = 1,
	.reg_in_bytes = 4,
};
struct reg_field dp_reg_field_220 = {
	.name = "Swing1_De1_Txcc",
	.bits_num = 32,
	.shift = 0,
	.reg_addr = 0x42c4,
};
struct reg_info dp_reg_49 = {
	.reg_block_name = "dp",
	.reg_mmio_addr = 0x42c4,
	.reg_sub_index = 0x31,
	.field_num = 1,
	.reg_in_bytes = 4,
};
struct reg_field dp_reg_field_221 = {
	.name = "Swing1_De2_Txcc",
	.bits_num = 32,
	.shift = 0,
	.reg_addr = 0x42c8,
};
struct reg_info dp_reg_50 = {
	.reg_block_name = "dp",
	.reg_mmio_addr = 0x42c8,
	.reg_sub_index = 0x32,
	.field_num = 1,
	.reg_in_bytes = 4,
};
struct reg_field dp_reg_field_222 = {
	.name = "Swing2_De0_Txcc",
	.bits_num = 32,
	.shift = 0,
	.reg_addr = 0x42cc,
};
struct reg_info dp_reg_51 = {
	.reg_block_name = "dp",
	.reg_mmio_addr = 0x42cc,
	.reg_sub_index = 0x33,
	.field_num = 1,
	.reg_in_bytes = 4,
};
struct reg_field dp_reg_field_223 = {
	.name = "Swing2_De1_Txcc",
	.bits_num = 32,
	.shift = 0,
	.reg_addr = 0x42d0,
};
struct reg_info dp_reg_52 = {
	.reg_block_name = "dp",
	.reg_mmio_addr = 0x42d0,
	.reg_sub_index = 0x34,
	.field_num = 1,
	.reg_in_bytes = 4,
};
struct reg_field dp_reg_field_224 = {
	.name = "Swing3_De0_Txcc",
	.bits_num = 32,
	.shift = 0,
	.reg_addr = 0x42d4,
};
struct reg_info dp_reg_53 = {
	.reg_block_name = "dp",
	.reg_mmio_addr = 0x42d4,
	.reg_sub_index = 0x35,
	.field_num = 1,
	.reg_in_bytes = 4,
};
struct reg_field dp_reg_field_225 = {
	.name = "Rate0_Cmn_Pdiag_Pll0_Cp_Iadj_M0",
	.bits_num = 16,
	.shift = 0,
	.reg_addr = 0x42d8,
};
struct reg_field dp_reg_field_226 = {
	.name = "Rate0_Cmn_Pdiag_Pll0_Cp_Pajd_M0",
	.bits_num = 16,
	.shift = 16,
	.reg_addr = 0x42d8,
};
struct reg_info dp_reg_54 = {
	.reg_block_name = "dp",
	.reg_mmio_addr = 0x42d8,
	.reg_sub_index = 0x36,
	.field_num = 2,
	.reg_in_bytes = 4,
};
struct reg_field dp_reg_field_227 = {
	.name = "Rate0_Cmn_Pll0_Intdiv_M0",
	.bits_num = 16,
	.shift = 0,
	.reg_addr = 0x42dc,
};
struct reg_field dp_reg_field_228 = {
	.name = "Rate0_Cmn_Pdiag_Pll0_Filt_Padj_M0",
	.bits_num = 16,
	.shift = 16,
	.reg_addr = 0x42dc,
};
struct reg_info dp_reg_55 = {
	.reg_block_name = "dp",
	.reg_mmio_addr = 0x42dc,
	.reg_sub_index = 0x37,
	.field_num = 2,
	.reg_in_bytes = 4,
};
struct reg_field dp_reg_field_229 = {
	.name = "Rate0_Cmn_Pll0_Fracdivh_M0",
	.bits_num = 16,
	.shift = 0,
	.reg_addr = 0x42e0,
};
struct reg_field dp_reg_field_230 = {
	.name = "Rate0_Cmn_Pll0_Fracdivl_M0",
	.bits_num = 16,
	.shift = 16,
	.reg_addr = 0x42e0,
};
struct reg_info dp_reg_56 = {
	.reg_block_name = "dp",
	.reg_mmio_addr = 0x42e0,
	.reg_sub_index = 0x38,
	.field_num = 2,
	.reg_in_bytes = 4,
};
struct reg_field dp_reg_field_231 = {
	.name = "Rate0_Cmn_Pdiag_Pll0_Ctrl_M0",
	.bits_num = 16,
	.shift = 0,
	.reg_addr = 0x42e4,
};
struct reg_field dp_reg_field_232 = {
	.name = "Rate0_Cmn_Pll0_High_Thr_M0",
	.bits_num = 16,
	.shift = 16,
	.reg_addr = 0x42e4,
};
struct reg_info dp_reg_57 = {
	.reg_block_name = "dp",
	.reg_mmio_addr = 0x42e4,
	.reg_sub_index = 0x39,
	.field_num = 2,
	.reg_in_bytes = 4,
};
struct reg_field dp_reg_field_233 = {
	.name = "Rate0_Cmn_Pll0_Lock_Refcnt_Start",
	.bits_num = 16,
	.shift = 0,
	.reg_addr = 0x42e8,
};
struct reg_field dp_reg_field_234 = {
	.name = "Rate0_Cmn_Pll0_Vcocal_Pllcnt_Start",
	.bits_num = 16,
	.shift = 16,
	.reg_addr = 0x42e8,
};
struct reg_info dp_reg_58 = {
	.reg_block_name = "dp",
	.reg_mmio_addr = 0x42e8,
	.reg_sub_index = 0x3a,
	.field_num = 2,
	.reg_in_bytes = 4,
};
struct reg_field dp_reg_field_235 = {
	.name = "Rate0_Cmn_Pll0_Lock_Pllcnt_Thr",
	.bits_num = 16,
	.shift = 0,
	.reg_addr = 0x42ec,
};
struct reg_field dp_reg_field_236 = {
	.name = "Rate0_Cmn_Pll0_Lock_Pllcnt_Start",
	.bits_num = 16,
	.shift = 16,
	.reg_addr = 0x42ec,
};
struct reg_info dp_reg_59 = {
	.reg_block_name = "dp",
	.reg_mmio_addr = 0x42ec,
	.reg_sub_index = 0x3b,
	.field_num = 2,
	.reg_in_bytes = 4,
};
struct reg_field dp_reg_field_237 = {
	.name = "Rate0_Cmn_Pll0_Ss_Ctrl2_M0",
	.bits_num = 16,
	.shift = 0,
	.reg_addr = 0x42f0,
};
struct reg_field dp_reg_field_238 = {
	.name = "Rate0_Cmn_Pll0_Ss_Ctrl1_M0",
	.bits_num = 16,
	.shift = 16,
	.reg_addr = 0x42f0,
};
struct reg_info dp_reg_60 = {
	.reg_block_name = "dp",
	.reg_mmio_addr = 0x42f0,
	.reg_sub_index = 0x3c,
	.field_num = 2,
	.reg_in_bytes = 4,
};
struct reg_field dp_reg_field_239 = {
	.name = "Rate0_Cmn_Pll0_Ss_Ctrl4_M0",
	.bits_num = 16,
	.shift = 0,
	.reg_addr = 0x42f4,
};
struct reg_field dp_reg_field_240 = {
	.name = "Rate0_Cmn_Pll0_Ss_Ctrl3_M0",
	.bits_num = 16,
	.shift = 16,
	.reg_addr = 0x42f4,
};
struct reg_info dp_reg_61 = {
	.reg_block_name = "dp",
	.reg_mmio_addr = 0x42f4,
	.reg_sub_index = 0x3d,
	.field_num = 2,
	.reg_in_bytes = 4,
};
struct reg_field dp_reg_field_241 = {
	.name = "Rate1_Cmn_Pdiag_Pll0_Cp_Iadj_M0",
	.bits_num = 16,
	.shift = 0,
	.reg_addr = 0x42f8,
};
struct reg_field dp_reg_field_242 = {
	.name = "Rate1_Cmn_Pdiag_Pll0_Cp_Pajd_M0",
	.bits_num = 16,
	.shift = 16,
	.reg_addr = 0x42f8,
};
struct reg_info dp_reg_62 = {
	.reg_block_name = "dp",
	.reg_mmio_addr = 0x42f8,
	.reg_sub_index = 0x3e,
	.field_num = 2,
	.reg_in_bytes = 4,
};
struct reg_field dp_reg_field_243 = {
	.name = "Rate1_Cmn_Pll0_Intdiv_M0",
	.bits_num = 16,
	.shift = 0,
	.reg_addr = 0x42fc,
};
struct reg_field dp_reg_field_244 = {
	.name = "Rate1_Cmn_Pdiag_Pll0_Filt_Padj_M0",
	.bits_num = 16,
	.shift = 16,
	.reg_addr = 0x42fc,
};
struct reg_info dp_reg_63 = {
	.reg_block_name = "dp",
	.reg_mmio_addr = 0x42fc,
	.reg_sub_index = 0x3f,
	.field_num = 2,
	.reg_in_bytes = 4,
};
struct reg_field dp_reg_field_245 = {
	.name = "Rate1_Cmn_Pll0_Fracdivh_M0",
	.bits_num = 16,
	.shift = 0,
	.reg_addr = 0x4300,
};
struct reg_field dp_reg_field_246 = {
	.name = "Rate1_Cmn_Pll0_Fracdivl_M0",
	.bits_num = 16,
	.shift = 16,
	.reg_addr = 0x4300,
};
struct reg_info dp_reg_64 = {
	.reg_block_name = "dp",
	.reg_mmio_addr = 0x4300,
	.reg_sub_index = 0x40,
	.field_num = 2,
	.reg_in_bytes = 4,
};
struct reg_field dp_reg_field_247 = {
	.name = "Rate1_Cmn_Pdiag_Pll0_Ctrl_M0",
	.bits_num = 16,
	.shift = 0,
	.reg_addr = 0x4304,
};
struct reg_field dp_reg_field_248 = {
	.name = "Rate1_Cmn_Pll0_High_Thr_M0",
	.bits_num = 16,
	.shift = 16,
	.reg_addr = 0x4304,
};
struct reg_info dp_reg_65 = {
	.reg_block_name = "dp",
	.reg_mmio_addr = 0x4304,
	.reg_sub_index = 0x41,
	.field_num = 2,
	.reg_in_bytes = 4,
};
struct reg_field dp_reg_field_249 = {
	.name = "Rate1_Cmn_Pll0_Lock_Refcnt_Start",
	.bits_num = 16,
	.shift = 0,
	.reg_addr = 0x4308,
};
struct reg_field dp_reg_field_250 = {
	.name = "Rate1_Cmn_Pll0_Vcocal_Pllcnt_Start",
	.bits_num = 16,
	.shift = 16,
	.reg_addr = 0x4308,
};
struct reg_info dp_reg_66 = {
	.reg_block_name = "dp",
	.reg_mmio_addr = 0x4308,
	.reg_sub_index = 0x42,
	.field_num = 2,
	.reg_in_bytes = 4,
};
struct reg_field dp_reg_field_251 = {
	.name = "Rate1_Cmn_Pll0_Lock_Pllcnt_Thr",
	.bits_num = 16,
	.shift = 0,
	.reg_addr = 0x430c,
};
struct reg_field dp_reg_field_252 = {
	.name = "Rate1_Cmn_Pll0_Lock_Pllcnt_Start",
	.bits_num = 16,
	.shift = 16,
	.reg_addr = 0x430c,
};
struct reg_info dp_reg_67 = {
	.reg_block_name = "dp",
	.reg_mmio_addr = 0x430c,
	.reg_sub_index = 0x43,
	.field_num = 2,
	.reg_in_bytes = 4,
};
struct reg_field dp_reg_field_253 = {
	.name = "Rate1_Cmn_Pll0_Ss_Ctrl2_M0",
	.bits_num = 16,
	.shift = 0,
	.reg_addr = 0x4310,
};
struct reg_field dp_reg_field_254 = {
	.name = "Rate1_Cmn_Pll0_Ss_Ctrl1_M0",
	.bits_num = 16,
	.shift = 16,
	.reg_addr = 0x4310,
};
struct reg_info dp_reg_68 = {
	.reg_block_name = "dp",
	.reg_mmio_addr = 0x4310,
	.reg_sub_index = 0x44,
	.field_num = 2,
	.reg_in_bytes = 4,
};
struct reg_field dp_reg_field_255 = {
	.name = "Rate1_Cmn_Pll0_Ss_Ctrl4_M0",
	.bits_num = 16,
	.shift = 0,
	.reg_addr = 0x4314,
};
struct reg_field dp_reg_field_256 = {
	.name = "Rate1_Cmn_Pll0_Ss_Ctrl3_M0",
	.bits_num = 16,
	.shift = 16,
	.reg_addr = 0x4314,
};
struct reg_info dp_reg_69 = {
	.reg_block_name = "dp",
	.reg_mmio_addr = 0x4314,
	.reg_sub_index = 0x45,
	.field_num = 2,
	.reg_in_bytes = 4,
};
struct reg_field dp_reg_field_257 = {
	.name = "Rate2_Cmn_Pdiag_Pll0_Cp_Iadj_M0",
	.bits_num = 16,
	.shift = 0,
	.reg_addr = 0x4318,
};
struct reg_field dp_reg_field_258 = {
	.name = "Rate2_Cmn_Pdiag_Pll0_Cp_Pajd_M0",
	.bits_num = 16,
	.shift = 16,
	.reg_addr = 0x4318,
};
struct reg_info dp_reg_70 = {
	.reg_block_name = "dp",
	.reg_mmio_addr = 0x4318,
	.reg_sub_index = 0x46,
	.field_num = 2,
	.reg_in_bytes = 4,
};
struct reg_field dp_reg_field_259 = {
	.name = "Rate2_Cmn_Pll0_Intdiv_M0",
	.bits_num = 16,
	.shift = 0,
	.reg_addr = 0x431c,
};
struct reg_field dp_reg_field_260 = {
	.name = "Rate2_Cmn_Pdiag_Pll0_Filt_Padj_M0",
	.bits_num = 16,
	.shift = 16,
	.reg_addr = 0x431c,
};
struct reg_info dp_reg_71 = {
	.reg_block_name = "dp",
	.reg_mmio_addr = 0x431c,
	.reg_sub_index = 0x47,
	.field_num = 2,
	.reg_in_bytes = 4,
};
struct reg_field dp_reg_field_261 = {
	.name = "Rate2_Cmn_Pll0_Fracdivh_M0",
	.bits_num = 16,
	.shift = 0,
	.reg_addr = 0x4320,
};
struct reg_field dp_reg_field_262 = {
	.name = "Rate2_Cmn_Pll0_Fracdivl_M0",
	.bits_num = 16,
	.shift = 16,
	.reg_addr = 0x4320,
};
struct reg_info dp_reg_72 = {
	.reg_block_name = "dp",
	.reg_mmio_addr = 0x4320,
	.reg_sub_index = 0x48,
	.field_num = 2,
	.reg_in_bytes = 4,
};
struct reg_field dp_reg_field_263 = {
	.name = "Rate2_Cmn_Pdiag_Pll0_Ctrl_M0",
	.bits_num = 16,
	.shift = 0,
	.reg_addr = 0x4324,
};
struct reg_field dp_reg_field_264 = {
	.name = "Rate2_Cmn_Pll0_High_Thr_M0",
	.bits_num = 16,
	.shift = 16,
	.reg_addr = 0x4324,
};
struct reg_info dp_reg_73 = {
	.reg_block_name = "dp",
	.reg_mmio_addr = 0x4324,
	.reg_sub_index = 0x49,
	.field_num = 2,
	.reg_in_bytes = 4,
};
struct reg_field dp_reg_field_265 = {
	.name = "Rate2_Cmn_Pll0_Lock_Refcnt_Start",
	.bits_num = 16,
	.shift = 0,
	.reg_addr = 0x4328,
};
struct reg_field dp_reg_field_266 = {
	.name = "Rate2_Cmn_Pll0_Vcocal_Pllcnt_Start",
	.bits_num = 16,
	.shift = 16,
	.reg_addr = 0x4328,
};
struct reg_info dp_reg_74 = {
	.reg_block_name = "dp",
	.reg_mmio_addr = 0x4328,
	.reg_sub_index = 0x4a,
	.field_num = 2,
	.reg_in_bytes = 4,
};
struct reg_field dp_reg_field_267 = {
	.name = "Rate2_Cmn_Pll0_Lock_Pllcnt_Thr",
	.bits_num = 16,
	.shift = 0,
	.reg_addr = 0x432c,
};
struct reg_field dp_reg_field_268 = {
	.name = "Rate2_Cmn_Pll0_Lock_Pllcnt_Start",
	.bits_num = 16,
	.shift = 16,
	.reg_addr = 0x432c,
};
struct reg_info dp_reg_75 = {
	.reg_block_name = "dp",
	.reg_mmio_addr = 0x432c,
	.reg_sub_index = 0x4b,
	.field_num = 2,
	.reg_in_bytes = 4,
};
struct reg_field dp_reg_field_269 = {
	.name = "Rate2_Cmn_Pll0_Ss_Ctrl2_M0",
	.bits_num = 16,
	.shift = 0,
	.reg_addr = 0x4330,
};
struct reg_field dp_reg_field_270 = {
	.name = "Rate2_Cmn_Pll0_Ss_Ctrl1_M0",
	.bits_num = 16,
	.shift = 16,
	.reg_addr = 0x4330,
};
struct reg_info dp_reg_76 = {
	.reg_block_name = "dp",
	.reg_mmio_addr = 0x4330,
	.reg_sub_index = 0x4c,
	.field_num = 2,
	.reg_in_bytes = 4,
};
struct reg_field dp_reg_field_271 = {
	.name = "Rate2_Cmn_Pll0_Ss_Ctrl4_M0",
	.bits_num = 16,
	.shift = 0,
	.reg_addr = 0x4334,
};
struct reg_field dp_reg_field_272 = {
	.name = "Rate2_Cmn_Pll0_Ss_Ctrl3_M0",
	.bits_num = 16,
	.shift = 16,
	.reg_addr = 0x4334,
};
struct reg_info dp_reg_77 = {
	.reg_block_name = "dp",
	.reg_mmio_addr = 0x4334,
	.reg_sub_index = 0x4d,
	.field_num = 2,
	.reg_in_bytes = 4,
};
struct reg_field dp_reg_field_273 = {
	.name = "Rate3_Cmn_Pdiag_Pll0_Cp_Iadj_M0",
	.bits_num = 16,
	.shift = 0,
	.reg_addr = 0x4338,
};
struct reg_field dp_reg_field_274 = {
	.name = "Rate3_Cmn_Pdiag_Pll0_Cp_Pajd_M0",
	.bits_num = 16,
	.shift = 16,
	.reg_addr = 0x4338,
};
struct reg_info dp_reg_78 = {
	.reg_block_name = "dp",
	.reg_mmio_addr = 0x4338,
	.reg_sub_index = 0x4e,
	.field_num = 2,
	.reg_in_bytes = 4,
};
struct reg_field dp_reg_field_275 = {
	.name = "Rate3_Cmn_Pll0_Intdiv_M0",
	.bits_num = 16,
	.shift = 0,
	.reg_addr = 0x433c,
};
struct reg_field dp_reg_field_276 = {
	.name = "Rate3_Cmn_Pdiag_Pll0_Filt_Padj_M0",
	.bits_num = 16,
	.shift = 16,
	.reg_addr = 0x433c,
};
struct reg_info dp_reg_79 = {
	.reg_block_name = "dp",
	.reg_mmio_addr = 0x433c,
	.reg_sub_index = 0x4f,
	.field_num = 2,
	.reg_in_bytes = 4,
};
struct reg_field dp_reg_field_277 = {
	.name = "Rate3_Cmn_Pll0_Fracdivh_M0",
	.bits_num = 16,
	.shift = 0,
	.reg_addr = 0x4340,
};
struct reg_field dp_reg_field_278 = {
	.name = "Rate3_Cmn_Pll0_Fracdivl_M0",
	.bits_num = 16,
	.shift = 16,
	.reg_addr = 0x4340,
};
struct reg_info dp_reg_80 = {
	.reg_block_name = "dp",
	.reg_mmio_addr = 0x4340,
	.reg_sub_index = 0x50,
	.field_num = 2,
	.reg_in_bytes = 4,
};
struct reg_field dp_reg_field_279 = {
	.name = "Rate3_Cmn_Pdiag_Pll0_Ctrl_M0",
	.bits_num = 16,
	.shift = 0,
	.reg_addr = 0x4344,
};
struct reg_field dp_reg_field_280 = {
	.name = "Rate3_Cmn_Pll0_High_Thr_M0",
	.bits_num = 16,
	.shift = 16,
	.reg_addr = 0x4344,
};
struct reg_info dp_reg_81 = {
	.reg_block_name = "dp",
	.reg_mmio_addr = 0x4344,
	.reg_sub_index = 0x51,
	.field_num = 2,
	.reg_in_bytes = 4,
};
struct reg_field dp_reg_field_281 = {
	.name = "Rate3_Cmn_Pll0_Lock_Refcnt_Start",
	.bits_num = 16,
	.shift = 0,
	.reg_addr = 0x4348,
};
struct reg_field dp_reg_field_282 = {
	.name = "Rate3_Cmn_Pll0_Vcocal_Pllcnt_Start",
	.bits_num = 16,
	.shift = 16,
	.reg_addr = 0x4348,
};
struct reg_info dp_reg_82 = {
	.reg_block_name = "dp",
	.reg_mmio_addr = 0x4348,
	.reg_sub_index = 0x52,
	.field_num = 2,
	.reg_in_bytes = 4,
};
struct reg_field dp_reg_field_283 = {
	.name = "Rate3_Cmn_Pll0_Lock_Pllcnt_Thr",
	.bits_num = 16,
	.shift = 0,
	.reg_addr = 0x434c,
};
struct reg_field dp_reg_field_284 = {
	.name = "Rate3_Cmn_Pll0_Lock_Pllcnt_Start",
	.bits_num = 16,
	.shift = 16,
	.reg_addr = 0x434c,
};
struct reg_info dp_reg_83 = {
	.reg_block_name = "dp",
	.reg_mmio_addr = 0x434c,
	.reg_sub_index = 0x53,
	.field_num = 2,
	.reg_in_bytes = 4,
};
struct reg_field dp_reg_field_285 = {
	.name = "Rate3_Cmn_Pll0_Ss_Ctrl2_M0",
	.bits_num = 16,
	.shift = 0,
	.reg_addr = 0x4350,
};
struct reg_field dp_reg_field_286 = {
	.name = "Rate3_Cmn_Pll0_Ss_Ctrl1_M0",
	.bits_num = 16,
	.shift = 16,
	.reg_addr = 0x4350,
};
struct reg_info dp_reg_84 = {
	.reg_block_name = "dp",
	.reg_mmio_addr = 0x4350,
	.reg_sub_index = 0x54,
	.field_num = 2,
	.reg_in_bytes = 4,
};
struct reg_field dp_reg_field_287 = {
	.name = "Rate3_Cmn_Pll0_Ss_Ctrl4_M0",
	.bits_num = 16,
	.shift = 0,
	.reg_addr = 0x4354,
};
struct reg_field dp_reg_field_288 = {
	.name = "Rate3_Cmn_Pll0_Ss_Ctrl3_M0",
	.bits_num = 16,
	.shift = 16,
	.reg_addr = 0x4354,
};
struct reg_info dp_reg_85 = {
	.reg_block_name = "dp",
	.reg_mmio_addr = 0x4354,
	.reg_sub_index = 0x55,
	.field_num = 2,
	.reg_in_bytes = 4,
};
struct reg_field dp_reg_field_289 = {
	.name = "Rate0_Xcvr_Diag_Hsclk_Div",
	.bits_num = 16,
	.shift = 0,
	.reg_addr = 0x4358,
};
struct reg_field dp_reg_field_290 = {
	.name = "Rate0_Cmn_Pdiag_Pll0_Clk_Sel_M0",
	.bits_num = 16,
	.shift = 16,
	.reg_addr = 0x4358,
};
struct reg_info dp_reg_86 = {
	.reg_block_name = "dp",
	.reg_mmio_addr = 0x4358,
	.reg_sub_index = 0x56,
	.field_num = 2,
	.reg_in_bytes = 4,
};
struct reg_field dp_reg_field_291 = {
	.name = "Rate1_Xcvr_Diag_Hsclk_Div",
	.bits_num = 16,
	.shift = 0,
	.reg_addr = 0x435c,
};
struct reg_field dp_reg_field_292 = {
	.name = "Rate1_Cmn_Pdiag_Pll0_Clk_Sel_M0",
	.bits_num = 16,
	.shift = 16,
	.reg_addr = 0x435c,
};
struct reg_info dp_reg_87 = {
	.reg_block_name = "dp",
	.reg_mmio_addr = 0x435c,
	.reg_sub_index = 0x57,
	.field_num = 2,
	.reg_in_bytes = 4,
};
struct reg_field dp_reg_field_293 = {
	.name = "Rate2_Xcvr_Diag_Hsclk_Div",
	.bits_num = 16,
	.shift = 0,
	.reg_addr = 0x4360,
};
struct reg_field dp_reg_field_294 = {
	.name = "Rate2_Cmn_Pdiag_Pll0_Clk_Sel_M0",
	.bits_num = 16,
	.shift = 16,
	.reg_addr = 0x4360,
};
struct reg_info dp_reg_88 = {
	.reg_block_name = "dp",
	.reg_mmio_addr = 0x4360,
	.reg_sub_index = 0x58,
	.field_num = 2,
	.reg_in_bytes = 4,
};
struct reg_field dp_reg_field_295 = {
	.name = "Rate3_Xcvr_Diag_Hsclk_Div",
	.bits_num = 16,
	.shift = 0,
	.reg_addr = 0x4364,
};
struct reg_field dp_reg_field_296 = {
	.name = "Rate3_Cmn_Pdiag_Pll0_Clk_Sel_M0",
	.bits_num = 16,
	.shift = 16,
	.reg_addr = 0x4364,
};
struct reg_info dp_reg_89 = {
	.reg_block_name = "dp",
	.reg_mmio_addr = 0x4364,
	.reg_sub_index = 0x59,
	.field_num = 2,
	.reg_in_bytes = 4,
};
struct reg_field dp_reg_field_297 = {
	.name = "Ephy_Lsb_First",
	.bits_num = 1,
	.shift = 0,
	.reg_addr = 0x4368,
};
struct reg_field dp_reg_field_298 = {
	.name = "Reserved_1",
	.bits_num = 2,
	.shift = 1,
	.reg_addr = 0x4368,
};
struct reg_field dp_reg_field_299 = {
	.name = "Mac_Div_Sel1_Ln",
	.bits_num = 9,
	.shift = 3,
	.reg_addr = 0x4368,
};
struct reg_field dp_reg_field_300 = {
	.name = "Mac_Div_Sel0_Ln",
	.bits_num = 7,
	.shift = 12,
	.reg_addr = 0x4368,
};
struct reg_field dp_reg_field_301 = {
	.name = "Mac_Src_Sel_Ln",
	.bits_num = 2,
	.shift = 19,
	.reg_addr = 0x4368,
};
struct reg_field dp_reg_field_302 = {
	.name = "Pma_Xcvr_Data_Width_Ln",
	.bits_num = 3,
	.shift = 21,
	.reg_addr = 0x4368,
};
struct reg_field dp_reg_field_303 = {
	.name = "Pma_Xcvr_Standard_Mode_Ln",
	.bits_num = 2,
	.shift = 24,
	.reg_addr = 0x4368,
};
struct reg_field dp_reg_field_304 = {
	.name = "Phy_Link_Mode",
	.bits_num = 2,
	.shift = 26,
	.reg_addr = 0x4368,
};
struct reg_field dp_reg_field_305 = {
	.name = "Phy_Link_Cfg_Ln",
	.bits_num = 4,
	.shift = 28,
	.reg_addr = 0x4368,
};
struct reg_info dp_reg_90 = {
	.reg_block_name = "dp",
	.reg_mmio_addr = 0x4368,
	.reg_sub_index = 0x5a,
	.field_num = 9,
	.reg_in_bytes = 4,
};
struct reg_field dp_reg_field_306 = {
	.name = "Reserved_1",
	.bits_num = 22,
	.shift = 0,
	.reg_addr = 0x436c,
};
struct reg_field dp_reg_field_307 = {
	.name = "Pma_Cmn_Refclk_Mode",
	.bits_num = 2,
	.shift = 22,
	.reg_addr = 0x436c,
};
struct reg_field dp_reg_field_308 = {
	.name = "Pma_Cmn_Ext_Refclk_Detected_Cfg",
	.bits_num = 1,
	.shift = 24,
	.reg_addr = 0x436c,
};
struct reg_field dp_reg_field_309 = {
	.name = "Pma_Cmn_Pll0_Refclk_Sel",
	.bits_num = 1,
	.shift = 25,
	.reg_addr = 0x436c,
};
struct reg_field dp_reg_field_310 = {
	.name = "Pma_Cmn_Refclk_Term_En",
	.bits_num = 1,
	.shift = 26,
	.reg_addr = 0x436c,
};
struct reg_field dp_reg_field_311 = {
	.name = "Pma_Cmn_Refclk_Dig_Div",
	.bits_num = 2,
	.shift = 27,
	.reg_addr = 0x436c,
};
struct reg_field dp_reg_field_312 = {
	.name = "Pma_Cmn_Refclk_Int_Mode",
	.bits_num = 2,
	.shift = 29,
	.reg_addr = 0x436c,
};
struct reg_field dp_reg_field_313 = {
	.name = "Pma_Cmn_Refclk_Dig_Sel",
	.bits_num = 1,
	.shift = 31,
	.reg_addr = 0x436c,
};
struct reg_info dp_reg_91 = {
	.reg_block_name = "dp",
	.reg_mmio_addr = 0x436c,
	.reg_sub_index = 0x5b,
	.field_num = 8,
	.reg_in_bytes = 4,
};
struct reg_field dp_reg_field_314 = {
	.name = "Pma_Rx_Eq_Eval_Ln_0",
	.bits_num = 1,
	.shift = 0,
	.reg_addr = 0x4370,
};
struct reg_field dp_reg_field_315 = {
	.name = "Pma_Rx_Eq_Training_Ln_0",
	.bits_num = 1,
	.shift = 1,
	.reg_addr = 0x4370,
};
struct reg_field dp_reg_field_316 = {
	.name = "Pma_Rx_Eq_Training_Data_Valid_Ln_0",
	.bits_num = 1,
	.shift = 2,
	.reg_addr = 0x4370,
};
struct reg_field dp_reg_field_317 = {
	.name = "Pma_Rx_Termination_Ln_0",
	.bits_num = 1,
	.shift = 3,
	.reg_addr = 0x4370,
};
struct reg_field dp_reg_field_318 = {
	.name = "Pma_Tx_Low_Power_Swing_En_Ln_0",
	.bits_num = 1,
	.shift = 4,
	.reg_addr = 0x4370,
};
struct reg_field dp_reg_field_319 = {
	.name = "Pma_Tx_Vmargin_Ln_0",
	.bits_num = 3,
	.shift = 5,
	.reg_addr = 0x4370,
};
struct reg_field dp_reg_field_320 = {
	.name = "Pma_Tx_Rcv_Detect_En_Ln_0",
	.bits_num = 1,
	.shift = 8,
	.reg_addr = 0x4370,
};
struct reg_field dp_reg_field_321 = {
	.name = "Pma_Tx_Local_Preset_Index_Ln_0",
	.bits_num = 4,
	.shift = 9,
	.reg_addr = 0x4370,
};
struct reg_field dp_reg_field_322 = {
	.name = "Pma_Tx_Get_Local_Preset_Coef_Ln_0",
	.bits_num = 1,
	.shift = 13,
	.reg_addr = 0x4370,
};
struct reg_field dp_reg_field_323 = {
	.name = "Pma_Tx_Deemphasis_Ln_0",
	.bits_num = 18,
	.shift = 14,
	.reg_addr = 0x4370,
};
struct reg_info dp_reg_92 = {
	.reg_block_name = "dp",
	.reg_mmio_addr = 0x4370,
	.reg_sub_index = 0x5c,
	.field_num = 10,
	.reg_in_bytes = 4,
};
struct reg_field dp_reg_field_324 = {
	.name = "Pma_Rx_Eq_Eval_Ln_1",
	.bits_num = 1,
	.shift = 0,
	.reg_addr = 0x4374,
};
struct reg_field dp_reg_field_325 = {
	.name = "Pma_Rx_Eq_Training_Ln_1",
	.bits_num = 1,
	.shift = 1,
	.reg_addr = 0x4374,
};
struct reg_field dp_reg_field_326 = {
	.name = "Pma_Rx_Eq_Training_Data_Valid_Ln_1",
	.bits_num = 1,
	.shift = 2,
	.reg_addr = 0x4374,
};
struct reg_field dp_reg_field_327 = {
	.name = "Pma_Rx_Termination_Ln_1",
	.bits_num = 1,
	.shift = 3,
	.reg_addr = 0x4374,
};
struct reg_field dp_reg_field_328 = {
	.name = "Pma_Tx_Low_Power_Swing_En_Ln_1",
	.bits_num = 1,
	.shift = 4,
	.reg_addr = 0x4374,
};
struct reg_field dp_reg_field_329 = {
	.name = "Pma_Tx_Vmargin_Ln_1",
	.bits_num = 3,
	.shift = 5,
	.reg_addr = 0x4374,
};
struct reg_field dp_reg_field_330 = {
	.name = "Pma_Tx_Rcv_Detect_En_Ln_1",
	.bits_num = 1,
	.shift = 8,
	.reg_addr = 0x4374,
};
struct reg_field dp_reg_field_331 = {
	.name = "Pma_Tx_Local_Preset_Index_Ln_1",
	.bits_num = 4,
	.shift = 9,
	.reg_addr = 0x4374,
};
struct reg_field dp_reg_field_332 = {
	.name = "Pma_Tx_Get_Local_Preset_Coef_Ln_1",
	.bits_num = 1,
	.shift = 13,
	.reg_addr = 0x4374,
};
struct reg_field dp_reg_field_333 = {
	.name = "Pma_Tx_Deemphasis_Ln_1",
	.bits_num = 18,
	.shift = 14,
	.reg_addr = 0x4374,
};
struct reg_info dp_reg_93 = {
	.reg_block_name = "dp",
	.reg_mmio_addr = 0x4374,
	.reg_sub_index = 0x5d,
	.field_num = 10,
	.reg_in_bytes = 4,
};
struct reg_field dp_reg_field_334 = {
	.name = "Pma_Rx_Eq_Eval_Ln_2",
	.bits_num = 1,
	.shift = 0,
	.reg_addr = 0x4378,
};
struct reg_field dp_reg_field_335 = {
	.name = "Pma_Rx_Eq_Training_Ln_2",
	.bits_num = 1,
	.shift = 1,
	.reg_addr = 0x4378,
};
struct reg_field dp_reg_field_336 = {
	.name = "Pma_Rx_Eq_Training_Data_Valid_Ln_2",
	.bits_num = 1,
	.shift = 2,
	.reg_addr = 0x4378,
};
struct reg_field dp_reg_field_337 = {
	.name = "Pma_Rx_Termination_Ln_2",
	.bits_num = 1,
	.shift = 3,
	.reg_addr = 0x4378,
};
struct reg_field dp_reg_field_338 = {
	.name = "Pma_Tx_Low_Power_Swing_En_Ln_2",
	.bits_num = 1,
	.shift = 4,
	.reg_addr = 0x4378,
};
struct reg_field dp_reg_field_339 = {
	.name = "Pma_Tx_Vmargin_Ln_2",
	.bits_num = 3,
	.shift = 5,
	.reg_addr = 0x4378,
};
struct reg_field dp_reg_field_340 = {
	.name = "Pma_Tx_Rcv_Detect_En_Ln_2",
	.bits_num = 1,
	.shift = 8,
	.reg_addr = 0x4378,
};
struct reg_field dp_reg_field_341 = {
	.name = "Pma_Tx_Local_Preset_Index_Ln_2",
	.bits_num = 4,
	.shift = 9,
	.reg_addr = 0x4378,
};
struct reg_field dp_reg_field_342 = {
	.name = "Pma_Tx_Get_Local_Preset_Coef_Ln_2",
	.bits_num = 1,
	.shift = 13,
	.reg_addr = 0x4378,
};
struct reg_field dp_reg_field_343 = {
	.name = "Pma_Tx_Deemphasis_Ln_2",
	.bits_num = 18,
	.shift = 14,
	.reg_addr = 0x4378,
};
struct reg_info dp_reg_94 = {
	.reg_block_name = "dp",
	.reg_mmio_addr = 0x4378,
	.reg_sub_index = 0x5e,
	.field_num = 10,
	.reg_in_bytes = 4,
};
struct reg_field dp_reg_field_344 = {
	.name = "Pma_Rx_Eq_Eval_Ln_3",
	.bits_num = 1,
	.shift = 0,
	.reg_addr = 0x437c,
};
struct reg_field dp_reg_field_345 = {
	.name = "Pma_Rx_Eq_Training_Ln_3",
	.bits_num = 1,
	.shift = 1,
	.reg_addr = 0x437c,
};
struct reg_field dp_reg_field_346 = {
	.name = "Pma_Rx_Eq_Training_Data_Valid_Ln_3",
	.bits_num = 1,
	.shift = 2,
	.reg_addr = 0x437c,
};
struct reg_field dp_reg_field_347 = {
	.name = "Pma_Rx_Termination_Ln_3",
	.bits_num = 1,
	.shift = 3,
	.reg_addr = 0x437c,
};
struct reg_field dp_reg_field_348 = {
	.name = "Pma_Tx_Low_Power_Swing_En_Ln_3",
	.bits_num = 1,
	.shift = 4,
	.reg_addr = 0x437c,
};
struct reg_field dp_reg_field_349 = {
	.name = "Pma_Tx_Vmargin_Ln_3",
	.bits_num = 3,
	.shift = 5,
	.reg_addr = 0x437c,
};
struct reg_field dp_reg_field_350 = {
	.name = "Pma_Tx_Rcv_Detect_En_Ln_3",
	.bits_num = 1,
	.shift = 8,
	.reg_addr = 0x437c,
};
struct reg_field dp_reg_field_351 = {
	.name = "Pma_Tx_Local_Preset_Index_Ln_3",
	.bits_num = 4,
	.shift = 9,
	.reg_addr = 0x437c,
};
struct reg_field dp_reg_field_352 = {
	.name = "Pma_Tx_Get_Local_Preset_Coef_Ln_3",
	.bits_num = 1,
	.shift = 13,
	.reg_addr = 0x437c,
};
struct reg_field dp_reg_field_353 = {
	.name = "Pma_Tx_Deemphasis_Ln_3",
	.bits_num = 18,
	.shift = 14,
	.reg_addr = 0x437c,
};
struct reg_info dp_reg_95 = {
	.reg_block_name = "dp",
	.reg_mmio_addr = 0x437c,
	.reg_sub_index = 0x5f,
	.field_num = 10,
	.reg_in_bytes = 4,
};
struct reg_field dp_reg_field_354 = {
	.name = "Dp_Pcie_Loop_Test",
	.bits_num = 1,
	.shift = 0,
	.reg_addr = 0x4380,
};
struct reg_field dp_reg_field_355 = {
	.name = "Dp_Pcie_Gen3",
	.bits_num = 1,
	.shift = 1,
	.reg_addr = 0x4380,
};
struct reg_field dp_reg_field_356 = {
	.name = "Dp_Pcie_Testpat_Mod",
	.bits_num = 4,
	.shift = 2,
	.reg_addr = 0x4380,
};
struct reg_field dp_reg_field_357 = {
	.name = "Dp_Pcie_Pat_Repeatnum",
	.bits_num = 8,
	.shift = 6,
	.reg_addr = 0x4380,
};
struct reg_field dp_reg_field_358 = {
	.name = "Signature_Rst",
	.bits_num = 1,
	.shift = 14,
	.reg_addr = 0x4380,
};
struct reg_field dp_reg_field_359 = {
	.name = "Reserved_1",
	.bits_num = 1,
	.shift = 15,
	.reg_addr = 0x4380,
};
struct reg_field dp_reg_field_360 = {
	.name = "Dp_Pcie_Pat_Dat_2",
	.bits_num = 16,
	.shift = 16,
	.reg_addr = 0x4380,
};
struct reg_info dp_reg_96 = {
	.reg_block_name = "dp",
	.reg_mmio_addr = 0x4380,
	.reg_sub_index = 0x60,
	.field_num = 7,
	.reg_in_bytes = 4,
};
struct reg_field dp_reg_field_361 = {
	.name = "Dp_Pcie_Pat_Dat_1",
	.bits_num = 32,
	.shift = 0,
	.reg_addr = 0x4384,
};
struct reg_info dp_reg_97 = {
	.reg_block_name = "dp",
	.reg_mmio_addr = 0x4384,
	.reg_sub_index = 0x61,
	.field_num = 1,
	.reg_in_bytes = 4,
};
struct reg_field dp_reg_field_362 = {
	.name = "Dp_Pcie_Pat_Dat_0",
	.bits_num = 32,
	.shift = 0,
	.reg_addr = 0x4388,
};
struct reg_info dp_reg_98 = {
	.reg_block_name = "dp",
	.reg_mmio_addr = 0x4388,
	.reg_sub_index = 0x62,
	.field_num = 1,
	.reg_in_bytes = 4,
};
struct reg_info * dp_reg_info[99] = {
&dp_reg_0,
&dp_reg_1,
&dp_reg_2,
&dp_reg_3,
&dp_reg_4,
&dp_reg_5,
&dp_reg_6,
&dp_reg_7,
&dp_reg_8,
&dp_reg_9,
&dp_reg_10,
&dp_reg_11,
&dp_reg_12,
&dp_reg_13,
&dp_reg_14,
&dp_reg_15,
&dp_reg_16,
&dp_reg_17,
&dp_reg_18,
&dp_reg_19,
&dp_reg_20,
&dp_reg_21,
&dp_reg_22,
&dp_reg_23,
&dp_reg_24,
&dp_reg_25,
&dp_reg_26,
&dp_reg_27,
&dp_reg_28,
&dp_reg_29,
&dp_reg_30,
&dp_reg_31,
&dp_reg_32,
&dp_reg_33,
&dp_reg_34,
&dp_reg_35,
&dp_reg_36,
&dp_reg_37,
&dp_reg_38,
&dp_reg_39,
&dp_reg_40,
&dp_reg_41,
&dp_reg_42,
&dp_reg_43,
&dp_reg_44,
&dp_reg_45,
&dp_reg_46,
&dp_reg_47,
&dp_reg_48,
&dp_reg_49,
&dp_reg_50,
&dp_reg_51,
&dp_reg_52,
&dp_reg_53,
&dp_reg_54,
&dp_reg_55,
&dp_reg_56,
&dp_reg_57,
&dp_reg_58,
&dp_reg_59,
&dp_reg_60,
&dp_reg_61,
&dp_reg_62,
&dp_reg_63,
&dp_reg_64,
&dp_reg_65,
&dp_reg_66,
&dp_reg_67,
&dp_reg_68,
&dp_reg_69,
&dp_reg_70,
&dp_reg_71,
&dp_reg_72,
&dp_reg_73,
&dp_reg_74,
&dp_reg_75,
&dp_reg_76,
&dp_reg_77,
&dp_reg_78,
&dp_reg_79,
&dp_reg_80,
&dp_reg_81,
&dp_reg_82,
&dp_reg_83,
&dp_reg_84,
&dp_reg_85,
&dp_reg_86,
&dp_reg_87,
&dp_reg_88,
&dp_reg_89,
&dp_reg_90,
&dp_reg_91,
&dp_reg_92,
&dp_reg_93,
&dp_reg_94,
&dp_reg_95,
&dp_reg_96,
&dp_reg_97,
&dp_reg_98,
};
struct reg_field * dp_reg_field_info[363] = {
&dp_reg_field_0,
&dp_reg_field_1,
&dp_reg_field_2,
&dp_reg_field_3,
&dp_reg_field_4,
&dp_reg_field_5,
&dp_reg_field_6,
&dp_reg_field_7,
&dp_reg_field_8,
&dp_reg_field_9,
&dp_reg_field_10,
&dp_reg_field_11,
&dp_reg_field_12,
&dp_reg_field_13,
&dp_reg_field_14,
&dp_reg_field_15,
&dp_reg_field_16,
&dp_reg_field_17,
&dp_reg_field_18,
&dp_reg_field_19,
&dp_reg_field_20,
&dp_reg_field_21,
&dp_reg_field_22,
&dp_reg_field_23,
&dp_reg_field_24,
&dp_reg_field_25,
&dp_reg_field_26,
&dp_reg_field_27,
&dp_reg_field_28,
&dp_reg_field_29,
&dp_reg_field_30,
&dp_reg_field_31,
&dp_reg_field_32,
&dp_reg_field_33,
&dp_reg_field_34,
&dp_reg_field_35,
&dp_reg_field_36,
&dp_reg_field_37,
&dp_reg_field_38,
&dp_reg_field_39,
&dp_reg_field_40,
&dp_reg_field_41,
&dp_reg_field_42,
&dp_reg_field_43,
&dp_reg_field_44,
&dp_reg_field_45,
&dp_reg_field_46,
&dp_reg_field_47,
&dp_reg_field_48,
&dp_reg_field_49,
&dp_reg_field_50,
&dp_reg_field_51,
&dp_reg_field_52,
&dp_reg_field_53,
&dp_reg_field_54,
&dp_reg_field_55,
&dp_reg_field_56,
&dp_reg_field_57,
&dp_reg_field_58,
&dp_reg_field_59,
&dp_reg_field_60,
&dp_reg_field_61,
&dp_reg_field_62,
&dp_reg_field_63,
&dp_reg_field_64,
&dp_reg_field_65,
&dp_reg_field_66,
&dp_reg_field_67,
&dp_reg_field_68,
&dp_reg_field_69,
&dp_reg_field_70,
&dp_reg_field_71,
&dp_reg_field_72,
&dp_reg_field_73,
&dp_reg_field_74,
&dp_reg_field_75,
&dp_reg_field_76,
&dp_reg_field_77,
&dp_reg_field_78,
&dp_reg_field_79,
&dp_reg_field_80,
&dp_reg_field_81,
&dp_reg_field_82,
&dp_reg_field_83,
&dp_reg_field_84,
&dp_reg_field_85,
&dp_reg_field_86,
&dp_reg_field_87,
&dp_reg_field_88,
&dp_reg_field_89,
&dp_reg_field_90,
&dp_reg_field_91,
&dp_reg_field_92,
&dp_reg_field_93,
&dp_reg_field_94,
&dp_reg_field_95,
&dp_reg_field_96,
&dp_reg_field_97,
&dp_reg_field_98,
&dp_reg_field_99,
&dp_reg_field_100,
&dp_reg_field_101,
&dp_reg_field_102,
&dp_reg_field_103,
&dp_reg_field_104,
&dp_reg_field_105,
&dp_reg_field_106,
&dp_reg_field_107,
&dp_reg_field_108,
&dp_reg_field_109,
&dp_reg_field_110,
&dp_reg_field_111,
&dp_reg_field_112,
&dp_reg_field_113,
&dp_reg_field_114,
&dp_reg_field_115,
&dp_reg_field_116,
&dp_reg_field_117,
&dp_reg_field_118,
&dp_reg_field_119,
&dp_reg_field_120,
&dp_reg_field_121,
&dp_reg_field_122,
&dp_reg_field_123,
&dp_reg_field_124,
&dp_reg_field_125,
&dp_reg_field_126,
&dp_reg_field_127,
&dp_reg_field_128,
&dp_reg_field_129,
&dp_reg_field_130,
&dp_reg_field_131,
&dp_reg_field_132,
&dp_reg_field_133,
&dp_reg_field_134,
&dp_reg_field_135,
&dp_reg_field_136,
&dp_reg_field_137,
&dp_reg_field_138,
&dp_reg_field_139,
&dp_reg_field_140,
&dp_reg_field_141,
&dp_reg_field_142,
&dp_reg_field_143,
&dp_reg_field_144,
&dp_reg_field_145,
&dp_reg_field_146,
&dp_reg_field_147,
&dp_reg_field_148,
&dp_reg_field_149,
&dp_reg_field_150,
&dp_reg_field_151,
&dp_reg_field_152,
&dp_reg_field_153,
&dp_reg_field_154,
&dp_reg_field_155,
&dp_reg_field_156,
&dp_reg_field_157,
&dp_reg_field_158,
&dp_reg_field_159,
&dp_reg_field_160,
&dp_reg_field_161,
&dp_reg_field_162,
&dp_reg_field_163,
&dp_reg_field_164,
&dp_reg_field_165,
&dp_reg_field_166,
&dp_reg_field_167,
&dp_reg_field_168,
&dp_reg_field_169,
&dp_reg_field_170,
&dp_reg_field_171,
&dp_reg_field_172,
&dp_reg_field_173,
&dp_reg_field_174,
&dp_reg_field_175,
&dp_reg_field_176,
&dp_reg_field_177,
&dp_reg_field_178,
&dp_reg_field_179,
&dp_reg_field_180,
&dp_reg_field_181,
&dp_reg_field_182,
&dp_reg_field_183,
&dp_reg_field_184,
&dp_reg_field_185,
&dp_reg_field_186,
&dp_reg_field_187,
&dp_reg_field_188,
&dp_reg_field_189,
&dp_reg_field_190,
&dp_reg_field_191,
&dp_reg_field_192,
&dp_reg_field_193,
&dp_reg_field_194,
&dp_reg_field_195,
&dp_reg_field_196,
&dp_reg_field_197,
&dp_reg_field_198,
&dp_reg_field_199,
&dp_reg_field_200,
&dp_reg_field_201,
&dp_reg_field_202,
&dp_reg_field_203,
&dp_reg_field_204,
&dp_reg_field_205,
&dp_reg_field_206,
&dp_reg_field_207,
&dp_reg_field_208,
&dp_reg_field_209,
&dp_reg_field_210,
&dp_reg_field_211,
&dp_reg_field_212,
&dp_reg_field_213,
&dp_reg_field_214,
&dp_reg_field_215,
&dp_reg_field_216,
&dp_reg_field_217,
&dp_reg_field_218,
&dp_reg_field_219,
&dp_reg_field_220,
&dp_reg_field_221,
&dp_reg_field_222,
&dp_reg_field_223,
&dp_reg_field_224,
&dp_reg_field_225,
&dp_reg_field_226,
&dp_reg_field_227,
&dp_reg_field_228,
&dp_reg_field_229,
&dp_reg_field_230,
&dp_reg_field_231,
&dp_reg_field_232,
&dp_reg_field_233,
&dp_reg_field_234,
&dp_reg_field_235,
&dp_reg_field_236,
&dp_reg_field_237,
&dp_reg_field_238,
&dp_reg_field_239,
&dp_reg_field_240,
&dp_reg_field_241,
&dp_reg_field_242,
&dp_reg_field_243,
&dp_reg_field_244,
&dp_reg_field_245,
&dp_reg_field_246,
&dp_reg_field_247,
&dp_reg_field_248,
&dp_reg_field_249,
&dp_reg_field_250,
&dp_reg_field_251,
&dp_reg_field_252,
&dp_reg_field_253,
&dp_reg_field_254,
&dp_reg_field_255,
&dp_reg_field_256,
&dp_reg_field_257,
&dp_reg_field_258,
&dp_reg_field_259,
&dp_reg_field_260,
&dp_reg_field_261,
&dp_reg_field_262,
&dp_reg_field_263,
&dp_reg_field_264,
&dp_reg_field_265,
&dp_reg_field_266,
&dp_reg_field_267,
&dp_reg_field_268,
&dp_reg_field_269,
&dp_reg_field_270,
&dp_reg_field_271,
&dp_reg_field_272,
&dp_reg_field_273,
&dp_reg_field_274,
&dp_reg_field_275,
&dp_reg_field_276,
&dp_reg_field_277,
&dp_reg_field_278,
&dp_reg_field_279,
&dp_reg_field_280,
&dp_reg_field_281,
&dp_reg_field_282,
&dp_reg_field_283,
&dp_reg_field_284,
&dp_reg_field_285,
&dp_reg_field_286,
&dp_reg_field_287,
&dp_reg_field_288,
&dp_reg_field_289,
&dp_reg_field_290,
&dp_reg_field_291,
&dp_reg_field_292,
&dp_reg_field_293,
&dp_reg_field_294,
&dp_reg_field_295,
&dp_reg_field_296,
&dp_reg_field_297,
&dp_reg_field_298,
&dp_reg_field_299,
&dp_reg_field_300,
&dp_reg_field_301,
&dp_reg_field_302,
&dp_reg_field_303,
&dp_reg_field_304,
&dp_reg_field_305,
&dp_reg_field_306,
&dp_reg_field_307,
&dp_reg_field_308,
&dp_reg_field_309,
&dp_reg_field_310,
&dp_reg_field_311,
&dp_reg_field_312,
&dp_reg_field_313,
&dp_reg_field_314,
&dp_reg_field_315,
&dp_reg_field_316,
&dp_reg_field_317,
&dp_reg_field_318,
&dp_reg_field_319,
&dp_reg_field_320,
&dp_reg_field_321,
&dp_reg_field_322,
&dp_reg_field_323,
&dp_reg_field_324,
&dp_reg_field_325,
&dp_reg_field_326,
&dp_reg_field_327,
&dp_reg_field_328,
&dp_reg_field_329,
&dp_reg_field_330,
&dp_reg_field_331,
&dp_reg_field_332,
&dp_reg_field_333,
&dp_reg_field_334,
&dp_reg_field_335,
&dp_reg_field_336,
&dp_reg_field_337,
&dp_reg_field_338,
&dp_reg_field_339,
&dp_reg_field_340,
&dp_reg_field_341,
&dp_reg_field_342,
&dp_reg_field_343,
&dp_reg_field_344,
&dp_reg_field_345,
&dp_reg_field_346,
&dp_reg_field_347,
&dp_reg_field_348,
&dp_reg_field_349,
&dp_reg_field_350,
&dp_reg_field_351,
&dp_reg_field_352,
&dp_reg_field_353,
&dp_reg_field_354,
&dp_reg_field_355,
&dp_reg_field_356,
&dp_reg_field_357,
&dp_reg_field_358,
&dp_reg_field_359,
&dp_reg_field_360,
&dp_reg_field_361,
&dp_reg_field_362,
};
unsigned int dp_reg_count = 99;
unsigned int dp_reg_start = 0x4200;
unsigned int dp_reg_end = 0x4388;
unsigned int dp_reg_in_bytes = 0x4;
unsigned int dp_reg_total_field_count = 363;
char * dp_reg_block_name = "dp";
