/* INDI0 --> LED2 is for fault status
 * INDI1 --> LED 3 is for AFE and PSFB status
 * INDI2 --> LED 1 is for Test Mode indication
 */

#define _PROCESS_
//#define OpenLoopTest
#include "process.h"
#include "adc.h"
#include "Kalman.h"
#include "dac.h"
#include "measurment.h"
#include "soft_start.h"
#include "hrtim.h"
#include "filter.h"
#include "pcp.h"
#include "tim.h"
#include "ntc_measurement.h"
#include "protection.h"
#include "debug.h"
//#include "CAN2_Receving.h"
//#include "CAN1_Receving.h"
#include "io.h"
#include "interface.h"
#include "error_display.h"

/*File description: Process execution (algorithm run)
 *Functions used:
 *Reference document:
 */
uint16_t Vref=2048;
LowPassFilter VdcLPF, SupFreqLPF = { 314, 314}, Ipsfb_LPF, Vout_LPF, Vbus_LPF,Iout_LPF,TDiode_LPF,Ttrafo_LPF,TAfe_LPF,TPsfb_LPF ; //Low Pass Filter
DCBlocker Vsup_DCBlock, Isup_DCBlock, Iafe_DCBlock; //DC Blockers
LowPassFilter vsupRmsLPF, isupRmsLPF, iafeRmsLPF;
extern uint16_t u8Slavenumber;
uint16_t PWMON_flag = 0;
uint16_t PSFBON_flag = 0;
uint8_t CELL_Mode = 0;
uint32_t fault_det = 0;
uint8_t test_mode_count=0;
uint32_t timer_period;
uint8_t g_AFE_switch;
uint8_t g_PSFB_switch;
uint8_t g_cell_test_switch;
uint8_t g_reset_switch;

float mod_index = 0.7;
float R_sine_wave[100] = {
		0,							0.06279052,		0.125333234,		0.187381315,		0.248689887,		0.309016994,		0.368124553,		0.425779292,		0.481753674,		0.535826795,
		0.587785252,		0.63742399,		0.684547106,		0.728968627,		0.770513243,		0.809016994,		0.844327926,		0.87630668,		0.904827052,		0.929776486,
		0.951056516,		0.968583161,		0.982287251,		0.992114701,		0.998026728,		1,							0.998026728,		0.992114701,		0.982287251,		0.968583161,
		0.951056516,		0.929776486,		0.904827052,		0.87630668,		0.844327926,		0.809016994,		0.770513243,		0.728968627,		0.684547106,		0.63742399,
		0.587785252,		0.535826795,		0.481753674,		0.425779292,		0.368124553,		0.309016994,		0.248689887,		0.187381315,		0.125333234,		0.06279052,
		0,							-0.06279052,		-0.125333234,		-0.187381315,		-0.248689887,		-0.309016994,		-0.368124553,		-0.425779292,		-0.481753674,		-0.535826795,
		-0.587785252,		-0.63742399,		-0.684547106,		-0.728968627,		-0.770513243,		-0.809016994,		-0.844327926,		-0.87630668,		-0.904827052,		-0.929776486,
		-0.951056516,		-0.968583161,		-0.982287251,		-0.992114701,		-0.998026728,		-1,						-0.998026728,		-0.992114701,		-0.982287251,		-0.968583161,
		-0.951056516,		-0.929776486,		-0.904827052,		-0.87630668,		-0.844327926,		-0.809016994,		-0.770513243,		-0.728968627,		-0.684547106,		-0.63742399,
		-0.587785252,		-0.535826795,		-0.481753674,		-0.425779292,		-0.368124553,		-0.309016994,		-0.248689887,		-0.187381315,		-0.125333234,		-0.06279052

		};


/* CELL TEST MODE START HERE
 * Cell test mode does following thing
 * 1) option to enable PSFB pulses based on GPIO option
 * 2) Lower the protection levels of some functions
 * 3) bypass some of the faults
 * */

void CELL_TEST(void)
{

/*	This function is removed because we will not be using the AFE switching as of now.
/ * Not deleting this code because this may be needed in future.
 *
 */

//	g_AFE_switch = GET_AFE_SWITCH;
  if((g_AFE_switch ==0) && (PWMON_flag==0) && (status1.bits.sHealthStatus == 0))
		{
			//TIM1->CCR1 =TIM1->ARR/2;
		//	TIM1->CCR2 =TIM1->ARR/2;
			PWMON();
			PWMON_flag = 1;
			TurnONFlag=1;
			LED3_ON;

		}
		else if ((g_AFE_switch ==0) && (PWMON_flag==1) && (status1.bits.sHealthStatus == 0))
		{
			LED3_ON;
		}
		else
		{
			PWMOFF();
			TurnONFlag=0;
			LED3_OFF;

			if(PSFBON_flag == 0)
			{
				LED3_OFF;
			}
         }

		//PSFB switching function
//  	  g_PSFB_switch = GET_PSFB_SWITCH;
  	  if((g_PSFB_switch==0) && (PSFBON_flag ==0)  && (status1.bits.sHealthStatus == 0))
		{
			PSFBON();
			PSFBON_flag = 1;
			Psfb_OnOffFlag = 1;
			LED3_ON;
		}
		else if ((g_PSFB_switch==0) && (PSFBON_flag ==1) && (status1.bits.sHealthStatus == 0))
		{
			LED3_ON;
		}
		else
		{
			PSFBOFF();

			if(PWMON_flag == 0)
			{
				LED3_OFF;
			}
        }

		//Lowering the threshold of faults for the test mode
		overlinkVolt.threshold = 850.0f;		//dc link over voltage setting
		overlinkCurr.threshold = 5.0f;		// dc link over current setting
		overIout.threshold = 5.0f;				// Iout over current setting

		//TODO: bypass some of the faults
}

