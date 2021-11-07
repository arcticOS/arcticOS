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

int SCREEN_WIDTH = 0;
int SCREEN_HEIGHT = 0;

void graphics_get_screen_size() {
    int width_data[2] = {0x00, 0x04};
    int* width_return[1] = {&SCREEN_WIDTH};
    system_call(&width_data[0], &width_return[0]);

    int height_data[2] = {0x00, 0x05};
    int* height_return[1] = {&SCREEN_HEIGHT};
    system_call(&height_data[0], &height_return[0]);
}

void graphics_plot_pixel(int x, int y, uint16_t color) {
    int params[6] = {0x00, 0x02, x, y, (int) ((color & 0xFF00) >> 8), (int) (color & 0x00FF)};
    system_call(&params[0], NULL);
}

void graphics_refresh() {
    int params[2] = {0x00, 0x03};
    system_call(&params[0], NULL);
}

void graphics_fill(uint16_t color) {
    graphics_get_screen_size();
    graphics_filled_rect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, color);
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
