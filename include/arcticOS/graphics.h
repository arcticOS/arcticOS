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

void screen_rect(uint16_t x, uint16_t y, uint16_t x2, uint16_t y2, uint16_t color);
void screen_filled_rect(uint16_t x, uint16_t y, uint16_t x2, uint16_t y2, uint16_t color);
void screen_circle(uint16_t x, uint16_t y, int16_t r, uint16_t color);
void screen_filled_circle(uint16_t x, uint16_t y, int16_t r, uint16_t color);
void screen_line(uint16_t x, uint16_t y, uint16_t x2, uint16_t y2, uint16_t color);
void screen_fasthline(uint16_t x, uint16_t y, uint16_t x2, uint16_t color);
void screen_fastvline(uint16_t x, uint16_t y, uint16_t y2, uint16_t color);