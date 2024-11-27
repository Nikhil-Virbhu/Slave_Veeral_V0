/* File description:
*Functions used:
 *Reference document:
*/
#include "main.h"

#ifdef _PCP_
	uint8_t g_number_of_bytes_received;
	uint8_t g_holding_buffer[4];
	uint16_t crc16_check(uint8_t byte[], uint8_t length);
	int32_t read_data_from_bus();
	uint16_t generate_address(void);
#else
	extern uint8_t g_number_of_bytes_received;
	extern uint8_t g_holding_buffer[4];
	extern uint16_t crc16_check(uint8_t byte[], uint8_t length);
	extern int32_t read_data_from_bus();
	extern uint16_t generate_address(void);
#endif


