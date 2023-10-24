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

#include "screen_bongocat.h"
#include "lvgl.h"
#include "overlay_panel.h"

lv_obj_t *screen_bongocat;
lv_obj_t *screen_bongocat_image_tap1;
lv_obj_t *screen_bongocat_image_tap2;
lv_obj_t *screen_bongocat_image_idle1;
lv_obj_t *screen_bongocat_image_idle2;
lv_obj_t *screen_bongocat_image_idle3;
lv_obj_t *screen_bongocat_image_idle4;
lv_obj_t *screen_bongocat_image_idle5;
lv_obj_t *screen_bongocat_image_prep;

lv_obj_t *visible_bongocat_image;

lv_obj_t *screen_bongocat_overlay;

LV_IMG_DECLARE(bongo_idle1);
LV_IMG_DECLARE(bongo_idle3);
LV_IMG_DECLARE(bongo_idle4);
LV_IMG_DECLARE(bongo_idle5);
LV_IMG_DECLARE(bongo_tap1);
LV_IMG_DECLARE(bongo_tap2);
LV_IMG_DECLARE(bongo_prep);

lv_obj_t *create_std_bongocat_img(lv_obj_t *parent, const lv_img_dsc_t *img) {
    lv_obj_t *new_img_obj = lv_img_create(parent);
    lv_img_set_src(new_img_obj, img);
    lv_obj_set_width( new_img_obj, LV_SIZE_CONTENT);
    lv_obj_set_height( new_img_obj, LV_SIZE_CONTENT);
    lv_obj_set_align( new_img_obj, LV_ALIGN_CENTER );
    lv_obj_add_flag( new_img_obj, LV_OBJ_FLAG_ADV_HITTEST );
    lv_obj_clear_flag( new_img_obj, LV_OBJ_FLAG_SCROLLABLE );
    lv_obj_add_flag( new_img_obj, LV_OBJ_FLAG_HIDDEN);

    return new_img_obj;
}

void screen_bongocat_init(void)
{
    screen_bongocat = lv_obj_create(NULL);
    lv_obj_clear_flag( screen_bongocat, LV_OBJ_FLAG_SCROLLABLE );
    lv_obj_set_style_bg_color(screen_bongocat, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT );
    lv_obj_set_style_bg_opa(screen_bongocat, 255, LV_PART_MAIN| LV_STATE_DEFAULT);

    screen_bongocat_image_tap1 = create_std_bongocat_img(screen_bongocat, &bongo_tap1);
    screen_bongocat_image_tap2 = create_std_bongocat_img(screen_bongocat, &bongo_tap2);
    screen_bongocat_image_prep = create_std_bongocat_img(screen_bongocat, &bongo_prep);
    screen_bongocat_image_idle1 = create_std_bongocat_img(screen_bongocat, &bongo_idle1);
    screen_bongocat_image_idle2 = screen_bongocat_image_idle1;  // idle1 and idle2 images are the same
    screen_bongocat_image_idle3 = create_std_bongocat_img(screen_bongocat, &bongo_idle3);
    screen_bongocat_image_idle4 = create_std_bongocat_img(screen_bongocat, &bongo_idle4);
    screen_bongocat_image_idle5 = create_std_bongocat_img(screen_bongocat, &bongo_idle5);

    lv_obj_clear_flag(screen_bongocat_image_idle1, LV_OBJ_FLAG_HIDDEN);
    visible_bongocat_image = screen_bongocat_image_idle1;

    screen_bongocat_overlay = create_overlay_panel(screen_bongocat);
}


void switch_to_image(lv_obj_t *bongoimage) {
    if (visible_bongocat_image != bongoimage) {
        lv_obj_add_flag(visible_bongocat_image, LV_OBJ_FLAG_HIDDEN);
        visible_bongocat_image = bongoimage;
        lv_obj_clear_flag(visible_bongocat_image, LV_OBJ_FLAG_HIDDEN);
    }
}

void screen_bongocat_show_state(bongocat_show_state_t current_image_state) {
    switch(current_image_state) {
    case bongocat_show_idle1:
        switch_to_image(screen_bongocat_image_idle1);
        break;
    case bongocat_show_idle2:
        switch_to_image(screen_bongocat_image_idle2);
        break;
    case bongocat_show_idle3:
        switch_to_image(screen_bongocat_image_idle3);
        break;
   case bongocat_show_idle4:
        switch_to_image(screen_bongocat_image_idle4);
        break;
    case bongocat_show_idle5:
        switch_to_image(screen_bongocat_image_idle5);
        break;
    case bongocat_show_tap1:
        switch_to_image(screen_bongocat_image_tap1);
        break;
    case bongocat_show_tap2:
        switch_to_image(screen_bongocat_image_tap2);
        break;
    case bongocat_show_prep:
        switch_to_image(screen_bongocat_image_prep);
        break;
    }
}

void load_screen_bongocat(void) {
    lv_scr_load(screen_bongocat);
}

void screen_bongocat_update_overlay(void) {
    update_overlay_panel(screen_bongocat_overlay);
}