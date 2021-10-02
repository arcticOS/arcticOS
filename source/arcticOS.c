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
 *
 * This is meant to run on RP2040-based boards.
 */

// CHANGE THE LINE BELOW TO CHANGE LANGUAGE
#include <strings/en-CA.h>

#include <arcticOS.h>

// Used for I/O
#include <stdio.h>
#include <pico/stdlib.h>
#include <hardware/spi.h>

// Used for interfacing with other hardware on motherboard
#include <hardware/arcticOS/cellular.h>
#include <hardware/arcticOS/keypad.h>
#include <hardware/arcticOS/screen.h>
#include <hardware/arcticOS/flash.h>

// Initialise arcticOS
int main(void) {
    // Init cellular
    cellular_init();

    // Init keypad
    keypad_init();

    // Init screen
    screen_init();

    // Init flash
    flash_load_user_data();

    uint16_t background_color = 0x0000;
    uint16_t foreground_color = 0xFFFF;

    if(user_data[0] == 0x00) {
        user_data[0] = 0x01;
    } else {
        user_data[0] = 0x00;
        background_color = 0xFFFF;
        foreground_color = 0x0000;
    }
    flash_write_user_data();

    while(1) {
        screen_fill(background_color);

        screen_print(10, 10, foreground_color, 2, SCREEN_FONT_VGA, "12:41 PM");
        screen_print(10, 42, foreground_color, 1, SCREEN_FONT_VGA, "Sat. 02/10/2021");
        screen_print(10, 58, foreground_color, 1, SCREEN_FONT_VGA, "arcticOS v0.2-alpha");
        screen_refresh();
    }
    return 0;
}