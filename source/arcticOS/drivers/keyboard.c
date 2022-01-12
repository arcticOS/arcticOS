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

#if defined(EVT3) | defined(EVT4)
#include <hardware/gpio.h>

int keyboard_buttons[8] = {7, 8, 9, 10, 11, 12, 13, 14};

void keyboard_init() {
    for(int i = 3; i < 8; i++) {
        gpio_init(keyboard_buttons[i]);
        gpio_set_dir(keyboard_buttons[i], GPIO_OUT);
        gpio_put(keyboard_buttons[i], 1);
    }

    for(int i = 0; i < 3; i++) {
        gpio_init(keyboard_buttons[i]);
        gpio_set_dir(keyboard_buttons[i], GPIO_IN);
        gpio_pull_up(keyboard_buttons[i]);
    }
}

char keyboard_get_character() {
    char translation[5][3] = {
        {'A', 'O', 'E'},
        {'1', '2', '3'},
        {'4', '5', '6'},
        {'7', '8', '9'},
        {'*', '0', '#'}
    };

    for(int y = 3; y < 8; y++) {
        gpio_put(keyboard_buttons[y], 0); // Set the Y pin low
        busy_wait_us(200); // Bug fix(?)

        for(int x = 0; x < 3; x++) { // Scan the X pins and set the needed bits in buttons_pressed
            busy_wait_us(200); // Bug fix(?)
            if(!gpio_get(keyboard_buttons[x])) return translation[y - 3][x];
        }

        gpio_put(keyboard_buttons[y], 1); // Set the Y pin high
        busy_wait_us(200); // Bug fix(?)
    }
}

int keyboard_is_pressed(char character) {
    char translation[5][3] = {
        {'A', 'O', 'E'},
        {'1', '2', '3'},
        {'4', '5', '6'},
        {'7', '8', '9'},
        {'*', '0', '#'}
    };

    for(int y = 3; y < 8; y++) {
        gpio_put(keyboard_buttons[y], 0); // Set the Y pin low
        busy_wait_us(200); // Bug fix(?)

        for(int x = 0; x < 3; x++) { // Scan the X pins and set the needed bits in buttons_pressed
            busy_wait_us(200); // Bug fix(?)
            if(!gpio_get(keyboard_buttons[x]) && character == translation[y - 3][x]) return 1;
        }

        gpio_put(keyboard_buttons[y], 1); // Set the Y pin high
        busy_wait_us(200); // Bug fix(?)
    }

    return 0;
}

#endif