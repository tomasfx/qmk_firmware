/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>

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

extern keymap_config_t keymap_config;

#ifdef OLED_DRIVER_ENABLE
static uint32_t oled_timer = 0;
#endif

extern uint8_t is_master;

#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

enum layer_names {
  _QWERTY,
  _LOWER,
  _RAISE,
  _ADJUST
};

enum planck_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  ADJUST
};

// Adding macros to make the keymaps below much easier to read.
#define GRVLCTL LCTL_T(KC_GRV)
#define QUOTRCTL RCTL_T(KC_QUOT)
#define TABLGUI LGUI_T(KC_TAB)
#define MINSRGUI RGUI_T(KC_MINS)
#define SPCLSFT LSFT_T(KC_SPC)
#define DELRSFT RSFT_T(KC_BSPC)
#define ZALT ALT_T(KC_Z)
#define SLSHALT ALT_T(KC_SLSH)
#define XRALT RALT_T(KC_X)
#define DOTRALT RALT_T(KC_DOT)
#define BSLSLSIFT LSFT(KC_BSLS)
#define LOWER LT(_LOWER, KC_ESC)
#define RAISE LT(_RAISE, KC_ENT)
#define ZCTRL LCTL(KC_Z)
#define XCTRL LCTL(KC_X)
#define CCTRL LCTL(KC_C)
#define VCTRL LCTL(KC_V)
#define ACTRL LCTL(KC_A)
#define SCTRL LCTL(KC_S)
#define DCTRL LCTL(KC_D)
#define FCTRL LCTL(KC_F)
#define GCTRL LCTL(KC_G)
#define FLGUI LGUI(KC_1)
#define SLGUI LGUI(KC_2)
#define THLGUI LGUI(KC_3)
#define FOLGUI LGUI(KC_4)
#define FVLGUI LGUI(KC_5)
#define SXLGUI LGUI(KC_6)
#define SVLGUI LGUI(KC_7)
#define ELGUI LGUI(KC_8)
#define NLGUI LGUI(KC_9)
#define FLSFT LSFT(KC_1)
#define SLSFT LSFT(KC_2)
#define THSFT LSFT(KC_3)
#define FOSFT LSFT(KC_4)
#define FVSFT LSFT(KC_5)
#define SXSFT LSFT(KC_6)
#define SVSFT LSFT(KC_7)
#define ESFT LSFT(KC_8)
#define NSFT LSFT(KC_9)
#define CSFT LSFT(KC_0)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
     KC_LBRC,  KC_Q,     KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,   KC_RBRC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     GRVLCTL,   KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                         KC_H,    KC_J,    KC_K,    KC_L,  KC_SCLN,  QUOTRCTL,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     KC_LSPO,   ZALT,    XRALT,   KC_C,    KC_V,    KC_B,                         KC_N,    KC_M,  KC_COMMA, DOTRALT, SLSHALT, KC_RSPC,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                         TABLGUI,   LOWER, SPCLSFT,     DELRSFT,  RAISE, MINSRGUI
                                      //`--------------------------'  `--------------------------'

  ),

  [_LOWER] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      KC_BRID,  FLGUI,   SLGUI,  THLGUI,  FOLGUI,  FVLGUI,                       SXLGUI,  SVLGUI,  ELGUI,   NLGUI,  KC_PSCR,  KC_BRIU,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      CG_TOGG, ACTRL,   SCTRL,   DCTRL,   FCTRL,   GCTRL,                        KC_LEFT, KC_DOWN,  KC_UP, KC_RIGHT, KC_HOME, KC_END,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_CAPS, ZCTRL,   XCTRL,   CCTRL,   VCTRL,   KC_APP,                       KC_MPRV, KC_MPLY, KC_MNXT, KC_MUTE, KC_VOLD, KC_VOLU,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                         TABLGUI, KC_TRNS, SPCLSFT,    DELRSFT,  KC_DEL, MINSRGUI
                                      //`--------------------------'  `--------------------------'
  ),

  [_RAISE] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
    BSLSLSIFT,  FLSFT,  SLSFT,   THSFT,   FOSFT,    FVSFT,                       SXSFT,    SVSFT,   ESFT,    NSFT,    CSFT,  KC_BSLS,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     KC_MINS,  KC_1,    KC_2,    KC_3,     KC_4,    KC_5,                        KC_6,    KC_7,    KC_8,    KC_9,    KC_0,   KC_EQL,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_F12, KC_F1,   KC_F2,   KC_F3,    KC_F4,   KC_F5,                        KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          TABLGUI,  LOWER, SPCLSFT,    DELRSFT, KC_TRNS, MINSRGUI
                                      //`--------------------------'  `--------------------------'
  ),

  [_ADJUST] = LAYOUT(
  //|-----------------------------------------------------|                    |-----------------------------------------------------|
     XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, RGB_TOG,                       XXXXXXX, XXXXXXX,  XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     XXXXXXX, RGB_HUI, RGB_SAI, RGB_VAI, RGB_SPI, RGB_MOD,                       XXXXXXX, XXXXXXX,  XXXXXXX,   XXXXXXX,   XXXXXXX,   RESET,  \
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     XXXXXXX, RGB_HUD, RGB_SAD, RGB_VAD, RGB_SPD, XXXXXXX,                        XXXXXXX, XXXXXXX,  XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,\
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                         KC_LCTL, KC_TRNS, KC_SPC,    KC_SPC, KC_TRNS, KC_RALT \
                                      //|--------------------------|  |--------------------------|
  )
};

