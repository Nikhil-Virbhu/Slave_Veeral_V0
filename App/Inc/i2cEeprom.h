#include "main.h"
#define COUNTOF(__BUFFER__)   (sizeof(__BUFFER__) / sizeof(*(__BUFFER__)))

/* Page Addresses */
#define EEPROM_ADDR1 (uint16_t)0x00A0
#define EEPROM_ADDR2 (uint16_t)0x00A2 
#define EEPROM_ADDR3 (uint16_t)0x00A4 
#define EEPROM_ADDR4 (uint16_t)0x00A6 
#define EEPROM_ADDR5 (uint16_t)0x00A8 //only for m24c16-rmn6p, not working for atmel eeprom

/* Dats Type storage in bytes */
#define INT_8  1
#define INT_16 2
#define INT_32 4
#define FLOAT  4

#define TRUE 1
#define FALSE 0

#ifdef I2CEEPROM_H_
	uint8_t memAddr=0;
	uint8_t dataPtr=0;
	uint8_t clearData[1] = {0};
	uint8_t eeprom_data_write_buf[96];
	uint8_t eeprom_data_read_buf[96];
//	uint8_t eepromWriteData(uint16_t pageAddress, uint8_t memAddress, uint8_t *txData, uint16_t buffSize,uint8_t dataType);
//	uint8_t eepromReadData(uint16_t pageAddress, uint8_t memAddress, uint8_t *rxData, uint16_t buffSize,uint8_t dataType);
//	uint8_t eepromEraseData(uint16_t pageAddress, uint8_t MemAddress);
	void writeStructureToEeprom(uint8_t*, uint16_t);
	uint8_t readStructurefromEeprom(uint8_t* config_pointer, uint16_t size_of_structure);
	void default_para_load();
	void para_load();
	void para_save();
	uint8_t set_default_para_cmd = 0,para_save_cmd = 0;

#else
	extern uint8_t memAddr;
	extern uint8_t dataPtr;
	extern uint8_t clearData[1];
	extern uint8_t eeprom_data_write_buf[96];
	extern uint8_t eeprom_data_read_buf[80];
//	extern uint8_t eepromWriteData(uint16_t pageAddress, uint8_t memAddress, uint8_t *txData, uint16_t buffSize,uint8_t dataType);
//	extern uint8_t eepromReadData(uint16_t pageAddress, uint8_t memAddress, uint8_t *rxData, uint16_t buffSize,uint8_t dataType);
//	extern uint8_t eepromEraseData(uint16_t pageAddress, uint8_t MemAddress);
	extern void writeStructureToEeprom(uint8_t *, uint16_t);
	extern uint8_t readStructurefromEeprom(uint8_t* config_pointer, uint16_t size_of_structure);
	extern void default_para_load();
	extern void para_load();
	extern void para_save();
	extern uint8_t set_default_para_cmd,para_save_cmd;
#endif
