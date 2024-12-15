/*
 * flash_mem.c
 *
 *  Created on: Dec 13, 2024
 *      Author: phat
 */

#include "flash_mem.h"

uint32_t Flash_Write_CharArr(char *data, uint32_t startAddress) {
    uint32_t endAddress = startAddress;
    uint32_t dataLength = strlen(data) + 1;
    uint32_t word;
    HAL_FLASH_Unlock();
    for (uint32_t i = 0; i < dataLength; i += 4) {
        word = 0xFFFFFFFF;
        for (uint32_t j = 0; j < 4 && (i + j) < dataLength; j++) {
            ((uint8_t*)&word)[j] = data[i + j];
        }
        if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, endAddress, word) != HAL_OK) {
            HAL_FLASH_Lock();
            return 0;
        }
        endAddress += 4;
    }
    HAL_FLASH_Lock();
    return endAddress;
}
HAL_StatusTypeDef Flash_Write_Byte(uint32_t address, uint8_t data) {
    HAL_StatusTypeDef status;
    uint32_t data32;

    HAL_FLASH_Unlock();
    data32 = (uint32_t)data;
    status = HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, address, data32);
    if (status != HAL_OK) {
        HAL_FLASH_Lock();
        return status; // Write failed
    }
    HAL_FLASH_Lock();
    return HAL_OK;
}
uint8_t Flash_Read_Byte(uint32_t address) {
    return *(uint8_t *)address;
}
uint8_t Flash_Read_CharArr(char *buffer, uint32_t startAddress) {
	if (Flash_Read_Byte(startAddress) == 0xFF) {
		return 0;
	}
    uint32_t i = 0;
    while (1) {
        buffer[i] = *((char*)(startAddress + i));
        if (buffer[i] == '\0') break;
        i++;
    }
    return 1;
}

uint8_t Flash_Erase_Sector11() {
	HAL_FLASH_Unlock();
	FLASH_EraseInitTypeDef eraseInitStruct;
	uint32_t sectorError;
	eraseInitStruct.TypeErase = FLASH_TYPEERASE_SECTORS;
	eraseInitStruct.VoltageRange = FLASH_VOLTAGE_RANGE_3;
	eraseInitStruct.Sector = FLASH_SECTOR_11;
	eraseInitStruct.NbSectors = 1;
	if (HAL_FLASHEx_Erase(&eraseInitStruct, &sectorError) != HAL_OK) {
		HAL_FLASH_Lock();
		return 0;
	}
	HAL_FLASH_Lock();
	return 1;
}
