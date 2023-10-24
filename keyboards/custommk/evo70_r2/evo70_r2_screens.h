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

#include "evo70_r2_encoder.h"
#include "evo70_r2.h"

#pragma once

enum display_screen_t {
    settings_screen,
    lcd_analog_clock,
    screen_datetime,
    bongocat_screen,
    custommk_logo_screen,
    custom_graphic_screen
};

typedef enum display_screen_t display_screen_t;

typedef enum {
    exit_settings,
    active_layer,
    backlight_brightness,
    backlight_breathing_period,
    underglow_mode,
    underglow_brightness,
    underglow_color,
    temperature_units,
    display_timeout,
    time_format,
    hide_seconds,
    date_format,
    set_year,
    set_month,
    set_day,
    set_hour,
    set_minute,
    set_second,
    audio_enable,
    lcd_brightness,
    default_layer
} settings_menu_item_t;



void display_management_init(void);

void display_management_task(void);

void adjust_setting(bool increase);
void change_screen(void);
void increment_screen(void);
void decrement_screen(void);

void show_new_screen(void);

void increment_menu_item(void);
void decrement_menu_item(void);

display_screen_t get_current_screen(void);

settings_menu_item_t get_current_menu_item(void);