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
    LAYER_NUMBER,
    LAYER_NAVIG,
    LAYER_POINTER,
    LAYER_QWERTY,
    LAYER_WIN_MGR,
    LAYER_FN,
    LAYER_MEDIA,
    LAYER_WEB,
    LAYER_TOOLS,
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

enum tap_dances {
    DEL,
    TAB,
    LPRN,
    RPRN,
    SLSH,
    ENT,
    QUOT,
    PSRC,
    W0,
    W1,
    W2,
    W3,
    W4,
    W5,
    W6,
    W7,
    W8,
    W9,
    WK,
    WJ,
    WH,
    WL,
};

/** \brief Custom keycodes for axis-locked drag-scroll. */
enum samflores_keycodes {
    SCROLL_H_ONLY = SAFE_RANGE, // Hold: drag-scroll, horizontal axis only.
    SCROLL_V_ONLY,              // Hold: drag-scroll, vertical axis only.
};

/** \brief Which axis drag-scroll emits; set by the scroll keys. */
enum scroll_axis_mode {
    SCROLL_AXIS_BOTH,
    SCROLL_AXIS_H_ONLY,
    SCROLL_AXIS_V_ONLY,
};

#define WMGR(X) ACTION_TAP_DANCE_DOUBLE(G(KC_##X), LSG(KC_##X))

tap_dance_action_t tap_dance_actions[] = {
    [DEL]  = ACTION_TAP_DANCE_DOUBLE(KC_DEL, S(KC_DEL)),
    [TAB]  = ACTION_TAP_DANCE_DOUBLE(KC_TAB, KC_CAPS),
    [LPRN] = ACTION_TAP_DANCE_DOUBLE(KC_LPRN, KC_LABK),
    [RPRN] = ACTION_TAP_DANCE_DOUBLE(KC_RPRN, KC_RABK),
    [SLSH] = ACTION_TAP_DANCE_DOUBLE(KC_SLSH, KC_BSLS),
    [ENT]  = ACTION_TAP_DANCE_DOUBLE(KC_ENT, G(KC_ENT)),
    [QUOT] = ACTION_TAP_DANCE_DOUBLE(KC_QUOT, KC_DQT),
    [PSRC] = ACTION_TAP_DANCE_DOUBLE(KC_PSCR, S(KC_PSCR)),
    [W0]   = WMGR(0), // go to workspace or send client to it
    [W1]   = WMGR(1),
    [W2]   = WMGR(2),
    [W3]   = WMGR(3),
    [W4]   = WMGR(4),
    [W5]   = WMGR(5),
    [W6]   = WMGR(6),
    [W7]   = WMGR(7),
    [W8]   = WMGR(8),
    [W9]   = WMGR(9),
    [WK]   = WMGR(K), // focus on client or move it
    [WH]   = WMGR(H),
    [WJ]   = WMGR(J),
    [WL]   = WMGR(L),
};

