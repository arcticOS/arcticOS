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

// CHANGE THE LINE BELOW TO CHANGE LANGUAGE
#include <arcticOS/strings/en-CA.h>
#include <arcticOS/build_settings.h>

// No longer build settings
#include <pico/stdlib.h>

extern datetime_t time;

extern const char* weekday_names[];
extern const char* month_names[];

extern uint16_t sleep_timer_goal;
extern uint64_t sleep_timer_last;
extern int enable_global_timer;
extern int in_global_timer;
extern int global_timer_watchdog;
extern struct repeating_timer global_timer;

extern uint16_t background_color;
extern uint16_t foreground_color;

extern uint8_t flash_buffer[];

extern int irq_table[];

// Sleep/Low-power functions
void system_sleep(); // Causes system to enter low-power mode for 10ms, and then check if we need to wake up before again entering low-power mode
void system_set_sleep_timer(int ms); // Sets the amount of milliseconds before the system enters sleep mode.
void system_reset_sleep_timer(); // Resets the amount of milliseconds passed in the sleep timer.
bool system_timer_process(struct repeating_timer *t); // Increments the sleep timer, or resets it if user input given.
void system_sleep_ok(); // Tell the system it is okay to go to sleep if needed.

// Interrupt functions
void system_disable_interrupts(); // Disable interrupts.
void system_enable_interrupts(); // Enable interrupts.

// System call functions
void register_syscall_handler();

// Debug functions
void system_panic(const char* message); // Kernel panic.
void system_hang(); // Freeze system.
void system_break();

// Functions for managing global data
void system_refresh_settings();

// Multitasking Functions
int create_service(void (*handler)(void), const char* name);
void kill_service(int id);