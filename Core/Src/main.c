/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "dac.h"
#include "dma.h"
#include "hrtim.h"
#include "i2c.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

#include "process.h"
#include"debug.h"
#include"i2cEeprom.h"
#include "protection.h"
#include "ntc_measurement.h"
#include "io.h"
#include "pcp.h"
//#include "CAN1_Transmitting.h"
//#include "CAN2_Transmitting.h"
//#include "CAN1_Receving.h"
//#include "CAN2_Receving.h"
//#include "Can_Data_Xchange.h"
#include "error_display.h"
//#include "ModbusRTU_Master.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define CONNECT 0x05  // it it for CAN Debug and Connection Indication
#define DISCONNECT 0x00 // it it for CAN Debug and Connection Indication
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
#define FACTORDEVISION 0.1 // It is used in the CAN Protocol

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

//extern uint8_t SUCESS1,FAIL1,SUCESS2,FAIL2,CAN2_Sucess1, CAN2_Sucess2,CAN2_Fail1, CAN2_Fail2;

uint8_t u8temp=1,u8temp1=1,u8MASTER1_STATUS,TXDATA[8],resetFlag=1,u8MASTER1_STATUS_CAN2;
uint16_t u8Slavenumber=0,u8_5mstimer;

extern uint8_t uartRxData;
extern uint16_t ModbusRegister[];
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
uint16_t SlaveBoardNum(void);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_HRTIM1_Init();
  MX_TIM7_Init();
  MX_DAC1_Init();
  MX_I2C4_Init();
  MX_SPI4_Init();
  MX_UART4_Init();
  MX_UART5_Init();
  MX_TIM1_Init();
  MX_TIM4_Init();
  MX_TIM6_Init();
  MX_ADC1_Init();
  /* USER CODE BEGIN 2 */
  para_load();

	// Define ManualSlaveNo for Testing.
#ifdef ManualSlaveNo
	u8Slavenumber=1;
#else
	u8Slavenumber = SlaveBoardNum();
	if(u8Slavenumber == 0 || u8Slavenumber > 39 ){
		fault7.bits.cellAddress_fault = 1;
		add_error_to_list(28);
	}

#endif

//	CAN2_Identification();
//	MX_FDCAN1_Init();
//	MX_FDCAN2_Init();
	ControlInit(); // peripheral Initialization
	turnOff(); // Ensuring the Turning off of AFE and PSFB pulses

	phaseShift_Pwm(); // Phase Shift Selection based on Slave Number Selected.

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
	HAL_UART_Receive_IT(&huart5 , &uartRxData , 1);
	ModbusRegister[0] = 20;
	ModbusRegister[1] = 15;
	ModbusRegister[2] = 20;
	ModbusRegister[3] = 4;
	ModbusRegister[4] = 5;
	ModbusRegister[5] = 6;
	while (1)
	{
		if(cmd.bits.fault_reset == 1){
		//	NVIC_SystemReset();	// System reset
			manual_fault_reset(); // Manual reset of Fault over command from Master

		}

		if (mSec1_Flag==1){
			getDigiIn();

	//			if((FAIL1 !=0) || (FAIL2 != 0))
	//			{
	//				HAL_FDCAN_Stop(&hfdcan1);
	//				u8Slavenumber = SlaveBoardNum();
	//				MX_FDCAN1_Init();
	//				FAIL1=0;
	//				FAIL2=0;
	//			}
	//			else
	//			{
	//			}

	//			if((CAN2_Fail1 !=0) || (CAN2_Fail2 != 0))
	//			{
	//				HAL_FDCAN_Stop(&hfdcan2);
	//				u8Slavenumber = SlaveBoardNum();
	//				MX_FDCAN2_Init();
	//				CAN2_Fail1=0;
	//				CAN2_Fail2=0;
	//			}
	//			else
	//			{
	//			}
			//CAN_DATA_XCHANGING(); // Exchange of Data between the Master and Slave
			mSec1_Flag=0;
		}

		//Task Executed at every 40 mSec
		if (mSec40_Flag==1){

			static uint8_t u8teamlastvalue;
			if(u8MASTER1_STATUS!=u8teamlastvalue)
			{
	//				API_CAN_HEARTBEAT_CELL0139_MASTER01(CONNECT);
			}
			else
			{
	//				API_CAN_HEARTBEAT_CELL0139_MASTER01(DISCONNECT);
			}
			u8teamlastvalue=u8MASTER1_STATUS;

			/*if((FAIL1 !=0) || (FAIL2 != 0))
			{
				HAL_FDCAN_Stop(&hfdcan1);
				u8Slavenumber = SlaveBoardNum();
				MX_FDCAN1_Init();
				FAIL1=0;
				FAIL2=0;
			}
			else
			{

			}*/

			/*CAN2*/
			static uint8_t u8teamlastvalue_CAN2;
			if(u8MASTER1_STATUS_CAN2!=u8teamlastvalue_CAN2)
			{
	//				API_CAN2_HEARTBEAT_CELL0139_MASTER01(CONNECT);
			}
			else
			{
	//				API_CAN2_HEARTBEAT_CELL0139_MASTER01(DISCONNECT);
			}
			u8teamlastvalue_CAN2=u8MASTER1_STATUS_CAN2;

			/*if((CAN2_Fail1 !=0) || (CAN2_Fail2 != 0))
			{
				HAL_FDCAN_Stop(&hfdcan2);
				u8Slavenumber = SlaveBoardNum();
				MX_FDCAN2_Init();
				CAN2_Fail1=0;
				CAN2_Fail2=0;
			}
			else
			{

			}*/
			mSec40_Flag=0;
		}
		//Task Executed at every 100 mSec
		if (mSec100_Flag==1){
			mSec100_Flag=0;
	//			CAN_DATA_XCHANGING();
		}

		// Task Executed at every 1 Sec
		if(Sec1_Flag==1){
			display_errors(); // show error in display
			u8MASTER1_STATUS=0;
			u8MASTER1_STATUS_CAN2=0;
			Sec1_Flag=0;
			if(cmd.bits.Parameter_Save == 1)
			{
				cmd.bits.Parameter_Save=0;
				para_save();
			}
		}
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	//		(u8temp==1) ? MX_FDCAN2_Init() : 0;
	//		u8temp=0;
	//
	//		(u8temp1==1) ? MX_FDCAN1_Init() : 0;
	//		u8temp1=0;
	//		API_CAN_HEARTBEAT_CELL0139_MASTER01(CONNECT);
	//				HAL_Delay(1000);

	//	  PSFBON();
	//	  HAL_Delay(1000);
	//	  PSFBOFF();
	//	  HAL_Delay(1000);
	/* USER CODE END WHILE */

	/* USER CODE BEGIN 3 */
		uartDataHandler();
	}
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1_BOOST);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = RCC_PLLM_DIV6;
  RCC_OscInitStruct.PLL.PLLN = 85;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
uint16_t SlaveBoardNum(void)
{
	/*Read bits from GPIO and return from here with Hex Number*/
	uint16_t u16Slavenumber=generate_address();
	return u16Slavenumber;
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
