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
#include "layer_settings.h"

#include "screen_settings.h"
#include "screen_settings_updater.h"

#include "screen_bongocat.h"
#include "screen_bongocat_updater.h"

#include "lcd_screen_analog_clock.h"
#include "lcd_screen_analog_updater.h"

#include "screen_datetime.h"
#include "screen_datetime_updater.h"

#include "screen_custommk_logo.h"
#include "screen_custom_graphic.h"

#include "overlay_panel.h"

// This file abstractly manages which screen is shown, updates settings, and updates displayed values as needed

// This file should remain independent of LVGL (no "lv_" objects), and ideally should remain unchanged when moving
// to a newer version of LVGL (or anyt other display softawre)
static uint8_t current_screen = 0; //used as index value of oled_screen_list and/or lcd_screen_list
static uint8_t current_settings_menu_item_number = 0;  //used as index value of oled_setting_list and/or lcd_setting_list

static bool current_settings_menu_item_is_selected = false;

static bool previous_encoder_pressed = false;
static bool encoder_is_pressed = false;
static uint32_t encoder_press_duration = 0;

static uint8_t num_screens = 2;
static uint8_t num_settings = 2;

#ifdef AUDIO_ENABLE
extern audio_config_t audio_config;
#endif
extern user_config_t user_config;
extern backlight_config_t backlight_config;


display_screen_t oled_screen_list[] = {
    custommk_logo_screen,
    screen_datetime,
    bongocat_screen,
    settings_screen
};

display_screen_t lcd_screen_list[] = {
    custommk_logo_screen,
    custom_graphic_screen,
    lcd_analog_clock,
    screen_datetime,
    bongocat_screen,
    settings_screen
};

settings_menu_item_t oled_settings_list[] = {
    exit_settings,
    active_layer,
    backlight_brightness,
    backlight_breathing_period,
    underglow_mode,
    underglow_brightness,
    underglow_color,
    temperature_units,
    display_timeout,
    time_format,
    hide_seconds,
    date_format,
    set_year,
    set_month,
    set_day,
    set_hour,
    set_minute,
    set_second,
    audio_enable,
    default_layer
};

settings_menu_item_t lcd_settings_list[] = {
    exit_settings,
    active_layer,
    backlight_brightness,
    backlight_breathing_period,
    underglow_mode,
    underglow_brightness,
    underglow_color,
    temperature_units,
    display_timeout,
    time_format,
    hide_seconds,
    date_format,
    set_year,
    set_month,
    set_day,
    set_hour,
    set_minute,
    set_second,
    audio_enable,
    lcd_brightness,
    default_layer
};

void display_management_init(void) {

    lcd_screen_analog_clock_init();
    screen_settings_init();
    screen_datetime_init();
    screen_bongocat_init();
    screen_custommk_logo_init();
    screen_custom_graphic_init();

    if (oled_exists()) {
        num_settings = sizeof(oled_settings_list) / sizeof(oled_settings_list[0]);
        num_screens = sizeof(oled_screen_list) / sizeof(oled_screen_list[0]);
    } else {
        num_settings = sizeof(lcd_settings_list) / sizeof(lcd_settings_list[0]);
        num_screens = sizeof(lcd_screen_list) / sizeof(lcd_screen_list[0]);
    }
    current_screen = user_config.current_screen;
    show_new_screen();
    focus_current_settings_menu_item(get_current_menu_item(), current_settings_menu_item_is_selected);


}