/* CELL TEST MODE END HERE */

/*
* Function Description: Function to start PSFB output waveform
* Input:
* Return:
*/
void PSFBON(void)
{
	SoftStartFlag = 1;
	phase_diff.Fix = 2800;			// 4250 is for 50 % phase shift (8500*0.5)= 4250
	phase_diff.Dynamic = 0;
	HAL_HRTIM_WaveformCounterStart(&hhrtim1,HRTIM_TIMERID_TIMER_C + HRTIM_TIMERID_TIMER_D+HRTIM_TIMERID_TIMER_E);
	HRTIM1->sTimerxRegs[HRTIM_TIMERINDEX_TIMER_C].CNTxR=500;
	HRTIM1->sTimerxRegs[HRTIM_TIMERINDEX_TIMER_D].CNTxR=500;
	HRTIM1->sTimerxRegs[HRTIM_TIMERINDEX_TIMER_E].CNTxR=500;
	HAL_HRTIM_WaveformOutputStart(&hhrtim1, HRTIM_OUTPUT_TC1 | HRTIM_OUTPUT_TC2 | HRTIM_OUTPUT_TD1 | HRTIM_OUTPUT_TD2 ); //Timer C and D for PSFB
}

/*
* Function Description: Function to stop PSFB output waveform
* Input:
* Return:
*/
void PSFBOFF(void)
{
	Psfb_OnOffFlag = 0;
	cmd.bits.psfb_on = 0;
	status1.bits.psfbFeedback = 0;
	SoftStartFlag = 0;
	phase_diff.Fix = 2800;			// 4250 is for 50 % phase shift (8500*0.5)= 4250
	phase_diff.Dynamic = 0;
	HAL_HRTIM_WaveformOutputStop(&hhrtim1, HRTIM_OUTPUT_TC1 | HRTIM_OUTPUT_TC2 | HRTIM_OUTPUT_TD1 | HRTIM_OUTPUT_TD2 );
	PSFBON_flag = 0;

	HRTIM1->sTimerxRegs[HRTIM_TIMERINDEX_TIMER_D].CMP1xR = 1+ phase_diff.Dynamic;
	HRTIM1->sTimerxRegs[HRTIM_TIMERINDEX_TIMER_D].CMP2xR = 4250 + phase_diff.Dynamic;

	//HAL_HRTIM_WaveformCounterStop(&hhrtim1,HRTIM_TIMERID_TIMER_C + HRTIM_TIMERID_TIMER_D+HRTIM_TIMERID_TIMER_E);
	HRTIM1->sTimerxRegs[HRTIM_TIMERINDEX_TIMER_C].CNTxR=0;
	HRTIM1->sTimerxRegs[HRTIM_TIMERINDEX_TIMER_D].CNTxR=0;
	HRTIM1->sTimerxRegs[HRTIM_TIMERINDEX_TIMER_E].CNTxR=0;

}

/*
* Function Description:
* Input:
* Return:
*/
void PWMON(void)
{
	//Pwm control configurations TBD
//	Psfb_OnOffFlag = 1;
	HAL_HRTIM_WaveformOutputStart(&hhrtim1, HRTIM_OUTPUT_TA1 | HRTIM_OUTPUT_TA2 | HRTIM_OUTPUT_TB1 | HRTIM_OUTPUT_TB2 ); //Timer A and B for AFE PWM

}

/*
* Function Description:
* Input:
* Return:
*/
void PWMOFF(void)
{
	//Pwm control configurations TBD
	HAL_HRTIM_WaveformOutputStop(&hhrtim1, HRTIM_OUTPUT_TA1 | HRTIM_OUTPUT_TA2 | HRTIM_OUTPUT_TB1 | HRTIM_OUTPUT_TB2 ); //Timer A and B for PWM AFE
	PWMON_flag = 0;
}

/*
* Function Description:
* Input:
* Return:
*/
void protectionMonitoring_DC(void)
{
/*	check_over_limitI(&overlinkCurr,Ipsfb[procValue] );
	if(overlinkCurr.ovlFault){
		fault1.bits.over_Ilink =  1;
		add_error_to_list(1);
		}
	else{
		fault1.bits.over_Ilink =  0;
		remove_error_from_list(1);
		}
*/

	check_over_limitI(&overIout,Iout[procValue] );
	if(overIout.ovlFault){
		fault1.bits.over_Iout = 1;
		add_error_to_list(3);
	}
	else{
		fault1.bits.over_Iout = 0;
		remove_error_from_list(3);
	}
/*This section is not mounted in slave PCB
	check_over_limit(&overVout, Vout[procValue] );
	if(overVout.ovlFault)
		fault1.bits.over_Vout = 1;
	else
		fault1.bits.over_Vout = 0;
*/

	check_over_limit(&overlinkVolt, Vbus[procValue]);
	if(overlinkVolt.ovlFault){
		fault1.bits.over_Vlink = 1;
		add_error_to_list(2);
	}
	else{
		fault1.bits.over_Vlink = 0;
		remove_error_from_list(2);
	}

/*	This section is not mounted in slave PCB
 * check_under_limit(&underVout, Vout[procValue] );
	if(underVout.underLFault)
		fault2.bits.under_Vout = 1;
	else
		fault2.bits.under_Vout = 0;*/
//bypass for cell testing
/*	check_under_limit(&underlinkVolt,Vbus[procValue]);
	if(underlinkVolt.underLFault){
		fault2.bits.underVlink = 1;
		add_error_to_list(5);
		}
	else{
		fault2.bits.underVlink = 0;
		remove_error_from_list(5);
		}
		*/
}

