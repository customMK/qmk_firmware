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

#include "evo70.h"
#include <stdbool.h>
#ifdef QWIIC_MICRO_OLED_ENABLE
#include "micro_oled.h"
#include "qwiic.h"
#endif

#define ENC_DISPLAY_X 0
#define ENC_DISPLAY_Y 0

#define LAYER_DISPLAY_X 5
#define LAYER_DISPLAY_Y 19

#define CAPSLOCK_DISPLAY_X 80
#define CAPSLOCK_DISPLAY_Y 19
#define NUMLOCK_DISPLAY_X 105
#define NUMLOCK_DISPLAY_Y 19


#define OLED_FONT 2

/* Encoder Parameters */
uint8_t enc_mode = 0;

#define ENCODER_MATRIX_ROW 5
#define ENCODER_MATRIX_COL 6

#define ENC_VOLUME 0
#define ENC_MEDIA 1
#define ENC_CUSTOM 2
#define ENC_BL_BRIGHT 3
#define ENC_RGB_BRIGHT 4
#define ENC_RGB_MODE 5
#define ENC_RGB_COLOR 6
#define ENC_SCROLL 7

char* enc_mode_str[] = {"Volume", \
    "Media Control", \
    "Custom",
	"Backlight Brightness", \
    "Underglow Brightness", \
    "Underglow Mode", \
	"Underglow Color", \
    "Scroll Wheel"
};

uint8_t enc_mode_str_startpos[] = {49, 28, 49, 7, 7, 25, 22, 31};
uint8_t num_enc_modes = 8;
uint16_t enc_cw[] =  { KC_VOLU, KC_MEDIA_NEXT_TRACK, 0, 0, 0, 0, 0, KC_WH_D };
uint16_t enc_ccw[] = { KC_VOLD, KC_MEDIA_PREV_TRACK, 0, 0, 0, 0, 0, KC_WH_U };

void draw_display(void);

bool send_oled = false;
static bool OLED_on = true;

void matrix_init_kb(void) {
	matrix_init_user();
}

__attribute__((weak)) void set_custom_encoder_mode_user(bool custom_encoder_mode) {}

void handle_encoder_switch_process_record(keyrecord_t *record) {
	static bool OLED_awakened = false;
    static uint32_t encoder_press_timer = 0;

	if (record->event.pressed) {
		if (OLED_on == false) {
		    OLED_on = true;
			OLED_awakened = true;
		} else {
            encoder_press_timer = timer_read32();
		}
	} else {
		if (OLED_awakened == true) {
			OLED_awakened = false;
		} else {
			if (timer_elapsed32(encoder_press_timer) < 300) {
				if (get_mods() & MOD_MASK_SHIFT) {
					enc_mode = (enc_mode + (num_enc_modes- 1)) % num_enc_modes;
				} else {
					enc_mode = (enc_mode + 1) % num_enc_modes;
				}
				set_custom_encoder_mode_user(enc_mode == ENC_CUSTOM);
			} else {
				OLED_on = false;
			}
		}
	}
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
	send_oled = true;
	if (record->event.key.row == ENCODER_MATRIX_ROW && record->event.key.col == ENCODER_MATRIX_COL){
		handle_encoder_switch_process_record(record);
		return false;
	} else {
	    return process_record_user(keycode, record);
	}
}

bool encoder_update_kb(uint8_t index, bool clockwise) {
    if (!encoder_update_user(index, clockwise)) return false;
    if (enc_mode == ENC_RGB_MODE) {
		if (clockwise) {
		    rgblight_step();
		} else {
            rgblight_step_reverse();
		}
	} else if (enc_mode == ENC_RGB_BRIGHT) {
		if (clockwise) {
		    rgblight_increase_val();
		} else {
            rgblight_decrease_val();
		}
	} else if (enc_mode == ENC_BL_BRIGHT) {
		if (clockwise) {
		    backlight_increase();
		} else {
            backlight_decrease();
		}
	} else if (enc_mode == ENC_RGB_COLOR) {
		if (clockwise) {
		    rgblight_increase_hue();
		} else {
            rgblight_decrease_hue();
		}
	} else {
		if (clockwise) {
			tap_code(enc_cw[enc_mode]);
		} else {
			tap_code(enc_ccw[enc_mode]);
		}
	}
	draw_display();
	return true;
}
	

