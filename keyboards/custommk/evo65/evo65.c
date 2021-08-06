/* Copyright 2021 customMK
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

#include "evo65.h"
#include <stdbool.h>

#ifdef QWIIC_MICRO_OLED_ENABLE
#include "micro_oled.h"
#include "qwiic.h"
#endif

#define LAYER_DISPLAY_X 5
#define LAYER_DISPLAY_Y 0
#define ENC_DISPLAY_X 50
#define ENC_DISPLAY_Y 0

#define LOCK_DISPLAY_X 5
#define LOCK_DISPLAY_Y 15
#define RGB_DISPLAY_X 55
#define RGB_DISPLAY_Y 15

#define WPM_DISPLAY_X 80
#define WPM_DISPLAY_Y 15


/* Encoder Parameters */
uint8_t enc_mode = 0;

char* enc_mode_str[] = {"VOL", "MED", "SCR", "VIA"};
uint8_t num_enc_mode = sizeof(enc_mode_str) / sizeof(enc_mode_str[0]);
uint16_t enc_cw[] =  { KC_VOLU, KC_MEDIA_NEXT_TRACK, KC_WH_D };
uint16_t enc_ccw[] = { KC_VOLD, KC_MEDIA_PREV_TRACK, KC_WH_U };

uint16_t wpm = 0;

bool send_oled = false;

keyevent_t encoder_ccw = {
    .key = (keypos_t){.row = 4, .col = 4},
    .pressed = false
};

keyevent_t encoder_cw = {
    .key = (keypos_t){.row = 4, .col = 5},
    .pressed = false
};

