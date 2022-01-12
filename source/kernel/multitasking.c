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

// This is just a small wrapper around FreeRTOS
#include <freeRTOS/FreeRTOS.h>
#include <freeRTOS/task.h>
#define MAX_SERVICES 8

TaskHandle_t services[MAX_SERVICES];
int services_running[MAX_SERVICES];

int create_service(void (*handler)(void), const char* name) {
    for(int i = 0; i < MAX_SERVICES; i++) {
        if(services_running[i]) continue;
        services_running[i] = 1;
        xTaskCreate(handler, name, 512, NULL, 1, NULL);
        return i;
    }
    system_panic("Too many services");
    return -1;
}

void kill_service(int id) {
    vTaskDelete(services[id]);
    services_running[id] = 0;
}