# MCU name
MCU = STM32F411
BOARD = BONSAI_C4

# Bootloader selection
BOOTLOADER = stm32-dfu

#RGBLIGHT_ENABLE = yes        # Enable keyboard RGB underglow
#RGBLIGHT_DRIVER = WS2812
#WS2812_DRIVER = pwm


EEPROM_DRIVER = spi

SPLIT_KEYBOARD = yes
DEFAULT_FOLDER = custommk/sofle_bonsai_c4/rev1
SWAP_HANDS_ENABLE = yes

SERIAL_DRIVER = usart