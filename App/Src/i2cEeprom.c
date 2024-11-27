#define I2CEEPROM_H_
#include "i2cEeprom.h"
#include "i2c.h"
#include"string.h"
#include "process.h"
#include "protection.h"
#include "debug.h"
#include "error_display.h"

//#include "i2cLcd.h"

extern I2C_HandleTypeDef hi2c4;

//uint8_t eepromWriteData(uint16_t pageAddress, uint8_t memAddress, uint8_t *txData, uint16_t buffSize,uint8_t dataType)
//{
//	/* Set WCN pin low */
////	WCN_GPIO_Port->ODR &= ~WCN_Pin;
//	memAddr = memAddress;
//	dataPtr = 0;
//
//	while(buffSize > 0)
//	{
//		/* Check if the EEPROM is ready for a new operation */
//		if(HAL_I2C_IsDeviceReady(&hi2c4, pageAddress, 10, 200) == HAL_OK)
//		{
//				if(HAL_I2C_Mem_Write(&hi2c4 , pageAddress, memAddr, I2C_MEMADD_SIZE_16BIT, (uint8_t*)(txData+dataPtr),dataType,300) != HAL_OK){
//					Error_Handler();
//		}
//	}
////    else
////    {
////	Error_Handler();
////    }
//
//		/* Wait for the end of the transfer */
//		while(HAL_I2C_GetState(&hi2c4) != HAL_I2C_STATE_READY){};
//
//		buffSize -= 1;
//		memAddr += dataType;
//		dataPtr++;
//	}
//
//	HAL_Delay(5);
//
//	/* Set WCN pin high */
////	WCN_GPIO_Port->ODR |= WCN_Pin; //setting WCN bit high
//	return TRUE;
//}
//
//uint8_t eepromReadData(uint16_t pageAddress, uint8_t memAddress, uint8_t *rxData, uint16_t buffSize,uint8_t dataType)
//{
//	/* Set WCN pin low */
////	WCN_GPIO_Port->ODR &= ~WCN_Pin; //setting WCN bit low //setting WCN bit low
//
//	memAddr = memAddress;
//	dataPtr = 0;
//
//	while(buffSize>0){
//		/* Check if the EEPROM is ready for a new operation */
//    if(HAL_I2C_IsDeviceReady(&hi2c4, pageAddress, 10, 200) == HAL_OK){
//			if(HAL_I2C_Mem_Read(&hi2c4, (uint16_t)pageAddress, memAddr, I2C_MEMADD_SIZE_16BIT, (uint8_t *)(rxData+dataPtr), dataType,300) != HAL_OK){
//				Error_Handler();
//			}
//		}
////    else{
////			Error_Handler();
////		}
//		/* Wait for the end of the transfer */
//		while (HAL_I2C_GetState(&hi2c4) != HAL_I2C_STATE_READY){};
//
//		buffSize -=1;
//		memAddr += dataType;
//		dataPtr++;
//	}
//
//	HAL_Delay(5);
//	/* Set WCN pin high */
////	WCN_GPIO_Port->ODR |= WCN_Pin; //setting WCN bit high
//
//	return TRUE;
//}
//uint8_t eepromEraseData(uint16_t pageAddress, uint8_t MemAddress)
//{
//	uint8_t buffSize;
//
//	/* Set WCN pin low */
////	WCN_GPIO_Port->ODR &= ~WCN_Pin;
//
//	memAddr = MemAddress;
//	buffSize = 1;
//
//	while(buffSize > 0)
//  {
//		/* Check if the EEPROM is ready for a new operation */
//    while(HAL_I2C_IsDeviceReady(&hi2c4, pageAddress, 20, 200) == HAL_TIMEOUT);
//
//    if(HAL_I2C_Mem_Write(&hi2c4 , pageAddress, memAddr, I2C_MEMADD_SIZE_16BIT, (uint8_t*)clearData,1,300) != HAL_OK)
//		{
//			Error_Handler();
//		}
//
//		/* Wait for the end of the transfer */
//    while(HAL_I2C_GetState(&hi2c4) != HAL_I2C_STATE_READY){};
//
//    buffSize -= 1;
//    memAddr += 1;
//	}
//
//	/* Set WCN pin high */
////	WCN_GPIO_Port->ODR |= WCN_Pin; //setting WCN bit high
//
//	return TRUE;
//}

