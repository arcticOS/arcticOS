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

#include <stdint.h>

uint8_t flash_load_byte(uint32_t offset);
void flash_load_user_data(uint32_t offset, uint8_t* buffer);
void flash_write_user_data(uint32_t offset, uint8_t* buffer);
void flash_erase_user_data(uint32_t offset);

#define USER_DATA_ADDRESS (256 * 1024)
#define SYSTEM_INFO_ADDRESS (255 * 1024)
#define USER_DATA_SIZE 1024

// Flash layout
#define FLASH_OFFSET_SETTINGS (0 * USER_DATA_SIZE)
// 1 byte
#define FLASH_SETTINGS_OOBE_COMPLETE 0
// 2 bytes
#define FLASH_SETTINGS_SLEEP_TIME 1
// 1 byte
#define FLASH_SETTINGS_THEME 3
// 1 byte
#define FLASH_SETTINGS_CLOCK 4

#define FLASH_OFFSET_CONTACTS (1 * USER_DATA_SIZE)