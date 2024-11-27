/* File description: This file contains definitions of functions and variables used for processing.(Core algorithm as well as low priority tasks).
*Functions used:
 *Reference document:
*/

#include"main.h"
#include "adc.h"
#include "tim.h"
#include "dac.h"
#include "syspara.h"
#include <math.h>

#define TWO_PI 6.28f

#define AV_REF (float)3.3f
#define ADC_COUNT (float)4096.0f
#define ADC_RESOLUTION (float)0.00080566f

#define AC_VOLTAGE_GAIN 8000.0f
#define AC_CURRENT_GAIN 20.0f
#define OUTPUT_VOLTAGE_GAIN 1500.0f
#define OUTPUT_CURRENT_GAIN 15.0f
#define CURRENT_FACTOR 1.55f

enum arrayValue{rawValue, procValue,kalmanValue};

#ifdef _PROCESS_
    configParameters ConfigPara;
    float VphBase,IphBase,VoutBase,IoutBase;
    unsigned char mSec1_Flag, mSec40_Flag, Sec1_Flag, mSec100_Flag;
    unsigned int CNT_TIM6;
	float V_cmd = 4250.0;
	float Vsup[3],Isup[3],Iafe[3]; // AC quantities
	float Ipsfb[2],Vout[2],Vbus[2],Iout[2]; //DC quantities
	float TDiode_Res[2],TTrafo_Res[2],TAfe_Res[2],TPsfb_Res[2]; //Temperature channel quantities (dc)
	float TTrafo_calc,TTrafo_meas;
	float TDiode, TTrafo, TAfe, TPsfb;
	float resistance;
	float Vsuprms, Isuprms,IafeRms;
	float iafe_rms_buffer, vsup_rms_buffer, isup_rms_buffer;

	/* CAN parameters for sending and receiving*/
	int8_t flag_transition = 0;
	uint16_t DutyRef_R,DutyRef_Y,DutyRef_B;
	uint8_t Gate_Command_Pulse;
	uint8_t convStateRecFlag;
	uint8_t Psfb_Command_Pulse, Psfb_OnOffFlag, Psfb_Feedback = 0;
    float Ma=0.5;
    uint16_t TIM1_CCR1, TIM1_CCR2;
    float innerFreq=5000.0f;
    float sinFreq=50.0f;
    unsigned int n_spwm;
//    float V_OUT[2],I_OUT[2];
//    float V_OUT_LPF[2],I_OUT_LPF[2];
    uint8_t TurnONFlag, SoftStartFlag=0;
    uint32_t DAC_value1;
    uint32_t DAC_value2;

	void ControlInit(void);
	void Parameter_Calculations(void);
	void parameterCalculations_ADC1(void);
	void parameterCalculations_ADC2(void);
	void parameterCalculations_ADC3(void);
	void parameterCalculations_ADC4(void);
	void TIM6_Execution(void);
	void Tim7_Execution(void);
	void Tim1_Execution(void);
	void startPWM(void);
	void stopPWM(void);
	void calculateRMS(unsigned int SamplingFreq, unsigned int Fsystem);
	void parameter_calculations(void);
	void PSFBOFF(void);
	void PSFBON(void);
	void PWMON(void);
	void PWMOFF(void);
	void turnOn_Scan(void);
	void ParaInit(void);
	void protectionMonitoring_DC(void);
	void protectionMonitoring_Temp(void);
	void protectionMonitoring_AC(void);
	void turnOn(void);
	void turnOff(void);
	void phaseShift_Pwm(void);
	void dutyUpdate(void);


#else
    extern configParameters ConfigPara;
    extern float VphBase,IphBase,VoutBase,IoutBase;
    extern unsigned char mSec1_Flag, mSec40_Flag, Sec1_Flag, mSec100_Flag;
	extern float V_cmd;
	extern float Vsup[3],Isup[3],Iafe[3]; // AC quantities
	extern float Ipsfb[2],Vout[2],Vbus[2],Iout[2]; //DC quantities
	extern float TDiode_Res[2],TTrafo_Res[2],TAfe_Res[2],TPsfb_Res[2]; //Temperature channel quantities (dc)
	extern float TTrafo_calc,TTrafo_meas;
	extern float TDiode, TTrafo, TAfe, TPsfb;
	extern float resistance;
	extern float Vsuprms, Isuprms,IafeRms;
	extern float iafe_rms_buffer, vsup_rms_buffer, isup_rms_buffer;
	extern float VrefADC;
	extern float Ma;
	extern uint16_t TIM1_CCR1, TIM1_CCR2;
//	extern float V_OUT[2],I_OUT[2];
//	extern float V_OUT_LPF[2],I_OUT_LPF[2];
	extern float innerFreq;
	extern float sinFreq;

	/* CAN parameters for sending and receiving*/
	extern int8_t flag_transition;
	extern uint8_t convPrevFlagState;
	extern uint16_t DutyRef_R,DutyRef_Y,DutyRef_B;
	extern uint8_t convStateRecFlag;
	extern uint8_t Psfb_Command_Pulse, Gate_Command_Pulse, Psfb_OnOffFlag, Psfb_Feedback;
	extern unsigned int n_spwm;
	extern uint32_t DAC_value1;
	extern uint32_t DAC_value2;
	extern void ControlInit(void);
	extern void Parameter_Calculations(void);
	extern void parameterCalculations_ADC1(void);
	extern void parameterCalculations_ADC2(void);
	extern void parameterCalculations_ADC3(void);
	extern void parameterCalculations_ADC4(void);
	extern void TIM6_Execution(void);
	extern void Tim7_Execution(void);
	extern void Tim1_Execution(void);

	extern void startPWM(void);
	extern void stopPWM(void);
	extern void calculateRMS(unsigned int SamplingFreq, unsigned int Fsystem);

	extern void PSFBOFF(void);
	extern void PSFBON(void);
	extern void PWMON(void);
	extern void PWMOFF(void);
	extern void turnOn_Scan(void);
	extern void ParaInit(void);
    extern void protectionMonitoring_DC(void);
    extern void protectionMonitoring_Temp(void);
    extern void protectionMonitoring_AC(void);
    extern void turnOn(void);
    extern void turnOff(void);
    extern void phaseShift_Pwm(void);
    extern void dutyUpdate(void);
#endif
