#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;

#define _COLEMAKDH 0
#define _CODING 1
#define _ARROWS 2
#define _MOUSE 3
#define _NUMPAD 4
#define _SPECIAL 5
#define _GAMING 6
#define _TEMPLATE 7

#define _LSB LSFT_T(KC_BSPC)
#define _LCE LCTL_T(KC_ENT)
#define _LGZ LGUI_T(KC_Z)
#define _LAX LALT_T(KC_X)

typedef struct {
  bool is_press_action;
  int state;
} tap;

enum {
  SINGLE_TAP = 1,
  SINGLE_HOLD = 2,
  DOUBLE_TAP = 3,
  DOUBLE_HOLD = 4,
  DOUBLE_SINGLE_TAP = 5,
  TRIPLE_TAP = 6,
  TRIPLE_HOLD = 7
};

enum {
  TD_ENT_SPEC = 0
};

int cur_dance (qk_tap_dance_state_t *state);
void x_finished (qk_tap_dance_state_t *state, void *user_data);
void x_reset (qk_tap_dance_state_t *state, void *user_data);

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_COLEMAKDH] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
     KC_ESC,   KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                               KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_TAB,   KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,                               KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_BSLS,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
      _LSB,    KC_A,    KC_R,    KC_S,    KC_T,    KC_G,                               KC_M,    KC_N,    KC_E,    KC_I,    KC_O,    KC_QUOT,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
      _LCE,    _LGZ,    _LAX,    KC_C,    KC_D,    KC_V,  TD(TD_ENT_SPEC),    KC_DEL,  KC_K,    KC_H,    KC_COMM, KC_DOT,  KC_SLSH, TO(6),
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                               LT(4,KC_Y), LT(1,KC_SPC), LSFT_T(KC_DEL),        KC_ENT, LT(2,KC_SPC), LT(1,KC_NO)
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ),

  [_CODING] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
     TO(0),    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                              KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_NO,   KC_TILD,  KC_NO,   KC_NO,   KC_PPLS, KC_EQL,                            KC_PIPE,  KC_LCBR, KC_RCBR, KC_CIRC, KC_COLN, KC_F12,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_NO,    KC_GRV,  KC_DLR, KC_ASTR,  KC_PMNS, KC_GT,                             KC_AMPR,  KC_LPRN, KC_RPRN, KC_LBRC, KC_RBRC, KC_DQUO,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_NO,    KC_NO,   KC_NO,  KC_PERC,  KC_UNDS, KC_LT,   KC_NO,            KC_NO,  KC_EXLM,  KC_EQL,  KC_LT,   KC_GT,   KC_QUES, TO(0),
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                     KC_NO,   KC_NO,   KC_NO,                     KC_NO,   KC_NO,   KC_NO
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ),

  [_ARROWS] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
      TO(0),   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                              KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
      KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                             KC_NO,LCTL(KC_LEFT),KC_UP,LCTL(KC_RGHT),KC_NO, KC_NO,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
      KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                              KC_HOME, KC_LEFT, KC_DOWN, KC_RGHT, KC_END,  KC_NO,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
      KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,            KC_NO,   KC_NO,LSFT(KC_LEFT),KC_NO,LSFT(KC_RGHT),KC_NO, TO(1),
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                     KC_NO,   TO(3),   KC_NO,                     KC_NO,   KC_NO,   KC_NO
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ),

  [_MOUSE] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
      TO(0),   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                              KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
      KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                              KC_NO,  KC_WH_U,  KC_MS_U, KC_WH_D, KC_NO,   KC_NO,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
      KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                              KC_NO,  KC_MS_L,  KC_MS_D, KC_MS_R, KC_BTN3, KC_NO,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
      KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,            KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   TO(2),
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                     KC_NO,  KC_TRNS,   KC_NO,                     KC_NO,  KC_BTN1, KC_BTN2
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ),

  [_NUMPAD] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
      TO(0),   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                              KC_NO,   KC_NO,  KC_PSLS,  KC_PAST, KC_PMNS, KC_NO,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
      KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                              KC_NO,   KC_P7,   KC_P8,   KC_P9,  KC_PPLS,  KC_NO,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
      KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                              KC_NO,   KC_P4,   KC_P5,   KC_P6,  KC_PCMM,  KC_NO,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
      KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,            KC_NO,   KC_NO,   KC_P1,   KC_P2,   KC_P3,  KC_PEQL,  TO(3),
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                     KC_NO,   KC_NO,   KC_NO,                     KC_NO,   KC_P0,   KC_PDOT
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ),

  [_SPECIAL] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
      TO(0),   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                              KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
      KC_NO,   KC_NO,   KC_NO,   KC_F5,   KC_F10,  KC_F11,                            RGB_TOG,  RGB_HUI, RGB_HUD, KC_NO,   KC_NO,   KC_NO,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
      KC_NO,   KC_NO,   KC_NO,   KC_F8,   KC_NO,   KC_F12,                            RGB_M_P,  RGB_SAI, RGB_SAD, KC_NO,   KC_NO,   KC_NO,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
      KC_NO,   KC_NO,   KC_NO,   KC_NO,  KC_PSCR,LALT(KC_PSCR),TO(0),          KC_NO,  RGB_M_B,  RGB_VAI, RGB_VAD, KC_NO,   KC_NO,   TO(4),
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                     KC_PGDN, KC_PGUP, KC_LSFT,                   KC_NO,   KC_NO,   KC_NO
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ),

    [_GAMING] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
      TO(0),   KC_1,     KC_2,   KC_3,    KC_4,    KC_5,                              KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
      KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                              KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
      KC_LSFT, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                              KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
      KC_LCTL, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,   KC_NO,            KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   TO(5),
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                     KC_NO,   KC_SPC,  KC_NO,                     KC_NO,   KC_NO,   KC_NO
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ),

  [_TEMPLATE] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
      TO(0),   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                              KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
      KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                              KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
      KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                              KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
      KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,            KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                     KC_NO,   KC_NO,   KC_NO,                     KC_NO,   KC_NO,   KC_NO
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ),
};

