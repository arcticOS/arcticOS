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
//#include <hardware/cellular.h> // EVT3 doesn't have cellular and EVT4 isn't ready yet
#include <hardware/keypad.h>

// TODO: Replace this with a hardware/screen.h thing
#include <hardware/ili9341/mode2.h>
#include <hardware/ili9341/ili9341.h>

// Initialise arcticOS
int main(void) {
    // Init cellular
    //cellular_init();

    // Init keypad
    keypad_init();

    // Init screen
    ili9341_init();
    ili9341_backlight(1);
    mode2_init();

    while(1) {
        mode2_clear(background_color);
        mode2_draw_string(10, 10, 2, foreground_color, "12:04 PM");
        mode2_draw_string(10, 42, 1, foreground_color, "Sat. 02/10/2021");
        mode2_draw_string(10, 58, 1, foreground_color, "arcticOS 0.2a Demo");
        mode2_render();
    }
    return 0;
}