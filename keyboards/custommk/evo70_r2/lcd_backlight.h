
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

#include "quantum.h"
#pragma once

void turn_off_lcd_backlight(void);
void turn_on_lcd_backlight(void);

void set_lcd_backlight_level(uint8_t);
uint8_t get_lcd_backlight_level(void);

void lcd_decrement_brightness(void);
void lcd_increment_brightness(void);

void lcd_backlight_init(void);