void matrix_init_user(void) {
  rgblight_enable();
}

void matrix_scan_user(void) {
  #ifdef RGBLIGHT_ENABLE

  static uint8_t old_layer = 255;
  uint8_t new_layer = biton32(layer_state);

  static uint16_t h = 240;
  static uint8_t s = 255;
  static uint8_t v = 255;

  if (old_layer != new_layer) {
    if (old_layer == _SPECIAL && rgblight_get_mode() != false) {
      uint16_t newH = rgblight_get_hue();
      uint8_t newS = rgblight_get_sat();
      uint8_t newV = rgblight_get_val();

      if (newH != 300 || newS != 255 || newV != v) {
         h = newH;
         s = newS;
         v = newV;
      }
    }
    switch (new_layer) {
      case _COLEMAKDH:
        rgblight_sethsv(h, s, v);
        break;
      case _CODING:
        rgblight_sethsv(0, 255, v);
        break;
      case _ARROWS:
        rgblight_sethsv(120, 255, v);
        break;
      case _MOUSE:
        rgblight_sethsv(180, 255, v);
        break;
      case _NUMPAD:
        rgblight_sethsv(60, 255, v);
        break;
      case _SPECIAL:
        rgblight_sethsv(300, 255, v);
        break;
      case _GAMING:
        rgblight_sethsv(120, 85, v);
        break;
    }

    old_layer = new_layer;
  }

  #endif //RGBLIGHT_ENABLE
}

int cur_dance (qk_tap_dance_state_t *state) {
  if (state->count == 1) {
    if (state->interrupted || !state->pressed)  return SINGLE_TAP;
    else return SINGLE_HOLD;
  }
  else if (state->count == 2) {
    if (state->interrupted) return DOUBLE_SINGLE_TAP;
    else if (state->pressed) return DOUBLE_HOLD;
    else return DOUBLE_TAP;
  }

  if (state->count == 3) {
    if (state->interrupted || !state->pressed)  return TRIPLE_TAP;
    else return TRIPLE_HOLD;
  }
  else return 8;
}

static tap xtap_state = {
  .is_press_action = true,
  .state = 0
};

void x_finished (qk_tap_dance_state_t *state, void *user_data) {
  xtap_state.state = cur_dance(state);
  switch (xtap_state.state) {
    case SINGLE_TAP: register_code(KC_ENT); break;
    case SINGLE_HOLD: layer_on(_SPECIAL); break;
    case DOUBLE_TAP: layer_on(_SPECIAL); break;
    case DOUBLE_HOLD: break;
    case DOUBLE_SINGLE_TAP: break;
  }
}

void x_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (xtap_state.state) {
    case SINGLE_TAP: unregister_code(KC_ENT); break;
    case SINGLE_HOLD: layer_off(_SPECIAL); break;
    case DOUBLE_TAP:  break;
    case DOUBLE_HOLD: break;
    case DOUBLE_SINGLE_TAP: break;
  }
  xtap_state.state = 0;
}

qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_ENT_SPEC] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, x_finished, x_reset)
};
