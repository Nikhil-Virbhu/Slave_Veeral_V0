/*File description: DAC debug and serial debug. This file is used to hold all possible DAC output and serial transmission.
 *Functions:
 *Reference document:
 */


#define _DEBUG_H_

//#define _PROCESS_
#include "debug.h"
#include "process.h"
#include "measurment.h"
//#include "usart.h"
#include "string.h"
#include "stdio.h"
#include "protection.h"

/*
* Function Description: This function calculates the value of DAC signal using offset, gain for different quantities.'Out' will be the output value. Switch cases are used for different quantities.
* Input: NONE
* Output: NONE
*
*/
uint32_t DAC_Update(uint8_t signal)
{
	float out,gain,offset;
	switch(signal)
	{
		case(1):
			offset = 0.0f; //TBD
			gain = VphBase/(ConfigPara.calFactor[IAFE].Gain * ConfigPara.calFactor[IAFE].corFac);
			out = Iafe[procValue] * gain + offset;
		break;
		case(2):
			offset = 0.0f; //TBD
			gain = VphBase/(ConfigPara.calFactor[VSUP].Gain * ConfigPara.calFactor[VSUP].corFac);
			out = Vsup[procValue] * gain + offset;
		break;

		case(3):
			offset = 0.0f; //TBD
			gain = VphBase/(ConfigPara.calFactor[ISUP].Gain * ConfigPara.calFactor[ISUP].corFac);
			out = Isup[procValue] * gain + offset;
		break;

		case(4):
			offset = 0.0f; //TBD
			gain = VphBase/(ConfigPara.calFactor[ISUP].Gain * ConfigPara.calFactor[ISUP].corFac);
			out = DutyRef_R * 1/* gain*/ + offset;
			break;
		case (5):
			out = (uint16_t)status1.bits.sHealthStatus * 3500;
		break;
		case (6):
			out = (uint16_t)V_cmd*0.1;
		break;
		case(7):
			out = (uint16_t)Adc_Avg_Buffer[VBUS];
		break;
		case(8):
		out = (uint16_t)fault3.bits.driver_not_ready * 3500;
		break;
	}
	return (uint32_t) out;
}

/*
* Function Description: DAC_Out to set the value which needs to be observed on DSO using DAC.
* Input: NONE
* Output: NONE
*
*/
void DAC_Out(void)
{

	dac1 = 8;
	dac2 = 5;
	DAC_value1 = (unsigned int) DAC_Update(dac1);
	DAC_value2 = (unsigned int) DAC_Update(dac2);
	HAL_DAC_SetValue(&hdac1, DAC_CHANNEL_1, DAC_ALIGN_12B_R, DAC_value1);
	HAL_DAC_SetValue(&hdac1, DAC_CHANNEL_2, DAC_ALIGN_12B_R, DAC_value2);
}
