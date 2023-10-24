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

#include "quantum.h"
#include "evo70_r2.h"

#pragma once

enum date_format_t {
    mmddyyyy,
    mdyy,
    ddmmyyyy,
    dmyy,
    yyyymmdd,
    mondyyyy,
    monthdyyyy,
    dmonyyyy,
    dmonthyyyy
};

typedef enum date_format_t date_format_t;

extern user_config_t user_config;

void date_format_increment(void);
void date_format_decrement(void);
char *get_date_format_str(void);

char *get_year_str_yyyy(uint16_t year);
char *get_year_str_yy(uint16_t year);
char *get_year_str(uint16_t year);
char *get_day_str_d(uint8_t day);
char *get_day_str_dd(uint8_t day);
char *get_day_str(uint8_t day);
char *get_month_str_m(uint8_t month);
char *get_month_str_mm(uint8_t month);
char *get_month_str_mon(uint8_t month);
char *get_month_str_momth(uint8_t month);
char *get_month_str(uint8_t month);
char *get_day_of_the_week_abbr3_str(uint8_t dotw);
char *get_day_of_the_week_str(uint8_t dotw);
char *get_date_formatted_str(uint16_t day, uint16_t month, uint16_t year);
char *get_date_formatted_str_specific(uint16_t day, uint16_t month, uint16_t year, date_format_t dateformat);
char *get_hour_str(uint8_t hour24);
char *get_time_str(uint8_t hour24, uint8_t minute, uint8_t second);
char *get_minute_str(uint8_t minute);
char *get_second_str(uint8_t second);