int RGB_current_mode;

// Setting ADJUST layer RGB back to default
void update_tri_layer_RGB(uint8_t layer1, uint8_t layer2, uint8_t layer3) {
  if (IS_LAYER_ON(layer1) && IS_LAYER_ON(layer2)) {
    layer_on(layer3);
  } else {
    layer_off(layer3);
  }
}

void matrix_init_user(void) {
    #ifdef RGBLIGHT_ENABLE
      RGB_current_mode = rgblight_config.mode;
    #endif
}

void rgb_matrix_indicators_user(void) {
  #ifdef RGB_MATRIX_ENABLE
  switch (biton32(layer_state)) {
    case _RAISE:
      for (int i = 0; i < DRIVER_LED_TOTAL; i++) {
          rgb_matrix_set_color(i, 255, 0, 0);
      }
      break;

    case _LOWER:
      for (int i = 0; i < DRIVER_LED_TOTAL; i++) {
         rgb_matrix_set_color(i, 0, 0, 255);
      }
      break;

    default:
        if (host_keyboard_leds() & (1<<USB_LED_CAPS_LOCK)) {
        for (int i = 0; i < DRIVER_LED_TOTAL; i++) {
          rgb_matrix_set_color(i, 0, 255, 0);
      }
       }
      break;
  }
  #endif
}

#ifdef OLED_DRIVER_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) { return OLED_ROTATION_270; }

void render_space(void) {
    oled_write_P(PSTR("     "), false);
}

