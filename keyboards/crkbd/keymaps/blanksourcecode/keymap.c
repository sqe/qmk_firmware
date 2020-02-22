#include QMK_KEYBOARD_H
#include "bootloader.h"
#ifdef PROTOCOL_LUFA
  #include "lufa.h"
  #include "split_util.h"
#endif
#ifdef SSD1306OLED
  #include "ssd1306.h"
#endif

#include <split_scomm.h>
#include "raw_hid.h"

extern keymap_config_t keymap_config;
extern rgblight_config_t rgblight_config;
extern uint8_t is_master;

// Layer defines
#define _COLEMAK 0
#define _CODING 1
#define _ARROWS 2
#define _NUMPAD 3
#define _RGB 4
#define _GAMING 5
#define _TEMPLATE 7

// Shorthand Macros
#define KC_TD(a) TD(a)
#define KC_TO(a) TO(a)
#define KC_LGZ LGUI_T(KC_Z)
#define KC_LAX LALT_T(KC_X)
#define KC_SHL LSFT_T(KC_LEFT)
#define KC_SHR LSFT_T(KC_RGHT)
#define KC_CTLL LCTL_T(KC_LEFT)
#define KC_CTLR LCTL_T(KC_RGHT)
#define KC_SDEL LSFT_T(KC_DEL)
#define KC_ASPC LT(_ARROWS,KC_SPC)
#define KC_CESC LCTL_T(KC_ESC)
#define KC_RTG RGB_TOG
#define KC_RHI RGB_HUI
#define KC_RHD RGB_HUD
#define KC_RSI RGB_SAI
#define KC_RSD RGB_SAD
#define KC_RVI RGB_VAI
#define KC_RVD RGB_VAD
#define KC_RMI RGB_MOD
#define KC_RMD RGB_RMOD
#define KC_RMP RGB_M_P
#define KC_RMR RGB_M_R
#define KC_BBS BACK_SLASH

// Custom keycodes
enum {
  SHIFT_TAB = SAFE_RANGE,
  REDO_NUM_F11,
  BACK_SLASH
};

// Tap-dance built-ins
void tapdance_oneach (qk_tap_dance_state_t *state, void *user_data);
void tapdance_onfinished (qk_tap_dance_state_t *state, void *user_data);
void tapdance_onreset (qk_tap_dance_state_t *state, void *user_data);

int cur_dance (qk_tap_dance_state_t *state);
typedef struct {
  bool is_press_action;
  int state;
} tap;

typedef struct {
  int single_tap;
  int single_hold;
  int double_tap;
  bool is_double_tap_layer_lock;
  bool use_instant_layer;
} tri_layer_action;

enum {
  SINGLE_TAP = 1,
  SINGLE_HOLD = 2,
  DOUBLE_TAP = 3,
  DOUBLE_HOLD = 4,
  DOUBLE_SINGLE_TAP = 5,
  TRIPLE_TAP = 6,
  TRIPLE_HOLD = 7
};

// Tap-dance defines
enum {
  TD_ENT = 0,
  TD_NUM,
  TD_SPC,
};

static tri_layer_action tri_layer_actions [] = {
  [TD_ENT] = { .single_tap = KC_ENT, .single_hold = _RGB, .double_tap = _RGB, .is_double_tap_layer_lock = true, .use_instant_layer = false },
  [TD_NUM] = { .single_tap = KC_F10, .single_hold = _NUMPAD, .double_tap = KC_F5, .is_double_tap_layer_lock = false, .use_instant_layer = true  },
  [TD_SPC] = { .single_tap = KC_F11, .single_hold = _CODING, .double_tap = KC_SPC, .is_double_tap_layer_lock = false, .use_instant_layer = true  }
};

static tap tap_states [] = {
  [TD_ENT] = { .is_press_action = true, .state = 0 },
  [TD_NUM] = { .is_press_action = true, .state = 0 },
  [TD_SPC] = { .is_press_action = true, .state = 0 }
};

qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_ENT] = { .fn = { tapdance_oneach, tapdance_onfinished, tapdance_onreset }, .user_data = (void*)TD_ENT },
  [TD_NUM] = { .fn = { tapdance_oneach, tapdance_onfinished, tapdance_onreset }, .user_data = (void*)TD_NUM },
  [TD_SPC] = { .fn = { tapdance_oneach, tapdance_onfinished, tapdance_onreset }, .user_data = (void*)TD_SPC }
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_COLEMAK] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
        TAB,   Q,     W,     F,     P,     B,                      J,     L,     U,     Y,  SCLN,    BBS,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       BSPC,   A,     R,     S,     T,     G,                      M,     N,     E,     I,    O,    QUOT,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       CESC,  LGZ,  LAX,     C,     D,     V,                      K,     H,  COMM,   DOT,  SLSH,  TO(5),\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                          TD(TD_NUM),TD(TD_SPC),SDEL,      ENT,  ASPC,TD(TD_ENT) \
                              //`--------------------'  `--------------------'
  ),

  [_CODING] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
        F1,  TILD,   DLR,  LCBR,  PPLS,   EQL,                   PIPE,  LCBR,  RCBR,  CIRC,  COLN,  TRNS,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      TRNS,   GRV,   DLR,  ASTR,  PMNS,    GT,                   AMPR,  LPRN,  RPRN,  LBRC,  RBRC,  DQUO,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      TRNS,  TRNS,  TRNS,  PERC,  UNDS,    LT,                   EXLM,   EQL,    LT,    GT,  QUES, TO(0),\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                  TRNS,  TRNS,  TRNS,     TRNS,  TRNS,  TRNS \
                              //`--------------------'  `--------------------'
  ),

  [_ARROWS] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
     TO(0),  TILD,   GRV,  TRNS,  TRNS,  TRNS,                   TRNS,  CTLL,   UP,   CTLR,  TRNS,  TRNS,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      TRNS,  EXLM,    AT,  HASH,   DLR,  PERC,                   HOME,  LEFT,  DOWN,  RGHT,   END,  TRNS,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      TRNS,  CIRC,  AMPR,  ASTR,  TRNS,  TRNS,                   TRNS,   SHL,  TRNS,   SHR,  TRNS, TO(1),\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                  TRNS,  TRNS,  TRNS,     TRNS,  TRNS,  TRNS \
                              //`--------------------'  `--------------------'
  ),

  [_NUMPAD] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
     TO(0),     1,     2,     3,     4,     5,                   TRNS,    P7,    P8,    P9,  PMNS,  TRNS,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      TRNS,     6,     7,     8,     9,     0,                   TRNS,    P4,    P5,    P6,  PPLS,  TRNS,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      TRNS,  TRNS,  TRNS,  TRNS,  TRNS,  TRNS,                   TRNS,    P1,    P2,    P3,   EQL, TO(2),\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                  TRNS,  TRNS,  TRNS,     TRNS,    P0,  PDOT \
                              //`--------------------'  `--------------------'
  ),

  [_RGB] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
     TO(0),  TRNS,  TRNS,  TRNS,  TRNS,  TRNS,                    RTG,   RHI,   RHD,  TRNS,  TRNS,   RMP,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      TRNS,  TRNS,  TRNS,  TRNS,  TRNS,  TRNS,                    RMI,   RSI,   RSD,  TRNS,  TRNS,   RMR,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      TRNS,  TRNS,  TRNS,  TRNS,  TRNS,  TRNS,                    RMD,   RVI,   RVD,  TRNS,  TRNS, TO(3),\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                  TRNS,  TRNS,  TRNS,     TRNS,  TRNS,  TRNS \
                              //`--------------------'  `--------------------'
  ),

  [_GAMING] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
     TO(0),  TRNS,     W,  TRNS,  TRNS,  TRNS,                   TRNS,  TRNS,  TRNS,  TRNS,  TRNS,  TRNS,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      TRNS,     S,     A,     D,  TRNS,  TRNS,                   TRNS,  TRNS,  TRNS,  TRNS,  TRNS,  TRNS,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      TRNS,  TRNS,  TRNS,  TRNS,  TRNS,  TRNS,                   TRNS,  TRNS,  TRNS,  TRNS,  TRNS, TO(4),\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                  TRNS,   SPC,  TRNS,     TRNS,  TRNS,  TRNS \
                              //`--------------------'  `--------------------'
  ),

  [_TEMPLATE] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
      TRNS,  TRNS,  TRNS,  TRNS,  TRNS,  TRNS,                   TRNS,  TRNS,  TRNS,  TRNS,  TRNS,  TRNS,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      TRNS,  TRNS,  TRNS,  TRNS,  TRNS,  TRNS,                   TRNS,  TRNS,  TRNS,  TRNS,  TRNS,  TRNS,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      TRNS,  TRNS,  TRNS,  TRNS,  TRNS,  TRNS,                   TRNS,  TRNS,  TRNS,  TRNS,  TRNS,  TRNS,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                  TRNS,  TRNS,  TRNS,     TRNS,  TRNS,  TRNS \
                              //`--------------------'  `--------------------'
  ),
};

