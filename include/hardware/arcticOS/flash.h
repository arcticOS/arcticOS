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

#include <pico/stdlib.h>

void flash_load_user_data(uint32_t offset, uint8_t* buffer);
void flash_write_user_data(uint32_t offset, uint8_t* buffer);
void flash_erase_user_data(uint32_t offset);

#if defined(EVT4)

#elif defined(EVT3)
#define USER_DATA_ADDRESS (256 * 1024)
#define USER_DATA_SIZE FLASH_SECTOR_SIZE
#include <hardware/flash.h>
#endif