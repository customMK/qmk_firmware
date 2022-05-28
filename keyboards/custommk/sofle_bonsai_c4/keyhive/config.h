/* Copyright 2022 customMK
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

#pragma once

#include "config_common.h"

// For boards using Bonsai C4 as a reference design, the VBUS sense pin A9
// can be used for other purposes instead (e.g. the switch matrix). If A9
// is not used for VBUS sensing, uncomment the line below. Most keyboards
// using Bonsai C4 itself should leave the line below commented out.


// USB Device descriptor parameter
#define VENDOR_ID    0xFC32
#define PRODUCT_ID   0x1287
#define DEVICE_VER   0x0002
#define MANUFACTURER customMK
#define PRODUCT      Sofle


//
// #define BOARD_OTG_NOVBUSSENS 1


/* example switch matrix */
#define MATRIX_ROWS 10
#define MATRIX_COLS 7

#define MATRIX_ROW_PINS       { B8, A3, B10, A8, B0 }
#define MATRIX_COL_PINS       { B1, B15, B14, B13, A1, A5, A4 }  //A4 is a virtual pin for encoder support in VIA
#define MATRIX_ROW_PINS_RIGHT { B8, A3, B10, A8, B0 }
#define MATRIX_COL_PINS_RIGHT { A5, A1, B13, B14, B15, B1, A4 } // A virtual pin is needed for the encoder key matrix in via.

// Communication between sides
#define SOFT_SERIAL_PIN A15


#define OLED_UPDATE_INTERVAL 66

#ifdef RGBLIGHT_ENABLE
/* example code for WS2812-style underglow */
#    define RGB_DI_PIN A10
#    define RGBLED_NUM 74
#    define RGBLED_SPLIT {37,37}
#    define RGBLIGHT_LIMIT_VAL 100 // LED Brightness, high power draw may exceed the USB limitations of 0.6A and cause a crash.
#    define RGBLIGHT_HUE_STEP  10
#    define RGBLIGHT_SAT_STEP  17
#    define RGBLIGHT_VAL_STEP  17
//#    define RGBLIGHT_LAYERS //Enable layer light indicators. Not required as updates are done in layer_state_set_user and led_update_user (+588).
#    define RGBLIGHT_SLEEP //Turn off LEDs when computer sleeping (+72)

#    define WS2812_PWM_DRIVER PWMD1
#    define WS2812_PWM_CHANNEL 3
#    define WS2812_PWM_PAL_MODE 1
#    define WS2812_DMA_STREAM STM32_DMA2_STREAM5
#    define WS2812_DMA_CHANNEL 6

//RGB LED Conversion macro from physical array to electric array (+146). This results in better looking animated effects.
//First section is the LED matrix, second section is the electrical wiring order, and the third section is the desired mapping
#    define LED_LAYOUT( \
  L00,  L01,  L02,  L03,  L04,  L05,          L08,  L09,  L010, L011, L012, L013, \
  L10,      L12,      L14,                              L19,      L111,     L113, \
  L20,  L21,  L22,  L23,  L24,  L25,          L28,  L29,  L210, L211, L212, L213, \
  L30,  L31,  L32,  L33,  L34,  L35,          L38,  L39,  L310, L311, L312, L313, \
  L40,      L42,      L44,                              L49,      L411,     L413, \
  L50,  L51,  L52,  L53,  L54,  L55,          L58,  L59,  L510, L511, L512, L513, \
          L62,  L63,  L64,  L65,  L66,      L67,  L68,  L69,  L610, L611,         \
      L71,                  L76,                  L77,                  L712     )\
  { \
    L14,L12,L10,L40,L42,L44,L71,L76,L66,L65,L55,L35,L25,L05,L04,L24,L34,L54,L64,L63,L53,L33,L23,L03,L02,L22,L32,L52,L62,L51,L31,L21,L01,L00,L20,L30,L50,L19,L111,L113,L413,L411,L49,L712,L77,L67,L68,L58,L38,L28,L08,L09,L29,L39,L59,L69,L610,L510,L310,L210,L010,L011,L211,L311,L511,L611,L512,L312,L212,L012,L013,L213,L313,L513, \
  }
//RGB LED logical order map
#    define RGBLIGHT_LED_MAP LED_LAYOUT( \
  5,  6,  17, 18, 29, 30,     43, 44, 55, 56, 67, 68, \
  4,    16,   28,                     45,   57,   69, \
  3,  7,  15, 19, 27, 31,     42, 46, 54, 58, 66, 70, \
  2,  8,  14, 20, 26, 32,     41, 47, 53, 59, 65, 71, \
  1,    13,   25,                     48,   60,   72, \
  0,  9,  12, 21, 24, 33,     40, 49, 52, 61, 64, 73, \
      11, 22, 23, 34, 35,   38, 39, 50, 51, 62,       \
      10,       36,              37,       63        )

#endif



/* example code for encoder */
#define ENCODERS_PAD_A { A6 }
#define ENCODERS_PAD_B { A7 }
#define ENCODERS_PAD_A_RIGHT { A7 }
#define ENCODERS_PAD_B_RIGHT { A6 }
#define ENCODER_RESOLUTION { 2, 2 }

#define TAP_CODE_DELAY  10

