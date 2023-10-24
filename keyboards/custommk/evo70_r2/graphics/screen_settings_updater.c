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
#include "quantum.h"
#include "evo70_r2_encoder.h"
#include "evo70_r2_screens.h"
#include "backlight_breathing.h"
#include "display_control.h"
#include "rtc.h"
#include "lcd_backlight.h"
#include "backlight.h"
#include "screen_settings.h"
#include "lcd_screen_analog_clock.h"
#include "date_format.h"
#include "layer_settings.h"

// This file abstractly manages which screen is shown, updates settings, and updates displayed values as needed

// This file should remain independent of LVGL (no "lv_" objects), and ideally should remain unchanged when moving
// to a newer version of LVGL (or anyt other display softawre)


#ifdef AUDIO_ENABLE
extern audio_config_t audio_config;
#endif
extern user_config_t user_config;
extern backlight_config_t backlight_config;

void update_settings_screen(void) {
    static uint8_t old_backlight_brightness = 0;
    if (backlight_config.level != old_backlight_brightness) {
        old_backlight_brightness = backlight_config.level;
        settings_update_backlight_brightness_value(backlight_config.level);
        //oled_update_backlight_brightness_value(user_config.settings_backlight_brightness);
    }

    static uint8_t old_backlight_breathing_period = 255;
    if (user_config.breathing_period != old_backlight_breathing_period) {
        old_backlight_breathing_period = user_config.breathing_period;
        settings_update_backlight_breathing_period(user_config.breathing_period);
        //oled_update_backlight_brightness_value(user_config.settings_backlight_brightness);
    }

    static uint8_t old_rgblight_mode = 255;
    if (rgblight_get_mode() != old_rgblight_mode) {
        //uprint("RGBlight mode changed\n");
        old_rgblight_mode = rgblight_get_mode();
        settings_update_underglow_mode(old_rgblight_mode);
        //oled_update_backlight_brightness_value(user_config.settings_backlight_brightness);
    }

    static uint8_t old_rgblight_value = 129;
    if (rgblight_get_val() != old_rgblight_value) {
        old_rgblight_value = rgblight_get_val();
        settings_update_underglow_brightness(old_rgblight_value);
        //oled_update_backlight_brightness_value(user_config.settings_backlight_brightness);
    }

    static uint16_t old_rgblight_hue = 256; // actual hue is 8 bit, so 256 is an impossible value
    if (rgblight_get_hue() != old_rgblight_hue) {
        old_rgblight_hue = rgblight_get_hue();
        settings_update_underglow_hue((uint8_t)old_rgblight_hue);
        //oled_update_backlight_brightness_value(user_config.settings_backlight_brightness);
    }


    static uint8_t old_temperature_unit_are_f = 2; // actual value is bool, so 2 is an impossible value
    if ((uint8_t)user_config.report_temperature_in_f != old_temperature_unit_are_f) {
        old_temperature_unit_are_f = user_config.report_temperature_in_f;
        settings_update_temperature_units_are_f((bool)old_temperature_unit_are_f);
        //oled_update_backlight_brightness_value(user_config.settings_backlight_brightness);
    }

//display timeout goes here
    static uint8_t old_display_timeout_setting = 20; // actual value is 1-8, so 20is an impossible value
    if ((uint8_t)user_config.display_timeout_setting != old_display_timeout_setting) {
        old_display_timeout_setting = user_config.display_timeout_setting;
        settings_update_display_timeout(user_config.display_timeout_setting);
        //oled_update_backlight_brightness_value(user_config.settings_backlight_brightness);
    }

    static uint8_t old_hide_seconds = 2; // actual value is bool, so 2 is an impossible value
    if ((uint8_t)user_config.hide_seconds != old_hide_seconds) {
        old_hide_seconds = user_config.hide_seconds;
        settings_update_hide_seconds((bool)old_hide_seconds);
    }

    static uint16_t old_year = 0;
    if (rtc_get_year() != old_year) {
        old_year = rtc_get_year();
        settings_update_year(old_year);
    }

    static uint8_t old_month = 0;
    if (rtc_get_month() != old_month) {
        old_month = rtc_get_month();
        settings_update_month(old_month);
    }

    static uint8_t old_day = 0;
    if (rtc_get_day() != old_day) {
        old_day = rtc_get_day();
        settings_update_day(old_day);
    }

    static uint8_t old_date_format = 9; // actual value is uint8_t:4, so 9 is an impossible value
    if ((uint8_t)user_config.date_format != old_date_format) {
        old_date_format = user_config.date_format;
        settings_update_date_format(old_date_format);
        settings_update_year(old_year);
        settings_update_month(old_month);
        settings_update_day(old_day);
    }

    static uint8_t old_hour = 0;
    if (rtc_get_hour24() != old_hour) {
        old_hour = rtc_get_hour24();
        settings_update_hour(old_hour);
    }

    static uint8_t old_time_format_in_24h = 2; // actual value is bool, so 2 is an impossible value
    if ((uint8_t)user_config.time_format_in_24h != old_time_format_in_24h) {
        old_time_format_in_24h = user_config.time_format_in_24h;
        settings_update_time_format_is_24h((bool)old_time_format_in_24h);
        settings_update_hour(old_hour);
    }

    static uint8_t old_minute = 0;
    if (rtc_get_minute() != old_minute) {
        old_minute = rtc_get_minute();
        settings_update_minute(old_minute);
    }

    static uint8_t old_second = 0;
    if (rtc_get_second() != old_second) {
        old_second = rtc_get_second();
        settings_update_second(old_second);
    }

    static uint8_t old_audio_enable = 2;
    if ((uint8_t)audio_config.enable != old_audio_enable) {
        old_audio_enable = audio_config.enable;
        settings_update_audio((bool)old_audio_enable);
    }

    static uint8_t old_lcd_backlight_brightness = 0;
    if (user_config.lcd_backlight_brightness != old_lcd_backlight_brightness) {
        old_lcd_backlight_brightness = user_config.lcd_backlight_brightness;
        settings_update_lcd_brightness(old_lcd_backlight_brightness);
    }

    static uint8_t old_active_layer = 33;
    // if the layer setting has changed since last time
    if (get_active_layer_setting() != old_active_layer) {
        old_active_layer = get_active_layer_setting();
        settings_update_active_layer(old_active_layer);
    }
    // if something else (like keypreses) turned off the active layer
    // then turn it back on, the setting takes precedence
    if (!layer_state_is(old_active_layer)) {
        layer_on(old_active_layer);       
    }

    static uint8_t old_default_layer = 33;
    // if the layer setting has changed since last time
    if (get_default_layer_setting() != old_default_layer) {
        old_default_layer = get_default_layer_setting();
        settings_update_default_layer(old_default_layer);
    }

    static uint8_t old_underglow_color_hidden = 2;
    bool underglow_color_hidden;
    uint8_t rgb_mode = rgblight_get_mode();
    if ((rgb_mode > 5) && (rgb_mode < 15)) {//rainbow
        underglow_color_hidden = true;
    } else {
        underglow_color_hidden = false;
    }
    if (underglow_color_hidden != old_underglow_color_hidden) {
        old_underglow_color_hidden = underglow_color_hidden;
        settings_update_underglow_color_hidden((bool)old_underglow_color_hidden);
    }

    static uint8_t old_underglow_brightness_hidden = 2;
    bool underglow_brightness_hidden;
    if ((rgb_mode > 1) && (rgb_mode < 6)) { //breathing
        underglow_brightness_hidden = true;
    } else {
        underglow_brightness_hidden = false;
    }
    if (underglow_brightness_hidden != old_underglow_brightness_hidden) {
        old_underglow_brightness_hidden = underglow_brightness_hidden;
        settings_update_underglow_brightness_hidden((bool)old_underglow_brightness_hidden);
    }
}


