
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

#include "overlay_panel.h"
#include "evo70_r2_graphics.h"


static char overlay_text[50];
static bool overlay_on = false;
static uint8_t current_overlay_message = 0;
static uint32_t overlay_timer;

LV_FONT_DECLARE(public_pixel)

lv_obj_t *create_overlay_panel(lv_obj_t *parent) {
    lv_obj_t *overlay_panel = lv_obj_create(parent);
    lv_obj_set_width( overlay_panel, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height( overlay_panel, LV_SIZE_CONTENT);   /// 60
    lv_obj_set_align( overlay_panel, LV_ALIGN_CENTER );
    lv_obj_clear_flag( overlay_panel, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
    lv_obj_set_style_bg_color(overlay_panel, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT );
    if (oled_exists()) {
        lv_obj_set_style_bg_opa(overlay_panel, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
        lv_obj_set_style_border_color(overlay_panel, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT );
        lv_obj_set_style_border_opa(overlay_panel, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
        lv_obj_set_style_pad_left(overlay_panel, 3, LV_PART_MAIN| LV_STATE_DEFAULT);
        lv_obj_set_style_pad_right(overlay_panel, 3, LV_PART_MAIN| LV_STATE_DEFAULT);
        lv_obj_set_style_pad_top(overlay_panel, 3, LV_PART_MAIN| LV_STATE_DEFAULT);
        lv_obj_set_style_pad_bottom(overlay_panel, 3, LV_PART_MAIN| LV_STATE_DEFAULT);
    } else {
        lv_obj_set_style_bg_opa(overlay_panel, 170, LV_PART_MAIN| LV_STATE_DEFAULT);
        lv_obj_set_style_border_width(overlay_panel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
        lv_obj_set_style_pad_left(overlay_panel, 5, LV_PART_MAIN| LV_STATE_DEFAULT);
        lv_obj_set_style_pad_right(overlay_panel, 5, LV_PART_MAIN| LV_STATE_DEFAULT);
        lv_obj_set_style_pad_top(overlay_panel, 5, LV_PART_MAIN| LV_STATE_DEFAULT);
        lv_obj_set_style_pad_bottom(overlay_panel, 5, LV_PART_MAIN| LV_STATE_DEFAULT);
    }
    lv_obj_add_flag(overlay_panel, LV_OBJ_FLAG_HIDDEN);


    if (oled_exists()) {
        lv_obj_t *overlay_label = lv_label_create(overlay_panel);
        lv_obj_set_width( overlay_label, LV_SIZE_CONTENT);  /// 1
        lv_obj_set_height( overlay_label, LV_SIZE_CONTENT);   /// 1
        lv_obj_set_align( overlay_label, LV_ALIGN_CENTER );
        lv_label_set_text(overlay_label,"Caps Lock On");
        lv_obj_set_style_text_color(overlay_label, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT );
        lv_obj_set_style_text_opa(overlay_label, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
        lv_obj_set_style_text_font(overlay_label, &public_pixel, LV_PART_MAIN| LV_STATE_DEFAULT);


    } else {
        lv_obj_t *overlay_subpanel = lv_obj_create(overlay_panel);
        lv_obj_set_width( overlay_subpanel, LV_SIZE_CONTENT);  /// 1
        lv_obj_set_height( overlay_subpanel, LV_SIZE_CONTENT);   /// 1
        lv_obj_set_align( overlay_subpanel, LV_ALIGN_CENTER );
        lv_obj_clear_flag( overlay_subpanel, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
        lv_obj_set_style_bg_color(overlay_subpanel, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT );
        lv_obj_set_style_bg_opa(overlay_subpanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
        lv_obj_set_style_border_color(overlay_subpanel, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT );
        lv_obj_set_style_border_opa(overlay_subpanel, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
        lv_obj_set_style_pad_left(overlay_subpanel, 5, LV_PART_MAIN| LV_STATE_DEFAULT);
        lv_obj_set_style_pad_right(overlay_subpanel, 5, LV_PART_MAIN| LV_STATE_DEFAULT);
        lv_obj_set_style_pad_top(overlay_subpanel, 5, LV_PART_MAIN| LV_STATE_DEFAULT);
        lv_obj_set_style_pad_bottom(overlay_subpanel, 5, LV_PART_MAIN| LV_STATE_DEFAULT);

        lv_obj_t *overlay_label = lv_label_create(overlay_subpanel);
        lv_obj_set_width( overlay_label, LV_SIZE_CONTENT);  /// 1
        lv_obj_set_height( overlay_label, LV_SIZE_CONTENT);   /// 1
        lv_obj_set_align( overlay_label, LV_ALIGN_CENTER );
        lv_label_set_text(overlay_label,"Caps Lock On");
        lv_obj_set_style_text_color(overlay_label, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT );
        lv_obj_set_style_text_opa(overlay_label, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
        lv_obj_set_style_text_font(overlay_label, &lv_font_montserrat_18, LV_PART_MAIN| LV_STATE_DEFAULT);
    }

    return overlay_panel;
}

bool is_overlay_on(void) {
    return overlay_on;
}

uint8_t overlay_message(void) {
    return current_overlay_message;
}
void hide_overlay_panel(lv_obj_t *overlay_panel) {
    lv_obj_add_flag(overlay_panel, LV_OBJ_FLAG_HIDDEN);
}

void show_overlay_panel(lv_obj_t *overlay_panel) {
    lv_obj_clear_flag(overlay_panel, LV_OBJ_FLAG_HIDDEN);
}

void change_overlay_panel_text(lv_obj_t *overlay_panel, char *new_text) {
    if (oled_exists()) {  //for OLED, label is child of panel
        lv_label_set_text(lv_obj_get_child(overlay_panel, 0), new_text);
    } else { // for LCD, label is child of child of panel
        lv_label_set_text(lv_obj_get_child(lv_obj_get_child(overlay_panel, 0), 0), new_text);
    }
}

void update_overlay_panel(lv_obj_t *overlay_panel) {
    if (overlay_on) {
        show_overlay_panel(overlay_panel);
    } else {
        hide_overlay_panel(overlay_panel);
    }
    change_overlay_panel_text(overlay_panel, overlay_text);
}

void overlay_capslock_on(void) {
    overlay_on = true;
    current_overlay_message = 32;
    sprintf(overlay_text, "Caps Lock On");
    overlay_timer = timer_read32();
}

void overlay_capslock_off(void) {
    overlay_on = true;
    current_overlay_message = 33;
    sprintf(overlay_text, "Caps Lock Off");
    overlay_timer = timer_read32();
}

void overlay_numlock_on(void) {
    overlay_on = true;
    current_overlay_message = 34;
    sprintf(overlay_text, "Num Lock On");
    overlay_timer = timer_read32();
}

void overlay_numlock_off(void) {
    overlay_on = true;
    current_overlay_message = 35;
    sprintf(overlay_text, "Num Lock Off");
    overlay_timer = timer_read32();
}

void overlay_layer_active(uint8_t layernum) {
    overlay_on = true;
    current_overlay_message = layernum;
    sprintf(overlay_text, "Layer %u", layernum);
    overlay_timer = timer_read32();
}

void overlay_task(void) {
    if (timer_elapsed32(overlay_timer) > 1000) {
        overlay_on = false;
    }

}