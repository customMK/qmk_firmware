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

bool handle_encoder_switch_process_record(keyrecord_t *record);
bool handle_encoder_rotation_process_record(keyrecord_t *record);

bool get_enc_pressed(void);

// return how long in ms the encoder has been pressed for
// if the encoder is not pressed, return how long the most recent press duration was
uint32_t get_enc_pressed_duration(void);

// Fetch how much the encoder has changed since this function was last called.
int get_enc_position_delta(void);

void suppress_encoder_user_keycode(void);
void unsuppress_encoder_user_keycode(void);

void suppress_encoder_user_rotation(void);
void unsuppress_encoder_user_rotation(void);

