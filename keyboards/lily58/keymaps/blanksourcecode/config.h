/*
This is the c configuration file for the keymap

Copyright 2012 Jun Wako <wakojun@gmail.com>
Copyright 2015 Jack Humbert

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#define USE_SERIAL
#define MASTER_LEFT

#define SSD1306OLED

#undef RGBLED_NUM
#define RGBLIGHT_ANIMATIONS
#define RGBLED_NUM 12
#define RGBLIGHT_LIMIT_VAL 120
#define RGBLIGHT_HUE_STEP 8
#define RGBLIGHT_SAT_STEP 8
#define RGBLIGHT_VAL_STEP 8

#undef TAPPING_TERM
#define TAPPING_TERM 200
#define TAPPING_TOGGLE 2

#define PERMISSIVE_HOLD
#define IGNORE_MOD_TAP_INTERRUPT

#define NUMBER_OF_ENCODERS 1
#define ENCODERS_PAD_A { F5 }
#define ENCODERS_PAD_B { F4 }

#define LAYOUT_kc( \
  L00, L01, L02, L03, L04, L05,           R00, R01, R02, R03, R04, R05, \
  L10, L11, L12, L13, L14, L15,           R10, R11, R12, R13, R14, R15, \
  L20, L21, L22, L23, L24, L25,           R20, R21, R22, R23, R24, R25, \
  L26, L27, L28, L29, L30, L31, L32, R26, R27, R28, R29, R30, R31, R32, \
                 L33, L34, L35, L36, R33, R34, R35, R36 \
  ) \
  LAYOUT( \
    KC_##L00, KC_##L01, KC_##L02, KC_##L03, KC_##L04, KC_##L05,                     KC_##R00, KC_##R01, KC_##R02, KC_##R03, KC_##R04, KC_##R05, \
    KC_##L10, KC_##L11, KC_##L12, KC_##L13, KC_##L14, KC_##L15,                     KC_##R10, KC_##R11, KC_##R12, KC_##R13, KC_##R14, KC_##R15, \
    KC_##L20, KC_##L21, KC_##L22, KC_##L23, KC_##L24, KC_##L25,                     KC_##R20, KC_##R21, KC_##R22, KC_##R23, KC_##R24, KC_##R25, \
    KC_##L26, KC_##L27, KC_##L28, KC_##L29, KC_##L30, KC_##L31, KC_##L32, KC_##R26, KC_##R27, KC_##R28, KC_##R29, KC_##R30, KC_##R31, KC_##R32, \
                                  KC_##L33, KC_##L34, KC_##L35, KC_##L36, KC_##R33, KC_##R34, KC_##R35, KC_##R36 \
  )
