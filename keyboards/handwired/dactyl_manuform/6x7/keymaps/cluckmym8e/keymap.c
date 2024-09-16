#include QMK_KEYBOARD_H


#define _QWERTY 0
#define _LOWER 1
#define _RAISE 2

#define RAISE MO(_RAISE)
#define LOWER MO(_LOWER)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTY] = LAYOUT_6x7(

             KC_MUTE,KC_VOLD,KC_VOLU,KC_MPRV,KC_MPLY,KC_MNXT,                KC_LBRC,KC_RBRC,KC_BSLS,KC_GRV ,KC_INS ,KC_PGDN,KC_PGUP,
             KC_ESC , KC_1  , KC_2  , KC_3  , KC_4  , KC_5  ,                KC_6   , KC_7  , KC_8  , KC_9  , KC_0  ,KC_SCLN,KC_DEL ,
             KC_CAPS, KC_Q  , KC_W  , KC_E  , KC_R  , KC_T  ,                KC_Y   , KC_U  , KC_I  , KC_O  , KC_P  ,KC_EQL ,KC_BSPC,
             KC_TAB , KC_A  , KC_S  , KC_D  , KC_F  , KC_G  ,                KC_H   , KC_J  , KC_K  , KC_L  ,KC_QUOT,KC_MINS,KC_ENT ,
             KC_LSFT, KC_Z  , KC_X  , KC_C  , KC_V  , KC_B  ,                KC_N   , KC_M  ,KC_COMM,KC_DOT ,KC_SLSH, KC_UP ,KC_MENU,
             KC_LCTL,KC_LWIN,A(KC_PSCR),KC_TAB,KC_NO, KC_NO ,                KC_MUTE,KC_MPLY,KC_HOME,KC_END ,KC_LEFT,KC_DOWN,KC_RGHT,
                                            KC_LSFT ,KC_SPC ,                KC_SPC ,KC_RSFT, 
                                            KC_LALT ,KC_LCTL,                KC_BSPC,MO(_LOWER),
                                            KC_F3,MO(_RAISE),                KC_ENT ,KC_DEL, KC_NO
  ),

  [_LOWER] = LAYOUT_6x7(

             _______,_______,_______,_______,_______,_______,                         _______,_______,_______,_______,_______,_______,_______,
             _______,_______,_______,_______,_______,_______,                         _______,_______,_______,_______,_______,_______,_______,
	     _______, KC_F1 , KC_F2 , KC_F3 , KC_F4 , KC_F5 ,                          KC_F6 , KC_F7 , KC_F8 , KC_F9 ,KC_F10 ,_______,_______,
             _______, KC_1  , KC_2  , KC_3  , KC_4  , KC_5  ,                          KC_6  , KC_7  , KC_8  , KC_9  , KC_0  ,_______,_______,
             _______, KC_F11 ,KC_F12,_______,_______,_______,                         _______,_______,_______,_______,_______,_______,_______,
             _______,_______,_______,_______,_______,_______,                         _______,_______,_______,_______,_______,_______,_______,
                                             _______,_______,                 _______,_______,
                                             _______,_______,                 _______,_______,
                                             _______,_______,                 _______,_______,_______
  ),

  [_RAISE] = LAYOUT_6x7(

             _______,_______,_______,_______,_______,_______,                         _______,_______,_______,_______,_______,_______, RESET ,
             _______,_______,_______,_______,_______,_______,                         _______,_______,_______,_______,_______,_______,_______,
             _______,KC_ACL2,_______,KC_WH_L,KC_MS_U,KC_WH_R,                         KC_WH_U,KC_HOME, KC_UP ,KC_END ,_______,_______,_______,
             _______,KC_ACL1,_______,KC_MS_L,KC_MS_D,KC_MS_R,                         KC_WH_D,KC_LEFT,KC_DOWN,KC_RGHT,_______,_______,_______,
             _______,KC_ACL0,_______,KC_BTN1,KC_BTN3,KC_BTN2,                         _______,_______,_______,_______,_______,_______,_______,
             _______,_______,_______,_______,_______,_______,                         _______,_______,_______,_______,_______,_______,_______,
                                             _______,_______,                 _______,_______,
                                             _______,_______,                 _______,_______,
                                             _______,_______,                 _______,_______,_______

  )

};

#ifdef ENCODER_ENABLE
void encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        if (clockwise) {
             tap_code(KC_MNXT);
        } else {
	     tap_code(KC_MPRV);
	       }
// } // experimental syntax, didn't compile
  } else if (index == 1) { /* Second encoder */
    if (clockwise) {
      tap_code(KC_VOLU);
    } else {
      tap_code(KC_VOLD);
    }
// experimental syntax, didn't compile
} else if (index == 2) { /* Third encoder */
    if (clockwise) {
      tap_code(KC_BRIU);
    } else {
      tap_code(KC_BRID);
    }
  }
}
#endif

#ifdef OLED_DRIVER_ENABLE
void oled_task_user(void) {
    // Host Keyboard Layer Status
    oled_write_P(PSTR("Layer: "), false);

    switch (get_highest_layer(layer_state)) {
        case _QWERTY:
            oled_write_P(PSTR("ALPHA\n"), false);
            break;
        case _RAISE:
            oled_write_P(PSTR("NAVI\n"), false);
            break;
        case _LOWER:
            oled_write_P(PSTR("NUMFUN\n"), false);
            break;
        default:
            // Or use the write_ln shortcut over adding '\n' to the end of your string
            oled_write_ln_P(PSTR("Undefined"), false);
    }

    // Host Keyboard LED Status
    led_t led_state = host_keyboard_led_state();
    oled_write_P(led_state.num_lock ? PSTR("NUM ") : PSTR("    "), false);
    oled_write_P(led_state.caps_lock ? PSTR("CAP ") : PSTR("    "), false);
    oled_write_P(led_state.scroll_lock ? PSTR("SCR ") : PSTR("    "), false);
}
#endif