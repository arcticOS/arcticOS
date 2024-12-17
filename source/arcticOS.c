/*
 * arcticOS
 * Copyright (C) 2024 Johnny Stene
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

#include <stdio.h>

#include <arcticOS.h>
#include <FreeRTOS/FreeRTOS.h>
#include <arcticOS/processes.h>
#include <arcticOS/menus.h>

// Used for flash memory
#include <arcticOS/drivers/flash.h>
uint8_t flash_buffer[USER_DATA_SIZE];

int main(void) {
    /* TODO: Init all hardware
    // Init cellular
    cellular_init();

    // Init keypad
    keyboard_init();

    // Init screen
    screen_init();*/

    // Override interface handlers
    interface_incoming_call = menu_incoming_call;
    interface_in_call = menu_in_call;
    interface_incoming_sms = menu_incoming_sms;

    // Start multitasking
    os_create_processes();
    vTaskStartScheduler();

    // Should never reach here
    system_panic("Failed to enable multitasking!");
    return;
}