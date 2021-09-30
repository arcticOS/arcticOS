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
 * This is meant to run on EVT 3, which is based on the reference schematic for the RP2040 chip.
 */

// CHANGE THE LINE BELOW TO CHANGE LANGUAGE
#include <strings/en-CA.h>

#include <arcticOS.h>

// Used for I/O
#include <stdio.h>
#include <pico/stdlib.h>
#include <hardware/spi.h>

// Used for interfacing with other hardware on motherboard
#include <hardware/cellular.h>
#include <hardware/keypad.h>
#include <hardware/ili9341/mode2.h>
#include <hardware/ili9341/ili9341.h>

// Initialise arcticOS
int main(void) {
    stdio_init_all();
    printf(STRING_HELLO_WORLD);

    // Init cellular
    cellular_init(20, 21, CELLULAR_DEFAULT_BAUDRATE, CELLULAR_DEFAULT_UART);

    // Init keypad
    keypad_init(7, 8, 9, 10, 11, 12, 13, 14, 15);

    // Init screen
    ili9341_init();
    mode2_init();
    return 0;
}