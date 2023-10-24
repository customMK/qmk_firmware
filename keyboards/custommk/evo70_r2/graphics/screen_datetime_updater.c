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

#include "screen_datetime.h"
#include "rtc.h"
#include "date_format.h"
#include "i2c_temperature.h"

void update_screen_datetime(void) {
    
    bool update_datetime = false;

    static uint8_t old_hide_seconds = 2; // actual value is bool, so 2 is an impossible value
    if ((uint8_t)user_config.hide_seconds != old_hide_seconds) {
        old_hide_seconds = user_config.hide_seconds;
        update_datetime = true;
    }

    static uint16_t old_year = 0;
    if (rtc_get_year() != old_year) {
        old_year = rtc_get_year();
        update_datetime = true;
    }

    static uint8_t old_month = 0;
    if (rtc_get_month() != old_month) {
        old_month = rtc_get_month();
        update_datetime = true;
    }

    static uint8_t old_day = 0;
    if (rtc_get_day() != old_day) {
        old_day = rtc_get_day();
        update_datetime = true;
    }

    static uint8_t old_hour = 0;
    if (rtc_get_hour24() != old_hour) {
        old_hour = rtc_get_hour24();
        update_datetime = true;
    }

    static uint8_t old_minute = 0;
    if (rtc_get_minute() != old_minute) {
        old_minute = rtc_get_minute();
        update_datetime = true;
    }

    static uint8_t old_second = 0;
    if ((!old_hide_seconds) && (rtc_get_second() != old_second)) {
        old_second = rtc_get_second();
        update_datetime = true;
    }

    static uint8_t old_time_format_in_24h = 2;
    if ((uint8_t)user_config.time_format_in_24h != old_time_format_in_24h) {
        old_time_format_in_24h = user_config.time_format_in_24h;
        update_datetime = true;
    }

    static uint8_t old_date_format = 9; // actual value is uint8_t:4, so 9 is an impossible value
    if ((uint8_t)user_config.date_format != old_date_format) {
        old_date_format = user_config.date_format;
        update_datetime = true;
    }

    static int16_t old_temperature_10x = 0;
    static uint8_t old_temperature_unit_are_f = 2; // actual value is bool, so 2 is an impossible value
    if (((uint8_t)user_config.report_temperature_in_f != old_temperature_unit_are_f) ||
        (get_temperature_10x() != old_temperature_10x)) {
        old_temperature_unit_are_f = user_config.report_temperature_in_f;
        old_temperature_10x = get_temperature_10x();
        update_datetime = true;
    }


    if (update_datetime) {
        static char datetimestr[50]; 
        // For the months and formats that cause the text to extend beyond the edge of the 128-pixel-wide OLED screen, override the user setting to abbreviate the month name.
        if ((old_month == 9) && (user_config.date_format == monthdyyyy)) {
            sprintf(datetimestr, "%s  %s\n%s\n%s", get_temperature_str(), get_day_of_the_week_str(rtc_get_dayoftheweek()), get_time_str(old_hour, old_minute, old_second), get_date_formatted_str_specific(old_day, old_month, old_year, mondyyyy));
        } else if (((old_month == 2) || (old_month == 11) || (old_month == 12)) && (user_config.date_format == monthdyyyy) && (old_day > 9)) {
            sprintf(datetimestr, "%s  %s\n%s\n%s", get_temperature_str(), get_day_of_the_week_str(rtc_get_dayoftheweek()), get_time_str(old_hour, old_minute, old_second), get_date_formatted_str_specific(old_day, old_month, old_year, mondyyyy));
        } else if ((old_month == 9) && (user_config.date_format == dmonthyyyy) && (old_day > 9)) {
            sprintf(datetimestr, "%s  %s\n%s\n%s", get_temperature_str(), get_day_of_the_week_str(rtc_get_dayoftheweek()), get_time_str(old_hour, old_minute, old_second), get_date_formatted_str_specific(old_day, old_month, old_year, dmonyyyy));
        } else {
            sprintf(datetimestr, "%s  %s\n%s\n%s", get_temperature_str(), get_day_of_the_week_str(rtc_get_dayoftheweek()), get_time_str(old_hour, old_minute, old_second), get_date_formatted_str(old_day, old_month, old_year));
        }
        screen_update_datetime_value(datetimestr);
    }
}
   