/*This section is not mounted in slave PCB
 * void protectionMonitoring_AC(void){
	//Checking for over supply current
	check_over_limitI(&overIsupply, Isuprms);
	if(overIsupply.ovlFault)
		fault1.bits.overIsup = 1;
	else
		fault1.bits.overIsup = 0;

	//Checking for Over Iac Slave_in current
	check_over_limitI(&overIac, IafeRms);
	if(overIac.ovlFault)
		fault1.bits.over_Iafe = 1;
	else
		fault1.bits.over_Iafe = 0;

	//Checking for over supply voltage
	check_over_limit(&overVsupply, Vsuprms);
	if(overVsupply.ovlFault)
		fault1.bits.overVsup = 1;
	else
		fault1.bits.overVsup = 0;

	check_under_limit(&underSupplyVolt,Vsuprms );
	if(underSupplyVolt.underLFault)
		fault2.bits.underSupVolt = 1;
	else
		fault2.bits.underSupVolt = 0;
}*/

void protectionMonitoring_Temp(void){
	if(overDiodeTemp.ovlFault){
		fault4.bits.overTemp_diode = 1;
		add_error_to_list(17);
	}
	else{
		fault4.bits.overTemp_diode = 0;
		remove_error_from_list(17);
	}

	if(overAfeTemp.ovlFault){
		fault4.bits.overTemp_afe = 1;
		add_error_to_list(14);
	}
	else{
		fault4.bits.overTemp_afe = 0;
		remove_error_from_list(14);
	}

	if(overPsfbTemp.ovlFault){
		fault4.bits.overTemp_psfb = 1;
		add_error_to_list(16);
	}
	else{
		fault4.bits.overTemp_psfb = 0;
		remove_error_from_list(16);
	}

	if(overTrafoTemp.ovlFault){
		fault4.bits.overTemp_trafo = 1;
		add_error_to_list(15);
	}
	else{
		fault4.bits.overTemp_trafo = 0;
		remove_error_from_list(15);
	}
}

/*
* Function Description:
* Input:
* Return:
*/
/*This section is not mounted in slave PCB
 * void calculateRMS(unsigned int SamplingFreq, unsigned int Fsystem){
	static uint8_t smplCnt = 0;
	uint8_t Temp_sample=SamplingFreq/Fsystem;

	vsup_rms_buffer = (float)vsup_rms_buffer + (float)(Vsup[procValue]*Vsup[procValue]);
	isup_rms_buffer = (float)isup_rms_buffer + (float)(Isup[procValue]*Isup[procValue]);
	iafe_rms_buffer  = (float)iafe_rms_buffer + (float)(Iafe[procValue]*Iafe[procValue]);

	smplCnt++;
	if(smplCnt >= Temp_sample){
		smplCnt = 0;
		vsupRmsLPF.xn = (float)sqrt(vsup_rms_buffer*VphBase/Temp_sample);
		isupRmsLPF.xn = (float)sqrt(isup_rms_buffer*IphBase/Temp_sample);
		iafeRmsLPF.xn = (float)sqrt(iafe_rms_buffer*IphBase/Temp_sample);

		vsupRmsLPF.yn = vsupRmsLPF.xn + (float)ConfigPara.lpf_factor.rmsCal*(vsupRmsLPF.yn - vsupRmsLPF.xn);
		isupRmsLPF.yn = isupRmsLPF.xn + (float)ConfigPara.lpf_factor.rmsCal*(isupRmsLPF.yn - isupRmsLPF.xn);
		iafeRmsLPF.yn = iafeRmsLPF.xn + (float)ConfigPara.lpf_factor.rmsCal*(iafeRmsLPF.yn - iafeRmsLPF.xn);

		Vsuprms = vsupRmsLPF.yn;
		Isuprms = isupRmsLPF.yn;
		IafeRms = iafeRmsLPF.yn;

		vsup_rms_buffer = 0.0f;
		isup_rms_buffer = 0.0f;
		iafe_rms_buffer = 0.0f;
	  //  protectionMonitoring_AC();
  }

}*/

