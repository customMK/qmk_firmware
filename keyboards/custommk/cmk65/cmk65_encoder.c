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

#include "cmk65_encoder.h"

uint8_t encoder_mode = ENC_MODE_VOLUME;


uint16_t get_encoder_mode(void){
  return encoder_mode;
}

const char* print_encoder_mode(void){
  switch(encoder_mode){
    default:
      return "";
      break;
    case ENC_MODE_VOLUME:
      return "VOLUME";
      break;
    case ENC_MODE_MEDIA:
      return "MED CTRL";
      break;
    case ENC_MODE_SCROLL:
      return "MOUSEWHL";
      break;
    case ENC_MODE_BRIGHTNESS:
      return "RGB BR";
      break;
  }
}

void change_encoder_mode(bool clockwise) {

  encoder_mode = (encoder_mode + 1) % _NUM_ENCODER_MODES;

}

uint16_t handle_encoder_cw(void) {
	uint16_t mapped_code = 0;
  switch(encoder_mode){
    default:
    	break;
    case ENC_MODE_VOLUME:
      mapped_code = KC_VOLU;
      break;
    case ENC_MODE_MEDIA:
      mapped_code = KC_MEDIA_NEXT_TRACK;
      break;
    case ENC_MODE_SCROLL:
      mapped_code = KC_WH_D;
      break;
    case ENC_MODE_BRIGHTNESS:
      mapped_code = RGB_VAI;
      break;
  }
  return mapped_code;
}

uint16_t handle_encoder_ccw(void) {
  uint16_t mapped_code = 0;
  switch(encoder_mode){
    default:
    	break;
    case ENC_MODE_VOLUME:
      mapped_code = KC_VOLD;
      break;
    case ENC_MODE_MEDIA:
      mapped_code = KC_MEDIA_PREV_TRACK;
      break;
    case ENC_MODE_SCROLL:
      mapped_code = KC_WH_U;
      break;
    case ENC_MODE_BRIGHTNESS:
      mapped_code = RGB_VAD;
      break;
  }
  return mapped_code;
}
