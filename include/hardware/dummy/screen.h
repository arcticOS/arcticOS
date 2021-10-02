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

#include <arcticOS.h>
#include <graphics/fonts/vga.h>

#define SCREEN_WIDTH 0
#define SCREEN_HEIGHT 0

#define SCREEN_FONT_DEFAULT &vga_font[0]

void screen_init() {}
void screen_backlight_on() {}
void screen_backlight_off() {}
void screen_plot_pixel(uint16_t x, uint16_t y, uint16_t color) {}
void screen_fill(uint16_t color) {}
void screen_putchar(uint16_t x, uint16_t y, uint16_t color, uint16_t size, int* font, char character) {}
void screen_print(uint16_t x, uint16_t y, uint16_t color, uint16_t size, int* font, const char* string)}
void screen_refresh() {system_sleep_ok();}

#endif