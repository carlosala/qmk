// Copiright 2023 Carlo Sala (@carlosala)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

enum user_layers {
    _DEF,
    _NUM,
    _SYM,
    _SET,
};

#define NUM_ENT LT(_NUM, KC_ENT)
#define SYM_ENT LT(_SYM, KC_ENT)

#define CTL_ESC LCTL_T(KC_ESC)
#define CTL_QUO LCTL_T(KC_QUOT)
#define LAL_SPC LALT_T(KC_SPC)
#define RAL_SPC RALT_T(KC_SPC)
#define SFT_CPS RSFT_T(KC_CAPS)
#define UC_CDOT UC(0x00B7)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_DEF] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,  KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      CTL_ESC,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                         KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, CTL_QUO,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, SFT_CPS,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI, LAL_SPC, NUM_ENT,    SYM_ENT, RAL_SPC, KC_LGUI
                                      //`--------------------------'  `--------------------------'

  ),

  [_NUM] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_GRV,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                         KC_6,    KC_7,    KC_8,    KC_9,    KC_0, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, KC_MINS,  KC_EQL, XXXXXXX, XXXXXXX, XXXXXXX,                      KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT, XXXXXXX,  KC_DEL,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, KC_UNDS, KC_PLUS, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, KC_COMM,  KC_DOT, KC_SLSH, _______,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, _______,    _______, _______, _______
                                      //`--------------------------'  `--------------------------'
  ),

  [_SYM] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      KC_TILD, KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC,                      KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|--------|
      _______, KC_MINS,  KC_EQL, KC_LBRC, KC_RBRC, KC_BSLS,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  KC_DEL,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE,                      XXXXXXX, XXXXXXX, XXXXXXX, UC_CDOT, XXXXXXX, _______,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, _______,    _______, _______, _______
                                      //`--------------------------'  `--------------------------'
  ),

  [_SET] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_F12,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                        KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, RGB_MOD, RGB_SPI, RGB_HUI, RGB_SAI, RGB_VAI,                      XXXXXXX, KC_VOLU, KC_BRIU, XXXXXXX, KC_PSCR,  KC_DEL,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|--------|
      RGB_TOG,RGB_RMOD, RGB_SPD, RGB_HUD, RGB_SAD, RGB_VAD,                      KC_MUTE, KC_VOLD, KC_BRID, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, _______,    _______, _______, _______
                                      //`--------------------------'  `--------------------------'
  )
};

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _NUM, _SYM, _SET);
}

#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (!is_keyboard_master()) {
    return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
  }
  return rotation;
}

void oled_render_layer_state(void) {
    oled_write_P(PSTR("LAYER: "), false);
    switch (get_highest_layer(layer_state)) {
        case _DEF:
            oled_write_ln_P(PSTR("Default"), false);
            break;
        case _NUM:
            oled_write_ln_P(PSTR("Numbers"), false);
            break;
        case _SYM:
            oled_write_ln_P(PSTR("Symbols"), false);
            break;
        case _SET:
            oled_write_ln_P(PSTR("Settings"), false);
            break;
        default:
            oled_write_ln_P(PSTR("Unknown"), false);
            break;
    }
}

void oled_render_wpm(void) {
    oled_write_P(PSTR("WPM: "), false);
    oled_write_ln(get_u8_str(get_current_wpm(), ' '), false);
}

void oled_render_logo(void) {
    static const char PROGMEM ohmyzsh_logo[] = {
      0,   0,   0,   0,   0,   128, 128, 128, 128, 128, 128, 128, 128, 128, 128,
      0,   0,   0,   0,   192, 240, 56,  12,  4,   196, 244, 60,  140, 128, 128,
      0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   128, 128, 128, 128,
      128, 128, 128, 128, 128, 128, 128, 0,   0,   128, 128, 128, 128, 128, 128,
      128, 128, 0,   0,   0,   0,   128, 128, 128, 128, 128, 128, 0,   0,   0,
      0,   128, 128, 128, 128, 128, 128, 0,   0,   0,   0,   0,   0,   128, 128,
      128, 128, 128, 128, 128, 128, 128, 128, 128, 0,   0,   0,   0,   128, 128,
      128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 192, 240, 56,  4,   4,
      196, 244, 60,  128, 128, 128, 0,   0,   0,   192, 120, 30,  7,   129, 193,
      97,  33,  33,  161, 225, 97,  1,   3,   143, 252, 120, 30,  7,   128, 192,
      96,  32,  32,  160, 224, 97,  1,   7,   158, 248, 0,   0,   0,   0,   0,
      128, 192, 120, 30,  7,   129, 193, 97,  33,  33,  161, 225, 97,  1,   1,
      131, 194, 97,  33,  33,  161, 225, 33,  1,   7,   158, 248, 60,  15,  3,
      193, 209, 61,  15,  3,   192, 208, 60,  15,  3,   193, 249, 63,  15,  3,
      0,   0,   0,   0,   60,  15,  35,  161, 225, 33,  1,   1,   193, 209, 61,
      15,  131, 192, 80,  60,  15,  3,   1,   33,  33,  33,  33,  33,  33,  225,
      225, 61,  15,  3,   128, 192, 32,  32,  32,  160, 224, 1,   1,   7,   222,
      248, 63,  225, 128, 128, 134, 135, 129, 132, 132, 134, 135, 129, 192, 112,
      158, 135, 129, 224, 120, 30,  7,   1,   224, 120, 158, 135, 129, 224, 120,
      30,  3,   0,   0,   0,   192, 240, 62,  135, 129, 192, 112, 30,  7,   1,
      192, 112, 158, 135, 129, 224, 120, 30,  7,   1,   224, 120, 158, 131, 128,
      224, 120, 62,  243, 192, 128, 128, 135, 131, 132, 196, 196, 7,   3,   192,
      240, 56,  15,  3,   0,   0,   0,   0,   0,   0,   0,   0,   224, 120, 158,
      131, 128, 128, 128, 135, 131, 132, 228, 60,  143, 135, 132, 132, 132, 132,
      132, 132, 128, 128, 224, 120, 152, 135, 131, 224, 120, 30,  3,   128, 224,
      120, 158, 131, 128, 224, 120, 31,  3,   0,   0,   0,   1,   1,   1,   1,
      1,   1,   1,   1,   1,   1,   1,   0,   1,   1,   1,   1,   0,   0,   0,
      0,   0,   0,   1,   1,   1,   1,   0,   0,   0,   0,   0,   0,   0,   0,
      0,   1,   1,   1,   0,   0,   0,   0,   0,   0,   1,   1,   1,   1,   0,
      0,   0,   0,   0,   0,   1,   1,   17,  61,  15,  35,  32,  32,  33,  33,
      33,  33,  33,  33,  32,  56,  30,  3,   0,   0,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   1,   1,   1,   1,   1,   1,   1,   1,
      0,   0,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   0,   1,
      1,   1,   1,   0,   0,   0,   0,   0,   0,   1,   1,   1,   0,   0,   0,
      0,   0,
    };
    oled_write_raw_P(ohmyzsh_logo, sizeof(ohmyzsh_logo));
    // static const char PROGMEM crkbd_logo[] = {
    //     0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93, 0x94,
    //     0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4,
    //     0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0xd4,
    //     0};
    // oled_write_P(crkbd_logo, false);
}

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        oled_render_layer_state();
        oled_render_wpm();
    } else {
        oled_render_logo();
    }
    return false;
}
#endif // OLED_ENABLE