/*
* Function Description:
* Input:
* Return:
*/
void Parameter_Calculations(void)
{
	parameterCalculations_ADC1(); //ADC1 measurement
	parameterCalculations_ADC2(); //ADC2 measurement

//Calculation of AC quantities like Iac, Vsup, Isup filtering and DC Blocking + Kalman Starts

/*	This section is not mounted in slave PCB
 * Iafe[rawValue] = ((((float)Adc_Avg_Buffer[IAFE]- Vref)*ADC_RESOLUTION*ConfigPara.calFactor[IAFE].Gain)* ConfigPara.calFactor[IAFE].corFac)/IphBase;//3.39
	iafeRmsLPF.yn = ConfigPara.DcBlocker_factor.Iafe*iafeRmsLPF.yn+(Iafe[rawValue]-iafeRmsLPF.xn);  // DC Blockers
	iafeRmsLPF.xn = Iafe[rawValue];
	Iafe[procValue] = iafeRmsLPF.yn; // only DC blocker Output
*/

/* This section is not mounted in slave PCB
	Vsup[rawValue] = ((((float)Adc_Avg_Buffer[VSUP]- Vref)*ADC_RESOLUTION*ConfigPara.calFactor[VSUP].Gain)* ConfigPara.calFactor[VSUP].corFac)/	IphBase; //3.39
	Vsup_DCBlock.yn = ConfigPara.DcBlocker_factor.Vsup*Vsup_DCBlock.yn+(Vsup[rawValue]-Vsup_DCBlock.xn);  // DC Blockers
	Vsup_DCBlock.xn = Vsup[rawValue];
	Vsup[procValue] = Vsup_DCBlock.yn; // only DC blocker Output
*/

/* This section is not mounted in slave PCB
	Isup[rawValue] = ((((float)Adc_Avg_Buffer[ISUP]- Vref)*ADC_RESOLUTION*ConfigPara.calFactor[ISUP].Gain)* ConfigPara.calFactor[ISUP].corFac)/IphBase;//3.39
	Isup_DCBlock.yn = ConfigPara.DcBlocker_factor.Isup*Isup_DCBlock.yn+(Isup[rawValue]-Isup_DCBlock.xn);  // DC Blockers
	Isup_DCBlock.xn = Isup[rawValue];
	Isup[procValue]=Isup_DCBlock.yn; // only DC blocker Output

*/


	//Calculation of DC quantities and low pass filtering
/*	This section is not mounted in slave PCB
 * Vout[rawValue] = ((float)Adc_Avg_Buffer[VOUT]*ADC_RESOLUTION);
	Vout[rawValue] = ((Vout[rawValue]*ConfigPara.calFactor[VOUT].Slope)+ ConfigPara.calFactor[VOUT].Offset)*(ConfigPara.calFactor[VOUT].corFac); // Low pass filter for Vout
	Vout_LPF.xn = Vout[rawValue];
	Vout_LPF.yn = Vout_LPF.xn + ((float)ConfigPara.lpf_factor.Vout*(Vout_LPF.yn-Vout_LPF.xn));
	Vout[procValue] = Vout_LPF.yn;*/

	Ipsfb[rawValue] = ((float)Adc_Avg_Buffer[IPSFB]*ADC_RESOLUTION);
	Ipsfb[rawValue] = ((Ipsfb[rawValue]*ConfigPara.calFactor[IPSFB].Slope) + ConfigPara.calFactor[IPSFB].Offset)*(ConfigPara.calFactor[IPSFB].corFac); // Low pass filter for Irect
	Ipsfb_LPF.xn = Ipsfb[rawValue];
	Ipsfb_LPF.yn = Ipsfb_LPF.xn + ((float)ConfigPara.lpf_factor.Ipsfb*(Ipsfb_LPF.yn-Ipsfb_LPF.xn));
	Ipsfb[procValue] = Ipsfb_LPF.yn;

	Iout[rawValue] = ((float)Adc_Avg_Buffer[IOUT]*ADC_RESOLUTION);
	Iout[rawValue] = ((Iout[rawValue]*ConfigPara.calFactor[IOUT].Slope) + ConfigPara.calFactor[IOUT].Offset)*(ConfigPara.calFactor[IOUT].corFac); // Low pass filter for Iout
	Iout_LPF.xn = Iout[rawValue];
	Iout_LPF.yn = Iout_LPF.xn + ((float)ConfigPara.lpf_factor.Iout*(Iout_LPF.yn-Iout_LPF.xn));
	Iout[procValue] = Iout_LPF.yn;

	Vbus[rawValue] = ((float)Adc_Avg_Buffer[VBUS] * ADC_RESOLUTION);

//	if(Psfb_OnOffFlag == 1)
	{
//		Vbus[rawValue] = ((Vbus[rawValue]*393.45f) - 18.305f )*(ConfigPara.calFactor[VBUS].corFac); // Low pass filter for VDC bus
	}
//	else
	{
		Vbus[rawValue] = ((Vbus[rawValue]*ConfigPara.calFactor[VBUS].Slope) + ConfigPara.calFactor[VBUS].Offset)*(ConfigPara.calFactor[VBUS].corFac); // Low pass filter for VDC bus
	}

	Vbus_LPF.xn = Vbus[rawValue];
	Vbus_LPF.yn = Vbus_LPF.xn + ((float)ConfigPara.lpf_factor.VBus*(Vbus_LPF.yn-Vbus_LPF.xn));
	Vbus[procValue] = Vbus_LPF.yn;
//	Vbus[procValue] = Vbus[rawValue];


	// Calculating the RMS and AC Protection function at every 1 mSec
	//calculateRMS(ConfigPara.freqInner, ConfigPara.Fsystem);	//Removing entire function because none of the section is mounted on PCB

}

