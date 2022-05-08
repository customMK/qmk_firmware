# Bonsai C4 Template

This is a template for some basic settings for Bonsai C4. It demonstrates configuration and use of SPI FRAM/EEPROM, SPI Flash, PWM of LEDs, and control of WS2812-style RGB LEDs

![Bonsai C4](https://cdn.shopify.com/s/files/1/0508/2152/9796/products/Bonsai_C4_compact_edition_1024x1024@2x.png?v=1645838618)

* Keyboard Maintainer: [customMK](https://github.com/customMK)
* Hardware Supported: Bonsai C4
* Hardware Availability: [customMK](https://shop.custommk.com/products/bonsai-c4-microcontroller-board)

Make example for this keyboard (after setting up your build environment):

    make custommk/bonsai_c4_template:default

Flashing example for this keyboard:

    make custommk/bonsai_c4_template:default:flash

Bonsai C4 has and STM32 USB dfu bootloader preinstalled. To enter the bootloader, run the flashing command above, and then either plug in the USB connection while holding the top-left key, or alternatively, plug in the USB connection and then press the reset button on the PCB

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
