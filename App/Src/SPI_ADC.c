#include "spi.h"

int32_t RecievedSPI, ADCValue[8];
uint8_t i = 0;
uint16_t data;
uint16_t datasize;
void ADC_SPI(void)
{
/*  //For AUTO RST Command
//	while (HAL_GPIO_ReadPin(CS_PC_GPIO_Port, CS_PC_Pin)==GPIO_PIN_RESET) {} //need to find new way
	HAL_GPIO_WritePin(CS_PC_GPIO_Port, CS_PC_Pin, GPIO_PIN_SET);
//	uint16_t data = 0X01FF; // Command :- set 01h(Auto sequence enable) to 0XFF for AUTO_RST mode.
//	HAL_SPI_Transmit(&hspi4 , data, dataSize, HAL_MAX_DELAY);
//	data = 0X02FF; // Command :- set 02h(channel power down) to 0XFF for AUTO_RST mode.
//	HAL_SPI_Transmit(&hspi4 , data, dataSize, HAL_MAX_DELAY);
//	data = 0X0303; // Command :- set 03h(Feature select)
//	HAL_SPI_Transmit(&hspi4 , data, dataSize, HAL_MAX_DELAY);
//	data = 0X0303; // Command :- set 03h(Feature select)
//	HAL_SPI_Transmit(&hspi4 , data, dataSize, HAL_MAX_DELAY);
	data = 0XA000; //Command :- Auto Ch. Sequence with Reset
	datasize = sizeof(data);
	HAL_SPI_Transmit(&hspi4 , data, datasize, HAL_MAX_DELAY);
//	HAL_SPI_Receive(&hspi4, ADC, , HAL_MAX_DELAY);
//	while (HAL_GPIO_ReadPin(CS_PC_GPIO_Port, CS_PC_Pin)==GPIO_PIN_RESET) {} //need to find new way
	HAL_GPIO_WritePin(CS_PC_GPIO_Port, CS_PC_Pin, GPIO_PIN_SET);
*/
	data = 0xC000; //read channel 0 data
	HAL_GPIO_WritePin(CS_PC_GPIO_Port, CS_PC_Pin, GPIO_PIN_SET);
	HAL_SPI_Transmit(&hspi4 , (uint8_t *)&data, datasize, HAL_MAX_DELAY);
	NOP();
	data = 0xC400; //read channel 1 data
	HAL_GPIO_WritePin(CS_PC_GPIO_Port, CS_PC_Pin, GPIO_PIN_SET);
	HAL_SPI_Transmit(&hspi4 , (uint8_t *)&data, datasize, HAL_MAX_DELAY);
	NOP();
	data = 0xC800; //read channel 2 data
	HAL_GPIO_WritePin(CS_PC_GPIO_Port, CS_PC_Pin, GPIO_PIN_SET);
	HAL_SPI_Transmit(&hspi4 , (uint8_t *)&data, datasize, HAL_MAX_DELAY);
	NOP();
	data = 0xCC00; //read channel 3 data
	HAL_GPIO_WritePin(CS_PC_GPIO_Port, CS_PC_Pin, GPIO_PIN_SET);
	HAL_SPI_Transmit(&hspi4 , (uint8_t *)&data, datasize, HAL_MAX_DELAY);
	NOP();
	data = 0xD000; //read channel 4 data
	HAL_GPIO_WritePin(CS_PC_GPIO_Port, CS_PC_Pin, GPIO_PIN_SET);
	HAL_SPI_Transmit(&hspi4 , (uint8_t *)&data, datasize, HAL_MAX_DELAY);
	NOP();
	data = 0xD400; //read channel 5 data
	HAL_GPIO_WritePin(CS_PC_GPIO_Port, CS_PC_Pin, GPIO_PIN_SET);
	HAL_SPI_Transmit(&hspi4 , (uint8_t *)&data, datasize, HAL_MAX_DELAY);
	NOP();
	data = 0xD800; //read channel 6 data
	HAL_GPIO_WritePin(CS_PC_GPIO_Port, CS_PC_Pin, GPIO_PIN_SET);
	HAL_SPI_Transmit(&hspi4 , (uint8_t *)&data, datasize, HAL_MAX_DELAY);
	NOP();
	data = 0xDC00; //read channel 7 data
	HAL_GPIO_WritePin(CS_PC_GPIO_Port, CS_PC_Pin, GPIO_PIN_SET);
	HAL_SPI_Transmit(&hspi4 , (uint8_t *)&data, datasize, HAL_MAX_DELAY);
	NOP();
}

void HAL_SPI_RxCpltCallback(SPI_HandleTypeDef *hspi)
{
	if((SPI_HandleTypeDef *)&hspi == (SPI_HandleTypeDef *)&hspi4)
	{

/*	//For AUTO RST Command
		if(i < 8)
		{
			HAL_SPI_Receive_IT(&hspi4, &RecievedSPI, sizeof(RecievedSPI)); // Need to check when i=0 is previous mode ADC value so we should ignore it or not.
			ADCValue[i] = RecievedSPI;
			i++;
			NOP();
			if( i <= 7)
			{
				HAL_GPIO_WritePin(CS_PC_GPIO_Port, CS_PC_Pin, GPIO_PIN_SET);
			}
		}
*/
	// For Manual command
			HAL_SPI_Receive_IT(&hspi4, (uint8_t *)&RecievedSPI, sizeof(RecievedSPI)); // Need to check when i=0 is previous mode ADC value so we should ignore it or not.
			ADCValue[i] = RecievedSPI;
			i++;
	}
}


