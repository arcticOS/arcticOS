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

#include <arcticOS/graphics/primitives.h>
#include <arcticOS/graphics/ui.h>

void ui_draw_element_outline(uint16_t x, uint16_t y, uint16_t x2, uint16_t y2) {
    graphics_filled_rect(x, y, x2, y2, COLOR_GREY); // Background

    // Highlights/shadows
    graphics_fastvline(x + 2, y + 2, y2 - 2, COLOR_WHITE);
    graphics_fasthline(x + 2, y + 2, x2 - 2, COLOR_WHITE);
    graphics_fastvline(x2 - 2, y + 2, y2 - 2, COLOR_LIGHT_GREY);
    graphics_fasthline(x + 2, y2 - 2, x2 - 1, COLOR_LIGHT_GREY);

    graphics_rect(x, y, x2, y2, COLOR_DARKER_GREY); // Dark outline
}

void ui_draw_element_inside(uint16_t x, uint16_t y, uint16_t x2, uint16_t y2) {
    graphics_filled_rect(x, y, x2, y2, COLOR_WHITE); // Background

    // Outline
    graphics_rect(x, y, x2, y2, COLOR_DARKER_GREY);
    graphics_fasthline(x, y - 2, x2, COLOR_WHITE);
    graphics_fasthline(x, y2 + 2, x2, COLOR_LIGHT_GREY);
}