static char *underglow_modes[] = { "None",
                                    "Static Light",
                                    "Breathing 1",
                                    "Breathing 2",
                                    "Breathing 3",
                                    "Breathing 4",
                                    "Rainbow Mood 1",
                                    "Rainbow Mood 2",
                                    "Rainbow Mood 3",
                                    "Rainbow Swirl 1",
                                    "Rainbow Swirl 2",
                                    "Rainbow Swirl 3",
                                    "Rainbow Swirl 4",
                                    "Rainbow Swirl 5",
                                    "Rainbow Swirl 6",
                                    "Snake 1",
                                    "Snake 2",
                                    "Snake 3",
                                    "Snake 4",
                                    "Snake 5",
                                    "Snake 6",
                                    "Knight 1",
                                    "Knight 2",
                                    "Knight 3",
                                    "Christmas",
                                    "Static Gradient 1",
                                    "Static Gradient 2",
                                    "Static Gradient 3",
                                    "Static Gradient 4",
                                    "Static Gradient 5",
                                    "Static Gradient 6",
                                    "Static Gradient 7",
                                    "Static Gradient 8",
                                    "Static Gradient 9",
                                    "Static Gradient 10",
                                    "RGB Test",
                                    "Alternating",
                                    "Twinkle 1",
                                    "Twinkle 2",
                                    "Twinkle 3",
                                    "Twinkle 4",
                                    "Twinkle 5",
                                    "Twinkle 6"
                                    };
                                    

