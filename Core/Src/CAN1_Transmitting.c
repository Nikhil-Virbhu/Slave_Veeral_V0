///*
// * CAN1_Transmitting.c
// *
// *  Created on: Aug 10, 2023
// *      Author: ujwalpatel
// */
//
//#include "CAN1_Transmitting.h"
//#include "fdcan.h"
//#include "error_display.h"
//
//extern uint16_t u8Slavenumber;
//extern FDCAN_TxHeaderTypeDef TxHeader_CAN1;
//uint8_t TxDataHandler_CAN1[8],SUCESS1,FAIL1,SUCESS2,FAIL2;
//
//void API_CAN_HEARTBEAT_CELL0139_MASTER01(uint8_t check)
//{
//	TxDataHandler_CAN1[4]=0;
//	TxDataHandler_CAN1[5]=u8Slavenumber;
//	TxDataHandler_CAN1[6]=0;
//	TxDataHandler_CAN1[7]=0;
//	if(check==CONNECT)
//	{
//		TxDataHandler_CAN1[0]=0x05;
//		if (HAL_FDCAN_AddMessageToTxFifoQ(&hfdcan1, &TxHeader_CAN1, TxDataHandler_CAN1) != HAL_OK)
//		{
//			FAIL1++;
//			add_error_to_list(10);
//		}
//		else
//		{SUCESS1++;}
//		//HAL_Delay(1);
//	}
//	else
//	{
//		TxDataHandler_CAN1[0]=0x00;
//		if (HAL_FDCAN_AddMessageToTxFifoQ(&hfdcan1, &TxHeader_CAN1, TxDataHandler_CAN1) != HAL_OK)
//		{
//			FAIL2++;
//			add_error_to_list(10);
//		}
//		else
//		{SUCESS2++;}
//		//HAL_Delay(1);
//	}
//	HAL_Delay(80);
//
//}
