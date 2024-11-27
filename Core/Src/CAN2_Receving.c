///*
// *   ONLY 500KBPS DATA INTERCHNAGE COMMUNICATION Always Activate CAN2 CHANNLE!!!!!
// *
// * CAN2_Receving.c
// *
// *  Created on: Aug 7, 2023
// *      Author: ujwalpatel
// */
//
//#include "CAN2_Receving.h"
//#include "fdcan.h"
//#include "process.h"
//#include "protection.h"
////#include "syspara.h"
//
//#define CAN2_ID_Frame1_SR 0X1E0101
//#define CAN2_ID_Frame2_SR 0X1E0201
//#define CAN2_ID_Frame3_SR 0X1E0301
//#define CAN2_ID_Frame4_SR 0X1E0401
//#define CAN2_ID_Frame5_SR 0X1E0501
//
//#define CAN2_ID_Frame6_SR 0X1EA001
//#define CAN2_ID_Frame7_SR 0X1EA101
//#define CAN2_ID_Frame8_SR 0X1EA201
//#define CAN2_ID_Frame9_SR 0X1EA301
//
//#define CAN2_ID_Frame10_SR 0X1EA401
//#define CAN2_ID_Frame11_SR 0X1EA501
//
//#define CAN2_ID_Frame12_SR 0X1ED101
//
//#define I_RECT 2
//#define  V_OUT 1
//#define VDC_BUS 0
//#define  I_AC 3
//#define I_OUT 4
//
//#define TPSFB 7
//#define TAFE 8
//#define TDIODE 9
//#define TTRAFO 10
//
//
//#define FACTORDEVISION 0.1
//#define FACTORDEVISION_OFFSET 0.01
//#define OFFSET 100
//
//
//extern FDCAN_RxHeaderTypeDef RxHeader_CAN1,RxHeader_CAN2;
//extern uint16_t u8Slavenumber;
//extern configParameters ConfigPara;
//extern uint8_t u8MASTER1_STATUS_CAN2;
//uint8_t can2_rx_error, can2_rx_success;
//
//uint32_t  u32CAN2_ID_Frame1,u32CAN2_ID_Frame2,u32CAN2_ID_Frame3,u32CAN2_ID_Frame4,
//		  u32CAN2_ID_Frame5,u32CAN2_ID_Frame6,u32CAN2_ID_Frame7,u32CAN2_ID_Frame8,u32CAN2_ID_Frame9,u32CAN2_ID_Frame10,u32CAN2_ID_Frame11,u32CAN2_ID_Frame12;
//uint8_t /*RXdata_Handler_CAN1[8],*/RXdata_Handler_CAN2[8];
//
//void CAN2_Identification(void);
//
//void CAN2_Identification()
//{
//	u32CAN2_ID_Frame1=(CAN2_ID_Frame1_SR<<8)|(u8Slavenumber);
//	u32CAN2_ID_Frame2=(CAN2_ID_Frame2_SR<<8)|(u8Slavenumber);
//	u32CAN2_ID_Frame3=(CAN2_ID_Frame3_SR<<8)|(u8Slavenumber);
//	u32CAN2_ID_Frame4=(CAN2_ID_Frame4_SR<<8)|(u8Slavenumber);
//	u32CAN2_ID_Frame5=(CAN2_ID_Frame5_SR<<8)|(u8Slavenumber);
//
//	u32CAN2_ID_Frame6=(CAN2_ID_Frame6_SR<<8)|(u8Slavenumber);
//	u32CAN2_ID_Frame7=(CAN2_ID_Frame7_SR<<8)|(u8Slavenumber);
//	u32CAN2_ID_Frame8=(CAN2_ID_Frame8_SR<<8)|(u8Slavenumber);
//	u32CAN2_ID_Frame9=(CAN2_ID_Frame9_SR<<8)|(u8Slavenumber);
//
//	u32CAN2_ID_Frame10=(CAN2_ID_Frame10_SR<<8)|(u8Slavenumber);
//	u32CAN2_ID_Frame11=(CAN2_ID_Frame11_SR<<8)|(u8Slavenumber);
//
//	u32CAN2_ID_Frame12=(CAN2_ID_Frame12_SR<<8)|(u8Slavenumber);
//}
//
//void HAL_FDCAN_RxFifo1Callback(FDCAN_HandleTypeDef *hfdcan, uint32_t RxFifo1ITs)
//{
//
//	if((RxFifo1ITs & FDCAN_IT_RX_FIFO1_NEW_MESSAGE) != RESET)
//	{
//		/* Retrieve Rx messages from RX FIFO0 */
//		if (HAL_FDCAN_GetRxMessage(&hfdcan2, FDCAN_RX_FIFO1, &RxHeader_CAN2, RXdata_Handler_CAN2) != HAL_OK)
//		{
//			can2_rx_error++;
//			/*Error_Handler();*/}
//		else
//		{
//			can2_rx_success++;
//			/*Do Nothing*/}
//
//		if(RxHeader_CAN2.Identifier == u32CAN2_ID_Frame1)
//		{
//			//cmd.byte  = (RXdata_Handler_CAN2[0] | RXdata_Handler_CAN2[1] << 8);
//			cmd.byte  = RXdata_Handler_CAN2[0];
////			uint16_t TBD2  = (((RXdata_Handler_CAN2[2] | RXdata_Handler_CAN2[3] << 8)*FACTORDEVISION)-OFFSET);
////			uint16_t TBD3   = (RXdata_Handler_CAN2[4] | RXdata_Handler_CAN2[5] << 8)*FACTORDEVISION;
////			uint16_t TBD4  = (((RXdata_Handler_CAN2[6] | RXdata_Handler_CAN2[7] << 8)*FACTORDEVISION)-OFFSET);
//		}
//		else if(RxHeader_CAN2.Identifier == u32CAN2_ID_Frame2)
//		{
//			ConfigPara.limitFactor.DiodeTempLimit=((RXdata_Handler_CAN2[0] | RXdata_Handler_CAN2[1] << 8)*FACTORDEVISION);
//			ConfigPara.limitFactor.trafoTempLimit =(RXdata_Handler_CAN2[2] | RXdata_Handler_CAN2[3] << 8)*FACTORDEVISION;
//			ConfigPara.limitFactor.psfbTempLimit =(RXdata_Handler_CAN2[4] | RXdata_Handler_CAN2[5] << 8)*FACTORDEVISION;
//			ConfigPara.limitFactor.fecTempLimit =(RXdata_Handler_CAN2[6] | RXdata_Handler_CAN2[7] << 8)*FACTORDEVISION;
//		}
//		else if(RxHeader_CAN2.Identifier == u32CAN2_ID_Frame3)
//		{
//			ConfigPara.limitFactor.dcOverCurrentLimit = (RXdata_Handler_CAN2[0] | RXdata_Handler_CAN2[1] << 8)*FACTORDEVISION;
//			ConfigPara.limitFactor.dcOverVoltageLimit = (RXdata_Handler_CAN2[2] | RXdata_Handler_CAN2[3] << 8)*FACTORDEVISION;
//			ConfigPara.limitFactor.dcUnderVoltageLimit = (RXdata_Handler_CAN2[4] | RXdata_Handler_CAN2[5] << 8)*FACTORDEVISION;
//			//ConfigPara.limitFactor.dcOverCurrentLimit = (RXdata_Handler_CAN2[6] | RXdata_Handler_CAN2[7] << 8)*FACTORDEVISION;
//		}
//		/*else if(RxHeader_CAN2.Identifier == u32CAN2_ID_Frame4)
//		{
//			uint16_t TBD1 = ((RXdata_Handler_CAN2[0] | RXdata_Handler_CAN2[1] << 8)*FACTORDEVISION);
//			uint16_t TBD2  = (((RXdata_Handler_CAN2[2] | RXdata_Handler_CAN2[3] << 8)*FACTORDEVISION)-OFFSET);
//			uint16_t TBD3 = ((RXdata_Handler_CAN2[4] | RXdata_Handler_CAN2[5] << 8)*FACTORDEVISION);
//			uint16_t TBD4  = (((RXdata_Handler_CAN2[6] | RXdata_Handler_CAN2[7] << 8)*FACTORDEVISION)-OFFSET);
//		}
//		else if(RxHeader_CAN2.Identifier == u32CAN2_ID_Frame5)
//		{
//			uint16_t TBD1 = (RXdata_Handler_CAN2[0] | RXdata_Handler_CAN2[1] << 8)*FACTORDEVISION;
//			uint16_t TBD2 = (((RXdata_Handler_CAN2[2] | RXdata_Handler_CAN2[3] << 8)*FACTORDEVISION)-OFFSET);
//			uint16_t TBD3 = RXdata_Handler_CAN2[4] | RXdata_Handler_CAN2[5] << 8;
//			uint16_t TBD4 = RXdata_Handler_CAN2[6] | RXdata_Handler_CAN2[7] << 8;
//		}*/
//		/*PC to CELL*/
//		else if(RxHeader_CAN2.Identifier == u32CAN2_ID_Frame6)
//		{
//			ConfigPara.calFactor[I_AC].corFac = (RXdata_Handler_CAN2[0] | RXdata_Handler_CAN2[1] << 8)*FACTORDEVISION_OFFSET;
////			uint16_t TBD2 = RXdata_Handler_CAN2[2] | RXdata_Handler_CAN2[3] << 8;
//			ConfigPara.calFactor[0].corFac = (RXdata_Handler_CAN2[4] | RXdata_Handler_CAN2[5] << 8)*FACTORDEVISION_OFFSET;
////			uint16_t TBD4 =(RXdata_Handler_CAN2[6] | RXdata_Handler_CAN2[7] << 8)*FACTORDEVISION;
//		}
//		else if(RxHeader_CAN2.Identifier == u32CAN2_ID_Frame7)
//		{
//			ConfigPara.calFactor[2].corFac  = (RXdata_Handler_CAN2[0] | RXdata_Handler_CAN2[1] << 8)*FACTORDEVISION_OFFSET;
////			uint16_t TBD2 = RXdata_Handler_CAN2[2] | RXdata_Handler_CAN2[3] << 8;
//			ConfigPara.calFactor[V_OUT].corFac = (RXdata_Handler_CAN2[4] | RXdata_Handler_CAN2[5] << 8)*FACTORDEVISION_OFFSET;
////			uint16_t TBD4 =(RXdata_Handler_CAN2[6] | RXdata_Handler_CAN2[7] << 8)*FACTORDEVISION;
//		}
//		else if(RxHeader_CAN2.Identifier == u32CAN2_ID_Frame8)
//		{
//			ConfigPara.calFactor[I_OUT].corFac = (RXdata_Handler_CAN2[0] | RXdata_Handler_CAN2[1] << 8)*FACTORDEVISION_OFFSET;
////			uint16_t TBD2 = RXdata_Handler_CAN2[2] | RXdata_Handler_CAN2[3] << 8;
////			uint16_t TBD3 = RXdata_Handler_CAN2[4] | RXdata_Handler_CAN2[5] << 8;
////			uint16_t TBD4 =(RXdata_Handler_CAN2[6] | RXdata_Handler_CAN2[7] << 8)*FACTORDEVISION;
//		}
//		else if(RxHeader_CAN2.Identifier == u32CAN2_ID_Frame9)
//		{
//			//uint16_t TBD1 = RXdata_Handler_CAN2[0] | RXdata_Handler_CAN2[1] << 8;
//			//uint16_t TBD2 = RXdata_Handler_CAN2[2] | RXdata_Handler_CAN2[3] << 8;
//			//uint16_t TBD3 = RXdata_Handler_CAN2[4] | RXdata_Handler_CAN2[5] << 8;
//			//uint16_t TBD4 =(RXdata_Handler_CAN2[6] | RXdata_Handler_CAN2[7] << 8)*FACTORDEVISION;
//		}
//
//		else if(RxHeader_CAN2.Identifier == u32CAN2_ID_Frame10)
//		{
//			ConfigPara.calFactor[TPSFB].corFac = ((RXdata_Handler_CAN2[0] | RXdata_Handler_CAN2[1] << 8)*FACTORDEVISION_OFFSET);
//			ConfigPara.calFactor[TAFE].corFac  = (((RXdata_Handler_CAN2[2] | RXdata_Handler_CAN2[3] << 8)*FACTORDEVISION_OFFSET));
//			ConfigPara.calFactor[TDIODE].corFac = ((RXdata_Handler_CAN2[4] | RXdata_Handler_CAN2[5] << 8)*FACTORDEVISION_OFFSET);
//			ConfigPara.calFactor[TTRAFO].corFac  = (((RXdata_Handler_CAN2[6] | RXdata_Handler_CAN2[7] << 8)*FACTORDEVISION_OFFSET));
//		}
//		else if(RxHeader_CAN2.Identifier == u32CAN2_ID_Frame11)
//		{
//			ConfigPara.calFactor[2].Offset = ((RXdata_Handler_CAN2[0] | RXdata_Handler_CAN2[1] << 8)*FACTORDEVISION);
//			ConfigPara.calFactor[2].Slope = (((RXdata_Handler_CAN2[2] | RXdata_Handler_CAN2[3] << 8)*FACTORDEVISION)-OFFSET);
////			uint16_t TBD3 = RXdata_Handler_CAN2[4] | RXdata_Handler_CAN2[5] << 8;
////			uint16_t TBD4 =(RXdata_Handler_CAN2[6] | RXdata_Handler_CAN2[7] << 8)*FACTORDEVISION;
//		}
//		else if(RxHeader_CAN2.Identifier == 0x1ED001FF)
//		{
//			u8MASTER1_STATUS_CAN2=RXdata_Handler_CAN2[0];
//		}
//#if 0
//		switch(RxHeader_CAN2.Identifier)
//		{
//			case 0X1E010101:
//			{
//				uint16_t TBD1  = (RXdata_Handler_CAN2[0] | RXdata_Handler_CAN2[1] << 8)*FACTORDEVISION;
//				uint16_t TBD2  = (((RXdata_Handler_CAN2[2] | RXdata_Handler_CAN2[3] << 8)*FACTORDEVISION)-OFFSET);
//				uint16_t TBD3   = (RXdata_Handler_CAN2[4] | RXdata_Handler_CAN2[5] << 8)*FACTORDEVISION;
//				uint16_t TBD4  = (((RXdata_Handler_CAN2[6] | RXdata_Handler_CAN2[7] << 8)*FACTORDEVISION)-OFFSET);
//			}
//			break;
//
//			case 0X1E020101:
//			{
//				ConfigPara.limitFactor.DiodeTempLimit=((RXdata_Handler_CAN2[0] | RXdata_Handler_CAN2[1] << 8)*FACTORDEVISION);
//				ConfigPara.limitFactor.trafoTempLimit =(RXdata_Handler_CAN2[2] | RXdata_Handler_CAN2[3] << 8)*FACTORDEVISION;
//				ConfigPara.limitFactor.psfbTempLimit =(RXdata_Handler_CAN2[4] | RXdata_Handler_CAN2[5] << 8)*FACTORDEVISION;
//				ConfigPara.limitFactor.fecTempLimit =(RXdata_Handler_CAN2[6] | RXdata_Handler_CAN2[7] << 8)*FACTORDEVISION;
//			}
//			break;
//
//			case 0X1E030101:
//			{
//				ConfigPara.limitFactor.dcOverCurrentLimit = (RXdata_Handler_CAN2[0] | RXdata_Handler_CAN2[1] << 8)*FACTORDEVISION;
//				ConfigPara.limitFactor.dcOverVoltageLimit = (RXdata_Handler_CAN2[2] | RXdata_Handler_CAN2[3] << 8)*FACTORDEVISION;
//				ConfigPara.limitFactor.dcUnderVoltageLimit = (RXdata_Handler_CAN2[4] | RXdata_Handler_CAN2[5] << 8)*FACTORDEVISION;
//				ConfigPara.limitFactor.dcOverCurrentLimit = (RXdata_Handler_CAN2[6] | RXdata_Handler_CAN2[7] << 8)*FACTORDEVISION;
//			}
//			break;
//			case 0X1E040101:
//			{
//				uint16_t TBD1 = ((RXdata_Handler_CAN2[0] | RXdata_Handler_CAN2[1] << 8)*FACTORDEVISION);
//				uint16_t TBD2  = (((RXdata_Handler_CAN2[2] | RXdata_Handler_CAN2[3] << 8)*FACTORDEVISION)-OFFSET);
//				uint16_t TBD3 = ((RXdata_Handler_CAN2[4] | RXdata_Handler_CAN2[5] << 8)*FACTORDEVISION);
//				uint16_t TBD4  = (((RXdata_Handler_CAN2[6] | RXdata_Handler_CAN2[7] << 8)*FACTORDEVISION)-OFFSET);
//			}
//			break;
//			case 0X1E050101:
//			{
//				uint16_t TBD1 = (RXdata_Handler_CAN2[0] | RXdata_Handler_CAN2[1] << 8)*FACTORDEVISION;
//				uint16_t TBD2 = (((RXdata_Handler_CAN2[2] | RXdata_Handler_CAN2[3] << 8)*FACTORDEVISION)-OFFSET);
//				uint16_t TBD3 = RXdata_Handler_CAN2[4] | RXdata_Handler_CAN2[5] << 8;
//				uint16_t TBD4 = RXdata_Handler_CAN2[6] | RXdata_Handler_CAN2[7] << 8;
//			}
//			break;
//
//
//			/*PC to SLAVE For Calibration*/
//			case 0X1EA00101:
//			{
//				uint16_t TBD1 = RXdata_Handler_CAN2[0] | RXdata_Handler_CAN2[1] << 8;
//				uint16_t TBD2 = RXdata_Handler_CAN2[2] | RXdata_Handler_CAN2[3] << 8;
//				uint16_t TBD3 = RXdata_Handler_CAN2[4] | RXdata_Handler_CAN2[5] << 8;
//				uint16_t TBD4 =(RXdata_Handler_CAN2[6] | RXdata_Handler_CAN2[7] << 8)*FACTORDEVISION;
//			}
//			break;
//			case 0X1EA10101:
//			{
//				uint16_t TBD1  = RXdata_Handler_CAN2[0] | RXdata_Handler_CAN2[1] << 8;
//				uint16_t TBD2 = RXdata_Handler_CAN2[2] | RXdata_Handler_CAN2[3] << 8;
//				uint16_t TBD3 = RXdata_Handler_CAN2[4] | RXdata_Handler_CAN2[5] << 8;
//				uint16_t TBD4 =(RXdata_Handler_CAN2[6] | RXdata_Handler_CAN2[7] << 8)*FACTORDEVISION;
//			}
//			break;
//			case 0X1EA20101:
//			{
//				uint16_t TBD1 = RXdata_Handler_CAN2[0] | RXdata_Handler_CAN2[1] << 8;
//				uint16_t TBD2 = RXdata_Handler_CAN2[2] | RXdata_Handler_CAN2[3] << 8;
//				uint16_t TBD3 = RXdata_Handler_CAN2[4] | RXdata_Handler_CAN2[5] << 8;
//				uint16_t TBD4 =(RXdata_Handler_CAN2[6] | RXdata_Handler_CAN2[7] << 8)*FACTORDEVISION;
//			}
//			break;
//			case 0X1EA30101:
//			{
//				uint16_t TBD1 = RXdata_Handler_CAN2[0] | RXdata_Handler_CAN2[1] << 8;
//				uint16_t TBD2 = RXdata_Handler_CAN2[2] | RXdata_Handler_CAN2[3] << 8;
//				uint16_t TBD3 = RXdata_Handler_CAN2[4] | RXdata_Handler_CAN2[5] << 8;
//				uint16_t TBD4 =(RXdata_Handler_CAN2[6] | RXdata_Handler_CAN2[7] << 8)*FACTORDEVISION;
//			}
//			break;
//			default:
//				break;
//		}
//#endif
//
//#if 0
//		if (HAL_FDCAN_GetRxMessage(&hfdcan1, FDCAN_RX_FIFO0, &RxHeader_CAN1, RXdata_Handler_CAN1) != HAL_OK)
//		{/*Error_Handler();*/}
//		else
//		{/*Do Nothing*/}
//		switch(RxHeader_CAN1.Identifier)
//		{
//			case 0X1E11F101:
//			{
//				Configpara.DutyRef_R=RXdata_Handler_CAN1[0] | RXdata_Handler_CAN1[1] << 8;
//				Configpara.DutyRef_Y=RXdata_Handler_CAN1[2] | RXdata_Handler_CAN1[3] << 8;
//				Configpara.DutyRef_B=RXdata_Handler_CAN1[4] | RXdata_Handler_CAN1[5] << 8;
//				Configpara.PSFBDuty =(RXdata_Handler_CAN1[6] | RXdata_Handler_CAN1[7] << 8)*FACTORDEVISION;
//			}
//			break;
//			case 0X1EC00100:
//			{
//				//u8MASTER1_STATUS=RXdata_Handler_CAN1[0];
//			}
//			break;
//		default:
//			break;
//		}
//#endif
//
//	}
//}
