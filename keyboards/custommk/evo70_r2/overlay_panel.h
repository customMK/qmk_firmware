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
#include "evo70_r2.h"

#pragma once

lv_obj_t *create_overlay_panel(lv_obj_t *parent);
void update_overlay_panel(lv_obj_t *overlay_panel);

bool is_overlay_on(void);
uint8_t overlay_message_id(void);

void overlay_capslock_on(void);
void overlay_capslock_off(void);
void overlay_numlock_on(void);
void overlay_numlock_off(void);
void overlay_layer_active(uint8_t layernum);

void overlay_task(void);