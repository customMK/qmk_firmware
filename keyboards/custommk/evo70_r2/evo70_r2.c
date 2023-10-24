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

#include "evo70_r2.h"
#include <stdbool.h>
#include "matrix.h"
#include "evo70_r2_graphics.h"
#include "rtc.h"
#include "i2c_temperature.h"
#include "evo70_r2_encoder.h"
#include "lcd_backlight.h"
#include "display_control.h"
#include "eeconfig.h"
#include "layer_settings.h"


#define ENCODER_MATRIX_ROW 1
#define ENCODER_MATRIX_COL 0

extern audio_config_t audio_config;
extern backlight_config_t backlight_config;

static bool eeprom_was_reset = false;

void matrix_init_kb(void) {

    user_config.raw = eeconfig_read_kb();
    if (user_config.eeprom_canary == false) { //EEPROM was cleared
        user_config.eeprom_canary = true;
        user_config.current_screen  = 0;
        user_config.breathing_period = 1; //disabled
        user_config.display_on = true;
        user_config.report_temperature_in_f = true;
        user_config.display_timeout_setting = 0; //never
        user_config.lcd_backlight_brightness = 15; //100%
        user_config.date_format = 5;
        user_config.hide_seconds = false;
        user_config.display_off_was_auto_timeout = true;
        update_kb_eeprom();

        eeprom_was_reset = true;

    }
    matrix_init_user();
}


void keyboard_post_init_kb(void) {

#ifdef EXTERNAL_FLASH_SPI_SLAVE_SELECT_PIN
    setPinOutput(EXTERNAL_FLASH_SPI_SLAVE_SELECT_PIN);
    writePinHigh(EXTERNAL_FLASH_SPI_SLAVE_SELECT_PIN);
#endif // EXTERNAL_FLASH_SPI_SLAVE_SELECT_PIN
    lcd_backlight_init();
    keyboard_post_init_display();

    init_temperature_i2c();
    rtc_refresh_time();

    if (eeprom_was_reset) {
        eeprom_was_reset = false;
        backlight_level(BACKLIGHT_LEVELS); // backlight all the way on
        rgblight_mode(RGBLIGHT_MODE_RAINBOW_SWIRL + 5);
    }

    if (user_config.breathing_period < 2 ) {
        breathing_disable();
        user_config.breathing_period = 1;
    }
    else {
        breathing_period_set(user_config.breathing_period);
        breathing_enable();
    }

    set_default_layer_in_settings_menu_noeeprom(biton(eeconfig_read_default_layer()));
    // Allow for user post-init
    keyboard_post_init_user();

}

static uint32_t display_housekeeping_time = 0;

void housekeeping_task_kb(void) {
    static uint32_t temperature_timer;
    if (timer_elapsed32(display_housekeeping_time) > 40) {
        display_housekeeping_time = timer_read32();
        rtc_refresh_time();
        display_housekeeping_task();
    
        // We exit the function here because I2C is slow and the display processing is slow.
        // By exiting here, the display update (if it's due to update) can happen *after*
        // running another matrix scan. Matrix scanning with the smallest time gaps is more important
        // than tiny delay to temperature measurement updating
        return;
    }

    if (timer_elapsed32(temperature_timer) > TEMPERATURE_UPDATE_PERIOD) {
        temperature_timer = timer_read32();
        update_temperature_i2c();
    }
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {

    // Something happened, if the display was off due to timeout, turn it back on
    if (is_display_off_due_to_timeout()) {
        turn_display_on();
    }

    // check for encoder press/release
    if (record->event.key.row == ENCODER_MATRIX_ROW && record->event.key.col == ENCODER_MATRIX_COL){
        if(handle_encoder_switch_process_record(record)== false) {
            return false;
        }
    }
    // check for encoder rotation
    if (IS_ENCODEREVENT(record->event)) {
        if (handle_encoder_rotation_process_record(record) == false) {
            return false;
        }
    }
    return process_record_user(keycode, record);
}

void update_kb_eeprom(void) {
    eeconfig_update_kb(user_config.raw);
}