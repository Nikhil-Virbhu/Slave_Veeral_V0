/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32g4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define SCLK_PC_Pin GPIO_PIN_2
#define SCLK_PC_GPIO_Port GPIOE
#define CS_PC_Pin GPIO_PIN_3
#define CS_PC_GPIO_Port GPIOE
#define DSP_FLTAFE_Pin GPIO_PIN_4
#define DSP_FLTAFE_GPIO_Port GPIOE
#define DSP_FLTAFE_EXTI_IRQn EXTI4_IRQn
#define SDO_PC_Pin GPIO_PIN_5
#define SDO_PC_GPIO_Port GPIOE
#define SDI_PC_Pin GPIO_PIN_6
#define SDI_PC_GPIO_Port GPIOE
#define RESET_DRIVER_Pin GPIO_PIN_13
#define RESET_DRIVER_GPIO_Port GPIOC
#define ERROR_DIODE_Pin GPIO_PIN_9
#define ERROR_DIODE_GPIO_Port GPIOF
#define DSP_FLTPSFB_Pin GPIO_PIN_10
#define DSP_FLTPSFB_GPIO_Port GPIOF
#define DSP_FLTPSFB_EXTI_IRQn EXTI15_10_IRQn
#define DSP_RDYAFE_Pin GPIO_PIN_0
#define DSP_RDYAFE_GPIO_Port GPIOC
#define DSP_RDYPSFB_Pin GPIO_PIN_1
#define DSP_RDYPSFB_GPIO_Port GPIOC
#define ERROR_MASTER_Pin GPIO_PIN_2
#define ERROR_MASTER_GPIO_Port GPIOC
#define ERROR_MASTER_EXTI_IRQn EXTI2_IRQn
#define DSP_PRECHARGEFLT_Pin GPIO_PIN_3
#define DSP_PRECHARGEFLT_GPIO_Port GPIOC
#define DSP_PRECHARGEFLT_EXTI_IRQn EXTI3_IRQn
#define DSP_PRECHARGE_MOSFET_Pin GPIO_PIN_2
#define DSP_PRECHARGE_MOSFET_GPIO_Port GPIOF
#define ZCP_Pin GPIO_PIN_0
#define ZCP_GPIO_Port GPIOA
#define ZCN_Pin GPIO_PIN_1
#define ZCN_GPIO_Port GPIOA
#define DAC1_Pin GPIO_PIN_4
#define DAC1_GPIO_Port GPIOA
#define DAC2_Pin GPIO_PIN_5
#define DAC2_GPIO_Port GPIOA
#define WDI_OP_Pin GPIO_PIN_6
#define WDI_OP_GPIO_Port GPIOA
#define SPARE_PC_Pin GPIO_PIN_7
#define SPARE_PC_GPIO_Port GPIOA
#define ID6_Pin GPIO_PIN_4
#define ID6_GPIO_Port GPIOC
#define DO1_Pin GPIO_PIN_13
#define DO1_GPIO_Port GPIOE
#define DO2_Pin GPIO_PIN_14
#define DO2_GPIO_Port GPIOE
#define ID3_Pin GPIO_PIN_15
#define ID3_GPIO_Port GPIOE
#define ID4_Pin GPIO_PIN_10
#define ID4_GPIO_Port GPIOB
#define PSFBH1_Pin GPIO_PIN_12
#define PSFBH1_GPIO_Port GPIOB
#define PSFBL1_Pin GPIO_PIN_13
#define PSFBL1_GPIO_Port GPIOB
#define PSFBH2_Pin GPIO_PIN_14
#define PSFBH2_GPIO_Port GPIOB
#define PSFBL2_Pin GPIO_PIN_15
#define PSFBL2_GPIO_Port GPIOB
#define SP_OP3_Pin GPIO_PIN_9
#define SP_OP3_GPIO_Port GPIOD
#define SP_OP2_Pin GPIO_PIN_10
#define SP_OP2_GPIO_Port GPIOD
#define SP_OP1_Pin GPIO_PIN_11
#define SP_OP1_GPIO_Port GPIOD
#define SP_IN3_Pin GPIO_PIN_13
#define SP_IN3_GPIO_Port GPIOD
#define SP_IN2_Pin GPIO_PIN_14
#define SP_IN2_GPIO_Port GPIOD
#define SP_IN1_Pin GPIO_PIN_15
#define SP_IN1_GPIO_Port GPIOD
#define SCL_Pin GPIO_PIN_6
#define SCL_GPIO_Port GPIOC
#define SDA_Pin GPIO_PIN_7
#define SDA_GPIO_Port GPIOC
#define DI1_Pin GPIO_PIN_8
#define DI1_GPIO_Port GPIOC
#define DI2_Pin GPIO_PIN_9
#define DI2_GPIO_Port GPIOC
#define AFEH1_Pin GPIO_PIN_8
#define AFEH1_GPIO_Port GPIOA
#define AFEL1_Pin GPIO_PIN_9
#define AFEL1_GPIO_Port GPIOA
#define AFEH2_Pin GPIO_PIN_10
#define AFEH2_GPIO_Port GPIOA
#define AFEL2_Pin GPIO_PIN_11
#define AFEL2_GPIO_Port GPIOA
#define ID5_Pin GPIO_PIN_12
#define ID5_GPIO_Port GPIOA
#define TXD_M_Pin GPIO_PIN_10
#define TXD_M_GPIO_Port GPIOC
#define RXD_M_Pin GPIO_PIN_11
#define RXD_M_GPIO_Port GPIOC
#define TXD_D_Pin GPIO_PIN_12
#define TXD_D_GPIO_Port GPIOC
#define SW1_Pin GPIO_PIN_0
#define SW1_GPIO_Port GPIOD
#define RXD_D_Pin GPIO_PIN_2
#define RXD_D_GPIO_Port GPIOD
#define SW2_Pin GPIO_PIN_3
#define SW2_GPIO_Port GPIOD
#define SW3_Pin GPIO_PIN_4
#define SW3_GPIO_Port GPIOD
#define SW4_Pin GPIO_PIN_5
#define SW4_GPIO_Port GPIOD
#define SW5_Pin GPIO_PIN_6
#define SW5_GPIO_Port GPIOD
#define SW6_Pin GPIO_PIN_7
#define SW6_GPIO_Port GPIOD
#define ID0_Pin GPIO_PIN_3
#define ID0_GPIO_Port GPIOB
#define ID1_Pin GPIO_PIN_4
#define ID1_GPIO_Port GPIOB
#define ID2_Pin GPIO_PIN_5
#define ID2_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
