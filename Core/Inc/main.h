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
#define PSFBH1_Pin GPIO_PIN_12
#define PSFBH1_GPIO_Port GPIOB
#define PSFBL1_Pin GPIO_PIN_13
#define PSFBL1_GPIO_Port GPIOB
#define PSFBH2_Pin GPIO_PIN_14
#define PSFBH2_GPIO_Port GPIOB
#define PSFBL2_Pin GPIO_PIN_15
#define PSFBL2_GPIO_Port GPIOB
#define AFEH1_Pin GPIO_PIN_8
#define AFEH1_GPIO_Port GPIOA
#define AFEL1_Pin GPIO_PIN_9
#define AFEL1_GPIO_Port GPIOA
#define AFEH2_Pin GPIO_PIN_10
#define AFEH2_GPIO_Port GPIOA
#define AFEL2_Pin GPIO_PIN_11
#define AFEL2_GPIO_Port GPIOA

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