/* Example implementation
configParameters configpara_receive;
writeStructureToEeprom((uint8_t*)&ConfigPara, sizeof(ConfigPara));
readStructurefromEeprom((uint8_t*)&configpara_receive, sizeof(configpara_receive));
*/
uint16_t eeprom_crc_generate(uint8_t* config_pointer, uint16_t size_of_structure)
{
	const uint16_t generator_polynomial = 0x1021;
	uint16_t crc = 0;

	for (uint16_t i=0; i<size_of_structure; i++)
	{
		crc ^= (uint16_t)((*(config_pointer + i)) << 8);

		for (int j = 0; j < 8; j++)
		{
			if((crc & 0x8000) != 0)
				crc = (uint16_t)((crc << 1) ^ generator_polynomial);
			else
				crc <<= 1;
		}
	}
	return crc;
}

void writeStructureToEeprom(uint8_t* config_pointer, uint16_t size_of_structure)
{
	if(HAL_I2C_Mem_Write(&hi2c4 , EEPROM_ADDR1, 0, I2C_MEMADD_SIZE_16BIT, (uint8_t*)config_pointer, size_of_structure,300) != HAL_OK){
//			Error_Handler();
		fault3.bits.eeprom_fault = 1;
		add_error_to_list(12);
		}
	uint16_t eeprom_crc_write = eeprom_crc_generate(config_pointer,size_of_structure);
	if(HAL_I2C_Mem_Write(&hi2c4 , EEPROM_ADDR1, 1000, I2C_MEMADD_SIZE_16BIT, (uint8_t*)&eeprom_crc_write, 2,300) != HAL_OK){
		fault3.bits.eeprom_fault = 1;
		add_error_to_list(12);
//				Error_Handler();
			}

}

uint8_t readStructurefromEeprom(uint8_t* config_pointer, uint16_t size_of_structure)
{
	uint16_t crc_received_from_eeprom;
	if(HAL_I2C_IsDeviceReady(&hi2c4, EEPROM_ADDR1, 10, 200) == HAL_OK){
			if(HAL_I2C_Mem_Read(&hi2c4, EEPROM_ADDR1, 0, I2C_MEMADD_SIZE_16BIT, (uint8_t *)config_pointer, size_of_structure,300) != HAL_OK){
//				Error_Handler();
				fault3.bits.eeprom_fault = 1;
				add_error_to_list(12);
				 return 0;
			}
		}
	if(HAL_I2C_Mem_Read(&hi2c4, EEPROM_ADDR1, 1000, I2C_MEMADD_SIZE_16BIT, (uint8_t *)&crc_received_from_eeprom, 2,300) != HAL_OK){
//		Error_Handler();
		fault3.bits.eeprom_fault = 1;
		add_error_to_list(12);
		 return 0;
	}
	uint16_t generated_crc = eeprom_crc_generate(config_pointer,size_of_structure);
	if(generated_crc == crc_received_from_eeprom)
		return 1;
	else
		return 0;

}

/*
This function is used to load the default parameter and save them to FRAM
*/
void para_load()
{
	if (readStructurefromEeprom((uint8_t*)&ConfigPara, sizeof(ConfigPara)) == 0) {
		 ParaInit();
		 if(fault3.bits.eeprom_fault == 0)
		 {remove_error_from_list(12);}
		 else if (fault3.bits.eeprom_fault == 1)
		 {add_error_to_list(12);}
	}else{
		 {/*Action to be added*/}
	}
}

/* This function is used to load default factory parameters*/
void default_para_load()
{
	ParaInit();
}

/*
This function is used to save the present parameters to the FRAM
*/
void para_save()
{
	writeStructureToEeprom((uint8_t*)&ConfigPara,sizeof(ConfigPara));
}

