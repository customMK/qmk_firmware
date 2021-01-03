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

#include "cmk65.h"
#include "cmk65_encoder.h"

#define _QWERTY 0
#define _FN 1



bool process_record_user(uint16_t keycode, keyrecord_t *record){
	if (record->event.key.row == 0 && record->event.key.col == 14){
		if (record->event.pressed) {
			change_encoder_mode(true);
			return false;	
		}
	}

	/*
	switch (keycode) {
		case ENC_PRESS:
			if (record->event.pressed) {
				change_encoder_mode(true);
			} 
			return false;
		default:
			break;
	}
	*/
	return true;
}


__attribute__((weak)) void encoder_update_user(uint8_t index, bool clockwise) {
	/*
	if (index == 0) {
		if (clockwise) {
			tap_code(KC_VOLU);
		} else {
			tap_code(KC_VOLD);
		}	
	}
	*/

	uint16_t mapped_code = 0;
	if (index == 0) {
		if (clockwise) {
			mapped_code = handle_encoder_cw();
		} else {
			mapped_code = handle_encoder_ccw();
		}

		if(mapped_code != 0){
			tap_code(mapped_code);
		}
	}

}

#ifdef OLED_DRIVER_ENABLE
__attribute__((weak)) void oled_task_user(void) {
    // Host Keyboard Layer Status
    oled_write_P(PSTR("Layer: "), false);

    switch (get_highest_layer(layer_state)) {
        case _QWERTY:
            oled_write_P(PSTR("Default\n"), false);
            break;
        case _FN:
            oled_write_P(PSTR("FN\n"), false);
            break;
        default:
            // Or use the write_ln shortcut over adding '\n' to the end of your string
            oled_write_ln_P(PSTR("Undefined"), false);
    }

    // Host Keyboard LED Status
    led_t led_state = host_keyboard_led_state();
    oled_write_P(led_state.num_lock ? PSTR("NUM ") : PSTR("    "), false);
    oled_write_P(led_state.caps_lock ? PSTR("CAP ") : PSTR("    "), false);
    oled_write_P(led_state.scroll_lock ? PSTR("SCR ") : PSTR("    "), false);

	static char encoder_mode[8] = {0};
	snprintf(encoder_mode, sizeof(encoder_mode), "ENC:%s", print_encoder_mode());
	oled_write(encoder_mode, false);
	

	oled_write_P(PSTR("\n"), false);

	#ifdef RGBLIGHT_ENABLE
	static char rgbStatusLine1[26] = {0};
	snprintf(rgbStatusLine1, sizeof(rgbStatusLine1), "RGB Mode: %d", rgblight_get_mode());
	oled_write_ln(rgbStatusLine1, false);
	static char rgbStatusLine2[26] = {0};
	snprintf(rgbStatusLine2, sizeof(rgbStatusLine2), "h:%d s:%d v:%d", rgblight_get_hue(), rgblight_get_sat(), rgblight_get_val());
	oled_write_ln(rgbStatusLine2, false);
	#endif
}
#endif
	