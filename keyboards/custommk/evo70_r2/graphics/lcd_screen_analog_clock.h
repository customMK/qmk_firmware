// Copyright 2023 David Hoelscher (@customMK)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "qp_lvgl.h"
#include "moonphase.h"
#include "i2c_temperature.h"
#include "date_format.h"

#pragma once

void lcd_screen_analog_clock_init(void);

void load_lcd_screen_analog_clock(void);

void lcd_screen_analog_set_date(char *datestr);
void lcd_screen_analog_set_temperature(char *temperature_string);

void lcd_screen_analog_draw_moon_phase(uint16_t cycle_percent_10x);

void lcd_screen_update_analog_seconds(uint32_t second_angle_10x);
void lcd_screen_update_analog_seconds_is_hidden(bool hidden);
void lcd_screen_update_analog_minutes(uint32_t minute_angle_10x);
void lcd_screen_update_analog_hours(uint32_t hour_angle_10x);

void lcd_screen_analog_update_overlay(void);