#include QMK_KEYBOARD_H

enum {
  SFT_CAPS,
  RBRC_FLYDOT,
};

void flydot_fn(qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) send_string("]");
  else send_unicode_string("·");
}

qk_tap_dance_action_t tap_dance_actions[] = {
  [RBRC_FLYDOT] = ACTION_TAP_DANCE_FN(flydot_fn),
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_60_ansi(
    KC_GRV, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSPC,
    KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, TD(RBRC_FLYDOT), KC_BSLS,
    KC_ESC, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_ENT,
    KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, RSFT_T(KC_CAPS),
    KC_LCTL, KC_LGUI, KC_LALT, KC_SPC, KC_RALT, MO(1), KC_APP, KC_RCTL),
  [1] = LAYOUT_60_ansi(
    KC_TRNS, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_TRNS,
    KC_TRNS, RGB_MOD, RGB_SPI, RGB_HUI, RGB_SAI, RGB_VAI, KC_TRNS, KC_HOME, KC_END, KC_TRNS, KC_PSCR, KC_TRNS, KC_TRNS, KC_DEL,
    KC_TRNS, RGB_RMOD, RGB_SPD, RGB_HUD, RGB_SAD, RGB_VAD, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, RGB_TOG, KC_TRNS, KC_VOLD, KC_VOLU, KC_TRNS, KC_TRNS, KC_MUTE, KC_TRNS, KC_TRNS, KC_TRNS, LALT(KC_F4),
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, RESET, KC_TRNS)
};