#define NUMBER LT(LAYER_NUMBER, KC_ESC)
#define NAVIG LT(LAYER_NAVIG, KC_BSPC)
#define MEDIA LT(LAYER_MEDIA, KC_ENT)
#define SF_C LT(LAYER_POINTER, KC_C)
#define SF_COMM LT(LAYER_POINTER, KC_COMM)
#define SF_F LT(LAYER_FN, KC_F)
#define SF_A LGUI_T(KC_A)
#define SF_R LCTL_T(KC_R)
#define SF_S LALT_T(KC_S)
#define SF_T LSFT_T(KC_T)
#define QW_A LGUI_T(KC_A)
#define QW_S LCTL_T(KC_S)
#define QW_D LALT_T(KC_D)
#define QW_F LSFT_T(KC_F)
#define SF_V LT(LAYER_WIN_MGR, KC_V)
#define SF_N RSFT_T(KC_N)
#define SF_E RALT_T(KC_E)
#define SF_I RCTL_T(KC_I)
#define SF_O RGUI_T(KC_O)
#define QW_J RSFT_T(KC_J)
#define QW_K RALT_T(KC_K)
#define QW_L RCTL_T(KC_L)
#define QW_SCLN RGUI_T(KC_SCLN)
#define SF_QUTE RGUI(RCTL(KC_Q))
#define SF_FRFX RGUI(RCTL(KC_F))
#define SF_CHRM RGUI(RCTL(KC_C))
#define SF_WIFI RGUI(RCTL(KC_W))
#define SF_FMGR RGUI(RCTL(KC_M))
#define SF_VOLU RGUI(RCTL(KC_V))
#define SF_BLUE RGUI(RCTL(KC_B))

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [LAYER_BASE] = LAYOUT(
  // ╭──────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────╮
       KC_AMPR,  KC_Q,    KC_W,    SF_F,    KC_P,    KC_G,       KC_J,    KC_L,    KC_U,    KC_Y, KC_SCLN,  TD(QUOT),
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       KC_ASTR,  SF_A,    SF_R,    SF_S,    SF_T,    KC_D,       KC_H,    SF_N,    SF_E,    SF_I,    SF_O,  KC_MINS,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       KC_BSLS,  KC_Z,    KC_X,    SF_C,    SF_V,    KC_B,       KC_K,    KC_M, SF_COMM,  KC_DOT, KC_SLSH,  KC_EQL,
  // ╰──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────╯
                                 TD(TAB),  KC_SPC, NUMBER,      NAVIG,  MEDIA
  //                            ╰───────────────────────────╯ ╰──────────────────╯
  ),

  [LAYER_NUMBER] = LAYOUT(
  // ╭──────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────╮
       KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,    KC_COMM,  KC_7,    KC_8,    KC_9, KC_LBRC,  KC_RBRC,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
         KC_LT, KC_LGUI, KC_LCTL, KC_LALT, KC_LSFT, XXXXXXX,    KC_PPLS,  KC_4,    KC_5,    KC_6, KC_PMNS,  KC_EQL,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
         KC_GT, KC_CIRC, KC_AMPR, KC_ASTR, KC_UNDS, TD(QUOT),   KC_PAST,  KC_1,    KC_2,    KC_3, KC_PSLS,  KC_DOT,
  // ╰──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────╯
                                  XXXXXXX, XXXXXXX, _______,    KC_BSPC,  KC_0
  //                            ╰───────────────────────────╯ ╰──────────────────╯
  ),

  [LAYER_NAVIG] = LAYOUT(
  // ╭──────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────╮
       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, AC_TOGG,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       XXXXXXX, KC_LEFT,   KC_UP, KC_DOWN, KC_RGHT, XXXXXXX,    XXXXXXX, KC_RSFT, KC_RALT, KC_RCTL, KC_RGUI, XXXXXXX,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       XXXXXXX, KC_HOME, KC_PGUP, KC_PGDN,  KC_END, XXXXXXX,   TD(PSRC), TD(DEL), XXXXXXX, XXXXXXX, XXXXXXX, DB_TOGG,
  // ╰──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────╯
                                  _______, _______, XXXXXXX,    _______, XXXXXXX
  //                            ╰───────────────────────────╯ ╰──────────────────╯
  ),

  [LAYER_POINTER] = LAYOUT(
  // ╭──────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────╮
       QK_BOOT, EE_CLR, XXXXXXX, DPI_RMOD,S_D_RMOD, XXXXXXX,    XXXXXXX, S_D_MOD, DPI_MOD, XXXXXXX, XXXXXXX, XXXXXXX,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       XXXXXXX, KC_LGUI, KC_LCTL, KC_LALT, KC_LSFT, XXXXXXX,    KC_WBAK, KC_RSFT, KC_RALT, KC_RCTL, KC_RGUI, XXXXXXX,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       SCROLL_H_ONLY, XXXXXXX, SCROLL_V_ONLY, _______, DRGSCRL, XXXXXXX,    KC_WFWD, DRGSCRL, _______, SNIPING, KC_BTN3, XXXXXXX,
  // ╰──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────╯
                                  KC_BTN3, KC_BTN1, KC_BTN2,    KC_BTN2, KC_BTN1
  //                            ╰───────────────────────────╯ ╰──────────────────╯
  ),

  [LAYER_QWERTY] = LAYOUT(
  // ╭──────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────╮
       KC_AMPR,    KC_Q,    KC_W,   KC_E,    KC_R,    KC_T,       KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, TD(QUOT),
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       KC_ASTR,    SF_A,    QW_S,   QW_D,    QW_F,    KC_G,       KC_H,    QW_J,    QW_K,    QW_L, QW_SCLN, KC_MINS,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       KC_BSLS,    KC_Z,    KC_X,   SF_C,    KC_V,    KC_B,       KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, KC_EQL,
  // ╰──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────╯
                                 TD(TAB),  KC_SPC,  NUMBER,      NAVIG,  MEDIA
  //                            ╰───────────────────────────╯ ╰──────────────────╯
  ),

  [LAYER_WIN_MGR] = LAYOUT(
  // ╭──────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────╮
       _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,     TD(WK),   TD(W7), TD(W8),   TD(W9), _______, _______,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,     TD(WJ),   TD(W4), TD(W5),   TD(W6),  TD(WH), _______,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    G(KC_ENT), TD(W1), TD(W2),   TD(W3),  TD(WL), _______,
  // ╰──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────╯
                                  _______, G(KC_R), _______,    _______,   TD(W0)
  //                            ╰───────────────────────────╯ ╰──────────────────╯
  ),

  [LAYER_FN] = LAYOUT(
  // ╭──────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────╮
       _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    _______,   KC_F7,  KC_F8,  KC_F9,  KC_F10, _______,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    _______,   KC_F4,  KC_F5,  KC_F6,  KC_F11, _______,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    _______,   KC_F1,  KC_F2,  KC_F3,  KC_F12, _______,
  // ╰──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────╯
                                  _______, _______, _______,    _______,  _______
  //                            ╰───────────────────────────╯ ╰──────────────────╯
  ),

  [LAYER_MEDIA] = LAYOUT(
  // ╭──────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────╮
       _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    _______, KC_MPRV, KC_MPLY, KC_MNXT, XXXXXXX, _______,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    _______, KC_VOLU, KC_VOLD, XXXXXXX, XXXXXXX, _______,
  // ╰──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────╯
                                  KC_MUTE, KC_MPLY, _______,    _______,  _______
  //                            ╰───────────────────────────╯ ╰──────────────────╯
  ),

  [LAYER_WEB] = LAYOUT(
  // ╭──────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────╮
       SF_QUTE, _______, _______, SF_FRFX, _______, _______,    _______, _______, _______, _______, _______, _______,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       _______, _______, _______, _______, _______, _______,    _______, _______, _______, _______, _______, _______,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       _______, _______, _______, SF_CHRM, _______, _______,    _______, _______, _______, _______, _______, _______,
  // ╰──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────╯
                                  _______, _______, _______,    _______,  _______
  //                            ╰───────────────────────────╯ ╰──────────────────╯
  ),

  [LAYER_TOOLS] = LAYOUT(
  // ╭──────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────╮
       _______, SF_WIFI, _______, SF_FMGR, _______, _______,    _______, _______, _______, _______, _______, _______,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       _______, _______, _______, _______, _______, _______,    _______, _______, _______, _______, _______, _______,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       _______, _______, _______, _______, SF_VOLU, SF_BLUE,    _______, _______, _______, _______, _______, _______,
  // ╰──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────╯
                                  _______, _______, _______,    _______,  _______
  //                            ╰───────────────────────────╯ ╰──────────────────╯
  ),
};
// clang-format on

