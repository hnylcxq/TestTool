#include "../reg.h"

struct reg_field hdmi_reg_field_0 = {
	.name = "Interrupt_Mode",
	.bits_num = 1,
	.shift = 0,
	.reg_addr = 0x4400,
};
struct reg_field hdmi_reg_field_1 = {
	.name = "Ycbcr422_Convertion_Mode",
	.bits_num = 1,
	.shift = 1,
	.reg_addr = 0x4400,
};
struct reg_field hdmi_reg_field_2 = {
	.name = "Enable_Dc_Gpkt",
	.bits_num = 1,
	.shift = 2,
	.reg_addr = 0x4400,
};
struct reg_field hdmi_reg_field_3 = {
	.name = "Disable_Packet_Num_Vblank",
	.bits_num = 1,
	.shift = 3,
	.reg_addr = 0x4400,
};
struct reg_field hdmi_reg_field_4 = {
	.name = "Packet_Num_Hblank",
	.bits_num = 4,
	.shift = 4,
	.reg_addr = 0x4400,
};
struct reg_field hdmi_reg_field_5 = {
	.name = "Packet_Num_Vblank",
	.bits_num = 8,
	.shift = 8,
	.reg_addr = 0x4400,
};
struct reg_field hdmi_reg_field_6 = {
	.name = "Base_Of_Delay_For_Hdcp",
	.bits_num = 1,
	.shift = 16,
	.reg_addr = 0x4400,
};
struct reg_field hdmi_reg_field_7 = {
	.name = "Delay_For_Hdcp",
	.bits_num = 7,
	.shift = 17,
	.reg_addr = 0x4400,
};
struct reg_field hdmi_reg_field_8 = {
	.name = "Ycbcr422_Convertion",
	.bits_num = 1,
	.shift = 24,
	.reg_addr = 0x4400,
};
struct reg_field hdmi_reg_field_9 = {
	.name = "Video_Pixel_Format_For_Tmds_Channels",
	.bits_num = 1,
	.shift = 25,
	.reg_addr = 0x4400,
};
struct reg_field hdmi_reg_field_10 = {
	.name = "Dvi_Mode",
	.bits_num = 1,
	.shift = 26,
	.reg_addr = 0x4400,
};
struct reg_field hdmi_reg_field_11 = {
	.name = "Video_Clip",
	.bits_num = 1,
	.shift = 27,
	.reg_addr = 0x4400,
};
struct reg_field hdmi_reg_field_12 = {
	.name = "Deep_Color_Mode",
	.bits_num = 2,
	.shift = 28,
	.reg_addr = 0x4400,
};
struct reg_field hdmi_reg_field_13 = {
	.name = "Hdmi_Enable",
	.bits_num = 1,
	.shift = 30,
	.reg_addr = 0x4400,
};
struct reg_field hdmi_reg_field_14 = {
	.name = "Hdmi_Reset",
	.bits_num = 1,
	.shift = 31,
	.reg_addr = 0x4400,
};
struct reg_info hdmi_reg_0 = {
	.reg_block_name = "hdmi",
	.reg_mmio_addr = 0x4400,
	.reg_sub_index = 0x0,
	.field_num = 15,
	.reg_in_bytes = 4,
};
struct reg_field hdmi_reg_field_15 = {
	.name = "Reserved_1",
	.bits_num = 4,
	.shift = 0,
	.reg_addr = 0x4404,
};
struct reg_field hdmi_reg_field_16 = {
	.name = "Vsync_Invert_Enable",
	.bits_num = 1,
	.shift = 4,
	.reg_addr = 0x4404,
};
struct reg_field hdmi_reg_field_17 = {
	.name = "Hsync_Invert_Enable",
	.bits_num = 1,
	.shift = 5,
	.reg_addr = 0x4404,
};
struct reg_field hdmi_reg_field_18 = {
	.name = "Clock_Lane_Enable",
	.bits_num = 1,
	.shift = 6,
	.reg_addr = 0x4404,
};
struct reg_field hdmi_reg_field_19 = {
	.name = "Infoframe_Fifo_Length",
	.bits_num = 5,
	.shift = 7,
	.reg_addr = 0x4404,
};
struct reg_field hdmi_reg_field_20 = {
	.name = "Transmit_After_650_Enable",
	.bits_num = 1,
	.shift = 12,
	.reg_addr = 0x4404,
};
struct reg_field hdmi_reg_field_21 = {
	.name = "Transmit_Between_385_507_Enable",
	.bits_num = 1,
	.shift = 13,
	.reg_addr = 0x4404,
};
struct reg_field hdmi_reg_field_22 = {
	.name = "Transmit_Between_300_Enable",
	.bits_num = 1,
	.shift = 14,
	.reg_addr = 0x4404,
};
struct reg_field hdmi_reg_field_23 = {
	.name = "Infoframe_Fifo1_Length",
	.bits_num = 5,
	.shift = 15,
	.reg_addr = 0x4404,
};
struct reg_field hdmi_reg_field_24 = {
	.name = "Infoframe_Fifo2_Start_Address",
	.bits_num = 4,
	.shift = 20,
	.reg_addr = 0x4404,
};
struct reg_field hdmi_reg_field_25 = {
	.name = "Infoframe_Fifo1_Start_Address",
	.bits_num = 4,
	.shift = 24,
	.reg_addr = 0x4404,
};
struct reg_field hdmi_reg_field_26 = {
	.name = "Info_Vsync_En",
	.bits_num = 1,
	.shift = 28,
	.reg_addr = 0x4404,
};
struct reg_field hdmi_reg_field_27 = {
	.name = "Infoframe_Fifo_Ready",
	.bits_num = 1,
	.shift = 29,
	.reg_addr = 0x4404,
};
struct reg_field hdmi_reg_field_28 = {
	.name = "Infoframe_Fifo1_Ready",
	.bits_num = 1,
	.shift = 30,
	.reg_addr = 0x4404,
};
struct reg_field hdmi_reg_field_29 = {
	.name = "Infoframe_Fifo2_Select",
	.bits_num = 1,
	.shift = 31,
	.reg_addr = 0x4404,
};
struct reg_info hdmi_reg_1 = {
	.reg_block_name = "hdmi",
	.reg_mmio_addr = 0x4404,
	.reg_sub_index = 0x1,
	.field_num = 15,
	.reg_in_bytes = 4,
};
struct reg_field hdmi_reg_field_30 = {
	.name = "Reserved_1",
	.bits_num = 8,
	.shift = 0,
	.reg_addr = 0x4408,
};
struct reg_field hdmi_reg_field_31 = {
	.name = "Hdmi_Acr_Ratio",
	.bits_num = 20,
	.shift = 8,
	.reg_addr = 0x4408,
};
struct reg_field hdmi_reg_field_32 = {
	.name = "Hw_Cts_Mode",
	.bits_num = 1,
	.shift = 28,
	.reg_addr = 0x4408,
};
struct reg_field hdmi_reg_field_33 = {
	.name = "Cts_Select",
	.bits_num = 1,
	.shift = 29,
	.reg_addr = 0x4408,
};
struct reg_field hdmi_reg_field_34 = {
	.name = "Hdmi_Acr_Enable",
	.bits_num = 1,
	.shift = 30,
	.reg_addr = 0x4408,
};
struct reg_field hdmi_reg_field_35 = {
	.name = "Hdmi_Audio_Enable",
	.bits_num = 1,
	.shift = 31,
	.reg_addr = 0x4408,
};
struct reg_info hdmi_reg_2 = {
	.reg_block_name = "hdmi",
	.reg_mmio_addr = 0x4408,
	.reg_sub_index = 0x2,
	.field_num = 6,
	.reg_in_bytes = 4,
};
struct reg_field hdmi_reg_field_36 = {
	.name = "N",
	.bits_num = 20,
	.shift = 0,
	.reg_addr = 0x440c,
};
struct reg_field hdmi_reg_field_37 = {
	.name = "Default_Phase",
	.bits_num = 1,
	.shift = 20,
	.reg_addr = 0x440c,
};
struct reg_field hdmi_reg_field_38 = {
	.name = "Pp_Select",
	.bits_num = 1,
	.shift = 21,
	.reg_addr = 0x440c,
};
struct reg_field hdmi_reg_field_39 = {
	.name = "Clear_Avmute_Enable",
	.bits_num = 1,
	.shift = 22,
	.reg_addr = 0x440c,
};
struct reg_field hdmi_reg_field_40 = {
	.name = "Set_Avmute_Enable",
	.bits_num = 1,
	.shift = 23,
	.reg_addr = 0x440c,
};
struct reg_field hdmi_reg_field_41 = {
	.name = "Cd",
	.bits_num = 4,
	.shift = 24,
	.reg_addr = 0x440c,
};
struct reg_field hdmi_reg_field_42 = {
	.name = "Sw_Pp",
	.bits_num = 4,
	.shift = 28,
	.reg_addr = 0x440c,
};
struct reg_info hdmi_reg_3 = {
	.reg_block_name = "hdmi",
	.reg_mmio_addr = 0x440c,
	.reg_sub_index = 0x3,
	.field_num = 7,
	.reg_in_bytes = 4,
};
struct reg_field hdmi_reg_field_43 = {
	.name = "Reserved_1",
	.bits_num = 11,
	.shift = 0,
	.reg_addr = 0x4410,
};
struct reg_field hdmi_reg_field_44 = {
	.name = "Cts_Select",
	.bits_num = 1,
	.shift = 11,
	.reg_addr = 0x4410,
};
struct reg_field hdmi_reg_field_45 = {
	.name = "Sw_Cts",
	.bits_num = 20,
	.shift = 12,
	.reg_addr = 0x4410,
};
struct reg_info hdmi_reg_4 = {
	.reg_block_name = "hdmi",
	.reg_mmio_addr = 0x4410,
	.reg_sub_index = 0x4,
	.field_num = 3,
	.reg_in_bytes = 4,
};
struct reg_field hdmi_reg_field_46 = {
	.name = "Reserved_1",
	.bits_num = 13,
	.shift = 0,
	.reg_addr = 0x4414,
};
struct reg_field hdmi_reg_field_47 = {
	.name = "Central_Start_Mode",
	.bits_num = 1,
	.shift = 13,
	.reg_addr = 0x4414,
};
struct reg_field hdmi_reg_field_48 = {
	.name = "Ycbcr420_Mode",
	.bits_num = 1,
	.shift = 14,
	.reg_addr = 0x4414,
};
struct reg_field hdmi_reg_field_49 = {
	.name = "Ycbcr420_Enable",
	.bits_num = 1,
	.shift = 15,
	.reg_addr = 0x4414,
};
struct reg_field hdmi_reg_field_50 = {
	.name = "Sscp_Ucc_Pos",
	.bits_num = 12,
	.shift = 16,
	.reg_addr = 0x4414,
};
struct reg_field hdmi_reg_field_51 = {
	.name = "Data__Island_Start_Select",
	.bits_num = 1,
	.shift = 28,
	.reg_addr = 0x4414,
};
struct reg_field hdmi_reg_field_52 = {
	.name = "Scramble_Active_Position_Select",
	.bits_num = 1,
	.shift = 29,
	.reg_addr = 0x4414,
};
struct reg_field hdmi_reg_field_53 = {
	.name = "Scrmable_Mode",
	.bits_num = 1,
	.shift = 30,
	.reg_addr = 0x4414,
};
struct reg_field hdmi_reg_field_54 = {
	.name = "Scramble_Enable",
	.bits_num = 1,
	.shift = 31,
	.reg_addr = 0x4414,
};
struct reg_info hdmi_reg_5 = {
	.reg_block_name = "hdmi",
	.reg_mmio_addr = 0x4414,
	.reg_sub_index = 0x5,
	.field_num = 9,
	.reg_in_bytes = 4,
};
struct reg_field hdmi_reg_field_55 = {
	.name = "Reserved_1",
	.bits_num = 4,
	.shift = 0,
	.reg_addr = 0x4418,
};
struct reg_field hdmi_reg_field_56 = {
	.name = "Hpd_Int_Status",
	.bits_num = 2,
	.shift = 4,
	.reg_addr = 0x4418,
};
struct reg_field hdmi_reg_field_57 = {
	.name = "Hpd_Pad_State",
	.bits_num = 1,
	.shift = 6,
	.reg_addr = 0x4418,
};
struct reg_field hdmi_reg_field_58 = {
	.name = "Map_State",
	.bits_num = 5,
	.shift = 7,
	.reg_addr = 0x4418,
};
struct reg_field hdmi_reg_field_59 = {
	.name = "Hw_Generated_Cts",
	.bits_num = 20,
	.shift = 12,
	.reg_addr = 0x4418,
};
struct reg_info hdmi_reg_6 = {
	.reg_block_name = "hdmi",
	.reg_mmio_addr = 0x4418,
	.reg_sub_index = 0x6,
	.field_num = 5,
	.reg_in_bytes = 4,
};
struct reg_field hdmi_reg_field_60 = {
	.name = "Reserved_1",
	.bits_num = 18,
	.shift = 0,
	.reg_addr = 0x441c,
};
struct reg_field hdmi_reg_field_61 = {
	.name = "Ctl",
	.bits_num = 3,
	.shift = 18,
	.reg_addr = 0x441c,
};
struct reg_field hdmi_reg_field_62 = {
	.name = "Ctl_Win_Sel",
	.bits_num = 3,
	.shift = 21,
	.reg_addr = 0x441c,
};
struct reg_field hdmi_reg_field_63 = {
	.name = "Test_Mode",
	.bits_num = 3,
	.shift = 24,
	.reg_addr = 0x441c,
};
struct reg_field hdmi_reg_field_64 = {
	.name = "Hsync_Invert_Enable",
	.bits_num = 1,
	.shift = 27,
	.reg_addr = 0x441c,
};
struct reg_field hdmi_reg_field_65 = {
	.name = "Vsync_Invert_Enable",
	.bits_num = 1,
	.shift = 28,
	.reg_addr = 0x441c,
};
struct reg_field hdmi_reg_field_66 = {
	.name = "Testen",
	.bits_num = 1,
	.shift = 29,
	.reg_addr = 0x441c,
};
struct reg_field hdmi_reg_field_67 = {
	.name = "Testen_Select",
	.bits_num = 1,
	.shift = 30,
	.reg_addr = 0x441c,
};
struct reg_field hdmi_reg_field_68 = {
	.name = "Source_Select",
	.bits_num = 1,
	.shift = 31,
	.reg_addr = 0x441c,
};
struct reg_info hdmi_reg_7 = {
	.reg_block_name = "hdmi",
	.reg_mmio_addr = 0x441c,
	.reg_sub_index = 0x7,
	.field_num = 9,
	.reg_in_bytes = 4,
};
struct reg_field hdmi_reg_field_69 = {
	.name = "Cec_Start_Total_L_Para",
	.bits_num = 7,
	.shift = 0,
	.reg_addr = 0x4420,
};
struct reg_field hdmi_reg_field_70 = {
	.name = "Cec20_Enable",
	.bits_num = 1,
	.shift = 7,
	.reg_addr = 0x4420,
};
struct reg_field hdmi_reg_field_71 = {
	.name = "Pulse_Sel",
	.bits_num = 1,
	.shift = 8,
	.reg_addr = 0x4420,
};
struct reg_field hdmi_reg_field_72 = {
	.name = "Error_Detect_Sel",
	.bits_num = 1,
	.shift = 9,
	.reg_addr = 0x4420,
};
struct reg_field hdmi_reg_field_73 = {
	.name = "Fall_To_Rise_Error_En",
	.bits_num = 1,
	.shift = 10,
	.reg_addr = 0x4420,
};
struct reg_field hdmi_reg_field_74 = {
	.name = "Reserved_2",
	.bits_num = 1,
	.shift = 11,
	.reg_addr = 0x4420,
};
struct reg_field hdmi_reg_field_75 = {
	.name = "Cec_Initiator_Cmd_Available",
	.bits_num = 1,
	.shift = 12,
	.reg_addr = 0x4420,
};
struct reg_field hdmi_reg_field_76 = {
	.name = "Cec_Enable",
	.bits_num = 1,
	.shift = 13,
	.reg_addr = 0x4420,
};
struct reg_field hdmi_reg_field_77 = {
	.name = "Reserved_1",
	.bits_num = 1,
	.shift = 14,
	.reg_addr = 0x4420,
};
struct reg_field hdmi_reg_field_78 = {
	.name = "Cec_Initiator_Broadcast",
	.bits_num = 1,
	.shift = 15,
	.reg_addr = 0x4420,
};
struct reg_field hdmi_reg_field_79 = {
	.name = "Cec_Initiator_Cmd_Len",
	.bits_num = 5,
	.shift = 16,
	.reg_addr = 0x4420,
};
struct reg_field hdmi_reg_field_80 = {
	.name = "Cec__Initiator_Dest_Addr",
	.bits_num = 4,
	.shift = 21,
	.reg_addr = 0x4420,
};
struct reg_field hdmi_reg_field_81 = {
	.name = "Cec_Device_Addr",
	.bits_num = 4,
	.shift = 25,
	.reg_addr = 0x4420,
};
struct reg_field hdmi_reg_field_82 = {
	.name = "Cec_Initiator_Retry_Times",
	.bits_num = 3,
	.shift = 29,
	.reg_addr = 0x4420,
};
struct reg_info hdmi_reg_8 = {
	.reg_block_name = "hdmi",
	.reg_mmio_addr = 0x4420,
	.reg_sub_index = 0x8,
	.field_num = 14,
	.reg_in_bytes = 4,
};
struct reg_field hdmi_reg_field_83 = {
	.name = "Cec_Initiator_Command",
	.bits_num = 32,
	.shift = 0,
	.reg_addr = 0x4424,
};
struct reg_info hdmi_reg_9 = {
	.reg_block_name = "hdmi",
	.reg_mmio_addr = 0x4424,
	.reg_sub_index = 0x9,
	.field_num = 1,
	.reg_in_bytes = 4,
};
struct reg_field hdmi_reg_field_84 = {
	.name = "Reserved_2",
	.bits_num = 7,
	.shift = 0,
	.reg_addr = 0x4428,
};
struct reg_field hdmi_reg_field_85 = {
	.name = "Ready_Status",
	.bits_num = 1,
	.shift = 7,
	.reg_addr = 0x4428,
};
struct reg_field hdmi_reg_field_86 = {
	.name = "Follower_Status",
	.bits_num = 3,
	.shift = 8,
	.reg_addr = 0x4428,
};
struct reg_field hdmi_reg_field_87 = {
	.name = "Initiator_Status",
	.bits_num = 3,
	.shift = 11,
	.reg_addr = 0x4428,
};
struct reg_field hdmi_reg_field_88 = {
	.name = "Retran_Status",
	.bits_num = 3,
	.shift = 14,
	.reg_addr = 0x4428,
};
struct reg_field hdmi_reg_field_89 = {
	.name = "Follower_Received_Event",
	.bits_num = 1,
	.shift = 17,
	.reg_addr = 0x4428,
};
struct reg_field hdmi_reg_field_90 = {
	.name = "Follower_Received_Ready",
	.bits_num = 1,
	.shift = 18,
	.reg_addr = 0x4428,
};
struct reg_field hdmi_reg_field_91 = {
	.name = "Follower_Received_Cmd_Len",
	.bits_num = 5,
	.shift = 19,
	.reg_addr = 0x4428,
};
struct reg_field hdmi_reg_field_92 = {
	.name = "Follower_Received_Broadcast",
	.bits_num = 1,
	.shift = 24,
	.reg_addr = 0x4428,
};
struct reg_field hdmi_reg_field_93 = {
	.name = "Follower_Received_Source_Addr",
	.bits_num = 4,
	.shift = 25,
	.reg_addr = 0x4428,
};
struct reg_field hdmi_reg_field_94 = {
	.name = "Reserved_1",
	.bits_num = 1,
	.shift = 29,
	.reg_addr = 0x4428,
};
struct reg_field hdmi_reg_field_95 = {
	.name = "Initiator_Transmit_Succeed",
	.bits_num = 1,
	.shift = 30,
	.reg_addr = 0x4428,
};
struct reg_field hdmi_reg_field_96 = {
	.name = "Initiator_Transmit_Finished",
	.bits_num = 1,
	.shift = 31,
	.reg_addr = 0x4428,
};
struct reg_info hdmi_reg_10 = {
	.reg_block_name = "hdmi",
	.reg_mmio_addr = 0x4428,
	.reg_sub_index = 0xa,
	.field_num = 13,
	.reg_in_bytes = 4,
};
struct reg_field hdmi_reg_field_97 = {
	.name = "Received_Command",
	.bits_num = 32,
	.shift = 0,
	.reg_addr = 0x442c,
};
struct reg_info hdmi_reg_11 = {
	.reg_block_name = "hdmi",
	.reg_mmio_addr = 0x442c,
	.reg_sub_index = 0xb,
	.field_num = 1,
	.reg_in_bytes = 4,
};
struct reg_field hdmi_reg_field_98 = {
	.name = "Cec_Start_Para",
	.bits_num = 7,
	.shift = 0,
	.reg_addr = 0x4430,
};
struct reg_field hdmi_reg_field_99 = {
	.name = "Cec_Logic0_Para",
	.bits_num = 7,
	.shift = 7,
	.reg_addr = 0x4430,
};
struct reg_field hdmi_reg_field_100 = {
	.name = "Cec_Logic1_Para",
	.bits_num = 7,
	.shift = 14,
	.reg_addr = 0x4430,
};
struct reg_field hdmi_reg_field_101 = {
	.name = "Cec_Error_Para",
	.bits_num = 7,
	.shift = 21,
	.reg_addr = 0x4430,
};
struct reg_field hdmi_reg_field_102 = {
	.name = "Cec_F2r_Error_Para4",
	.bits_num = 2,
	.shift = 28,
	.reg_addr = 0x4430,
};
struct reg_field hdmi_reg_field_103 = {
	.name = "Reserved_1",
	.bits_num = 1,
	.shift = 30,
	.reg_addr = 0x4430,
};
struct reg_field hdmi_reg_field_104 = {
	.name = "Cec_Timing_Para_Sel",
	.bits_num = 1,
	.shift = 31,
	.reg_addr = 0x4430,
};
struct reg_info hdmi_reg_12 = {
	.reg_block_name = "hdmi",
	.reg_mmio_addr = 0x4430,
	.reg_sub_index = 0xc,
	.field_num = 7,
	.reg_in_bytes = 4,
};
struct reg_field hdmi_reg_field_105 = {
	.name = "Cec_Ack0_Para",
	.bits_num = 7,
	.shift = 0,
	.reg_addr = 0x4434,
};
struct reg_field hdmi_reg_field_106 = {
	.name = "Cec_Ack1_Para",
	.bits_num = 7,
	.shift = 7,
	.reg_addr = 0x4434,
};
struct reg_field hdmi_reg_field_107 = {
	.name = "Cec_Start_Rise_L_Para",
	.bits_num = 7,
	.shift = 14,
	.reg_addr = 0x4434,
};
struct reg_field hdmi_reg_field_108 = {
	.name = "Cec_Start_Rise_H_Para",
	.bits_num = 7,
	.shift = 21,
	.reg_addr = 0x4434,
};
struct reg_field hdmi_reg_field_109 = {
	.name = "Cec_F2r_Error_Para3",
	.bits_num = 4,
	.shift = 28,
	.reg_addr = 0x4434,
};
struct reg_info hdmi_reg_13 = {
	.reg_block_name = "hdmi",
	.reg_mmio_addr = 0x4434,
	.reg_sub_index = 0xd,
	.field_num = 5,
	.reg_in_bytes = 4,
};
struct reg_field hdmi_reg_field_110 = {
	.name = "Cec_Start_Total_H_Para",
	.bits_num = 7,
	.shift = 0,
	.reg_addr = 0x4438,
};
struct reg_field hdmi_reg_field_111 = {
	.name = "Cec_Ack_Total_Para",
	.bits_num = 7,
	.shift = 7,
	.reg_addr = 0x4438,
};
struct reg_field hdmi_reg_field_112 = {
	.name = "Cec_Error_Total_Para",
	.bits_num = 7,
	.shift = 14,
	.reg_addr = 0x4438,
};
struct reg_field hdmi_reg_field_113 = {
	.name = "Cec_Data_Strobe_Para",
	.bits_num = 7,
	.shift = 21,
	.reg_addr = 0x4438,
};
struct reg_field hdmi_reg_field_114 = {
	.name = "Cec_F2r_Error_Para4",
	.bits_num = 4,
	.shift = 28,
	.reg_addr = 0x4438,
};
struct reg_info hdmi_reg_14 = {
	.reg_block_name = "hdmi",
	.reg_mmio_addr = 0x4438,
	.reg_sub_index = 0xe,
	.field_num = 5,
	.reg_in_bytes = 4,
};
struct reg_field hdmi_reg_field_115 = {
	.name = "Cec_Wr_Para",
	.bits_num = 7,
	.shift = 0,
	.reg_addr = 0x443c,
};
struct reg_field hdmi_reg_field_116 = {
	.name = "Cec_F2f_Error_Para",
	.bits_num = 7,
	.shift = 7,
	.reg_addr = 0x443c,
};
struct reg_field hdmi_reg_field_117 = {
	.name = "Cec_F2r_Error_Para1",
	.bits_num = 7,
	.shift = 14,
	.reg_addr = 0x443c,
};
struct reg_field hdmi_reg_field_118 = {
	.name = "Cec_F2r_Error_Para2",
	.bits_num = 7,
	.shift = 21,
	.reg_addr = 0x443c,
};
struct reg_field hdmi_reg_field_119 = {
	.name = "Cec_F2r_Error_Para3",
	.bits_num = 3,
	.shift = 28,
	.reg_addr = 0x443c,
};
struct reg_field hdmi_reg_field_120 = {
	.name = "Cec_F2r_Error_Para4",
	.bits_num = 1,
	.shift = 31,
	.reg_addr = 0x443c,
};
struct reg_info hdmi_reg_15 = {
	.reg_block_name = "hdmi",
	.reg_mmio_addr = 0x443c,
	.reg_sub_index = 0xf,
	.field_num = 6,
	.reg_in_bytes = 4,
};
struct reg_field hdmi_reg_field_121 = {
	.name = "Initiator_Command",
	.bits_num = 32,
	.shift = 0,
	.reg_addr = 0x4440,
};
struct reg_info hdmi_reg_16 = {
	.reg_block_name = "hdmi",
	.reg_mmio_addr = 0x4440,
	.reg_sub_index = 0x10,
	.field_num = 1,
	.reg_in_bytes = 4,
};
struct reg_field hdmi_reg_field_122 = {
	.name = "Reserved_1",
	.bits_num = 2,
	.shift = 0,
	.reg_addr = 0x4444,
};
struct reg_field hdmi_reg_field_123 = {
	.name = "I2c_Frequency_Sleect",
	.bits_num = 3,
	.shift = 2,
	.reg_addr = 0x4444,
};
struct reg_field hdmi_reg_field_124 = {
	.name = "I2c_Status",
	.bits_num = 1,
	.shift = 5,
	.reg_addr = 0x4444,
};
struct reg_field hdmi_reg_field_125 = {
	.name = "Command_Buffer_Nempty",
	.bits_num = 1,
	.shift = 6,
	.reg_addr = 0x4444,
};
struct reg_field hdmi_reg_field_126 = {
	.name = "Command_Buffer_Nfull",
	.bits_num = 1,
	.shift = 7,
	.reg_addr = 0x4444,
};
struct reg_field hdmi_reg_field_127 = {
	.name = "Read_Data",
	.bits_num = 8,
	.shift = 8,
	.reg_addr = 0x4444,
};
struct reg_field hdmi_reg_field_128 = {
	.name = "Write_Data",
	.bits_num = 8,
	.shift = 16,
	.reg_addr = 0x4444,
};
struct reg_field hdmi_reg_field_129 = {
	.name = "Read_Finished",
	.bits_num = 1,
	.shift = 24,
	.reg_addr = 0x4444,
};
struct reg_field hdmi_reg_field_130 = {
	.name = "Slave_Receiver_Not_Ready",
	.bits_num = 1,
	.shift = 25,
	.reg_addr = 0x4444,
};
struct reg_field hdmi_reg_field_131 = {
	.name = "Stop_Request",
	.bits_num = 1,
	.shift = 26,
	.reg_addr = 0x4444,
};
struct reg_field hdmi_reg_field_132 = {
	.name = "Start_Request",
	.bits_num = 1,
	.shift = 27,
	.reg_addr = 0x4444,
};
struct reg_field hdmi_reg_field_133 = {
	.name = "Write_Data_Available",
	.bits_num = 1,
	.shift = 28,
	.reg_addr = 0x4444,
};
struct reg_field hdmi_reg_field_134 = {
	.name = "I2c__Software_Reset",
	.bits_num = 1,
	.shift = 29,
	.reg_addr = 0x4444,
};
struct reg_field hdmi_reg_field_135 = {
	.name = "Software_Requests_I2c_Access",
	.bits_num = 1,
	.shift = 30,
	.reg_addr = 0x4444,
};
struct reg_field hdmi_reg_field_136 = {
	.name = "Hdmi_I2c_Function_Enable",
	.bits_num = 1,
	.shift = 31,
	.reg_addr = 0x4444,
};
struct reg_info hdmi_reg_17 = {
	.reg_block_name = "hdmi",
	.reg_mmio_addr = 0x4444,
	.reg_sub_index = 0x11,
	.field_num = 15,
	.reg_in_bytes = 4,
};
struct reg_field hdmi_reg_field_137 = {
	.name = "Scdc_Rr_Enable",
	.bits_num = 1,
	.shift = 0,
	.reg_addr = 0x4448,
};
struct reg_field hdmi_reg_field_138 = {
	.name = "Scdc_Hw_Drv_Start_Enable",
	.bits_num = 1,
	.shift = 1,
	.reg_addr = 0x4448,
};
struct reg_field hdmi_reg_field_139 = {
	.name = "Scdc_Hw_Drv_Stop_Enable",
	.bits_num = 1,
	.shift = 2,
	.reg_addr = 0x4448,
};
struct reg_field hdmi_reg_field_140 = {
	.name = "Scdc_Start_Stop_Enable",
	.bits_num = 1,
	.shift = 3,
	.reg_addr = 0x4448,
};
struct reg_field hdmi_reg_field_141 = {
	.name = "Reserved_2",
	.bits_num = 1,
	.shift = 4,
	.reg_addr = 0x4448,
};
struct reg_field hdmi_reg_field_142 = {
	.name = "I2c_State_Time_Out",
	.bits_num = 1,
	.shift = 5,
	.reg_addr = 0x4448,
};
struct reg_field hdmi_reg_field_143 = {
	.name = "Reserved_1",
	.bits_num = 2,
	.shift = 6,
	.reg_addr = 0x4448,
};
struct reg_field hdmi_reg_field_144 = {
	.name = "Scdc_Wait_Timeout",
	.bits_num = 24,
	.shift = 8,
	.reg_addr = 0x4448,
};
struct reg_info hdmi_reg_18 = {
	.reg_block_name = "hdmi",
	.reg_mmio_addr = 0x4448,
	.reg_sub_index = 0x12,
	.field_num = 8,
	.reg_in_bytes = 4,
};
struct reg_field hdmi_reg_field_145 = {
	.name = "I2c_State_Timeout",
	.bits_num = 23,
	.shift = 0,
	.reg_addr = 0x444c,
};
struct reg_field hdmi_reg_field_146 = {
	.name = "Scdc_Wdata_Sel",
	.bits_num = 1,
	.shift = 23,
	.reg_addr = 0x444c,
};
struct reg_field hdmi_reg_field_147 = {
	.name = "Scdc_Wdata",
	.bits_num = 8,
	.shift = 24,
	.reg_addr = 0x444c,
};
struct reg_info hdmi_reg_19 = {
	.reg_block_name = "hdmi",
	.reg_mmio_addr = 0x444c,
	.reg_sub_index = 0x13,
	.field_num = 3,
	.reg_in_bytes = 4,
};
struct reg_info * hdmi_reg_info[20] = {
&hdmi_reg_0,
&hdmi_reg_1,
&hdmi_reg_2,
&hdmi_reg_3,
&hdmi_reg_4,
&hdmi_reg_5,
&hdmi_reg_6,
&hdmi_reg_7,
&hdmi_reg_8,
&hdmi_reg_9,
&hdmi_reg_10,
&hdmi_reg_11,
&hdmi_reg_12,
&hdmi_reg_13,
&hdmi_reg_14,
&hdmi_reg_15,
&hdmi_reg_16,
&hdmi_reg_17,
&hdmi_reg_18,
&hdmi_reg_19,
};
struct reg_field * hdmi_reg_field_info[148] = {
&hdmi_reg_field_0,
&hdmi_reg_field_1,
&hdmi_reg_field_2,
&hdmi_reg_field_3,
&hdmi_reg_field_4,
&hdmi_reg_field_5,
&hdmi_reg_field_6,
&hdmi_reg_field_7,
&hdmi_reg_field_8,
&hdmi_reg_field_9,
&hdmi_reg_field_10,
&hdmi_reg_field_11,
&hdmi_reg_field_12,
&hdmi_reg_field_13,
&hdmi_reg_field_14,
&hdmi_reg_field_15,
&hdmi_reg_field_16,
&hdmi_reg_field_17,
&hdmi_reg_field_18,
&hdmi_reg_field_19,
&hdmi_reg_field_20,
&hdmi_reg_field_21,
&hdmi_reg_field_22,
&hdmi_reg_field_23,
&hdmi_reg_field_24,
&hdmi_reg_field_25,
&hdmi_reg_field_26,
&hdmi_reg_field_27,
&hdmi_reg_field_28,
&hdmi_reg_field_29,
&hdmi_reg_field_30,
&hdmi_reg_field_31,
&hdmi_reg_field_32,
&hdmi_reg_field_33,
&hdmi_reg_field_34,
&hdmi_reg_field_35,
&hdmi_reg_field_36,
&hdmi_reg_field_37,
&hdmi_reg_field_38,
&hdmi_reg_field_39,
&hdmi_reg_field_40,
&hdmi_reg_field_41,
&hdmi_reg_field_42,
&hdmi_reg_field_43,
&hdmi_reg_field_44,
&hdmi_reg_field_45,
&hdmi_reg_field_46,
&hdmi_reg_field_47,
&hdmi_reg_field_48,
&hdmi_reg_field_49,
&hdmi_reg_field_50,
&hdmi_reg_field_51,
&hdmi_reg_field_52,
&hdmi_reg_field_53,
&hdmi_reg_field_54,
&hdmi_reg_field_55,
&hdmi_reg_field_56,
&hdmi_reg_field_57,
&hdmi_reg_field_58,
&hdmi_reg_field_59,
&hdmi_reg_field_60,
&hdmi_reg_field_61,
&hdmi_reg_field_62,
&hdmi_reg_field_63,
&hdmi_reg_field_64,
&hdmi_reg_field_65,
&hdmi_reg_field_66,
&hdmi_reg_field_67,
&hdmi_reg_field_68,
&hdmi_reg_field_69,
&hdmi_reg_field_70,
&hdmi_reg_field_71,
&hdmi_reg_field_72,
&hdmi_reg_field_73,
&hdmi_reg_field_74,
&hdmi_reg_field_75,
&hdmi_reg_field_76,
&hdmi_reg_field_77,
&hdmi_reg_field_78,
&hdmi_reg_field_79,
&hdmi_reg_field_80,
&hdmi_reg_field_81,
&hdmi_reg_field_82,
&hdmi_reg_field_83,
&hdmi_reg_field_84,
&hdmi_reg_field_85,
&hdmi_reg_field_86,
&hdmi_reg_field_87,
&hdmi_reg_field_88,
&hdmi_reg_field_89,
&hdmi_reg_field_90,
&hdmi_reg_field_91,
&hdmi_reg_field_92,
&hdmi_reg_field_93,
&hdmi_reg_field_94,
&hdmi_reg_field_95,
&hdmi_reg_field_96,
&hdmi_reg_field_97,
&hdmi_reg_field_98,
&hdmi_reg_field_99,
&hdmi_reg_field_100,
&hdmi_reg_field_101,
&hdmi_reg_field_102,
&hdmi_reg_field_103,
&hdmi_reg_field_104,
&hdmi_reg_field_105,
&hdmi_reg_field_106,
&hdmi_reg_field_107,
&hdmi_reg_field_108,
&hdmi_reg_field_109,
&hdmi_reg_field_110,
&hdmi_reg_field_111,
&hdmi_reg_field_112,
&hdmi_reg_field_113,
&hdmi_reg_field_114,
&hdmi_reg_field_115,
&hdmi_reg_field_116,
&hdmi_reg_field_117,
&hdmi_reg_field_118,
&hdmi_reg_field_119,
&hdmi_reg_field_120,
&hdmi_reg_field_121,
&hdmi_reg_field_122,
&hdmi_reg_field_123,
&hdmi_reg_field_124,
&hdmi_reg_field_125,
&hdmi_reg_field_126,
&hdmi_reg_field_127,
&hdmi_reg_field_128,
&hdmi_reg_field_129,
&hdmi_reg_field_130,
&hdmi_reg_field_131,
&hdmi_reg_field_132,
&hdmi_reg_field_133,
&hdmi_reg_field_134,
&hdmi_reg_field_135,
&hdmi_reg_field_136,
&hdmi_reg_field_137,
&hdmi_reg_field_138,
&hdmi_reg_field_139,
&hdmi_reg_field_140,
&hdmi_reg_field_141,
&hdmi_reg_field_142,
&hdmi_reg_field_143,
&hdmi_reg_field_144,
&hdmi_reg_field_145,
&hdmi_reg_field_146,
&hdmi_reg_field_147,
};
unsigned int hdmi_reg_count = 20;
unsigned int hdmi_reg_start = 0x4400;
unsigned int hdmi_reg_end = 0x444c;
unsigned int hdmi_reg_in_bytes = 0x4;
unsigned int hdmi_reg_total_field_count = 148;
char * hdmi_reg_block_name = "hdmi";
