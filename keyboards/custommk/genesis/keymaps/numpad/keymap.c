/* Copyright 2020 David Hoelscher (customMK)
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

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	[0] = LAYOUT_NUM(
			MO(1),  KC_PSLS,  KC_PAST, KC_PMNS, 
			KC_P7,  KC_P8,    KC_P9,   ______, 
			KC_P4,  KC_P5,    KC_P6,   KC_PPLS, 
			KC_P1,  KC_P2,    KC_P3,   ______, 
			KC_P0,  ______,   KC_PDOT, KC_ENT),

	[1] = LAYOUT_NUM(
			KC_TRNS, KC_TRNS, RGB_TOG, RGB_MOD, 
			KC_TRNS, KC_TRNS, KC_TRNS, ______, 
			RGB_VAI, RGB_VAD, RGB_SPI, RGB_SPD, 
			KC_TRNS, KC_TRNS, KC_TRNS, ______, 
			RGB_HUI, ______,  KC_TRNS, RGB_HUD),

	[2] = LAYOUT_NUM(
			KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
			KC_TRNS, KC_TRNS, KC_TRNS, ______, 
			KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
			KC_TRNS, KC_TRNS, KC_TRNS, ______, 
			KC_TRNS, ______,  KC_TRNS, KC_TRNS),

	[3] = LAYOUT_NUM(
			KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
			KC_TRNS, KC_TRNS, KC_TRNS, ______, 
			KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
			KC_TRNS, KC_TRNS, KC_TRNS, ______, 
			KC_TRNS, ______,  KC_TRNS, KC_TRNS),

};


