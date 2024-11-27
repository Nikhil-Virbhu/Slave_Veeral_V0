#include"main.h"

typedef struct{
	float Dynamic;
	float Fix;
}softStart_Structure;

#ifdef _SOFT_START_

	softStart_Structure phase_diff;
	void softStartVariable(softStart_Structure *Temp, float sampleFreq, float Positive_SlwRate, float Negative_SlwRate);

#else

	extern softStart_Structure phase_diff;
	extern void softStartVariable(softStart_Structure *Temp, float sampleFreq, float Positive_SlwRate, float Negative_SlwRate);

#endif
