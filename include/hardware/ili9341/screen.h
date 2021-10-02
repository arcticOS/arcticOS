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

#ifndef SCREEN_H
#define SCREEN_H

#include <hardware/ili9341/mode2.h>
#include <hardware/ili9341/ili9341.h>

#include <graphics/fonts/vga.h>

#define SCREEN_WIDTH 240
#define SCREEN_HEIGHT 320

#define SCREEN_FONT_VGA &vga_font[0]
#define SCREEN_FONT_DEFAULT &vga_font[0]

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

void screen_print(uint16_t x, uint16_t y, uint16_t color, uint16_t size, int* font, const char* string) {
    mode2_draw_string(x, y, (int) size, color, font, string);
}

void screen_refresh() {
    mode2_render();
}

#endif