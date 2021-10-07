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

void settings_run() { // List submenus
    while(1) {
        flash_load_user_data(FLASH_OFFSET_SETTINGS, &flash_buffer[0]);
        const char* menu_items[4] = {STRING_ABOUT, STRING_THEME, STRING_SLEEP_TIME, STRING_ERASE_DATA};
        int choice = ui_list_menu(STRING_APP_SETTINGS, &menu_items, 4);
        if(choice == -1) return;
        else if(choice == 0) settings_run_about();
        else if(choice == 1) settings_run_theme_picker();
        else if(choice == 2) settings_run_sleep_time_picker();
        else if(choice == 3) settings_run_factory_reset();
        flash_write_user_data(FLASH_OFFSET_SETTINGS, &flash_buffer[0]);
        system_refresh_settings();
    }
}

void settings_run_about() {
    // This is based off the list menu code (ui/listmenu.c)
    // Just loops through and prints all needed about menu items
    while(1) {
        int font_height = font_character_height(SCREEN_FONT_DEFAULT);
        screen_fill(background_color);
        screen_print_centered(10, foreground_color, SCREEN_FONT_DEFAULT_MEDIUM, STRING_ABOUT);

        const char* items[1] = {BUILD_STRING};
        int count = 1;

        for(int i = 0; i < count; i++) {
            int y = (10 * (i + 1)) + (font_height * 2) + (i * font_height);
            if(y + font_height >= SCREEN_HEIGHT - font_height - 20) break;
            screen_print_centered(y, foreground_color, SCREEN_FONT_DEFAULT, items[i]);
        }

        screen_print(SCREEN_WIDTH - 10 - font_string_width(SCREEN_FONT_DEFAULT, STRING_BACK), SCREEN_HEIGHT - 26, foreground_color, SCREEN_FONT_DEFAULT, STRING_BACK);

        screen_refresh();

        if(KEYPAD_HAS_DPAD) {

        } else {
            if(keypad_is_button_pressed(BUTTON_E)) {
                keypad_wait_for_no_button();
                return;
            }
        }
    }
}

int settings_run_theme_picker() {
    screen_fill(background_color);
    const char* theme_menu[5] = {STRING_LIGHT, STRING_DARK};
    int result = ui_list_menu(STRING_THEME, &theme_menu, 2);
    if(result == -1) { keypad_wait_for_no_button(); return 1; }
    flash_buffer[FLASH_SETTINGS_THEME] = result;
    keypad_wait_for_no_button();
    return 0;
}

int settings_run_sleep_time_picker() {
    screen_fill(background_color);

    uint16_t sleep_times[4] = {0, 5000, 15000, 30000}; // These correspond to the string list below, times are in milliseconds
    const char* sleep_times_menu[4] = {STRING_DO_NOT_SLEEP, STRING_FIVE_SECONDS, STRING_FIFTEEN_SECONDS, STRING_THIRTY_SECONDS};

    int result = ui_list_menu(STRING_SLEEP_TIME, &sleep_times_menu, 4); // Basic list menu
    if(result == -1) { keypad_wait_for_no_button(); return 1; } // Return if the user clicked back
    uint16_t sleep_time = sleep_times[result]; // Cleans up the below code slightly + allows it to be more easily reused
    
    // Convert the uint16_t into two uint8_t variables and store them in the flash buffer
    flash_buffer[FLASH_SETTINGS_SLEEP_TIME] = sleep_time >> 8;
    flash_buffer[FLASH_SETTINGS_SLEEP_TIME + 1] = (uint8_t) sleep_time;

    keypad_wait_for_no_button();
    return 0;
}

void settings_run_factory_reset() {
    const char* menu_items[6] = {STRING_NO, STRING_NO, STRING_NO, STRING_NO, STRING_YES, STRING_NO}; // Shamelessly stolen from old Android bootloaders

    if(ui_list_menu(STRING_CONFIRM_ERASE_DATA, &menu_items, 6) == 4) { // Make sure the user wants to wipe the phone
        flash_erase_user_data(FLASH_OFFSET_SETTINGS); // Wipe the phone

        // Show a screen telling the user to restart, then hang the phone.
        // We do this so we can avoid issues relating to data accidentally sticking around after format.
        // TODO: Use small fonts, the "restart your device" line runs past the edge of the screen.
        screen_fill(SCREEN_COLOR_RED);
        screen_print(10, 10, foreground_color, SCREEN_FONT_DEFAULT, STRING_DATA_ERASED);
        screen_print(10, 26, foreground_color, SCREEN_FONT_DEFAULT, STRING_RESTART_DEVICE);
        screen_refresh();
        system_hang();
    }
}

