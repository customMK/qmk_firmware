
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

#include "display_control.h"
#include "evo70_r2_graphics.h"
#include "lcd_backlight.h"
#include "quantum.h"

extern user_config_t user_config;

void display_decrease_timeout(void) {
    if (user_config.display_timeout_setting > 0) {
        user_config.display_timeout_setting--;
        update_kb_eeprom();
    }
}

void display_increase_timeout(void) {
    if (user_config.display_timeout_setting < 7) {
        user_config.display_timeout_setting++;
        update_kb_eeprom();
    }
}

uint32_t timeout_durations_ms[] = {
    0,
    10000, // 10 seconds
    30000,  // 30 seconds
    60000,  // 60 seconds
    300000,  //5 minutes
    600000,  //10 minutes
    3600000, // 1 hour
    28800000 //8 hours
};

char *timeout_durations_strings[] = {
    "Never",
    "10 seconds",
    "30 seconds",
    "60 seconds",
    "5 minutes",
    "15 minutes",
    "1 hour",
    "8 hours"
};


uint32_t get_display_timeout_duration_ms(display_timeout_t duration) {
    return timeout_durations_ms[duration];
}

char *get_display_timeout_duration_str(display_timeout_t duration) {
    return timeout_durations_strings[duration];
}

 void display_timeout_task(void) {
    // if timeout isn't infinity and we've have reached the timeout threshold, and the display is on, then turn display off as a timeout
    if ((user_config.display_timeout_setting != 0) && (last_input_activity_elapsed() > get_display_timeout_duration_ms(user_config.display_timeout_setting))) {
        if(is_display_on()) {
            turn_display_off_auto_timeout();
        }
    }
}

void turn_display_on(void)  {
    qp_power(display,true);
    if (!oled_exists()) {
        turn_on_lcd_backlight();
    }
    user_config.display_on = true;
    update_kb_eeprom();
}

void turn_display_off(void)  {
    qp_power(display,false);
    if (!oled_exists()) {
        turn_off_lcd_backlight();
    }
    user_config.display_on = false;
    user_config.display_off_was_auto_timeout = false;
    update_kb_eeprom();
}

void turn_display_off_auto_timeout(void)  {
    qp_power(display,false);
    if (!oled_exists()) {
        turn_off_lcd_backlight();
    }
    user_config.display_on = false;
    user_config.display_off_was_auto_timeout = true;
    update_kb_eeprom();
}


bool is_display_on(void)  {
    return user_config.display_on;
}

bool is_display_off_due_to_timeout(void) {
    return ((user_config.display_on == 0) && (user_config.display_off_was_auto_timeout));
}