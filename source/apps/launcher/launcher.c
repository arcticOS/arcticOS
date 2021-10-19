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
 *
 * This is meant to run on RP2040-based boards.
 */
 
#include <arcticOS.h>

#include <hardware/arcticOS/keypad.h>

#include <arcticOS/graphics/primitives.h>
#include <arcticOS/graphics/ui.h>
#include <arcticOS/graphics/text.h>

#include <apps/launcher/launcher.h>
#include <apps/settings/settings.h>

char time_buffer[9];
char date_buffer[32];

void launcher_run() { 
    graphics_get_screen_size();
    
    while(1) {
        graphics_fill(COLOR_WHITE);

        // Get the actual time
        if(!rtc_get_datetime(&time) && ENFORCE_RTC_ENABLED) {
            system_panic("RTC Failure");
        }

        // Calculate time in 12-hour time and get it as a string
        int hour = time.hour;
        if(hour > 12) hour /= 2;
        if(hour == 0) hour = 12;
        if(time.hour > 12) sprintf(time_buffer, "%d:%d PM", hour / 2, time.min);
        else sprintf(time_buffer, "%d:%d AM", hour, time.min);

        // Get date as a string
        sprintf(date_buffer, "%s %s %d", weekday_names[time.dotw - 1], month_names[time.month - 1], time.day);

        ui_draw_element_outline(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
        ui_draw_element_inside(4, 4, SCREEN_WIDTH - 4, 70);
        ui_draw_element_inside(4, 78, SCREEN_WIDTH - 4, SCREEN_HEIGHT - 34);

        // Draw the time & date
        text_print_centered(10, COLOR_BLACK, FONT_DEFAULT_MEDIUM, &time_buffer);
        text_print_centered(42, COLOR_BLACK, FONT_DEFAULT, &date_buffer);

        // Draw the bottom bar
        text_print_centered(SCREEN_HEIGHT - 24, COLOR_BLACK, FONT_DEFAULT_TINY, STRING_MENU);

        if(keypad_is_button_pressed(BUTTON_O)) launcher_run_app_picker();

        graphics_refresh();
    }
}

void launcher_run_app_picker() {
    // Just a basic list of apps
    keypad_wait_for_no_button();
    const char* apps[1] = {STRING_APP_SETTINGS};
    int choice = ui_list_menu(STRING_MENU, apps, 1);
    if(choice == 0) settings_run();
}