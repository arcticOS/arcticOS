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
 * arcticOS Menu system
 * 
 * Menus in arcticOS are called from inside the interface process. They are passed
 * a debounced keypress value and are expected to return quickly - loops are discouraged
 * as if the interface takes too long to finish the system process assumes the worst
 * and kernel panics.
 *
 * The interface process has some handlers that it will call when some events happen - 
 * these are set from arcticOS.c before the tasks are created. If any of them remain
 * unset when the process starts, the interface process kernel panics.
 */

// General Menus

// Call-Related Menus
void menu_incoming_call(char keypress);
void menu_in_call(char keypress);

// SMS-Related Menus
void menu_incoming_sms(char keypress);
