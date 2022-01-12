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

#include <arcticOS/drivers/cpu.h>
#include <pico/stdlib.h>

void set_cpu_clock(int clock) {
    uint32_t clocks[5] = {CPU_OVERCLOCK_50MHZ, CPU_OVERCLOCK_100MHZ, CPU_OVERCLOCK_BASE, CPU_OVERCLOCK_200MHZ, CPU_OVERCLOCK_250MHZ};
    set_sys_clock_khz(clocks[clock], 0);
}