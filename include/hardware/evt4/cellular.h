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

#ifndef CELLULAR_H
#define CELLULAR_H

#include <stdio.h>
#include <pico/stdlib.h>
#include <hardware/uart.h>

#define CELLULAR_DEFAULT_BAUDRATE 115200

#define CELLULAR_DEFAULT_UART uart0

void cellular_init(int tx_pin, int rx_pin, int baudrate, int uart) {
    uart_init(uart, baudrate);
    
    gpio_set_function(tx_pin, GPIO_FUNC_UART);
    gpio_set_function(rx_pin, GPIO_FUNC_UART);
}
#endif