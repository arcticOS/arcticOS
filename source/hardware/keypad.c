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

#include <hardware/arcticOS/keypad.h>

#if defined(EVT3)
#include <stdio.h>
#include <pico/stdlib.h>
#include <hardware/gpio.h>

int keypad_buttons[8] = {7, 8, 9, 10, 11, 12, 13, 14};

uint16_t buttons_pressed = 0;
char characters_pressed[16];

uint16_t keypad_button_matrix[5][3] = { // I don't even know what the fuck causes this bug but there's no way in hell I'm hunting it down right now
    {BUTTON_A, BUTTON_O, BUTTON_E},
    {BUTTON_1, BUTTON_2, BUTTON_3},
    {BUTTON_4, BUTTON_5, BUTTON_6},
    {BUTTON_7, BUTTON_8, BUTTON_9},
    {BUTTON_STAR, BUTTON_0, BUTTON_POUND}
};

char keypad_button_translation[5][3] = {
    {'A', 'O', 'E'},
    {'1', '2', '3'},
    {'4', '5', '6'},
    {'7', '8', '9'},
    {'*', '0', '#'},
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

void keypad_refresh() {
    buttons_pressed = 0x0000;
    for(int y = 3; y < 8; y++) {
        gpio_put(keypad_buttons[y], 0);
        busy_wait_us(200);

        for(int x = 0; x < 3; x++) {
            busy_wait_us(200);
            if(!gpio_get(keypad_buttons[x])) {
                buttons_pressed |= keypad_button_matrix[y - 3][x];
                characters_pressed[(y * 3) + x] = keypad_button_translation[y - 3][x];
            } else characters_pressed[(y * 3) + x] = 0x00;
        }

        gpio_put(keypad_buttons[y], 1);
        busy_wait_us(200);
    }
}

bool keypad_no_buttons_pressed() {
    keypad_refresh();
    return buttons_pressed == 0x0000;
}

bool keypad_is_character_pressed(char character){ 
    keypad_refresh();
    for(int i = 0; i < 16; i++) {
        if(characters_pressed[i] == character) return true;
    }
    return false;
}

bool keypad_is_button_pressed(uint16_t button){ 
    keypad_refresh();
    return buttons_pressed & button;
}

void keypad_wait_for_no_button() {
    while(buttons_pressed) {
        keypad_refresh();
    }
}
#endif