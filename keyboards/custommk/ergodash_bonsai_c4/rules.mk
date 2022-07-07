# MCU name
MCU = STM32F411
BOARD = BONSAI_C4

# Bootloader selection
BOOTLOADER = stm32-dfu

# Build Options
#   change yes to no to disable
#
BOOTMAGIC_ENABLE = no       # Enable Bootmagic Lite
MOUSEKEY_ENABLE = no       # Mouse keys
EXTRAKEY_ENABLE = yes       # Audio control and System control
CONSOLE_ENABLE = no         # Console for debug
COMMAND_ENABLE = no        # Commands for debug and configuration
NKRO_ENABLE = no            # Enable N-Key Rollover
BACKLIGHT_ENABLE = yes      # Enable keyboard backlight functionality
RGBLIGHT_ENABLE = yes        # Enable keyboard RGB underglow
RGBLIGHT_DRIVER = WS2812
WS2812_DRIVER = pwm


EEPROM_DRIVER = spi

SPLIT_KEYBOARD = yes
DEFAULT_FOLDER = custommk/ergodash_bonsai_c4/rev1

SERIAL_DRIVER = usart