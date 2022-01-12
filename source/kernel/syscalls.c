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
#include <arcticOS/kernel/flash.h>
#include <freeRTOS/FreeRTOS.h>
#include <freeRTOS/task.h>
#include <hardware/arcticOS/screen.h>
#include <hardware/arcticOS/keypad.h>

struct syscall_params {
    int* data;
    int** return_values;
};

void display_syscall(int* data, int** return_data) {
    uint16_t color;

    switch(data[1]) {
        case 0x00: // Backlight (int on/off)
            if(data[2]) screen_backlight_on();
            else screen_backlight_off();
            break;
        case 0x01: // Fill (uint16_t* color)
            color = ((uint16_t*) data[2])[0];
            screen_fill(color);
            break;
        case 0x02: // Plot (int x) (int y) (int color_high) (int color_low)
            color = data[4] << 8;
            color |= data[5];
            screen_plot_pixel(data[2], data[3], color);
            break;
        case 0x03: // Refresh
            screen_refresh();
            break;
        case 0x04: // Get screen width
            return_data[0][0] = SCREEN_WIDTH;
            break;
        case 0x05: // Get screen height
            return_data[0][0] = SCREEN_HEIGHT;
            break;
    }
}

void panic_syscall(int* data, int** return_data) {
    // Panic (const int* message)
    system_panic(&data[1]);
}

void input_syscall(int* data, int** return_data) {
    keypad_refresh();
    switch(data[1]) {
        case 0x00: // Is button pressed (uint16_t* mask)
            return_data[0][0] = buttons_pressed & data[2];
            break;
        case 0x01: // Is button not pressed (uint16_t* mask)
            return_data[0][0] = buttons_pressed & data[2] == 0x0000;
            break;
        case 0x02: // Is no button pressed 
            return_data[0][0] = buttons_pressed == 0x0000;
            break;
    }
}

void storage_syscall(int* data, int** return_data) {
    switch(data[1]) {
        case 0: // Load byte at offset
            return_data[0][0] = flash_load_byte((uint32_t) data[2]);
    }
}

void handle_syscall(int* data, int** return_data) {
    screen_backlight_off();
    // TODO: Check permissions

    switch(data[0]) {
        case 0x00: // Display
            display_syscall(data, return_data);
            break;
        case 0x01: // Kernel Panic
            panic_syscall(data, return_data);
            break;
        case 0x02: // User Input
            input_syscall(data, return_data);
            break;
        case 0x03: // Storage
            storage_syscall(data, return_data);
            break;
        case 0x04: // Cellular
            break;
        case 0x05: // GPIO
            break;
        case 0x06: // Internal Communication (UART/SPI)
            break;
        case 0x07: // Secure Messaging
            break;
        case 0x08: // General Cryptography
            break;
    }
}

void register_syscall_handler() {
    flash_buffer[0] = &handle_syscall;

    uint8_t* write_target = (uint8_t*) (XIP_BASE + SYSTEM_INFO_ADDRESS);
    for(int i = 0; i < 3 * ENFORCE_FLASH_WRITE_SUCCESS; i++) { // Writes always fail the first time for some reason.
        flash_range_erase(SYSTEM_INFO_ADDRESS, USER_DATA_SIZE); // Erase the sector.
        flash_range_program(SYSTEM_INFO_ADDRESS, flash_buffer, USER_DATA_SIZE); // Write the sector.

        // Verify flash write.
        if(ENFORCE_FLASH_WRITE_SUCCESS) {
            int fail = 0;
            for(int i = 0; i < USER_DATA_SIZE; i++) {
                if(flash_buffer[i] != write_target[i]) {
                    fail = 1;
                    break;
                }
            }
            if(!fail) return;
        } else return;
    }

    // This will only be called if flash writes are enforced and the write fails 3 times.
    for(;;) {
        screen_backlight_off();
        sleep_ms(500);
        screen_backlight_on();
        sleep_ms(500);
    }
}