void matrix_init_kb(void) {
	
	matrix_init_user();
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {

	if (record->event.key.row == 3 && record->event.key.col == 0){
		if (record->event.pressed) {
			enc_mode = (enc_mode + 1) % num_enc_mode;
		}
	}
    send_oled = true;

	return process_record_user(keycode, record);
}


bool encoder_update_kb(uint8_t index, bool clockwise) {
    if (!encoder_update_user(index, clockwise)) return false;
	if (enc_mode == num_enc_mode - 1) {
		if (clockwise) {
			encoder_cw.pressed = true;
			encoder_cw.time = (timer_read() | 1);
			action_exec(encoder_cw);
			
    	}
		else {
			encoder_ccw.pressed = true;
			encoder_ccw.time = (timer_read() | 1);
			action_exec(encoder_ccw);
		}
	}
	else {
		if (clockwise) {
			tap_code(enc_cw[enc_mode]);
		} else {
			tap_code(enc_ccw[enc_mode]);
		}
	}
	return true;
}
	

/* OLED Draw Functions */
void draw_keyboard_layer(void){
    draw_string(LAYER_DISPLAY_X, LAYER_DISPLAY_Y + 2, "LAYER", PIXEL_ON, NORM, 0);

    draw_rect_filled_soft(LAYER_DISPLAY_X + 31, LAYER_DISPLAY_Y, 11, 11, PIXEL_ON, NORM);
    draw_char(LAYER_DISPLAY_X + 34, LAYER_DISPLAY_Y + 2, get_highest_layer(layer_state) + 0x30, PIXEL_ON, XOR, 0);
}

void draw_enc_mode(void){
	draw_string(ENC_DISPLAY_X, ENC_DISPLAY_Y + 2, "ENC", PIXEL_ON, NORM, 0);
    draw_rect_filled_soft(ENC_DISPLAY_X + 19, ENC_DISPLAY_Y, 21, 11, PIXEL_ON, NORM);
    draw_string(ENC_DISPLAY_X + 21, ENC_DISPLAY_Y + 2, enc_mode_str[enc_mode], PIXEL_ON, XOR, 0);
}

void draw_rgb_info(void) {
	draw_rect_soft(RGB_DISPLAY_X, RGB_DISPLAY_Y, 22, 11, PIXEL_ON, NORM);
	draw_string(RGB_DISPLAY_X + 3, RGB_DISPLAY_Y +2, "rgb", PIXEL_ON, NORM, 0);
}

void draw_wpm(void) {
    int remainder = 0;
	char wpm_str[4] = "   ";
	if (wpm > 999) {
		wpm = 999;
	}
	else  {
		remainder = wpm % 10;
		wpm_str[2] = 48 + remainder;
		wpm = (wpm - remainder)/10;
		if (wpm > 0) {
			remainder = wpm % 10;
			wpm_str[1] = 48 + remainder;
			wpm = (wpm - remainder)/10;
			if (wpm > 0) {
				remainder = wpm % 10;
				wpm_str[0] = 48 + remainder;
			}
		}
	}

	draw_string(WPM_DISPLAY_X + 3, WPM_DISPLAY_Y +2, wpm_str, PIXEL_ON, NORM, 0);	
	draw_rect_soft(WPM_DISPLAY_X, WPM_DISPLAY_Y, 22, 11, PIXEL_ON, NORM);

}

void draw_keyboard_locks(void) {
	led_t led_state = host_keyboard_led_state();
    if (led_state.caps_lock == true) {
        draw_rect_filled_soft(LOCK_DISPLAY_X + 0, LOCK_DISPLAY_Y, 5 + (3 * 6), 11, PIXEL_ON, NORM);
        draw_string(LOCK_DISPLAY_X + 3, LOCK_DISPLAY_Y +2, "CAP", PIXEL_OFF, NORM, 0);
    } else if (led_state.caps_lock == false) {
        draw_rect_filled_soft(LOCK_DISPLAY_X + 0, LOCK_DISPLAY_Y, 5 + (3 * 6), 11, PIXEL_OFF, NORM);
        draw_rect_soft(LOCK_DISPLAY_X + 0, LOCK_DISPLAY_Y, 5 + (3 * 6), 11, PIXEL_ON, NORM);
        draw_string(LOCK_DISPLAY_X + 3, LOCK_DISPLAY_Y +2, "CAP", PIXEL_ON, NORM, 0);
    }

	if (led_state.num_lock == true) {
        draw_rect_filled_soft(LOCK_DISPLAY_X + 26, LOCK_DISPLAY_Y, 5 + (3 * 6), 11, PIXEL_ON, NORM);
        draw_string(LOCK_DISPLAY_X + 29, LOCK_DISPLAY_Y +2, "NUM", PIXEL_OFF, NORM, 0);
    } else if (led_state.num_lock == false) {
        draw_rect_filled_soft(LOCK_DISPLAY_X + 26, LOCK_DISPLAY_Y, 5 + (3 * 6), 11, PIXEL_OFF, NORM);
        draw_rect_soft(LOCK_DISPLAY_X + 26, LOCK_DISPLAY_Y, 5 + (3 * 6), 11, PIXEL_ON, NORM);
        draw_string(LOCK_DISPLAY_X + 29, LOCK_DISPLAY_Y +2, "NUM", PIXEL_ON, NORM, 0);
    }
}



void init_oled(void) {
	clear_buffer();
	
	draw_keyboard_layer();
	draw_enc_mode();
	draw_keyboard_locks();
	draw_rgb_info();
	draw_wpm();
}

void draw_display(void) {
	draw_keyboard_layer();
	draw_enc_mode();
	draw_rgb_info();
	draw_keyboard_locks();
	draw_wpm();
	send_buffer();
}


void matrix_scan_kb(void) {
	if (send_oled) {
		draw_display();
		send_oled = false;
	}

	if (enc_mode == num_enc_mode - 1) {
		if (IS_PRESSED(encoder_ccw)) {
			encoder_ccw.pressed = false;
			encoder_ccw.time = (timer_read() | 1);
			action_exec(encoder_ccw);
    	}

		if (IS_PRESSED(encoder_cw)) {
			encoder_cw.pressed = false;
			encoder_cw.time = (timer_read() | 1);
			action_exec(encoder_cw);
		}
	}

	wpm = get_current_wpm();
	
	matrix_scan_user();
}

void keyboard_post_init_user(void){
	init_oled();
}
