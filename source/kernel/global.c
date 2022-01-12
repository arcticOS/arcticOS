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

#include <arcticOS.h>
#include <hardware/arcticOS/flash.h>
#include <apps/settings/settings.h>

void system_refresh_settings() {
    // Load settings from flash
    flash_load_user_data(FLASH_OFFSET_SETTINGS, &flash_buffer[0]);

    // Do OOBE if needed
    if(flash_buffer[FLASH_SETTINGS_OOBE_COMPLETE] == 0xFF) settings_run_oobe();

    // Set theme
    int theme = flash_buffer[FLASH_SETTINGS_THEME];
    if(theme == 0) {
        background_color = 0xFFFF;
        foreground_color = 0x0000;
    } else if(theme == 1) {
        background_color = 0x0000;
        foreground_color = 0xFFFF;
    }

    // Set sleep timer
    system_set_sleep_timer(( (uint16_t) flash_buffer[FLASH_SETTINGS_SLEEP_TIME] << 8) + flash_buffer[FLASH_SETTINGS_SLEEP_TIME + 1]);
}