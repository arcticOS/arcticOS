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
#include <arcticOS/kernel/syscall.h>

void graphics_plot_pixel(uint16_t x, uint16_t y, uint16_t color) {
    do_system_call(0, 2, x, y, color);
}

void graphics_refresh() {
    do_system_call(0, 3, 0, 0, 0);
}

void graphics_rect(uint16_t x, uint16_t y, uint16_t x2, uint16_t y2, uint16_t color) {
    graphics_fasthline(x, y, x2, color);
    graphics_fasthline(x, y2, x2 + 1, color);
    graphics_fastvline(x, y, y2, color);
    graphics_fastvline(x2, y, y2, color);
}

void graphics_filled_rect(uint16_t x, uint16_t y, uint16_t x2, uint16_t y2, uint16_t color) { 
    for(int dx = x; dx < x2; dx ++) {
        for(int dy = y; dy < y2; dy ++) {
            graphics_plot_pixel(dx, dy, color);
        }
    }
}

void graphics_circle(uint16_t x, uint16_t y, int16_t r, uint16_t color) {
    // Bresenham's Algorithm
    uint16_t dx = 0, dy = r;
    int16_t d = 3 - (2 * r); // I spent 30 minutes debugging, turns out the problem was I was using unsigned ints. FML
    graphics_plot_pixel(x + dx, y + dy, color);
    graphics_plot_pixel(x - dx, y + dy, color);
    graphics_plot_pixel(x + dx, y - dy, color);
    graphics_plot_pixel(x - dx, y - dy, color);
    graphics_plot_pixel(x + dy, y + dx, color);
    graphics_plot_pixel(x - dy, y + dx, color);
    graphics_plot_pixel(x + dy, y - dx, color);
    graphics_plot_pixel(x - dy, y - dx, color);
    while (dy >= dx)
    {
        dx++;
 
        if (d > 0)
        {
            dy--;
            d = d + 4 * (dx - dy) + 10;
        }
        else d = d + 4 * dx + 6;
        graphics_plot_pixel(x + dx, y + dy, color);
        graphics_plot_pixel(x - dx, y + dy, color);
        graphics_plot_pixel(x + dx, y - dy, color);
        graphics_plot_pixel(x - dx, y - dy, color);
        graphics_plot_pixel(x + dy, y + dx, color);
        graphics_plot_pixel(x - dy, y + dx, color);
        graphics_plot_pixel(x + dy, y - dx, color);
        graphics_plot_pixel(x - dy, y - dx, color);
    }
}

void graphics_filled_circle(uint16_t x, uint16_t y, int16_t r, uint16_t color) {
    // Bresenham's Algorithm
    uint16_t dx = 0, dy = r;
    int16_t d = 3 - (2 * r); // I spent 30 minutes debugging, turns out the problem was I was using unsigned ints. FML
    graphics_line(x + dx, y + dy, x - dx, y + dy, color);
    graphics_line(x + dy, y + dx, x - dy, y + dx, color);
    graphics_line(x + dx, y - dy, x - dx, y - dy, color);
    graphics_line(x + dy, y - dx, x - dy, y - dx, color);
    while (dy >= dx)
    {
        dx++;
 
        if (d > 0)
        {
            dy--;
            d = d + 4 * (dx - dy) + 10;
        }
        else d = d + 4 * dx + 6;
        graphics_line(x + dx, y + dy, x - dx, y + dy, color);
        graphics_line(x + dy, y + dx, x - dy, y + dx, color);
        graphics_line(x + dx, y - dy, x - dx, y - dy, color);
        graphics_line(x + dy, y - dx, x - dy, y - dx, color);
    }
}

void graphics_line(uint16_t x, uint16_t y, uint16_t x2, uint16_t y2, uint16_t color) {
    if(x2 < x) {
        int tmp = x;
        x = x2;
        x2 = tmp;
    }

    if(y2 < y) {
        int tmp = y;
        y = y2;
        y2 = tmp;
    }
    
    if(x == x2) graphics_fastvline(x, y, y2, color);
    else if(y == y2) graphics_fasthline(x, y, x2, color);
    else {
        // DDA Line Drawing Algorithm
        int dx = x2 - x;
        int dy = y2 - y;
        int steps = 0;

        if(abs(dx) > abs(dy)) steps = abs(dx);
        else steps = abs(dy);

        float x_increment = dx / (float) steps;
        float y_increment = dy / (float) steps;

        float px = x;
        float py = y;

        for(int v = 0; v < steps; v ++) {
            graphics_plot_pixel(px, py, color);
            px += x_increment;
            py += y_increment;
        }
    }
}

void graphics_fasthline(uint16_t x, uint16_t y, uint16_t x2, uint16_t color) {
    for(int dx = x; dx < x2; dx++) {
        graphics_plot_pixel(dx, y, color);
    }
}

void graphics_fastvline(uint16_t x, uint16_t y, uint16_t y2, uint16_t color) {
    for(int dy = y; dy < y2; dy++) {
        graphics_plot_pixel(x, dy, color);
    }
}
