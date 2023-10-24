

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

#include "backlight_breathing.h"

extern user_config_t user_config;

void backlight_breathing_period_increment(void) {
    if (user_config.breathing_period < 15) {
        user_config.breathing_period++;
        update_breathing();
    }
}

void backlight_breathing_period_decrement(void) {
    if (user_config.breathing_period > 2) {
        user_config.breathing_period--;
    } 
    else {
        user_config.breathing_period = 1;
    }
    update_breathing();
}

void update_breathing(void) {
    if (user_config.breathing_period == 1) {
        breathing_disable();
    }
    else {
        breathing_period_set(user_config.breathing_period);
        breathing_enable();
    }
    update_kb_eeprom();
}