/*
* Function Description:
* Input:
* Return:
*/
void tempParameter_Calculations(void)
{
	parameterCalculations_ADC3(); //ADC3 measurement for temperature sensing at low rate 10*4 Hz
	parameterCalculations_ADC4();
	//Calculation of Temperature and low pass filtering
	TDiode_Res[rawValue] = (((float)Adc_Avg_Buffer[TDIODE]) * ADC_RESOLUTION); // Low pass filter for Ttrafo (in resistance)
	TDiode_LPF.xn = TDiode_Res[rawValue];
	TDiode_LPF.yn = TDiode_LPF.xn + ((float)ConfigPara.lpf_factor.Tdiode*(TDiode_LPF.yn-TDiode_LPF.xn));
	TDiode_Res[procValue] = TDiode_LPF.yn;
	TDiode_Res[procValue] = ((TDiode_Res[procValue] * ConfigPara.calFactor[TDIODE].Slope) + ConfigPara.calFactor[TDIODE].Offset)*(ConfigPara.calFactor[TDIODE].corFac);
	TDiode = calculateTemperature(TDiode_Res[procValue]); //Converting resistance to temperature

	TTrafo_Res[rawValue] = (((float)Adc_Avg_Buffer[TTRAFO]) * ADC_RESOLUTION); // Low pass filter for Tfec (in resistance)
	Ttrafo_LPF.xn = TTrafo_Res[rawValue];
	Ttrafo_LPF.yn = Ttrafo_LPF.xn + ((float)ConfigPara.lpf_factor.Ttrafo*(Ttrafo_LPF.yn-Ttrafo_LPF.xn));
	TTrafo_Res[procValue] = Ttrafo_LPF.yn;
	TTrafo_Res[procValue] = ((TTrafo_Res[procValue] * ConfigPara.calFactor[TTRAFO].Slope) + ConfigPara.calFactor[TTRAFO].Offset)*(ConfigPara.calFactor[TTRAFO].corFac);
	//TTrafo = calculateTemperature(TTrafo_Res[procValue]); //Converting resistance to temperature

	//This calculation is taken reference from Sensing.xlsx
	TTrafo_calc = (TTrafo_Res[procValue] /5.5455)*1000;
	TTrafo_meas = (TTrafo_calc -100) /0.39;
	TTrafo = calculateTrafoTemperature(TTrafo_meas);

	//For temperature calibration (power board), R28_1 and R28_2 changed to 1.5K (earlier 2.2K) and R29_1 and R29_2 changed to 15K (earlier 22K)
	TAfe_Res[rawValue] = (((float)Adc_Avg_Buffer[TAFE]) * ADC_RESOLUTION); // Low pass filter for Tfec (in resistance)
	TAfe_LPF.xn = TAfe_Res[rawValue];
	TAfe_LPF.yn = TAfe_LPF.xn + ((float)ConfigPara.lpf_factor.Tafe*(TAfe_LPF.yn - TAfe_LPF.xn));
	TAfe_Res[procValue] = TAfe_LPF.yn;
	TAfe_Res[procValue] = ((TAfe_Res[procValue] * ConfigPara.calFactor[TAFE].Slope) + ConfigPara.calFactor[TAFE].Offset)*(ConfigPara.calFactor[TAFE].corFac);
	TAfe = calculateTemperature(TAfe_Res[procValue]); //Converting resistance to temperature

	TPsfb_Res[rawValue] = (((float)Adc_Avg_Buffer[TPSFB]) * ADC_RESOLUTION); // Low pass filter for Tpsfb (in resistance)
	TPsfb_LPF.xn = TPsfb_Res[rawValue];
	TPsfb_LPF.yn = TPsfb_LPF.xn + ((float)ConfigPara.lpf_factor.Tpsfb *(TPsfb_LPF.yn-TPsfb_LPF.xn));
	TPsfb_Res[procValue] = TPsfb_LPF.yn;
	TPsfb_Res[procValue] = /*TPsfb_Res[procValue]/0.000083; */((TPsfb_Res[procValue] * ConfigPara.calFactor[TPSFB].Slope) + ConfigPara.calFactor[TPSFB].Offset)*(ConfigPara.calFactor[TPSFB].corFac);
	TPsfb = calculateTemperature(TPsfb_Res[procValue]); //Converting resistance to
    protectionMonitoring_Temp();
}

/* Call this function once after Control Initialisation */
void phaseShift_Pwm(void){
	if((u8Slavenumber > 0 && u8Slavenumber <= 4)  || (u8Slavenumber > 13 && u8Slavenumber <= 17) || (u8Slavenumber > 26 && u8Slavenumber <= 30 )){
		HRTIM1->sMasterRegs.MCMP1R = 1; //0 degree phase shift
	}
	else if((u8Slavenumber > 4 && u8Slavenumber <= 8) || (u8Slavenumber > 17 && u8Slavenumber <= 21) || (u8Slavenumber > 30 && u8Slavenumber <= 34 )){
			HRTIM1->sMasterRegs.MCMP1R = 11333; //120 degree phase shift
	}
	else if((u8Slavenumber > 8 && u8Slavenumber <= 13) || (u8Slavenumber > 21 && u8Slavenumber <= 26) || (u8Slavenumber > 34 && u8Slavenumber <= 39 )){
			HRTIM1->sMasterRegs.MCMP1R = 22666; //240 degree phase shift
	}
	else{
		HRTIM1->sMasterRegs.MCMP1R = 0; //No waveform
	}
}

