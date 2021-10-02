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

// For some reason this won't build, it can't even see uint8_ts

#ifndef FLASH_H
#define FLASH_H

#define USER_DATA_ADDRESS (256 * 1024)
#define USER_DATA_SIZE FLASH_PAGE_SIZE

#include <stdio.h>
#include <stdlib.h>
#include <pico/stdlib.h>
#include <hardware/flash.h>

int user_data[USER_DATA_SIZE];
const uint8_t *flash_user_data = (const uint8_t *) (XIP_BASE + USER_DATA_ADDRESS);

void flash_load_user_data() {
    for(int i = 0; i < USER_DATA_SIZE; i++) {
        user_data[i] = flash_user_data[i];
    }
}

void flash_write_user_data() {
    flash_range_erase(USER_DATA_ADDRESS, USER_DATA_SIZE);
    flash_range_program(USER_DATA_ADDRESS, &user_data, USER_DATA_SIZE);
}
#endif