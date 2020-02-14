#include QMK_KEYBOARD_H

#ifdef PROTOCOL_LUFA
  #include "lufa.h"
  #include "split_util.h"
#endif
#ifdef SSD1306OLED
  #include "ssd1306.h"
#endif

// Add headers for raw hid communication
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
#define _TEMPLATE 6

// Shorthand Macros
#define KC_TD(a) TD(TD_##a)
#define KC_TO(a) TO(a)
#define KC_LGZ LGUI_T(KC_Z)
#define KC_LAX LALT_T(KC_X)
#define KC_SHL LSFT_T(KC_LEFT)
#define KC_SHR LSFT_T(KC_RGHT)
#define KC_CET LCTL_T(KC_ENT)
#define KC_CTLL LCTL_T(KC_LEFT)
#define KC_CTLR LCTL_T(KC_RGHT)
#define KC_SDEL LSFT_T(KC_DEL)
#define KC_ASPC LT(_ARROWS,KC_SPC)
#define KC_LSB LSFT_T(KC_BSPC)
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
#define KC_APS SCREENCAP

// Custom keycodes
enum {
  SHIFT_TAB = SAFE_RANGE,
  REDO_NUM_F11,
  SCREENCAP,
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
  TD_SFT,
  TD_DEL
};

static tri_layer_action tri_layer_actions [] = {
  [TD_ENT] = { .single_tap = KC_ENT, .single_hold = _ARROWS, .double_tap = _ARROWS, .is_double_tap_layer_lock = true, .use_instant_layer = false },
  [TD_NUM] = { .single_tap = KC_F11, .single_hold = _NUMPAD, .double_tap = KC_F5, .is_double_tap_layer_lock = false, .use_instant_layer = true  },
  [TD_SPC] = { .single_tap = KC_SPC, .single_hold = _CODING, .double_tap = KC_SPC, .is_double_tap_layer_lock = false, .use_instant_layer = true  },
  [TD_SFT] = { .single_tap = KC_ENT, .single_hold = _CODING, .double_tap = KC_SPC, .is_double_tap_layer_lock = false, .use_instant_layer = true  },
  [TD_DEL] = { .single_tap = KC_DEL, .single_hold = _RGB, .double_tap = _RGB, .is_double_tap_layer_lock = true, .use_instant_layer = false  }
};

static tap tap_states [] = {
  [TD_ENT] = { .is_press_action = true, .state = 0 },
  [TD_NUM] = { .is_press_action = true, .state = 0 },
  [TD_SPC] = { .is_press_action = true, .state = 0 },
  [TD_SFT] = { .is_press_action = true, .state = 0 },
  [TD_DEL] = { .is_press_action = true, .state = 0 }
};

qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_ENT] = { .fn = { tapdance_oneach, tapdance_onfinished, tapdance_onreset }, .user_data = (void*)TD_ENT },
  [TD_NUM] = { .fn = { tapdance_oneach, tapdance_onfinished, tapdance_onreset }, .user_data = (void*)TD_NUM },
  [TD_SPC] = { .fn = { tapdance_oneach, tapdance_onfinished, tapdance_onreset }, .user_data = (void*)TD_SPC },
  [TD_SFT] = { .fn = { tapdance_oneach, tapdance_onfinished, tapdance_onreset }, .user_data = (void*)TD_SFT },
  [TD_DEL] = { .fn = { tapdance_oneach, tapdance_onfinished, tapdance_onreset }, .user_data = (void*)TD_DEL }
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_COLEMAK] = LAYOUT_kc( \
  // .-----------------------------------------.                    .-----------------------------------------.
        ESC,   1,     2,     3,     4,    5,                           6,     7,     8,     9,     0,    BSPC, \
  // |------+------+------+------+------+------|                    |------+------+------+------+------+------|
        TAB,   Q,     W,     F,     P,    B,                           J,     L,     U,     Y,    SCLN,  BSLS, \
  // |------+------+------+------+------+------|                    |------+------+------+------+------+------|
        LSB,   A,     R,     S,     T,    G,                           M,     N,     E,     I,     O,    QUOT, \
  // |------+------+------+------+------+------|-------|    |-------|------+------+------+------+------+------|
        CET,  LGZ,   LAX,    C,     D,    V,   TD(ENT),      TD(DEL),  K,    H,     COMM,   DOT,  SLSH, TO(5), \
  // `-----------------------------------------/-------/    \-------\-----------------------------------------'
                         F10, TD(NUM),TD(SPC), SDEL,            ENT,    ASPC,   TRNS,   TRNS  \
  //                   `------+------+------''------'          '-------''------+------+------'
  ),

  [_CODING] = LAYOUT_kc( \
  // .-----------------------------------------.                    .-----------------------------------------.
      TO(0),   F1,    F2,    F3,    F4,    F5,                         F6,    F7,    F8,    F9,   F10,   F11, \
  // |------+------+------+------+------+------|                    |------+------+------+------+------+------|
       TRNS,  TILD,   DLR,  LCBR,  PPLS,   EQL,                       PIPE,  LCBR,  RCBR,  CIRC,  COLN,  F12, \
  // |------+------+------+------+------+------|                    |------+------+------+------+------+------|
       TRNS,   GRV,   DLR,  ASTR,  PMNS,   GT,                        AMPR,  LPRN,  RPRN,  LBRC,  RBRC,  DQUO, \
  // |------+------+------+------+------+------|-------|    |-------|------+------+------+------+------+------|
       TRNS,  TRNS,  TRNS,  PERC,  UNDS,   LT,   TRNS,        TRNS,   EXLM,   EQL,    LT,    GT,  QUES, TO(0), \
  // `-----------------------------------------/-------/    \-------\-----------------------------------------'
                         TRNS,  TRNS,  TRNS,    TRNS,           TRNS,     TRNS,  TRNS,  TRNS  \
  //                   `------+------+------''------'          '-------''------+------+------'
  ),

  [_ARROWS] = LAYOUT_kc( \
  // .-----------------------------------------.                    .-----------------------------------------.
      TO(0),  TRNS,  TRNS,  TRNS,  TRNS,  TRNS,                       TRNS,  TRNS,  TRNS,  TRNS,  TRNS,  TRNS, \
  // |------+------+------+------+------+------|                    |------+------+------+------+------+------|
       TRNS,  TRNS,  TRNS,  TRNS,  TRNS,  TRNS,                       TRNS,  CTLL,   UP,   CTLR,  TRNS,  TRNS, \
  // |------+------+------+------+------+------|                    |------+------+------+------+------+------|
       TRNS,  TRNS,  TRNS,  TRNS,  TRNS,  TRNS,                       HOME,  LEFT,  DOWN,  RGHT,   END,  TRNS, \
  // |------+------+------+------+------+------|-------|    |-------|------+------+------+------+------+------|
       TRNS,  TRNS,  TRNS,  TRNS,  TRNS,  TRNS,  TRNS,        TRNS,   TRNS,   SHL,  TRNS,   SHR,  TRNS, TO(1), \
  // `-----------------------------------------/-------/    \-------\-----------------------------------------'
                         TRNS,  TRNS,  TRNS,    TRNS,             TRNS,   TRNS,  PSCR,  APS  \
  //                   `------+------+------''------'          '-------''------+------+------'
  ),

  [_NUMPAD] = LAYOUT_kc( \
  // .-----------------------------------------.                    .-----------------------------------------.
      TO(0),  TRNS,  TRNS,  TRNS,  TRNS,  TRNS,                       TRNS,  TRNS,  PSLS,  PAST,  PMNS,  TRNS, \
  // |------+------+------+------+------+------|                    |------+------+------+------+------+------|
       TRNS,  TRNS,  TRNS,  TRNS,  TRNS,  TRNS,                       TRNS,    P7,    P8,    P9,  PPLS,  TRNS, \
  // |------+------+------+------+------+------|                    |------+------+------+------+------+------|
       TRNS,  TRNS,  TRNS,  TRNS,  TRNS,  TRNS,                       TRNS,    P4,    P5,    P6,  PCMM,  TRNS, \
  // |------+------+------+------+------+------|-------|    |-------|------+------+------+------+------+------|
       TRNS,  TRNS,  TRNS,  TRNS,  TRNS,  TRNS,  TRNS,        TRNS,   TRNS,    P1,    P2,    P3,   EQL, TO(2), \
  // `-----------------------------------------/-------/    \-------\-----------------------------------------'
                         TRNS,  TRNS,  TRNS,    TRNS,             TRNS,     P0,  PDOT,  TRNS  \
  //                   `------+------+------''------'          '-------''------+------+------'
  ),

  [_RGB] = LAYOUT_kc( \
  // .-----------------------------------------.                    .-----------------------------------------.
      TO(0),  TRNS,  TRNS,  TRNS,  TRNS,  TRNS,                       TRNS,  TRNS,  TRNS,  TRNS,  TRNS,  TRNS, \
  // |------+------+------+------+------+------|                    |------+------+------+------+------+------|
       TRNS,  TRNS,  TRNS,  TRNS,  TRNS,  TRNS,                        RTG,   RHI,   RHD,  TRNS,  TRNS,  TRNS, \
  // |------+------+------+------+------+------|                    |------+------+------+------+------+------|
       TRNS,  TRNS,  TRNS,  TRNS,  TRNS,  TRNS,                        RMI,   RSI,   RSD,  TRNS,  TRNS,  TRNS, \
  // |------+------+------+------+------+------|-------|    |-------|------+------+------+------+------+------|
       TRNS,  TRNS,  TRNS,  TRNS,  TRNS,  TRNS,  TRNS,        TRNS,    RMD,   RVI,   RVD,  TRNS,  TRNS, TO(3), \
  // `-----------------------------------------/-------/    \-------\-----------------------------------------'
                         TRNS,  TRNS,  TRNS,    TRNS,             TRNS,   TRNS,  TRNS,  TRNS  \
  //                   `------+------+------''------'          '-------''------+------+------'
  ),

  [_GAMING] = LAYOUT_kc( \
  // .-----------------------------------------.                    .-----------------------------------------.
       ESC,  TRNS,  TRNS,  TRNS,  TRNS,  TRNS,                       TRNS,  TRNS,  TRNS,  TRNS,  TRNS,  TRNS, \
  // |------+------+------+------+------+------|                    |------+------+------+------+------+------|
       TRNS,    Q,    W,     E,     R,     T,                        TRNS,  TRNS,  TRNS,  TRNS,  TRNS,  TRNS, \
  // |------+------+------+------+------+------|                    |------+------+------+------+------+------|
       TRNS,    A,     S,     D,    F,     G,                        TRNS,  TRNS,  TRNS,  TRNS,  TRNS,  TRNS, \
  // |------+------+------+------+------+------|-------|    |-------|------+------+------+------+------+------|
       TRNS,  TRNS,  TRNS,  TRNS,   V,     B,   TRNS,        TRNS,   TRNS,  TRNS,  TRNS,  TRNS,  TRNS, TO(4), \
  // `-----------------------------------------/-------/    \-------\-----------------------------------------'
                         TRNS,  TRNS,  SPC,    TRNS,             TRNS,   TRNS,  TRNS,  TRNS  \
  //                   `------+------+------''------'          '-------''------+------+------'
  ),

  [_TEMPLATE] = LAYOUT_kc( \
  // .-----------------------------------------.                    .-----------------------------------------.
      TO(0),  TRNS,  TRNS,  TRNS,  TRNS,  TRNS,                       TRNS,  TRNS,  TRNS,  TRNS,  TRNS,  TRNS, \
  // |------+------+------+------+------+------|                    |------+------+------+------+------+------|
       TRNS,  TRNS,  TRNS,  TRNS,  TRNS,  TRNS,                       TRNS,  TRNS,  TRNS,  TRNS,  TRNS,  TRNS, \
  // |------+------+------+------+------+------|                    |------+------+------+------+------+------|
       TRNS,  TRNS,  TRNS,  TRNS,  TRNS,  TRNS,                       TRNS,  TRNS,  TRNS,  TRNS,  TRNS,  TRNS, \
  // |------+------+------+------+------+------|-------|    |-------|------+------+------+------+------+------|
       TRNS,  TRNS,  TRNS,  TRNS,  TRNS,  TRNS,  TRNS,        TRNS,   TRNS,  TRNS,  TRNS,  TRNS,  TRNS,  TRNS, \
  // `-----------------------------------------/-------/    \-------\-----------------------------------------'
                         TRNS,  TRNS,  TRNS,    TRNS,             TRNS,   TRNS,  TRNS,  TRNS  \
  //                   `------+------+------''------'          '-------''------+------+------'
  ),
};