int RGB_current_mode;

void matrix_init_user(void) {
    iota_gfx_init(false);
}

// When add source files to SRC in rules.mk, you can use functions.
const char *read_layer_state(void);
const char *read_logo(void);
void set_keylog(uint16_t keycode, keyrecord_t *record);
const char *read_keylog(void);
const char *read_keylogs(void);

// Screen printing
bool foundHID = false;
char layer_state_str[20];
const char *write_layer(void){
  switch (biton32(layer_state))
  {
  case _COLEMAK:
    snprintf(layer_state_str, sizeof(layer_state_str), "Layer: Colemak-DH");
    break;
  case _CODING:
    snprintf(layer_state_str, sizeof(layer_state_str), "Layer: Code Symbols");
    break;
  case _ARROWS:
    snprintf(layer_state_str, sizeof(layer_state_str), "Layer: Navigation");
    break;
  case _NUMPAD:
    snprintf(layer_state_str, sizeof(layer_state_str), "Layer: Numpad");
    break;
  case _RGB:
    snprintf(layer_state_str, sizeof(layer_state_str), "Layer: RGB Lighting");
    break;
  case _GAMING:
    snprintf(layer_state_str, sizeof(layer_state_str), "Layer: Gaming Mode");
    break;
  default:
    snprintf(layer_state_str, sizeof(layer_state_str), "Layer: Id-%ld", layer_state);
  }

  return layer_state_str;
}

char rbf_info_str[24];
const char *write_rgb(void) {
  snprintf(rbf_info_str, sizeof(rbf_info_str), "%s: %02d h%03d s%03d v%03d",
    rgblight_config.enable ? "\x02A" : "-", rgblight_config.mode,
    rgblight_config.hue, rgblight_config.sat, rgblight_config.val);
  return rbf_info_str;
}

char hid_info_str[20];
const char *write_hid(void) {
  snprintf(hid_info_str, sizeof(hid_info_str), "%s", foundHID ? "connected." : " ");
  return hid_info_str;
}

char cpu_info_str[20];
char mem_info_str[20];
char dsk_info_str[20];
char net_info_str[20];
char screen_str[22 * 4];
void write_stats(struct CharacterMatrix *matrix) {
  if (serial_slave_screen_buffer[0] > 0) {
    matrix_write(matrix, (char*)serial_slave_screen_buffer + 1);
  } else {
    matrix_write_ln(matrix, "");
    matrix_write(matrix, read_logo());
  }
}