void dutyUpdate(void){

	if(u8Slavenumber > 0 && u8Slavenumber <= 13  ){
		V_cmd = ((float)(DutyRef_R - 2000)/(10 * 100));
	}
	else if (u8Slavenumber > 13 && u8Slavenumber <= 26  ){
		V_cmd = ((float)(DutyRef_Y - 2000)/(10 * 100));
	}
	else if(u8Slavenumber > 26 && u8Slavenumber <= 39 ){
		V_cmd = ((float)(DutyRef_B - 2000)/(10 * 100));
	}

	HRTIM1->sTimerxRegs[HRTIM_TIMERINDEX_TIMER_A].CMP3xR = (uint16_t)(((float) V_cmd * HRTIM1->sTimerxRegs[HRTIM_TIMERINDEX_TIMER_A].PERxR  + (float) HRTIM1->sTimerxRegs[HRTIM_TIMERINDEX_TIMER_A].PERxR) * 0.5f) ;
	HRTIM1->sTimerxRegs[HRTIM_TIMERINDEX_TIMER_B].CMP3xR = (uint16_t)(((float)(- V_cmd) * HRTIM1->sTimerxRegs[HRTIM_TIMERINDEX_TIMER_B].PERxR + (float) HRTIM1->sTimerxRegs[HRTIM_TIMERINDEX_TIMER_B].PERxR) * 0.5f);

}
/*
* Function Description: Initializing peripherals
* Input:
* Return:
*/
void ControlInit(void)
{
	// System Interrupt for Low priority task based on RoundRobin
	TIM6->PSC = 1; //Timer 6 (2 KHz= 500us)
	TIM6->ARR = (uint16_t)(SystemCoreClock/((1+TIM6->PSC)*(2000))) - 1;

	// High Priority System Interrupt for Control System, --> ADC1 and ADC2 triggered with this timer
	TIM7->PSC = 0; //Timer 7
	TIM7->ARR = (uint16_t)(SystemCoreClock/((1+TIM7->PSC)*(5000))) - 1;

	// for Slow Quantities Measurement like Temperature-> ADC3 and ADC4  is triggered with this timer
	TIM4->PSC=249; //Timer 4 at 10*4 = 40 Hz
    TIM4->ARR = (uint16_t)(SystemCoreClock/((1+TIM4->PSC)*(40))) - 1;

	HAL_TIM_Base_Start_IT(&htim4);
	HAL_TIM_Base_Start_IT(&htim6);
	HAL_TIM_Base_Start_IT(&htim7);

	HAL_ADC_Start_DMA(&hadc1,(uint32_t*)Adc1_Buffer, ADC1_BUFFER_SIZE); //Start ADC1
//	HAL_ADC_Start_DMA(&hadc2,(uint32_t*)Adc2_Buffer, ADC2_BUFFER_SIZE); //Start ADC2
//	HAL_ADC_Start_DMA(&hadc3,(uint32_t*)Adc3_Buffer, ADC3_BUFFER_SIZE); //Start ADC3
//	HAL_ADC_Start_DMA(&hadc4,(uint32_t*)Adc4_Buffer, ADC4_BUFFER_SIZE); //Start ADC4

	HAL_DAC_Start(&hdac1, DAC_CHANNEL_1); // Start DAC
	HAL_DAC_Start(&hdac1, DAC_CHANNEL_2); // Start DAC

//	HAL_GPIO_WritePin(INH_GPIO_Port, INH_Pin, GPIO_PIN_RESET); // It is to be set Low for enable the pulses from Hardware IC (74HC573).

	HAL_HRTIM_WaveformCounterStart(&hhrtim1, HRTIM_TIMERID_MASTER + HRTIM_TIMERID_TIMER_A + HRTIM_TIMERID_TIMER_B + HRTIM_TIMERID_TIMER_C + HRTIM_TIMERID_TIMER_D+HRTIM_TIMERID_TIMER_E ); //Timer A,B,C and D of HRTIM1 counter start
	
	faultInit(); // Fault Structure Initialization
	reset_driver(); // To reset all the driver before starting Pulses

}
/*
* Function Description: Parameter initialization
* Input:
* Return:
*/
void ParaInit(void)
{
	ConfigPara.Vrated = 1000.0f; //system rated Line to Line voltage (RMS)
	ConfigPara.Prated = 15000.0f; //system rated Power (Peak Power)
	ConfigPara.Irated = ConfigPara.Prated/(1.73f*ConfigPara.Vrated); //system rated Current (RMS)
	ConfigPara.Voutrated = 1000.0f; //converter DC output voltage
	ConfigPara.Fsystem = 50.0f; //supply frequency
	ConfigPara.Ioutrated = ConfigPara.Prated/ConfigPara.Voutrated;

	ConfigPara.freqInner = 5000.0f ;//AFE switching freq.
	ConfigPara.freqAfe = 5000.0f; //Front-End-Converter switching frequency
	ConfigPara.PSFBdeadband = 1.2f; //deadband value in uSecond for PSFB
	ConfigPara.FECdeadband = 1.2f; //deadband value in uSecond for FEC
	ConfigPara.freqPSFB = 20000.0f; //Phase-Shifted-Full-Bridge switching frequency

	//Calibration factor for AC quantities
/*	This section is not mounted in slave PCB
 * ConfigPara.calFactor[VSUP].Gain = (AC_VOLTAGE_GAIN*2.0*1.41/3.0f);
	ConfigPara.calFactor[VSUP].corFac = 0;
	ConfigPara.calFactor[IAFE].Gain = (AC_CURRENT_GAIN*2.0*1.41/3.0f);
	ConfigPara.calFactor[IAFE].corFac = 0;
	ConfigPara.calFactor[ISUP].Gain = (AC_CURRENT_GAIN*2.0*1.41/3.0f);
	ConfigPara.calFactor[ISUP].corFac = 0;*/

	//  Calibration factor for DC quantities
	ConfigPara.calFactor[IPSFB].Slope = (OUTPUT_CURRENT_GAIN/3.0f);
	ConfigPara.calFactor[IPSFB].Offset = 0;
	ConfigPara.calFactor[IPSFB].corFac = 1;

/*	This section is not mounted in slave PCB
 * ConfigPara.calFactor[VOUT].Slope = 637.7848f;
	ConfigPara.calFactor[VOUT].Offset = -36.7093f;
	ConfigPara.calFactor[VOUT].corFac = 1;*/

	ConfigPara.calFactor[IOUT].Slope =  9.4845f; /*(OUTPUT_CURRENT_GAIN/3.0f)*/
	ConfigPara.calFactor[IOUT].Offset = -9.089f;
	ConfigPara.calFactor[IOUT].Gain = ConfigPara.calFactor[IOUT].boardGain * ConfigPara.calFactor[IOUT].sensorGain * ADC_RESOLUTION;
	ConfigPara.calFactor[IOUT].boardGain = 1;
	ConfigPara.calFactor[IOUT].sensorGain = 1;
	ConfigPara.calFactor[IOUT].corFac = 0.64;

	//ConfigPara.calFactor[VDC_BUS].Gain=SENSOR_GAIN*CKT_GAIN;//
	ConfigPara.calFactor[VBUS].Slope = 372.51f;
	ConfigPara.calFactor[VBUS].Offset = -0.3692f;
	ConfigPara.calFactor[VBUS].corFac = 1;

	//Calibration factor for temperature sensing (Slope currently zero will add the formula later on)
	//ConfigPara.calFactor[NTCDIODE].Gain=0;
	ConfigPara.calFactor[TDIODE].Slope = 12079.0f;
	ConfigPara.calFactor[TDIODE].Offset = 0;
	ConfigPara.calFactor[TDIODE].corFac = 1;



	//ConfigPara.calFactor[TTRAFO].Gain=0;
	ConfigPara.calFactor[TTRAFO].Slope = 1.0f;
	ConfigPara.calFactor[TTRAFO].Offset = 0;
	ConfigPara.calFactor[TTRAFO].corFac = 1;



	//ConfigPara.calFactor[TFEC].Gain=0;
	ConfigPara.calFactor[TAFE].Slope = 12079.0f; //From calibration
	ConfigPara.calFactor[TAFE].Offset = 0.0f; //From calibration
	ConfigPara.calFactor[TAFE].corFac = 1;

	//ConfigPara.calFactor[TPSFB].Gain=0;
	ConfigPara.calFactor[TPSFB].Slope = 12079.0f; //From calibration
	ConfigPara.calFactor[TPSFB].Offset = 0.0f; //From calibration
	ConfigPara.calFactor[TPSFB].corFac = 1;

	#ifdef _SKIP_
		VphBase = (100.0f*ConfigPara.Vrated*1.41f/(1.73f)); //User Defined PerUnit
		IphBase = (100.0f*ConfigPara.Irated*1.41f); //User Defined PerUnit
		ConfigPara.VoutBase = (100.0f*ConfigPara.Voutrated); //Peak voltage
		ConfigPara.IoutBase = (100.0f*ConfigPara.Ioutrated); //Peak Current
	#endif

	//DC Blocker factor for AC quantities
/*	This section is not mounted in slave PCB
 * ConfigPara.DcBlocker_factor.Iafe = 0.998f;
	ConfigPara.DcBlocker_factor.Vsup = 0.998f;
	ConfigPara.DcBlocker_factor.Isup = 0.998f;*/

	//Low Pass Filter factor for DC quantities
	ConfigPara.lpf_factor.Tdiode = 0.8f;
	ConfigPara.lpf_factor.Ttrafo = 0.8f;
	ConfigPara.lpf_factor.Tafe = 0.8f;
	ConfigPara.lpf_factor.Tpsfb = 0.8f;
	ConfigPara.lpf_factor.Ipsfb = 0.995f;
	//ConfigPara.lpf_factor.Vout = 0.995f;		//This section is not mounted in slave PCB
	ConfigPara.lpf_factor.VBus = 0.995f;
	ConfigPara.lpf_factor.Iout = 0.995f;
}

