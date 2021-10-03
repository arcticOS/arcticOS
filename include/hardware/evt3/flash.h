/*
 * arcticOS
 * Copyright (C) 2021 Johnny Stene
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

#ifndef FLASH_H
#define FLASH_H

// 256k from start
#define USER_DATA_ADDRESS (256 * 1024)

// 4k sectors
#define USER_DATA_SIZE FLASH_SECTOR_SIZE

#include <stdio.h>
#include <stdlib.h>
#include <pico/stdlib.h>
#include <hardware/flash.h>
#include <arcticOS.h>

const uint8_t *flash_user_data = (const uint8_t *) (XIP_BASE + USER_DATA_ADDRESS);

void flash_load_user_data(uint32_t offset, uint8_t* buffer) {
    system_disable_interrupts();
    for(int i = 0; i < USER_DATA_SIZE; i++) {
        buffer[i] = flash_user_data[i + (offset * USER_DATA_SIZE)];
    }
    system_enable_interrupts();
}

void flash_write_user_data(uint32_t offset, uint8_t* buffer) {
    for(int i = 0; i < 3 * ENFORCE_FLASH_WRITE_SUCCESS; i++) {
        system_disable_interrupts();
        flash_range_erase(USER_DATA_ADDRESS + (offset * USER_DATA_SIZE), USER_DATA_SIZE);
        flash_range_program(USER_DATA_ADDRESS + (offset * USER_DATA_SIZE), buffer, USER_DATA_SIZE);
        system_enable_interrupts();

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
    system_panic("Flash Failed to Verify");
}
#endif