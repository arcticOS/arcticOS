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

// Hardware Commands
void cellular_init();

// SIM-Related Commands
void cellular_request_imsi(char* buffer, int length); // Get IMSI to buffer
void cellular_sim_status(char* buffer, int length); // Get SIM status to buffer
void cellular_sim_enter_pin(char* buffer); // Enter SIM PIN (4 characters)
int cellular_sim_pin_attempts(); // Get SIM PIN attempts remaining

// Time-Related Commands
void cellular_time_gmt(char* buffer, int length); // Get GMT time to buffer
void cellular_time_local(char* buffer, int length); // Get local time to buffer

// Network-Related Commands
void cellular_network_technology(char* buffer, int length); // Get network technology 
void cellular_network_name(char* buffer, int length); // Get network name
int cellular_get_signal_strength(); // Get signal strength from 1-10

// Call-Related Commands
void cellular_call_answer(); // Answer incoming call
void cellular_call_end(); // End current call
void cellular_dial(char* buffer); // Dial a call (buffer size 32, null-terminated string)
bool cellular_ringing(); // True if phone should be ringing
void cellular_dtmf(char character); // Send DTMF tone

// SMS-Related Commands
void cellular_sms_next(char* buffer, int length); // Get data of next incoming SMS
void cellular_sms_send(char* number, char* data, int data_length); // Send SMS (number buffer size 32, data buffer size variable)

#if defined(EVT4)
#include <arcticOS/drivers/net/ec25/cellular.h>
#elif defined(EVT3)
#include <arcticOS/drivers/net/ec25/cellular.h>
#endif