void display_management_task(void) {
    // First half of this function processes any inputs like encoder rotation or press/release and makes changes accordingly,
    // like display on/off or changing which settings menu item is selected, selecting/deselecting menu items, and changing settings
    bool encoder_has_been_released;
    if ((get_enc_pressed() == true) && (previous_encoder_pressed == false)) {
        //encoder_has_been_pressed = true; // true only for one cycle at the moment of press
        encoder_is_pressed = true;
        encoder_has_been_released = false;
    } else if ((get_enc_pressed() == false) && (previous_encoder_pressed == true)) {
        encoder_has_been_released = true; // true only for one cycle at the moment of release
        encoder_is_pressed = false;
        encoder_press_duration = get_enc_pressed_duration();
    } else {
        encoder_has_been_released = false;
    }

    previous_encoder_pressed = get_enc_pressed();
    if (encoder_has_been_released == true) {
        if (encoder_press_duration > 300) {
            if (is_display_on()) {
                turn_display_off();
            } else {
                turn_display_on();
            }
        } else {
            if (is_display_on() == false) {
                turn_display_on();
            } else if (get_current_screen() == settings_screen) {  // display is on, but is the settings screen
                if (get_current_menu_item() == exit_settings) { // and we are on the "exit settings" menu option
                    change_screen();
                } else {
                    // handle the menu setting selection/deselection
                    current_settings_menu_item_is_selected = !current_settings_menu_item_is_selected;
                    focus_current_settings_menu_item(get_current_menu_item(), current_settings_menu_item_is_selected);
                }
            } else { // for any other screen, we just advance to the next/prev screen
                change_screen();
            }
        }
    }
    int enc_position_delta;
    enc_position_delta = get_enc_position_delta();

    if ((get_current_screen() == settings_screen) && (enc_position_delta != 0) && (is_display_on())) {
        //we are in the setting screen and the encoder has been rotated
        if (current_settings_menu_item_is_selected) {
            //a current menu setting is selected, so we adjust the setting
            if (enc_position_delta < 0) {
                adjust_setting(true);
            } else {
                adjust_setting(false);
            }
        } else {
            // no menu setting is currently selected, so we navigate the menu up/down instead
            // no rollover, just stop at the limits
            if (enc_position_delta < 0) {
                increment_menu_item();
            } else {
                decrement_menu_item();
            }
            focus_current_settings_menu_item(get_current_menu_item(), false);
        }
    }
    // When the setting screen is shown, don't propagate keycodes
    if ((get_current_screen() == settings_screen) && (is_display_on())) {
        suppress_encoder_user_keycode();
        suppress_encoder_user_rotation();
    } else {
        unsuppress_encoder_user_keycode();
        unsuppress_encoder_user_rotation();
    }

    //At this point, all user input controls have been handled, all settings are udpated, states are known.

    switch(get_current_screen()) {
    case settings_screen:
        update_settings_screen();
        break; 
    case lcd_analog_clock:
        update_lcd_analog_clock_screen();
        break; 
    case screen_datetime:
        update_screen_datetime();
        break; 
    case bongocat_screen:
        update_screen_bongocat();
        break; 
    default:
        break;
    }


    screen_custommk_logo_update_overlay();
    screen_custom_graphic_update_overlay();
    screen_datetime_update_overlay();
    lcd_screen_analog_update_overlay();
    screen_bongocat_update_overlay();


    static uint8_t old_highest_layer = 0;
    static bool old_numlock = false;
    static bool old_capslock = false;

    uint8_t highest_layer;
    highest_layer = get_highest_layer(layer_state);

    if (highest_layer != old_highest_layer) {
        old_highest_layer = highest_layer;
        overlay_layer_active(old_highest_layer);
    }

    led_t led_state = host_keyboard_led_state();
    if (led_state.num_lock != old_numlock) {
        old_numlock = led_state.num_lock;
        if (old_numlock) {
            overlay_numlock_on();
        } else {
            overlay_numlock_off();
        }
    }

    if (led_state.caps_lock != old_capslock) {
        old_capslock = led_state.caps_lock;
        if (old_capslock) {
            overlay_capslock_on();
        } else {
            overlay_capslock_off();
        }
    }
    
    overlay_task();
    display_timeout_task();
}


void show_new_screen(void) {
    switch(get_current_screen()) {
    case settings_screen :
        load_screen_settings();
        break;
    case lcd_analog_clock :
        load_lcd_screen_analog_clock();
        break;
    case screen_datetime:
        load_screen_datetime();
        break; 
    case bongocat_screen:
        load_screen_bongocat();
        break; 
    case custommk_logo_screen:
        load_screen_custommk_logo();
        break; 
    case custom_graphic_screen:
        load_screen_custom_graphic();
        break; 
    default:
        break;
    }
}


