#define _Kalman_

#include "Kalman.h"
#include "arm_math.h"

/* Kalman Setup -----------------------------------------------------------
K_temp[10] variables: [0,1,2,3,4,5,6,7,8,9]
0-Ts_K  (kalman sample time)
1- n_K (sample number)
2- w_K
3-	P2[0]
4- P2[1]
5- P2[2]
6- P2[3]
7-	X2[0]
8-X2[1]
9- S1
*/
/*File description: Kalman filter functions
 *Functions used:
 *Reference document:
 */

/*Function description:  */
Kalman_Structure *Kalman_Filter1(Kalman_Structure *k_temp, float Sample_Freq, float Wn, float Q1, float Q2, float Q3, float Q4, float R1)
{
	float C[2], angle_K, P1[4], KnX, K[2], Jsc, X1[2],Ts_K; //R1=7.20f, Q[4]={0.01f, 0, 0, 0.01f}
	Ts_K = (float) 1/Sample_Freq;
	angle_K = (float)Wn*k_temp -> n*Ts_K;
	C[0] = (float)arm_cos_f32(angle_K);
	C[1] = (float)-arm_sin_f32(angle_K);

	P1[0] = k_temp->P2[0] + Q1; // Eq 1
	P1[1] = k_temp->P2[1] + Q2; // Eq 1
	P1[2] = k_temp->P2[2] + Q3; // Eq 1
	P1[3] = k_temp->P2[3] + Q4; // Eq 1

	KnX = (float)((C[0]*(C[0]*P1[0]+C[1]*P1[2]))+ (C[1]*(C[0]*P1[1]+C[1]*P1[3])))+ R1; //	Equ 2
	KnX = (float)1/KnX; //Equ 2
	K[0] = (float)(P1[0]*C[0]+P1[1]*C[1])*KnX; //	Equ 2
	K[1] = (float)(P1[2]*C[0]+P1[3]*C[1])*KnX; //	Equ 2
	
	//Jsc=(k_temp[9]- (C[0]*k_temp[7]+C[1]*k_temp[8])); //Jsc=(S1- (C[0]*X2[0]+C[1]*X2[1])); // Equ 3
	Jsc = (float)(k_temp -> InOut)- ((C[0]*(k_temp -> X2[0]))+ (C[1]*(k_temp -> X2[1]))); //Jsc=(S1- (C[0]*X2[0]+C[1]*X2[1]));
	X1[0] = (float)k_temp -> X2[0]+ (K[0]*Jsc);
	X1[1] = (float)k_temp -> X2[1]+ (K[1]*Jsc);
	
	k_temp -> P2[0]=P1[0]-(K[0]*C[0]*P1[0]+K[0]*C[1]*P1[2]); //P2[0]=P1[0]-(K[0]*C[0]*P1[0]+K[0]*C[1]*P1[2]); // Eq 4
	k_temp -> P2[1]=P1[1]-(K[0]*C[0]*P1[1]+K[0]*C[1]*P1[3]); //P2[1]=P1[1]-(K[0]*C[0]*P1[1]+K[0]*C[1]*P1[3]); // Eq 4
	k_temp -> P2[2]=P1[2]-(K[1]*C[0]*P1[0]+K[1]*C[1]*P1[2]); //P2[2]=P1[2]-(K[1]*C[0]*P1[0]+K[1]*C[1]*P1[2]); // Eq 4
	k_temp -> P2[3]=P1[3]-(K[1]*C[0]*P1[1]+K[1]*C[1]*P1[3]); //P2[3]=P1[3]-(K[1]*C[0]*P1[1]+K[1]*C[1]*P1[3]); // Eq 4
	k_temp -> X2[0]=X1[0];
	k_temp -> X2[1]=X1[1];
	k_temp -> InOut=C[0]*X1[0]+C[1]*X1[1]; // S1=C[0]*X1[0]+C[1]*X1[1];
	
	k_temp -> n = k_temp->n+1.0f;
	if(k_temp -> n >= ((unsigned int)two_PI/((float)Wn*Ts_K)))
	   k_temp -> n=0;
	
	return(k_temp);	
}

