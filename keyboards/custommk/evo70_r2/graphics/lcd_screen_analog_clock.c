// Copyright 2023 David Hoelscher (@customMK)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "lcd_screen_analog_clock.h"
#include "overlay_panel.h"
#include <math.h>

static lv_obj_t *lcd_screen_analog_clock;

static lv_style_t style_screen;

static lv_obj_t *leatherbg;
static lv_obj_t *analog_clockface;
static lv_obj_t *analog_clockface_hourhand;
static lv_obj_t *analog_clockface_minutehand;
static lv_obj_t *analog_clockface_secondhand;
static lv_obj_t *analog_clockface_moon;

static lv_obj_t *analog_clockface_date;
static lv_obj_t *analog_clockface_temperature;

static lv_obj_t * mooncanvas;

static lv_obj_t * lcd_screen_analog_overlay;

#define MOONWIDTH 50
#define MOONHEIGHT 50

lv_obj_t *create_std_img(lv_obj_t *parent, const lv_img_dsc_t *img, int x, int y) {

    lv_obj_t *new_img_obj = lv_img_create(parent);
    lv_img_set_src(new_img_obj, img);
    lv_obj_set_width(new_img_obj, LV_SIZE_CONTENT);
    lv_obj_set_height(new_img_obj, LV_SIZE_CONTENT);
    lv_obj_set_x(new_img_obj, x);
    lv_obj_set_y(new_img_obj, y);
    lv_obj_set_align(new_img_obj, LV_ALIGN_CENTER);
    lv_obj_clear_flag(new_img_obj, LV_OBJ_FLAG_SCROLLABLE);

    return new_img_obj;
}

LV_IMG_DECLARE(leatherbackground);
LV_IMG_DECLARE(watchface1);
LV_IMG_DECLARE(hourhand);
LV_IMG_DECLARE(minutehand);
LV_IMG_DECLARE(secondhand_2x_white);
LV_IMG_DECLARE(moon);

