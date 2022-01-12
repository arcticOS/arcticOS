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
 *
 * This is meant to run on RP2040-based boards.
 */

#include <arcticOS/drivers/display/screen.h>
#include <arcticOS/graphics/text.h>

int* text_get_offset(int* font, char character) {
    character -= 0x20; // Remove the unused 32 ASCII characters

    // TODO: This won't work with non-monospace fonts.
    int font_byte_length = font[0] * font[1];
	int* character_data = &font[2 + (character * (font_byte_length + 2))];
    return character_data;
}

int text_character_width(int* font, char character) {
    return text_get_offset(font, character)[0]; // First character in character is width
}

int text_character_height(int* font) {
    return font[1]; // Second character in font is height
}

int text_string_width(int* font, const char* string) {
    // This is future-proofed for non-monospace fonts.
    int i = 0;
    int width = 0;
    while(string[i]) {
        width += text_character_width(font, string[i]);
        i++;
    }
    return width;
}

void text_draw_character(uint16_t x, uint16_t y, uint16_t color, int* font, char character) {
    character -= 0x20; // Get rid of the 32 unused characters in the ASCII table
	int font_byte_length = font[0] * font[1];
	int* character_data = &font[2 + (character * (font_byte_length + 2))];
	int character_width = character_data[0];
	int character_height = character_data[1];
	character_data = &character_data[2];

	int i = 0; // Character data index
	for(int font_y = 0; font_y < character_height; font_y ++) {
		for(int byte = 0; byte < font[0]; byte++) {
            int draw_x = font[0];
			for(int font_x = 0; font_x < 8; font_x++) {
				if((character_data[i] >> font_x) & 1) screen_plot_pixel(x + draw_x + 8 + (8*byte), y + font_y, color);
                draw_x --;
			}
			i ++;
		}
	}
}

void text_print(uint16_t x, uint16_t y, uint16_t color, int* font, const char* string) {
    // TODO: This won't work for non-monospace fonts. A width variable is needed - copy the
    // fontutils width code.
    int i = 0;
	while(string[i]) {
		text_draw_character(x + (i * text_character_width(font, string[i])), y, color, font, string[i]);
		i++;
	}
}

void text_print_centered(uint16_t y, uint16_t color, int* font, const char* string) {
    uint16_t x = (SCREEN_WIDTH / 2) - (text_string_width(font, string) / 2); // Figure out where we need to draw the text to drop it in the center
    text_print(x, y, color, font, string); // Put it there
}