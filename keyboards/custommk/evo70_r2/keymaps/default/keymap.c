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

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
// QWERTY
	[0] = LAYOUT(
			KC_NO,        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,     KC_5,    KC_6,     KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_DEL,
						  KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,     KC_T,    KC_Y,     KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_PGUP,
		KC_F1,   KC_F2,   KC_CAPS, 			KC_A,    KC_S,    KC_D,     KC_F,    KC_G,     KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,  KC_PGDN,
	    KC_F3,   KC_F4,	  KC_LSFT, KC_NUBS, KC_Z,    KC_X,    KC_C,     KC_V,    KC_B,     KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, KC_UP,   KC_END,
		KC_F5,   KC_F6,   KC_LCTL, KC_LWIN,          KC_LALT,                    KC_SPACE,                   KC_RALT, KC_RCTL,          KC_LEFT, KC_DOWN, KC_RGHT),

// DVORAK
	[1] = LAYOUT(
			KC_NO,        KC_ESC, KC_1,     KC_2,    KC_3,    KC_4,     KC_5,    KC_6,     KC_7,    KC_8,    KC_9,    KC_0,    KC_LBRC, KC_RBRC, KC_BSPC, KC_DEL,
						  KC_TAB,  KC_QUOT, KC_COMM, KC_DOT,  KC_P,     KC_Y,    KC_F,     KC_G,    KC_C,    KC_R,    KC_L,    KC_SLSH, KC_EQL,  KC_BSLS, KC_PGUP,
		KC_F1,   KC_F2,   KC_CAPS, 			KC_A,    KC_O,    KC_E,     KC_U,    KC_I,     KC_D,    KC_H,    KC_T,    KC_N,    KC_S,    KC_MINS, KC_ENT,  KC_PGDN,
	    KC_F3,   KC_F4,	  KC_LSFT, KC_NUBS, KC_SCLN, KC_Q,    KC_J,     KC_K,    KC_X,     KC_B,    KC_M,    KC_W,    KC_V,    KC_Z, KC_RSFT, KC_UP,   KC_END,
		KC_F5,   KC_F6,   KC_LCTL, KC_LWIN,          KC_LALT,                    KC_SPACE,                   KC_RALT, KC_RCTL,          KC_LEFT, KC_DOWN, KC_RGHT),

// COLEMAK
	[2] = LAYOUT(
			KC_NO,        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,     KC_5,    KC_6,     KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_DEL,
						  KC_TAB,  KC_Q,    KC_W,    KC_F,    KC_P,     KC_G,    KC_J,     KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_LBRC, KC_RBRC, KC_BSLS, KC_PGUP,
		KC_F1,   KC_F2,   KC_CAPS, 			KC_A,    KC_R,    KC_S,     KC_T,    KC_D,     KC_H,    KC_N,    KC_E,    KC_I,    KC_O,    KC_QUOT, KC_ENT,  KC_PGDN,
	    KC_F3,   KC_F4,	  KC_LSFT, KC_NUBS, KC_Z,    KC_X,    KC_C,     KC_V,    KC_B,     KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, KC_UP,   KC_END,
		KC_F5,   KC_F6,   KC_LCTL, KC_LWIN,          KC_LALT,                    KC_SPACE,                   KC_RALT, KC_RCTL,          KC_LEFT, KC_DOWN, KC_RGHT),

// WORKMAN
	[3] = LAYOUT(
			KC_NO,        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,     KC_5,    KC_6,     KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_DEL,
						  KC_TAB,  KC_Q,    KC_D,    KC_R,    KC_W,     KC_B,    KC_J,     KC_F,    KC_U,    KC_P,    KC_SCLN, KC_LBRC, KC_RBRC, KC_BSLS, KC_PGUP,
		KC_F	 1,   KC_F2,   KC_CAPS, 			KC_A,    KC_S,    KC_H,     KC_T,    KC_G,     KC_Y,    KC_N,    KC_E,    KC_O,    KC_I,    KC_QUOT, KC_ENT,  KC_PGDN,
	    KC_F3,   KC_F4,	  KC_LSFT, KC_NUBS, KC_Z,    KC_X,    KC_M,     KC_C,    KC_V,     KC_K,    KC_L,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, KC_UP,   KC_END,
		KC_F5,   KC_F6,   KC_LCTL, KC_LWIN,          KC_LALT,                    KC_SPACE,                   KC_RALT, KC_RCTL,          KC_LEFT, KC_DOWN, KC_RGHT),
};


#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] =   { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [1] =   { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [2] =   { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [3] =   { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) }

};
#endif