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

#include <arcticOS/input/keypad.h>
#include <arcticOS/kernel/syscall.h>

int keypad_is_button_pressed(uint16_t bitmask) {
    int result = 0;
    do_returning_system_call(2, 0, 0, bitmask, 0, &result);
    return result;
}

int keypad_no_buttons_pressed() {
    int result = 0;
    do_returning_system_call(2, 0, 1, 0, 0, &result);
    return result;
}

void keypad_wait_for_no_button() {
    while(1) {
        int result = 0;
        do_returning_system_call(2, 0, 1, 0, 0, &result);
        if(result) return;
    }
}