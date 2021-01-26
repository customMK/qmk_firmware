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
#include "quantum.h"
#include "timer.h"

#ifdef QWIIC_MICRO_OLED_ENABLE
#include "micro_oled.h"
#include "qwiic.h"
#endif

#define BAT_DISPAY_X 5
#define BAT_DISPLAY_Y 0
#define MATRIX_DISPLAY_X 5
#define MATRIX_DISPLAY_Y 16
#define LOCK_DISPLAY_X 45
#define LOCK_DISPLAY_Y 18
#define MOD_DISPLAY_X 74
#define MOD_DISPLAY_Y 18
#define LAYER_DISPLAY_X 39
#define LAYER_DISPLAY_Y 0
#define ENC_DISPLAY_X 86
#define ENC_DISPLAY_Y 0

bool led_numlock = false;
bool led_capslock = false;
bool led_scrolllock = false;

bool send_oled = false;

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {


    send_oled = true;

	return process_record_user(keycode, record);
}

/*
bool process_record_user(uint16_t keycode, keyrecord_t *record){
	
	if (record->event.key.row == 0 && record->event.key.col == 14){
		if (record->event.pressed) {
			change_encoder_mode(true);
			return false;	
		}
	}
	
	//send_oled = true;

	return true;
}
*/

__attribute__((weak)) void encoder_update_user(uint8_t index, bool clockwise) {
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

void draw_keyboard_locks(void) {
    draw_string(LAYER_DISPLAY_X, LAYER_DISPLAY_Y + 2, "LAYER", PIXEL_ON, NORM, 0);
}

void init_oled(void) {
	clear_buffer();
	draw_keyboard_locks();
}

void draw_display(void) {
	draw_keyboard_locks();
	send_buffer();
}

void keyboard_post_init_user(void){
	init_oled();

}

void matrix_scan_kb(void) {
	if (send_oled) {
		draw_display();
		send_oled = false;
	}
	
	matrix_scan_user();
}

#ifdef OLED_DRIVER_ENABLE
__attribute__((weak)) void oled_task_user(void) {
    // Host Keyboard Layer Status
    oled_write_P(PSTR("Layer: "), false);

	static char layer_num[3] = {0};
	snprintf(layer_num, sizeof(layer_num), "%d", get_highest_layer(layer_state));
	oled_write(layer_num, false);

	//oled_write_P(PSTR("   "), false);
	
	static char encoder_mode[12] = {0};
	snprintf(encoder_mode, sizeof(encoder_mode), "   %s", print_encoder_mode());
	oled_write(encoder_mode, false);
	
	oled_write_P(PSTR("\n"), false);

	/*
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
	*/

    // Host Keyboard LED Status
    led_t led_state = host_keyboard_led_state();
    //oled_write_P(led_state.num_lock ? PSTR("NUM ") : PSTR("    "), false);
	if (led_state.num_lock) {
		oled_write_P(PSTR("NUM "), true);
	} else {
		oled_write_P(PSTR("NUM "), false);
	}
    oled_write_P(led_state.caps_lock ? PSTR("CAP ") : PSTR("    "), false);
    oled_write_P(led_state.scroll_lock ? PSTR("SCR ") : PSTR("    "), false);

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
	