void lcd_screen_analog_clock_init(void)
{

    lv_style_init(&style_screen);
    lv_style_set_bg_color(&style_screen, lv_color_white());

    lcd_screen_analog_clock = lv_obj_create(NULL);
    lv_obj_add_style(lcd_screen_analog_clock, &style_screen, 0);
    lv_obj_clear_flag(lcd_screen_analog_clock, LV_OBJ_FLAG_SCROLLABLE);
    

    leatherbg = create_std_img(lcd_screen_analog_clock, &leatherbackground, 0, 0);
    analog_clockface = create_std_img(lcd_screen_analog_clock, &watchface1, -40, 0);
    analog_clockface_hourhand = create_std_img(lcd_screen_analog_clock, &hourhand, -40, 0);
    analog_clockface_minutehand = create_std_img(lcd_screen_analog_clock, &minutehand, -40, 0);
    analog_clockface_secondhand = create_std_img(lcd_screen_analog_clock, &secondhand_2x_white, -40, -20);

    lv_img_set_pivot(analog_clockface_secondhand, 9, 66);
    lv_img_set_angle(analog_clockface_secondhand, 1800);
    lv_obj_set_style_img_recolor(analog_clockface_secondhand, lv_color_hex(0xCF0000), LV_PART_MAIN| LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor_opa(analog_clockface_secondhand, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
    lv_img_set_zoom(analog_clockface_secondhand,128);

    analog_clockface_date = lv_label_create(lcd_screen_analog_clock);
    lv_obj_set_width( analog_clockface_date, lv_pct(100));
    lv_obj_set_height( analog_clockface_date, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_x( analog_clockface_date, 0 );
    lv_obj_set_y( analog_clockface_date, 24 );
    lv_obj_set_align( analog_clockface_date, LV_ALIGN_RIGHT_MID );
    lv_label_set_text(analog_clockface_date, "Sunday\nJan 31, 2023");
    lv_obj_set_style_text_align(analog_clockface_date, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN| LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(analog_clockface_date, &lv_font_montserrat_14, LV_PART_MAIN);

    analog_clockface_temperature = lv_label_create(lcd_screen_analog_clock);
    lv_obj_set_x(analog_clockface_temperature, 5);
    lv_obj_set_y(analog_clockface_temperature, -30);
    lv_label_set_text(analog_clockface_temperature, "-98.6F");
    lv_obj_set_style_text_align(analog_clockface_temperature, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN| LV_STATE_DEFAULT);
    lv_obj_set_align( analog_clockface_temperature, LV_ALIGN_CENTER );
    lv_obj_set_width( analog_clockface_temperature, LV_SIZE_CONTENT);
    lv_obj_set_height( analog_clockface_temperature, LV_SIZE_CONTENT); 
    lv_obj_set_style_text_font(analog_clockface_temperature, &lv_font_montserrat_16, LV_PART_MAIN);

    analog_clockface_moon = create_std_img(lcd_screen_analog_clock, &moon, 55, -16);

    static lv_color_t cbuf[LV_CANVAS_BUF_SIZE_ALPHA_4BIT(50, 50)];
    mooncanvas = lv_canvas_create(lcd_screen_analog_clock);
    lv_canvas_set_buffer(mooncanvas, cbuf, 50, 50, LV_IMG_CF_ALPHA_4BIT);
    lv_obj_align(mooncanvas, LV_ALIGN_CENTER, 55, -16);

    uint8_t i,j;
    for (i = 0; i < MOONHEIGHT/2; i++) {
        for (j = 0; j < MOONWIDTH; j++) {
            lv_canvas_set_px(mooncanvas, j, i, lv_color_make(0,0,0));
            lv_canvas_set_px(mooncanvas, j, MOONHEIGHT-i, lv_color_make(0,0,0));
        }
    }

    lcd_screen_analog_overlay = create_overlay_panel(lcd_screen_analog_clock);
}

void lcd_screen_update_analog_seconds(uint32_t second_angle_10x) {
    lv_img_set_angle(analog_clockface_secondhand, second_angle_10x); 
}

void lcd_screen_update_analog_seconds_is_hidden(bool hidden) {
    if (hidden) {
        lv_obj_add_flag(analog_clockface_secondhand, LV_OBJ_FLAG_HIDDEN);
    } else {
        lv_obj_clear_flag(analog_clockface_secondhand, LV_OBJ_FLAG_HIDDEN);        
    }
}

void lcd_screen_update_analog_minutes(uint32_t minute_angle_10x) {
    lv_img_set_angle(analog_clockface_minutehand, minute_angle_10x); 
}

void lcd_screen_update_analog_hours(uint32_t hour_angle_10x) {
    lv_img_set_angle(analog_clockface_hourhand, hour_angle_10x); 
}

void lcd_screen_analog_set_date(char *datestr) {
    lv_label_set_text(analog_clockface_date, datestr);
}

void lcd_screen_analog_draw_moon_phase(uint16_t cycle_percent_10x) {
    static uint16_t prev_cycle_percent_10x = 1001;
    if (cycle_percent_10x == prev_cycle_percent_10x) {
        return;
    }
    prev_cycle_percent_10x = cycle_percent_10x;
    uint8_t i, j;
    float shadow_edge;
    uint8_t shadow_edge_uint;
    
    bool waxing = true;
    if (cycle_percent_10x > 500) {
        waxing = false;
        cycle_percent_10x = cycle_percent_10x - 500;
    }
    for (i = 1; i <= 25; i++) {
        shadow_edge = cosf((float)cycle_percent_10x/500.0*3.14159)*sqrtf(48*48/(2*2)-((25-i)*(25-i)))+24;
        shadow_edge_uint = (uint8_t)shadow_edge;
        lv_canvas_set_px_opa(mooncanvas, shadow_edge_uint, i, LV_OPA_50);
        lv_canvas_set_px_opa(mooncanvas, shadow_edge_uint, 48-i, LV_OPA_50);

        //if waxing, draw black opaque pixels to the left of the shadow line
        //if waning, draw black opaque pixels to the right of the shadow line
        for (j=0;j<shadow_edge_uint;j++) {
            if (waxing) {
                lv_canvas_set_px_opa(mooncanvas, j, 48-i, LV_OPA_COVER);
                lv_canvas_set_px_opa(mooncanvas, j, i, LV_OPA_COVER);
            } else {
                lv_canvas_set_px_opa(mooncanvas, j, 48-i, LV_OPA_TRANSP);
                lv_canvas_set_px_opa(mooncanvas, j, i, LV_OPA_TRANSP);
            }
        }
        for (j=49;j>shadow_edge_uint;j--) {
            if (waxing) {
                lv_canvas_set_px_opa(mooncanvas, j, 48-i, LV_OPA_TRANSP);
                lv_canvas_set_px_opa(mooncanvas, j, i, LV_OPA_TRANSP);
            } else {
                lv_canvas_set_px_opa(mooncanvas, j, 48-i, LV_OPA_COVER);
                lv_canvas_set_px_opa(mooncanvas, j, i, LV_OPA_COVER);
            }
        }
    }
}

void lcd_screen_analog_set_temperature(char *temperature_string) {
    lv_label_set_text(analog_clockface_temperature, temperature_string);
}


void load_lcd_screen_analog_clock(void) {
    lv_scr_load(lcd_screen_analog_clock);
}

void lcd_screen_analog_update_overlay(void) {
    update_overlay_panel(lcd_screen_analog_overlay);
}