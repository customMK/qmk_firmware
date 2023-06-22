// Copyright 2023 David Hoelscher (@customMK)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "qp_internal.h"
#include "qp_comms.h"
#include "qp_oled_panel.h"
#include "qp_ssd1306.h"
#include "qp_ssd1306_opcodes.h"
#include "qp_surface.h"
#include "qp_surface_internal.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Driver storage
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef struct ssd1306_device_t {
    oled_panel_painter_device_t oled;

    uint8_t framebuffer[SURFACE_REQUIRED_BUFFER_BYTE_SIZE(128, 64, 1)];
} ssd1306_device_t;

static ssd1306_device_t ssd1306_drivers[SSD1306_NUM_DEVICES] = {0};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Quantum Painter API implementations

// Initialisation
__attribute__((weak)) bool qp_ssd1306_init(painter_device_t device, painter_rotation_t rotation) {
    ssd1306_device_t *driver = (ssd1306_device_t *)device;

    // Change the surface geometry based on the panel rotation
    if (rotation == QP_ROTATION_90 || rotation == QP_ROTATION_270) {
        driver->oled.surface.base.panel_width  = driver->oled.base.panel_height;
        driver->oled.surface.base.panel_height = driver->oled.base.panel_width;
    } else {
        driver->oled.surface.base.panel_width  = driver->oled.base.panel_width;
        driver->oled.surface.base.panel_height = driver->oled.base.panel_height;
    }

    // Init the internal surface
    if (!qp_init(&driver->oled.surface.base, QP_ROTATION_0)) {
        qp_dprintf("Failed to init internal surface in qp_ssd1306_init\n");
        return false;
    }
    
    // clang-format off
    uint8_t ssd1306_init_sequence[] = {
        // Command,                 Delay,  N, Data[N]
        SSD1306_SET_MUX_RATIO,           0,  1, 0x3F,
        SSD1306_DISPLAY_OFFSET,          0,  1, 0x00,
        SSD1306_DISPLAY_START_LINE,      0,  0,
        SSD1306_SET_SEGMENT_REMAP_INV,   0,  0,
        SSD1306_COM_SCAN_DIR_DEC,        0,  0,
        SSD1306_COM_PADS_HW_CFG,         0,  1, 0x12,
        SSD1306_SET_CONTRAST,            0,  1, 0x7F,
        SSD1306_ALL_ON_RESUME,           0,  0,
        SSD1306_NON_INVERTING_DISPLAY,   0,  0,
        SSD1306_SET_OSC_DIVFREQ,         0,  1, 0x80,
        SSD1306_SET_CHARGE_PUMP,         0,  1, 0x14,
        SSD1306_DISPLAY_ON,              0,  0
    };
    // clang-format on

    // For 128x32 display, change SSD1306_COM_PADS_HW_CFG data byte from alternating (0x12) to sequential (0x02)
    if (driver->oled.base.panel_width == 128 && driver->oled.base.panel_height == 32) {
        ssd1306_init_sequence[20] = 0x02;
    }

    // If the display height is smaller than the maximum of 64 pixels, change SSD1306_SET_MUX_RATIO data byte to 31 to reduce the multiplexer ratio
    if (driver->oled.base.panel_height != 64) {
        ssd1306_init_sequence[3] = driver->oled.base.panel_height - 1;
    }

    qp_comms_bulk_command_sequence(device, ssd1306_init_sequence, sizeof(ssd1306_init_sequence));
    return true;
}

