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


enum bongocat_show_state_t {
    bongocat_show_idle1,
    bongocat_show_idle2,
    bongocat_show_idle3,
    bongocat_show_idle4,
    bongocat_show_idle5,
    bongocat_show_prep,
    bongocat_show_tap1,
    bongocat_show_tap2
};

typedef enum bongocat_show_state_t bongocat_show_state_t;

void screen_bongocat_init(void);
void load_screen_bongocat(void);

void screen_bongocat_show_state(bongocat_show_state_t current_image_state);

void screen_bongocat_update_overlay(void);