/**
 * Copyright 2022 Charly Delay <charly@codesink.dev> (@0xcharly)
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
#include QMK_KEYBOARD_H

enum charybdis_keymap_layers {
    LAYER_BASE = 0,
    LAYER_LOWER,
    LAYER_RAISE,
    LAYER_POINTER,
    LAYER_QWERTY,
    LAYER_WIN_MGR,
};

/** \brief Automatically enable sniping-mode on the pointer layer. */
#define CHARYBDIS_AUTO_SNIPING_ON_LAYER LAYER_POINTER

#ifdef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE
static uint16_t auto_pointer_layer_timer = 0;

#    ifndef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS
#        define CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS 1000
#    endif // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS

#    ifndef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD
#        define CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD 8
#    endif // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD
#endif     // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE

#define LOWER MO(LAYER_LOWER)
#define RAISE MO(LAYER_RAISE)
#define QWERTY MO(LAYER_QWERTY)
#define PT_Z LT(LAYER_POINTER, KC_Z)
#define PT_SLSH LT(LAYER_POINTER, KC_SLSH)
#define SF_A LGUI_T(KC_A)
#define SF_R LCTL_T(KC_R)
#define SF_S LALT_T(KC_S)
#define SF_T LSFT_T(KC_T)
#define SF_D LT(LAYER_WIN_MGR, KC_D)
#define SF_N RSFT_T(KC_N)
#define SF_E RALT_T(KC_E)
#define SF_I RCTL_T(KC_I)
#define SF_O RGUI_T(KC_O)
#define WMGR(X) ACTION_TAP_DANCE_DOUBLE(G(KC_##X), LSG(KC_##X))

enum tap_dances {
    TD_TAB,
    TD_LPRN,
    TD_RPRN,
    TD_W0,
    TD_W1,
    TD_W2,
    TD_W3,
    TD_W4,
    TD_W5,
    TD_W6,
    TD_W7,
    TD_W8,
    TD_W9,
    TD_WK,
    TD_WJ,
    TD_WH,
    TD_WL,
};

