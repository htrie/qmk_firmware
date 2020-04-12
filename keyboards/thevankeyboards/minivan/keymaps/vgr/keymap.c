
#include "quantum.h"

#define LAYOUT(K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, K30, K31, K32, K34, K33, K37, K38, K39, K3A, K3B) { \
  { K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B }, \
  { K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B }, \
  { K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B }, \
  { K30, K31, K32, K33, K34, KC_NO, KC_NO, K37, K38, K39, K3A, K3B } \
}

void matrix_init_kb(void) {
  matrix_init_user();
}
void matrix_scan_kb(void) {
  matrix_scan_user();
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
  return process_record_user(keycode, record);
}

void led_set_kb(uint8_t usb_led) {
  led_set_user(usb_led);
}

enum custom_keycodes {
  M_IME = SAFE_RANGE
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    switch(keycode) {
      case M_IME:
        SEND_STRING(SS_DOWN(X_LSHIFT)SS_DOWN(X_LALT));
        return false;
    }
  }
  else {
    switch(keycode) {
      case M_IME:
        SEND_STRING(SS_UP(X_LSHIFT)SS_UP(X_LALT));
        return false;
    }
  }
  return true;
};
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT(KC_ESC, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_BSPC, LT(3, KC_TAB), KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, LT(1, KC_SCLN), KC_ENT, KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, KC_NO, KC_LGUI, KC_LALT, KC_LCTL, MO(2), KC_SPC, KC_RALT, KC_RCTL, KC_RGUI, KC_NO),
  [1] = LAYOUT(KC_TRNS, KC_NO, KC_LPRN, KC_LCBR, KC_LBRC, KC_NO, KC_PGUP, KC_HOME, KC_UP, KC_END, KC_NO, KC_TRNS, KC_TRNS, KC_LCTL, KC_LSFT, KC_LALT, KC_TAB, KC_NO, KC_PGDN, KC_LEFT, KC_DOWN, KC_RIGHT, KC_TRNS, KC_TRNS, KC_TRNS, KC_NO, KC_RPRN, KC_RCBR, KC_RBRC, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),
  [2] = LAYOUT(KC_GRV, KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_LPRN, KC_SLSH, KC_7, KC_8, KC_9, KC_PLUS, KC_MINS, KC_TRNS, KC_PIPE, KC_PERC, KC_AMPR, KC_UNDS, KC_LCBR, KC_0, KC_4, KC_5, KC_6, KC_ASTR, KC_EQL, KC_TRNS, KC_CIRC, KC_TILD, KC_QUOT, KC_DQT, KC_LBRC, KC_DOT, KC_1, KC_2, KC_3, KC_BSLS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),
  [3] = LAYOUT(KC_TRNS, KC_F1, KC_F2, KC_F3, KC_F4, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_F5, KC_F6, KC_F7, KC_F8, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_F9, KC_F10, KC_F11, KC_F12, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS)
};

void process_indicator_update(uint32_t state, uint8_t usb_led) {
  for (int i = 0; i < 3; i++) {
    setrgb(0, 0, 0, (LED_TYPE *)&led[i]);
  }
  setrgb(192, 0, 0, (LED_TYPE *)&led[0]);
    if (state & (1<<3)) {
  setrgb(0, 185, 0, (LED_TYPE *)&led[0]);
}

  if (state & (1<<2)) {
  setrgb(0, 0, 215, (LED_TYPE *)&led[1]);
}

  if (state & (1<<1)) {
  setrgb(0, 208, 255, (LED_TYPE *)&led[2]);
}


  rgblight_set();
};

void keyboard_post_init_user(void) {
  process_indicator_update(layer_state, host_keyboard_leds());
};

void led_set_user(uint8_t usb_led) {
  process_indicator_update(layer_state, host_keyboard_leds());
};

uint32_t layer_state_set_user(uint32_t state) {
  process_indicator_update(state, host_keyboard_leds());
  return state;
};