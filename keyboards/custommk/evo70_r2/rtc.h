// Copyright 2022 David Hoelscher (@customMK)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "quantum.h"

// Checks to see if the date or time has been set, or if it is an invalid date/time
bool has_datetime_been_set(void);

//meant to be called in the housekeeping_kb function
void rtc_refresh_time(void);

// Functions to retrieve the date/time

uint32_t rtc_get_milliseconds_since_midnight(void);
uint32_t rtc_get_seconds_since_midnight(void);
uint8_t rtc_get_second(void);
uint8_t rtc_get_minute(void);
uint16_t rtc_get_minutes_since_midnight(void);
uint8_t rtc_get_hour12(void);
uint8_t rtc_get_hour24(void);
bool rtc_is_am(void);
bool rtc_is_pm(void);
uint8_t rtc_get_day(void);
uint8_t rtc_get_month(void);
uint16_t rtc_get_year(void);
uint8_t rtc_get_dayoftheweek(void);

uint16_t rtc_get_second_analog_angle_10x_deg(void);
uint16_t rtc_get_minute_analog_angle_10x_deg(void);
uint16_t rtc_get_hour12_analog_angle_10x_deg(void);

// Functions to set the date/time

// Time assignments
void rtc_set_time(uint32_t hour, uint32_t minute, uint32_t second);

// Second adjustments
void rtc_increment_second(void);
void rtc_decrement_second(void);

// Minute adjustments
void rtc_increment_minute(void);
void rtc_decrement_minute(void);

// Hour adjustments
void rtc_increment_hour(void);
void rtc_decrement_hour(void);

// Date assignements
void rtc_set_date(uint16_t month, uint16_t day, uint16_t year);

// Day adjustments
void rtc_increment_day(void);
void rtc_decrement_day(void);

// Month adjustments
void rtc_increment_month(void);
void rtc_decrement_month(void);

// Year adjustments
void rtc_increment_year(void);
void rtc_decrement_year(void);
void rtc_set_year(uint16_t year);