void render_mod_status_gui_alt(uint8_t modifiers) {
    static const char PROGMEM gui_off_1[] = {0x85, 0x86, 0};
    static const char PROGMEM gui_off_2[] = {0xa5, 0xa6, 0};
    static const char PROGMEM gui_on_1[] = {0x8d, 0x8e, 0};
    static const char PROGMEM gui_on_2[] = {0xad, 0xae, 0};

    static const char PROGMEM alt_off_1[] = {0x87, 0x88, 0};
    static const char PROGMEM alt_off_2[] = {0xa7, 0xa8, 0};
    static const char PROGMEM alt_on_1[] = {0x8f, 0x90, 0};
    static const char PROGMEM alt_on_2[] = {0xaf, 0xb0, 0};

    // fillers between the modifier icons bleed into the icon frames
    static const char PROGMEM off_off_1[] = {0xc5, 0};
    static const char PROGMEM off_off_2[] = {0xc6, 0};
    static const char PROGMEM on_off_1[] = {0xc7, 0};
    static const char PROGMEM on_off_2[] = {0xc8, 0};
    static const char PROGMEM off_on_1[] = {0xc9, 0};
    static const char PROGMEM off_on_2[] = {0xca, 0};
    static const char PROGMEM on_on_1[] = {0xcb, 0};
    static const char PROGMEM on_on_2[] = {0xcc, 0};

    if(modifiers & MOD_MASK_GUI) {
        oled_write_P(gui_on_1, false);
    } else {
        oled_write_P(gui_off_1, false);
    }

    if ((modifiers & MOD_MASK_GUI) && (modifiers & MOD_MASK_ALT)) {
        oled_write_P(on_on_1, false);
    } else if(modifiers & MOD_MASK_GUI) {
        oled_write_P(on_off_1, false);
    } else if(modifiers & MOD_MASK_ALT) {
        oled_write_P(off_on_1, false);
    } else {
        oled_write_P(off_off_1, false);
    }

    if(modifiers & MOD_MASK_ALT) {
        oled_write_P(alt_on_1, false);
    } else {
        oled_write_P(alt_off_1, false);
    }

    if(modifiers & MOD_MASK_GUI) {
        oled_write_P(gui_on_2, false);
    } else {
        oled_write_P(gui_off_2, false);
    }

    if (modifiers & MOD_MASK_GUI & MOD_MASK_ALT) {
        oled_write_P(on_on_2, false);
    } else if(modifiers & MOD_MASK_GUI) {
        oled_write_P(on_off_2, false);
    } else if(modifiers & MOD_MASK_ALT) {
        oled_write_P(off_on_2, false);
    } else {
        oled_write_P(off_off_2, false);
    }

    if(modifiers & MOD_MASK_ALT) {
        oled_write_P(alt_on_2, false);
    } else {
        oled_write_P(alt_off_2, false);
    }
}

void render_mod_status_ctrl_shift(uint8_t modifiers) {
    static const char PROGMEM ctrl_off_1[] = {0x89, 0x8a, 0};
    static const char PROGMEM ctrl_off_2[] = {0xa9, 0xaa, 0};
    static const char PROGMEM ctrl_on_1[] = {0x91, 0x92, 0};
    static const char PROGMEM ctrl_on_2[] = {0xb1, 0xb2, 0};

    static const char PROGMEM shift_off_1[] = {0x8b, 0x8c, 0};
    static const char PROGMEM shift_off_2[] = {0xab, 0xac, 0};
    static const char PROGMEM shift_on_1[] = {0xcd, 0xce, 0};
    static const char PROGMEM shift_on_2[] = {0xcf, 0xd0, 0};

    // fillers between the modifier icons bleed into the icon frames
    static const char PROGMEM off_off_1[] = {0xc5, 0};
    static const char PROGMEM off_off_2[] = {0xc6, 0};
    static const char PROGMEM on_off_1[] = {0xc7, 0};
    static const char PROGMEM on_off_2[] = {0xc8, 0};
    static const char PROGMEM off_on_1[] = {0xc9, 0};
    static const char PROGMEM off_on_2[] = {0xca, 0};
    static const char PROGMEM on_on_1[] = {0xcb, 0};
    static const char PROGMEM on_on_2[] = {0xcc, 0};

    if(modifiers & MOD_MASK_CTRL) {
        oled_write_P(ctrl_on_1, false);
    } else {
        oled_write_P(ctrl_off_1, false);
    }

    if ((modifiers & MOD_MASK_CTRL) && (modifiers & MOD_MASK_SHIFT)) {
        oled_write_P(on_on_1, false);
    } else if(modifiers & MOD_MASK_CTRL) {
        oled_write_P(on_off_1, false);
    } else if(modifiers & MOD_MASK_SHIFT) {
        oled_write_P(off_on_1, false);
    } else {
        oled_write_P(off_off_1, false);
    }

    if(modifiers & MOD_MASK_SHIFT) {
        oled_write_P(shift_on_1, false);
    } else {
        oled_write_P(shift_off_1, false);
    }

    if(modifiers & MOD_MASK_CTRL) {
        oled_write_P(ctrl_on_2, false);
    } else {
        oled_write_P(ctrl_off_2, false);
    }

    if (modifiers & MOD_MASK_CTRL & MOD_MASK_SHIFT) {
        oled_write_P(on_on_2, false);
    } else if(modifiers & MOD_MASK_CTRL) {
        oled_write_P(on_off_2, false);
    } else if(modifiers & MOD_MASK_SHIFT) {
        oled_write_P(off_on_2, false);
    } else {
        oled_write_P(off_off_2, false);
    }

    if(modifiers & MOD_MASK_SHIFT) {
        oled_write_P(shift_on_2, false);
    } else {
        oled_write_P(shift_off_2, false);
    }
}