/*
* Function Description:
* Input:
* Return:
*/
void Tim7_Execution(void)
{
	error_display(); // Error display function
//	MCU_LIVE_ON;
    Parameter_Calculations();
    protectionMonitoring_DC();

	faultDetection(); // keep this enable to detect fault
	slave_health();
	DAC_Out();
	turnOn_Scan();

	if(SoftStartFlag == 1){
		if((phase_diff.Dynamic == phase_diff.Fix) && (phase_diff.Fix > 0)  ){
			SoftStartFlag = 0;
			status1.bits.psfbFeedback = 1;
		}
	}

	if(Psfb_OnOffFlag == 1){
		softStartVariable(&phase_diff, 5000.0f, 4250.0f/7.0f , 4250.0f/7.0f);
		HRTIM1->sTimerxRegs[HRTIM_TIMERINDEX_TIMER_D].CMP1xR = 1+ phase_diff.Dynamic;
		HRTIM1->sTimerxRegs[HRTIM_TIMERINDEX_TIMER_D].CMP2xR = 4250 + phase_diff.Dynamic;
	}
		#ifdef OpenLoopTest
				V_cmd= ((float)Ma*sinf((float)TWO_PI*sinFreq*n_spwm/(float)innerFreq)); // 0.5 + ma* 0.5 sin (2*pi*f*n*Ts)
				//DAC_Value=(fabs)((V_cmd*0.5+0.5)*4096);
				HRTIM1->sTimerxRegs[HRTIM_TIMERINDEX_TIMER_A].CMP2xR = (uint16_t)(((float)0.5+0.5*V_cmd)*HRTIM1->sTimerxRegs[HRTIM_TIMERINDEX_TIMER_A].PERxR);
				HRTIM1->sTimerxRegs[HRTIM_TIMERINDEX_TIMER_B].CMP2xR = (uint16_t)(((float)0.5-0.5*V_cmd)*HRTIM1->sTimerxRegs[HRTIM_TIMERINDEX_TIMER_B].PERxR);
				n_spwm = n_spwm+1;
				if(n_spwm > ((float)innerFreq/(sinFreq))-1){
					n_spwm = 0;
				}
		#else

				/* Removing the AFE sine wave generation function as it is not needed now.
				 * Not removing from code because it maybe needed in future
				 */
//				if(HAL_GPIO_ReadPin(AFE_Switch_GPIO_Port,AFE_Switch_Pin) ==0 && PWMON_flag==1 && (status1.bits.sHealthStatus == 0))
				if(PWMON_flag==1 && (status1.bits.sHealthStatus == 0))
				{
					test_mode_count++;
					if(test_mode_count>=100)
					{
						test_mode_count =0;
					}
					timer_period = HRTIM1->sTimerxRegs[HRTIM_TIMERINDEX_TIMER_B].PERxR;

					V_cmd = (R_sine_wave[test_mode_count]* mod_index+1) * (timer_period/2) ;
					//HAL_DAC_SetValue(&hdac1, DAC_CHANNEL_1, DAC_ALIGN_12B_R, V_cmd*0.1);

					HRTIM1->sTimerxRegs[HRTIM_TIMERINDEX_TIMER_A].CMP3xR = V_cmd;
					HRTIM1->sTimerxRegs[HRTIM_TIMERINDEX_TIMER_B].CMP3xR = V_cmd;
				}
				else
				{
					dutyUpdate();
				}
		#endif

//				MCU_LIVE_OFF;
}

