/*
 * arcticOS
 * Copyright (C) 2024 Johnny Stene
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

/*
 * EVT5 Keyboard Driver
 *
 * The EVT5 has a full QWERTY keyboard with (custom) modifier keys. It uses the 
 * TCA8418 chip from TI to handle the keyboard matrix, which then lets us query
 * the information over I2C. 
 */

#if defined(EVT5)
// Datasheet: https://www.ti.com/lit/ds/symlink/tca8418.pdf?ts=1734365985479

#include <hardware/gpio.h>
#include <hardware/i2c.h>

#define KEYBOARD_ADDRESS 0x00

void keyboard_init() {
    #if !defined(i2c_default) || !defined(PICO_DEFAULT_I2C_SDA_PIN) || !defined(PICO_DEFAULT_I2C_SCL_PIN)
        #error no default i2c pins found
    #endif

    i2c_init(i2c_default, 100 * 1000);
    gpio_set_function(PICO_DEFAULT_I2C_SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(PICO_DEFAULT_I2C_SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(PICO_DEFAULT_I2C_SDA_PIN);
    gpio_pull_up(PICO_DEFAULT_I2C_SCL_PIN);
}

char keyboard_get_character() {

}

int keyboard_is_pressed(char character) {


    return 0;
}

#endif