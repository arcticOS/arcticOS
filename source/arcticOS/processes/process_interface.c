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
#include <arcticOS/processes.h>
#include <FreeRTOS/FreeRTOS.h>
#include <FreeRTOS/queue.h>

char interface_last_keypress;

void process_interface(void) {
    // Init interface process
    if(interface_incoming_call == NULL) system_panic("No incoming call handler");
    if(interface_in_call == NULL) system_panic("No in-call handler");
    if(interface_incoming_sms == NULL) system_panic("No incoming SMS handler");

    // Interface process loop
    for(;;) {
        // Get system packet
        uint32_t system_packet;
        if(xQueueReceive(sysq, &(system_packet), (TickType_t) 16) != pdPASS) {
            // Get packet failed
            system_panic("SYSQ empty, system hung?");
        }

        // Handle key debounce
        char keypress = (system_packet & SYSQ_BUTTON_PRESS) >> 24;
        if(keypress == interface_last_keypress) keypress = '\0';
        else interface_last_keypress = keypress; 

        if(system_packet & SYSQ_CELL_RINGING) interface_incoming_call(keypress);
        else if(system_packet & SYSQ_CELL_NEW_SMS) interface_incoming_sms(keypress);
        else if(system_packet & SYSQ_CELL_IN_CALL) interface_in_call(keypress);
        else {
            // Draw top bar
            // TODO: this

            // Run current screen
            if(interface_current_screen != NULL) interface_current_screen(keypress);    
        }
    }
}