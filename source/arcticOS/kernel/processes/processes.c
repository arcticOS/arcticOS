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

#include <arcticOS/kernel/processes.h>
#include <arcticOS/kernel/ipc.h>
#include <FreeRTOS/FreeRTOS.h>
#include <FreeRTOS/task.h>
#include <FreeRTOS/queue.h>
#include <stdint.h>

QueueHandle_t sysq;

void os_create_processes() {
    // First create the system queue
    sysq = xQueueCreate(1, sizeof(uint32_t));
    if(!sysq) system_panic("Failed to init system queue");

    // Then create both processes
    xTaskCreate(process_system, "system", 256, NULL, 1, NULL);
    xTaskCreate(process_interface, "interface", 256, NULL, 1, NULL);
}