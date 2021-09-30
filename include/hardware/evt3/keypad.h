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

#ifndef KEYPAD_H
#define KEYPAD_H

#include <stdio.h>
#include <pico/stdlib.h>
#include <hardware/gpio.h>

int keypad_buttons[8] = {7, 8, 9, 10, 11, 12, 13, 14};

void keypad_init() {
    // "X" pins are used to pull down "Y" pins to GND.
    // First 4 and last are "X" pins, others are "Y" pins

    for(int i = 0; i < 3; i++) {
        gpio_init(keypad_buttons[i]);
        gpio_set_dir(keypad_buttons[i], GPIO_OUT);
    }

    for(int i = 3; i < 8; i++) {
        gpio_init(keypad_buttons[i]);
        gpio_set_dir(keypad_buttons[i], GPIO_IN);
        gpio_pull_up(keypad_buttons[i]);
    }
}

#endif