char * get_underglow_mode_str(uint8_t underglow_mode) {
    return underglow_modes[underglow_mode];
}


static char *colors[] = { "Red", 
                          "Tomato Red",
                          "Warm Red", 
                          "International Orange",
                          "Bright Orange",
                          "Orange",
                          "Dark Orange",
                          "Yellow Orange",
                          "Amber",
                          "Rubber Ducky Yellow",
                          "Cadmium Yellow",
                          "Yellow",
                          "Neon Yellow",
                          "Greenish Yellow",
                          "Lime",
                          "Bright Yellow Green",
                          "Spring Green",
                          "Bright Lime Green",
                          "Warm Green",
                          "Radioactive Green",
                          "Highlighter Green",
                          "Green 1",
                          "Green 2",
                          "Cool Green 1",
                          "Cool Green 2",
                          "Cool Green 3",
                          "Ocean Green 1",
                          "Ocean Green 2",
                          "Sea Green",
                          "Turquoise",
                          "Teal",
                          "Bright Aqua",
                          "Cyan",
                          "Bright Turqoise",
                          "Bright Sky Blue",
                          "Sky Blue",
                          "Azure",
                          "Deep Sky Blue",
                          "Brandeis Blue",
                          "Bright Blue",
                          "Ocean Blue",
                          "Rich Blue 1",
                          "Rich Blue 2",
                          "Blue",
                          "Strong Blue",
                          "Ultramarine 1",
                          "Ultramarine 2",
                          "Electric Indigo",
                          "Purple",
                          "Vivid Violet",
                          "Bright Violet",
                          "Cool Magenta",
                          "Phlox",
                          "Magenta",
                          "Bright Magenta 1",
                          "Bright Magenta 2",
                          "Warm Magenta",
                          "Hollywood Cerise",
                          "Crimson 1",
                          "Crimson 2",
                          "Folly 1",
                          "Folly 2",
                          "Ruddy",
                          "Bright Red"
                          };

char * get_underglow_color_str(uint8_t underglow_color) {
    return colors[(underglow_color >> 2)];
}

static char *layernames[] = {
    "QWERTY",  // 0
    "Dvorak",  // 1
    "Colemak",  // 2
    "Workman", // 3
    "", // "Excel", // 4
    "", // "Photoshop", // 5
    "", // "Starcraft", // 6
    "", // "WoW", // 7
    "", // 8
    "", // 9
    "", // 10
    "", // 11
    "", // 12
    "", // 13
    "", // 14
    "", // 15
    "", // 16
    "", // 17
    "", // 18
    "", // 19
    "", // 20
    "", // 21
    "", // 22
    "", // 23
    "", // 24
    "", // 25
    "", // 26
    "", // 27
    "", // 28
    "", // 29
    "", // 30
    ""  // 31
};

char * get_layer_str(uint8_t layer) {
    return layernames[layer];
}