/* OLED Draw Functions */

void draw_text_rectangle(uint8_t x, uint8_t y, uint8_t width, char* str, bool filled) {
	if (filled) {
		draw_rect_filled_soft(x, y, width, 11, PIXEL_ON, NORM);
	} else {
		draw_rect_filled_soft(x, y, width, 11, PIXEL_OFF, NORM);
		draw_rect_soft(x, y, width, 11, PIXEL_ON, NORM);
	}
    draw_string(x+3, y+2, str, PIXEL_ON, XOR, OLED_FONT);
}

void draw_keyboard_layer(void){
    draw_rect_filled_soft(LAYER_DISPLAY_X, LAYER_DISPLAY_Y, 48, 11, PIXEL_OFF, NORM);
	draw_string(LAYER_DISPLAY_X+3, LAYER_DISPLAY_Y+2, "0 1 2 3", PIXEL_ON, XOR, OLED_FONT);
	draw_rect_filled_soft(LAYER_DISPLAY_X + get_highest_layer(layer_state)*12, LAYER_DISPLAY_Y, 11, 11, PIXEL_ON, XOR);

	draw_line_hori(0, 14, 128, PIXEL_ON, NORM);

}

void draw_media_arrow(uint8_t x, uint8_t y, bool fwd) {
	draw_line_vert(x, y, 7, PIXEL_ON, XOR);
	draw_line_vert(x+4, y, 7, PIXEL_ON, XOR);
	draw_line_vert(x+2, y+2, 3, PIXEL_ON, XOR);
	if (fwd) {
	    draw_line_vert(x+1, y+1, 5, PIXEL_ON, XOR);
	    draw_line_vert(x+3, y+3, 1, PIXEL_ON, XOR);
	} else {
        draw_line_vert(x+3, y+1, 5, PIXEL_ON, XOR);
	    draw_line_vert(x+1, y+3, 1, PIXEL_ON, XOR);
	}
}

void draw_enc_mode(void){
    draw_rect_filled_soft(ENC_DISPLAY_X, ENC_DISPLAY_Y, 128, 11, PIXEL_OFF, NORM);
    draw_string(enc_mode_str_startpos[enc_mode], ENC_DISPLAY_Y + 2, enc_mode_str[enc_mode], PIXEL_ON, XOR, OLED_FONT);
	if (enc_mode == ENC_MEDIA) {
		draw_media_arrow(enc_mode_str_startpos[enc_mode] - 16, ENC_DISPLAY_Y + 2, false);
		draw_media_arrow(enc_mode_str_startpos[enc_mode] + 88, ENC_DISPLAY_Y + 2, true);
	}
}

void draw_keyboard_locks(void) {
	led_t led_state = host_keyboard_led_state();
    draw_text_rectangle(CAPSLOCK_DISPLAY_X, CAPSLOCK_DISPLAY_Y, 5 + (3 * 6), "CAP", led_state.caps_lock);
    draw_text_rectangle(NUMLOCK_DISPLAY_X, NUMLOCK_DISPLAY_Y, 5 + (3 * 6), "NUM", led_state.num_lock);
}

void draw_display(void) {
	clear_buffer();
	if (OLED_on) {
	    draw_keyboard_layer();
 	    draw_enc_mode();
        draw_keyboard_locks();
	}
	send_buffer();
}

void matrix_scan_kb(void) {
	if (send_oled ) {
		draw_display();
		send_oled = false;
	}

	matrix_scan_user();
}

