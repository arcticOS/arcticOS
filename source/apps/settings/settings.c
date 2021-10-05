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

void settings_run() {
    while(1) {
        flash_load_user_data(FLASH_OFFSET_SETTINGS, &flash_buffer);
        const char* menu_items[3] = {STRING_THEME, STRING_SLEEP_TIME, STRING_ERASE_DATA};
        int choice = ui_list_menu(STRING_APP_SETTINGS, &menu_items, 3);
        if(choice == -1) return;
        else if(choice == 0) settings_run_theme_picker();
        else if(choice == 1) settings_run_sleep_time_picker();
        else if(choice == 2) settings_run_factory_reset();
        flash_write_user_data(FLASH_OFFSET_SETTINGS, &flash_buffer);
        system_refresh_settings();
    }
}

int settings_run_theme_picker() {
    screen_fill(background_color);
    const char* theme_menu[5] = {STRING_LIGHT, STRING_DARK};
    int result = ui_list_menu(STRING_THEME, &theme_menu, 2);
    if(result == -1) return 1;
    flash_buffer[FLASH_SETTINGS_THEME] = result;
    return 0;
}

int settings_run_sleep_time_picker() {
    screen_fill(background_color);

    uint16_t sleep_time = 0;
    uint16_t sleep_times[5] = {5000, 15000, 30000, 60000, 120000};
    const char* sleep_times_menu[5] = {STRING_FIVE_SECONDS, STRING_FIFTEEN_SECONDS, STRING_THIRTY_SECONDS, STRING_ONE_MINUTE, STRING_TWO_MINUTES};
    int result = ui_list_menu(STRING_SLEEP_TIME, &sleep_times_menu, 5);
    if(result == -1) return 1;
    sleep_time = sleep_times[result];
    flash_buffer[FLASH_SETTINGS_SLEEP_TIME] = sleep_time >> 8;
    flash_buffer[FLASH_SETTINGS_SLEEP_TIME + 1] = (uint8_t) sleep_time;
    return 0;
}

void settings_run_factory_reset() {
    const char* menu_items[6] = {STRING_NO, STRING_NO, STRING_NO, STRING_NO, STRING_YES, STRING_NO};
    if(ui_list_menu(STRING_CONFIRM_ERASE_DATA, &menu_items, 6) == 4) {
        flash_erase_user_data(FLASH_OFFSET_SETTINGS);
        screen_fill(SCREEN_COLOR_RED);
        screen_print(10, 10, foreground_color, 1, SCREEN_FONT_VGA, STRING_DATA_ERASED);
        screen_print(10, 26, foreground_color, 1, SCREEN_FONT_VGA, STRING_RESTART_DEVICE);
        screen_refresh();
        system_hang();
    }
}

void settings_run_oobe() {
    keypad_wait_for_no_button();
    flash_load_user_data(FLASH_OFFSET_SETTINGS, &flash_buffer);

    screen_fill(background_color);
    screen_print_centered(30, foreground_color, 3, SCREEN_FONT_VGA, STRING_HELLO);
    screen_print_centered(SCREEN_HEIGHT - 42, foreground_color, 1, SCREEN_FONT_VGA, STRING_PRESS_MIDDLE_BUTTON);
    screen_print_centered(SCREEN_HEIGHT - 26, foreground_color, 1, SCREEN_FONT_VGA, STRING_TO_SET_UP_PHONE);
    screen_refresh();
    while(!keypad_is_button_pressed(BUTTON_O)) {}
    keypad_wait_for_no_button();

    // Time until sleep
    screen_fill(background_color);
    screen_print_centered(30, foreground_color, 1, SCREEN_FONT_VGA, STRING_OOBE_SLEEP1);
    screen_print_centered(46, foreground_color, 1, SCREEN_FONT_VGA, STRING_OOBE_SLEEP2);
    screen_print_centered(62, foreground_color, 1, SCREEN_FONT_VGA, STRING_OOBE_SLEEP3);
    screen_print_centered(SCREEN_HEIGHT - 42, foreground_color, 1, SCREEN_FONT_VGA, STRING_PRESS_MIDDLE_BUTTON);
    screen_print_centered(SCREEN_HEIGHT - 26, foreground_color, 1, SCREEN_FONT_VGA, STRING_TO_CONTINUE);
    screen_refresh();
    while(!keypad_is_button_pressed(BUTTON_O)) {}
    keypad_wait_for_no_button();
    while(settings_run_sleep_time_picker()) {}

    // Theme
    screen_fill(background_color);
    screen_print_centered(30, foreground_color, 1, SCREEN_FONT_VGA, STRING_OOBE_THEME1);
    screen_print_centered(46, foreground_color, 1, SCREEN_FONT_VGA, STRING_OOBE_THEME2);
    screen_print_centered(62, foreground_color, 1, SCREEN_FONT_VGA, STRING_OOBE_THEME3);
    screen_print_centered(SCREEN_HEIGHT - 42, foreground_color, 1, SCREEN_FONT_VGA, STRING_PRESS_MIDDLE_BUTTON);
    screen_print_centered(SCREEN_HEIGHT - 26, foreground_color, 1, SCREEN_FONT_VGA, STRING_TO_CONTINUE);
    screen_refresh();
    while(!keypad_is_button_pressed(BUTTON_O)) {}
    keypad_wait_for_no_button();
    while(settings_run_theme_picker()) {}

    flash_buffer[FLASH_SETTINGS_OOBE_COMPLETE] = 1;
    flash_write_user_data(FLASH_OFFSET_SETTINGS, &flash_buffer);

    screen_fill(background_color);
    screen_print_centered(30, foreground_color, 3, SCREEN_FONT_VGA, STRING_ALL_SET);
    screen_print_centered(SCREEN_HEIGHT - 42, foreground_color, 1, SCREEN_FONT_VGA, STRING_PRESS_MIDDLE_BUTTON);
    screen_print_centered(SCREEN_HEIGHT - 26, foreground_color, 1, SCREEN_FONT_VGA, STRING_TO_USE_PHONE);
    screen_refresh();
    while(!keypad_is_button_pressed(BUTTON_O)) {}
    keypad_wait_for_no_button();
}