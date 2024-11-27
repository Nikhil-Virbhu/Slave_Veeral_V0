/*
 * measurement.c
 * File description: ADC parameter calculations

 * 	Adc_Avg_Buffer[0];   //PA0 -> Vbus ADC1 channel 1
	Adc_Avg_Buffer[1];   //PA1 -> Iafe  ADC1 channel 2
	Adc_Avg_Buffer[2];   //PA2 -> Ipsfb ADC1 channel 3
	Adc_Avg_Buffer[3];   //PA3 -> Vout ADC1 channel 4
	Adc_Avg_Buffer[4];   //PA6 -> I-out ADC2 channel 3
	Adc_Avg_Buffer[5];   //PA7 -> Vsup ADC2 channel 4
	Adc_Avg_Buffer[6];   //PC4 -> Isup ADC2 channel 5
	Adc_Avg_Buffer[7];   //PC5 -> Tpsfb ADC2 channel 11
	Adc_Avg_Buffer[8];   //PB1 -> Tafe ADC3 channel 1
	Adc_Avg_Buffer[9];   //PB0 -> Tdiode ADC3 channel 12
	Adc_Avg_Buffer[10];   //PD14 -> Ttrafo ADC4 channel 12

 *  Created on: 26-Apr-2023
 *      Author: hp
 */

#define _MEASUREMENT_
#include "main.h"
#include "measurment.h"

/*
* Function Description: Function to calculate Average of ADC1 Parameters
* Input:
* Return:
*/
void parameterCalculations_ADC1(void)
{
	Adc_Sum_Buffer[VBUS]=0,Adc_Sum_Buffer[IAFE]=0, Adc_Sum_Buffer[IPSFB]=0, Adc_Sum_Buffer[VOUT]=0;

	for(int i=0;i<ADC_SAMPLE_SIZE;i++)
	{
		Adc_Sum_Buffer[VBUS] += Adc1_Buffer[i*ADC1_CHN + 0];
		//Adc_Sum_Buffer[IAFE] += Adc1_Buffer[i*ADC1_CHN + 1];		//This section is not mounted in slave PCB
		Adc_Sum_Buffer[IPSFB] += Adc1_Buffer[i*ADC1_CHN + 2];
	//	Adc_Sum_Buffer[VOUT] += Adc1_Buffer[i*ADC1_CHN + 3];		//This section is not mounted in slave PCB
	}
	Adc_Avg_Buffer[VBUS] = Adc_Sum_Buffer[VBUS]/ADC_SAMPLE_SIZE;
	//Adc_Avg_Buffer[IAFE] = Adc_Sum_Buffer[IAFE]/ADC_SAMPLE_SIZE;	//This section is not mounted in slave PCB
	Adc_Avg_Buffer[IPSFB] = Adc_Sum_Buffer[IPSFB]/ADC_SAMPLE_SIZE;
	//Adc_Avg_Buffer[VOUT] = Adc_Sum_Buffer[VOUT]/ADC_SAMPLE_SIZE;	//This section is not mounted in slave PCB
}

/*
* Function Description: Function to calculate Average of ADC2 Parameters
* Input:
* Return:
*/
void parameterCalculations_ADC2(void)
{
	Adc_Sum_Buffer[IOUT]=0,Adc_Sum_Buffer[VSUP]=0,Adc_Sum_Buffer[ISUP]=0,Adc_Sum_Buffer[TPSFB]=0;

	for(int i=0;i<ADC_SAMPLE_SIZE;i++){
		Adc_Sum_Buffer[IOUT] += Adc2_Buffer[i*ADC2_CHN + 0];
	//	Adc_Sum_Buffer[VSUP] += Adc2_Buffer[i*ADC2_CHN + 1];	//This section is not mounted in slave PCB
	//	Adc_Sum_Buffer[ISUP] += Adc2_Buffer[i*ADC2_CHN + 2];		//This section is not mounted in slave PCB
		Adc_Sum_Buffer[TPSFB] += Adc2_Buffer[i*ADC2_CHN + 3];
	}
	Adc_Avg_Buffer[IOUT] = Adc_Sum_Buffer[IOUT]/ADC_SAMPLE_SIZE;
	//Adc_Avg_Buffer[VSUP] = Adc_Sum_Buffer[VSUP]/ADC_SAMPLE_SIZE;	//This section is not mounted in slave PCB
	//Adc_Avg_Buffer[ISUP] = Adc_Sum_Buffer[ISUP]/ADC_SAMPLE_SIZE;	//This section is not mounted in slave PCB
	Adc_Avg_Buffer[TPSFB] = Adc_Sum_Buffer[TPSFB]/ADC_SAMPLE_SIZE;
}

/*
* Function Description: Function to calculate Average of ADC3 Parameters
* Input:
* Return:
*/
void parameterCalculations_ADC3(void)
{
	Adc_Sum_Buffer[TAFE]=0,Adc_Sum_Buffer[TDIODE]=0;

	for(int i=0;i<ADC_SAMPLE_SIZE;i++){
		Adc_Sum_Buffer[TAFE] += Adc3_Buffer[i*ADC3_CHN + 0];
		Adc_Sum_Buffer[TDIODE] += Adc3_Buffer[i*ADC3_CHN + 1];
	}
	Adc_Avg_Buffer[TAFE] = Adc_Sum_Buffer[TAFE]/ADC_SAMPLE_SIZE;
	Adc_Avg_Buffer[TDIODE] = Adc_Sum_Buffer[TDIODE]/ADC_SAMPLE_SIZE;
}

/*
* Function Description: Function to calculate Average of ADC4 Parameters
* Input:
* Return:
*/
void parameterCalculations_ADC4(void)
{
	Adc_Sum_Buffer[TTRAFO]=0;

	for(int i=0;i<ADC_SAMPLE_SIZE;i++)
		Adc_Sum_Buffer[TTRAFO] += Adc4_Buffer[i*ADC4_CHN + 0];

	Adc_Avg_Buffer[TTRAFO] = Adc_Sum_Buffer[TTRAFO]/ADC_SAMPLE_SIZE;
}
