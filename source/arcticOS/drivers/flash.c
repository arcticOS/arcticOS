/*
 * arcticOS
 * Copyright (C) 2022 Johnny Stene
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <arcticOS/drivers/flash.h>
#include <FreeRTOS/FreeRTOS.h>
#include <FreeRTOS/task.h>

#if defined(EVT3)
#include <stdio.h>
#include <stdlib.h>
#include <pico/stdlib.h>
#include <hardware/flash.h>
#include <arcticOS.h>

const uint8_t *flash_user_data = (const uint8_t *) (XIP_BASE + USER_DATA_ADDRESS);

// Loads a byte from flash
uint8_t flash_load_byte(uint32_t offset) {
    taskENTER_CRITICAL();
    uint8_t value = flash_user_data[offset];
    taskEXIT_CRITICAL();
    return value;
}

// Loads a sector of flash into the buffer in arcticOS.c
void flash_load_user_data(uint32_t offset, uint8_t* buffer) {
    taskENTER_CRITICAL();
    for(int i = 0; i < USER_DATA_SIZE; i++) {
        buffer[i] = flash_user_data[i + (offset * USER_DATA_SIZE)];
    }
    taskEXIT_CRITICAL();
}

// Writes a sector of flash from a buffer.
void flash_write_user_data(uint32_t offset, uint8_t* buffer) {
    for(int i = 0; i < 3 * ENFORCE_FLASH_WRITE_SUCCESS; i++) { // Writes always fail the first time for some reason.
        taskENTER_CRITICAL();
        flash_range_erase(USER_DATA_ADDRESS + (offset * USER_DATA_SIZE), USER_DATA_SIZE); // Erase the sector.
        flash_range_program(USER_DATA_ADDRESS + (offset * USER_DATA_SIZE), buffer, USER_DATA_SIZE); // Write the sector.
        taskEXIT_CRITICAL();

        // Verify flash write.
        if(ENFORCE_FLASH_WRITE_SUCCESS) {
            int fail = 0;
            for(int i = 0; i < USER_DATA_SIZE; i++) {
                if(buffer[i] != flash_user_data[i + (offset * USER_DATA_SIZE)]) {
                    fail = 1;
                    break;
                }
            }
            if(!fail) return;
        } else return;
    }

    // This will only be called if flash writes are enforced and the write fails 3 times.
    system_panic("Flash Failed to Verify");
}

// Erases a sector of flash.
void flash_erase_user_data(uint32_t offset) {
    for(int i = 0; i < 3 * ENFORCE_FLASH_WRITE_SUCCESS; i++) { // Writes always fail the first time for some reason.
        taskENTER_CRITICAL();
        flash_range_erase(USER_DATA_ADDRESS + (offset * USER_DATA_SIZE), USER_DATA_SIZE); // Erase the sector.
        taskEXIT_CRITICAL();

        // Verify flash write.
        if(ENFORCE_FLASH_WRITE_SUCCESS) {
            int fail = 0;
            for(int i = 0; i < USER_DATA_SIZE; i++) {
                if((flash_user_data[i + (offset * USER_DATA_SIZE)] != 0x00) && (flash_user_data[i + (offset * USER_DATA_SIZE)] != 0xFF)) {
                    fail = 1;
                    break;
                }
            }
            if(!fail) return;
        } else return;
    }

    // This will only be called if flash writes are enforced and the write fails 3 times.
    system_panic("Flash Failed to Verify");
}
#endif