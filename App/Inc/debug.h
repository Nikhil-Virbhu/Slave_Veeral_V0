/*File description: DAC debug header file.This header file contains definition of variables and functions which are used for DAC debugging.
 *Functions used:
 *Reference document:
 */
#include "main.h"
#include "dac.h"

#define SERIAL_DEBUG_ENABLE 0 	//make this 1 to keep the serial debug messages
								//make this 0 to disable the serial debug messages

#define TOTAL_DAC_SIGNALS 3 //3 AC quantities for DAC (Isup, Vsup and Iac)
#define RX_DATA_BUFF 200
#define TX_DATA_BUFF 200

enum DAC_Output_Quantity{dac_vsup,dac_isup,dac_iafe};

#ifdef _DEBUG_H_
	uint8_t dac1 , dac2 ; //DAC Variables
	float DAC_Value[TOTAL_DAC_SIGNALS];
	uint8_t RxData[RX_DATA_BUFF]; //UART Receive buffer
	uint8_t TxData[TX_DATA_BUFF]; //UART Transmit buffer

	void DAC_Out(void);
	uint32_t DAC_Update(uint8_t signal);

#else
	extern uint8_t dac1, dac2; //DAC Variables
	extern float DAC_Value[TOTAL_DAC_SIGNALS];
	extern uint8_t RxData[RX_DATA_BUFF]; //UART Receive buffer
	extern uint8_t TxData[TX_DATA_BUFF]; //UART Transmit buffer

	extern void DAC_Out(void);
	extern uint32_t DAC_Update(uint8_t signal);
#endif
