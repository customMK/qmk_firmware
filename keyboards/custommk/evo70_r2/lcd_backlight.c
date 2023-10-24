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

#include "lcd_backlight.h"
#include "evo70_r2.h"

extern user_config_t user_config;

// I would reuse CIE lightness functions from the backlight_pwm implementation, but it's not
// exposed through a header file. It probably should be however, because both AVR and ARM
// each have it implemented twice (identically)

// See http://jared.geek.nz/2013/feb/linear-led-pwm
static uint16_t cie_lightness(uint16_t v) {
    if (v <= 5243)    // if below 8% of max
        return v / 9; // same as dividing by 900%
    else {
        uint32_t y = (((uint32_t)v + 10486) << 8) / (10486 + 0xFFFFUL); // add 16% of max and compare
        // to get a useful result with integer division, we shift left in the expression above
        // and revert what we've done again after squaring.
        y = y * y * y >> 8;
        if (y > 0xFFFFUL) { // prevent overflow
            return 0xFFFFU;
        } else {
            return (uint16_t)y;
        }
    }
}

void turn_off_lcd_backlight(void){
    
    //chSysLockFromISR();
    //pwmDisableChannel(&PWMD2, 3 - 1);
    //chSysUnlockFromISR();
    
    pwmDisableChannel(&PWMD2, 3 - 1);

}

void turn_on_lcd_backlight(void){

    uint32_t level;
    // Never dim to full off becasuse that's hard to recover from (can't see the screen).
    // Better to require the user to turn off the display with a long press instead
    level = user_config.lcd_backlight_brightness + 1;
    // 17 backlight levels, including "off" which we are making unreachable
    uint32_t duty = (uint32_t)(cie_lightness(0xFFFF * (uint32_t)level / 16));  
    // Timer 2, channel 3
    
    //chSysLockFromISR();
    //pwmEnableChannelI(&PWMD2, 3 - 1, PWM_FRACTION_TO_WIDTH(&PWMD2, 0xFFFF, duty));
    //chSysUnlockFromISR();
    
    pwmEnableChannel(&PWMD2, 3 - 1, PWM_FRACTION_TO_WIDTH(&PWMD2, 0xFFFF, duty));
}

void set_lcd_backlight_level(uint8_t brightness){
    user_config.lcd_backlight_brightness = brightness % 16;
    update_kb_eeprom();
    turn_on_lcd_backlight();
}

uint8_t get_lcd_backlight_level(void) {
    return user_config.lcd_backlight_brightness;
}

void lcd_decrement_brightness(void) {
    if (user_config.lcd_backlight_brightness > 0) {
        user_config.lcd_backlight_brightness--;
        update_kb_eeprom();
    }
    turn_on_lcd_backlight();
}

void lcd_increment_brightness(void) {
    if (user_config.lcd_backlight_brightness < 15) {
        user_config.lcd_backlight_brightness++;
        update_kb_eeprom();
    }
    turn_on_lcd_backlight();
}

void lcd_backlight_init(void) {
    palSetPadMode(PAL_PORT(B10), PAL_PAD(B10), PAL_MODE_ALTERNATE(1));

    static PWMConfig pwmCFG = {
        .frequency = 0xFFFF, /* PWM clock frequency  */
        .period    = 256,    /* PWM period in counter ticks. e.g. clock frequency is 10KHz, period is 256 ticks then t_period is 25.6ms */
    };

    //channel 3
    pwmCFG.channels[3 - 1].mode = PWM_OUTPUT_ACTIVE_HIGH;
    pwmStart(&PWMD2, &pwmCFG);

}

