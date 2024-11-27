///*
// * Can_Data_Xchange.c
// *
// *  Created on: Aug 11, 2023
// *      Author: ujwalpatel
// */
//
//#include "Can_Data_Xchange.h"
//#include "process.h"
//#include"debug.h"
//#include"i2cEeprom.h"
//#include "ntc_measurement.h"
//#include "io.h"
//#include "pcp.h"
//#include "protection.h"
//#include "CAN1_Transmitting.h"
//#include "CAN2_Transmitting.h"
//#include "CAN1_Receving.h"
//#include "CAN2_Receving.h"
//
//#define RSVD 0x00
//
//
//void CAN_DATA_XCHANGING()
//{
//	API_CAN_PSFB_FEC_Volt_Current(Vbus[procValue],Ipsfb[procValue],IafeRms,Iout[procValue]);
//	//API_CAN_PSFB_FEC_Volt_Current(100, 100.5, 115.4, 115.6);
////
//	API_CAN_PSFB_AC_TRAFO_Colt_Current_Temp(Vout[procValue],RSVD,RSVD,TTrafo);
////
//	API_CAN_FEC_PSFB_DIODE_Temp(TAfe,TPsfb,TDiode,RSVD);
//
//	//API_CAN_PHASE_VDC_GAIN_OFFSET(10, 20, 30, 40);
//
//	API_CAN_CELL01_FAULT(fault1.byte, fault2.byte, fault3.byte, fault4.byte, fault5.byte, fault6.byte, fault7.byte, fault8.byte);
//
//	API_CAN_CELL01_Status(status1.byte, status2.byte, status3.byte, RSVD, RSVD, RSVD, RSVD, RSVD);
//
//	//HAL_Delay(10);
//}
