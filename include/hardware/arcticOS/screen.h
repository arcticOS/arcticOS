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

#include <pico/stdlib.h>

#include <graphics/fonts/sono.h>
#define SCREEN_FONT_SONO_TINY &sono_tiny[0]
#define SCREEN_FONT_SONO_SMALL &sono_small[0]
#define SCREEN_FONT_SONO_MEDIUM &sono_medium[0]

#define SCREEN_FONT_DEFAULT_TINY SCREEN_FONT_SONO_TINY
#define SCREEN_FONT_DEFAULT_SMALL SCREEN_FONT_SONO_SMALL
#define SCREEN_FONT_DEFAULT_MEDIUM SCREEN_FONT_SONO_MEDIUM
#define SCREEN_FONT_DEFAULT_LARGE SCREEN_FONT_SONO_MEDIUM

#define SCREEN_FONT_DEFAULT SCREEN_FONT_DEFAULT_SMALL

void screen_init();
void screen_backlight_on();
void screen_backlight_off();
void screen_plot_pixel(uint16_t x, uint16_t y, uint16_t color);
void screen_fill(uint16_t color);
void screen_putchar(uint16_t x, uint16_t y, uint16_t color, int* font, char character);
void screen_refresh();

void screen_print(uint16_t x, uint16_t y, uint16_t color, int* font, const char* string);
void screen_print_centered(uint16_t y, uint16_t color, int* font, const char* string);


#if defined(EVT3) || defined(EVT4)
#define SCREEN_WIDTH 240
#define SCREEN_HEIGHT 320

// BRG for some stupid reason
#define SCREEN_COLOR_BLACK 0x0000
#define SCREEN_COLOR_WHITE 0xFFFF
#define SCREEN_COLOR_RED 0x07E0
#define SCREEN_COLOR_BLUE 0xF800
#define SCREEN_COLOR_GREEN 0x001F
#endif