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

int keypad_buttons[9];

void keypad_init(int x0, int x1, int x2, int x3, int y0, int y1, int y2, int y3, int ok) {
    // "X" pins are used to pull down "Y" pins to GND.

    keypad_buttons[0] = x0;
    keypad_buttons[1] = x1;
    keypad_buttons[2] = x2;
    keypad_buttons[3] = x3;
    keypad_buttons[4] = y0;
    keypad_buttons[5] = y1;
    keypad_buttons[6] = y2;
    keypad_buttons[7] = y3;
    keypad_buttons[8] = ok;

    for(int i = 0; i < 4; i++) {
        gpio_init(keypad_buttons[i]);
        gpio_set_dir(keypad_buttons[i], GPIO_OUT);
    }

    // The "OK" pin is also an "X" pin.
    gpio_init(ok);
    gpio_set_dir(ok, GPIO_OUT);

    for(int i = 4; i < 8; i++) {
        gpio_init(keypad_buttons[i]);
        gpio_set_dir(keypad_buttons[i], GPIO_IN);
        gpio_pull_up(keypad_buttons[i]);
    }
}

#endif