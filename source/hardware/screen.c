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
#include <graphics/fonts/fontutils.h>

void screen_rect(uint16_t x, uint16_t y, uint16_t x2, uint16_t y2, uint16_t color) {
    screen_fasthline(x, y, x2, color);
    screen_fasthline(x, y2, x2, color);
    screen_fastvline(x, y, y2, color);
    screen_fastvline(x2, y, y2, color);
}

void screen_filled_rect(uint16_t x, uint16_t y, uint16_t x2, uint16_t y2, uint16_t color) { 
    for(int dx = x; dx < x2; dx ++) {
        for(int dy = y; dy < y2; dy ++) {
            screen_plot_pixel(dx, dy, color);
        }
    }
}

void screen_line(uint16_t x, uint16_t y, uint16_t x2, uint16_t y2, uint16_t color) {
    if(x == x2) screen_fastvline(x, y, y2, color);
    else if(y == y2) screen_fasthline(x, y, x2, color);
    else {
        // DDA Line Drawing Algorithm
        int dx = x2 - x;
        int dy = y2 - y;
        int steps = 0;

        if(abs(dx) > abs(dy)) steps = abs(dx);
        else steps = abs(dy);

        float x_increment = dx / (float) steps;
        float y_increment = dy / (float) steps;

        float px = x;
        float py = y;

        for(int v = 0; v < steps; v ++) {
            screen_plot_pixel(px, py, color);
            px += x_increment;
            py += y_increment;
        }
    }
}

void screen_fasthline(uint16_t x, uint16_t y, uint16_t x2, uint16_t color) {
    for(int dx = x; dx < x2; dx++) {
        screen_plot_pixel(dx, y, color);
    }
}

void screen_fastvline(uint16_t x, uint16_t y, uint16_t y2, uint16_t color) {
    for(int dy = y; dy < y2; dy++) {
        screen_plot_pixel(x, dy, color);
    }
}

void screen_print(uint16_t x, uint16_t y, uint16_t color, int* font, const char* string) {
    // TODO: This won't work for non-monospace fonts. A width variable is needed - copy the
    // fontutils width code.
    int i = 0;
	while(string[i]) {
		screen_putchar(x + (i * font_character_width(font, string[i])), y, color, font, string[i]);
		i++;
	}
}

void screen_print_centered(uint16_t y, uint16_t color, int* font, const char* string) {
    uint16_t x = (SCREEN_WIDTH / 2) - (font_string_width(font, string) / 2); // Figure out where we need to draw the text to drop it in the center
    screen_print(x, y, color, font, string); // Put it there
}

#if defined(EVT3) || defined(EVT4)

#include <hardware/ili9341/mode2.h>
#include <hardware/ili9341/ili9341.h>

void screen_init() {
    ili9341_init();
    mode2_init();
    ili9341_backlight(1);
}

void screen_backlight_on() {
    ili9341_backlight(1);
}

void screen_backlight_off() {
    ili9341_backlight(0);
}

void screen_plot_pixel(uint16_t x, uint16_t y, uint16_t color) {
    mode2_pixel(x, y, color);
}

void screen_fill(uint16_t color) {
    mode2_clear(color);
}

void screen_putchar(uint16_t x, uint16_t y, uint16_t color, int* font, char character) {
    mode2_draw_char(x, y, color, font, character);
}

void screen_refresh() {
    mode2_render();
    system_sleep_ok();
}

#endif