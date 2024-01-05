/*
Copyright 2022 @Yowkees
Copyright 2022 MURAOKA Taro (aka KoRoN, @kaoriya)

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

#include QMK_KEYBOARD_H

#include "quantum.h"

// see keycodes for https://github.com/qmk/qmk_firmware/blob/master/docs/keycodes.md
// and https://github.com/Yowkees/keyball/blob/main/qmk_firmware/keyboards/keyball/lib/keyball/keycodes.md
#define KBC_RST  0x7e00  // Keyball設定のリセット
#define KBC_SAVE 0x7e01  // 現在のKeyball設定をEEPROMに保存します
#define CPI_I100 0x7e02  // CPIを100増加させます(最大:12000)
#define CPI_D100 0x7e03  // CPIを100減少させます(最小:100)
#define CPI_I1K  0x7e04  // CPIを1000増加させます(最大:12000)
#define CPI_D1K  0x7e05  // CPIを1000減少させます(最小:100)
#define SCRL_TO  0x7e06  // タップごとにスクロールモードのON/OFFを切り替えます
#define SCRL_MO  0x7e07  // キーを押している間、スクロールモードになります
#define SCRL_DVI 0x7e08  // スクロール除数を１つ上げます(max D7 = 1/128)←最もスクロール遅い
#define SCRL_DVD 0x7e09  // スクロール除数を１つ下げます(min D0 = 1/1)←最もスクロール速い

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_universal(
    KC_EQUAL , KC_1    , KC_2    , KC_3    , KC_4         , KC_5         ,                                       KC_6         , KC_7  , KC_8    , KC_9   , KC_0    , KC_MINS          ,
    KC_GRAVE , KC_Q    , KC_W    , KC_E    , KC_R         , KC_T         ,                                       KC_Y         , KC_U  , KC_I    , KC_O   , KC_P    , KC_BSLS          ,
    KC_LALT  , KC_A    , KC_S    , KC_D    , KC_F         , KC_G         ,                                       KC_H         , KC_J  , KC_K    , KC_L   , KC_SCLN , LALT_T(KC_QUOTE) ,
    KC_LSFT  , KC_Z    , KC_X    , KC_C    , KC_V         , KC_B         , LCTL_T(KC_ESC) ,     LCTL_T(KC_ESC) , KC_N         , KC_M  , KC_COMM , KC_DOT , KC_SLSH , KC_LSFT          ,
    KC_LNG2  , KC_LGUI , KC_LBRC , KC_RBRC , LT(1,KC_ESC) , LT(2,KC_SPC) , LT(3,KC_TAB)   ,     KC_BSPC        , LT(2,KC_ENT) , KC_NO , KC_NO   , KC_NO  , KC_LGUI , KC_LNG1
  ),

  [1] = LAYOUT_universal(
    KC_NO   , KC_1  , KC_2 , KC_3 , KC_4    , KC_5   ,                         KC_NO  , KC_NO        , KC_NO     , KC_NO      , KC_NO      , KC_NO ,
    KC_NO   , KC_Q  , KC_W , KC_E , KC_NO   , KC_F3  ,                         KC_NO  , KC_LEFT      , KC_UP     , KC_RIGHT   , KC_NO      , KC_NO ,
    KC_LCTL , KC_A  , KC_S , KC_D , KC_F    , KC_F5  ,                         KC_NO  , KC_MS_BTN1   , KC_DOWN   , KC_MS_BTN2 , KC_MS_BTN3 , KC_NO ,
    KC_LSFT , KC_6  , KC_7 , KC_8 , KC_9    , KC_0   , KC_ESC  ,     KC_NO   , KC_F1  , LAG(KC_PSCR) , LAG(KC_G) , LAG(KC_R)  , LGUI(KC_G) , KC_NO ,
    TO(0)   , KC_NO , KC_Z , KC_B , KC_LCTL , KC_SPC , KC_LSFT ,     KC_BSPC , KC_ENT , KC_NO        , KC_NO     , KC_NO      , KC_NO      , KC_NO
  ),

  [2] = LAYOUT_universal(
    KC_NO   , KC_F1   , KC_F2 , KC_F3  , KC_F4 , KC_F5 ,                              KC_F6   , KC_F7   , KC_F8   , KC_F9   , KC_F10  , KC_F11  ,
    KC_NO   , KC_NO   , KC_7  , KC_8   , KC_9  , KC_NO ,                              KC_NO   , KC_LEFT , KC_UP   , KC_RGHT , KC_NO   , KC_F12  ,
    KC_LALT , KC_NO   , KC_4  , KC_5   , KC_6  , KC_NO ,                              KC_PGUP , KC_BTN1 , KC_DOWN , KC_BTN2 , KC_BTN3 , KC_LALT ,
    KC_LSFT , KC_NO   , KC_1  , KC_2   , KC_3  , KC_NO , KC_NO ,             KC_NO  , KC_PGDN , KC_HOME , KC_NO   , KC_END  , KC_NO   , KC_LSFT ,
    TO(0)   , KC_LGUI , KC_0  , KC_DOT , KC_NO , KC_NO , KC_NO ,             KC_DEL , KC_NO   , KC_NO   , KC_NO   , KC_NO   , KC_LGUI , KC_NO
  ),

  [3] = LAYOUT_universal(
    TO(1)   , KC_NO   , KC_NO   , KC_NO    , KC_NO    , KC_NO   ,                                 KC_NO    , KC_NO    , KC_NO , KC_NO , KC_NO   , KC_NO   ,
    KC_NO   , KC_NO   , KC_NO   , KC_NO    , KC_NO    , KC_NO   ,                                 KC_NO    , KC_NO    , KC_NO , KC_NO , KC_NO   , KC_NO   ,
    KC_LALT , KC_NO   , KC_NO   , KC_NO    , KC_NO    , KC_NO   ,                                 KC_NO    , KC_NO    , KC_NO , KC_NO , KC_NO   , KC_LALT ,
    KC_LSFT , KC_NO   , CPI_D1K , CPI_D100 , CPI_I100 , CPI_I1K , KBC_SAVE ,            KBC_RST , SCRL_DVI , SCRL_DVD , KC_NO , KC_NO , KC_NO   , KC_LSFT ,
    TO(0)   , KC_LGUI , KC_NO   , KC_NO    , KC_NO    , KC_NO   , KC_NO    ,            KC_NO   , KC_NO    , KC_NO    , KC_NO , KC_NO , KC_LGUI , KC_NO
  ),
};
// clang-format on

layer_state_t layer_state_set_user(layer_state_t state) {
    // Auto enable scroll mode when the highest layer is 3
    keyball_set_scroll_mode(get_highest_layer(state) == 3);
    return state;
}

#ifdef OLED_ENABLE

#    include "lib/oledkit/oledkit.h"

void oledkit_render_info_user(void) {
    keyball_oled_render_keyinfo();
    keyball_oled_render_ballinfo();
    keyball_oled_render_layerinfo();
}
#endif
