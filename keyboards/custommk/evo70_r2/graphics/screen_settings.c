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

#include "screen_settings.h"
#include <math.h>

lv_obj_t *screen_settings;

lv_style_t style_screen;

lv_obj_t *setting_exit_panel;
lv_obj_t *setting_exit_panel_label;

lv_obj_t *setting_active_layer;
lv_obj_t *setting_active_layer_value;
lv_obj_t *setting_active_layer_slider;

lv_obj_t *setting_backlight_brightness;
lv_obj_t *setting_backlight_brightness_slider;

lv_obj_t *setting_backlight_breathing_period;
lv_obj_t *setting_backlight_breathing_period_value;
lv_obj_t *setting_backlight_breathing_period_slider;

lv_obj_t *setting_underglow_mode;
lv_obj_t *setting_underglow_mode_value;

lv_obj_t *setting_underglow_brightness;
lv_obj_t *setting_underglow_brightness_slider;

lv_obj_t *setting_underglow_color;
lv_obj_t *setting_underglow_color_value;
lv_obj_t *setting_underglow_color_slider;

lv_obj_t *setting_panelslider;
lv_obj_t *setting_panelslider_slider;

lv_obj_t *setting_panelslidervalue;
lv_obj_t *setting_panelslidervalue_value;
lv_obj_t *setting_panelslidervalue_slider;

lv_obj_t *setting_temperature_units;
lv_obj_t *setting_temperature_units_value;

lv_obj_t *setting_display_timeout;
lv_obj_t *setting_display_timeout_value;

lv_obj_t *setting_time_format;
lv_obj_t *setting_time_format_value;

lv_obj_t *setting_hide_seconds;
lv_obj_t *setting_hide_seconds_value;

lv_obj_t *setting_date_format;
lv_obj_t *setting_date_format_value;

lv_obj_t *setting_year;
lv_obj_t *setting_year_value;

lv_obj_t *setting_month;
lv_obj_t *setting_month_value;

lv_obj_t *setting_day;
lv_obj_t *setting_day_value;

lv_obj_t *setting_hour;
lv_obj_t *setting_hour_value;

lv_obj_t *setting_minute;
lv_obj_t *setting_minute_value;

lv_obj_t *setting_second;
lv_obj_t *setting_second_value;

lv_obj_t *setting_audio;
lv_obj_t *setting_audio_value;

lv_obj_t *setting_lcd_brightness;
lv_obj_t *setting_lcd_brightness_slider;

lv_obj_t *setting_default_layer;
lv_obj_t *setting_default_layer_value;
lv_obj_t *setting_default_layer_slider;

/* shared styles */
lv_style_t style_panel;
lv_style_t style_panel_focused;
lv_style_t style_panel_selected;

lv_group_t * settings_panels_group;

LV_FONT_DECLARE(font_tseng_eva)

void screen_settings_screen_styles_init(void) {
    lv_style_init(&style_panel);
    lv_style_set_pad_top(&style_panel, 4);
    lv_style_set_pad_bottom(&style_panel, 4);
    lv_style_set_pad_left(&style_panel, 4);
    lv_style_set_pad_right(&style_panel, 4);
    lv_style_set_border_opa(&style_panel, 0);
    lv_style_set_bg_opa(&style_panel, 0);
    if (oled_exists()) {
        lv_style_set_text_font(&style_panel, &font_tseng_eva);
    } else {
        lv_style_set_text_font(&style_panel, &lv_font_montserrat_14);
    }

    lv_style_init(&style_panel_focused);
    lv_style_set_border_color(&style_panel_focused, lv_color_hex(0x2B97F3));
    lv_style_set_border_opa(&style_panel_focused, 255);
    lv_style_set_border_width(&style_panel_focused, 2);

    lv_style_init(&style_panel_selected);
    lv_style_set_bg_color(&style_panel_selected, lv_color_hex(0x005614));
    lv_style_set_border_opa(&style_panel_selected, 255);
}

