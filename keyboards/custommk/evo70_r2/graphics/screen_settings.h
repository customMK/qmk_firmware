// Copyright 2023 David Hoelscher (@customMK)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "qp_lvgl.h"
#include "evo70_r2_screens.h"
#include "date_format.h"
#include "display_control.h"
#include "screen_settings_updater.h"

#pragma once

void screen_settings_init(void);

void load_screen_settings(void);

void focus_current_settings_menu_item(settings_menu_item_t menu_item, bool is_selected);

void settings_update_active_layer(uint8_t new_value);
void settings_update_backlight_brightness_value(uint8_t new_value);
void settings_update_backlight_breathing_period(uint8_t new_value);
void settings_update_underglow_mode(uint8_t new_value);
void settings_update_underglow_brightness(uint8_t new_value);
void settings_update_underglow_hue(uint8_t new_value);
void settings_update_temperature_units_are_f(bool new_value);
void settings_update_display_timeout(uint8_t new_value);
void settings_update_time_format_is_24h(bool new_value);
void settings_update_hide_seconds(bool new_value);
void settings_update_year(uint16_t year);
void settings_update_month(uint8_t month);
void settings_update_day(uint8_t day);
void settings_update_hour(uint8_t hour);
void settings_update_minute(uint8_t minute);
void settings_update_second(uint8_t second);
void settings_update_audio(bool new_value);
void settings_update_date_format(date_format_t date_format);
void settings_update_lcd_brightness(uint8_t new_value);
void settings_update_underglow_color_hidden(bool new_value);
void settings_update_underglow_brightness_hidden(bool new_value);
void settings_update_default_layer(uint8_t new_value);
