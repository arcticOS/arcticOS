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

#include <arcticOS.h>

#include <hardware/arcticOS/screen.h>

void system_sleep() {
    screen_backlight_off();
    while(1) {
        sleep_ms(10);
        if(!keypad_no_buttons_pressed()) { // Button is pressed, wake up
            screen_backlight_on();
            system_reset_sleep_timer();
            return;
        }
    }
}

void system_set_sleep_timer(int ms) {
    sleep_timer_goal = ms;
}

void system_reset_sleep_timer() {
    sleep_timer_last = time_us_64();
}

void system_sleep_ok() {
    if(!sleep_timer_goal) return;
    if((time_us_64() - sleep_timer_last) / 1000 >= sleep_timer_goal) {
        system_sleep();
    } 
}
