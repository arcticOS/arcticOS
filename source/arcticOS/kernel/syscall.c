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

#include <hardware/irq.h>

struct syscall_params {
    int type;
    uint16_t param0;
    uint16_t param1;
    uint16_t param2;
    uint16_t param3;
    char* data;

    int* return_pointer;
};

void do_system_call(int type, uint16_t param0, uint16_t param1, uint16_t param2, uint16_t param3) {
    struct syscall_params params;
    params.type = type;
    params.param0 = param0;
    params.param1 = param1;
    params.param2 = param2;
    params.param3 = param3;
    asm volatile("mov R1, %0" : : "r" (&params));
    irq_set_pending(30);
}

void do_data_system_call(int type, char* data) {
    struct syscall_params params;
    params.type = type;
    params.data = data;
    asm volatile("mov R1, %0" : : "r" (&params));
    irq_set_pending(30);
}
void do_returning_data_system_call(int type, char* data, int* pointer) {
    struct syscall_params params;
    params.type = type;
    params.data = data;
    params.return_pointer = pointer;
    asm volatile("mov R1, %0" : : "r" (&params));
    irq_set_pending(30);
}

void do_returning_system_call(int type, uint16_t param0, uint16_t param1, uint16_t param2, uint16_t param3, int* pointer) {
    struct syscall_params params;
    params.type = type;
    params.param0 = param0;
    params.param1 = param1;
    params.param2 = param2;
    params.param3 = param3;
    params.return_pointer = pointer;
    asm volatile("mov R1, %0" : : "r" (&params));
    irq_set_pending(30);
}