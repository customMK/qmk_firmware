#include QMK_KEYBOARD_H
#include <hal.h>
#include <string.h>
#include <ctype.h>
#include <printf.h>
#include "qp.h"
#include "i2c_master.h"
#include "evo70_r2.h"
#include "evo70_r2_graphics.h"
#include "evo70_r2_screens.h"
#include "lcd_screen_analog_clock.h"
#include "screen_settings.h"
#include "display_control.h"
#include "lcd_backlight.h"
#include "rtc.h"
#include "qp_lvgl.h"



#define MODS_SHIFT ((get_mods() | get_oneshot_mods()) & MOD_MASK_SHIFT)
#define MODS_CTRL ((get_mods() | get_oneshot_mods()) & MOD_MASK_CTRL)
#define MODS_ALT ((get_mods() | get_oneshot_mods()) & MOD_MASK_ALT)
#define MODS_GUI ((get_mods() | get_oneshot_mods()) & MOD_MASK_GUI)

extern user_config_t user_config;

static bool oled_found = true;

bool oled_exists(void) {
    return oled_found;
}

void toggle_state(void *obj, lv_state_t state, bool enabled) {
    if (enabled) {
        lv_obj_add_state(obj, state);
    } else {
        lv_obj_clear_state(obj, state);
    }
}

void toggle_hidden(void *obj, bool visible) {
    if (visible) {
        lv_obj_clear_flag(obj, LV_OBJ_FLAG_HIDDEN);
    } else {
        lv_obj_add_flag(obj, LV_OBJ_FLAG_HIDDEN);
    }
}

__attribute__((weak)) bool display_init_user(void) {
    return true;
}

__attribute__((weak)) void display_housekeeping_task(void) {
    display_management_task();
}

void oled_set_pixel(struct _lv_disp_drv_t *disp_drv, uint8_t *buf, lv_coord_t buf_w, lv_coord_t x, lv_coord_t y, lv_color_t color, lv_opa_t opa){
    uint16_t index = x/8 + y * (buf_w / 8);
    uint8_t data = buf[index];
    if (lv_color_to1(color)) {
        data |= (1 << (x % 8));
    } else {
        data &= ~(1 << (x % 8));
    }
    buf[index] = data;
}

void rounder_cb_mono(lv_disp_drv_t *disp_drv, lv_area_t *area) {
    area->x1 &= ~0x7;
    area->x2 |= 0x7;
}

//----------------------------------------------------------
// UI Initialisation
void keyboard_post_init_display(void) {
    oled_found = false;
    i2c_status_t i2c_status;

    //check the I2C bus for the address where the I2C display SSD1306 should be located
    i2c_init();
    i2c_status = i2c_ping_address((0x3C << 1), 500);
    if (i2c_status == I2C_STATUS_SUCCESS) {
        oled_found = true;
        display = qp_sh1106_make_i2c_device(128, 32, 0x3C);
        qp_init(display, QP_ROTATION_0);
    } else {
        oled_found = false;
        display = qp_st7735_make_spi_device(80, 160, LCD_CS_PIN, LCD_DC_PIN, LCD_RST_PIN, 4,3);
        qp_init(display, QP_ROTATION_90);
    }
    qp_power(display,true); //turn on immediately for the purposes of attaching lvgl


    qp_lvgl_attach(display);

    lv_disp_t  *lv_display = lv_disp_get_default();
    if (oled_exists()) {
        // If it's the OLED, update the driver to use rounder_cb and set_px_cb, which are needed for remapping/converting to monochrome OLED format
        lv_disp_drv_t *my_driver = lv_display->driver;
        my_driver->set_px_cb = oled_set_pixel;
        my_driver->rounder_cb = rounder_cb_mono;
        lv_disp_drv_update(lv_display, my_driver);
    }
    lv_theme_t *lv_theme   = lv_theme_default_init(lv_display, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_CYAN), true, LV_FONT_DEFAULT);

    lv_disp_set_theme(lv_display, lv_theme);


    if (user_config.display_on) {
        turn_display_on();
    } else {
        if (user_config.display_off_was_auto_timeout) {
            turn_display_on();  //if it was only off because of automatic timeout, then turn it back on upon powerup
        } else {
            turn_display_off();
        }
    }

    display_management_init();
}
