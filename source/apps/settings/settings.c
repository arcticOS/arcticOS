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
#include <hardware/arcticOS/keypad.h>
#include <hardware/arcticOS/flash.h>

#include <apps/settings/settings.h>

#include <ui/listmenu.h>

void settings_run_factory_reset() {
    const char* menu_items[6] = {"No", "No", "No", "No", "Yes", "No"};
    if(ui_list_menu("Erase Data?", &menu_items, 6) == 4) {
        flash_erase_user_data(FLASH_OFFSET_SETTINGS);
        screen_fill(SCREEN_COLOR_RED);
        screen_print(10, 10, foreground_color, 1, SCREEN_FONT_VGA, "Data erased.");
        screen_print(10, 26, foreground_color, 1, SCREEN_FONT_VGA, "Restart your device.");
        screen_refresh();
        return;
    }
}

void settings_run_oobe() {
    flash_load_user_data(FLASH_OFFSET_SETTINGS, &flash_buffer);

    screen_fill(background_color);
    screen_print_centered(30, foreground_color, 3, SCREEN_FONT_VGA, "Hello!");
    screen_print_centered(SCREEN_HEIGHT - 42, foreground_color, 1, SCREEN_FONT_VGA, "Press the left button");
    screen_print_centered(SCREEN_HEIGHT - 26, foreground_color, 1, SCREEN_FONT_VGA, "to set up your phone.");
    screen_refresh();
    while(!keypad_is_button_pressed(BUTTON_A)) {}
    keypad_wait_for_no_button();

    // Time until sleep
    screen_fill(background_color);
    screen_print_centered(30, foreground_color, 1, SCREEN_FONT_VGA, "First, pick how long");
    screen_print_centered(46, foreground_color, 1, SCREEN_FONT_VGA, "your phone should wait");
    screen_print_centered(62, foreground_color, 1, SCREEN_FONT_VGA, "before it goes to sleep.");
    screen_print_centered(SCREEN_HEIGHT - 42, foreground_color, 1, SCREEN_FONT_VGA, "Press the left button");
    screen_print_centered(SCREEN_HEIGHT - 26, foreground_color, 1, SCREEN_FONT_VGA, "to continue.");
    screen_refresh();
    while(!keypad_is_button_pressed(BUTTON_A)) {}
    keypad_wait_for_no_button();

    uint16_t sleep_time = 0;
    uint16_t sleep_times[5] = {5000, 15000, 30000, 60000, 120000};
    const char* sleep_times_menu[5] = {"5 Seconds", "15 Seconds", "30 Seconds", "1 Minute", "2 Minutes"};
    sleep_time = sleep_times[ui_list_menu("Sleep Time", &sleep_times_menu, 5)];
    flash_buffer[FLASH_SETTINGS_SLEEP_TIME] = sleep_time >> 8;
    flash_buffer[FLASH_SETTINGS_SLEEP_TIME + 1] = (uint8_t) sleep_time;

    // Theme
    screen_fill(background_color);
    screen_print_centered(30, foreground_color, 1, SCREEN_FONT_VGA, "Next, pick whether you");
    screen_print_centered(46, foreground_color, 1, SCREEN_FONT_VGA, "want your phone to have a");
    screen_print_centered(62, foreground_color, 1, SCREEN_FONT_VGA, "light theme or a dark theme.");
    screen_print_centered(SCREEN_HEIGHT - 42, foreground_color, 1, SCREEN_FONT_VGA, "Press the left button");
    screen_print_centered(SCREEN_HEIGHT - 26, foreground_color, 1, SCREEN_FONT_VGA, "to continue.");
    screen_refresh();
    while(!keypad_is_button_pressed(BUTTON_A)) {}
    keypad_wait_for_no_button();
    const char* theme_menu[5] = {"Light", "Dark"};
    flash_buffer[FLASH_SETTINGS_THEME] = ui_list_menu("Theme", &theme_menu, 2);

    flash_buffer[FLASH_SETTINGS_OOBE_COMPLETE] = 1;
    flash_write_user_data(FLASH_OFFSET_SETTINGS, &flash_buffer);

    screen_fill(background_color);
    screen_print_centered(30, foreground_color, 3, SCREEN_FONT_VGA, "All set!");
    screen_print_centered(SCREEN_HEIGHT - 42, foreground_color, 1, SCREEN_FONT_VGA, "Press the left button");
    screen_print_centered(SCREEN_HEIGHT - 26, foreground_color, 1, SCREEN_FONT_VGA, "to use your phone.");
    screen_refresh();
    while(!keypad_is_button_pressed(BUTTON_A)) {}
    keypad_wait_for_no_button();
}