/* Copyright 2021 Nathan Spears
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


// Defines for task manager and such
#define CALTDEL LCTL(LALT(KC_DEL))
#define TSKMGR LCTL(LSFT(KC_ESC))

void keyboard_post_init_user(void) {
  debug_enable=true;
  debug_matrix=true;
  debug_keyboard=true;
}


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
* .-----------------------------------------------------------------------------------------------------------------------.
* |------+------+------+------+------+------+------+------+------+------+------+------+------+------+------+------+-------|
* | Tab  |   Q  |   W  |   E  |   R  |   T  | NLCK |  N7  |  N8  |  N9   | HOME |  Y   |   U  |   I  |   O  |  P  |  Bksp |
* |------+------+------+------+------+------+------+------+------+------+------+------+------+------+------+------+-------|
* |C(ESC)|   A  |   S  |   D  |   F  |   G  | INS  |  N4  |  N5  |  N6   | PgUp |  H   |  J   |   K  |   L  | '"  |  ;:   |
* |------+------+------+------+------+------+------+------+------+------+------+------+------+------+------+------+-------|
* |Shift |   Z  |   X  |   C  |   V  |   B  | DEL  |  N1  |  N2  |  N3   | PgDn |   N  |  M   |   ,  |   .  |   ?  |  Ent |
* |------+------+------+------+------+------+------+------+------+------+------+------+------+------+------+------+-------|
* | LCTRL| LOS  | LALT |   /  |   `  |   -  |  =   |  [   |TT(1) |LT(SPC)|   ]  | MENU | RALT | ROS  |RCTRL | CAPS |QK_BOOT |
* '-----------------------------------------------------------------------------------------------------------------------'
*/
[0] = LAYOUT_grid(
  KC_TAB,        KC_Q,       KC_W,    KC_E,    KC_R,   KC_T,    KC_NUM,  KC_P7,   KC_P8,   KC_P9,         KC_HOME,    KC_Y,    KC_U,    KC_I,     KC_O,     KC_P,    KC_BSPC,
  CTL_T(KC_ESC), KC_A,       KC_S,    KC_D,    KC_F,   KC_G,    KC_INS,  KC_P4,   KC_P5,   KC_P6,         KC_PGUP,    KC_H,    KC_J,    KC_K,     KC_L,     KC_SCLN, KC_QUOT,
  KC_LSFT,       KC_Z,       KC_X,    KC_C,    KC_V,   KC_B,    KC_DEL,  KC_P1,   KC_P2,   KC_P3,         KC_PGDN,    KC_N,    KC_M,    KC_COMM,  KC_DOT,   KC_SLSH, KC_ENT,
  KC_LCTL,       KC_LGUI,    KC_LALT, KC_BSLS, KC_GRV, KC_MINS, KC_EQL,  KC_LBRC, TT(1),   LT(2, KC_SPC), KC_RBRC,    KC_MENU, KC_RALT, KC_RGUI,  KC_RCTL,  KC_CAPS, QK_BOOT
),

/* 1
* .-----------------------------------------------------------------------------------------------------------------------.
* |------+------+------+------+------+------+------+------+------+------+------+------+------+------+------+------+-------|
* |  ~   |   !  |  @   |   #  |  $   |  %   |      |      |      |      |      |  ^   |  &   |  *   |  (   |   )  | Bksp  |
* |------+------+------+------+------+------+------+------+------+------+------+------+------+------+------+------+-------|
* |   \  |   1  |   2  |   3  |   4  |   5  |      |      |      |      |  6   |   7  |   8  |   9  |   0  |  /   |       |
* |------+------+------+------+------+------+------+------+------+------+------+------+------+------+------+------+-------|
* |      |      |      |      |      |      |      |      |      |      |      |      |     |       |   +  |   =  |       |
* |------+------+------+------+------+------+------+------+------+------+------+------+------+------+------+------+-------|
* |C.A.D.|TSKMGR|      |      |      |      |      |      |      |      |      |      |     |       | SPC  |   |  |   `   |
* '-----------------------------------------------------------------------------------------------------------------------'
*/
[1] = LAYOUT_grid(
  KC_TILD, KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC, _______, _______, _______, _______, _______, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC,
  KC_SLSH,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5, _______, _______, _______, _______,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_BSLS, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_PPLS,  KC_EQL, _______,
  CALTDEL,  TSKMGR, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_SPC, KC_NUBS,   KC_GRV
),

/* 2
* .----------------------------------------------------------------------------------------------------------------------.
* |------+------+------+------+------+------+------+------+------+------+------+------+------+------+------+------+------|
* | RHUI | RSAI |      |      |  UP  |      |      |      |      |      |      |      |   _  |      |  (   |  )  |  RVAI |
* |------+------+------+------+------+------+------+------+------+------+------+------+------+------+------+------+------|
* | RHUD | RSAD |      | LEFT | DOWN |RIGHT |      |      |      |      |      |      |   -  |      |   [  |   ]  | RVAD |
* |------+------+------+------+------+------+------+------+------+------+------+------+------+------+------+------+------|
* |      |  F1  |  F2  |  F3  |  F4  |  F5  |      |      |      |  F6  |  F7  |  F8  |  F9  | F10  | F11  | F12  |      |
* |------+------+------+------+------+------+------+------+------+------+------+------+------+------+------+------+------|
* |QK_BOOT | RTOG |      |      |      |      |      |      |      |      |      |      |      |      |      | RMOD |RRMOD |
* '----------------------------------------------------------------------------------------------------------------------'
*/
[2] = LAYOUT_grid(
  RGB_HUI,  RGB_SAI, _______, KC_UP,   _______, _______, _______, _______, _______, _______, _______, _______, KC_UNDS, _______, KC_LBRC, KC_RBRC, RGB_VAI,
  RGB_HUD,  RGB_SAD, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______, _______, _______, _______, _______, _______, KC_MINS, _______, KC_LCBR, KC_RCBR, RGB_VAD,
  _______,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   _______, _______, _______,   KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,  KC_F12, _______,
  QK_BOOT, RGB_TOG,  _______, _______, _______, _______,   _______, _______, _______, _______, _______, _______, _______, _______, _______, RGB_MOD, RGB_RMOD
),
};
