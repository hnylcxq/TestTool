#include "../reg.h"

struct reg_field codec_reg_field_0 = {
	.name = "Dclk_Ratio_31to0",
	.bits_num = 32,
	.shift = 0,
	.reg_addr = 0x4050,
};
struct reg_info codec_reg_0 = {
	.reg_block_name = "codec",
	.reg_mmio_addr = 0x4050,
	.reg_sub_index = 0x0,
	.field_num = 1,
	.reg_in_bytes = 4,
};
struct reg_field codec_reg_field_1 = {
	.name = "Codec_Dclk_Ratio_39to32",
	.bits_num = 8,
	.shift = 0,
	.reg_addr = 0x4054,
};
struct reg_field codec_reg_field_2 = {
	.name = "Read_Out_Control_Select",
	.bits_num = 8,
	.shift = 8,
	.reg_addr = 0x4054,
};
struct reg_field codec_reg_field_3 = {
	.name = "Load_Function_Group_Subsystemid",
	.bits_num = 1,
	.shift = 16,
	.reg_addr = 0x4054,
};
struct reg_field codec_reg_field_4 = {
	.name = "Load_Function_Group_Power_State",
	.bits_num = 1,
	.shift = 17,
	.reg_addr = 0x4054,
};
struct reg_field codec_reg_field_5 = {
	.name = "Reserved_1",
	.bits_num = 11,
	.shift = 18,
	.reg_addr = 0x4054,
};
struct reg_field codec_reg_field_6 = {
	.name = "Codec1_Mute_En",
	.bits_num = 1,
	.shift = 29,
	.reg_addr = 0x4054,
};
struct reg_field codec_reg_field_7 = {
	.name = "Force_Wake",
	.bits_num = 1,
	.shift = 30,
	.reg_addr = 0x4054,
};
struct reg_field codec_reg_field_8 = {
	.name = "Codec_Sw_Reset",
	.bits_num = 1,
	.shift = 31,
	.reg_addr = 0x4054,
};
struct reg_info codec_reg_1 = {
	.reg_block_name = "codec",
	.reg_mmio_addr = 0x4054,
	.reg_sub_index = 0x1,
	.field_num = 8,
	.reg_in_bytes = 4,
};
struct reg_field codec_reg_field_9 = {
	.name = "Hdaudio_Mode_Select",
	.bits_num = 1,
	.shift = 0,
	.reg_addr = 0x4058,
};
struct reg_field codec_reg_field_10 = {
	.name = "Resp_Generation",
	.bits_num = 1,
	.shift = 1,
	.reg_addr = 0x4058,
};
struct reg_field codec_reg_field_11 = {
	.name = "Resp_Ready",
	.bits_num = 1,
	.shift = 2,
	.reg_addr = 0x4058,
};
struct reg_field codec_reg_field_12 = {
	.name = "Send_Unsolresp",
	.bits_num = 1,
	.shift = 3,
	.reg_addr = 0x4058,
};
struct reg_field codec_reg_field_13 = {
	.name = "Hdaudio_Codec_Enable",
	.bits_num = 1,
	.shift = 4,
	.reg_addr = 0x4058,
};
struct reg_field codec_reg_field_14 = {
	.name = "Up_Sample_Incoming_Audio",
	.bits_num = 4,
	.shift = 5,
	.reg_addr = 0x4058,
};
struct reg_field codec_reg_field_15 = {
	.name = "Driver_Ready",
	.bits_num = 1,
	.shift = 9,
	.reg_addr = 0x4058,
};
struct reg_field codec_reg_field_16 = {
	.name = "Ignore_Driver_Ready",
	.bits_num = 1,
	.shift = 10,
	.reg_addr = 0x4058,
};
struct reg_field codec_reg_field_17 = {
	.name = "Down_Sample_Incoming_Audio_Factor",
	.bits_num = 4,
	.shift = 11,
	.reg_addr = 0x4058,
};
struct reg_field codec_reg_field_18 = {
	.name = "Use_Sw_Stream_Format",
	.bits_num = 1,
	.shift = 15,
	.reg_addr = 0x4058,
};
struct reg_field codec_reg_field_19 = {
	.name = "Sw_Stream_Format",
	.bits_num = 16,
	.shift = 16,
	.reg_addr = 0x4058,
};
struct reg_info codec_reg_2 = {
	.reg_block_name = "codec",
	.reg_mmio_addr = 0x4058,
	.reg_sub_index = 0x2,
	.field_num = 11,
	.reg_in_bytes = 4,
};
struct reg_field codec_reg_field_20 = {
	.name = "Hda_Hdmi_Cmd_Verb",
	.bits_num = 20,
	.shift = 0,
	.reg_addr = 0x405c,
};
struct reg_field codec_reg_field_21 = {
	.name = "Nid",
	.bits_num = 8,
	.shift = 20,
	.reg_addr = 0x405c,
};
struct reg_field codec_reg_field_22 = {
	.name = "Cad",
	.bits_num = 4,
	.shift = 28,
	.reg_addr = 0x405c,
};
struct reg_info codec_reg_3 = {
	.reg_block_name = "codec",
	.reg_mmio_addr = 0x405c,
	.reg_sub_index = 0x3,
	.field_num = 3,
	.reg_in_bytes = 4,
};
struct reg_field codec_reg_field_23 = {
	.name = "Response",
	.bits_num = 32,
	.shift = 0,
	.reg_addr = 0x4060,
};
struct reg_info codec_reg_4 = {
	.reg_block_name = "codec",
	.reg_mmio_addr = 0x4060,
	.reg_sub_index = 0x4,
	.field_num = 1,
	.reg_in_bytes = 4,
};
struct reg_field codec_reg_field_24 = {
	.name = "Eld_Read_Status",
	.bits_num = 1,
	.shift = 0,
	.reg_addr = 0x4064,
};
struct reg_field codec_reg_field_25 = {
	.name = "Dip_Write_Status",
	.bits_num = 1,
	.shift = 1,
	.reg_addr = 0x4064,
};
struct reg_field codec_reg_field_26 = {
	.name = "Dip_Read_Status",
	.bits_num = 1,
	.shift = 2,
	.reg_addr = 0x4064,
};
struct reg_field codec_reg_field_27 = {
	.name = "Hda_Setconvert_Int_Status",
	.bits_num = 1,
	.shift = 3,
	.reg_addr = 0x4064,
};
struct reg_field codec_reg_field_28 = {
	.name = "Hda_Cpcontrol_Int_Status",
	.bits_num = 1,
	.shift = 4,
	.reg_addr = 0x4064,
};
struct reg_field codec_reg_field_29 = {
	.name = "Set_Converter1_Digiconvert3_Int_Status",
	.bits_num = 1,
	.shift = 5,
	.reg_addr = 0x4064,
};
struct reg_field codec_reg_field_30 = {
	.name = "Set_Fungroup_Powerstate_Int_Status",
	.bits_num = 1,
	.shift = 6,
	.reg_addr = 0x4064,
};
struct reg_field codec_reg_field_31 = {
	.name = "Set_Eld_Default",
	.bits_num = 1,
	.shift = 7,
	.reg_addr = 0x4064,
};
struct reg_field codec_reg_field_32 = {
	.name = "Sample_Flat",
	.bits_num = 1,
	.shift = 8,
	.reg_addr = 0x4064,
};
struct reg_field codec_reg_field_33 = {
	.name = "Always_Output_Audio",
	.bits_num = 1,
	.shift = 9,
	.reg_addr = 0x4064,
};
struct reg_field codec_reg_field_34 = {
	.name = "Multiple_Sample",
	.bits_num = 1,
	.shift = 10,
	.reg_addr = 0x4064,
};
struct reg_field codec_reg_field_35 = {
	.name = "Faudio_Selsect",
	.bits_num = 1,
	.shift = 11,
	.reg_addr = 0x4064,
};
struct reg_field codec_reg_field_36 = {
	.name = "Ratio_Clk_Select",
	.bits_num = 1,
	.shift = 12,
	.reg_addr = 0x4064,
};
struct reg_field codec_reg_field_37 = {
	.name = "Codec_Type",
	.bits_num = 2,
	.shift = 13,
	.reg_addr = 0x4064,
};
struct reg_field codec_reg_field_38 = {
	.name = "Reserved_1",
	.bits_num = 9,
	.shift = 15,
	.reg_addr = 0x4064,
};
struct reg_field codec_reg_field_39 = {
	.name = "Eld_Use_Lut",
	.bits_num = 1,
	.shift = 24,
	.reg_addr = 0x4064,
};
struct reg_field codec_reg_field_40 = {
	.name = "Enable_Transmit_Dip_Packet",
	.bits_num = 1,
	.shift = 25,
	.reg_addr = 0x4064,
};
struct reg_field codec_reg_field_41 = {
	.name = "Enable_Hda_Pos_Ctr",
	.bits_num = 1,
	.shift = 26,
	.reg_addr = 0x4064,
};
struct reg_field codec_reg_field_42 = {
	.name = "Converter_Stream_Channel",
	.bits_num = 1,
	.shift = 27,
	.reg_addr = 0x4064,
};
struct reg_field codec_reg_field_43 = {
	.name = "Cp_Control_Ces_State",
	.bits_num = 1,
	.shift = 28,
	.reg_addr = 0x4064,
};
struct reg_field codec_reg_field_44 = {
	.name = "Cp_Control_Ready_Status",
	.bits_num = 1,
	.shift = 29,
	.reg_addr = 0x4064,
};
struct reg_field codec_reg_field_45 = {
	.name = "Channel_Status_Control",
	.bits_num = 2,
	.shift = 30,
	.reg_addr = 0x4064,
};
struct reg_info codec_reg_5 = {
	.reg_block_name = "codec",
	.reg_mmio_addr = 0x4064,
	.reg_sub_index = 0x5,
	.field_num = 22,
	.reg_in_bytes = 4,
};
struct reg_field codec_reg_field_46 = {
	.name = "Channel_Status_0",
	.bits_num = 1,
	.shift = 0,
	.reg_addr = 0x4068,
};
struct reg_field codec_reg_field_47 = {
	.name = "Channel_Status_1",
	.bits_num = 1,
	.shift = 1,
	.reg_addr = 0x4068,
};
struct reg_field codec_reg_field_48 = {
	.name = "Channel_Status_31_2",
	.bits_num = 30,
	.shift = 2,
	.reg_addr = 0x4068,
};
struct reg_info codec_reg_6 = {
	.reg_block_name = "codec",
	.reg_mmio_addr = 0x4068,
	.reg_sub_index = 0x6,
	.field_num = 3,
	.reg_in_bytes = 4,
};
struct reg_field codec_reg_field_49 = {
	.name = "Channel_Status_63_32",
	.bits_num = 32,
	.shift = 0,
	.reg_addr = 0x406c,
};
struct reg_info codec_reg_7 = {
	.reg_block_name = "codec",
	.reg_mmio_addr = 0x406c,
	.reg_sub_index = 0x7,
	.field_num = 1,
	.reg_in_bytes = 4,
};
struct reg_field codec_reg_field_50 = {
	.name = "Channel_Status_95_64",
	.bits_num = 32,
	.shift = 0,
	.reg_addr = 0x4070,
};
struct reg_info codec_reg_8 = {
	.reg_block_name = "codec",
	.reg_mmio_addr = 0x4070,
	.reg_sub_index = 0x8,
	.field_num = 1,
	.reg_in_bytes = 4,
};
struct reg_field codec_reg_field_51 = {
	.name = "Channel_Status_127_96",
	.bits_num = 32,
	.shift = 0,
	.reg_addr = 0x4074,
};
struct reg_info codec_reg_9 = {
	.reg_block_name = "codec",
	.reg_mmio_addr = 0x4074,
	.reg_sub_index = 0x9,
	.field_num = 1,
	.reg_in_bytes = 4,
};
struct reg_field codec_reg_field_52 = {
	.name = "Channel_Status_159_128",
	.bits_num = 32,
	.shift = 0,
	.reg_addr = 0x4078,
};
struct reg_info codec_reg_10 = {
	.reg_block_name = "codec",
	.reg_mmio_addr = 0x4078,
	.reg_sub_index = 0xa,
	.field_num = 1,
	.reg_in_bytes = 4,
};
struct reg_field codec_reg_field_53 = {
	.name = "Channel_Status_191_160",
	.bits_num = 32,
	.shift = 0,
	.reg_addr = 0x407c,
};
struct reg_info codec_reg_11 = {
	.reg_block_name = "codec",
	.reg_mmio_addr = 0x407c,
	.reg_sub_index = 0xb,
	.field_num = 1,
	.reg_in_bytes = 4,
};
struct reg_field codec_reg_field_54 = {
	.name = "Device_Id",
	.bits_num = 16,
	.shift = 0,
	.reg_addr = 0x4080,
};
struct reg_field codec_reg_field_55 = {
	.name = "Vendor_Id",
	.bits_num = 16,
	.shift = 16,
	.reg_addr = 0x4080,
};
struct reg_info codec_reg_12 = {
	.reg_block_name = "codec",
	.reg_mmio_addr = 0x4080,
	.reg_sub_index = 0xc,
	.field_num = 2,
	.reg_in_bytes = 4,
};
struct reg_field codec_reg_field_56 = {
	.name = "Stepping_Id",
	.bits_num = 8,
	.shift = 0,
	.reg_addr = 0x4084,
};
struct reg_field codec_reg_field_57 = {
	.name = "Revision_Id",
	.bits_num = 8,
	.shift = 8,
	.reg_addr = 0x4084,
};
struct reg_field codec_reg_field_58 = {
	.name = "Minrev",
	.bits_num = 4,
	.shift = 16,
	.reg_addr = 0x4084,
};
struct reg_field codec_reg_field_59 = {
	.name = "Majrev",
	.bits_num = 4,
	.shift = 20,
	.reg_addr = 0x4084,
};
struct reg_field codec_reg_field_60 = {
	.name = "Pcm_Support",
	.bits_num = 1,
	.shift = 24,
	.reg_addr = 0x4084,
};
struct reg_field codec_reg_field_61 = {
	.name = "Pcm_Float32_Only_Support",
	.bits_num = 1,
	.shift = 25,
	.reg_addr = 0x4084,
};
struct reg_field codec_reg_field_62 = {
	.name = "Ac3_16bit_Only_Support",
	.bits_num = 1,
	.shift = 26,
	.reg_addr = 0x4084,
};
struct reg_field codec_reg_field_63 = {
	.name = "Reserved_1",
	.bits_num = 1,
	.shift = 27,
	.reg_addr = 0x4084,
};
struct reg_field codec_reg_field_64 = {
	.name = "Supppowerstate_D0sup",
	.bits_num = 1,
	.shift = 28,
	.reg_addr = 0x4084,
};
struct reg_field codec_reg_field_65 = {
	.name = "Supppowerstate_D1sup",
	.bits_num = 1,
	.shift = 29,
	.reg_addr = 0x4084,
};
struct reg_field codec_reg_field_66 = {
	.name = "Supppowerstate_D2sup",
	.bits_num = 1,
	.shift = 30,
	.reg_addr = 0x4084,
};
struct reg_field codec_reg_field_67 = {
	.name = "Supppowerstate_D3sup",
	.bits_num = 1,
	.shift = 31,
	.reg_addr = 0x4084,
};
struct reg_info codec_reg_13 = {
	.reg_block_name = "codec",
	.reg_mmio_addr = 0x4084,
	.reg_sub_index = 0xd,
	.field_num = 12,
	.reg_in_bytes = 4,
};
struct reg_field codec_reg_field_68 = {
	.name = "Fungroup_Sub_Node_Count_Total",
	.bits_num = 8,
	.shift = 0,
	.reg_addr = 0x4088,
};
struct reg_field codec_reg_field_69 = {
	.name = "Reserved_2",
	.bits_num = 8,
	.shift = 8,
	.reg_addr = 0x4088,
};
struct reg_field codec_reg_field_70 = {
	.name = "Fungroup_Sub_Node_Start_Num",
	.bits_num = 8,
	.shift = 16,
	.reg_addr = 0x4088,
};
struct reg_field codec_reg_field_71 = {
	.name = "Reserved_1",
	.bits_num = 8,
	.shift = 24,
	.reg_addr = 0x4088,
};
struct reg_info codec_reg_14 = {
	.reg_block_name = "codec",
	.reg_mmio_addr = 0x4088,
	.reg_sub_index = 0xe,
	.field_num = 4,
	.reg_in_bytes = 4,
};
struct reg_field codec_reg_field_72 = {
	.name = "Afgc_Output_Delay",
	.bits_num = 4,
	.shift = 0,
	.reg_addr = 0x408c,
};
struct reg_field codec_reg_field_73 = {
	.name = "Reserved_5",
	.bits_num = 4,
	.shift = 4,
	.reg_addr = 0x408c,
};
struct reg_field codec_reg_field_74 = {
	.name = "Afgc_Input_Delay",
	.bits_num = 4,
	.shift = 8,
	.reg_addr = 0x408c,
};
struct reg_field codec_reg_field_75 = {
	.name = "Reserved_4",
	.bits_num = 4,
	.shift = 12,
	.reg_addr = 0x408c,
};
struct reg_field codec_reg_field_76 = {
	.name = "Afgc_Beepgen",
	.bits_num = 1,
	.shift = 16,
	.reg_addr = 0x408c,
};
struct reg_field codec_reg_field_77 = {
	.name = "Reserved_3",
	.bits_num = 2,
	.shift = 17,
	.reg_addr = 0x408c,
};
struct reg_field codec_reg_field_78 = {
	.name = "Epss",
	.bits_num = 1,
	.shift = 19,
	.reg_addr = 0x408c,
};
struct reg_field codec_reg_field_79 = {
	.name = "Clkstop",
	.bits_num = 1,
	.shift = 20,
	.reg_addr = 0x408c,
};
struct reg_field codec_reg_field_80 = {
	.name = "S3d3coldsup",
	.bits_num = 1,
	.shift = 21,
	.reg_addr = 0x408c,
};
struct reg_field codec_reg_field_81 = {
	.name = "D3coldsup",
	.bits_num = 1,
	.shift = 22,
	.reg_addr = 0x408c,
};
struct reg_field codec_reg_field_82 = {
	.name = "Afgt_Node_Type",
	.bits_num = 8,
	.shift = 23,
	.reg_addr = 0x408c,
};
struct reg_field codec_reg_field_83 = {
	.name = "Afgt_Unsol_Capable",
	.bits_num = 1,
	.shift = 31,
	.reg_addr = 0x408c,
};
struct reg_info codec_reg_15 = {
	.reg_block_name = "codec",
	.reg_mmio_addr = 0x408c,
	.reg_sub_index = 0xf,
	.field_num = 12,
	.reg_in_bytes = 4,
};
struct reg_field codec_reg_field_84 = {
	.name = "R1",
	.bits_num = 1,
	.shift = 0,
	.reg_addr = 0x4090,
};
struct reg_field codec_reg_field_85 = {
	.name = "R2",
	.bits_num = 1,
	.shift = 1,
	.reg_addr = 0x4090,
};
struct reg_field codec_reg_field_86 = {
	.name = "R3",
	.bits_num = 1,
	.shift = 2,
	.reg_addr = 0x4090,
};
struct reg_field codec_reg_field_87 = {
	.name = "R4",
	.bits_num = 1,
	.shift = 3,
	.reg_addr = 0x4090,
};
struct reg_field codec_reg_field_88 = {
	.name = "R5",
	.bits_num = 1,
	.shift = 4,
	.reg_addr = 0x4090,
};
struct reg_field codec_reg_field_89 = {
	.name = "R6",
	.bits_num = 1,
	.shift = 5,
	.reg_addr = 0x4090,
};
struct reg_field codec_reg_field_90 = {
	.name = "R7",
	.bits_num = 1,
	.shift = 6,
	.reg_addr = 0x4090,
};
struct reg_field codec_reg_field_91 = {
	.name = "R8",
	.bits_num = 1,
	.shift = 7,
	.reg_addr = 0x4090,
};
struct reg_field codec_reg_field_92 = {
	.name = "R9",
	.bits_num = 1,
	.shift = 8,
	.reg_addr = 0x4090,
};
struct reg_field codec_reg_field_93 = {
	.name = "R10",
	.bits_num = 1,
	.shift = 9,
	.reg_addr = 0x4090,
};
struct reg_field codec_reg_field_94 = {
	.name = "R11",
	.bits_num = 1,
	.shift = 10,
	.reg_addr = 0x4090,
};
struct reg_field codec_reg_field_95 = {
	.name = "R12",
	.bits_num = 1,
	.shift = 11,
	.reg_addr = 0x4090,
};
struct reg_field codec_reg_field_96 = {
	.name = "Reserved_2",
	.bits_num = 4,
	.shift = 12,
	.reg_addr = 0x4090,
};
struct reg_field codec_reg_field_97 = {
	.name = "B8",
	.bits_num = 1,
	.shift = 16,
	.reg_addr = 0x4090,
};
struct reg_field codec_reg_field_98 = {
	.name = "B16",
	.bits_num = 1,
	.shift = 17,
	.reg_addr = 0x4090,
};
struct reg_field codec_reg_field_99 = {
	.name = "B20",
	.bits_num = 1,
	.shift = 18,
	.reg_addr = 0x4090,
};
struct reg_field codec_reg_field_100 = {
	.name = "B24",
	.bits_num = 1,
	.shift = 19,
	.reg_addr = 0x4090,
};
struct reg_field codec_reg_field_101 = {
	.name = "B32",
	.bits_num = 1,
	.shift = 20,
	.reg_addr = 0x4090,
};
struct reg_field codec_reg_field_102 = {
	.name = "Reserved_1",
	.bits_num = 11,
	.shift = 21,
	.reg_addr = 0x4090,
};
struct reg_info codec_reg_16 = {
	.reg_block_name = "codec",
	.reg_mmio_addr = 0x4090,
	.reg_sub_index = 0x10,
	.field_num = 19,
	.reg_in_bytes = 4,
};
struct reg_field codec_reg_field_103 = {
	.name = "Outputampc_Offset",
	.bits_num = 7,
	.shift = 0,
	.reg_addr = 0x4094,
};
struct reg_field codec_reg_field_104 = {
	.name = "Reserved_3",
	.bits_num = 1,
	.shift = 7,
	.reg_addr = 0x4094,
};
struct reg_field codec_reg_field_105 = {
	.name = "Outputampc_Numsteps",
	.bits_num = 7,
	.shift = 8,
	.reg_addr = 0x4094,
};
struct reg_field codec_reg_field_106 = {
	.name = "Reserved_2",
	.bits_num = 1,
	.shift = 15,
	.reg_addr = 0x4094,
};
struct reg_field codec_reg_field_107 = {
	.name = "Outputampc_Stepsize",
	.bits_num = 7,
	.shift = 16,
	.reg_addr = 0x4094,
};
struct reg_field codec_reg_field_108 = {
	.name = "Reserved_1",
	.bits_num = 8,
	.shift = 23,
	.reg_addr = 0x4094,
};
struct reg_field codec_reg_field_109 = {
	.name = "Outputampc_Mute_Capable",
	.bits_num = 1,
	.shift = 31,
	.reg_addr = 0x4094,
};
struct reg_info codec_reg_17 = {
	.reg_block_name = "codec",
	.reg_mmio_addr = 0x4094,
	.reg_sub_index = 0x11,
	.field_num = 7,
	.reg_in_bytes = 4,
};
struct reg_field codec_reg_field_110 = {
	.name = "Fungroup_Subsystemid_Ssid",
	.bits_num = 32,
	.shift = 0,
	.reg_addr = 0x4098,
};
struct reg_info codec_reg_18 = {
	.reg_block_name = "codec",
	.reg_mmio_addr = 0x4098,
	.reg_sub_index = 0x12,
	.field_num = 1,
	.reg_in_bytes = 4,
};
struct reg_field codec_reg_field_111 = {
	.name = "Stereo",
	.bits_num = 1,
	.shift = 0,
	.reg_addr = 0x409c,
};
struct reg_field codec_reg_field_112 = {
	.name = "In_Amp_Present",
	.bits_num = 1,
	.shift = 1,
	.reg_addr = 0x409c,
};
struct reg_field codec_reg_field_113 = {
	.name = "Out_Amp_Present",
	.bits_num = 1,
	.shift = 2,
	.reg_addr = 0x409c,
};
struct reg_field codec_reg_field_114 = {
	.name = "Amp_Param_Override",
	.bits_num = 1,
	.shift = 3,
	.reg_addr = 0x409c,
};
struct reg_field codec_reg_field_115 = {
	.name = "Format_Override",
	.bits_num = 1,
	.shift = 4,
	.reg_addr = 0x409c,
};
struct reg_field codec_reg_field_116 = {
	.name = "Stripe",
	.bits_num = 1,
	.shift = 5,
	.reg_addr = 0x409c,
};
struct reg_field codec_reg_field_117 = {
	.name = "Proc_Widget",
	.bits_num = 1,
	.shift = 6,
	.reg_addr = 0x409c,
};
struct reg_field codec_reg_field_118 = {
	.name = "Unsol_Capable",
	.bits_num = 1,
	.shift = 7,
	.reg_addr = 0x409c,
};
struct reg_field codec_reg_field_119 = {
	.name = "Conn_List",
	.bits_num = 1,
	.shift = 8,
	.reg_addr = 0x409c,
};
struct reg_field codec_reg_field_120 = {
	.name = "Digital",
	.bits_num = 1,
	.shift = 9,
	.reg_addr = 0x409c,
};
struct reg_field codec_reg_field_121 = {
	.name = "Power_Cntrl",
	.bits_num = 1,
	.shift = 10,
	.reg_addr = 0x409c,
};
struct reg_field codec_reg_field_122 = {
	.name = "Lr_Swap",
	.bits_num = 1,
	.shift = 11,
	.reg_addr = 0x409c,
};
struct reg_field codec_reg_field_123 = {
	.name = "Reserved_3",
	.bits_num = 4,
	.shift = 12,
	.reg_addr = 0x409c,
};
struct reg_field codec_reg_field_124 = {
	.name = "Delay",
	.bits_num = 4,
	.shift = 16,
	.reg_addr = 0x409c,
};
struct reg_field codec_reg_field_125 = {
	.name = "Type",
	.bits_num = 4,
	.shift = 20,
	.reg_addr = 0x409c,
};
struct reg_field codec_reg_field_126 = {
	.name = "Reserved_1",
	.bits_num = 8,
	.shift = 24,
	.reg_addr = 0x409c,
};
struct reg_info codec_reg_19 = {
	.reg_block_name = "codec",
	.reg_mmio_addr = 0x409c,
	.reg_sub_index = 0x13,
	.field_num = 16,
	.reg_in_bytes = 4,
};
struct reg_field codec_reg_field_127 = {
	.name = "Stereo",
	.bits_num = 1,
	.shift = 0,
	.reg_addr = 0x40a0,
};
struct reg_field codec_reg_field_128 = {
	.name = "In_Amp_Present",
	.bits_num = 1,
	.shift = 1,
	.reg_addr = 0x40a0,
};
struct reg_field codec_reg_field_129 = {
	.name = "Out_Amp_Present",
	.bits_num = 1,
	.shift = 2,
	.reg_addr = 0x40a0,
};
struct reg_field codec_reg_field_130 = {
	.name = "Amp_Param_Override",
	.bits_num = 1,
	.shift = 3,
	.reg_addr = 0x40a0,
};
struct reg_field codec_reg_field_131 = {
	.name = "Format_Override",
	.bits_num = 1,
	.shift = 4,
	.reg_addr = 0x40a0,
};
struct reg_field codec_reg_field_132 = {
	.name = "Stripe",
	.bits_num = 1,
	.shift = 5,
	.reg_addr = 0x40a0,
};
struct reg_field codec_reg_field_133 = {
	.name = "Proc_Widget",
	.bits_num = 1,
	.shift = 6,
	.reg_addr = 0x40a0,
};
struct reg_field codec_reg_field_134 = {
	.name = "Unsol_Capable",
	.bits_num = 1,
	.shift = 7,
	.reg_addr = 0x40a0,
};
struct reg_field codec_reg_field_135 = {
	.name = "Conn_List",
	.bits_num = 1,
	.shift = 8,
	.reg_addr = 0x40a0,
};
struct reg_field codec_reg_field_136 = {
	.name = "Digital",
	.bits_num = 1,
	.shift = 9,
	.reg_addr = 0x40a0,
};
struct reg_field codec_reg_field_137 = {
	.name = "Power_Cntrl",
	.bits_num = 1,
	.shift = 10,
	.reg_addr = 0x40a0,
};
struct reg_field codec_reg_field_138 = {
	.name = "Lr_Swap",
	.bits_num = 1,
	.shift = 11,
	.reg_addr = 0x40a0,
};
struct reg_field codec_reg_field_139 = {
	.name = "Reserved_3",
	.bits_num = 4,
	.shift = 12,
	.reg_addr = 0x40a0,
};
struct reg_field codec_reg_field_140 = {
	.name = "Delay",
	.bits_num = 4,
	.shift = 16,
	.reg_addr = 0x40a0,
};
struct reg_field codec_reg_field_141 = {
	.name = "Type",
	.bits_num = 4,
	.shift = 20,
	.reg_addr = 0x40a0,
};
struct reg_field codec_reg_field_142 = {
	.name = "Reserved_1",
	.bits_num = 8,
	.shift = 24,
	.reg_addr = 0x40a0,
};
struct reg_info codec_reg_20 = {
	.reg_block_name = "codec",
	.reg_mmio_addr = 0x40a0,
	.reg_sub_index = 0x14,
	.field_num = 16,
	.reg_in_bytes = 4,
};
struct reg_field codec_reg_field_143 = {
	.name = "Impedance_Sense_Capable",
	.bits_num = 1,
	.shift = 0,
	.reg_addr = 0x40a4,
};
struct reg_field codec_reg_field_144 = {
	.name = "Trigger_Req",
	.bits_num = 1,
	.shift = 1,
	.reg_addr = 0x40a4,
};
struct reg_field codec_reg_field_145 = {
	.name = "Presense_Detect_Capable",
	.bits_num = 1,
	.shift = 2,
	.reg_addr = 0x40a4,
};
struct reg_field codec_reg_field_146 = {
	.name = "Headphone_Drive_Capable",
	.bits_num = 1,
	.shift = 3,
	.reg_addr = 0x40a4,
};
struct reg_field codec_reg_field_147 = {
	.name = "Output_Capable",
	.bits_num = 1,
	.shift = 4,
	.reg_addr = 0x40a4,
};
struct reg_field codec_reg_field_148 = {
	.name = "Input_Capable",
	.bits_num = 1,
	.shift = 5,
	.reg_addr = 0x40a4,
};
struct reg_field codec_reg_field_149 = {
	.name = "Balanced_Io_Pins",
	.bits_num = 1,
	.shift = 6,
	.reg_addr = 0x40a4,
};
struct reg_field codec_reg_field_150 = {
	.name = "Hdmi",
	.bits_num = 1,
	.shift = 7,
	.reg_addr = 0x40a4,
};
struct reg_field codec_reg_field_151 = {
	.name = "Vref_Control__Hiz",
	.bits_num = 1,
	.shift = 8,
	.reg_addr = 0x40a4,
};
struct reg_field codec_reg_field_152 = {
	.name = "Vref_Control_150_Percent",
	.bits_num = 1,
	.shift = 9,
	.reg_addr = 0x40a4,
};
struct reg_field codec_reg_field_153 = {
	.name = "Vref_Control_2_Ground",
	.bits_num = 1,
	.shift = 10,
	.reg_addr = 0x40a4,
};
struct reg_field codec_reg_field_154 = {
	.name = "Reserved_4",
	.bits_num = 1,
	.shift = 11,
	.reg_addr = 0x40a4,
};
struct reg_field codec_reg_field_155 = {
	.name = "Vref_Control4_80percent",
	.bits_num = 1,
	.shift = 12,
	.reg_addr = 0x40a4,
};
struct reg_field codec_reg_field_156 = {
	.name = "Vref_Control5_100percent",
	.bits_num = 1,
	.shift = 13,
	.reg_addr = 0x40a4,
};
struct reg_field codec_reg_field_157 = {
	.name = "Reserved_3",
	.bits_num = 2,
	.shift = 14,
	.reg_addr = 0x40a4,
};
struct reg_field codec_reg_field_158 = {
	.name = "Eapd_Capable",
	.bits_num = 1,
	.shift = 16,
	.reg_addr = 0x40a4,
};
struct reg_field codec_reg_field_159 = {
	.name = "Reserved_2",
	.bits_num = 10,
	.shift = 17,
	.reg_addr = 0x40a4,
};
struct reg_field codec_reg_field_160 = {
	.name = "Hbr_Enable",
	.bits_num = 1,
	.shift = 27,
	.reg_addr = 0x40a4,
};
struct reg_field codec_reg_field_161 = {
	.name = "Reserved_1",
	.bits_num = 4,
	.shift = 28,
	.reg_addr = 0x40a4,
};
struct reg_info codec_reg_21 = {
	.reg_block_name = "codec",
	.reg_mmio_addr = 0x40a4,
	.reg_sub_index = 0x15,
	.field_num = 19,
	.reg_in_bytes = 4,
};
struct reg_field codec_reg_field_162 = {
	.name = "Config_Default_Sequence",
	.bits_num = 4,
	.shift = 0,
	.reg_addr = 0x40a8,
};
struct reg_field codec_reg_field_163 = {
	.name = "Config_Default_Default_Assn",
	.bits_num = 4,
	.shift = 4,
	.reg_addr = 0x40a8,
};
struct reg_field codec_reg_field_164 = {
	.name = "Config_Default_Misc",
	.bits_num = 4,
	.shift = 8,
	.reg_addr = 0x40a8,
};
struct reg_field codec_reg_field_165 = {
	.name = "Config_Default_Color",
	.bits_num = 4,
	.shift = 12,
	.reg_addr = 0x40a8,
};
struct reg_field codec_reg_field_166 = {
	.name = "Config_Default_Connect_Type",
	.bits_num = 4,
	.shift = 16,
	.reg_addr = 0x40a8,
};
struct reg_field codec_reg_field_167 = {
	.name = "Config_Default_Device",
	.bits_num = 4,
	.shift = 20,
	.reg_addr = 0x40a8,
};
struct reg_field codec_reg_field_168 = {
	.name = "Config_Default_Location_Lowbits",
	.bits_num = 4,
	.shift = 24,
	.reg_addr = 0x40a8,
};
struct reg_field codec_reg_field_169 = {
	.name = "Config_Default_Location_Hibits",
	.bits_num = 2,
	.shift = 28,
	.reg_addr = 0x40a8,
};
struct reg_field codec_reg_field_170 = {
	.name = "Config_Default_Port_Connectivity",
	.bits_num = 2,
	.shift = 30,
	.reg_addr = 0x40a8,
};
struct reg_info codec_reg_22 = {
	.reg_block_name = "codec",
	.reg_mmio_addr = 0x40a8,
	.reg_sub_index = 0x16,
	.field_num = 9,
	.reg_in_bytes = 4,
};
struct reg_field codec_reg_field_171 = {
	.name = "Converter_Format_Chan",
	.bits_num = 4,
	.shift = 0,
	.reg_addr = 0x40ac,
};
struct reg_field codec_reg_field_172 = {
	.name = "Converter_Format_Bits",
	.bits_num = 3,
	.shift = 4,
	.reg_addr = 0x40ac,
};
struct reg_field codec_reg_field_173 = {
	.name = "Reserved_3",
	.bits_num = 1,
	.shift = 7,
	.reg_addr = 0x40ac,
};
struct reg_field codec_reg_field_174 = {
	.name = "Converter_Format_Div",
	.bits_num = 3,
	.shift = 8,
	.reg_addr = 0x40ac,
};
struct reg_field codec_reg_field_175 = {
	.name = "Converter_Format_Mult",
	.bits_num = 3,
	.shift = 11,
	.reg_addr = 0x40ac,
};
struct reg_field codec_reg_field_176 = {
	.name = "Converter_Format_Base",
	.bits_num = 1,
	.shift = 14,
	.reg_addr = 0x40ac,
};
struct reg_field codec_reg_field_177 = {
	.name = "Converter_Format_Type",
	.bits_num = 1,
	.shift = 15,
	.reg_addr = 0x40ac,
};
struct reg_field codec_reg_field_178 = {
	.name = "Reserved_1",
	.bits_num = 8,
	.shift = 16,
	.reg_addr = 0x40ac,
};
struct reg_field codec_reg_field_179 = {
	.name = "Converter_Channel",
	.bits_num = 4,
	.shift = 24,
	.reg_addr = 0x40ac,
};
struct reg_field codec_reg_field_180 = {
	.name = "Converter_Stream",
	.bits_num = 4,
	.shift = 28,
	.reg_addr = 0x40ac,
};
struct reg_info codec_reg_23 = {
	.reg_block_name = "codec",
	.reg_mmio_addr = 0x40ac,
	.reg_sub_index = 0x17,
	.field_num = 10,
	.reg_in_bytes = 4,
};
struct reg_field codec_reg_field_181 = {
	.name = "Converter1_Digiconvert_Sic_Digen",
	.bits_num = 1,
	.shift = 0,
	.reg_addr = 0x40b0,
};
struct reg_field codec_reg_field_182 = {
	.name = "Converter1_Digiconvert_Sic_Vcfg",
	.bits_num = 1,
	.shift = 1,
	.reg_addr = 0x40b0,
};
struct reg_field codec_reg_field_183 = {
	.name = "Converter1_Digiconvert_Sic_Vcfg",
	.bits_num = 1,
	.shift = 2,
	.reg_addr = 0x40b0,
};
struct reg_field codec_reg_field_184 = {
	.name = "Converter1_Digiconvert_Sic_Pre",
	.bits_num = 1,
	.shift = 3,
	.reg_addr = 0x40b0,
};
struct reg_field codec_reg_field_185 = {
	.name = "Converter1_Digiconvert_Sic_Copy",
	.bits_num = 1,
	.shift = 4,
	.reg_addr = 0x40b0,
};
struct reg_field codec_reg_field_186 = {
	.name = "Converter1_Digiconvert_Sic_Audio",
	.bits_num = 1,
	.shift = 5,
	.reg_addr = 0x40b0,
};
struct reg_field codec_reg_field_187 = {
	.name = "Converter1_Digiconvert_Sic_Pro",
	.bits_num = 1,
	.shift = 6,
	.reg_addr = 0x40b0,
};
struct reg_field codec_reg_field_188 = {
	.name = "Converter1_Digiconvert_Sicl",
	.bits_num = 1,
	.shift = 7,
	.reg_addr = 0x40b0,
};
struct reg_field codec_reg_field_189 = {
	.name = "Converter1_Digiconvert_Siccc_6to0",
	.bits_num = 7,
	.shift = 8,
	.reg_addr = 0x40b0,
};
struct reg_field codec_reg_field_190 = {
	.name = "Converter1_Digiconvert_Sic",
	.bits_num = 1,
	.shift = 15,
	.reg_addr = 0x40b0,
};
struct reg_field codec_reg_field_191 = {
	.name = "Iec_Coding_Type",
	.bits_num = 4,
	.shift = 16,
	.reg_addr = 0x40b0,
};
struct reg_field codec_reg_field_192 = {
	.name = "Disable_Non_Audio",
	.bits_num = 1,
	.shift = 20,
	.reg_addr = 0x40b0,
};
struct reg_field codec_reg_field_193 = {
	.name = "Copy_Bit_Polarity",
	.bits_num = 1,
	.shift = 21,
	.reg_addr = 0x40b0,
};
struct reg_field codec_reg_field_194 = {
	.name = "Enable_73_Verb",
	.bits_num = 1,
	.shift = 22,
	.reg_addr = 0x40b0,
};
struct reg_field codec_reg_field_195 = {
	.name = "Keep_Alive_Enable",
	.bits_num = 1,
	.shift = 23,
	.reg_addr = 0x40b0,
};
struct reg_field codec_reg_field_196 = {
	.name = "Enableunsol_Tag",
	.bits_num = 6,
	.shift = 24,
	.reg_addr = 0x40b0,
};
struct reg_field codec_reg_field_197 = {
	.name = "Enableunsol_Bit6",
	.bits_num = 1,
	.shift = 30,
	.reg_addr = 0x40b0,
};
struct reg_field codec_reg_field_198 = {
	.name = "Enableunsol_Enable",
	.bits_num = 1,
	.shift = 31,
	.reg_addr = 0x40b0,
};
struct reg_info codec_reg_24 = {
	.reg_block_name = "codec",
	.reg_mmio_addr = 0x40b0,
	.reg_sub_index = 0x18,
	.field_num = 18,
	.reg_in_bytes = 4,
};
struct reg_field codec_reg_field_199 = {
	.name = "Converter1_Stripe_Control",
	.bits_num = 2,
	.shift = 0,
	.reg_addr = 0x40b4,
};
struct reg_field codec_reg_field_200 = {
	.name = "Reserved_2",
	.bits_num = 6,
	.shift = 2,
	.reg_addr = 0x40b4,
};
struct reg_field codec_reg_field_201 = {
	.name = "Undefined",
	.bits_num = 12,
	.shift = 8,
	.reg_addr = 0x40b4,
};
struct reg_field codec_reg_field_202 = {
	.name = "Capability__Bit0",
	.bits_num = 1,
	.shift = 20,
	.reg_addr = 0x40b4,
};
struct reg_field codec_reg_field_203 = {
	.name = "Capability__Bit1",
	.bits_num = 1,
	.shift = 21,
	.reg_addr = 0x40b4,
};
struct reg_field codec_reg_field_204 = {
	.name = "Capability__Bit2",
	.bits_num = 1,
	.shift = 22,
	.reg_addr = 0x40b4,
};
struct reg_field codec_reg_field_205 = {
	.name = "Reserved_1",
	.bits_num = 9,
	.shift = 23,
	.reg_addr = 0x40b4,
};
struct reg_info codec_reg_25 = {
	.reg_block_name = "codec",
	.reg_mmio_addr = 0x40b4,
	.reg_sub_index = 0x19,
	.field_num = 7,
	.reg_in_bytes = 4,
};
struct reg_field codec_reg_field_206 = {
	.name = "Rightchnl",
	.bits_num = 1,
	.shift = 0,
	.reg_addr = 0x40b8,
};
struct reg_field codec_reg_field_207 = {
	.name = "Impedance",
	.bits_num = 30,
	.shift = 1,
	.reg_addr = 0x40b8,
};
struct reg_field codec_reg_field_208 = {
	.name = "Presense_Detect",
	.bits_num = 1,
	.shift = 31,
	.reg_addr = 0x40b8,
};
struct reg_info codec_reg_26 = {
	.reg_block_name = "codec",
	.reg_mmio_addr = 0x40b8,
	.reg_sub_index = 0x1a,
	.field_num = 3,
	.reg_in_bytes = 4,
};
struct reg_field codec_reg_field_209 = {
	.name = "Pinwidget1_Control__Vrefen",
	.bits_num = 3,
	.shift = 0,
	.reg_addr = 0x40bc,
};
struct reg_field codec_reg_field_210 = {
	.name = "Reserved_2",
	.bits_num = 2,
	.shift = 3,
	.reg_addr = 0x40bc,
};
struct reg_field codec_reg_field_211 = {
	.name = "Pinwidget1_Control__In_Enable",
	.bits_num = 1,
	.shift = 5,
	.reg_addr = 0x40bc,
};
struct reg_field codec_reg_field_212 = {
	.name = "Pinwidget1_Control__Out_Enable",
	.bits_num = 1,
	.shift = 6,
	.reg_addr = 0x40bc,
};
struct reg_field codec_reg_field_213 = {
	.name = "Pinwidget1_Control__Hphn_Enable",
	.bits_num = 1,
	.shift = 7,
	.reg_addr = 0x40bc,
};
struct reg_field codec_reg_field_214 = {
	.name = "Fungroup_Power_State_Ps_Setpsact",
	.bits_num = 4,
	.shift = 8,
	.reg_addr = 0x40bc,
};
struct reg_field codec_reg_field_215 = {
	.name = "Power_State",
	.bits_num = 7,
	.shift = 12,
	.reg_addr = 0x40bc,
};
struct reg_field codec_reg_field_216 = {
	.name = "Hda_Power_Saving",
	.bits_num = 1,
	.shift = 19,
	.reg_addr = 0x40bc,
};
struct reg_field codec_reg_field_217 = {
	.name = "Ps_Settingsreset",
	.bits_num = 1,
	.shift = 20,
	.reg_addr = 0x40bc,
};
struct reg_field codec_reg_field_218 = {
	.name = "Reserved_1",
	.bits_num = 11,
	.shift = 21,
	.reg_addr = 0x40bc,
};
struct reg_info codec_reg_27 = {
	.reg_block_name = "codec",
	.reg_mmio_addr = 0x40bc,
	.reg_sub_index = 0x1b,
	.field_num = 10,
	.reg_in_bytes = 4,
};
struct reg_field codec_reg_field_219 = {
	.name = "Converter_Channel_Count",
	.bits_num = 8,
	.shift = 0,
	.reg_addr = 0x40c0,
};
struct reg_field codec_reg_field_220 = {
	.name = "Byte_Offset_Into_Eld",
	.bits_num = 8,
	.shift = 8,
	.reg_addr = 0x40c0,
};
struct reg_field codec_reg_field_221 = {
	.name = "Eld_Buffer_Size",
	.bits_num = 8,
	.shift = 16,
	.reg_addr = 0x40c0,
};
struct reg_field codec_reg_field_222 = {
	.name = "Dip_Packet_Buffer_Size",
	.bits_num = 3,
	.shift = 24,
	.reg_addr = 0x40c0,
};
struct reg_field codec_reg_field_223 = {
	.name = "Dip_Pi_Base_Size",
	.bits_num = 5,
	.shift = 27,
	.reg_addr = 0x40c0,
};
struct reg_info codec_reg_28 = {
	.reg_block_name = "codec",
	.reg_mmio_addr = 0x40c0,
	.reg_sub_index = 0x1c,
	.field_num = 5,
	.reg_in_bytes = 4,
};
struct reg_field codec_reg_field_224 = {
	.name = "Aspchannelmap_Slot_0",
	.bits_num = 4,
	.shift = 0,
	.reg_addr = 0x40c4,
};
struct reg_field codec_reg_field_225 = {
	.name = "Aspchannelmap_Slot_1",
	.bits_num = 4,
	.shift = 4,
	.reg_addr = 0x40c4,
};
struct reg_field codec_reg_field_226 = {
	.name = "Aspchannelmap_Slot_2",
	.bits_num = 4,
	.shift = 8,
	.reg_addr = 0x40c4,
};
struct reg_field codec_reg_field_227 = {
	.name = "Aspchannelmap_Slot_3",
	.bits_num = 4,
	.shift = 12,
	.reg_addr = 0x40c4,
};
struct reg_field codec_reg_field_228 = {
	.name = "Aspchannelmap_Slot_4",
	.bits_num = 4,
	.shift = 16,
	.reg_addr = 0x40c4,
};
struct reg_field codec_reg_field_229 = {
	.name = "Aspchannelmap_Slot_5",
	.bits_num = 4,
	.shift = 20,
	.reg_addr = 0x40c4,
};
struct reg_field codec_reg_field_230 = {
	.name = "Aspchannelmap_Slot_6",
	.bits_num = 4,
	.shift = 24,
	.reg_addr = 0x40c4,
};
struct reg_field codec_reg_field_231 = {
	.name = "Aspchannelmap_Slot_7",
	.bits_num = 4,
	.shift = 28,
	.reg_addr = 0x40c4,
};
struct reg_info codec_reg_29 = {
	.reg_block_name = "codec",
	.reg_mmio_addr = 0x40c4,
	.reg_sub_index = 0x1d,
	.field_num = 8,
	.reg_in_bytes = 4,
};
struct reg_field codec_reg_field_232 = {
	.name = "Dipxmitctrl_Pi0",
	.bits_num = 2,
	.shift = 0,
	.reg_addr = 0x40c8,
};
struct reg_field codec_reg_field_233 = {
	.name = "Dipxmitctrl_Pi1",
	.bits_num = 2,
	.shift = 2,
	.reg_addr = 0x40c8,
};
struct reg_field codec_reg_field_234 = {
	.name = "Dipxmitctrl_Pi2",
	.bits_num = 2,
	.shift = 4,
	.reg_addr = 0x40c8,
};
struct reg_field codec_reg_field_235 = {
	.name = "Dipxmitctrl_Pi3",
	.bits_num = 2,
	.shift = 6,
	.reg_addr = 0x40c8,
};
struct reg_field codec_reg_field_236 = {
	.name = "Dipxmitctrl_Pi4",
	.bits_num = 2,
	.shift = 8,
	.reg_addr = 0x40c8,
};
struct reg_field codec_reg_field_237 = {
	.name = "Dipxmitctrl_Pi5",
	.bits_num = 2,
	.shift = 10,
	.reg_addr = 0x40c8,
};
struct reg_field codec_reg_field_238 = {
	.name = "Dipxmitctrl_Pi6",
	.bits_num = 2,
	.shift = 12,
	.reg_addr = 0x40c8,
};
struct reg_field codec_reg_field_239 = {
	.name = "Dipxmitctrl_Pi7",
	.bits_num = 2,
	.shift = 14,
	.reg_addr = 0x40c8,
};
struct reg_field codec_reg_field_240 = {
	.name = "Cpcontrol_Requested_State",
	.bits_num = 2,
	.shift = 16,
	.reg_addr = 0x40c8,
};
struct reg_field codec_reg_field_241 = {
	.name = "Cpcontrol_0",
	.bits_num = 1,
	.shift = 18,
	.reg_addr = 0x40c8,
};
struct reg_field codec_reg_field_242 = {
	.name = "Cpcontrol_Ur_Subtag",
	.bits_num = 5,
	.shift = 19,
	.reg_addr = 0x40c8,
};
struct reg_field codec_reg_field_243 = {
	.name = "Onebit_Audioen",
	.bits_num = 1,
	.shift = 24,
	.reg_addr = 0x40c8,
};
struct reg_field codec_reg_field_244 = {
	.name = "Onebit_Audio_Mapping",
	.bits_num = 1,
	.shift = 25,
	.reg_addr = 0x40c8,
};
struct reg_field codec_reg_field_245 = {
	.name = "Eld_Rdstatus_Control",
	.bits_num = 1,
	.shift = 26,
	.reg_addr = 0x40c8,
};
struct reg_field codec_reg_field_246 = {
	.name = "Dip_Write_Status_Control",
	.bits_num = 1,
	.shift = 27,
	.reg_addr = 0x40c8,
};
struct reg_field codec_reg_field_247 = {
	.name = "Dip_Read_Status_Control",
	.bits_num = 1,
	.shift = 28,
	.reg_addr = 0x40c8,
};
struct reg_field codec_reg_field_248 = {
	.name = "Reserved_1",
	.bits_num = 3,
	.shift = 29,
	.reg_addr = 0x40c8,
};
struct reg_info codec_reg_30 = {
	.reg_block_name = "codec",
	.reg_mmio_addr = 0x40c8,
	.reg_sub_index = 0x1e,
	.field_num = 17,
	.reg_in_bytes = 4,
};
struct reg_field codec_reg_field_249 = {
	.name = "Load_Converter1_Streamformat",
	.bits_num = 1,
	.shift = 0,
	.reg_addr = 0x40cc,
};
struct reg_field codec_reg_field_250 = {
	.name = "Load_Converter1_Chanstreamid",
	.bits_num = 1,
	.shift = 1,
	.reg_addr = 0x40cc,
};
struct reg_field codec_reg_field_251 = {
	.name = "Load_Converter1_Digiconvert",
	.bits_num = 1,
	.shift = 2,
	.reg_addr = 0x40cc,
};
struct reg_field codec_reg_field_252 = {
	.name = "Load_Pinwidget1_Unsoliresponse",
	.bits_num = 1,
	.shift = 3,
	.reg_addr = 0x40cc,
};
struct reg_field codec_reg_field_253 = {
	.name = "Load_Converter1_Stripecontrol",
	.bits_num = 1,
	.shift = 4,
	.reg_addr = 0x40cc,
};
struct reg_field codec_reg_field_254 = {
	.name = "Load_Pinwidget1_Pinsense",
	.bits_num = 1,
	.shift = 5,
	.reg_addr = 0x40cc,
};
struct reg_field codec_reg_field_255 = {
	.name = "Load_Pinwidget1_Control",
	.bits_num = 1,
	.shift = 6,
	.reg_addr = 0x40cc,
};
struct reg_field codec_reg_field_256 = {
	.name = "Load_Pinwidget1_Configdefault",
	.bits_num = 1,
	.shift = 7,
	.reg_addr = 0x40cc,
};
struct reg_field codec_reg_field_257 = {
	.name = "Load_Convert1_Converter_Channel_Count",
	.bits_num = 1,
	.shift = 8,
	.reg_addr = 0x40cc,
};
struct reg_field codec_reg_field_258 = {
	.name = "Load_Asp_Channel_Mapping",
	.bits_num = 1,
	.shift = 9,
	.reg_addr = 0x40cc,
};
struct reg_field codec_reg_field_259 = {
	.name = "Load_Eld_Offset",
	.bits_num = 1,
	.shift = 10,
	.reg_addr = 0x40cc,
};
struct reg_field codec_reg_field_260 = {
	.name = "Load_Dip_Xmitctrl",
	.bits_num = 1,
	.shift = 11,
	.reg_addr = 0x40cc,
};
struct reg_field codec_reg_field_261 = {
	.name = "Load_Cp_Control",
	.bits_num = 1,
	.shift = 12,
	.reg_addr = 0x40cc,
};
struct reg_field codec_reg_field_262 = {
	.name = "Load_Onebit_Audio_Control",
	.bits_num = 1,
	.shift = 13,
	.reg_addr = 0x40cc,
};
struct reg_field codec_reg_field_263 = {
	.name = "Reserved_1",
	.bits_num = 18,
	.shift = 14,
	.reg_addr = 0x40cc,
};
struct reg_info codec_reg_31 = {
	.reg_block_name = "codec",
	.reg_mmio_addr = 0x40cc,
	.reg_sub_index = 0x1f,
	.field_num = 15,
	.reg_in_bytes = 4,
};
struct reg_field codec_reg_field_264 = {
	.name = "Codec_Read_Out",
	.bits_num = 32,
	.shift = 0,
	.reg_addr = 0x40d0,
};
struct reg_info codec_reg_32 = {
	.reg_block_name = "codec",
	.reg_mmio_addr = 0x40d0,
	.reg_sub_index = 0x20,
	.field_num = 1,
	.reg_in_bytes = 4,
};
struct reg_info * codec_reg_info[33] = {
&codec_reg_0,
&codec_reg_1,
&codec_reg_2,
&codec_reg_3,
&codec_reg_4,
&codec_reg_5,
&codec_reg_6,
&codec_reg_7,
&codec_reg_8,
&codec_reg_9,
&codec_reg_10,
&codec_reg_11,
&codec_reg_12,
&codec_reg_13,
&codec_reg_14,
&codec_reg_15,
&codec_reg_16,
&codec_reg_17,
&codec_reg_18,
&codec_reg_19,
&codec_reg_20,
&codec_reg_21,
&codec_reg_22,
&codec_reg_23,
&codec_reg_24,
&codec_reg_25,
&codec_reg_26,
&codec_reg_27,
&codec_reg_28,
&codec_reg_29,
&codec_reg_30,
&codec_reg_31,
&codec_reg_32,
};
struct reg_field * codec_reg_field_info[265] = {
&codec_reg_field_0,
&codec_reg_field_1,
&codec_reg_field_2,
&codec_reg_field_3,
&codec_reg_field_4,
&codec_reg_field_5,
&codec_reg_field_6,
&codec_reg_field_7,
&codec_reg_field_8,
&codec_reg_field_9,
&codec_reg_field_10,
&codec_reg_field_11,
&codec_reg_field_12,
&codec_reg_field_13,
&codec_reg_field_14,
&codec_reg_field_15,
&codec_reg_field_16,
&codec_reg_field_17,
&codec_reg_field_18,
&codec_reg_field_19,
&codec_reg_field_20,
&codec_reg_field_21,
&codec_reg_field_22,
&codec_reg_field_23,
&codec_reg_field_24,
&codec_reg_field_25,
&codec_reg_field_26,
&codec_reg_field_27,
&codec_reg_field_28,
&codec_reg_field_29,
&codec_reg_field_30,
&codec_reg_field_31,
&codec_reg_field_32,
&codec_reg_field_33,
&codec_reg_field_34,
&codec_reg_field_35,
&codec_reg_field_36,
&codec_reg_field_37,
&codec_reg_field_38,
&codec_reg_field_39,
&codec_reg_field_40,
&codec_reg_field_41,
&codec_reg_field_42,
&codec_reg_field_43,
&codec_reg_field_44,
&codec_reg_field_45,
&codec_reg_field_46,
&codec_reg_field_47,
&codec_reg_field_48,
&codec_reg_field_49,
&codec_reg_field_50,
&codec_reg_field_51,
&codec_reg_field_52,
&codec_reg_field_53,
&codec_reg_field_54,
&codec_reg_field_55,
&codec_reg_field_56,
&codec_reg_field_57,
&codec_reg_field_58,
&codec_reg_field_59,
&codec_reg_field_60,
&codec_reg_field_61,
&codec_reg_field_62,
&codec_reg_field_63,
&codec_reg_field_64,
&codec_reg_field_65,
&codec_reg_field_66,
&codec_reg_field_67,
&codec_reg_field_68,
&codec_reg_field_69,
&codec_reg_field_70,
&codec_reg_field_71,
&codec_reg_field_72,
&codec_reg_field_73,
&codec_reg_field_74,
&codec_reg_field_75,
&codec_reg_field_76,
&codec_reg_field_77,
&codec_reg_field_78,
&codec_reg_field_79,
&codec_reg_field_80,
&codec_reg_field_81,
&codec_reg_field_82,
&codec_reg_field_83,
&codec_reg_field_84,
&codec_reg_field_85,
&codec_reg_field_86,
&codec_reg_field_87,
&codec_reg_field_88,
&codec_reg_field_89,
&codec_reg_field_90,
&codec_reg_field_91,
&codec_reg_field_92,
&codec_reg_field_93,
&codec_reg_field_94,
&codec_reg_field_95,
&codec_reg_field_96,
&codec_reg_field_97,
&codec_reg_field_98,
&codec_reg_field_99,
&codec_reg_field_100,
&codec_reg_field_101,
&codec_reg_field_102,
&codec_reg_field_103,
&codec_reg_field_104,
&codec_reg_field_105,
&codec_reg_field_106,
&codec_reg_field_107,
&codec_reg_field_108,
&codec_reg_field_109,
&codec_reg_field_110,
&codec_reg_field_111,
&codec_reg_field_112,
&codec_reg_field_113,
&codec_reg_field_114,
&codec_reg_field_115,
&codec_reg_field_116,
&codec_reg_field_117,
&codec_reg_field_118,
&codec_reg_field_119,
&codec_reg_field_120,
&codec_reg_field_121,
&codec_reg_field_122,
&codec_reg_field_123,
&codec_reg_field_124,
&codec_reg_field_125,
&codec_reg_field_126,
&codec_reg_field_127,
&codec_reg_field_128,
&codec_reg_field_129,
&codec_reg_field_130,
&codec_reg_field_131,
&codec_reg_field_132,
&codec_reg_field_133,
&codec_reg_field_134,
&codec_reg_field_135,
&codec_reg_field_136,
&codec_reg_field_137,
&codec_reg_field_138,
&codec_reg_field_139,
&codec_reg_field_140,
&codec_reg_field_141,
&codec_reg_field_142,
&codec_reg_field_143,
&codec_reg_field_144,
&codec_reg_field_145,
&codec_reg_field_146,
&codec_reg_field_147,
&codec_reg_field_148,
&codec_reg_field_149,
&codec_reg_field_150,
&codec_reg_field_151,
&codec_reg_field_152,
&codec_reg_field_153,
&codec_reg_field_154,
&codec_reg_field_155,
&codec_reg_field_156,
&codec_reg_field_157,
&codec_reg_field_158,
&codec_reg_field_159,
&codec_reg_field_160,
&codec_reg_field_161,
&codec_reg_field_162,
&codec_reg_field_163,
&codec_reg_field_164,
&codec_reg_field_165,
&codec_reg_field_166,
&codec_reg_field_167,
&codec_reg_field_168,
&codec_reg_field_169,
&codec_reg_field_170,
&codec_reg_field_171,
&codec_reg_field_172,
&codec_reg_field_173,
&codec_reg_field_174,
&codec_reg_field_175,
&codec_reg_field_176,
&codec_reg_field_177,
&codec_reg_field_178,
&codec_reg_field_179,
&codec_reg_field_180,
&codec_reg_field_181,
&codec_reg_field_182,
&codec_reg_field_183,
&codec_reg_field_184,
&codec_reg_field_185,
&codec_reg_field_186,
&codec_reg_field_187,
&codec_reg_field_188,
&codec_reg_field_189,
&codec_reg_field_190,
&codec_reg_field_191,
&codec_reg_field_192,
&codec_reg_field_193,
&codec_reg_field_194,
&codec_reg_field_195,
&codec_reg_field_196,
&codec_reg_field_197,
&codec_reg_field_198,
&codec_reg_field_199,
&codec_reg_field_200,
&codec_reg_field_201,
&codec_reg_field_202,
&codec_reg_field_203,
&codec_reg_field_204,
&codec_reg_field_205,
&codec_reg_field_206,
&codec_reg_field_207,
&codec_reg_field_208,
&codec_reg_field_209,
&codec_reg_field_210,
&codec_reg_field_211,
&codec_reg_field_212,
&codec_reg_field_213,
&codec_reg_field_214,
&codec_reg_field_215,
&codec_reg_field_216,
&codec_reg_field_217,
&codec_reg_field_218,
&codec_reg_field_219,
&codec_reg_field_220,
&codec_reg_field_221,
&codec_reg_field_222,
&codec_reg_field_223,
&codec_reg_field_224,
&codec_reg_field_225,
&codec_reg_field_226,
&codec_reg_field_227,
&codec_reg_field_228,
&codec_reg_field_229,
&codec_reg_field_230,
&codec_reg_field_231,
&codec_reg_field_232,
&codec_reg_field_233,
&codec_reg_field_234,
&codec_reg_field_235,
&codec_reg_field_236,
&codec_reg_field_237,
&codec_reg_field_238,
&codec_reg_field_239,
&codec_reg_field_240,
&codec_reg_field_241,
&codec_reg_field_242,
&codec_reg_field_243,
&codec_reg_field_244,
&codec_reg_field_245,
&codec_reg_field_246,
&codec_reg_field_247,
&codec_reg_field_248,
&codec_reg_field_249,
&codec_reg_field_250,
&codec_reg_field_251,
&codec_reg_field_252,
&codec_reg_field_253,
&codec_reg_field_254,
&codec_reg_field_255,
&codec_reg_field_256,
&codec_reg_field_257,
&codec_reg_field_258,
&codec_reg_field_259,
&codec_reg_field_260,
&codec_reg_field_261,
&codec_reg_field_262,
&codec_reg_field_263,
&codec_reg_field_264,
};
unsigned int codec_reg_count = 33;
unsigned int codec_reg_start = 0x4050;
unsigned int codec_reg_end = 0x40d0;
unsigned int codec_reg_in_bytes = 0x4;
unsigned int codec_reg_total_field_count = 265;
char * codec_reg_block_name = "codec";
