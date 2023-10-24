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


#include "evo70_r2_encoder.h"

static bool enc_pressed = false;
static uint32_t enc_pressed_duration = 0;
static uint32_t encoder_press_timer = 0;
static bool encoder_user_keycode_suppressed = false;
static bool encoder_user_rotation_suppressed = false;

void suppress_encoder_user_keycode(void) {
    encoder_user_keycode_suppressed = true;
}

void unsuppress_encoder_user_keycode(void) {
    encoder_user_keycode_suppressed = false;
}

void suppress_encoder_user_rotation(void) {
    encoder_user_rotation_suppressed = true;
}

void unsuppress_encoder_user_rotation(void) {
    encoder_user_rotation_suppressed = false;
}

bool handle_encoder_switch_process_record(keyrecord_t *record) {
    if (record->event.pressed) {
        enc_pressed = true;
        encoder_press_timer = timer_read32();
    } else
    {
        enc_pressed = false;
        enc_pressed_duration = timer_elapsed32(encoder_press_timer);
    }
    if (encoder_user_keycode_suppressed) {
        return false;
    } else {
        return true;
    }
}

bool get_enc_pressed(void) {
    return enc_pressed;
}

// return how long in ms the encoder has been pressed for
// if the encoder is not pressed, return how long the most recent press duration was
uint32_t get_enc_pressed_duration(void) {
    if (enc_pressed) {
        return timer_elapsed32(encoder_press_timer);
    } else {
        return enc_pressed_duration;
    }
}

static int enc_position = 0;

bool handle_encoder_rotation_process_record(keyrecord_t *record) {
    if (record->event.type == ENCODER_CW_EVENT) {
        enc_position--;
    }
    if (record->event.type == ENCODER_CCW_EVENT) {
        enc_position++;
    }
    
    if (encoder_user_rotation_suppressed) {
        return false;
    } else {
        return true;
    }
}


// Fetch how much the encoder has changed since this function was last called.

int get_enc_position_delta(void) {

    int enc_position_delta;
    enc_position_delta = enc_position;
    enc_position = 0;
    return enc_position_delta;
}

