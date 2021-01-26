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

#include QMK_KEYBOARD_H

enum encoder_modes {
  ENC_MODE_VOLUME,
  ENC_MODE_MEDIA,
  ENC_MODE_SCROLL,
  ENC_MODE_BRIGHTNESS, 
  _NUM_ENCODER_MODES
};


uint16_t 
  handle_encoder_cw(void),
  get_encoder_mode(void),
  handle_encoder_ccw(void);

void change_encoder_mode(bool clockwise);

const char* print_encoder_mode(void);