/*
* Function Description:Low priority tasks execution in round robin algorithm
* Input:
* Return:
*/
void TIM6_Execution(void)
{

	CNT_TIM6++; // Increment at every 50 mSec
	if (CNT_TIM6%2 == 0){
		mSec1_Flag = 1; // Every 1 mSec
	}
	if (CNT_TIM6%80 == 0){
		mSec40_Flag = 1; // Every 40 mSec
	}
	if (CNT_TIM6%2000 == 0){
		Sec1_Flag = 1; // Every 1 Sec
	}
	if(CNT_TIM6%100 == 0){
		tempParameter_Calculations();
		mSec100_Flag = 1; //Every 100 mSec
	}
}

/*
* Function Description: //Function to turn on the slave (SYNC pin will receive signal from master
* Input:
* Return:
*/
void turnOn_Scan(void)
{

//	g_cell_test_switch =GET_CELL_TEST_SWITCH;
	if (g_cell_test_switch ==0)		// CELL TEST MODE
	{
		LED1_ON;
		CELL_Mode = 1;		//Test mode enable
		CELL_TEST();
	}

	else
	{
		CELL_Mode = 0;		// Normal mode of operation
		LED1_OFF;
		if((cmd.bits.psfb_on == 1) && (Psfb_OnOffFlag == 0) && (TurnONFlag == 0)  && (status1.bits.sHealthStatus == 0) )
		{
			Psfb_OnOffFlag = 1;
			PSFBON();
		}

		if((cmd.bits.system_on == 1) && (TurnONFlag == 0) && (status1.bits.psfbFeedback == 1)   && (status1.bits.sHealthStatus == 0) )
		{
			turnOn();
		}
		else if ((cmd.bits.system_on == 0 && TurnONFlag == 1 )  || (status1.bits.sHealthStatus != 0)  || ( (status1.bits.psfbFeedback == 1) && (cmd.bits.psfb_on == 0) )  )
		{
			turnOff();
		}
		else
		{
			//NOP;
		}
	}

//	g_reset_switch = GET_RESET_SWITCH;
    if (g_reset_switch ==0)        //fault reset through hardware switch for testing purpose
    {
        fault_det++;
    	cmd.bits.fault_reset=1;
    	LED2_OFF;
    }
}

void turnOn()
{
	TurnONFlag=1;
	if(cmd.bits.afe_pwm_mask == 1){
		PWMON();
	}
}

void turnOff()
{
	cmd.bits.system_on = 0;
	TurnONFlag = 0;
	PWMOFF();
	PSFBOFF();
}
