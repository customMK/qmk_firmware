AUDIO_DRIVER = pwm_hardware

QUANTUM_PAINTER_DRIVERS += st7735_spi
QUANTUM_PAINTER_DRIVERS += sh1106_i2c
QUANTUM_PAINTER_LVGL_INTEGRATION = yes

DEBOUNCE_TYPE = sym_eager_pk

CUSTOM_MATRIX = lite
CIE1931_CURVE = yes

VPATH += keyboards/custommk/evo70_r2/graphics \
         keyboards/custommk/evo70_r2/graphics/assets

SRC += matrix.c \
       evo70_r2_graphics.c \
       rtc.c \
       i2c_temperature.c \
       lcd_screen_analog_clock.c \
       lcd_screen_analog_updater.c \
       screen_datetime.c \
       screen_datetime_updater.c \
       screen_settings.c \
       screen_settings_updater.c \
       layer_settings.c \
       screen_bongocat.c \
       screen_custommk_logo.c \
       screen_custom_graphic.c \
       screen_bongocat_updater.c \
       evo70_r2_screens.c \
       watchface1.c \
       hourhand.c \
       minutehand.c \
       secondhand_2x_white.c \
       leatherbackground.c \
       moonphase.c \
       moon.c \
       display_control.c \
       lcd_backlight.c \
       evo70_r2_encoder.c \
       backlight_breathing.c \
       date_format.c \
       tseng_eva.c \
       public_pixel.c \
       bongo_idle1.c \
       bongo_idle3.c \
       bongo_idle4.c \
       bongo_idle5.c \
       bongo_tap1.c \
       bongo_tap2.c \
       bongo_prep.c \
       custommk_logo.c \
       beachview.c \
       overlay_panel.c
