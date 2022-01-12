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

#include <arcticOS/drivers/display/screen.h>
#include <arcticOS/drivers/flash.h>

#include <arcticOS/graphics/ui.h>
#include <arcticOS/graphics/text.h>

#include <arcticOS/strings/en-CA.h> // TODO: Find a better solution

void ui_draw_element_outline(uint16_t x, uint16_t y, uint16_t x2, uint16_t y2) {
    switch(flash_load_byte(FLASH_OFFSET_SETTINGS + FLASH_SETTINGS_THEME)) {
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
    switch(flash_load_byte(FLASH_OFFSET_SETTINGS + FLASH_SETTINGS_THEME)) {
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

#define UI_LIST_MENU_ITEM_PADDING_VERTICAL 7
#define UI_LIST_MENU_ITEM_PADDING_HORIZONTAL 5

int ui_list_menu(const char* title, char** items, int count) {
    uint16_t background_color = get_background_color();
    uint16_t foreground_color = get_foreground_color();
    uint16_t accent_color = get_accent_color();
    int selected = 0;

    while(1) {
        int font_height = text_character_height(FONT_DEFAULT_MEDIUM);

        screen_fill(background_color);
        text_print_centered(14, foreground_color, FONT_DEFAULT_LARGE, title);

        for(int i = 0; i < count; i++) { // Loop through all items
            // Draw text
            int y = 51 + (i * (font_height + (UI_LIST_MENU_ITEM_PADDING_VERTICAL * 2)));
            if(y + font_height >= SCREEN_HEIGHT - font_height - 20) break;

            if(items[i][0] != 0x00) {
                if(i == selected) {
                    graphics_gradient_rect(0, y + 1, SCREEN_WIDTH, y + 1 + font_height + (UI_LIST_MENU_ITEM_PADDING_VERTICAL * 2), accent_color, 0x0020);
                    text_print(UI_LIST_MENU_ITEM_PADDING_HORIZONTAL, y + 1 + UI_LIST_MENU_ITEM_PADDING_VERTICAL, COLOR_WHITE, FONT_DEFAULT_MEDIUM, items[i]);
                } else {
                    graphics_filled_rect(0, y + 1, SCREEN_WIDTH, y + 1 + font_height + (UI_LIST_MENU_ITEM_PADDING_VERTICAL * 2), COLOR_DARK_GREY);
                    if(i != count - 1)
                        graphics_fasthline(0, y + font_height + (UI_LIST_MENU_ITEM_PADDING_VERTICAL * 2), SCREEN_WIDTH, COLOR_GREY);
                    text_print(UI_LIST_MENU_ITEM_PADDING_HORIZONTAL, y + 1 + UI_LIST_MENU_ITEM_PADDING_VERTICAL, foreground_color, FONT_DEFAULT_MEDIUM, items[i]);
                }
            } else continue;
        }

        screen_refresh();
    }
}

