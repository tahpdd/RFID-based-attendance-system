/*
 * flash_mem.h
 *
 *  Created on: Dec 13, 2024
 *      Author: phat
 */

#ifndef INC_FLASH_MEM_H_
#define INC_FLASH_MEM_H_

#include "stm32f4xx_hal.h"
#include <stdint.h>
#include <string.h>


// Function prototypes
uint32_t Flash_Write_CharArr(char *data, uint32_t startAddress);
HAL_StatusTypeDef Flash_Write_Byte(uint32_t address, uint8_t data);
uint8_t Flash_Read_Byte(uint32_t address);
uint8_t Flash_Read_CharArr(char *buffer, uint32_t startAddress);
uint8_t Flash_Erase_Sector11(void);

#endif /* INC_FLASH_MEM_H_ */