void adjust_setting(bool increase) {
    //This function processes control inputs when they occur
    switch(get_current_menu_item()) {

    case exit_settings : // should never get here
        break; 
    case backlight_brightness : //  Backlight Brightness
        if (increase) {
            backlight_increase();
        } else {
            backlight_decrease();
        }
        break; 
    case backlight_breathing_period : //  Backlight Breathing Period
        if (increase) {
            backlight_breathing_period_increment();
        } else {
            backlight_breathing_period_decrement();
        }
        break; 
    case underglow_mode : //  Underglow Mode
        if (increase) {
            rgblight_step();
        } else {
            rgblight_step_reverse();
        }
        break; 
    case underglow_brightness : //  Underglow Brightness
        if (increase) {
            rgblight_increase_val();
        } else {
            rgblight_decrease_val();
        }
        break;
    case underglow_color : //  Underglow Color
        if (increase) {
            rgblight_increase_hue();
        } else {
            rgblight_decrease_hue();
        }
        break;
    case temperature_units : //  Temperature units
        user_config.report_temperature_in_f = !user_config.report_temperature_in_f;
        update_kb_eeprom();
        break; 
    case display_timeout : //  Display Timeout
        if (increase) {
            display_increase_timeout();
        } else {
            display_decrease_timeout();
        }
        break;
    case time_format: // Set time format 12/24hr
        user_config.time_format_in_24h = !user_config.time_format_in_24h;
        update_kb_eeprom();
        break;
    case hide_seconds:
        user_config.hide_seconds = !user_config.hide_seconds;
        update_kb_eeprom();
        break;
    case date_format :
        if (increase) {
            date_format_increment();
        } else {
            date_format_decrement();
        }
        break;
    case set_year : //  Set Year
        if (increase) {
            rtc_increment_year();
        } else {
            rtc_decrement_year();
        }
        break;
    case set_month : //  Set Month
        if (increase) {
            rtc_increment_month();
        } else {
            rtc_decrement_month();
        }
        break;
    case set_day : //  Set Day
        if (increase) {
            rtc_increment_day();
        } else {
            rtc_decrement_day();
        }
        break;
    case set_hour: //  Set Hours
        if (increase) {
            rtc_increment_hour();
        } else {
            rtc_decrement_hour();
        }
        break;
    case set_minute : //  Set Minutes
        if (increase) {
            rtc_increment_minute();
        } else {
            rtc_decrement_minute(); 
        }
        break;
    case set_second : //  Set Seconds
        if (increase) {
            rtc_increment_second();
        } else {
            rtc_decrement_second();
        }
        break;
    case audio_enable : //  Audio Enable
#ifdef AUDIO_ENABLE
            audio_config.enable = !audio_config.enable;
            eeconfig_update_audio(audio_config.raw);
#endif
        break; 
    case lcd_brightness : //  LCD brightness
        if (increase) {
            lcd_increment_brightness();
        } else {
            lcd_decrement_brightness();
        }
        break;
    case default_layer : // Default Layer
        if (increase) {
            increment_default_layer();
        } else {
            decrement_default_layer();
        }
        break;
    case active_layer : // Active Layer
        if (increase) {
            increment_active_layer();
        } else {
            decrement_active_layer();
        }
        break;
    }
}


void change_screen(void) {
    if (get_mods() & MOD_MASK_SHIFT) {
        increment_screen();

    } else {
        decrement_screen();
        
    }
    show_new_screen();
}

void increment_screen(void) {
    current_screen = (current_screen + (num_screens- 1)) % num_screens;
    user_config.current_screen = current_screen;
    update_kb_eeprom();
}

void decrement_screen(void) {
    current_screen = (current_screen + 1) % num_screens;
    user_config.current_screen = current_screen;
    update_kb_eeprom();
}
display_screen_t get_current_screen(void) {
    if(oled_exists()) {
        return oled_screen_list[current_screen];
    } else {
        return lcd_screen_list[current_screen];
    }
}



bool is_underglow_color_hidden(void) {
    uint8_t rgb_mode = rgblight_get_mode();
    return ((rgb_mode > 5) && (rgb_mode < 15)); //rainbow
}

bool is_underglow_brigthness_hidden(void) {
    uint8_t rgb_mode = rgblight_get_mode();
    return ((rgb_mode > 1) && (rgb_mode < 6)); //breathing
}

bool is_current_menu_item_hidden(void) {
    return ((is_underglow_color_hidden() && (get_current_menu_item() == underglow_color)) || (is_underglow_brigthness_hidden() &&  (get_current_menu_item() == underglow_brightness)));
}

void decrement_menu_item(void) {
    if (current_settings_menu_item_number == 0) {
        current_settings_menu_item_number = 0;
    } else {
        current_settings_menu_item_number = current_settings_menu_item_number - 1;
    }
    if (is_current_menu_item_hidden()) {
        decrement_menu_item();
    }
}

void increment_menu_item(void) {
    if (current_settings_menu_item_number < (num_settings - 1)) {
        current_settings_menu_item_number = current_settings_menu_item_number + 1;
    }
    if (is_current_menu_item_hidden()) {
        increment_menu_item();
    }
}

settings_menu_item_t get_current_menu_item(void) {
    if(oled_exists()) {
        return oled_settings_list[current_settings_menu_item_number];
    } else {
        return lcd_settings_list[current_settings_menu_item_number];
    }
}

