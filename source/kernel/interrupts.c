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
#include <hardware/arcticOS/keypad.h>

bool system_timer_process(struct repeating_timer *t) {
    if(in_global_timer) {
        if(ENFORCE_WATCHDOG_COUNT) {
            global_timer_watchdog ++;
            if(global_timer_watchdog >= ENFORCE_WATCHDOG_COUNT) system_panic("Watchdog BITE!");
        }
        return true;
    }
    if(!enable_global_timer) return true;

    in_global_timer = 0;
    if(sleep_timer_goal) {
        if(!keypad_no_buttons_pressed()) sleep_timer_last = time_us_64();
    }

    global_timer_watchdog = 0;
    in_global_timer = 1;
    return true;
}

void system_disable_interrupts() {
    for(int i = 0; i < 25; i++) {
        irq_table[i] = irq_is_enabled(i);
        irq_set_enabled(i, 0);
    }
}

void system_enable_interrupts() {
    for(int i = 0; i < 25; i++) {
        irq_set_enabled(i, irq_table[i]); // If we enable unhandled interrupts, it triggers a breakpoint for some reason
    }
}