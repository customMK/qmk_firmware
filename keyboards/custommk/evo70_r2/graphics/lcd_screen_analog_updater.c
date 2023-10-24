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

// This file abstractly manages which screen is shown, updates settings, and updates displayed values as needed

// This file should remain independent of LVGL (no "lv_" objects), and ideally should remain unchanged when moving
// to a newer version of LVGL (or anyt other display softawre)


void update_lcd_analog_clock_screen(void) {

    uint32_t ms_since_midnight = rtc_get_milliseconds_since_midnight();

    static uint8_t old_hide_seconds = 3;
    if ((uint8_t)user_config.hide_seconds != old_hide_seconds) {
        old_hide_seconds = user_config.hide_seconds;
        lcd_screen_update_analog_seconds_is_hidden((bool)old_hide_seconds);
    }


////This method does smooth second hand ticking instead of ticking
    static uint32_t old_second_angle_10x = 0;
    if (!old_hide_seconds) {
        uint32_t ms_since_minute = ms_since_midnight % 60000;
        uint32_t second_angle_10x = (3 * ms_since_minute / 50);  // (3600 * ms_since_minute / 60000);
        if (second_angle_10x != old_second_angle_10x) {
            old_second_angle_10x = second_angle_10x;
            lcd_screen_update_analog_seconds(old_second_angle_10x);
        }
    }

    static uint32_t old_minute_angle_10x = 0;
    uint32_t ms_since_hour = ms_since_midnight % 3600000;
    uint32_t minute_angle_10x = ms_since_hour / 1000; // (3600 * ms_since_hour / 3600000);
    if (minute_angle_10x != old_minute_angle_10x) {
        old_minute_angle_10x = minute_angle_10x;
        lcd_screen_update_analog_minutes(old_minute_angle_10x);
    }


    static uint32_t old_hour_angle_10x = 0;
    uint32_t ms_since_12 = ms_since_midnight % 43200000;
    uint32_t hour_angle_10x = ms_since_12 / 12000;  // (3600 * ms_since_12) / 43200000;
    if (hour_angle_10x != old_hour_angle_10x) {
        old_hour_angle_10x = hour_angle_10x;
        lcd_screen_update_analog_hours(old_hour_angle_10x);
    }

////This method does second ticking motion instead of continuous
/*
    static uint32_t old_seconds_since_midnight = 100000;
    uint32_t seconds_since_midnight = ms_since_midnight / 1000;
    if (old_seconds_since_midnight != seconds_since_midnight) {
        //seconds since midnight have changed, update the clock
        uint32_t seconds_since_minute = seconds_since_midnight % 60;
        uint32_t second_angle_10x = (3 * (seconds_since_minute * 1000) / 50);  // (3600 * ms_since_minute / 60000);
        lcd_screen_update_analog_seconds(second_angle_10x);

        uint32_t ms_since_hour = ms_since_midnight % 3600000;
        uint32_t minute_angle_10x = ms_since_hour / 1000; // (3600 * ms_since_hour / 3600000);
        lcd_screen_update_analog_minutes(minute_angle_10x);

        uint32_t ms_since_12 = ms_since_midnight % 43200000;
        uint32_t hour_angle_10x = ms_since_12 / 12000;  // (3600 * ms_since_12) / 43200000;
        lcd_screen_update_analog_hours(hour_angle_10x);
    }
*/

    //update if either temperature or temperature units changed
    static int16_t old_temperature_10x = 0;
    static uint8_t old_temperature_unit_are_f = 2; // actual value is bool, so 2 is an impossible value
    if (((uint8_t)user_config.report_temperature_in_f != old_temperature_unit_are_f) ||
        (get_temperature_10x() != old_temperature_10x)) {
        old_temperature_unit_are_f = user_config.report_temperature_in_f;
        old_temperature_10x = get_temperature_10x();
        lcd_screen_analog_set_temperature(get_temperature_str());
    }

    static uint8_t old_date_format = 32; // actual value is uint8_t:4, so 32 is an impossible value
    static uint16_t old_year = 0;
    static uint8_t old_month = 13;
    static uint8_t old_day = 32;
    static char date_str[30];
    if (((uint8_t)user_config.date_format != old_date_format) ||
        (rtc_get_year() != old_year) ||
        (rtc_get_month() != old_month) ||
        (rtc_get_day() != old_day)) {
        old_date_format = user_config.date_format;
        old_year = rtc_get_year();
        old_month = rtc_get_month();
        old_day = rtc_get_day();
        sprintf(date_str, "%s\n%s", get_day_of_the_week_str(rtc_get_dayoftheweek()), get_date_formatted_str(old_day, old_month, old_year));
        lcd_screen_analog_set_date(date_str);
    }

    static uint16_t old_moon_phase_fraction_10x = 1001;
    uint16_t moon_phase_fraction_10x = calc_moon_phase(old_month, old_day, old_year, rtc_get_hour24());
    if (moon_phase_fraction_10x != old_moon_phase_fraction_10x) {
        old_moon_phase_fraction_10x = moon_phase_fraction_10x;
        lcd_screen_analog_draw_moon_phase(old_moon_phase_fraction_10x);
    }
}
