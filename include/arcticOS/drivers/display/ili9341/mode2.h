/*
 * Copyright (C) 2021 Shawn Hyam, Johnny Stene
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

#ifndef _MODE2_H
#define _MODE2_H

#include <arcticOS/drivers/display/ili9341/ili9341.h>

extern uint16_t mode2_buffer[ILI9341_TFTWIDTH*ILI9341_TFTHEIGHT];

void mode2_init();
void mode2_clear(uint16_t color);
void mode2_pixel(uint16_t x, uint16_t y, uint16_t color);
void mode2_rect(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t color);
void mode2_render();
#endif

