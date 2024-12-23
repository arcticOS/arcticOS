/*
 * arcticOS
 * Copyright (C) 2024 Johnny Stene
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

// https://chrishewett.com/blog/true-rgb565-colour-picker/
#define COLOR_BLACK 0x0000
#define COLOR_DARKER_GREY 0x39C7
#define COLOR_DARK_GREY 0x6B6D
#define COLOR_GREY 0x9CF3
#define COLOR_LIGHT_GREY 0xCE59
#define COLOR_WHITE 0xFFFF

#define COLOR_RED 0xF800
#define COLOR_ORANGE 0xFA62
#define COLOR_YELLOW 0xFFE0
#define COLOR_GREEN 0x07E0
#define COLOR_CYAN 0x07FF
#define COLOR_BLUE 0x001F
#define COLOR_MAGENTA 0xF81F

void screen_init();
void screen_backlight_on();
void screen_backlight_off();
void screen_plot_pixel(uint16_t x, uint16_t y, uint16_t color);
void screen_fill(uint16_t color);
void screen_refresh();

void graphics_get_screen_size();
void graphics_rect(uint16_t x, uint16_t y, uint16_t x2, uint16_t y2, uint16_t color);
void graphics_filled_rect(uint16_t x, uint16_t y, uint16_t x2, uint16_t y2, uint16_t color);
void graphics_gradient_rect(uint16_t x, uint16_t y, uint16_t x2, uint16_t y2, uint16_t color, uint16_t color2);
void graphics_circle(uint16_t x, uint16_t y, int16_t r, uint16_t color);
void graphics_filled_circle(uint16_t x, uint16_t y, int16_t r, uint16_t color);
void graphics_line(uint16_t x, uint16_t y, uint16_t x2, uint16_t y2, uint16_t color);
void graphics_fasthline(uint16_t x, uint16_t y, uint16_t x2, uint16_t color);
void graphics_fastvline(uint16_t x, uint16_t y, uint16_t y2, uint16_t color);
uint16_t graphics_to_565(uint8_t r, uint8_t g, uint8_t b);

#if defined(EVT3) || defined(EVT4)
#define SCREEN_WIDTH 240
#define SCREEN_HEIGHT 320
#endif