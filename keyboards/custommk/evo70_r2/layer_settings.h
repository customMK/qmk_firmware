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

uint8_t get_default_layer_setting(void);

void increment_default_layer(void);
void decrement_default_layer(void);

void set_default_layer_in_settings_menu_noeeprom(uint8_t layernum);
void set_default_layer_in_settings_menu(uint8_t layernum);

layer_state_t default_layer_state_set_kb(layer_state_t state);
void update_latest_default_layer_from_eeprom(void);

uint8_t get_active_layer_setting(void);

void increment_active_layer(void);
void decrement_active_layer(void);

layer_state_t default_layer_state_set_kb(layer_state_t state);
