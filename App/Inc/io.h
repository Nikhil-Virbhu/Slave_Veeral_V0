/* File description: Digital Input/ output header file. This file contains the structures and function definition related to Digital input and output.
*Functions used:
 *Reference document:
*/

#include "main.h"

typedef enum{
	IN1 = 0U,
	IN2,
}digiIn;

typedef enum{
	OUT1,
	OUT2,
}digiOut;

#ifdef _IO_
	uint8_t getDigiIn(void);
	void checkDebounce(void);
	void setDigiOut(digiOut digiOutput, GPIO_PinState state);
#else
	extern uint8_t getDigiIn(void);
	extern void checkDebounce(void);
	extern void setDigiOut(digiOut digiOutput, GPIO_PinState state);
#endif