// HID input
void raw_hid_receive(uint8_t *data, uint8_t length)
{
  foundHID = true;
  if (length >= 5) {
      memset((char*)&serial_slave_screen_buffer[0], ' ', sizeof(serial_slave_screen_buffer));

      memcpy((char*)&serial_slave_screen_buffer[1], "cpu:", 4);
      memcpy((char*)&serial_slave_screen_buffer[22], "mem:", 4);
      memcpy((char*)&serial_slave_screen_buffer[43], "dsk:", 4);
      memcpy((char*)&serial_slave_screen_buffer[64], "net:", 4);

      for (int i = 0; i < 4; i++) {
        for (int j = 0; j < data[i]; j++) {
          serial_slave_screen_buffer[1 + (i * 21) + 5 + j] = 'o';
        }
        serial_slave_screen_buffer[1 + (i * 21) + 16] = '|';
      }

      serial_slave_screen_buffer[0] = 1;
      serial_slave_screen_buffer[sizeof(serial_slave_screen_buffer) - 1] = 0;

      data[0] = length;
      data[1] = serial_slave_screen_buffer[0];
      data[2] = serial_slave_screen_buffer[1];
      data[3] = serial_slave_screen_buffer[22];
      data[4] = serial_slave_screen_buffer[43];
      data[5] = serial_slave_screen_buffer[64];
      raw_hid_send(data, length);

      hid_screen_change = true;
  }
}

void matrix_scan_user(void) {
   iota_gfx_task();
}

void matrix_render_user(struct CharacterMatrix *matrix) {
  if (is_master) {
    matrix_write_ln(matrix, write_layer());
    matrix_write_ln(matrix, " ");
    matrix_write_ln(matrix, write_rgb());
    matrix_write(matrix, write_hid());
  } else {
    write_stats(matrix);
  }
}

void matrix_update(struct CharacterMatrix *dest, const struct CharacterMatrix *source) {
  if (memcmp(dest->display, source->display, sizeof(dest->display))) {
    memcpy(dest->display, source->display, sizeof(dest->display));
    dest->dirty = true;
  }
}

void iota_gfx_task_user(void) {
  struct CharacterMatrix matrix;
  matrix_clear(&matrix);
  matrix_render_user(&matrix);
  matrix_update(&display, &matrix);
}

// Base layer color values
uint16_t h = 156;
uint8_t s = 255;
uint8_t v = 255;
bool is_in_rgb_mode = false;

void eeconfig_init_user(void) {
  rgblight_enable();
  rgblight_set_effect_range(0, 27);
  rgblight_sethsv_noeeprom(h, s, v);
}

uint32_t layer_state_set_user(uint32_t state) {
  static uint8_t old_layer = 255;
  uint8_t new_layer = biton32(state);

  if (old_layer != new_layer) {
    if (old_layer == _RGB) {
      is_in_rgb_mode = false;
      if (rgblight_get_mode() != false) {
        uint16_t newH = rgblight_get_hue();
        uint8_t newS = rgblight_get_sat();
        uint8_t newV = rgblight_get_val();

        if (newH != 120 || newS != 255 || newV != v) {
          h = newH;
          s = newS;
          v = newV;
        }
      }
    }

    switch (new_layer) {
      case _COLEMAK:
        rgblight_sethsv_noeeprom(h, s, v);
        break;
      case _CODING:
        rgblight_sethsv_noeeprom(0, 255, v);
        break;
      case _ARROWS:
        rgblight_sethsv_noeeprom(83, 255, v);
        break;
      case _NUMPAD:
        rgblight_sethsv_noeeprom(43, 255, v);
        // Ensure numlock is on so we can actually use the number keys
        if (!(host_keyboard_leds() & (1<<USB_LED_NUM_LOCK))) {
          register_code(KC_NUMLOCK);
          unregister_code(KC_NUMLOCK);
        }
        break;
      case _RGB:
        rgblight_sethsv_noeeprom(120, 255, v);
        break;
      case _GAMING:
        rgblight_sethsv_noeeprom(120, 85, v);
        break;
    }

    old_layer = new_layer;
  }

  return state;
}

