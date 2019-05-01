#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;

// Layer defines
#define _COLEMAKDH 0
#define _CODING 1
#define _ARROWS 2
#define _MOUSE 3
#define _NUMPAD 4
#define _SPECIAL 5
#define _GAMING 6
#define _TEMPLATE 7

// Shorthand Macros
#define _LSB LSFT_T(KC_BSPC)
#define _LC1 LCTL_T(KC_F10)
#define _LGZ LGUI_T(KC_Z)
#define _LAX LALT_T(KC_X)

// Custom keycodes
enum {
  SHIFT_TAB = SAFE_RANGE,
  REDO_NUM_F11
};

// Tap-dance defines
enum {
  TD_ENT_SPEC = 0,
  TD_4_F11_F5,
};

void tapdance_oneach (qk_tap_dance_state_t *state, void *user_data);
void tapdance_onfinished (qk_tap_dance_state_t *state, void *user_data);
void tapdance_onreset (qk_tap_dance_state_t *state, void *user_data);

// Tap-dance built-ins
int cur_dance (qk_tap_dance_state_t *state);
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

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_COLEMAKDH] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
     KC_ESC,   KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                               KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
  SHIFT_TAB,   KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,                               KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_BSLS,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
      _LSB,    KC_A,    KC_R,    KC_S,    KC_T,    KC_G,                               KC_M,    KC_N,    KC_E,    KC_I,    KC_O,    KC_QUOT,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
      _LC1,    _LGZ,   _LAX,    KC_C,    KC_D,    KC_V,  TD(TD_ENT_SPEC),    KC_DEL,  KC_K,    KC_H,    KC_COMM, KC_DOT,  KC_SLSH, TO(6),
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                           TD(TD_4_F11_F5), LT(1,KC_SPC), LSFT_T(KC_DEL),    KC_ENT, LT(2,KC_SPC), LT(1,KC_NO)
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
      TO(0),   KC_1,     KC_2,   KC_3,    KC_4,    KC_5,                              KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
      KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                              KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
      KC_LSFT, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                              KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
      KC_LCTL, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,   KC_NO,            KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   TO(5),
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                     KC_NO,   KC_SPC,  KC_NO,                     KC_TRNS,   KC_TRNS,   KC_TRNS
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

// Base layer color values
uint16_t h = 240;
uint8_t s = 255;
uint8_t v = 255;
bool is_in_rgb_mode = false;

void eeconfig_init_user(void) {
  rgblight_enable();
  rgblight_sethsv_noeeprom(h, s, v);
}

uint32_t layer_state_set_user(uint32_t state) {
  static uint8_t old_layer = 255;
  uint8_t new_layer = biton32(state);

  if (old_layer != new_layer) {
    if (old_layer == _SPECIAL) {
      is_in_rgb_mode = false;
      if (rgblight_get_mode() != false) {
        uint16_t newH = rgblight_get_hue();
        uint8_t newS = rgblight_get_sat();
        uint8_t newV = rgblight_get_val();

        if (newH != 300 || newS != 255 || newV != v) {
          h = newH;
          s = newS;
          v = newV;
        }
      }
    }

    switch (new_layer) {
      case _COLEMAKDH:
        rgblight_sethsv_noeeprom(h, s, v);
        break;
      case _CODING:
        rgblight_sethsv_noeeprom(0, 255, v);
        break;
      case _ARROWS:
        rgblight_sethsv_noeeprom(120, 255, v);
        break;
      case _MOUSE:
        rgblight_sethsv_noeeprom(180, 255, v);
        break;
      case _NUMPAD:
        rgblight_sethsv_noeeprom(60, 255, v);
        // Ensure numlock is on so we can actually use the number keys
        if (!(host_keyboard_leds() & (1<<USB_LED_NUM_LOCK))) {
          register_code(KC_NUMLOCK);
          unregister_code(KC_NUMLOCK);
        }
        break;
      case _SPECIAL:
        rgblight_sethsv_noeeprom(300, 255, v);
        break;
      case _GAMING:
        rgblight_sethsv_noeeprom(120, 85, v);
        break;
    }

    old_layer = new_layer;
  }

  return state;
}

