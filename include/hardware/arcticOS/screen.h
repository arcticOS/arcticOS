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

#include <pico/stdlib.h>

void screen_init();
void screen_backlight_on();
void screen_backlight_off();
void screen_plot_pixel(uint16_t x, uint16_t y, uint16_t color);
void screen_fill(uint16_t color);
void screen_refresh();

#if defined(EVT3) || defined(EVT4)
#define SCREEN_WIDTH 240
#define SCREEN_HEIGHT 320
#endif