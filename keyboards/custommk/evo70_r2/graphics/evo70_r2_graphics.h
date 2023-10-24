#include QMK_KEYBOARD_H
#include <hal.h>
#include <string.h>
#include <ctype.h>
#include <printf.h>
#include "qp.h"


painter_device_t display;

bool oled_exists(void);

//----------------------------------------------------------
// UI Initialisation
void keyboard_post_init_display(void);

void display_housekeeping_task(void);