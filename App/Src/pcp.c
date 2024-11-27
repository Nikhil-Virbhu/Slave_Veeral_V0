/*
 * File description : Contains functions to receive data based on parallel communication protocol
 */
#define _PCP_
#include "pcp.h"

/*
* Function Description: Generates the crc checksum for input array of bytes
* Input:
* Return:
*/
uint16_t crc16_check(uint8_t byte[], uint8_t length)
{
	const uint16_t generator_polynomial = 0x1021;
	uint16_t crc = 0;

	for (uint8_t i=0; i<length; i++)
	{
		crc ^= ((uint16_t)(byte[i]) << 8);

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

/*
* Function Description: Reads the data from the bus performs the the crc check and returns the value sent
* Input:
* Return:
*/
int32_t read_data_from_bus()
{
	uint8_t bytes_received[2];
	uint16_t local_checksum;
	uint16_t received_checksum;
//	g_holding_buffer[g_number_of_bytes_received] = (uint8_t)((GPIO_TypeDef *) PB0_GPIO_Port->IDR) & (uint8_t)0xff;
	g_number_of_bytes_received ++;
	if(g_number_of_bytes_received == 4)
	{
		g_number_of_bytes_received = 0;
		bytes_received[0] = g_holding_buffer[1]; //Assuming MSB
		bytes_received[1] = g_holding_buffer[0]; //Assuming LSB
		local_checksum = crc16_check(bytes_received, 2);
		received_checksum = (g_holding_buffer[2] << 8) | g_holding_buffer[3];
		if (received_checksum == local_checksum)
		{
			return ((bytes_received[0] << 8) | bytes_received[1]);
		}
		else
		{
//			HAL_GPIO_WritePin(ACK_GPIO_Port, ACK_Pin, 1);
			// Insert a delay
//			HAL_GPIO_WritePin(ACK_GPIO_Port, ACK_Pin, 0);
			return -1;
		}
	}
	else
		return -1;
}

/*
* Function Description: read the status of DIP switch and generate a cell address based on it.
* Input:
* Return:
*/
uint8_t switch_states[6];
uint16_t generate_address()
{
//	uint8_t switch_states[6];
	uint16_t address;
	switch_states[0] = HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_7);
	switch_states[1] = HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_6);
	switch_states[2] = HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_5);
	switch_states[3] = HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_4);
	switch_states[4] = HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_3);
	switch_states[5] = HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_0);
	address = (uint16_t)(((uint16_t)switch_states[0] << 5) | ((uint16_t)switch_states[1] << 4) | ((uint16_t)switch_states[2] << 3) | ((uint16_t)switch_states[3]) << 2 | ((uint16_t)switch_states[4]) << 1 | ((uint16_t)switch_states[5]));
	return address;
}
