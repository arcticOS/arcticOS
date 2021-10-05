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

void system_panic(const char* message) {
    sleep_timer_goal = 0;
    screen_fill(SCREEN_COLOR_RED);
    screen_print(10, 56, SCREEN_COLOR_WHITE, 1, SCREEN_FONT_VGA, message);
    while(1) {
        enable_global_timer = 0;
        screen_print(10, 10, SCREEN_COLOR_WHITE, 3, SCREEN_FONT_VGA, "PANIC!");
        screen_refresh();
        sleep_ms(500);
        screen_print(10, 10, SCREEN_COLOR_RED, 3, SCREEN_FONT_VGA, "PANIC!");
        screen_refresh();
        sleep_ms(500);
    }
}