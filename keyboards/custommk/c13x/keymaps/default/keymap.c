// Copyright 2023 customMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_ESC,   KC_W,    KC_E, KC_R,   KC_T,   KC_Y, KC_U, KC_I, KC_O, KC_DEL,
        KC_MENU, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_CAPS,
        KC_LSFT, KC_X, KC_C, KC_V, KC_B, KC_B, KC_N, KC_M, KC_RSFT, MO(1),
        KC_LCTL, KC_LALT, KC_R, KC_SPC, KC_SPC, KC_GRV, KC_RCTL
    )
};
