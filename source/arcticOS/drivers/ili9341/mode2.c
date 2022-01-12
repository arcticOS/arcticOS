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

#include <arcticOS/drivers/display/ili9341/mode2.h>
#include <string.h>

#define SIZE (ILI9341_TFTHEIGHT*ILI9341_TFTWIDTH)

int mode2_is_rendering = 0;
uint16_t mode2_buffer[SIZE] = { 0 };

void mode2_init() {
}

void mode2_clear(uint16_t color) {
	while(mode2_is_rendering) {}
	uint16_t real_color = (color >> 8) | (color << 8);
    memset(mode2_buffer, real_color, SIZE*sizeof(uint16_t));
}

void mode2_pixel(uint16_t x, uint16_t y, uint16_t color) {
	while(mode2_is_rendering) {}
	if(x < 0 || x >= ILI9341_TFTWIDTH) return;
	if(y < 0 || y >= ILI9341_TFTHEIGHT) return;
	uint16_t real_color = (color >> 8) | (color << 8);
	mode2_buffer[y*ILI9341_TFTWIDTH+x] = real_color;
}

void mode2_rect(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t color) {
	while(mode2_is_rendering) {}
	uint16_t *base_loc = &mode2_buffer[x*ILI9341_TFTWIDTH+y];

	for (int h=0; h<width; h++) {
	    uint16_t *loc = base_loc + h*ILI9341_TFTWIDTH;
    	for (int v=0; v<height; v++) {
			*loc++ = color;
    	}
	}
}

void mode2_render() {
	mode2_is_rendering = 1;
    ili9341_start_writing();
	ili9341_write_data_continuous(mode2_buffer, SIZE*sizeof(uint16_t));
	ili9341_stop_writing();
	mode2_is_rendering = 0;
}

