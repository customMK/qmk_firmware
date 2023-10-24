
/* Copyright 2023 David Hoelscher (@customMK)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "evo70_r2.h"

#pragma once

enum display_timeout_t{
    never,
    sec10,
    sec30,
    sec60,
    min5,
    min15,
    hour1,
    hour8
};

typedef enum display_timeout_t display_timeout_t;

void display_decrease_timeout(void);

void display_increase_timeout(void);

uint32_t get_display_timeout_duration_ms(display_timeout_t duration);
char *get_display_timeout_duration_str(display_timeout_t duration);

void display_timeout_task(void);

void turn_display_on(void);
void turn_display_off(void);
void turn_display_off_auto_timeout(void);

bool is_display_on(void);
bool is_display_off_due_to_timeout(void); 
