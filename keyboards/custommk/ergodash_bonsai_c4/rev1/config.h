/*
Copyright 2012 Jun Wako <wakojun@gmail.com>
Copyright 2015 Jack Humbert
Copyright 2022 customMK

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0x6060
#define DEVICE_VER      0x0100
#define MANUFACTURER    Omkbd
#define PRODUCT         ErgoDash


/* key matrix size */
// Rows are doubled-up
#define MATRIX_ROWS 10
#define MATRIX_COLS 7

// wiring of each half
#define MATRIX_ROW_PINS { A4, A3, B10, A8, B0 }
#define MATRIX_COL_PINS { A7, A6, A5, A1, B13, B14, B5 }
// #define MATRIX_COL_PINS { B5, B14, B13, A1, A5, A6, A7 } //uncomment this line and comment line above if you need to reverse left-to-right key order

#define DIODE_DIRECTION COL2ROW

/* define tapping term */
#define TAPPING_TERM 120

/* define if matrix has ghost */
//#define MATRIX_HAS_GHOST

#define AUDIO_PIN B8

/* number of backlight levels */
#ifdef BACKLIGHT_ENABLE
  #define BACKLIGHT_PIN B1
  #define BACKLIGHT_LIMIT_VAL 255
  #define BACKLIGHT_LEVELS 7
  #define BACKLIGHT_PWM_DRIVER PWMD3
  #define BACKLIGHT_PWM_CHANNEL 4
  #define BACKLIGHT_PAL_MODE 2
//  #define BACKLIGHT_BREATHING
//  #define BREATHING_PERIOD 4
#endif

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

/* ws2812 RGB LED */
#define RGB_DI_PIN A10
#define WS2812_PWM_CHANNEL 3
#define WS2812_PWM_PAL_MODE 1
#define WS2812_DMA_STREAM STM32_DMA2_STREAM5
#define WS2812_DMA_CHANNEL 6
#define RGBLIGHT_ANIMATIONS
#define RGBLED_NUM 24
#define RGBLIGHT_SPLIT
#define RGBLED_SPLIT { 12, 12 }    // Number of LEDs

// The LEDs on the slave half go in reverse order
#define RGBLIGHT_LED_MAP { 0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, \
                          23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12}

#define TAP_CODE_DELAY 10

/* communication between sides */
#define USE_SERIAL
//#define SERIAL_USE_MULTI_TRANSACTION
#define SOFT_SERIAL_PIN B6
#define SELECT_SOFT_SERIAL_SPEED 1
#define SERIAL_USART_DRIVER SD1
#define SERIAL_USART_TX_PAL_MODE 7
#define SERIAL_USART_TIMEOUT 20