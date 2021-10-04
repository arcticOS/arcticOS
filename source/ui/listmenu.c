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
#include <graphics/fonts/fontutils.h>

int ui_list_menu(const char* title, char** items, int count) {
    int selected = 0;

    while(1) {
        int font_height = font_character_height(SCREEN_FONT_DEFAULT);
        int font_width = font_character_width(SCREEN_FONT_DEFAULT);
        screen_fill(background_color);
        screen_print(10, 10, foreground_color, 2, SCREEN_FONT_DEFAULT, title);

        for(int i = 0; i < count; i++) {
            int x = (SCREEN_WIDTH / 2) - (font_string_width(SCREEN_FONT_DEFAULT, items[i]) / 2);
            int y = (10 * (i + 1)) + (font_height * 2) + (i * font_height);
            screen_print(x, y, foreground_color, 1, SCREEN_FONT_DEFAULT, items[i]);

            if(i == selected) {
                for(int lx = x; lx < x + font_string_width(SCREEN_FONT_DEFAULT, items[i]); lx ++) {
                    screen_plot_pixel(lx, y + font_height, foreground_color);
                }
            }
        }

        screen_refresh();

        if(KEYPAD_HAS_DPAD) {

        } else {
            if(keypad_is_button_pressed(BUTTON_8)) {
                selected ++;
                if(selected >= count) selected = 0;
                
            } else if(keypad_is_button_pressed(BUTTON_2)) {
                selected --;
                if(selected < 0) selected = count - 1;
            } else if(keypad_is_button_pressed(BUTTON_O)) {
                keypad_wait_for_no_button();
                return selected;
            }
        }
        keypad_wait_for_no_button();
    }
}