/*Function description: Calculates and updates parameters for Kalman filter structure */
float * Kalman_Filter(float *k_temp,float Q1, float Q2, float Q3, float Q4, float R1)
{
	float C[2], angle_K, P1[4], KnX, K[2], Jsc, X1[2],Ts_K,n_K,W_K; //R1=7.20f, Q[4]={0.01f, 0, 0, 0.01f}
	Ts_K = *(k_temp+0);
	n_K = *(k_temp+1);
	W_K = *(k_temp+2);
	angle_K = (float)W_K*n_K*Ts_K;
	C[0] = (float)arm_cos_f32(angle_K);
	C[1] = (float)-arm_sin_f32(angle_K);

	P1[0] = *(k_temp+3)+Q1; //P1[0]=P2[0]+Q[0]; // Eq 1
	P1[1] = *(k_temp+4)+Q2; // Eq 1
	P1[2] = *(k_temp+5)+Q3; // Eq 1
	P1[3] = *(k_temp+6)+Q4; // Eq 1

	KnX = (float)((C[0]*(C[0]*P1[0]+C[1]*P1[2]))+ (C[1]*(C[0]*P1[1]+C[1]*P1[3])))+ R1; //	Equ 2
	KnX = (float)1/KnX; //Equ 2
	K[0] = (float)(P1[0]*C[0]+P1[1]*C[1])*KnX; //	Equ 2
	K[1] = (float)(P1[2]*C[0]+P1[3]*C[1])*KnX; //	Equ 2

	//	Jsc=(k_temp[9]- (C[0]*k_temp[7]+C[1]*k_temp[8])); //Jsc=(S1- (C[0]*X2[0]+C[1]*X2[1])); // Equ 3
	Jsc = (float)(*(k_temp+9))- ((C[0]*(*(k_temp+7)))+ (C[1]*(*(k_temp+8)))); //Jsc=(S1- (C[0]*X2[0]+C[1]*X2[1]));
	X1[0] = (float)*(k_temp+7)+ (K[0]*Jsc);
	X1[1] = (float)*(k_temp+8)+ (K[1]*Jsc);

	*(k_temp + 3) = P1[0]-(K[0]*C[0]*P1[0]+K[0]*C[1]*P1[2]); //P2[0]=P1[0]-(K[0]*C[0]*P1[0]+K[0]*C[1]*P1[2]); // Eq 4
	*(k_temp + 4) = P1[1]-(K[0]*C[0]*P1[1]+K[0]*C[1]*P1[3]); //P2[1]=P1[1]-(K[0]*C[0]*P1[1]+K[0]*C[1]*P1[3]); // Eq 4
	*(k_temp + 5) = P1[2]-(K[1]*C[0]*P1[0]+K[1]*C[1]*P1[2]); //P2[2]=P1[2]-(K[1]*C[0]*P1[0]+K[1]*C[1]*P1[2]); // Eq 4
	*(k_temp + 6) = P1[3]-(K[1]*C[0]*P1[1]+K[1]*C[1]*P1[3]); //P2[3]=P1[3]-(K[1]*C[0]*P1[1]+K[1]*C[1]*P1[3]); // Eq 4
	*(k_temp + 7) = X1[0];
	*(k_temp + 8) = X1[1];
	*(k_temp + 9) = C[0]*X1[0]+C[1]*X1[1]; // S1=C[0]*X1[0]+C[1]*X1[1];
	
	n_K = n_K+1.0f;
	if(n_K > ((unsigned int)two_PI/(W_K*Ts_K))){
	   n_K = 0;
	}
	*(k_temp + 1) = n_K;
	return (k_temp);	
}
