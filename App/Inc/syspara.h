/* File description: Variable structure
*/
#include "main.h"

#define MAX_CELL 13

#ifndef _syspara_
	enum Phase{R_PHASE,Y_PHASE,B_PHASE};
	enum NTC_ch{AFE,PSFB,TRAFO,DIODE};
	enum sw{FEC_H1,FEC_L1,FEC_H2,FEC_L2,PSFB_H1,PSFB_L1,PSFB_H2,PSFB_L2};

	typedef struct
		{
			float Iafe;
			float Vsup;
			float Isup;
		}dcBlockerFactor;

	typedef struct
		{
			float Ipsfb;
			float Vout;
			float VBus;
			float Iout;
			float Tdiode;
			float Ttrafo;
			float Tpsfb;
			float Tafe;
			float rmsCal;
		}lpfFactor;

	typedef struct
	{
		float Offset;
		float Slope;
		float Gain;
		float corFac;
		float sensorGain;
		float boardGain;
	}calibration;

	typedef struct
	{
		float DiodeTempLimit;
		float trafoTempLimit;
		float fecTempLimit;
	    float psfbTempLimit;
	    float dcOverVoltageLimit;
		float dcOverCurrentLimit;
		float dcLinkOverVoltageLimit;
		float dcUnderVoltageLimit;
		float dcUnderCurrentLimit;
	}limitValue;

	typedef struct
	{
	  float Vrated; //system rated voltage
	  float Irated; //system rated Current
	  float Prated; //system rated Power
	  float Voutrated; //Out rated voltage
	  float Ioutrated; //Out rated current
	  float VoutBase; //Peak voltage
	  float IoutBase; //Peak current
	  float freqAfe; //Front-End-Converter switching frequency
	  float Fsystem;
	  float freqInner; //inner loop rate
	  float PSFBdeadband; //deadband value in uSecond for PSFB
	  float FECdeadband; //deadband value in uSecond for FEC
	  float freqPSFB; //Phase-Shifted-Full-Bridge switching frequency
	  float VMF_Vac; // AC voltage Sensor Gain //optional
	  float CMF_Iac; // AC current Sensor Gain //optional
	  float CMF_Iin; // AFE Input current Sensor Gain //optional
	  float VMF_Vout; // Converter Output Voltage Sensor Gain //optional
	  float VMF_Vrect; // AFE Output VOltage Sensor Gain
	  float VMF_Irect; //PSFB INPUT current Sensor Gain //optional
	  float CMF_Iout; // Converter Output Current Sensor Gain //optional
	  float OuterLoopSlowBy;
	  dcBlockerFactor DcBlocker_factor;
	  lpfFactor lpf_factor;
	  calibration calFactor[10];
	  limitValue limitFactor;
	  float DutyRef;
	  float PSFBDuty;
	  float Gate_Command_Pulse;
	  /*float DutyRef_R;
	  float DutyRef_Y;
	  float DutyRef_B;*/
	  float PhaseDelay;
	  uint16_t DutyRef_R;
	  uint16_t DutyRef_Y;
	  uint16_t DutyRef_B;
	}configParameters;

//	//variables for each stage/cell
//	typedef struct
//	{
//		float FEC_Iin;
//		float FEC_Iout;//Front-end converter DC Voltage
//		float FEC_Vout;//MF Trafo AC Current
//		float PSFB_Vout;//Converter Output DC Voltage
//		float PSFB_Iout;//Converter Output DC Current
//		float HsinkTemp[4];
//	}cellSignals;
//
//	typedef struct
//	{
//		float Grid_V;//Grid AC Voltage
//		float Grid_I;//Grid AC Current
//		cellSignals cellSig[MAX_CELL];
//		uint8_t slaveHealth[MAX_CELL];
//	}sysParameters;

#endif



