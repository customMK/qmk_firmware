/* Copyright 2021 Nathan Spears
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#define TAPPING_TOGGLE 2
#define TAPPING_TERM 200

// With 8k FRAM, max out dynamic keymap layers and macros
// 4x17 matrix (136 bytes) and three encoders (12 bytes) consume 148 bytes per layer
// 32 layers consumes 4736 bytes
#define DYNAMIC_KEYMAP_LAYER_COUNT 32

// Most of the remaining space can be used for macros
// QMK Macro keycode range allows up to 128 macros
#define DYNAMIC_KEYMAP_MACRO_COUNT 128
