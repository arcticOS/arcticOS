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

#include <arcticOS.h>
#include <FreeRTOS/FreeRTOS.h>

// Used for I/O
#include <stdio.h>

// Theme
uint16_t background_color = 0x0000;
uint16_t foreground_color = 0xFFFF;

// Used for disabling/enabling interrupts
#include <hardware/irq.h>
int irq_table[32];

// Used for interfacing with other hardware on motherboard
#include <arcticOS/drivers/net/cellular.h>
#include <arcticOS/drivers/display/screen.h>

// Used for flash memory
#include <arcticOS/drivers/flash.h>
uint8_t flash_buffer[USER_DATA_SIZE];

// First process to run after boot
void init(void) {
    
    for(;;);
}

// Initialise arcticOS
int main(void) {
    // Init cellular
    cellular_init();

    // Init keypad
    keyboard_init();

    // Init screen
    screen_init();
    
    // Start init process
    xTaskCreate(init, "init", 256, NULL, 1, NULL);
    vTaskStartScheduler();

    system_panic("Failed to enable multitasking!");
    return 0;
}