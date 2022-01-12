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

#include <stdint.h>

// General element outline
void ui_draw_element_outline(uint16_t x, uint16_t y, uint16_t x2, uint16_t y2);
void ui_draw_element_inside(uint16_t x, uint16_t y, uint16_t x2, uint16_t y2);

// Buttons
void ui_draw_button(uint16_t x, uint16_t y, uint16_t x2, uint16_t y2, const char* text);
void ui_draw_button_pressed(uint16_t x, uint16_t y, uint16_t x2, uint16_t y2, const char* text);

// Menus
int ui_list_menu(const char* title, char** items, int count);