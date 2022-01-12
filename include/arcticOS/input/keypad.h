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

#include <pico/stdlib.h>

#define BUTTON_A 0b0000000000000001
#define BUTTON_O 0b0000000000000010
#define BUTTON_E 0b0000000000000100
#define BUTTON_1 0b0000000000001000
#define BUTTON_2 0b0000000000010000
#define BUTTON_3 0b0000000000100000
#define BUTTON_4 0b0000000001000000
#define BUTTON_5 0b0000000010000000
#define BUTTON_6 0b0000000100000000
#define BUTTON_7 0b0000001000000000
#define BUTTON_8 0b0000010000000000
#define BUTTON_9 0b0000100000000000
#define BUTTON_STAR 0b0001000000000000
#define BUTTON_0 0b0010000000000000
#define BUTTON_POUND 0b0100000000000000

int keypad_no_buttons_pressed();
int keypad_is_button_pressed(uint16_t bitmask);
void keypad_wait_for_no_button();