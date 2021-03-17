# Genesis

![CMK65]
![CMK65 PCB]

CMK65 is a 65% keyboard designed and produced by customMK. 

* Keyboard Maintainer: [customMK](https://github.com/customMK)
* Hardware Supported: CMK65
* Hardware Availability: [customMK](https://shop.custommk.com/products/cmk65)

Make example for this keyboard (after setting up your build environment):

    make custommk/cmk65:default

Flashing example for this keyboard:

    make custommk/cmk65:default:flash

CMK65 has qmk-dfu bootloader preinstalled. To enter the bootloader, run the flashing command above, and then either plug in the USB connection while holding the top-left key, or alternatively, plug in the USB connection and then press the reset button on the PCB

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
