#pragma once

/* USB Device descriptor parameter */
#define VENDOR_ID       0xFC32
#define PRODUCT_ID      0x0287
#define DEVICE_VER      0x0001
#define MANUFACTURER    customMK
#define PRODUCT         Sofle


/* key matrix size */
// Rows are doubled-up
#define MATRIX_ROWS 10
#define MATRIX_COLS 6

// wiring of each half
#define MATRIX_ROW_PINS { B8, A3, B10, A8, B0 }
#define MATRIX_COL_PINS { B1, B15, B14, B13, A1, A5 }
#define DIODE_DIRECTION COL2ROW

#define TAPPING_TERM 100
#define DEBOUNCE 5

/* encoder support */
#define ENCODERS_PAD_A { A6 }
#define ENCODERS_PAD_B { A7 }
#define ENCODERS_PAD_A_RIGHT { A7 }
#define ENCODERS_PAD_B_RIGHT { A6 }
#define ENCODER_RESOLUTION 2

#define TAP_CODE_DELAY 10

/* communication between sides */
#define USE_SERIAL
//#define SERIAL_USE_MULTI_TRANSACTION
#define SOFT_SERIAL_PIN A15
#define SELECT_SOFT_SERIAL_SPEED 1
#define SERIAL_USART_DRIVER SD1
#define SERIAL_USART_TX_PAL_MODE 7
#define SERIAL_USART_TIMEOUT 20