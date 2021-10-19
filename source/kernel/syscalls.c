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

#include <arcticOS.h>
#include <hardware/arcticOS/screen.h>
#include <hardware/arcticOS/keypad.h>

struct syscall_params {
    int type;
    uint16_t param0;
    uint16_t param1;
    uint16_t param2;
    uint16_t param3;

    int* return_pointer;
};

void register_syscall_handler() {
    irq_set_exclusive_handler(30, &handle_syscall);
    irq_set_enabled(30, 1);
}

void handle_syscall(void) {
    struct syscall_params* params;
    asm volatile("mov %0, R1" : "=r" (params));

    if(params->type == 0) { // Screen
        // Param0 - Operation type
        if(params->param0 == 0) { // Backlight
            // Param1 - On/Off
            if(params->param1) screen_backlight_on();
            else screen_backlight_off();
        } else if(params->param0 == 1) { // Fill
            // Param1 - Color
            screen_fill(params->param1); 
        } else if(params->param0 == 2) { // Plot
            // Param1 - X
            // Param2 - Y
            // Param3 - Color
            screen_plot_pixel(params->param1, params->param2, params->param3);
        } else if(params->param0 == 3) screen_refresh(); // Refresh
        else if(params->param0 == 4) { // Get Screen Width
            params->return_pointer[0] = SCREEN_WIDTH;
        } else if(params->param0 == 5) { // Get Screen Height
            params->return_pointer[0] = SCREEN_HEIGHT;
        }
    } else if(params->type == 1) { // Panic
        system_panic("App caused system crash");
    } else if(params->type == 2) { // User Input
        if(params->param0 == 0) { // Keypad
            keypad_refresh();
            if(params->param1 == 0) { // Is button pressed
                // Param2 - Button bitmask
                params->return_pointer[0] = buttons_pressed & params->param2;
            } else if(params->param1 == 1) { // Is no button pressed
                params->return_pointer[0] = buttons_pressed == 0x0000;
            }
        }
    }
}
