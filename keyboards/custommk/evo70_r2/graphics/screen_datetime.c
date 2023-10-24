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
#include "date_format.h"
#include "rtc.h"
#include "overlay_panel.h"

lv_obj_t *screen_datetime;
lv_obj_t *screen_datetime_label;

lv_obj_t *screen_datetime_overlay;

LV_FONT_DECLARE(public_pixel)

void screen_datetime_init(void)
{
    screen_datetime = lv_obj_create(NULL);
    lv_obj_clear_flag(screen_datetime, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
    lv_obj_set_style_bg_color(screen_datetime, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT );
    lv_obj_set_style_bg_opa(screen_datetime, 255, LV_PART_MAIN| LV_STATE_DEFAULT);

    screen_datetime_label = lv_label_create(screen_datetime);
    lv_obj_set_width( screen_datetime_label, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height( screen_datetime_label, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_align( screen_datetime_label, LV_ALIGN_CENTER );
    lv_label_set_text(screen_datetime_label,"date and time goes here");
    lv_obj_set_style_text_color(screen_datetime_label, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT );
    lv_obj_set_style_text_opa(screen_datetime_label, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(screen_datetime_label, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(screen_datetime_label, 3, LV_PART_MAIN| LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(screen_datetime_label, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN| LV_STATE_DEFAULT);
    if (oled_exists()) {
        lv_obj_set_style_text_font(screen_datetime_label, &public_pixel, LV_PART_MAIN| LV_STATE_DEFAULT);
    } else {
        lv_obj_set_style_text_font(screen_datetime_label, &lv_font_montserrat_16, LV_PART_MAIN| LV_STATE_DEFAULT);
    }

    screen_datetime_overlay = create_overlay_panel(screen_datetime); 

}

void load_screen_datetime(void) {
    lv_scr_load(screen_datetime);
}


void screen_update_datetime_value(char *datetimestr) {
    lv_label_set_text(screen_datetime_label, datetimestr);
}

void screen_datetime_update_overlay(void) {
    update_overlay_panel(screen_datetime_overlay);
}
