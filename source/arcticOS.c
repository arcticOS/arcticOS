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

// Used for I/O
#include <stdio.h>
#include <pico/stdlib.h>
#include <hardware/spi.h>

// Used for RTC
#include <hardware/rtc.h>
#include <pico/util/datetime.h>

// When the universe was created
datetime_t time = {
    .year  = 2021,
    .month = 10,
    .day   = 02,
    .dotw  = 7,
    .hour  = 0,
    .min   = 41,
    .sec   = 00
};

const char* weekday_names[7] = {STRING_DAY_SUNDAY, STRING_DAY_MONDAY, STRING_DAY_TUESDAY, STRING_DAY_WEDNESDAY, STRING_DAY_THURSDAY, STRING_DAY_FRIDAY, STRING_DAY_SATURDAY};
const char* month_names[12] = {STRING_MONTH_JANUARY, STRING_MONTH_FEBRUARY, STRING_MONTH_MARCH, STRING_MONTH_APRIL, STRING_MONTH_MAY, STRING_MONTH_JUNE, 
                                STRING_MONTH_JULY, STRING_MONTH_AUGUST, STRING_MONTH_SEPTEMBER, STRING_MONTH_OCTOBER, STRING_MONTH_NOVEMBER, STRING_MONTH_DECEMBER};

// Used for low-power mode
uint16_t sleep_timer_goal = 0;
uint64_t sleep_timer_last = 0;

// Used for global timer
int enable_global_timer = 1;
int in_global_timer = 0;
int global_timer_watchdog = 0;
struct repeating_timer global_timer;
#define GLOBAL_TIMER_INTERVAL 40

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
uint8_t flash_buffer[USER_DATA_SIZE];

// Used for GUI
#include <ui/listmenu.h>

// Apps
#include <apps/launcher/launcher.h>
#include <apps/settings/settings.h>

// Initialise arcticOS
int main(void) {
    // Init cellular
    cellular_init();

    // Init keypad
    keypad_init();

    // Init screen
    screen_init();

    // Factory reset if user is holding down end call button
    if(keypad_is_button_pressed(BUTTON_E)) settings_run_factory_reset();

    // Load settings from flash
    flash_load_user_data(FLASH_OFFSET_SETTINGS, &flash_buffer);

    // Do OOBE if needed
    if(flash_buffer[FLASH_SETTINGS_OOBE_COMPLETE] == 0xFF) settings_run_oobe();

    int theme = flash_buffer[FLASH_SETTINGS_THEME];
    if(theme == 0) {
        background_color = 0xFFFF;
        foreground_color = 0x0000;
    } else if(theme == 1) {
        background_color = 0x0000;
        foreground_color = 0xFFFF;
    }

    // Init RTC
    rtc_init();
    rtc_set_datetime(&time);

    // Init global timer + sleep mode
    add_repeating_timer_ms(GLOBAL_TIMER_INTERVAL, system_timer_process, NULL, &global_timer);
    system_set_sleep_timer(( (uint16_t) flash_buffer[FLASH_SETTINGS_SLEEP_TIME] << 8) + flash_buffer[FLASH_SETTINGS_SLEEP_TIME + 1]);

    // Start launcher app
    start_launcher();

    system_panic("Launcher exited!");
    return 0;
}