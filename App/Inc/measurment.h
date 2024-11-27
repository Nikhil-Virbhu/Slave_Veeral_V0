/* File description: Measurement of voltage and current parameters from the grid. (total 12 ADC sensing parameters
 *  File description: ADC parameter calculations
 *  Adc_Avg_Buffer[0];   //PA0 -> Vbus ADC1 channel 1
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
	We have used 4 adcs for sensing
*/
#include "main.h"

#define ADC_SAMPLE_SIZE 4

#define ADC1_CHN 4
#define ADC1_BUFFER_SIZE ADC1_CHN*ADC_SAMPLE_SIZE

#define ADC2_CHN 4
#define ADC2_BUFFER_SIZE ADC2_CHN*ADC_SAMPLE_SIZE

#define ADC3_CHN 2
#define ADC3_BUFFER_SIZE ADC3_CHN*ADC_SAMPLE_SIZE

#define ADC4_CHN 1
#define ADC4_BUFFER_SIZE ADC4_CHN*ADC_SAMPLE_SIZE

#define TOTAL_ADC_PARAMETERS 11

typedef enum {VBUS,IAFE,IPSFB,VOUT,IOUT,VSUP,ISUP,TPSFB,TAFE,TDIODE,TTRAFO} ADCmeasurement;

#ifdef _MEASUREMENT_

	uint16_t Adc1_Buffer[ADC1_BUFFER_SIZE];
	uint16_t Adc2_Buffer[ADC2_BUFFER_SIZE];
	uint16_t Adc3_Buffer[ADC3_BUFFER_SIZE];
	uint16_t Adc4_Buffer[ADC4_BUFFER_SIZE];

	uint32_t Adc_Sum_Buffer[TOTAL_ADC_PARAMETERS];
	uint32_t Adc_Avg_Buffer[TOTAL_ADC_PARAMETERS];

//	void parameterCalculations_ADC1(void);
//	void parameterCalculations_ADC2(void);
//	void parameterCalculations_ADC3(void);
//	void parameterCalculations_ADC4(void);


#else

	extern uint16_t Adc1_Buffer[ADC1_BUFFER_SIZE];
	extern uint16_t Adc2_Buffer[ADC2_BUFFER_SIZE];
	extern uint16_t Adc3_Buffer[ADC3_BUFFER_SIZE];
	extern uint32_t Adc4_Buffer[ADC4_BUFFER_SIZE];

	extern uint32_t Adc_Sum_Buffer[TOTAL_ADC_PARAMETERS];
	extern uint32_t Adc_Avg_Buffer[TOTAL_ADC_PARAMETERS];

//	extern void parameterCalculations_ADC2(void);
//	extern void parameterCalculations_ADC3(void);
//	extern void parameterCalculations_ADC4(void);

#endif
