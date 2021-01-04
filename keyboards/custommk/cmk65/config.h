/* Copyright 2020 customMK
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


#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0xF35B
#define PRODUCT_ID      0xFAB1
#define DEVICE_VER      0x0001
#define MANUFACTURER    customMK
#define PRODUCT         CMK65

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 15

/* key matrix pins */
#define MATRIX_ROW_PINS { D3, D2, F7, F6, F5 }
//changed col4 and col7 to other pins temporarily
#define MATRIX_COL_PINS { F0, F1, F4, E6, D0, B7, B0, D1, D4, D6, D7, B4, B5, B6, C6 }
#define UNUSED_PINS

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE

/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

#define ENCODERS_PAD_A { C7 }
#define ENCODERS_PAD_B { D5 }
#define ENCODER_RESOLUTION 4
#define TAP_CODE_DELAY 10

#define RGB_DI_PIN B2
#define RGBLIGHT_ANIMATIONS
#define RGBLED_NUM 30
#define RGBLIGHT_HUE_STEP 8
#define RGBLIGHT_SAT_STEP 8
#define RGBLIGHT_VAL_STEP 8
#define RGBLIGHT_LIMIT_VAL 128