bool is_ctrl_tabbing = 0;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case RGB_HUI:
    case RGB_HUD:
    case RGB_SAI:
    case RGB_SAD:
    case RGB_VAI:
    case RGB_VAD: {
      if (record->event.pressed) {
        uint8_t new_layer = biton32(layer_state);
        if (new_layer == _SPECIAL && !is_in_rgb_mode) {
          is_in_rgb_mode = true;
          rgblight_sethsv_noeeprom(h, s, v);
        }
      }
      return true;
    }

    case SHIFT_TAB: {
      const uint8_t is_ctrl = (get_mods() & (MOD_BIT(KC_LCTL) | MOD_BIT(KC_RCTL)));
      const uint8_t is_shift = (get_mods() & (MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT)));

      if (record->event.pressed) {
        if (is_ctrl) {
          // CTRL + Tab gets converted to SHIFT + Tab
          is_ctrl_tabbing = true;
          unregister_code(KC_LCTRL);
          register_code(KC_LSFT);
          register_code(KC_TAB);
        } else {
          register_code(KC_TAB);
        }
      } else {
        if (is_ctrl_tabbing) {
          // Turn off the SHIFT + Tab
          is_ctrl_tabbing = false;
          unregister_code(KC_LSFT);
          unregister_code(KC_TAB);
          if (is_shift) {
            // Re-register CTRL if the mod button was still held down
            register_code(KC_LCTRL);
          }
        } else {
          unregister_code(KC_TAB);
        }
      }

      return false;
    }

    case TD(TD_4_F11_F5):
    case LT(4,KC_F11): {
      const uint8_t is_ctrl = (get_mods() & (MOD_BIT(KC_LCTL) | MOD_BIT(KC_RCTL)));
      if (record->event.pressed) {
        if (is_ctrl) {
          // Redo
          register_code(KC_Y);
          return false;
        }
      } else {
        if (is_ctrl) {
          // Redo
          unregister_code(KC_Y);
          return false;
        }
      }
    }
  }

  return true;
}

int cur_dance (qk_tap_dance_state_t *state) {
  if (state->count == 1) {
    if (!state->pressed)  return SINGLE_TAP;
    else return SINGLE_HOLD;
  }
  else if (state->count == 2) {
    if (state->interrupted) return DOUBLE_SINGLE_TAP;
    else if (state->pressed) return DOUBLE_HOLD;
    else return DOUBLE_TAP;
  }
  else return 8;
}

static tap tap_states [] = {
  [TD_ENT_SPEC] = { .is_press_action = true, .state = 0 },
  [TD_4_F11_F5] = { .is_press_action = true, .state = 0 }
};

void tapdance_oneach (qk_tap_dance_state_t *state, void *user_data) {
}

void tapdance_onfinished (qk_tap_dance_state_t *state, void *user_data) {
  int id = (int)user_data;
  tap_states[id].state = cur_dance(state);
  switch (id) {
    case TD_ENT_SPEC: {
      switch (tap_states[id].state) {
        case SINGLE_TAP: register_code(KC_ENT); break;
        case SINGLE_HOLD: layer_on(_SPECIAL); break;
        case DOUBLE_TAP: layer_on(_SPECIAL); break;
        case DOUBLE_HOLD: break;
        case DOUBLE_SINGLE_TAP: break;
      }
      break;
    }

    case TD_4_F11_F5: {
      switch (tap_states[id].state) {
        case SINGLE_TAP: register_code(KC_F11); break;
        case SINGLE_HOLD: layer_on(_NUMPAD); break;
        case DOUBLE_TAP: register_code(KC_F5); break;
        case DOUBLE_HOLD: break;
        case DOUBLE_SINGLE_TAP: break;
      }
      break;
    }
  }
}

void tapdance_onreset (qk_tap_dance_state_t *state, void *user_data) {
  int id = (int)user_data;
  switch (id) {
    case TD_ENT_SPEC: {
      switch (tap_states[id].state) {
        case SINGLE_TAP: unregister_code(KC_ENT); break;
        case SINGLE_HOLD: layer_off(_SPECIAL); break;
        case DOUBLE_TAP:  break;
        case DOUBLE_HOLD: break;
        case DOUBLE_SINGLE_TAP: break;
      }
      break;
    }

    case TD_4_F11_F5: {
      switch (tap_states[id].state) {
        case SINGLE_TAP: unregister_code(KC_F11); break;
        case SINGLE_HOLD: layer_off(_NUMPAD); break;
        case DOUBLE_TAP: unregister_code(KC_F5); break;
        case DOUBLE_HOLD: break;
        case DOUBLE_SINGLE_TAP: break;
      }
      break;
    }
  }
  tap_states[id].state = 0;
}

qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_ENT_SPEC] = { .fn = { tapdance_oneach, tapdance_onfinished, tapdance_onreset }, .user_data = (void*)TD_ENT_SPEC },
  [TD_4_F11_F5] = { .fn = { tapdance_oneach, tapdance_onfinished, tapdance_onreset }, .user_data = (void*)TD_4_F11_F5 }
};
