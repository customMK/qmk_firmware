// Copyright 2022 David Hoelscher (@customMK)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "rtc.h"
#include "quantum.h"

RTCDateTime current_timespec;

static bool datetime_has_been_set = false;

bool has_datetime_been_set(void) {
    return datetime_has_been_set;
}

void rtc_init(void) {
    // if we're within 10 seconds of the starting time for the RTC clock, assume
    // first time boot or no battery, so no datetime has been set
    if ((rtc_get_year() == 1980) && 
        (rtc_get_month() == 1) &&
        (rtc_get_day() == 1) &&
        (rtc_get_seconds_since_midnight() < 10)) {
            datetime_has_been_set = false;
        } else {
            datetime_has_been_set = true;
        }
}

// Functions to retrieve the date/time

void rtc_refresh_time(void) {
    // Ideally call this function from housekeeping_kb function to keep time updated regularly
    static uint32_t lastread = 0;
    // Take care not to call rtcGetTime more often than 2 RTCCLK periods (about 60us)
    // We ensure this by running only when there has been at least one millisecond increments
    // And just skip the millsecond whenever currentread = 0 because that is the initial condition
    // (better safe than sorry)
    static uint32_t currentread = 0;
    currentread = timer_read32();
    if ((currentread != 0) && (lastread != currentread)) {
        rtcGetTime(&RTCD1, &current_timespec);
        lastread = currentread;
    }
}

uint32_t rtc_get_milliseconds_since_midnight(void) {
    rtc_refresh_time();
    return (uint32_t) current_timespec.millisecond;
}

uint32_t rtc_get_seconds_since_midnight(void) {
    rtc_refresh_time();
    return (uint32_t) (current_timespec.millisecond / 1000);
}

uint8_t rtc_get_second(void) {
    return (uint8_t) (rtc_get_seconds_since_midnight() % 60);
}

uint16_t rtc_get_second_analog_angle_10x_deg(void) {
    rtc_refresh_time();
    return (uint16_t) (current_timespec.millisecond % 60000) * 3 / 500; // 3 * 500 is simplification of (360 [deg] / 60000 [ms]) * 10
}

uint8_t rtc_get_minute(void) {
    return (uint8_t) (rtc_get_minutes_since_midnight() % 60);
}

uint16_t rtc_get_minute_analog_angle_10x_deg(void) {
    rtc_refresh_time();
    return (uint16_t) (current_timespec.millisecond % 3600000) / 1000; // / 100 is simplification of (360 [deg] / 3600000 [ms]) * 10
}

uint16_t rtc_get_minutes_since_midnight(void) {
     return (uint16_t) (rtc_get_seconds_since_midnight() / 60);
}

uint16_t rtc_get_hour12_analog_angle_10x_deg(void) {
    rtc_refresh_time();
    return (uint16_t) (current_timespec.millisecond % 43200000) / 12000; // /12000 is simplification of (360 [deg] / 43200000 [ms]) * 10
}

uint8_t rtc_get_hour12(void) {
    uint8_t hour24 = rtc_get_hour24();
    if (hour24 == 0) {
        return 12;
    }
    if (hour24 > 12) {
        return hour24 - 12;
    }
    return hour24;
}

uint8_t rtc_get_hour24(void) {
    return (uint8_t) (rtc_get_seconds_since_midnight() / 3600);
}

bool rtc_is_am(void) {
    return (rtc_get_hour24() < 12);
}

bool rtc_is_pm(void) {
    return !rtc_is_am();
}

uint8_t rtc_get_day(void) {
    return (uint8_t) current_timespec.day;
}

uint8_t rtc_get_month(void) {
    return (uint8_t) current_timespec.month;
}

uint16_t rtc_get_year(void) {
    return (uint16_t) current_timespec.year + 1980;
}

uint8_t rtc_get_dayoftheweek(void) {
    return (uint8_t) current_timespec.dayofweek;
}

// Functions to set the date/time

uint8_t rtc_calc_dayofweek(uint8_t day, uint8_t month, uint16_t year) {
    // returns day of the week as an integer
    // Sunday = 1
    // Monday = 2
    // ...
    // Saturday = 7

    uint16_t d;
    uint16_t y;
    if ( month < 3 ) {
        d = day + year;
        y = year - 1;
    }
    else {
        d = day + year - 2;
        y = year;
    }

    return (uint8_t) (((23 * month/9) + d + 4 + y/4 - y/100 + y/400) % 7) + 1;
}

void rtc_SetTime_recalc_dayofweek(void) {
    //rtc_refresh_time();
    current_timespec.dayofweek = rtc_calc_dayofweek(current_timespec.day, current_timespec.month, current_timespec.year + 1980);
    rtcSetTime(&RTCD1, &current_timespec);
}

// Time assignment

void rtc_set_time(uint32_t hour, uint32_t minute, uint32_t second) {
    // This function allows directly setting of the time
    rtc_refresh_time();
    current_timespec.millisecond = ((second * 1000) + (minute * 60000) + (hour * 3600000)) % 86400000;
    rtcSetTime(&RTCD1, &current_timespec);
    datetime_has_been_set = true;
}

// Second adjustments

void rtc_increment_second(void) {
    rtc_refresh_time();
    current_timespec.millisecond = (current_timespec.millisecond + 1000) % 86400000;
    rtcSetTime(&RTCD1, &current_timespec);
    datetime_has_been_set = true;
}

