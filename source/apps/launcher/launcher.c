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

#include <hardware/arcticOS/screen.h>
#include <hardware/arcticOS/keypad.h>

#include <apps/launcher/launcher.h>

char time_buffer[9];
char date_buffer[32];

void start_launcher() { 
    while(1) {
        screen_fill(background_color);

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
        sprintf(date_buffer, "%s, %s %d", weekday_names[time.dotw - 1], month_names[time.month - 1], time.day);

        screen_print(10, 10, foreground_color, 2, SCREEN_FONT_VGA, &time_buffer);
        screen_print(10, 42, foreground_color, 1, SCREEN_FONT_VGA, &date_buffer);
        screen_print(10, 58, foreground_color, 1, SCREEN_FONT_VGA, "arcticOS v0.2-alpha");

        if(keypad_is_button_pressed(BUTTON_6)) screen_putchar(20, 80, foreground_color, 1, SCREEN_FONT_VGA, 'G');
        screen_refresh();
    }
}