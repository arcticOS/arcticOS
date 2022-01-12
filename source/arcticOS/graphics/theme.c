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
#include <arcticOS/graphics/theme.h>

// Redmond, Flat
uint16_t foreground_colors[3] = {COLOR_WHITE, COLOR_WHITE, COLOR_WHITE};
uint16_t background_colors[3] = {COLOR_DARKER_GREY, COLOR_DARKER_GREY, COLOR_DARKER_GREY};
uint16_t accent_colors[3] =     {COLOR_GREEN, COLOR_ORANGE, COLOR_BLUE};

int get_current_theme() {
    int theme = flash_load_byte(FLASH_OFFSET_SETTINGS + FLASH_SETTINGS_THEME);
    return theme;
}

uint16_t get_foreground_color() {
    return foreground_colors[get_current_theme()];
}

uint16_t get_background_color() {
    return background_colors[get_current_theme()];
}

uint16_t get_accent_color() {
    return accent_colors[get_current_theme()];
}