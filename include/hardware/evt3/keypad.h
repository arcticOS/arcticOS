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


char keypad_button_translation[5][3] = { // I don't even know what the fuck causes this bug but there's no way in hell I'm hunting it down right now
    {'*', 'O', 'E'},
    {'A', '2', '3'},
    {'1', '5', '6'},
    {'4', '8', '9'},
    {'7', '0', '#'}
};

void keypad_init() {
    // "X" pins are used to pull down "Y" pins to GND.
    // First 4 and last are "X" pins, others are "Y" pins

    for(int i = 3; i < 8; i++) {
        gpio_init(keypad_buttons[i]);
        gpio_set_dir(keypad_buttons[i], GPIO_OUT);
        gpio_put(keypad_buttons[i], 1);
    }

    for(int i = 0; i < 3; i++) {
        gpio_init(keypad_buttons[i]);
        gpio_set_dir(keypad_buttons[i], GPIO_IN);
        gpio_pull_up(keypad_buttons[i]);
    }
}

char keypad_get_button_pressed() {
    for(int y = 3; y < 8; y++) {
        gpio_put(keypad_buttons[y], 0);

        for(int x = 0; x < 3; x++) {
            if(!gpio_get(keypad_buttons[x])) return keypad_button_translation[y - 3][x];
        }

        gpio_put(keypad_buttons[y], 1);
    }

    return 0x00;
}

void keypad_wait_for_no_button() {
    while(1) {
        int good = 1;
        for(int y = 3; y < 8; y++) {
            gpio_put(keypad_buttons[y], 0);

            for(int x = 0; x < 3; x++) {
                if(!gpio_get(keypad_buttons[x])) good = 0;
            }

            gpio_put(keypad_buttons[y], 1);
        }
        if(good) return;
    }
}

char keypad_wait_for_button() {
    char button = 0x00;
    while(!button) {
        button = keypad_get_button_pressed();
    }
    keypad_wait_for_no_button();
    return button;
}

#endif