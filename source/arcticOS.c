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

// CHANGE THE LINE BELOW TO CHANGE LANGUAGE
#include <strings/en-CA.h>

#include <arcticOS.h>

// Used for I/O
#include <stdio.h>
#include <pico/stdlib.h>
#include <hardware/spi.h>

// Used for RTC
#include <hardware/rtc.h>
#include <pico/util/datetime.h>

const char* weekday_names[7] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
const char* month_names[12] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};

// Used for low-power mode
uint16_t sleep_timer_goal = 0;
uint64_t sleep_timer_last = 0;

// Used for global timer
int enable_global_timer = 1;
int global_timer_watchdog;
struct repeating_timer global_timer;
#define GLOBAL_TIMER_INTERVAL 10

// Theme
uint16_t background_color = 0x0000;
uint16_t foreground_color = 0xFFFF;

// Used for disabling/enabling interrupts
#include <hardware/irq.h>
int irq_table[25];

// Used for interfacing with other hardware on motherboard
#include <hardware/arcticOS/cellular.h>
#include <hardware/arcticOS/keypad.h>
#include <hardware/arcticOS/screen.h>

// Used for flash memory
#include <hardware/arcticOS/flash.h>
#include <flash-layout/flash-layout.h>
#include <flash-layout/settings.h>

uint8_t flash_buffer[USER_DATA_SIZE];

// Initialise arcticOS
int main(void) {
    // Init cellular
    cellular_init();

    // Init keypad
    keypad_init();

    // Init screen
    screen_init();

    // Load settings from flash
    flash_load_user_data(FLASH_OFFSET_SETTINGS, &flash_buffer);

    // Do OOBE if needed
    // For now, this just sets all defaults.
    if(!flash_buffer[FLASH_SETTINGS_OOBE_COMPLETE]) {
        flash_buffer[FLASH_SETTINGS_OOBE_COMPLETE] = 1;
        flash_buffer[FLASH_SETTINGS_SLEEP_TIME] = 15000 >> 8;
        flash_buffer[FLASH_SETTINGS_SLEEP_TIME + 1] = (uint8_t) 15000;
        flash_write_user_data(FLASH_OFFSET_SETTINGS, &flash_buffer);
        flash_load_user_data(FLASH_OFFSET_SETTINGS, &flash_buffer);
    }

    // Init RTC
    // This is the same on all platforms
    datetime_t time = {
        .year  = 2021,
        .month = 10,
        .day   = 02,
        .dotw  = 7,
        .hour  = 0,
        .min   = 41,
        .sec   = 00
    };

    rtc_init();
    rtc_set_datetime(&time);

    char time_buffer[9];
    char date_buffer[32];

    // Init global timer + sleep mode
    add_repeating_timer_ms(GLOBAL_TIMER_INTERVAL, system_timer_process, NULL, &global_timer);
    system_set_sleep_timer(/*( (uint16_t) flash_buffer[FLASH_SETTINGS_SLEEP_TIME] << 8) + flash_buffer[FLASH_SETTINGS_SLEEP_TIME + 1]*/15000);

    // OS loop
    while(1) {
        screen_fill(background_color);

        // Get the actual time
        if(!rtc_get_datetime(&time) && ENFORCE_RTC_ENABLED) {
            system_panic("RTC Failure");
        }

        // Calculate time in 12-hour time and get it as a string
        int hour = time.hour;
        if(hour > 12) hour /= 2;
        if(hour == 0) hour = 12;
        if(time.hour > 12) sprintf(time_buffer, "%d:%d PM", hour / 2, time.min);
        else sprintf(time_buffer, "%d:%d AM", hour, time.min);

        // Get date as a string
        sprintf(date_buffer, "%s, %s %d", weekday_names[time.dotw - 1], month_names[time.month - 1], time.day);

        screen_print(10, 10, foreground_color, 2, SCREEN_FONT_VGA, &time_buffer);
        screen_print(10, 42, foreground_color, 1, SCREEN_FONT_VGA, &date_buffer);
        screen_print(10, 58, foreground_color, 1, SCREEN_FONT_VGA, "arcticOS v0.2-alpha");

        if(keypad_is_button_pressed(BUTTON_6)) screen_putchar(20, 80, foreground_color, 1, SCREEN_FONT_VGA, 'G');
        screen_refresh();
    }
    return 0;
}

void system_sleep() {
    screen_backlight_off();
    while(1) {
        sleep_ms(10);
        if(!keypad_no_buttons_pressed()) { // Button is pressed, wake up
            screen_backlight_on();
            system_reset_sleep_timer();
            return;
        }
    }
}

void system_set_sleep_timer(int ms) {
    sleep_timer_goal = ms;
}

void system_reset_sleep_timer() {
    sleep_timer_last = time_us_64();
}

bool system_timer_process(struct repeating_timer *t) {
    if(!enable_global_timer) {
        if(ENFORCE_WATCHDOG_COUNT) {
            global_timer_watchdog ++;
            if(global_timer_watchdog >= ENFORCE_WATCHDOG_COUNT) system_panic("Watchdog BITE!");
        }
        return true;
    }

    enable_global_timer = 0;
    if(sleep_timer_goal) {
        if(!keypad_no_buttons_pressed()) sleep_timer_last = time_us_64();
    }

    enable_global_timer = 1;
    return true;
}

void system_sleep_ok() {
    if(!sleep_timer_goal) return;
    if((time_us_64() - sleep_timer_last) / 1000 >= sleep_timer_goal) {
        system_sleep();
    } 
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

void system_panic(const char* message) {
    sleep_timer_goal = 0;
    screen_fill(0xF800);
    screen_print(10, 56, 0xFFFF, 1, SCREEN_FONT_VGA, message);
    while(1) {
        enable_global_timer = 0;
        screen_print(10, 10, 0xFFFF, 3, SCREEN_FONT_VGA, "PANIC!");
        screen_refresh();
        sleep_ms(500);
        screen_print(10, 10, 0xF800, 3, SCREEN_FONT_VGA, "PANIC!");
        screen_refresh();
        sleep_ms(500);
    }
}