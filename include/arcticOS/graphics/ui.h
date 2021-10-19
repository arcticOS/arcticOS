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

// https://chrishewett.com/blog/true-rgb565-colour-picker/
#define COLOR_BLACK 0x0000
#define COLOR_DARKER_GREY 0x39C7
#define COLOR_DARK_GREY 0x6B6D
#define COLOR_GREY 0x9CF3
#define COLOR_LIGHT_GREY 0xCE59
#define COLOR_WHITE 0xFFFF

void ui_draw_element_outline(uint16_t x, uint16_t y, uint16_t x2, uint16_t y2);
void ui_draw_element_inside(uint16_t x, uint16_t y, uint16_t x2, uint16_t y2);