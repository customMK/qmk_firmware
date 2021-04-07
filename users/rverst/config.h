/* Copyright 2021 Robert Verst <robert@verst.eu> @rverst
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

#ifdef RGBLIGHT_ENABLE
#    define RGBLIGHT_SLEEP
#    ifdef RGBLIGHT_ANIMATIONS
#        undef RGBLIGHT_ANIMATIONS
#    endif
#    define RGBLIGHT_SLEEP
#    define RGBLIGHT_EFFECT_BREATHING
#    define RGBLIGHT_EFFECT_RAINBOW_MOOD
#    define RGBLIGHT_EFFECT_RAINBOW_SWIRL
#    define RGBLIGHT_EFFECT_STATIC_GRADIENT
#    define RGBLIGHT_EFFECT_TWINKLE
#endif  // RGBLIGHT_ENABLE

#if defined(LOCKING_SUPPORT_ENABLE)
#    undef LOCKING_SUPPORT_ENABLE
#endif

#if defined(LOCKING_RESYNC_ENABLE)
#    undef LOCKING_RESYNC_ENABLE
#endif
