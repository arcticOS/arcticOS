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
#include <arcticOS/graphics/primitives.h>
#include <arcticOS/graphics/ui.h>
#include <arcticOS/graphics/text.h>
#include <arcticOS/input/keypad.h>

// Kernel panic
void system_panic(const char* message) {
    system_disable_interrupts();
    sleep_timer_goal = 0;
    graphics_fill(COLOR_RED);
    text_print(10, 56, COLOR_WHITE, FONT_DEFAULT_TINY, message); // Print error
    while(1) { // Disable global timer and flash PANIC! on screen
        enable_global_timer = 0;
        text_print(10, 10, COLOR_WHITE, FONT_DEFAULT_LARGE, "PANIC!");
        graphics_refresh();
        screen_backlight_on();
        sleep_ms(500);
        text_print(10, 10, COLOR_RED, FONT_DEFAULT_LARGE, "PANIC!");
        graphics_refresh();
        screen_backlight_off();
        sleep_ms(500);
    }
}

// Kill interrupts and stop running.
void system_hang() {
    system_disable_interrupts();
    while(1) {}
}

void system_break(const char* message) {
    system_disable_interrupts();
    sleep_timer_goal = 0;
    graphics_fill(COLOR_RED);
    text_print(10, 56, COLOR_WHITE, FONT_DEFAULT_TINY, message); // Print error
    keypad_wait_for_no_button();
    while(!keypad_is_button_pressed(BUTTON_E)) { // Disable global timer and flash PANIC! on screen
        enable_global_timer = 0;
        text_print(10, 10, COLOR_WHITE, FONT_DEFAULT_LARGE, "BREAK!");
        graphics_refresh();
        screen_backlight_off();
        sleep_ms(500);
        text_print(10, 10, COLOR_RED, FONT_DEFAULT_LARGE, "BREAK!");
        graphics_refresh();
        screen_backlight_on();
        sleep_ms(500);
    }
    enable_global_timer = 1;
    system_enable_interrupts();
}