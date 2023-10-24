/* Copyright 2023 David Hoelscher (@customMK), Moritz Plattner
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

#include "screen_bongocat_updater.h"
#include "screen_bongocat.h"
#include "matrix.h"
#include "quantum.h"


#define BONGOCAT_ANIM_FRAME_DURATION 100
#define BONGOCAT_IDLE_TIMEOUT 750
#define BONGOCAT_SLEEP_TIMEOUT 15000

enum anin_states { sleep, idle, prep, tap };
static uint8_t anim_state = idle;
uint32_t idle_timeout_timer = 0;
uint32_t anim_timer = 0;
bongocat_show_state_t current_idle_frame = 0;
bongocat_show_state_t current_tap_frame = 6;


bool is_key_down(void) {
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
        if (matrix_get_row(i) > 0) {
            return true;
        }
    }
    return false;
}

bool is_new_tap(void) {
    static matrix_row_t old_matrix[] = { 0, 0, 0, 0, 0, 0, 0 };
    bool new_tap = false;
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
        if (matrix_get_row(i) > old_matrix[i]) { // more 1's detected, there was a new tap
            new_tap = true;

        }
        old_matrix[i] = matrix_get_row(i);
    }
    return new_tap;
}

void eval_anim_state(void) {
    bool key_down;
    key_down = is_key_down();

    switch (anim_state) {
        case sleep:
            if(key_down) { anim_state = tap; }
            break; 
        case idle:
            if(key_down) { anim_state = tap; }
            else if (timer_elapsed32(idle_timeout_timer) >= BONGOCAT_SLEEP_TIMEOUT) //prep to idle
                {
                    anim_state = sleep;
                    current_idle_frame = 0;
                }
            break;
        case prep:
            if(key_down) { anim_state = tap; }
            else if (timer_elapsed32(idle_timeout_timer) >= BONGOCAT_IDLE_TIMEOUT) //prep to idle
                {
                    anim_state = idle;
                    current_idle_frame = 0;
                }
            break;
        case tap:
            if (!key_down)
            {
                anim_state = prep;
                idle_timeout_timer = timer_read32();
            }
            break;
        default:
            break;
    }
}

void update_screen_bongocat(void) {
    static bool already_tapped = false;
    if (is_new_tap()) {
        already_tapped = false;
    };
    eval_anim_state();
    switch (anim_state) {
        case sleep:
            screen_bongocat_show_state(bongocat_show_idle5);
            break;
        case idle:       
            screen_bongocat_show_state(bongocat_show_idle5 - current_idle_frame);
            if (timer_elapsed32(anim_timer) > BONGOCAT_ANIM_FRAME_DURATION) {
                current_idle_frame = (current_idle_frame + 1) % 5;
                anim_timer = timer_read32();
            }
            break;
        case prep:
            screen_bongocat_show_state(bongocat_show_prep);
            already_tapped = false;
            break;
        case tap:
            if (already_tapped == false) {
                if (current_tap_frame == bongocat_show_tap1) {
                    current_tap_frame = bongocat_show_tap2;
                }
                else {
                    current_tap_frame = bongocat_show_tap1;
                }
                screen_bongocat_show_state(current_tap_frame);
            }
            already_tapped = true;
            break;
        default:
            screen_bongocat_show_state(bongocat_show_idle5);
            already_tapped = false;
            break;

    }
}
   