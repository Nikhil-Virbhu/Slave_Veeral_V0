///*
// * CAN1_Receving.c
// *
// *  Created on: Aug 7, 2023
// *      Author: ujwalpatel
// */
//
//#include "CAN2_Receving.h"
//#include "fdcan.h"
////#include "syspara.h"
//#include "process.h"
//#include "protection.h"
//
//
//#define FACTORDEVISION 0.1
//
//extern FDCAN_RxHeaderTypeDef RxHeader_CAN1,RxHeader_CAN2;
//extern uint8_t u8MASTER1_STATUS;
//extern configParameters ConfigPara;
//
//uint8_t TBD1;
//
//uint8_t RXdata_Handler_CAN1[8]/*,RXdata_Handler_CAN2[8]*/;
//
//void HAL_FDCAN_RxFifo0Callback(FDCAN_HandleTypeDef *hfdcan, uint32_t RxFifo0ITs)
//{
//	if((RxFifo0ITs & FDCAN_IT_RX_FIFO0_NEW_MESSAGE) != RESET)
//	{
//		/* Retrieve Rx messages from RX FIFO0 */
//#if 0
//		if (HAL_FDCAN_GetRxMessage(&hfdcan2, FDCAN_RX_FIFO0, &RxHeader_CAN2, RXdata_Handler_CAN2) != HAL_OK)
//		{	/*Error_Handler();*/
//
//		}
//		else
//		{
//			/*Do Nothing*/
//		}
//#endif
//#if 0
//		switch(RxHeader_CAN2.Identifier)
//		{
//		case 0X1E11F101:
//		{
//			Configpara.DutyRef_R=RXdata_Handler_CAN2[0] | RXdata_Handler_CAN2[1] << 8;
//			Configpara.DutyRef_Y=RXdata_Handler_CAN2[2] | RXdata_Handler_CAN2[3] << 8;
//			Configpara.DutyRef_B=RXdata_Handler_CAN2[4] | RXdata_Handler_CAN2[5] << 8;
//			Configpara.PSFBDuty =(RXdata_Handler_CAN2[6] | RXdata_Handler_CAN2[7] << 8)*FACTORDEVISION;
//		}
//		break;
//		default:
//			break;
//		}
//#endif
//
//		if (HAL_FDCAN_GetRxMessage(&hfdcan1, FDCAN_RX_FIFO0, &RxHeader_CAN1, RXdata_Handler_CAN1) != HAL_OK)
//		{/*Error_Handler();*/}
//		else
//		{/*Do Nothing*/}
//
//		switch(RxHeader_CAN1.Identifier)
//		{
//			case 0X1E0001FF:
//			{
//				DutyRef_R=RXdata_Handler_CAN1[0] | RXdata_Handler_CAN1[1] << 8;
//				DutyRef_Y=RXdata_Handler_CAN1[2] | RXdata_Handler_CAN1[3] << 8;
//				DutyRef_B=RXdata_Handler_CAN1[4] | RXdata_Handler_CAN1[5] << 8;
//				cmd.byte = RXdata_Handler_CAN1[6];
//				TBD1 = RXdata_Handler_CAN1[7];
//				//HAL_DAC_SetValue(&hdac1, DAC_CHANNEL_1, DAC_ALIGN_12B_R, DutyRef_R);
//			}
//			break;
//			case 0X1EC001FF:
//			{
//				u8MASTER1_STATUS=RXdata_Handler_CAN1[0];
//			}
//			break;
//		default:
//			break;
//		}
//	}
//}
//
//
