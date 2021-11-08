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

#include <arcticOS.h>
#include <hardware/arcticOS/screen.h>
#include <hardware/arcticOS/keypad.h>

struct syscall_params {
    int* data;
    int** return_values;
};

void register_syscall_handler() {
    irq_set_exclusive_handler(30, &handle_syscall);
    irq_set_enabled(30, 1);
}

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

void handle_syscall(void) {
    struct syscall_params* params;
    asm volatile("mov %0, R1" : "=r" (params));

    int* data = params->data;
    int** return_data = params->return_values;

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
