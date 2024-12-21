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
 * arcticOS System Processes
 * 
 * arcticOS uses two processes to handle all of the OS tasks - process_system
 * handles input, cellular, and other general OS tasks, and process_interface 
 * handles everything user-facing.
 *
 * The two processes communicate via SYSQ - see include/arcticOS/kernel/ipc.h
 * for more information.
 */

#ifndef PROCESSES_H
#define PROCESSES_H

#include <FreeRTOS/FreeRTOS.h>

/*
 * PROCESS_INTERFACE
 */
void (*interface_current_screen)(char); // Function pointer to current screen handler

// Handlers
void (*interface_incoming_call)(char); // Function pointer to incoming call handler
void (*interface_in_call)(char); // Function pointer to in-call handler
void (*interface_incoming_sms)(char); // Function pointer to incoming SMS handler

/*
 * FUNCTIONS
 */
void os_create_processes();

void process_system(void);
void process_interface(void);

#endif