bool is_ctrl_shifting = 0;
bool is_back_shifting = 0;
bool is_ctrl_shift_ent = 0;

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
        if (new_layer == _RGB && !is_in_rgb_mode) {
          is_in_rgb_mode = true;
          rgblight_sethsv_noeeprom(h, s, v);
        }
      }
      return true;
    }

    case BACK_SLASH: {
      const uint8_t is_shift = (get_mods() & (MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT)));

      if (record->event.pressed) {
        if (is_shift) {
          is_back_shifting = true;
          unregister_code(KC_LSFT);
          register_code(KC_BSLS);
        } else {
          register_code(KC_BSPC);
        }
      } else {
        if (is_back_shifting) {
          is_back_shifting = false;
          if (is_shift) {
            register_code(KC_LSFT);
          }
        } else {
          unregister_code(KC_BSPC);
        }
      }

      return false;
    }

    case KC_BSPC: {
      const uint8_t is_ctrl = (get_mods() & (MOD_BIT(KC_LCTL) | MOD_BIT(KC_RCTL)));

      if (record->event.pressed) {
        if (is_ctrl) {
          // CTRL + Backspace gets converted to CTRL + SHIFT
          is_ctrl_shifting = true;
          register_code(KC_LSFT);
          register_code(KC_LCTL);
        } else {
          register_code(KC_BSPC);
        }
      } else {
        if (is_ctrl_shifting) {
          // Turn off the CTRL + SHIFT
          is_ctrl_shifting = false;
          unregister_code(KC_LSFT);
        } else {
          unregister_code(KC_BSPC);
        }
      }

      return false;
    }

    case TD(TD_NUM):
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

      return true;
    }

    case LSFT_T(KC_DEL): {
      const uint8_t is_shift = (get_mods() & (MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT)));
      const uint8_t is_ctrl = (get_mods() & (MOD_BIT(KC_LCTL) | MOD_BIT(KC_RCTL)));
      if (is_shift && is_ctrl) {
        if (record->event.pressed) {
          is_ctrl_shift_ent = true;
          clear_mods();
          tap_code(KC_ENT);
          unregister_code(KC_LSFT);
          unregister_code(KC_LCTL);
        }
        return false;
      }
      return true;
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

void tapdance_oneach (qk_tap_dance_state_t *state, void *user_data) {
  int id = (int)user_data;
  tri_layer_action action = tri_layer_actions[id];

  if (action.use_instant_layer && state->pressed) {
    layer_on(action.single_hold);
  }
}

void tapdance_onfinished (qk_tap_dance_state_t *state, void *user_data) {
  int id = (int)user_data;
  tap_states[id].state = cur_dance(state);
  tri_layer_action action = tri_layer_actions[id];

  switch (tap_states[id].state) {
    case SINGLE_TAP: register_code(action.single_tap); break;
    case SINGLE_HOLD: layer_on(action.single_hold); break;
    case DOUBLE_TAP: {
      if (action.is_double_tap_layer_lock) {
        layer_on(action.double_tap);
      } else {
        register_code(action.double_tap);
      }
      break;
    }
  }
}

void tapdance_onreset (qk_tap_dance_state_t *state, void *user_data) {
  int id = (int)user_data;
  tri_layer_action action = tri_layer_actions[id];

  switch (tap_states[id].state) {
    case SINGLE_TAP: unregister_code(action.single_tap); break;
    case SINGLE_HOLD: layer_off(action.single_hold); break;
    case DOUBLE_TAP: {
      if (action.is_double_tap_layer_lock) {
      } else {
        unregister_code(action.double_tap);
      }
      break;
    }
  }

  if (action.use_instant_layer) {
    layer_off(action.single_hold);
  }

  tap_states[id].state = 0;
}
