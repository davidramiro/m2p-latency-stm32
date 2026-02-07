#include "../Inc/flash.h"
#include "../Inc/main.h"

uint32_t packedChecksum(const uint8_t val8, const uint16_t val16) {
    return val16 << 8 | val8;
}

void readFlash(void) {
    uint8_t cycles_read = *(__IO uint32_t *)CYCLES_MEM_ADDR;
    uint16_t threshold_read = *(__IO uint32_t *)THRESHOLD_MEM_ADDR;
    uint32_t checksum_read = *(__IO uint32_t *)CHECKSUM_MEM_ADDR;

    if (packedChecksum(cycles_read, threshold_read) != checksum_read) {
        // Checksum mismatch - write defaults to flash
        // Ignore return value on initialization - defaults are already set
        saveToFlash();
    } else {
        num_cycles = cycles_read;
        sensor_threshold = threshold_read;
    }
}

FlashStatus saveToFlash(void) {
    uint8_t cycles = *(__IO uint32_t *)CYCLES_MEM_ADDR;
    uint16_t threshold = *(__IO uint32_t *)THRESHOLD_MEM_ADDR;
    uint32_t checksum = *(__IO uint32_t *)CHECKSUM_MEM_ADDR;

    // No need to write if data unchanged
    if (cycles == num_cycles && threshold == sensor_threshold && checksum == packedChecksum(cycles, threshold))
    {
        return FLASH_OK;
    }

    HAL_StatusTypeDef status;

    status = HAL_FLASH_Unlock();
    if (status != HAL_OK) {
        return FLASH_ERROR_UNLOCK;
    }

    FLASH_EraseInitTypeDef eraseInit;
    eraseInit.TypeErase = FLASH_TYPEERASE_SECTORS;
    eraseInit.Sector = 7;
    eraseInit.NbSectors = 1;
    eraseInit.VoltageRange = FLASH_VOLTAGE_RANGE_3;

    uint32_t sectorError = 0;
    status = HAL_FLASHEx_Erase(&eraseInit, &sectorError);
    if (status != HAL_OK) {
        HAL_FLASH_Lock();
        return FLASH_ERROR_ERASE;
    }

    status = HAL_FLASH_Program(FLASH_TYPEPROGRAM_BYTE, CYCLES_MEM_ADDR, num_cycles);
    if (status != HAL_OK) {
        HAL_FLASH_Lock();
        return FLASH_ERROR_PROGRAM_CYCLES;
    }

    status = HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD, THRESHOLD_MEM_ADDR, sensor_threshold);
    if (status != HAL_OK) {
        HAL_FLASH_Lock();
        return FLASH_ERROR_PROGRAM_THRESHOLD;
    }

    status = HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, CHECKSUM_MEM_ADDR, packedChecksum(num_cycles, sensor_threshold));
    if (status != HAL_OK) {
        HAL_FLASH_Lock();
        return FLASH_ERROR_PROGRAM_CHECKSUM;
    }

    HAL_FLASH_Lock();

    uint8_t cycles_read = *(__IO uint32_t *)CYCLES_MEM_ADDR;
    uint16_t threshold_read = *(__IO uint32_t *)THRESHOLD_MEM_ADDR;
    uint32_t checksum_read = *(__IO uint32_t *)CHECKSUM_MEM_ADDR;

    if (cycles_read != num_cycles || threshold_read != sensor_threshold ||
        checksum_read != packedChecksum(num_cycles, sensor_threshold)) {
        return FLASH_ERROR_VERIFY;
    }

    return FLASH_OK;
}
