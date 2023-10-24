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

#include "layer_settings.h"
#include "evo70_r2.h"

// This file handles changes to the Active Layer and Default Layer in the settings menu


// the layer settings don't have dedicated files, so we'll handle them right here
static uint8_t active_layer_from_settings_menu = 0;
static uint8_t default_layer_from_settings_menu = 0;

uint8_t get_default_layer_setting(void) {
    update_latest_default_layer_from_eeprom();
    return default_layer_from_settings_menu;
}

void increment_default_layer(void) {
    default_layer_from_settings_menu = (default_layer_from_settings_menu + 1) % 32; //32 is the maximum number of default layers
    set_single_persistent_default_layer(default_layer_from_settings_menu);
}

void decrement_default_layer(void) {
    default_layer_from_settings_menu = (32 + default_layer_from_settings_menu - 1) % 32;
    set_single_persistent_default_layer(default_layer_from_settings_menu);
}

void set_default_layer_in_settings_menu_noeeprom(uint8_t layernum) {
    if (layernum > 31) {
        layernum = 31;
    }
    default_layer_from_settings_menu = layernum;  
}
void set_default_layer_in_settings_menu(uint8_t layernum) {
    set_default_layer_in_settings_menu_noeeprom(layernum);
    set_single_persistent_default_layer(layernum);
}

static bool should_fetch_latest_default_layer_from_eeprom = true;

layer_state_t default_layer_state_set_kb(layer_state_t state) {
    // We don't know whether this is a transient change or one that is written to eeprom
    // All we know is that we should check the eeprom later (during housekeeping tasks)
    // and update the default layer here if needed. Current assumption is that QMK is
    // trending toward storing only a single default layer--but may change to be a bitmask...?
    should_fetch_latest_default_layer_from_eeprom = true;
    return default_layer_state_set_user(state);
}

void update_latest_default_layer_from_eeprom(void) {
    if (should_fetch_latest_default_layer_from_eeprom) {
        should_fetch_latest_default_layer_from_eeprom = false;
        set_default_layer_in_settings_menu_noeeprom(eeconfig_read_default_layer());
    }
}


uint8_t get_active_layer_setting(void) {
    return active_layer_from_settings_menu;
}

void increment_active_layer(void) {
    layer_off(active_layer_from_settings_menu);
    active_layer_from_settings_menu = (active_layer_from_settings_menu + 1) % 32; //32 is the maximum number of active layers
    layer_on(active_layer_from_settings_menu);
}

void decrement_active_layer(void) {
    layer_off(active_layer_from_settings_menu);
    active_layer_from_settings_menu = (32 + active_layer_from_settings_menu - 1) % 32;
    layer_on(active_layer_from_settings_menu);
}

