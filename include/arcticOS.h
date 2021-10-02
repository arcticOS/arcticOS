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
#define BUILD_VERSION "0.2"
#define BUILD_SUFFIX "-alpha"

#include <pico/stdlib.h>

// Sleep/Low-power functions
void system_sleep(); // Causes system to enter low-power mode for 10ms, and then check if we need to wake up before again entering low-power mode
void system_set_sleep_timer(int ms); // Sets the amount of milliseconds before the system enters sleep mode.
void system_reset_sleep_timer(); // Resets the amount of milliseconds passed in the sleep timer.
bool system_sleep_timer_process(struct repeating_timer *t); // Increments the sleep timer, or resets it if user input given.
void system_sleep_ok(); // Tell the system it is okay to go to sleep if needed.