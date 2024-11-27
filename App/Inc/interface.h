/*
 * interface.h
 *
 *  Created on: Nov 7, 2023
 *      Author: EngTest05
 *
 *      Description: This file will have all possible interfaces to the MCU hardwares which are needed by APP.
 *      We are doing this so the MCU call in APP can be reduced and strictlly defined.
 *
 *      By following this method we want to achieve an interface layer between the MCU and APP
 */

#ifndef INC_INTERFACE_H_
#define INC_INTERFACE_H_

//#define GET_AFE_SWITCH 			(HAL_GPIO_ReadPin(AFE_Switch_GPIO_Port,AFE_Switch_Pin))
//#define GET_PSFB_SWITCH 			(HAL_GPIO_ReadPin(PSFB_Switch_GPIO_Port,PSFB_Switch_Pin))
//#define GET_CELL_TEST_SWITCH (HAL_GPIO_ReadPin(CELL_TEST_Switch_GPIO_Port,CELL_TEST_Switch_Pin))
//#define GET_RESET_SWITCH		(HAL_GPIO_ReadPin(HW_fault_reset_GPIO_Port,HW_fault_reset_Pin))


#define LED1_ON 							(HAL_GPIO_WritePin(ID2_GPIO_Port,ID2_Pin,1))
#define LED1_OFF 						(HAL_GPIO_WritePin(ID2_GPIO_Port,ID2_Pin,0))

#define LED2_ON							(HAL_GPIO_WritePin(ID0_GPIO_Port,ID0_Pin,1))
#define LED2_OFF 						(HAL_GPIO_WritePin(ID0_GPIO_Port,ID0_Pin,0))
#define LED2_TOGGLE					(HAL_GPIO_TogglePin(ID0_GPIO_Port,ID0_Pin))

#define LED3_ON 							(HAL_GPIO_WritePin(ID1_GPIO_Port,ID1_Pin,1))
#define LED3_OFF 						(HAL_GPIO_WritePin(ID1_GPIO_Port,ID1_Pin,0))

//#define MCU_LIVE_ON					(HAL_GPIO_WritePin(MCU_live_GPIO_Port,MCU_live_Pin,1))
//#define MCU_LIVE_OFF					(HAL_GPIO_WritePin(MCU_live_GPIO_Port,MCU_live_Pin,0))
#endif /* INC_INTERFACE_H_ */
