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

#include <hardware/ili9341/mode2.h>
#include <string.h>
#include <hardware/ili9341/font.h>

#define SIZE (ILI9341_TFTHEIGHT*ILI9341_TFTWIDTH)

uint16_t mode2_buffer[SIZE] = { 0 };

void mode2_draw_string(uint16_t x, uint16_t y, int size, uint16_t color, const char* string) {
	int i = 0;
	while(string[i] != 0x00) {
		mode2_draw_char(x + (i * 8 * size), y, size, color, string[i]);
		i++;
	}
}

void mode2_draw_char(uint16_t x, uint16_t y, int size, uint16_t color, char character) {
	int* character_data = &font[character * 16];

	for(int font_y = 0; font_y < 16; font_y++) {
		int draw_x = 7; // There is a better solution to this, but I am too fucking tired for it.
		for(int font_x = 0; font_x < 8; font_x++) {
			int bit = (character_data[font_y] >> font_x) & 1;
			for(int scale_x = 0; scale_x < size; scale_x ++) {
				for(int scale_y = 0; scale_y < size; scale_y ++) {
					if(bit) mode2_pixel(x + scale_x + (draw_x * size), y + scale_y + (font_y * size), color);
				}
			}
			draw_x--;
		}
	}
}

void mode2_init() {
}

void mode2_clear(uint16_t color) {
    memset(mode2_buffer, color, SIZE*sizeof(uint16_t));
}

void mode2_pixel(uint16_t x, uint16_t y, uint16_t color) {
	if(x < 0 || x >= ILI9341_TFTWIDTH) return;
	if(y < 0 || y >= ILI9341_TFTHEIGHT) return;
	mode2_buffer[y*ILI9341_TFTWIDTH+x] = color;
}

void mode2_rect(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t color) {
	uint16_t *base_loc = &mode2_buffer[x*ILI9341_TFTWIDTH+y];

	for (int h=0; h<width; h++) {
	    uint16_t *loc = base_loc + h*ILI9341_TFTWIDTH;
    	for (int v=0; v<height; v++) {
			*loc++ = color;
    	}
	}
}

void mode2_render() {
    ili9341_start_writing();
	ili9341_write_data_continuous(mode2_buffer, SIZE*sizeof(uint16_t));
	ili9341_stop_writing();
}

