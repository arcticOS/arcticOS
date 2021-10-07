/*
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

int* font_get_offset(int* font, char character) {
    character -= 0x20; // Remove the unused 32 ASCII characters

    // TODO: This won't work with non-monospace fonts.
    int font_byte_length = font[0] * font[1];
	int* character_data = &font[2 + (character * (font_byte_length + 2))];
    return character_data;
}

int font_character_width(int* font, char character) {
    return font_get_offset(font, character)[0]; // First character in character is width
}

int font_character_height(int* font) {
    return font[1]; // Second character in font is height
}

int font_string_width(int* font, const char* string) {
    // This is future-proofed for non-monospace fonts.
    int i = 0;
    int width = 0;
    while(string[i]) {
        width += font_character_width(font, string[i]);
        i++;
    }
    return width;
}