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

#include <arcticOS/strings/en-CA.h> // TODO: Find a better solution

void ui_draw_element_outline(uint16_t x, uint16_t y, uint16_t x2, uint16_t y2) {
    graphics_filled_rect(x, y, x2, y2, COLOR_GREY); // Background

    // Highlights/shadows
    graphics_fastvline(x + 2, y + 2, y2 - 2, COLOR_WHITE);
    graphics_fasthline(x + 2, y + 2, x2 - 2, COLOR_WHITE);
    graphics_fastvline(x2 - 2, y + 2, y2 - 2, COLOR_LIGHT_GREY);
    graphics_fasthline(x + 2, y2 - 2, x2 - 1, COLOR_LIGHT_GREY);

    graphics_rect(x, y, x2, y2, COLOR_DARKER_GREY); // Dark outline
}

void ui_draw_element_inside(uint16_t x, uint16_t y, uint16_t x2, uint16_t y2) {
    graphics_filled_rect(x, y, x2, y2, COLOR_WHITE); // Background

    // Outline
    graphics_rect(x, y, x2, y2, COLOR_DARKER_GREY);
    graphics_fasthline(x, y - 2, x2, COLOR_WHITE);
    graphics_fasthline(x, y2 + 2, x2, COLOR_LIGHT_GREY);
}

void ui_draw_button(uint16_t x, uint16_t y, uint16_t x2, uint16_t y2, const char* text) {
    ui_draw_element_outline(x, y, x2, y2);
}

void ui_draw_button_pressed(uint16_t x, uint16_t y, uint16_t x2, uint16_t y2, const char* text) {

}

int ui_list_menu(const char* title, char** items, int count) {
    int selected = 0;

    while(1) {
        int font_height = text_character_height(FONT_DEFAULT);
        graphics_fill(COLOR_WHITE);
        text_print_centered(10, COLOR_BLACK, FONT_DEFAULT_MEDIUM, title);

        for(int i = 0; i < count; i++) { // Loop through all items
            // Draw text
            int y = (10 * (i + 1)) + (font_height * 2) + (i * font_height);
            if(y + font_height >= SCREEN_HEIGHT - font_height - 20) break;
            text_print_centered(y, COLOR_BLACK, FONT_DEFAULT, items[i]);

            // Draw a line under the current line of text
            if(i == selected) {
                int x = (SCREEN_WIDTH / 2) - (text_string_width(FONT_DEFAULT, items[i]) / 2);
                for(int lx = x; lx < x + text_string_width(FONT_DEFAULT, items[i]); lx ++) {
                    graphics_plot_pixel(lx, y + font_height, COLOR_BLACK);
                }
            }
        }

        // Draw hint bar
        text_print_centered(SCREEN_HEIGHT - 26, COLOR_BLACK, FONT_DEFAULT_TINY, STRING_SELECT);
        text_print(SCREEN_WIDTH - 10 - text_string_width(FONT_DEFAULT_TINY, STRING_BACK), SCREEN_HEIGHT - 26, COLOR_BLACK, FONT_DEFAULT_TINY, STRING_BACK);

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

