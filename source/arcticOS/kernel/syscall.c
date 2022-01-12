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

#include <arcticOS/kernel/flash.h>
#include <pico/stdlib.h>

struct syscall_params {
    int* data;
    int** return_values;
};

void system_call(int data, int** return_data) {
    uint8_t** system_call_location = (uint8_t**) (XIP_BASE + SYSTEM_INFO_ADDRESS);
    void (*system_call_function)(int*, int**) = (void (*)(int*, int**)) system_call_location[0];
    system_call_function(data, return_data);
}
