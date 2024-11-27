/*
 * io.c
 *
 *  Created on: 25-Apr-2023
 *      Author: hp
 */
#define _IO_
#include "io.h"
#include "main.h"
#include "debug.h"
#include "process.h"
#include "protection.h"

uint32_t switch_stable;
uint8_t switch_change_flag;
uint8_t switch_state[5];
uint32_t new_stable;
uint8_t ss1 = 0,ss2 = 0;

/*
* Function Description: This function will check if the input remained high or low for a defined state of time. If it is stable for given time then only it is considered low or high.
* debounce time is settable by increasing the size of the array.
* Input: NONE
* Output: NONE
*/
void checkDebounce(void)
{
	uint8_t temp1,temp2;
	static uint8_t sw_state_ptr;
	static uint32_t stayed_high;
	static uint32_t stayed_low;
	static uint32_t switch_changes;


	temp1 = (uint8_t)(HAL_GPIO_ReadPin(DI1_GPIO_Port,DI1_Pin));
	temp2 = ((uint8_t)(HAL_GPIO_ReadPin(DI2_GPIO_Port,DI2_Pin)))<<1;

    //debounce inputs
    switch_state[sw_state_ptr] = temp1 | temp2 ;
    sw_state_ptr++;
    if (sw_state_ptr == 5)
    	sw_state_ptr = 0;

    stayed_high = switch_state[0] & switch_state[1] & switch_state[2] & switch_state[3] & switch_state[4];
    stayed_low = !switch_state[0] & !switch_state[1] & !switch_state[2] & !switch_state[3] & !switch_state[4];

    new_stable = (stayed_high | stayed_low);
    switch_changes = (new_stable ^ switch_stable); //switch changes, switch_stable are globals

    if(switch_changes > 0){
      switch_change_flag = 1; //set a flag to allow processing outside the interrupt (global scope)
      switch_stable = new_stable; //save new stable sta&te
    }

}

/* Function description: Function to read pin state of the digital input
 */
uint8_t getDigiIn(void)
{
/*	checkDebounce();
	if (switch_change_flag == 1){
		switch_change_flag = 0;
	}
	//psfb button
	if((HAL_GPIO_ReadPin(DI1_GPIO_Port,DI1_Pin) == 1)){
		if(ss1== 0){
			PSFBON();
			ss1 = 1;
		}
	}else{
		if(ss1== 1){
			PSFBOFF();
			ss1 = 0;
		}
	}

	//Afe button
	if ((HAL_GPIO_ReadPin(DI2_GPIO_Port,DI2_Pin) == 1)){
		if(ss2== 0){
			PWMON();
			ss2 = 1;
		}
	}else{
		if(ss2== 1){
			PWMOFF();
			ss2 = 0;
		}
	}*/

	// function not in use anymore
	return 0;
}
//	switch(index){
//		  case IN1: //Start push button
//			return (GPIO_PinState)(switch_stable & 0x1);  //Read digital Input
//			break;
//		  case IN2: // Stop push button
//			return (GPIO_PinState)((switch_stable & 0x2)>>1);
//			break;
//		  default:
//		  	return 0;
//	}

/* Function description: Function to set pin state of the digital output
 */

void setDigiOut(digiOut digiOutput, GPIO_PinState state )
{
	switch(digiOutput){
		case OUT1:
		  HAL_GPIO_WritePin(DO1_GPIO_Port,DO1_Pin,state);  //Write digital Output
		  break;

		case OUT2:
		  HAL_GPIO_WritePin(DO2_GPIO_Port,DO2_Pin,state);
		  break;

		default:
		  break;
	}

}
