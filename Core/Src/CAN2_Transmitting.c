///*
// * CAN2_Transmitting.c
// *
// *  Created on: Jul 21, 2023
// *      Author: ujwalpatel
// */
//
//#include "CAN2_Transmitting.h"
//#include "fdcan.h"
//#include "process.h"
//#include "protection.h"
//#include "error_display.h"
//
//#define DELAY 5
//#define FACTOR_1 1
//#define FACTOR_10 10
//
//#define PRODUCT_ID 0x01
//#define MAJOR_FIRMWARE 0x00
//#define MINOR_FIRMWARE 0x00
//
//
//extern FDCAN_TxHeaderTypeDef TxHeader_CAN1,TxHeader1_CAN1,
//							 TxHeader_CAN2,TxHeader1_CAN2,TxHeader2_CAN2,TxHeader3_CAN2,TxHeader4_CAN2,TxHeader5_CAN2,TxHeader6_CAN2;
//
//extern FDCAN_RxHeaderTypeDef RxHeader_CAN1,RxHeader_CAN2;
//extern uint16_t u8Slavenumber;
//
//uint8_t TxDataHandler_CAN2[8],TxDataHandler1_CAN2[8],TxDataHandler2_CAN2[8],TxDataHandler3_CAN2[8],
//		TxDataHandler4_CAN2[8],TxDataHandler5_CAN2[8],TxDataHandler6_CAN2[8];
//
//uint8_t CAN2_Sucess1, CAN2_Sucess2,CAN2_Fail1, CAN2_Fail2;
//
//void API_CAN2_HEARTBEAT_CELL0139_MASTER01(uint8_t check)
//{
//	TxDataHandler6_CAN2[4]=PRODUCT_ID;
//	TxDataHandler6_CAN2[5]=u8Slavenumber;
//	TxDataHandler6_CAN2[6]=MAJOR_FIRMWARE;
//	TxDataHandler6_CAN2[7]=MINOR_FIRMWARE;
//
//	if(check==0x05)
//	{
//		TxDataHandler6_CAN2[0]=0x05;
//		if (HAL_FDCAN_AddMessageToTxFifoQ(&hfdcan2, &TxHeader6_CAN2, TxDataHandler6_CAN2) != HAL_OK){
//			CAN2_Fail1++;
//			add_error_to_list(13);
//		}
//		else
//		{CAN2_Sucess1++;}
//		//HAL_Delay(1);
//	}
//	else
//	{
//		TxDataHandler6_CAN2[0]=0x00;
//		if (HAL_FDCAN_AddMessageToTxFifoQ(&hfdcan2, &TxHeader6_CAN2, TxDataHandler6_CAN2) != HAL_OK){
//			CAN2_Fail2++;
//			add_error_to_list(13);
//		}
//		else
//		{CAN2_Sucess2++;}
//		//HAL_Delay(1);
//	}
//	HAL_Delay(80);
//
//}
//
//void API_CAN_PSFB_FEC_Volt_Current(float DC_BUS_VOLTAGE,float PSFB_INPUT_DC_CURRENT,float FEC_INPUT_AC_CURRENT,float PSFB_OUTPUT_DC_CURRENT)
//{
//	/*Converting Required Data type*/
//	uint16_t u16DC_BUS_VOLTAGE=(DC_BUS_VOLTAGE*FACTOR_10);
//
//	uint16_t u16PSFB_INPUT_DC_CURRENT=(PSFB_INPUT_DC_CURRENT*FACTOR_10);
//
//	uint16_t u16FEC_INPUT_AC_CURRENT=(FEC_INPUT_AC_CURRENT*FACTOR_10);
//
//	uint16_t u16PSFB_OUTPUT_DC_CURRENT=(PSFB_OUTPUT_DC_CURRENT*FACTOR_10);
//
//	TxDataHandler_CAN2[0]=u16DC_BUS_VOLTAGE;
//	TxDataHandler_CAN2[1]=u16DC_BUS_VOLTAGE>>8;
//
//	TxDataHandler_CAN2[2]=u16PSFB_INPUT_DC_CURRENT;
//	TxDataHandler_CAN2[3]=u16PSFB_INPUT_DC_CURRENT>>8;
//
//	TxDataHandler_CAN2[4]=u16FEC_INPUT_AC_CURRENT;
//	TxDataHandler_CAN2[5]=u16FEC_INPUT_AC_CURRENT>>8;
//
//	TxDataHandler_CAN2[6]=u16PSFB_OUTPUT_DC_CURRENT;
//	TxDataHandler_CAN2[7]=u16PSFB_OUTPUT_DC_CURRENT>>8;
//
//	if (HAL_FDCAN_AddMessageToTxFifoQ(&hfdcan2, &TxHeader_CAN2, TxDataHandler_CAN2) != HAL_OK)
//	{}
//	else
//	{}
//	HAL_Delay(u8Slavenumber);
//}
//
//void API_CAN_PSFB_AC_TRAFO_Colt_Current_Temp(float PSFB_OUTPUT_DC_VOLTAGE,float AC_VOLTAGE,float AC_CURRENT,float TRAFO_TEMPERATURE)
//{
//	/*Converting Required Data type*/
//	uint16_t u16PSFB_OUTPUT_DC_VOLTAGE=(PSFB_OUTPUT_DC_VOLTAGE*FACTOR_1);
//
//	uint16_t u16AC_VOLTAGE=(AC_VOLTAGE*FACTOR_1);
//
//	uint16_t u16AC_CURRENT=(AC_CURRENT*FACTOR_1);
//
//	uint16_t u16TRAFO_TEMPERATURE=(TRAFO_TEMPERATURE*FACTOR_10);
//
//	TxDataHandler1_CAN2[0]=u16PSFB_OUTPUT_DC_VOLTAGE;
//	TxDataHandler1_CAN2[1]=u16PSFB_OUTPUT_DC_VOLTAGE>>8;
//	TxDataHandler1_CAN2[2]=u16AC_VOLTAGE;
//	TxDataHandler1_CAN2[3]=u16AC_VOLTAGE>>8;
//	TxDataHandler1_CAN2[4]=u16AC_CURRENT;
//	TxDataHandler1_CAN2[5]=u16AC_CURRENT>>8;
//	TxDataHandler1_CAN2[6]=u16TRAFO_TEMPERATURE;
//	TxDataHandler1_CAN2[7]=u16TRAFO_TEMPERATURE>>8;
//
//	if (HAL_FDCAN_AddMessageToTxFifoQ(&hfdcan2, &TxHeader1_CAN2, TxDataHandler1_CAN2) != HAL_OK)
//	{}
//	else
//	{}
//	HAL_Delay(u8Slavenumber);
//}
//
//void API_CAN_FEC_PSFB_DIODE_Temp(float FEC_TEMPERATURE,float PSFB_TEMPERATURE,float Diode_TEMPERATURE,float RSVD)
//{
//
//	/*Converting Required Data type*/
//	uint16_t u16FEC_TEMPERATURE=(FEC_TEMPERATURE*FACTOR_10);
//
//	uint16_t u16PSFB_TEMPERATURE=(PSFB_TEMPERATURE*FACTOR_10);
//
//	uint16_t u16Diode_TEMPERATURE=(Diode_TEMPERATURE*FACTOR_10);
//
//
//	TxDataHandler2_CAN2[0]=u16FEC_TEMPERATURE;
//	TxDataHandler2_CAN2[1]=u16FEC_TEMPERATURE>>8;
//	TxDataHandler2_CAN2[2]=u16PSFB_TEMPERATURE;
//	TxDataHandler2_CAN2[3]=u16PSFB_TEMPERATURE>>8;
//	TxDataHandler2_CAN2[4]=u16Diode_TEMPERATURE;
//	TxDataHandler2_CAN2[5]=u16Diode_TEMPERATURE>>8;
//	TxDataHandler2_CAN2[6]=00;
//	TxDataHandler2_CAN2[7]=00>>8;
//
//	if (HAL_FDCAN_AddMessageToTxFifoQ(&hfdcan2, &TxHeader2_CAN2, TxDataHandler2_CAN2) != HAL_OK)
//	{}
//	else
//	{}
//	HAL_Delay(u8Slavenumber);
//}
//
//void API_CAN_PHASE_VDC_GAIN_OFFSET(float RSVD1,float RSVD2,float RSVD3,uint16_t RSVD4)
//{
//	/*Converting Required Data type*/
//	uint16_t u16RSVD1=(RSVD1*FACTOR_10);
//
//	uint16_t u16RSVD2=(RSVD2*FACTOR_10);
//
//	uint16_t u16RSVD3=(RSVD3*FACTOR_10);
//
//	uint16_t u16RSVD4=(RSVD4*FACTOR_1);
//
//	TxDataHandler3_CAN2[0]=u16RSVD1;
//	TxDataHandler3_CAN2[1]=u16RSVD1>>8;
//	TxDataHandler3_CAN2[2]=u16RSVD2;
//	TxDataHandler3_CAN2[3]=u16RSVD2>>8;
//	TxDataHandler3_CAN2[4]=u16RSVD3;
//	TxDataHandler3_CAN2[5]=u16RSVD3>>8;
//	TxDataHandler3_CAN2[6]=u16RSVD4;
//	TxDataHandler3_CAN2[7]=u16RSVD4>>8;
//
//	if (HAL_FDCAN_AddMessageToTxFifoQ(&hfdcan2, &TxHeader3_CAN2, TxDataHandler3_CAN2) != HAL_OK)
//	{}
//	else
//	{}
//	HAL_Delay(1);
//}
//
//
//void API_CAN_CELL01_FAULT(uint8_t Fault1,uint8_t Fault2,uint8_t Fault3,uint8_t Fault4,uint8_t Fault5,uint8_t Fault6,uint8_t Fault7,uint8_t Fault8)
//{
//	TxDataHandler4_CAN2[0]=Fault1;
//	TxDataHandler4_CAN2[1]=Fault2;
//	TxDataHandler4_CAN2[2]=Fault3;
//	TxDataHandler4_CAN2[3]=Fault4;
//	TxDataHandler4_CAN2[4]=Fault5;
//	TxDataHandler4_CAN2[5]=Fault6;
//	TxDataHandler4_CAN2[6]=Fault7;
//	TxDataHandler4_CAN2[7]=Fault8;
//
//	if (HAL_FDCAN_AddMessageToTxFifoQ(&hfdcan2, &TxHeader4_CAN2, TxDataHandler4_CAN2) != HAL_OK)
//	{}
//	else
//	{}
//	HAL_Delay(u8Slavenumber);
//}
//
//void API_CAN_CELL01_Status(uint8_t Status1,uint8_t Status2,uint8_t Status3,uint8_t Status4,uint8_t Status5,uint8_t Status6,uint8_t Status7,uint8_t Status8)
//{
//	TxDataHandler5_CAN2[0]=Status1;
//	TxDataHandler5_CAN2[1]=Status2;
//	TxDataHandler5_CAN2[2]=Status3;
//	TxDataHandler5_CAN2[3]=Status4;
//	TxDataHandler5_CAN2[4]=Status5;
//	TxDataHandler5_CAN2[5]=Status6;
//	TxDataHandler5_CAN2[6]=Status7;
//	TxDataHandler5_CAN2[7]=Status8;
//
//	if (HAL_FDCAN_AddMessageToTxFifoQ(&hfdcan2, &TxHeader5_CAN2, TxDataHandler5_CAN2) != HAL_OK)
//	{
//		//CAN1++;
//	}
//	else
//	{
//		//CAN2++;
//	}
//	HAL_Delay(u8Slavenumber);
//}
//
//