enum unicode_names {
    AGRAVE,
    THUMBS_UP,
    THUMBS_DOWN,
    FROG,
    ROCKET,
};

const uint32_t PROGMEM unicode_map[] = {
    [AGRAVE]      = 0x00E0,  // à
    [THUMBS_UP]   = 0x1f44D, // 👍
    [THUMBS_DOWN] = 0x1f44E, // 👎
    [FROG]        = 0x1F438, // 🐸
    [ROCKET]      = 0x1f680, // 🚀
};

const uint16_t PROGMEM pointer_combo[] = {SF_T, SF_C, COMBO_END};
const uint16_t PROGMEM colemak_combo[] = {KC_B, KC_N, COMBO_END};
const uint16_t PROGMEM qwerty_combo[]  = {KC_B, KC_K, COMBO_END};
const uint16_t PROGMEM web_combo[]     = {SF_O, KC_W, COMBO_END};
const uint16_t PROGMEM tools_combo[]   = {SF_O, SF_T, COMBO_END};
const uint16_t PROGMEM acute_combo[]   = {SF_E, SF_T, COMBO_END};
const uint16_t PROGMEM tilde_combo[]   = {SF_E, SF_N, COMBO_END};
const uint16_t PROGMEM circ_combo[]    = {SF_E, SF_V, COMBO_END};
const uint16_t PROGMEM cedil_combo[]   = {SF_E, SF_C, COMBO_END};
const uint16_t PROGMEM grave_combo[]   = {SF_E, SF_I, COMBO_END};
const uint16_t PROGMEM agrave_combo[]  = {SF_E, SF_A, COMBO_END};
const uint16_t PROGMEM lparen_combo[]  = {KC_M, SF_COMM, COMBO_END};
const uint16_t PROGMEM rparen_combo[]  = {SF_COMM, KC_DOT, COMBO_END};
const uint16_t PROGMEM lsqbrkt_combo[] = {KC_L, KC_U, COMBO_END};
const uint16_t PROGMEM rsqbrkt_combo[] = {KC_U, KC_Y, COMBO_END};
const uint16_t PROGMEM tup_combo[]     = {KC_F, KC_P, COMBO_END};
const uint16_t PROGMEM tdown_combo[]   = {SF_C, KC_V, COMBO_END};
const uint16_t PROGMEM frog_combo[]    = {KC_W, KC_F, COMBO_END};
const uint16_t PROGMEM rocket_combo[]  = {KC_X, SF_C, COMBO_END};