void render_logo(void) {
    static const char PROGMEM corne_logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84,
        0xa0, 0xa1, 0xa2, 0xa3, 0xa4,
        0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0};
    oled_write_P(corne_logo, false);
    oled_write_P(PSTR("corne"), false);
}

void render_layer_state(void) {
    static const char PROGMEM default_layer[] = {
        0x20, 0x94, 0x95, 0x96, 0x20,
        0x20, 0xb4, 0xb5, 0xb6, 0x20,
        0x20, 0xd4, 0xd5, 0xd6, 0x20, 0};
    static const char PROGMEM raise_layer[] = {
        0x20, 0x97, 0x98, 0x99, 0x20,
        0x20, 0xb7, 0xb8, 0xb9, 0x20,
        0x20, 0xd7, 0xd8, 0xd9, 0x20, 0};
    static const char PROGMEM lower_layer[] = {
        0x20, 0x9a, 0x9b, 0x9c, 0x20,
        0x20, 0xba, 0xbb, 0xbc, 0x20,
        0x20, 0xda, 0xdb, 0xdc, 0x20, 0};
    if(layer_state_is(_LOWER)) {
        oled_write_P(lower_layer, false);
    } else if(layer_state_is(_RAISE)) {
        oled_write_P(raise_layer, false);
    } else {
        oled_write_P(default_layer, false);
    }
}

void render_status_main(void) {
    render_logo();
    render_space();
    render_layer_state();
    render_space();
    render_mod_status_gui_alt(get_mods()|get_oneshot_mods());
    render_mod_status_ctrl_shift(get_mods()|get_oneshot_mods());
}

void render_status_secondary(void) {
    render_logo();
    render_space();
    render_layer_state();
    render_space();
    render_mod_status_gui_alt(get_mods()|get_oneshot_mods());
    render_mod_status_ctrl_shift(get_mods()|get_oneshot_mods());
}

void oled_task_user(void) {
    if (timer_elapsed32(oled_timer) > 300000) {
        oled_off();
        return;
    }
#ifndef SPLIT_KEYBOARD
    else { oled_on(); }
#endif

    if (is_master) {
        render_status_main();  // Renders the current keyboard state (layer, lock, caps, scroll, etc)
    } else {
        render_status_secondary();
    }
}

#endif
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
#ifdef OLED_DRIVER_ENABLE
        oled_timer = timer_read32();
#endif
    // set_timelog();
  }
  return true;
}

#ifdef RGB_MATRIX_ENABLE

void suspend_power_down_user(void) {
    rgb_matrix_set_suspend_state(true);
}

void suspend_wakeup_init_user(void) {
    rgb_matrix_set_suspend_state(false);
}

#endif