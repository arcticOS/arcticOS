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

#include <arcticOS.h>
#include <arcticOS/kernel/processes.h>
#include <arcticOS/kernel/ipc.h>
#include <FreeRTOS/FreeRTOS.h>
#include <FreeRTOS/queue.h>

void process_system(void) {
    // Init system process

    // System process loop
    for(;;) {
        uint32_t current_packet = 0x00000000;

        // Check cellular status
        // TODO: this
        current_packet |= SYSQ_CELL_CONNECTED;

        // Check button presses
        // TODO: this
        char pressed = '\0';
        current_packet |= pressed << 32;

        // Check battery voltage
        // TODO: this
        int chargestatus = 100;
        current_packet |= (chargestatus & 0b00000111) << 24;

        // Send packet
        if(xQueueSend(sysq, (void*) &current_packet, (TickType_t) 16) != pdPASS) {
            // Packet send failure
            system_panic("SYSQ full, interface hung?");
        }
    }
}