int RGB_current_mode;
const char *read_logo(void);

void matrix_init_user(void) {
    iota_gfx_init(false);
}

void matrix_scan_user(void) {
   iota_gfx_task();
}

// HID input
bool is_hid_connected = false; // Flag indicating if we have a PC connection yet
uint8_t screen_max_count = 0;  // Number of info screens we can scroll through (set by connecting node script)
uint8_t screen_show_index = 0; // Current index of the info screen we are displaying
uint8_t screen_data_buffer[SERIAL_SCREEN_BUFFER_LENGTH - 1] =  {0}; // Buffer used to store the screen data sent by connected node script
int screen_data_index = 0; // Current index into the screen_data_buffer that we should write to

void raw_hid_send_screen_index(void) {
  // Send the current info screen index to the connected node script so that it can pass back the new data
  uint8_t send_data[32] = {0};
  send_data[0] = screen_show_index + 1; // Add one so that we can distinguish it from a null byte
  raw_hid_send(send_data, sizeof(send_data));
}

void raw_hid_receive(uint8_t *data, uint8_t length) {
  // PC connected, so set the flag to show a message on the master display
  is_hid_connected = true;

  // Initial connections use '1' in the first byte to indicate this
  if (length > 1 && data[0] == 1) {
    // New connection so restart screen_data_buffer
    screen_data_index = 0;

    // The second byte is the number of info screens the connected node script allows us to scroll through
    screen_max_count = data[1];
    if (screen_show_index >= screen_max_count) {
      screen_show_index = 0;
    }

    // Tell the connection which info screen we want to look at initially
    raw_hid_send_screen_index();
    return;
  }

  // Otherwise the data we receive is one line of the screen to show on the display
  if (length >= 21) {
    // Copy the data into our buffer and increment the number of lines we have got so far
    memcpy((char*)&screen_data_buffer[screen_data_index * 21], data, 21);
    screen_data_index++;

    // Once we reach 4 lines, we have a full screen
    if (screen_data_index == 4) {
      // Reset the buffer back to receive the next full screen data
      screen_data_index = 0;

      // Now get ready to transfer the whole 4 lines to the slave side of the keyboard.
      // First clear the transfer buffer with spaces just in case.
      memset((char*)&serial_slave_screen_buffer[0], ' ', sizeof(serial_slave_screen_buffer));

      // Copy in the 4 lines of screen data, but start at index 1, we use index 0 to indicate a connection in the slave code
      memcpy((char*)&serial_slave_screen_buffer[1], screen_data_buffer, sizeof(screen_data_buffer));

      // Set index 0 to indicate a connection has been established
      serial_slave_screen_buffer[0] = 1;

      // Make sure to zero terminate the buffer
      serial_slave_screen_buffer[sizeof(serial_slave_screen_buffer) - 1] = 0;

      // Indicate that the screen data has changed and needs transferring to the slave side
      hid_screen_change = true;
    }
  }
}

