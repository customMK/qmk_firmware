# MCU name
MCU = STM32F411
BOARD = BONSAI_C4

# Bootloader selection
BOOTLOADER = stm32-dfu

# Build Options
#   change yes to no to disable
#
BOOTMAGIC_ENABLE = yes     # Virtual DIP switch configuration
MOUSEKEY_ENABLE = no       # Mouse keys
EXTRAKEY_ENABLE = no       # Audio control and System control
CONSOLE_ENABLE = yes        # Console for debug
DEBUG_FLASH_SPI_OUTPUT = yes
COMMAND_ENABLE = yes         # Commands for debug and configuration
# Do not enable SLEEP_LED_ENABLE. it uses the same timer as BACKLIGHT_ENABLE
SLEEP_LED_ENABLE = no       # Breathing sleep LED during USB suspend
# if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
NKRO_ENABLE = no           # USB Nkey Rollover

BACKLIGHT_ENABLE = yes       # Enable keyboard backlight functionality
BACKLIGHT_DRIVER = pwm

DEBUG_ENABLE = yes

RGBLIGHT_ENABLE = yes        # Enable keyboard RGB underglow
RGBLIGHT_DRIVER = WS2812
WS2812_DRIVER = pwm


AUDIO_ENABLE = no           # Audio output
ENCODER_ENABLE = yes
#OLED_ENABLE = yes
#OLED_DRIVER = SSD1306

EEPROM_DRIVER = spi