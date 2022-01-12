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

#include <arcticOS.h>
#include <FreeRTOS/FreeRTOS.h>
#include <arcticOS/drivers/display/screen.h>
#include <arcticOS/graphics/ui.h>
#include <arcticOS/graphics/text.h>

// Kernel panic
void system_panic(const char* message) {
    vTaskSuspendAll();
    screen_fill(COLOR_RED);
    text_print(10, 56, COLOR_WHITE, FONT_DEFAULT_TINY, message); // Print error
    while(1) { // Disable global timer and flash PANIC! on screen
        text_print(10, 10, COLOR_WHITE, FONT_DEFAULT_LARGE, "PANIC!");
        screen_refresh();
        screen_backlight_on();
        sleep_ms(500);
        text_print(10, 10, COLOR_RED, FONT_DEFAULT_LARGE, "PANIC!");
        screen_refresh();
        screen_backlight_off();
        sleep_ms(500);
    }
}