// Screen printing
char layer_state_str[20];
const char *write_layer(void) {
  // Print the layer name for the current layer
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
  // Print the current rgb values
  snprintf(rbf_info_str, sizeof(rbf_info_str), "%s: %02d h%03d s%03d v%03d",
    rgblight_config.enable ? "\x02A" : "-", rgblight_config.mode,
    rgblight_config.hue, rgblight_config.sat, rgblight_config.val);
  return rbf_info_str;
}

char hid_info_str[20];
const char *write_hid(void) {
  snprintf(hid_info_str, sizeof(hid_info_str), "%s", is_hid_connected ? "connected." : " ");
  return hid_info_str;
}

void write_slave_info_screen(struct CharacterMatrix *matrix) {
  if (serial_slave_screen_buffer[0] > 0) {
    // If the first byte of the buffer is non-zero we should have a full set of data to show,
    // So we copy it into the display
    matrix_write(matrix, (char*)serial_slave_screen_buffer + 1);
  } else {
    // Otherwise we just draw the logo
    matrix_write_ln(matrix, "");
    matrix_write(matrix, read_logo());
  }
}

void matrix_render_user(struct CharacterMatrix *matrix) {
  if (is_master) {
    // Show layer and rgb values on the master side
    matrix_write_ln(matrix, write_layer());
    matrix_write_ln(matrix, " ");
    matrix_write_ln(matrix, write_rgb());
    matrix_write(matrix, write_hid()); // Add if we have a connection established
  } else {
    // Show the logo or screen info on the slave side
    write_slave_info_screen(matrix);
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

// RGB Lighting
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

// Custom keys
bool is_ctrl_tabbing = false;
bool is_ctrl_f10 = false;
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

    case KC_TAB: {
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

    case KC_F10: {
      const uint8_t is_ctrl = (get_mods() & (MOD_BIT(KC_LCTL) | MOD_BIT(KC_RCTL)));
      if (record->event.pressed) {
        if (is_ctrl) {
          // CTRL + F10 is converted into CTRL + Y (Redo)
          is_ctrl_f10 = true;
          register_code(KC_Y);
          return false;
        }
      } else {
        if (is_ctrl_f10) {
          // Turn off the CTRL + Y (Redo)
          is_ctrl_f10 = false;
          unregister_code(KC_Y);
          return false;
        }
      }

      return true;
    }

    case SCREENCAP: {
      if (record->event.pressed) {
        // Use ALT + PrintScreen to only capture the focused window
        register_code(KC_LALT);
        tap_code(KC_PSCR);
        unregister_code(KC_LALT);
        return false;
      }

      return true;
    }
  }

  return true;
}

// Rotary Encoder
void encoder_update_user(uint8_t index, bool clockwise) {
  switch (biton32(layer_state)) {
    case _RGB: {
      // On the RGB layer we control the screen display with the encoder
      if (clockwise) {
        // Increment and loop back to beginning if we go over the max
        screen_show_index++;
        if (screen_show_index >= screen_max_count) {
          screen_show_index = 0;
        }
      } else {
        // Decrement and loop back to the end if we are about to go below zero,
        // Be careful since index is unsigned.
        if (screen_show_index == 0) {
          screen_show_index = screen_max_count - 1;
        } else {
          screen_show_index--;
        }
      }

      // If we have a connection we should tell it about the change,
      // Otherwise it will be notified when it first connects instead.
      if (is_hid_connected) {
        raw_hid_send_screen_index();
      }
      break;
    }

    case _ARROWS: {
      // ALT + LEFT and ALT + RIGHT (Forward/Back in vs/code) on Arrow layer
      if (clockwise) {
        register_code(KC_LALT);
				tap_code(KC_LEFT);
				unregister_code(KC_LALT);
      } else {
        register_code(KC_LALT);
				tap_code(KC_RIGHT);
				unregister_code(KC_LALT);
      }
      break;
    }

    default: {
      // ALT + UP and ALT + DOWN (Move line in vs/code) on all layers
      if (clockwise) {
        register_code(KC_LALT);
				tap_code(KC_UP);
				unregister_code(KC_LALT);
      } else {
        register_code(KC_LALT);
				tap_code(KC_DOWN);
				unregister_code(KC_LALT);
      }
      break;
    }
  }
}

// Tap Dance
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
