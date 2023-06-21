// Copyright 2023 customMK
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

// With 1k EEPROM, calculate out dynamic keymap layers and macros
// 4x10 matrix = 80 bytes bytes per layer
// 8 layers consumes 640 bytes
#define DYNAMIC_KEYMAP_LAYER_COUNT 8

// Most of the remaining space can be used for macros
// QMK Macro keycode range allows up to 128 macros
#define DYNAMIC_KEYMAP_MACRO_COUNT 128
