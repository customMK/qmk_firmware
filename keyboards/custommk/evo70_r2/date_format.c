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

#include "date_format.h"

static char currentyear[10];
char *get_year_str_yyyy(uint16_t year) {
    sprintf(currentyear, "%04u", year);
    return currentyear;
}


char *get_year_str_yy(uint16_t year) {
    sprintf(currentyear, "%02u", (year%100));
    return currentyear;
}

char *get_year_str_specific(uint16_t year, date_format_t dateformat) {
    switch(dateformat) {
        case mdyy:
        case dmyy:
            return get_year_str_yy(year);
            break;
        default:
            return get_year_str_yyyy(year);
            break;
    }
}

char *get_year_str(uint16_t year) {
    return get_year_str_specific(year, user_config.date_format);
}

static char currentday[10];
char *get_day_str_d(uint8_t day) {
    sprintf(currentday, "%u", day);
    return currentday;
}

static char currentday[10];
char *get_day_str_dd(uint8_t day) {
    sprintf(currentday, "%02u", day);
    return currentday;
}

char *get_day_str_specific(uint8_t day, date_format_t dateformat) {
    switch(dateformat) {
        case mdyy:
        case dmyy:
        case mondyyyy:
        case dmonyyyy:
        case monthdyyyy:
        case dmonthyyyy:
            return get_day_str_d(day);
            break;
        default:
            return get_day_str_dd(day);
            break;
    }
}

char *get_day_str(uint8_t day) {
    return get_day_str_specific(day, user_config.date_format);
}

static char currentmonth[10];
char *get_month_str_m(uint8_t month) {
    sprintf(currentmonth, "%u", month);
    return currentmonth;
}

char *get_month_str_mm(uint8_t month) {
    sprintf(currentmonth, "%02u", month);
    return currentmonth;
}

static char *months_abbr3[] = { "Jan", 
                                "Feb",
                                "Mar", 
                                "Apr",
                                "May",
                                "Jun",
                                "Jul",
                                "Aug",
                                "Sep",
                                "Oct",
                                "Nov",
                                "Dec"
};

char * get_month_str_mon(uint8_t month) {
    return months_abbr3[(month - 1)];
}

static char *months[] = { "January", 
                          "February",
                          "March", 
                          "April",
                          "May",
                          "June",
                          "July",
                          "August",
                          "September",
                          "October",
                          "November",
                          "December"
};

char * get_month_str_month(uint8_t month) {
    return months[(month - 1)];
}

char *get_month_str_specific(uint8_t month, date_format_t dateformat) {
    switch(dateformat) {
        case mdyy:
        case dmyy:
            return get_month_str_m(month);
            break;
        case mmddyyyy:
        case ddmmyyyy:
        case yyyymmdd:
            return get_month_str_mm(month);
            break;
        case monthdyyyy:
        case dmonthyyyy:
            return get_month_str_month(month);
            break;
        case mondyyyy:
        case dmonyyyy:
            return get_month_str_mon(month);
            break;
        default:
            return get_month_str_m(month);
            break;
    }
}

char *get_month_str(uint8_t month) {
    return get_month_str_specific(month, user_config.date_format);
}


static char *date_format[] = { "mm/dd/yyyy", 
                               "m/d/yy",
                               "dd/mm/yyyy", 
                               "d/m/yy",
                               "yyyy/mm/dd",
                               "mon d, yyyy",
                               "month d, yyyy",
                               "d mon yyyy",
                               "d month yyyy"
};

char *get_date_format_str(void) {
    return date_format[user_config.date_format];
}

void date_format_increment(void) {
    user_config.date_format = (user_config.date_format + 1) % 9;
    update_kb_eeprom();
}

void date_format_decrement(void) {
    if ((user_config.date_format) == 0) {
        user_config.date_format = 8;
    } else {
        user_config.date_format--;
    }
    update_kb_eeprom();
}


static char *days_of_the_week_abbr3[] = { "Sun", 
                                          "Mon",
                                          "Tue", 
                                          "Wed",
                                          "Thu",
                                          "Fri",
                                          "Sat"
};

char *get_day_of_the_week_abbr3_str(uint8_t dotw) {
    return days_of_the_week_abbr3[(dotw - 1)];
}

static char *days_of_the_week[] = { "Sunday", 
                                    "Monday",
                                    "Tuesday", 
                                    "Wednesday",
                                    "Thursday",
                                    "Friday",
                                    "Saturday"
};

char * get_day_of_the_week_str(uint8_t dotw) {
    return days_of_the_week[(dotw - 1)];
}

char *get_date_formatted_str(uint16_t day, uint16_t month, uint16_t year) {
    return get_date_formatted_str_specific(day, month, year, user_config.date_format);
}