void settings_run_oobe() {
    // TODO: Use small fonts, most of the text runs past the screen edges.
    keypad_wait_for_no_button();
    flash_load_user_data(FLASH_OFFSET_SETTINGS, &flash_buffer[0]);

    // Friendly boot screen
    screen_fill(background_color);
    screen_print_centered(30, foreground_color, SCREEN_FONT_DEFAULT_LARGE, STRING_HELLO);
    screen_print_centered(SCREEN_HEIGHT - 42, foreground_color, SCREEN_FONT_DEFAULT, STRING_PRESS_MIDDLE_BUTTON);
    screen_print_centered(SCREEN_HEIGHT - 26, foreground_color, SCREEN_FONT_DEFAULT, STRING_TO_SET_UP_PHONE);
    screen_refresh();
    while(!keypad_is_button_pressed(BUTTON_O)) {}
    keypad_wait_for_no_button();

    // Time until sleep
    screen_fill(background_color);
    screen_print_centered(30, foreground_color, SCREEN_FONT_DEFAULT, STRING_OOBE_SLEEP1);
    screen_print_centered(46, foreground_color, SCREEN_FONT_DEFAULT, STRING_OOBE_SLEEP2);
    screen_print_centered(62, foreground_color, SCREEN_FONT_DEFAULT, STRING_OOBE_SLEEP3);
    screen_print_centered(SCREEN_HEIGHT - 42, foreground_color, SCREEN_FONT_DEFAULT, STRING_PRESS_MIDDLE_BUTTON);
    screen_print_centered(SCREEN_HEIGHT - 26, foreground_color, SCREEN_FONT_DEFAULT, STRING_TO_CONTINUE);
    screen_refresh();
    while(!keypad_is_button_pressed(BUTTON_O)) {}
    keypad_wait_for_no_button();
    while(settings_run_sleep_time_picker()) {}

    // Theme
    screen_fill(background_color);
    screen_print_centered(30, foreground_color, SCREEN_FONT_DEFAULT, STRING_OOBE_THEME1);
    screen_print_centered(46, foreground_color, SCREEN_FONT_DEFAULT, STRING_OOBE_THEME2);
    screen_print_centered(62, foreground_color, SCREEN_FONT_DEFAULT, STRING_OOBE_THEME3);
    screen_print_centered(SCREEN_HEIGHT - 42, foreground_color, SCREEN_FONT_DEFAULT, STRING_PRESS_MIDDLE_BUTTON);
    screen_print_centered(SCREEN_HEIGHT - 26, foreground_color, SCREEN_FONT_DEFAULT, STRING_TO_CONTINUE);
    screen_refresh();
    while(!keypad_is_button_pressed(BUTTON_O)) {}
    keypad_wait_for_no_button();
    while(settings_run_theme_picker()) {}

    // Save the user's choices to flash
    flash_buffer[FLASH_SETTINGS_OOBE_COMPLETE] = 1;
    flash_write_user_data(FLASH_OFFSET_SETTINGS, &flash_buffer[0]);

    // Friendly outro screen
    screen_fill(background_color);
    screen_print_centered(30, foreground_color, SCREEN_FONT_DEFAULT_LARGE, STRING_ALL_SET);
    screen_print_centered(SCREEN_HEIGHT - 42, foreground_color, SCREEN_FONT_DEFAULT, STRING_PRESS_MIDDLE_BUTTON);
    screen_print_centered(SCREEN_HEIGHT - 26, foreground_color, SCREEN_FONT_DEFAULT, STRING_TO_USE_PHONE);
    screen_refresh();
    while(!keypad_is_button_pressed(BUTTON_O)) {}
    keypad_wait_for_no_button();
}