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

#pragma once

#include "quantum.h"
#include "qp.h"
#include "evo70_r2_graphics.h"
#include "keycodes.h"
#include "evo70_r2_encoder.h"

typedef union {
    uint32_t raw;
    struct {
        bool eeprom_canary : 1;
        bool display_on : 1;
        bool report_temperature_in_f : 1;
        bool time_format_in_24h : 1;
        uint8_t breathing_period : 4;

        uint8_t current_screen;

        uint8_t display_timeout_setting: 4;
        uint8_t lcd_backlight_brightness: 4;

        uint8_t date_format: 4;
        bool hide_seconds: 1;
        bool display_off_was_auto_timeout: 1;  // only valid when display_on == 0
    };
} user_config_t;

user_config_t user_config;

void update_kb_eeprom(void);