char *get_date_formatted_str_specific(uint16_t day, uint16_t month, uint16_t year, date_format_t dateformat) {
    static char datestr[35] = "";    
    switch(dateformat) {
        case mdyy:
            sprintf(datestr, "%s/%s/%s", get_month_str_specific(month, dateformat), get_day_str_specific(day, dateformat), get_year_str_specific(year, dateformat));
            break;
        case mmddyyyy:
            sprintf(datestr, "%s/%s/%s", get_month_str_specific(month, dateformat), get_day_str_specific(day, dateformat), get_year_str_specific(year, dateformat));
            break;
        case ddmmyyyy:
            sprintf(datestr, "%s/%s/%s", get_day_str_specific(day, dateformat), get_month_str_specific(month, dateformat), get_year_str_specific(year, dateformat));
            break;
        case dmyy:
            sprintf(datestr, "%s/%s/%s", get_day_str_specific(day, dateformat), get_month_str_specific(month, dateformat), get_year_str_specific(year, dateformat));
            break;
        case yyyymmdd:
            sprintf(datestr, "%s/%s/%s", get_year_str_specific(year, dateformat), get_month_str_specific(month, dateformat), get_day_str_specific(day, dateformat));
            break;
        case monthdyyyy:
            sprintf(datestr, "%s %s, %s", get_month_str_specific(month, dateformat), get_day_str_specific(day, dateformat), get_year_str_specific(year, dateformat));
            break;
        case dmonthyyyy:
            sprintf(datestr, "%s %s %s", get_day_str_specific(day, dateformat), get_month_str_specific(month, dateformat), get_year_str_specific(year, dateformat));
            break;
        case mondyyyy:
            sprintf(datestr, "%s %s, %s", get_month_str_specific(month, dateformat), get_day_str_specific(day, dateformat), get_year_str_specific(year, dateformat));
            break;
        case dmonyyyy:
            sprintf(datestr, "%s %s %s", get_day_str_specific(day, dateformat), get_month_str_specific(month, dateformat), get_year_str_specific(year, dateformat));
            break;
        default:
            sprintf(datestr, "%s/%s/%s", get_year_str_specific(year, dateformat), get_month_str_specific(month, dateformat), get_day_str_specific(day, dateformat));
            break;
    }
    return datestr;
}

//input is the 24 hour time (range 0 to 23)
static char hour_str[10];
char * get_hour_str(uint8_t hour24) {

    if (user_config.time_format_in_24h) {
        sprintf(hour_str, "%02u", hour24);
    } else {
        uint8_t disp_hour;
        // 12 hour time mode
        disp_hour = hour24;

        // handle midnight hour
        if (hour24 == 0) {
            disp_hour = 12;
        }
        
        // shift post-noon hours down by 12
        if (hour24 > 12) {
            disp_hour = hour24 - 12;
        }

        if (hour24 < 12) { // AM
            sprintf(hour_str, "%u AM", disp_hour);
        } else {
            sprintf(hour_str, "%u PM", disp_hour);
        }
    }
    return hour_str;
}

//input is the 24 hour time (range 0 to 23)
static char time_str[30];
char * get_time_str(uint8_t hour24, uint8_t minute, uint8_t second) {
    if (user_config.time_format_in_24h) {
        if (user_config.hide_seconds) {
            sprintf(time_str, "%02u:%02u", hour24, minute);
        } else {
            sprintf(time_str, "%02u:%02u:%02u", hour24, minute, second);
        }
    } else {
        uint8_t disp_hour;
        //we're in 12 hour time mode
        disp_hour = hour24;

        // handle midnight hour
        if (hour24 == 0) {
            disp_hour = 12;
        }
        
        // shift post-noon hours down by 12
        if (hour24 > 12) {
            disp_hour = hour24 - 12;
        }

        if (hour24 < 12) { // AM
            if (user_config.hide_seconds) {
                sprintf(time_str, "%u:%02u AM", disp_hour, minute);
            } else {
                sprintf(time_str, "%u:%02u:%02u AM", disp_hour, minute, second);
            }
        } else {
            if (user_config.hide_seconds) {
                sprintf(time_str, "%u:%02u PM", disp_hour, minute);
            } else {
                sprintf(time_str, "%u:%02u:%02u PM", disp_hour, minute, second);
            }
        }
    }
    return time_str;
}

static char minute_str[10];
char * get_minute_str(uint8_t minute) {
    sprintf(minute_str, "%u", minute);
    return minute_str;
}

static char second_str[10];
char * get_second_str(uint8_t second) {
    sprintf(second_str, "%u", second);
    return second_str;
}
