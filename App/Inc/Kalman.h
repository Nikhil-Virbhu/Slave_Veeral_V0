/* File description: Kalman filter structures and variables definition
 * Functions used:
 * Reference document:
*/
#include "main.h"

/* 
Example of Using Kalman:

float Ia_Kalman, K_Temp_Ia[10];
float * kptr_a = &K_Temp_Ia[0];
K_Temp_Ia[9]=yn_Ia;
K_Temp_Ia[0]=(float)1/(F_Timer2);
K_Temp_Ia[2]=(float)2*PI*SupFreq;//2*PI*50;
kptr_a = Kalman_Filter(K_Temp_Ia,0.01f, 0, 0, 0.01f, 7.2f); //	K_Temp_Ia
Ia_Kalman=K_Temp_Ia[9];

*/
#define two_PI (float)6.28f

typedef struct{
	float n; // number of sample
	float P2[4]; // power matrix
	float X2[2]; // variable Matrix
	float InOut;
}Kalman_Structure;

#ifdef _Kalman_
  	Kalman_Structure *PtrKalman;
  	Kalman_Structure Iafe_Klmn, Vsup_Klmn, Isup_Klmn; // kalman filter variables
    float *Kalman_Filter(float*, float, float, float, float, float);
    Kalman_Structure *Kalman_Filter1(Kalman_Structure *k_temp, float Sample_Freq, float Wn, float Q1, float Q2, float Q3, float Q4, float R1);

#else
    extern float *Kalman_Filter(float*, float, float, float, float, float);
    extern Kalman_Structure *Kalman_Filter1(Kalman_Structure *k_temp, float Sample_Freq, float Wn, float Q1, float Q2, float Q3, float Q4, float R1);
    extern Kalman_Structure *PtrKalman;
    extern Kalman_Structure Iafe_Klmn, Vsup_Klmn, Isup_Klmn; // kalman filter variables

#endif