void rtc_decrement_second(void) {
    rtc_refresh_time();
    // 86,400,000 milliseconds in one day
    if (current_timespec.millisecond < 1000) {
        current_timespec.millisecond = current_timespec.millisecond + 86400000;
    }
    current_timespec.millisecond = (current_timespec.millisecond - 1000);

    rtcSetTime(&RTCD1, &current_timespec);
    datetime_has_been_set = true;
}

// Minute adjustments

void rtc_increment_minute(void) {
    rtc_refresh_time();
    current_timespec.millisecond = (current_timespec.millisecond + 60000) % 86400000;
    rtcSetTime(&RTCD1, &current_timespec);
    datetime_has_been_set = true;
}

void rtc_decrement_minute(void) {
    rtc_refresh_time();
    if (current_timespec.millisecond < 60000) {
        current_timespec.millisecond = current_timespec.millisecond + 86400000;
    }
    current_timespec.millisecond = (current_timespec.millisecond - 60000);
    rtcSetTime(&RTCD1, &current_timespec);
    datetime_has_been_set = true;
}

// Hour adjustments

void rtc_increment_hour(void) {
    rtc_refresh_time();
    current_timespec.millisecond = (current_timespec.millisecond + 3600000) % 86400000;
    rtcSetTime(&RTCD1, &current_timespec);
    datetime_has_been_set = true;
}

void rtc_decrement_hour(void) {
    rtc_refresh_time();
    if (current_timespec.millisecond < 3600000) {
        current_timespec.millisecond = current_timespec.millisecond + 86400000;
    }
    current_timespec.millisecond = (current_timespec.millisecond - 3600000);
    rtcSetTime(&RTCD1, &current_timespec);
    datetime_has_been_set = true;
}

// Date Assignment

uint8_t rtc_get_daylimit(uint16_t month, uint16_t year) {
    uint8_t daylimit = 31;
    if (month == 9 || month == 4 || month == 6 || month == 11) {
        daylimit = 30;
    } else if(month == 2){
        daylimit = year % 4 == 0 && !(year % 100 == 0 && year % 400 != 0) ? 29 : 28;
    }
    return daylimit;
}

void rtc_set_date(uint16_t month, uint16_t day, uint16_t year) {
    // This function allows directly setting of the date
    rtc_refresh_time();

    if (year < 1980) {
        current_timespec.year = 0;
    } else {
        current_timespec.year = year - 1980;
    }

    if (month == 0) {
        current_timespec.month = 1;
    } else {
        current_timespec.month = ((month - 1) % 12) + 1;
    }

    uint8_t day_limit;
    day_limit = rtc_get_daylimit(current_timespec.month, current_timespec.year + 1980);
    if (day == 0) {
        current_timespec.day = 1;
    } else {
        current_timespec.day = ((day - 1) % day_limit) + 1;
    }
    rtc_SetTime_recalc_dayofweek();
    datetime_has_been_set = true;
}

// Day adjustments

void rtc_increment_day(void) {
    uint8_t day_limit;
    rtc_refresh_time();
    day_limit = rtc_get_daylimit(current_timespec.month, current_timespec.year + 1980);
    if (current_timespec.day == day_limit) {
        current_timespec.day = 1;
    } else {
        current_timespec.day++;
    }
    rtc_SetTime_recalc_dayofweek();
    datetime_has_been_set = true;
}

void rtc_decrement_day(void) {
    uint8_t day_limit;
    rtc_refresh_time();
    day_limit = rtc_get_daylimit(current_timespec.month, current_timespec.year + 1980);
    if (current_timespec.day == 1) {
        current_timespec.day = day_limit;
    } else {
        current_timespec.day--;
    }
    rtc_SetTime_recalc_dayofweek();
    datetime_has_been_set = true;
}

// Month adjustments
void rtc_increment_month(void) {
    rtc_refresh_time();
    if (current_timespec.month == 12) {
        current_timespec.month = 1;
    } else {
        current_timespec.month++;
    }
    rtc_SetTime_recalc_dayofweek();
    datetime_has_been_set = true;
}

void rtc_decrement_month(void) {
    rtc_refresh_time();
    if (current_timespec.month == 1) {
        current_timespec.month = 12;
    } else {
        current_timespec.month--;
    }
    rtc_SetTime_recalc_dayofweek();
    datetime_has_been_set = true;
}

// Year adjustments

void rtc_increment_year(void) {
    rtc_refresh_time();

    current_timespec.year++; //should wrap to 1980 beyond year 2235
    //because chibios stores year as 8 bits
    rtc_SetTime_recalc_dayofweek();
    datetime_has_been_set = true;
}

void rtc_decrement_year(void) {
    rtc_refresh_time();
    current_timespec.year--;
    rtc_SetTime_recalc_dayofweek();
    datetime_has_been_set = true;
}

void rtc_set_year(uint16_t year) {
    // This function allows directly setting of the year
    // Useful for first-time clock setting; if the year is read as 1980
    // then a better default (e.g. 2023) can be assigned.
    if (year < 1980) {
        current_timespec.year = 0;
    } else {
        current_timespec.year = year - 1980;
    }
    rtc_SetTime_recalc_dayofweek();
    datetime_has_been_set = true;
}