combo_t key_combos[] = {
    COMBO(qwerty_combo, DF(LAYER_QWERTY)),   // QWERTY
    COMBO(colemak_combo, DF(LAYER_BASE)),    // COLEMAK
    COMBO(web_combo, OSL(LAYER_WEB)),        // Web
    COMBO(tools_combo, OSL(LAYER_TOOLS)),    // Tools
    COMBO(acute_combo, RALT(KC_QUOT)),       // '
    COMBO(tilde_combo, RSA(KC_GRV)),         // ~
    COMBO(circ_combo, RALT(KC_6)),           // ^
    COMBO(cedil_combo, RALT(KC_COMM)),       // ç
    COMBO(grave_combo, RALT(KC_GRV)),        // `
    COMBO(lparen_combo, KC_LPRN),            // (
    COMBO(rparen_combo, KC_RPRN),            // )
    COMBO(lsqbrkt_combo, KC_LBRC),           // [
    COMBO(rsqbrkt_combo, KC_RBRC),           // ]
    COMBO(agrave_combo, UM(AGRAVE)),         // à
    COMBO(tup_combo, UM(THUMBS_UP)),         // 👍
    COMBO(tdown_combo, UM(THUMBS_DOWN)),     // 👎
    COMBO(frog_combo, UM(FROG)),             // 🐸
    COMBO(rocket_combo, UM(ROCKET)),         // 🚀
    COMBO(pointer_combo, TG(LAYER_POINTER)), // Toggle pointer layer
};

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

/** \brief Current drag-scroll axis restriction. */
static enum scroll_axis_mode scroll_axis = SCROLL_AXIS_BOTH;

/** \brief Axis-locked scroll keys; DRGSCRL resets to both axes. */
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case DRGSCRL:
            if (record->event.pressed) {
                scroll_axis = SCROLL_AXIS_BOTH;
            }
            break;
        case SCROLL_H_ONLY:
            scroll_axis = SCROLL_AXIS_H_ONLY;
            charybdis_set_pointer_dragscroll_enabled(record->event.pressed);
            break;
        case SCROLL_V_ONLY:
            scroll_axis = SCROLL_AXIS_V_ONLY;
            charybdis_set_pointer_dragscroll_enabled(record->event.pressed);
            break;
    }
    return true;
}

/* If CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE is defined, merge this with
 * the auto-pointer-layer hook above (only one definition is allowed). */
/** \brief Zero the unwanted scroll axis (runs after charybdis' conversion). */
report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
    if (charybdis_get_pointer_dragscroll_enabled()) {
        switch (scroll_axis) {
            case SCROLL_AXIS_H_ONLY:
                mouse_report.v = 0;
                break;
            case SCROLL_AXIS_V_ONLY:
                mouse_report.h = 0;
                break;
            default:
                break;
        }
    }
    return mouse_report;
}

#    ifdef CHARYBDIS_AUTO_SNIPING_ON_LAYER
layer_state_t layer_state_set_user(layer_state_t state) {
    charybdis_set_pointer_sniping_enabled(layer_state_cmp(state, CHARYBDIS_AUTO_SNIPING_ON_LAYER));
    return state;
}
#    endif // CHARYBDIS_AUTO_SNIPING_ON_LAYER
#endif     // POINTING_DEVICE_ENABLE

#ifdef RGB_MATRIX_ENABLE
void rgb_matrix_update_pwm_buffers(void);
#endif
