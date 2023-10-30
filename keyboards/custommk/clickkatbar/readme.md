# ClickKat Bar

The ClickKat Bar is an ortho-layout drop-in replacement PCB for the CandyBar by TheKey.Company.

* Keyboard Maintainer: [customMK](https://github.com/customMK)
* Hardware Supported: ClickKat Bar
* Hardware Availability: [customMK](https://www.custommk.com)

Make example for this keyboard (after setting up your build environment):

    make custommk/clickkatbar:default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (the key in the top left corner) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
