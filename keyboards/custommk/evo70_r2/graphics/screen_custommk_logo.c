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

#include "lvgl.h"
#include "overlay_panel.h"

lv_obj_t *screen_custommk_logo;
lv_obj_t *screen_custommk_logo_image;

lv_obj_t *screen_custommk_logo_overlay;

LV_IMG_DECLARE(custommk_logo);

void screen_custommk_logo_init(void) {
    screen_custommk_logo = lv_obj_create(NULL);
    lv_obj_clear_flag( screen_custommk_logo, LV_OBJ_FLAG_SCROLLABLE );
    lv_obj_set_style_bg_color(screen_custommk_logo, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT );
    lv_obj_set_style_bg_opa(screen_custommk_logo, 255, LV_PART_MAIN| LV_STATE_DEFAULT);

    screen_custommk_logo_image = lv_img_create(screen_custommk_logo);
    lv_img_set_src(screen_custommk_logo_image, &custommk_logo);
    lv_obj_set_width( screen_custommk_logo_image, LV_SIZE_CONTENT);
    lv_obj_set_height( screen_custommk_logo_image, LV_SIZE_CONTENT);
    lv_obj_set_align( screen_custommk_logo_image, LV_ALIGN_CENTER );
    lv_obj_add_flag( screen_custommk_logo_image, LV_OBJ_FLAG_ADV_HITTEST );
    lv_obj_clear_flag( screen_custommk_logo_image, LV_OBJ_FLAG_SCROLLABLE );

    screen_custommk_logo_overlay = create_overlay_panel(screen_custommk_logo);
}

void load_screen_custommk_logo(void) {
    lv_scr_load(screen_custommk_logo);
}

void screen_custommk_logo_update_overlay(void) {
    update_overlay_panel(screen_custommk_logo_overlay);
}