// Screen flush
bool qp_ssd1306_flush(painter_device_t device) {
    ssd1306_device_t *driver = (ssd1306_device_t *)device;

    if (!driver->oled.surface.dirty.is_dirty) {
        return true;
    }

    switch (driver->oled.base.rotation) {
        default:
        case QP_ROTATION_0:
            qp_oled_panel_page_column_flush_rot0(device, &driver->oled.surface.dirty, driver->framebuffer);
            break;
        case QP_ROTATION_90:
            qp_oled_panel_page_column_flush_rot90(device, &driver->oled.surface.dirty, driver->framebuffer);
            break;
        case QP_ROTATION_180:
            qp_oled_panel_page_column_flush_rot180(device, &driver->oled.surface.dirty, driver->framebuffer);
            break;
        case QP_ROTATION_270:
            qp_oled_panel_page_column_flush_rot270(device, &driver->oled.surface.dirty, driver->framebuffer);
            break;
    }

    // Clear the dirty area
    qp_flush(&driver->oled.surface);

    return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Driver vtable
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const oled_panel_painter_driver_vtable_t ssd1306_driver_vtable = {
    .base =
        {
            .init            = qp_ssd1306_init,
            .power           = qp_oled_panel_power,
            .clear           = qp_oled_panel_clear,
            .flush           = qp_ssd1306_flush,
            .pixdata         = qp_oled_panel_passthru_pixdata,
            .viewport        = qp_oled_panel_passthru_viewport,
            .palette_convert = qp_oled_panel_passthru_palette_convert,
            .append_pixels   = qp_oled_panel_passthru_append_pixels,
            .append_pixdata  = qp_oled_panel_passthru_append_pixdata,
        },
    .opcodes =
        {
            .display_on     = SSD1306_DISPLAY_ON,
            .display_off    = SSD1306_DISPLAY_OFF,
            .set_page       = SSD1306_PAGE_ADDR,
            .set_column_lsb = SSD1306_SETCOLUMN_LSB,
            .set_column_msb = SSD1306_SETCOLUMN_MSB,
        },
};

#ifdef QUANTUM_PAINTER_SSD1306_SPI_ENABLE
// Factory function for creating a handle to the SH1106 device
painter_device_t qp_ssd1306_make_spi_device(uint16_t panel_width, uint16_t panel_height, pin_t chip_select_pin, pin_t dc_pin, pin_t reset_pin, uint16_t spi_divisor, int spi_mode) {
    for (uint32_t i = 0; i < SSD1306_NUM_DEVICES; ++i) {
        ssd1306_device_t *driver = &ssd1306_drivers[i];
        if (!driver->oled.base.driver_vtable) {
            painter_device_t surface = qp_make_mono1bpp_surface_advanced(&driver->oled.surface, 1, panel_width, panel_height, driver->framebuffer);
            if (!surface) {
                return NULL;
            }

            // Setup the OLED device
            driver->oled.base.driver_vtable         = (const painter_driver_vtable_t *)&ssd1306_driver_vtable;
            driver->oled.base.comms_vtable          = (const painter_comms_vtable_t *)&spi_comms_with_dc_vtable;
            driver->oled.base.native_bits_per_pixel = 1; // 1bpp mono
            driver->oled.base.panel_width           = panel_width;
            driver->oled.base.panel_height          = panel_height;
            driver->oled.base.rotation              = QP_ROTATION_0;
            driver->oled.base.offset_x              = 0;
            driver->oled.base.offset_y              = 0;

            // SPI and other pin configuration
            driver->oled.base.comms_config                                   = &driver->oled.spi_dc_reset_config;
            driver->oled.spi_dc_reset_config.spi_config.chip_select_pin      = chip_select_pin;
            driver->oled.spi_dc_reset_config.spi_config.divisor              = spi_divisor;
            driver->oled.spi_dc_reset_config.spi_config.lsb_first            = false;
            driver->oled.spi_dc_reset_config.spi_config.mode                 = spi_mode;
            driver->oled.spi_dc_reset_config.dc_pin                          = dc_pin;
            driver->oled.spi_dc_reset_config.reset_pin                       = reset_pin;
            driver->oled.spi_dc_reset_config.command_params_uses_command_pin = true;

            if (!qp_internal_register_device((painter_device_t)driver)) {
                memset(driver, 0, sizeof(ssd1306_device_t));
                return NULL;
            }

            return (painter_device_t)driver;
        }
    }
    return NULL;
}

#endif // QUANTUM_PAINTER_SSD1306_SPI_ENABLE

#ifdef QUANTUM_PAINTER_SSD1306_I2C_ENABLE
// Factory function for creating a handle to the SH1106 device
painter_device_t qp_ssd1306_make_i2c_device(uint16_t panel_width, uint16_t panel_height, uint8_t i2c_address) {
    for (uint32_t i = 0; i < SSD1306_NUM_DEVICES; ++i) {
        ssd1306_device_t *driver = &ssd1306_drivers[i];
        if (!driver->oled.base.driver_vtable) {
            // Instantiate the surface, intentional swap of width/high due to transpose
            painter_device_t surface = qp_make_mono1bpp_surface_advanced(&driver->oled.surface, 1, panel_width, panel_height, driver->framebuffer);
            if (!surface) {
                return NULL;
            }

            // Setup the OLED device
            driver->oled.base.driver_vtable         = (const painter_driver_vtable_t *)&ssd1306_driver_vtable;
            driver->oled.base.comms_vtable          = (const painter_comms_vtable_t *)&i2c_comms_cmddata_vtable;
            driver->oled.base.native_bits_per_pixel = 1; // 1bpp mono
            driver->oled.base.panel_width           = panel_width;
            driver->oled.base.panel_height          = panel_height;
            driver->oled.base.rotation              = QP_ROTATION_0;
            driver->oled.base.offset_x              = 0;
            driver->oled.base.offset_y              = 0;

            // I2C configuration
            driver->oled.base.comms_config       = &driver->oled.i2c_config;
            driver->oled.i2c_config.chip_address = i2c_address;

            if (!qp_internal_register_device((painter_device_t)driver)) {
                memset(driver, 0, sizeof(ssd1306_device_t));
                return NULL;
            }

            return (painter_device_t)driver;
        }
    }
    return NULL;
}

#endif // QUANTUM_PAINTER_SSD1306_SPI_ENABLE