tap_dance_action_t tap_dance_actions[] = {
    [TD_TAB]  = ACTION_TAP_DANCE_DOUBLE(KC_TAB, KC_CAPS),
    [TD_LPRN] = ACTION_TAP_DANCE_DOUBLE(KC_LPRN, KC_LABK),
    [TD_RPRN] = ACTION_TAP_DANCE_DOUBLE(KC_RPRN, KC_RABK),
    [TD_W0]   = WMGR(0), // go to workspace or send client to it
    [TD_W1]   = WMGR(1), // go to workspace or send client to it
    [TD_W2]   = WMGR(2), // go to workspace or send client to it
    [TD_W3]   = WMGR(3), // go to workspace or send client to it
    [TD_W4]   = WMGR(4), // go to workspace or send client to it
    [TD_W5]   = WMGR(5), // go to workspace or send client to it
    [TD_W6]   = WMGR(6), // go to workspace or send client to it
    [TD_W7]   = WMGR(7), // go to workspace or send client to it
    [TD_W8]   = WMGR(8), // go to workspace or send client to it
    [TD_W9]   = WMGR(9), // go to workspace or send client to it
    [TD_WK]   = WMGR(K), // navigate to client or move it
    [TD_WH]   = WMGR(H), // navigate to client or move it
    [TD_WJ]   = WMGR(J), // navigate to client or move it
    [TD_WL]   = WMGR(L), // navigate to client or move it
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [LAYER_BASE] = LAYOUT(
  // ╭──────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────╮
       TD_TAB,     KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,       KC_J,    KC_L,    KC_U,    KC_Y, KC_SCLN, KC_BSPC,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       KC_ESC,     SF_A,    SF_R,    SF_S,    SF_T,    SF_D,       KC_H,    SF_N,    SF_E,    SF_I,    SF_O, KC_ENT,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       TD_LPRN,    PT_Z,    KC_X,    KC_C,    KC_V,    KC_B,       KC_K,    KC_M, KC_COMM,  KC_DOT, PT_SLSH, TD_RPRN,
  // ╰──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────╯
                                  QWERTY,   KC_SPC,   LOWER,      RAISE,  KC_ENT
  //                            ╰───────────────────────────╯ ╰──────────────────╯
  ),

  [LAYER_LOWER] = LAYOUT(
  // ╭──────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────╮
       KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,    KC_LBRC,    KC_7,    KC_8,    KC_9, KC_0,    KC_RBRC,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       XXXXXXX, KC_LGUI, KC_LCTL, KC_LALT, KC_LSFT, XXXXXXX,    KC_PPLS,    KC_4,    KC_5,    KC_6, KC_PMNS, KC_PEQL,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       XXXXXXX, KC_CIRC, KC_AMPR, KC_ASTR, KC_UNDS, KC_QUOT,    KC_PAST,    KC_1,    KC_2,    KC_3, KC_PSLS, KC_PDOT,
  // ╰──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────╯
                                  XXXXXXX, XXXXXXX, _______,    XXXXXXX, _______
  //                            ╰───────────────────────────╯ ╰──────────────────╯
  ),

  [LAYER_RAISE] = LAYOUT(
  // ╭──────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────╮
       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, KC_VOLU, KC_MUTE, KC_VOLD, XXXXXXX, XXXXXXX,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       XXXXXXX, KC_LEFT,   KC_UP, KC_DOWN, KC_RGHT, XXXXXXX,    XXXXXXX, KC_RSFT, KC_RALT, KC_RCTL, KC_RGUI, XXXXXXX,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       XXXXXXX, KC_HOME, KC_PGUP, KC_PGDN,  KC_END, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  // ╰──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────╯
                                  _______, _______, XXXXXXX,    _______, XXXXXXX
  //                            ╰───────────────────────────╯ ╰──────────────────╯
  ),

  [LAYER_POINTER] = LAYOUT(
  // ╭──────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────╮
       QK_BOOT,  EE_CLR, XXXXXXX, XXXXXXX, DPI_MOD, S_D_MOD,    S_D_MOD, DPI_MOD, XXXXXXX, XXXXXXX,  EE_CLR, QK_BOOT,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       XXXXXXX, KC_LGUI, KC_LCTL, KC_LALT, KC_LSFT, XXXXXXX,    XXXXXXX, KC_RSFT, KC_RALT, KC_RCTL, KC_RGUI, KC_MUTE,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       XXXXXXX, _______, DRGSCRL, SNIPING, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, SNIPING, DRGSCRL, _______, XXXXXXX,
  // ╰──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────╯
                                  KC_BTN2, KC_BTN1, KC_BTN3,    KC_BTN3, KC_BTN1
  //                            ╰───────────────────────────╯ ╰──────────────────╯
  ),

  [LAYER_QWERTY] = LAYOUT(
  // ╭──────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────╮
       _______,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,       KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, _______,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       _______,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,       KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, _______,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       _______,    PT_Z,    KC_X,    KC_C,    KC_V,    KC_B,       KC_N,    KC_M, KC_COMM,  KC_DOT, PT_SLSH, _______,
  // ╰──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────╯
                                  _______, _______, _______,    _______,  _______
  //                            ╰───────────────────────────╯ ╰──────────────────╯
  ),

  [LAYER_WIN_MGR] = LAYOUT(
  // ╭──────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────╮
       _______,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    _______,   TD_W7,   TD_W8,   TD_W9,  TD_W0, _______,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       _______,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,      TD_WK,   TD_W4,   TD_W5,   TD_W6,  TD_WH, G(KC_ENT),
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       _______,    PT_Z,    KC_X,    KC_C,    KC_V,    KC_B,      TD_WJ,   TD_W1,   TD_W2,   TD_W3,  TD_WL, _______,
  // ╰──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────╯
                                  _______, _______, G(KC_R),    _______,  _______
  //                            ╰───────────────────────────╯ ╰──────────────────╯
  ),
};
// clang-format on

#ifdef POINTING_DEVICE_ENABLE
#    ifdef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE
report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
    if (abs(mouse_report.x) > CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD || abs(mouse_report.y) > CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD) {
        if (auto_pointer_layer_timer == 0) {
            layer_on(LAYER_POINTER);
#        ifdef RGB_MATRIX_ENABLE
            rgb_matrix_mode_noeeprom(RGB_MATRIX_NONE);
            rgb_matrix_sethsv_noeeprom(HSV_GREEN);
#        endif // RGB_MATRIX_ENABLE
        }
        auto_pointer_layer_timer = timer_read();
    }
    return mouse_report;
}

void matrix_scan_user(void) {
    if (auto_pointer_layer_timer != 0 && TIMER_DIFF_16(timer_read(), auto_pointer_layer_timer) >= CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS) {
        auto_pointer_layer_timer = 0;
        layer_off(LAYER_POINTER);
#        ifdef RGB_MATRIX_ENABLE
        rgb_matrix_mode_noeeprom(RGB_MATRIX_DEFAULT_MODE);
#        endif // RGB_MATRIX_ENABLE
    }
}
#    endif // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE

#    ifdef CHARYBDIS_AUTO_SNIPING_ON_LAYER
layer_state_t layer_state_set_user(layer_state_t state) {
    charybdis_set_pointer_sniping_enabled(layer_state_cmp(state, CHARYBDIS_AUTO_SNIPING_ON_LAYER));
    return state;
}
#    endif // CHARYBDIS_AUTO_SNIPING_ON_LAYER
#endif     // POINTING_DEVICE_ENABLE

#ifdef RGB_MATRIX_ENABLE
// Forward-declare this helper function since it is defined in rgb_matrix.c.
void rgb_matrix_update_pwm_buffers(void);
#endif
