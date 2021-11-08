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
 *
 * This is meant to run on RP2040-based boards.
 */

#include <pico/stdlib.h>

#include <arcticOS/graphics/fonts/zap.h>
#include <arcticOS/graphics/fonts/bizcat.h>

#define FONT_BIZCAT_SMALL &bizcat[0]

#define FONT_ZAP_TINY &zapsmall[0]
#define FONT_ZAP_SMALL &zapsmall[0]
#define FONT_ZAP_MEDIUM &zapmed[0]

#define FONT_DEFAULT_TINY FONT_ZAP_TINY
#define FONT_DEFAULT_SMALL FONT_BIZCAT_SMALL
#define FONT_DEFAULT_MEDIUM FONT_ZAP_MEDIUM
#define FONT_DEFAULT_LARGE FONT_ZAP_MEDIUM

#define FONT_DEFAULT FONT_DEFAULT_SMALL

// Functions for getting font information
int* text_get_offset(int* font, char character);
int text_character_width(int* font, char character);
int text_character_height(int* font);
int text_string_width(int* font, const char* string);

// Functions for drawing text
void text_draw_character(uint16_t x, uint16_t y, uint16_t color, int* font, char character);
void text_print(uint16_t x, uint16_t y, uint16_t color, int* font, const char* string);
void text_print_centered(uint16_t y, uint16_t color, int* font, const char* string);