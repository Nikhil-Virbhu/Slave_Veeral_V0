#define _SOFT_START_
#include "soft_start.h"

/*
* Function Description: To give soft start to variables
* Input:
* Return:
*/
void softStartVariable(softStart_Structure *Temp, float sampleFreq, float Positive_SlwRate, float Negative_SlwRate){
	float positiveStepSize = (float)Positive_SlwRate/sampleFreq;
	float negativeStepSize = (float)Negative_SlwRate/sampleFreq;

	if(Temp -> Dynamic <= (Temp -> Fix - positiveStepSize*2.0f)){
		Temp -> Dynamic = Temp -> Dynamic + positiveStepSize;
	}else if(Temp -> Dynamic >= (Temp -> Fix + negativeStepSize*2.0f)){
	Temp -> Dynamic = Temp -> Dynamic - negativeStepSize;
 }else {
	Temp -> Dynamic = Temp -> Fix;
 }
}
