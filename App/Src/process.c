/*
 * process.c
 *
 *  Created on: Oct 17, 2024
 *      Author: SavanSutariya
 */

#include "main.h"
#include "hrtim.h"
#include "tim.h"
#include "process.h"

uint8_t test_mode_count=0;
uint32_t timer_period;

float mod_index = 0.7;
float V_cmd = 4250.0;
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

void ControlInit(void)
{

	TIM7->PSC = 0; //Timer 7
	TIM7->ARR = (uint16_t)(SystemCoreClock/((1+TIM7->PSC)*(5000))) - 1;

	HAL_TIM_Base_Start_IT(&htim7);

	HAL_HRTIM_WaveformCounterStart(&hhrtim1, HRTIM_TIMERID_TIMER_A + HRTIM_TIMERID_TIMER_B + HRTIM_TIMERID_TIMER_C + HRTIM_TIMERID_TIMER_D ); //Timer A,B,C and D of HRTIM1 counter start

	HAL_HRTIM_WaveformOutputStart(&hhrtim1, HRTIM_OUTPUT_TA1 | HRTIM_OUTPUT_TA2 | HRTIM_OUTPUT_TB1 | HRTIM_OUTPUT_TB2 ); //Timer A and B for AFE PWM

}
/*
* Function Description: Function to start PSFB output waveform
* Input:
* Return:
*/
void PSFBON(void)
{
	HAL_HRTIM_WaveformCounterStart(&hhrtim1,HRTIM_TIMERID_TIMER_C + HRTIM_TIMERID_TIMER_D);
	HRTIM1->sTimerxRegs[HRTIM_TIMERINDEX_TIMER_C].CNTxR=500;
	HRTIM1->sTimerxRegs[HRTIM_TIMERINDEX_TIMER_D].CNTxR=500;
	HAL_HRTIM_WaveformOutputStart(&hhrtim1, HRTIM_OUTPUT_TC1 | HRTIM_OUTPUT_TC2 | HRTIM_OUTPUT_TD1 | HRTIM_OUTPUT_TD2 ); //Timer C and D for PSFB
}


/*
* Function Description: Function to stop PSFB output waveform
* Input:
* Return:
*/
void PSFBOFF(void)
{
	HAL_HRTIM_WaveformOutputStop(&hhrtim1, HRTIM_OUTPUT_TC1 | HRTIM_OUTPUT_TC2 | HRTIM_OUTPUT_TD1 | HRTIM_OUTPUT_TD2 );

	HRTIM1->sTimerxRegs[HRTIM_TIMERINDEX_TIMER_C].CNTxR=0;
	HRTIM1->sTimerxRegs[HRTIM_TIMERINDEX_TIMER_D].CNTxR=0;

}
void Tim7_Execution(void)
{
	test_mode_count++;
	if(test_mode_count>=100)
	{
		test_mode_count =0;
	}

	timer_period = HRTIM1->sTimerxRegs[HRTIM_TIMERINDEX_TIMER_B].PERxR;

	V_cmd = (R_sine_wave[test_mode_count]* mod_index + 1) * (timer_period/2);
	//HAL_DAC_SetValue(&hdac1, DAC_CHANNEL_1, DAC_ALIGN_12B_R, V_cmd*0.1);

	HRTIM1->sTimerxRegs[HRTIM_TIMERINDEX_TIMER_A].CMP3xR = V_cmd;
	HRTIM1->sTimerxRegs[HRTIM_TIMERINDEX_TIMER_B].CMP3xR = V_cmd;

}
