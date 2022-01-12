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

#include <hardware/arcticOS/keypad.h>
#include <hardware/arcticOS/flash.h>

#include <arcticOS/graphics/primitives.h>
#include <arcticOS/graphics/ui.h>
#include <arcticOS/graphics/text.h>

#include <apps/settings/settings.h>

void settings_run() { // List submenus
    graphics_get_screen_size();

    while(1) {
        flash_load_user_data(FLASH_OFFSET_SETTINGS, &flash_buffer[0]);
        const char* menu_items[5] = {STRING_ABOUT, STRING_SLEEP_TIME, STRING_THEME, STRING_ERASE_DATA, STRING_OVERCLOCK};
        int choice = ui_list_menu(STRING_APP_SETTINGS, &menu_items, 5);
        
        switch(choice) {
            case -1:
                return;
            case 0:
                settings_run_about();
                break;
            case 1:
                settings_run_sleep_time_picker();
                break;
            case 2:
                settings_run_theme_picker();
                break;
            case 3:
                settings_run_factory_reset();
                break;
            case 4:
                settings_run_overclock_menu();
                break;
        }

        flash_write_user_data(FLASH_OFFSET_SETTINGS, &flash_buffer[0]);
        system_refresh_settings();
    }
}

void settings_run_about() {
    graphics_get_screen_size();

    // This is based off the list menu code (ui/listmenu.c)
    // Just loops through and prints all needed about menu items
    while(1) {
        const char* items[1] = {BUILD_STRING};
        int count = 1;

        int font_height = text_character_height(FONT_DEFAULT_TINY);

        ui_draw_element_outline(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
        ui_draw_element_inside(4, 4, SCREEN_WIDTH - 4, 42);
        ui_draw_element_inside(4, 50, SCREEN_WIDTH - 4, SCREEN_HEIGHT - 34);

        text_print_centered(10, COLOR_BLACK, FONT_DEFAULT_MEDIUM, STRING_ABOUT);

        for(int i = 0; i < count; i++) { // Loop through all items
            // Draw text
            int y = 50 + (i * font_height);
            if(y + font_height >= SCREEN_HEIGHT - font_height - 20) break;
            text_print(10, y, COLOR_BLACK, FONT_DEFAULT_TINY, items[i]);
        }

        text_print(SCREEN_WIDTH - 10 - text_string_width(FONT_DEFAULT, STRING_BACK), SCREEN_HEIGHT - 24, COLOR_BLACK, FONT_DEFAULT, STRING_BACK);

        graphics_refresh();

        if(KEYPAD_HAS_DPAD) {

        } else {
            if(keypad_is_button_pressed(BUTTON_E)) {
                keypad_wait_for_no_button();
                return;
            }
        }
    }
}

int settings_run_sleep_time_picker() {
    graphics_get_screen_size();
    graphics_fill(COLOR_WHITE);

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

int settings_run_theme_picker() {
    graphics_get_screen_size();
    graphics_fill(COLOR_WHITE);

    const char* theme_menu[4] = {STRING_GREEN, STRING_ORANGE, STRING_BLUE};

    int result = ui_list_menu(STRING_THEME, &theme_menu, 2); // Basic list menu
    if(result == -1) { keypad_wait_for_no_button(); return 1; } // Return if the user clicked back
    
    // Convert the uint16_t into two uint8_t variables and store them in the flash buffer
    flash_buffer[FLASH_SETTINGS_THEME] = result;

    keypad_wait_for_no_button();
    return 0;
}

int settings_run_overclock_menu() {
    graphics_get_screen_size();
    graphics_fill(COLOR_WHITE);

    const char* menu[5] = {STRING_OC_50MHZ, STRING_OC_100MHZ, STRING_OC_BASE, STRING_OC_200MHZ, STRING_OC_250MHZ};

    int result = ui_list_menu(STRING_OVERCLOCK, &menu, 5); // Basic list menu
    if(result == -1) { keypad_wait_for_no_button(); return 1; } // Return if the user clicked back
    
    // Convert the uint16_t into two uint8_t variables and store them in the flash buffer
    flash_buffer[FLASH_SETTINGS_CLOCK] = result;

    keypad_wait_for_no_button();
}

void settings_run_factory_reset() {
    graphics_get_screen_size();
    const char* menu_items[6] = {STRING_NO, STRING_NO, STRING_NO, STRING_NO, STRING_YES, STRING_NO}; // Shamelessly stolen from old Android bootloaders

    if(ui_list_menu(STRING_CONFIRM_ERASE_DATA, &menu_items, 6) == 4) { // Make sure the user wants to wipe the phone
        flash_erase_user_data(FLASH_OFFSET_SETTINGS); // Wipe the phone

        // Show a screen telling the user to restart, then hang the phone.
        // We do this so we can avoid issues relating to data accidentally sticking around after format.
        graphics_fill(COLOR_RED);
        text_print(10, 10, COLOR_BLACK, FONT_DEFAULT_TINY, STRING_DATA_ERASED);
        text_print(10, 26, COLOR_BLACK, FONT_DEFAULT_TINY, STRING_RESTART_DEVICE);
        screen_refresh();
        system_hang();
    }
}

void settings_run_oobe() {
    graphics_get_screen_size();
    keypad_wait_for_no_button();
    flash_load_user_data(FLASH_OFFSET_SETTINGS, &flash_buffer[0]);

    // Load in theme
    flash_buffer[FLASH_SETTINGS_THEME] = 1;
    flash_write_user_data(FLASH_OFFSET_SETTINGS, &flash_buffer[0]);
    flash_load_user_data(FLASH_OFFSET_SETTINGS, &flash_buffer[0]);
    uint16_t foreground_color = get_foreground_color();
    uint16_t background_color = get_background_color();

    // Friendly boot screen
    graphics_fill(background_color);
    text_print_centered(30, foreground_color, FONT_DEFAULT_MEDIUM, STRING_HELLO);
    text_print_centered(SCREEN_HEIGHT - 42, foreground_color, FONT_DEFAULT_TINY, STRING_PRESS_MIDDLE_BUTTON);
    text_print_centered(SCREEN_HEIGHT - 26, foreground_color, FONT_DEFAULT_TINY, STRING_TO_SET_UP_PHONE);
    graphics_refresh();
    while(!keypad_is_button_pressed(BUTTON_O)) {}
    keypad_wait_for_no_button();

    // Friendly warning
    graphics_fill(background_color);
    text_print_centered(30, foreground_color, FONT_DEFAULT_TINY, STRING_OOBE_PROTOTYPE1);
    text_print_centered(46, foreground_color, FONT_DEFAULT_TINY, STRING_OOBE_PROTOTYPE2);
    text_print_centered(62, foreground_color, FONT_DEFAULT_TINY, STRING_OOBE_PROTOTYPE3);
    text_print_centered(SCREEN_HEIGHT - 42, foreground_color, FONT_DEFAULT_TINY, STRING_PRESS_MIDDLE_BUTTON);
    text_print_centered(SCREEN_HEIGHT - 26, foreground_color, FONT_DEFAULT_TINY, STRING_TO_CONTINUE);
    graphics_refresh();
    while(!keypad_is_button_pressed(BUTTON_O)) {}
    keypad_wait_for_no_button();

    // Time until sleep
    graphics_fill(background_color);
    text_print_centered(30, foreground_color, FONT_DEFAULT_TINY, STRING_OOBE_SLEEP1);
    text_print_centered(46, foreground_color, FONT_DEFAULT_TINY, STRING_OOBE_SLEEP2);
    text_print_centered(62, foreground_color, FONT_DEFAULT_TINY, STRING_OOBE_SLEEP3);
    text_print_centered(SCREEN_HEIGHT - 42, foreground_color, FONT_DEFAULT_TINY, STRING_PRESS_MIDDLE_BUTTON);
    text_print_centered(SCREEN_HEIGHT - 26, foreground_color, FONT_DEFAULT_TINY, STRING_TO_CONTINUE);
    graphics_refresh();
    while(!keypad_is_button_pressed(BUTTON_O)) {}
    keypad_wait_for_no_button();
    while(settings_run_sleep_time_picker()) {}

    // Save the user's choices to flash
    flash_buffer[FLASH_SETTINGS_OOBE_COMPLETE] = 1;
    flash_write_user_data(FLASH_OFFSET_SETTINGS, &flash_buffer[0]);

    // Friendly outro screen
    graphics_fill(background_color);
    text_print_centered(30, foreground_color, FONT_DEFAULT_MEDIUM, STRING_ALL_SET);
    text_print_centered(SCREEN_HEIGHT - 42, foreground_color, FONT_DEFAULT_TINY, STRING_PRESS_MIDDLE_BUTTON);
    text_print_centered(SCREEN_HEIGHT - 26, foreground_color, FONT_DEFAULT_TINY, STRING_TO_USE_PHONE);
    graphics_refresh();
    while(!keypad_is_button_pressed(BUTTON_O)) {}
    keypad_wait_for_no_button();
}