void hide_values_and_sliders(lv_obj_t *panel) {
    uint32_t i;
    for(i = 1; i < lv_obj_get_child_cnt(panel); i++) {
        lv_obj_add_flag(lv_obj_get_child(panel, i), LV_OBJ_FLAG_HIDDEN);
    }
}

void show_values_and_sliders(lv_obj_t *panel) {
    uint32_t i;
    for(i = 1; i < lv_obj_get_child_cnt(panel); i++) {
        lv_obj_clear_flag(lv_obj_get_child(panel, i), LV_OBJ_FLAG_HIDDEN);
    }
}

lv_obj_t *create_settings_panel(lv_obj_t *parent, const char *setting_name) {
    lv_obj_t *new_panel = lv_obj_create(parent);
    lv_obj_set_height(new_panel, LV_SIZE_CONTENT); //28);
    lv_obj_set_width(new_panel, lv_pct(100));
    lv_obj_set_align(new_panel, LV_ALIGN_CENTER );
    lv_obj_set_flex_flow(new_panel,LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(new_panel, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START);
    lv_obj_add_flag( new_panel, LV_OBJ_FLAG_SCROLL_ON_FOCUS | LV_OBJ_FLAG_SCROLL_ONE);
    lv_obj_clear_flag(new_panel, LV_OBJ_FLAG_SCROLLABLE);
    if (oled_exists()) {
        lv_obj_set_style_pad_row(new_panel, 1, LV_PART_MAIN| LV_STATE_DEFAULT);
    }

    lv_obj_add_style(new_panel, &style_panel, LV_PART_MAIN| LV_STATE_DEFAULT);
    lv_obj_add_style(new_panel, &style_panel_focused, LV_PART_MAIN| LV_STATE_FOCUSED);
    lv_obj_add_style(new_panel, &style_panel_selected, LV_PART_MAIN| LV_STATE_PRESSED);

    lv_obj_t *label = lv_label_create(new_panel);
    lv_obj_set_width(label, lv_pct(100));
    lv_obj_set_height(label, LV_SIZE_CONTENT);
    lv_obj_set_align(label, LV_ALIGN_LEFT_MID);
    lv_label_set_long_mode(label, LV_LABEL_LONG_CLIP);
    lv_label_set_text(label,setting_name);

    lv_group_add_obj(settings_panels_group, new_panel);

    return new_panel;
}

lv_obj_t *create_settings_slider(lv_obj_t *parent) {
    lv_obj_t *new_slider = lv_slider_create(parent);
    if (oled_exists()) {
        lv_obj_set_height(new_slider, 3);
    } else {
        lv_obj_set_height(new_slider, 5);
    }
    lv_obj_set_width(new_slider, lv_pct(100));
    lv_obj_set_style_pad_left(new_slider, 1, LV_PART_KNOB| LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(new_slider, 1, LV_PART_KNOB| LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(new_slider, 1, LV_PART_KNOB| LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(new_slider, 1, LV_PART_KNOB| LV_STATE_DEFAULT);
    lv_obj_set_style_anim_time(new_slider, 150, LV_PART_MAIN| LV_STATE_DEFAULT);
    lv_obj_add_flag(new_slider, LV_OBJ_FLAG_HIDDEN);
    lv_slider_set_value(new_slider, 0, LV_ANIM_OFF);

    return new_slider;
}

// Creates a right-aligned text object for use in a settings panel
lv_obj_t *create_settings_value(lv_obj_t *parent) {
    lv_obj_t *new_value = lv_label_create(parent);
    lv_obj_set_width(new_value, lv_pct(100));
    lv_obj_set_height(new_value, LV_SIZE_CONTENT);
    lv_obj_set_align(new_value, LV_ALIGN_LEFT_MID );
    lv_label_set_text(new_value,"#");
    lv_obj_set_style_text_align(new_value, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN| LV_STATE_DEFAULT);
    lv_label_set_long_mode(new_value, LV_LABEL_LONG_SCROLL_CIRCULAR);
    lv_obj_add_flag(new_value, LV_OBJ_FLAG_HIDDEN);
    return new_value;
}

void screen_settings_init(void)
{
    screen_settings_screen_styles_init();

    screen_settings = lv_obj_create(NULL);
    lv_obj_set_scrollbar_mode(screen_settings, LV_SCROLLBAR_MODE_ACTIVE);
    lv_obj_set_flex_flow(screen_settings,LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(screen_settings, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START);
    lv_obj_set_style_pad_left(screen_settings, 3, LV_PART_MAIN| LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(screen_settings, 13, LV_PART_MAIN| LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(screen_settings, 25, LV_PART_MAIN| LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(screen_settings, 25, LV_PART_MAIN| LV_STATE_DEFAULT);
    lv_obj_set_style_pad_row(screen_settings, 4, LV_PART_MAIN| LV_STATE_DEFAULT);
    lv_obj_set_style_pad_column(screen_settings, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
    lv_obj_set_scroll_snap_y(screen_settings, LV_SCROLL_SNAP_CENTER);
    lv_obj_set_scrollbar_mode(screen_settings, LV_SCROLLBAR_MODE_ON);
    lv_obj_set_scroll_dir(screen_settings, LV_DIR_VER);
    lv_obj_set_style_bg_color(screen_settings, lv_color_hex(0x2B97F3), LV_PART_SCROLLBAR | LV_STATE_DEFAULT );

    if (oled_exists()) {
        lv_obj_set_style_pad_row(screen_settings, -3, LV_PART_MAIN| LV_STATE_DEFAULT);
    }

    settings_panels_group = lv_group_create();

    setting_exit_panel = create_settings_panel(screen_settings, "Exit Settings   ");

    setting_active_layer = create_settings_panel(screen_settings, "Active Layer");
    setting_active_layer_value = create_settings_value(setting_active_layer);
    lv_label_set_long_mode(setting_active_layer_value, LV_LABEL_LONG_SCROLL);
    setting_active_layer_slider = create_settings_slider(setting_active_layer);
    lv_slider_set_range(setting_active_layer_slider, 0, 31);


    setting_backlight_brightness = create_settings_panel(screen_settings, "Backlight Brightness   ");
    setting_backlight_brightness_slider = create_settings_slider(setting_backlight_brightness);
    lv_slider_set_range(setting_backlight_brightness_slider, 0, BACKLIGHT_LEVELS);


    setting_backlight_breathing_period = create_settings_panel(screen_settings, "Backlight Breathing Period");
    setting_backlight_breathing_period_value = create_settings_value(setting_backlight_breathing_period);
    setting_backlight_breathing_period_slider = create_settings_slider(setting_backlight_breathing_period);
    lv_slider_set_range(setting_backlight_breathing_period_slider, 1, 15);


    setting_underglow_mode = create_settings_panel(screen_settings, "Underglow Mode");
    setting_underglow_mode_value = create_settings_value(setting_underglow_mode);


    setting_underglow_brightness = create_settings_panel(screen_settings, "Underglow Brightness");
    setting_underglow_brightness_slider = create_settings_slider(setting_underglow_brightness);
    lv_slider_set_range(setting_underglow_brightness_slider, 0, 128);


    setting_underglow_color = create_settings_panel(screen_settings, "Underglow Color");
    setting_underglow_color_value = create_settings_value(setting_underglow_color);
    lv_label_set_long_mode(setting_underglow_color_value, LV_LABEL_LONG_SCROLL);
    setting_underglow_color_slider = create_settings_slider(setting_underglow_color);
    lv_slider_set_range(setting_underglow_color_slider, 0, 255);


    setting_temperature_units = create_settings_panel(screen_settings, "Temperature Units");
    setting_temperature_units_value = create_settings_value(setting_temperature_units);

    setting_display_timeout = create_settings_panel(screen_settings, "Display Timeout");
    setting_display_timeout_value = create_settings_value(setting_display_timeout);

    setting_time_format = create_settings_panel(screen_settings, "Time Format");
    setting_time_format_value = create_settings_value(setting_time_format);

    setting_hide_seconds = create_settings_panel(screen_settings, "Hide Seconds");
    setting_hide_seconds_value = create_settings_value(setting_hide_seconds);

    setting_date_format = create_settings_panel(screen_settings, "Date Format");
    setting_date_format_value = create_settings_value(setting_date_format);

    setting_year = create_settings_panel(screen_settings, "Year");
    setting_year_value = create_settings_value(setting_year);

    setting_month = create_settings_panel(screen_settings, "Month");
    setting_month_value = create_settings_value(setting_month);

    setting_day = create_settings_panel(screen_settings, "Day");
    setting_day_value = create_settings_value(setting_day);

    setting_hour = create_settings_panel(screen_settings, "Hour");
    setting_hour_value = create_settings_value(setting_hour);

    setting_minute = create_settings_panel(screen_settings, "Minute");
    setting_minute_value = create_settings_value(setting_minute);

    setting_second = create_settings_panel(screen_settings, "Second");
    setting_second_value = create_settings_value(setting_second);
#ifdef AUDIO_ENABLE
    setting_audio = create_settings_panel(screen_settings, "Audio");
    setting_audio_value = create_settings_value(setting_audio);
#endif
    if (oled_exists() == false) {
        setting_lcd_brightness = create_settings_panel(screen_settings, "LCD Brightness");
        setting_lcd_brightness_slider = create_settings_slider(setting_lcd_brightness);
        lv_slider_set_range(setting_lcd_brightness_slider, 0, 15);
    }

    setting_default_layer = create_settings_panel(screen_settings, "Default Layer");
    setting_default_layer_value = create_settings_value(setting_default_layer);
    lv_label_set_long_mode(setting_default_layer_value, LV_LABEL_LONG_SCROLL);
    setting_default_layer_slider = create_settings_slider(setting_default_layer);
    lv_slider_set_range(setting_default_layer_slider, 0, 31);

}

void load_screen_settings(void) {
    lv_scr_load(screen_settings);
}

lv_obj_t * get_panel_from_menu_item(settings_menu_item_t menu_item);

void focus_current_settings_menu_item(settings_menu_item_t menu_item, bool is_selected) {
    static settings_menu_item_t previous_menu_item = 255;

    //if menu option changed
    lv_obj_t * active_menu_panel = get_panel_from_menu_item(menu_item);
    if (previous_menu_item != menu_item) {
        lv_obj_t * previous_menu_panel = get_panel_from_menu_item(previous_menu_item);
        lv_label_set_long_mode(lv_obj_get_child(previous_menu_panel, 0), LV_LABEL_LONG_CLIP);
        // Uncomment the line below for less smooth menu scrolling (can improve encoder repsonsiveness)
        // lv_obj_scroll_to_view(active_menu_panel, LV_ANIM_OFF);
        lv_group_focus_obj(active_menu_panel);
        lv_label_set_long_mode(lv_obj_get_child(active_menu_panel, 0), LV_LABEL_LONG_SCROLL_CIRCULAR);
        previous_menu_item = menu_item;
    }

    if (is_selected) {
        lv_obj_add_state(active_menu_panel, LV_STATE_PRESSED); 
        show_values_and_sliders(active_menu_panel);
    } else {
        lv_obj_clear_state(active_menu_panel, LV_STATE_PRESSED); 
        hide_values_and_sliders(active_menu_panel);
    }
    lv_group_focus_obj(active_menu_panel);
}

lv_obj_t * get_panel_from_menu_item(settings_menu_item_t menu_item) {
    switch(menu_item) {
    case exit_settings :
        return setting_exit_panel;
        break; 
    case active_layer : // Default layer setting
        return setting_active_layer;
        break;
    case backlight_brightness : //  Backlight Brightness
        return setting_backlight_brightness;
        break; 
    case backlight_breathing_period : //  Backlight Breathing Period
        return setting_backlight_breathing_period;
        break; 
    case underglow_mode : //  Underglow Mode
        return setting_underglow_mode;
        break; 
    case underglow_brightness : //  Underglow Brightness
        return setting_underglow_brightness;
        break;
    case underglow_color : //  Underglow Color
        return setting_underglow_color;
        break;
    case temperature_units : //  Temperature units
        return setting_temperature_units;
        break; 
    case display_timeout : //  Display Timeout
        return setting_display_timeout;
        break;
    case time_format:
        return setting_time_format;
        break;
    case hide_seconds:
        return setting_hide_seconds;
        break;
    case date_format:
        return setting_date_format;
        break;
    case set_year : //  Set Year
        return setting_year;
        break;
    case set_month : //  Set Month
        return setting_month;
        break;
    case set_day : //  Set Day
        return setting_day;
        break;
    case set_hour: //  Set Hours
        return setting_hour;
        break;
    case set_minute : //  Set Minutes
        return setting_minute;
        break;
    case set_second : //  Set Seconds
        return setting_second;
        break;
    case audio_enable : //  Audio Enable
        return setting_audio;
        break; 
    case lcd_brightness : // LCD brightness
        return setting_lcd_brightness;
        break;
    case default_layer : // Default layer setting
        return setting_default_layer;
        break;
    default:
        return setting_exit_panel;
        uprint("default break\n");
        break;
    }
}

void settings_update_backlight_brightness_value(uint8_t new_value) {
    lv_slider_set_value(setting_backlight_brightness_slider, new_value, LV_ANIM_ON);
}

void settings_update_backlight_breathing_period(uint8_t new_value) {
    lv_slider_set_value(setting_backlight_breathing_period_slider, new_value, LV_ANIM_ON);
    //if value is 1, write disabled, otherwise write newvalue seconds
    char new_value_str[15];
    if (new_value == 1) {
        sprintf(new_value_str, "Disabled");
    } else {
        sprintf(new_value_str, "%u seconds", new_value);
    }
    lv_label_set_text(setting_backlight_breathing_period_value,new_value_str);
}

 void settings_update_underglow_mode(uint8_t new_value) {
    //if value is 1, write disabled, otherwise write newvalue seconds
    //char new_value_str[20];
    lv_label_set_text(setting_underglow_mode_value, get_underglow_mode_str(new_value));
}

void settings_update_underglow_brightness(uint8_t new_value) {
    lv_slider_set_value(setting_underglow_brightness_slider, new_value, LV_ANIM_ON);
}

void settings_update_underglow_hue(uint8_t new_value) {
    lv_label_set_text(setting_underglow_color_value, get_underglow_color_str(new_value));
    lv_slider_set_value(setting_underglow_color_slider, new_value, LV_ANIM_ON);
}

void settings_update_temperature_units_are_f(bool new_value) {
    if (new_value == true) {
        lv_label_set_text(setting_temperature_units_value, "degrees F");
    } else {
        lv_label_set_text(setting_temperature_units_value, "degrees C");
    }
}

void settings_update_display_timeout(display_timeout_t new_value) {
    lv_label_set_text(setting_display_timeout_value, get_display_timeout_duration_str(new_value));
}

void settings_update_time_format_is_24h(bool new_value) {
    char new_value_str[8];
    if (new_value == 1) {
        sprintf(new_value_str, "24 Hour");
    } else {
        sprintf(new_value_str, "12 Hour");
    }
    lv_label_set_text(setting_time_format_value, new_value_str);
}

void settings_update_hide_seconds(bool new_value) {
    char new_value_str[8];
    if (new_value == 1) {
        sprintf(new_value_str, "Yes");
    } else {
        sprintf(new_value_str, "No");
    }
    lv_label_set_text(setting_hide_seconds_value, new_value_str);
}

void settings_update_date_format(date_format_t date_format) {
    switch(date_format) {
    case mmddyyyy :
        lv_label_set_text(setting_date_format_value, "mm/dd/yyyy");
        break; 
    case mdyy :
        lv_label_set_text(setting_date_format_value, "m/d/yy");
        break; 
    case ddmmyyyy :
        lv_label_set_text(setting_date_format_value, "dd/mm/yyyy");
        break;
    case dmyy :
        lv_label_set_text(setting_date_format_value, "d/m/yy");
        break;
    case yyyymmdd :
        lv_label_set_text(setting_date_format_value, "yyyy/mm/dd");
        break;
    case mondyyyy :
        lv_label_set_text(setting_date_format_value, "mon d, yyyy");
        break;
    case dmonyyyy :
        lv_label_set_text(setting_date_format_value, "d mon yyyy");
        break;
    case monthdyyyy :
        lv_label_set_text(setting_date_format_value, "month d, yyyy");
        break;
    case dmonthyyyy :
        lv_label_set_text(setting_date_format_value, "d month yyyy");
        break;
    default:
        lv_label_set_text(setting_date_format_value, "yyyy/mm/dd");
        uprint("default break\n");
        break;
    }
}

void settings_update_year(uint16_t year) {
    lv_label_set_text(setting_year_value, get_year_str(year));
}

void settings_update_month(uint8_t month) {
    lv_label_set_text(setting_month_value, get_month_str(month));
}

void settings_update_day(uint8_t day) {
    lv_label_set_text(setting_day_value, get_day_str(day));
}

void settings_update_hour(uint8_t hour) {
    lv_label_set_text(setting_hour_value, get_hour_str(hour));
}

void settings_update_minute(uint8_t minute) {
    lv_label_set_text(setting_minute_value, get_minute_str(minute));
}

void settings_update_second(uint8_t second) {
    lv_label_set_text(setting_second_value, get_second_str(second));
}

void settings_update_audio(bool new_value) {
    char new_value_str[10];
    if (new_value == 1) {
        sprintf(new_value_str, "Enabled");
    } else {
        sprintf(new_value_str, "Disabled");
    }
    lv_label_set_text(setting_audio_value, new_value_str);
}

void settings_update_lcd_brightness(uint8_t new_value) {
    lv_slider_set_value(setting_lcd_brightness_slider, new_value, LV_ANIM_ON);
}

void settings_update_underglow_color_hidden(bool new_value) {
    if (new_value) {
        lv_obj_add_flag(setting_underglow_color, LV_OBJ_FLAG_HIDDEN);
    } else {
        lv_obj_clear_flag(setting_underglow_color, LV_OBJ_FLAG_HIDDEN);
    }
}

void settings_update_underglow_brightness_hidden(bool new_value) {
    if (new_value) {
        lv_obj_add_flag(setting_underglow_brightness, LV_OBJ_FLAG_HIDDEN);
    } else {
        lv_obj_clear_flag(setting_underglow_brightness, LV_OBJ_FLAG_HIDDEN);
    }
}


void settings_update_active_layer(uint8_t new_value) {
    lv_slider_set_value(setting_active_layer_slider, new_value, LV_ANIM_ON);
    char new_value_str[15];
    sprintf(new_value_str, "%s  %u", get_layer_str(new_value), new_value);
    lv_label_set_text(setting_active_layer_value,new_value_str);
}

void settings_update_default_layer(uint8_t new_value) {
    lv_slider_set_value(setting_default_layer_slider, new_value, LV_ANIM_ON);
    char new_value_str[15];
    sprintf(new_value_str, "%s  %u", get_layer_str(new_value), new_value);
    lv_label_set_text(setting_default_layer_value,new_value_str);
}