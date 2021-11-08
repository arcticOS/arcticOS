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

#include <arcticOS/graphics/primitives.h>
#include <arcticOS/graphics/ui.h>
#include <arcticOS/graphics/text.h>

#include <arcticOS/input/keypad.h>

#include <arcticOS/kernel/flash.h>

#include <arcticOS/strings/en-CA.h> // TODO: Find a better solution

void ui_draw_element_outline(uint16_t x, uint16_t y, uint16_t x2, uint16_t y2) {
    switch(flash_get_byte(FLASH_OFFSET_SETTINGS + FLASH_SETTINGS_THEME)) {
        case 0: // Redmond
            graphics_filled_rect(x, y, x2, y2, COLOR_GREY); // Background
            
            // Top & left side (White + Light Grey)
            graphics_fasthline(x, y, x2 - 1, COLOR_WHITE);
            graphics_fastvline(x, y, y2 - 1, COLOR_WHITE);
            graphics_fasthline(x + 1, y + 1, x2 - 1, COLOR_LIGHT_GREY);
            graphics_fastvline(x + 1, y + 1, y2 - 2, COLOR_LIGHT_GREY);

            // Bottom & right side (Black + Dark Grey)
            graphics_fasthline(x, y2, x2, COLOR_BLACK);
            graphics_fastvline(x2, y, y2, COLOR_BLACK);
            graphics_fasthline(x + 1, y2 - 1, x2 - 1, COLOR_DARK_GREY);
            graphics_fastvline(x2 - 1, y + 1, y2 - 1, COLOR_DARK_GREY);
            break;
        case 1: // Flat
            graphics_filled_rect(x, y, x2, y2, COLOR_BLACK);
            break;
    }
}

void ui_draw_element_inside(uint16_t x, uint16_t y, uint16_t x2, uint16_t y2) {
    switch(flash_get_byte(FLASH_OFFSET_SETTINGS + FLASH_SETTINGS_THEME)) {
        case 0: // Redmond
            graphics_filled_rect(x, y, x2, y2, COLOR_WHITE); // Background

            // Top & left side (Black + Dark Grey)
            graphics_fasthline(x, y, x2, COLOR_DARK_GREY);
            graphics_fastvline(x, y, y2, COLOR_DARK_GREY);
            graphics_fasthline(x + 1, y + 1, x2 - 1, COLOR_BLACK);
            graphics_fastvline(x + 1, y + 1, y2 - 1, COLOR_BLACK);

            // Bottom & right side (White + Light Grey)
            graphics_fasthline(x, y2, x2, COLOR_WHITE);
            graphics_fastvline(x2, y, y2, COLOR_WHITE);
            graphics_fasthline(x + 1, y2 - 1, x2 - 1, COLOR_LIGHT_GREY);
            graphics_fastvline(x2 - 1, y + 1, y2 - 1, COLOR_LIGHT_GREY);
            break;
        case 1: // Flat
            graphics_rect(x, y, x2, y2, COLOR_WHITE);
            break;
    }
}

void ui_draw_button(uint16_t x, uint16_t y, uint16_t x2, uint16_t y2, const char* text) {
    ui_draw_element_outline(x, y, x2, y2);
}

void ui_draw_button_pressed(uint16_t x, uint16_t y, uint16_t x2, uint16_t y2, const char* text) {

}

int ui_list_menu(const char* title, char** items, int count) {
    uint16_t background_color = get_background_color();
    uint16_t foreground_color = get_foreground_color();
    uint16_t accent_color = get_accent_color();
    int selected = 0;

    while(1) {
        int font_height = text_character_height(FONT_DEFAULT_TINY);

        ui_draw_element_outline(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
        ui_draw_element_inside(4, 4, SCREEN_WIDTH - 4, 42);
        ui_draw_element_inside(4, 50, SCREEN_WIDTH - 4, SCREEN_HEIGHT - 34);

        text_print_centered(14, foreground_color, FONT_DEFAULT_MEDIUM, title);

        for(int i = 0; i < count; i++) { // Loop through all items
            // Draw text
            int y = 51 + (i * font_height);
            if(y + font_height >= SCREEN_HEIGHT - font_height - 20) break;
            text_print(10, y + 1, foreground_color, FONT_DEFAULT_TINY, items[i]);

            // Draw a line under the current line of text
            if(i == selected) {
                graphics_filled_rect(6, y + 1, SCREEN_WIDTH - 5, y + 1 + font_height, accent_color);
                text_print(10, y + 1, COLOR_WHITE, FONT_DEFAULT_TINY, items[i]);
            }
        }

        // Draw hint bar
        text_print_centered(SCREEN_HEIGHT - 24, foreground_color, FONT_DEFAULT_SMALL, STRING_SELECT);
        text_print(SCREEN_WIDTH - 10 - text_string_width(FONT_DEFAULT_SMALL, STRING_BACK), SCREEN_HEIGHT - 24, foreground_color, FONT_DEFAULT_SMALL, STRING_BACK);

        graphics_refresh();

        // Basic menu code
        if(keypad_is_button_pressed(BUTTON_8)) {
            selected ++;
            if(selected >= count) selected = 0;
            
        } else if(keypad_is_button_pressed(BUTTON_2)) {
            selected --;
            if(selected < 0) selected = count - 1;
        } else if(keypad_is_button_pressed(BUTTON_O)) {
            keypad_wait_for_no_button();
            return selected;
        } else if(keypad_is_button_pressed(BUTTON_E)) {
            return -1;
        }
        
        keypad_wait_for_no_button();
    }
}

