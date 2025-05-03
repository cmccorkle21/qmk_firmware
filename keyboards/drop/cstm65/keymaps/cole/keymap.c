#include QMK_KEYBOARD_H
#if __has_include("keymap.h")
#    include "keymap.h"
#endif

// RAW HID layer indicator setup

#define RAW_EPSIZE 32
#include "raw_hid.h"
layer_state_t layer_state_set_user(layer_state_t state) {
    uint8_t layer = get_highest_layer(state);
    uint8_t buf[RAW_EPSIZE] = {0};
    buf[0] = 0x01; // type = 1 means layer update
    buf[1] = layer;
    raw_hid_send(buf, RAW_EPSIZE);
    return state;
}

#include QMK_KEYBOARD_H
#include "rgb_matrix.h"
//lighting
bool rgb_matrix_indicators_user(void) {
    uint8_t layer = get_highest_layer(layer_state);
    if (layer == 1) {
        rgb_matrix_set_color(0, 255, 0, 0);  // index 0, red
    }
    return true;
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
//    ┌──────┬──────┬──────┬───┬───┬───┬───┬───┬───┬───┬───┬───────────┬──────┬─────────────┬──────┐
//    │  `   │  1   │  2   │ 3 │ 4 │ 5 │ 6 │ 7 │ 8 │ 9 │ 0 │     -     │  =   │    bspc     │ del  │
//    ├──────┴──────┼──────┼───┼───┼───┼───┼───┼───┼───┼───┼───────────┼──────┼──────┬──────┼──────┤
//    │     tab     │  q   │ w │ e │ r │ t │ y │ u │ i │ o │     p     │  [   │  ]   │  \   │ home │
//    ├─────────────┼──────┼───┼───┼───┼───┼───┼───┼───┼───┼───────────┼──────┼──────┴──────┼──────┤
//    │ LT(1, esc)  │  a   │ s │ d │ f │ g │ h │ j │ k │ l │     ;     │  '   │     ent     │ pgdn │
//    ├─────────────┼──────┼───┼───┼───┼───┼───┼───┼───┼───┼───────────┼──────┴──────┬──────┼──────┤
//    │   SC_LSPO   │  z   │ x │ c │ v │ b │ n │ m │ , │ . │     /     │   SC_RSPC   │  up  │  b   │
//    ├──────┬──────┼──────┼───┴───┴───┴───┴───┴───┴───┴───┼───────────┼──────┬──────┼──────┼──────┤
//    │ lctl │ lgui │ lalt │              spc              │ OSM(HYPR) │ rctl │ left │ down │ rght │
//    └──────┴──────┴──────┴───────────────────────────────┴───────────┴──────┴──────┴──────┴──────┘
[0] = LAYOUT_65_ansi_blocker(
  KC_GRV  , KC_1    , KC_2    , KC_3 , KC_4 , KC_5 , KC_6 , KC_7 , KC_8 , KC_9    , KC_0   , KC_MINS       , KC_EQL  ,           KC_BSPC , KC_DEL ,
       KC_TAB       , KC_Q    , KC_W , KC_E , KC_R , KC_T , KC_Y , KC_U , KC_I    , KC_O   , KC_P          , KC_LBRC , KC_RBRC , KC_BSLS , KC_HOME,
    LT(1, KC_ESC)   , KC_A    , KC_S , KC_D , KC_F , KC_G , KC_H , KC_J , KC_K    , KC_L   , KC_SCLN       , KC_QUOT ,      KC_ENT       , KC_PGDN,
       SC_LSPO      , KC_Z    , KC_X , KC_C , KC_V , KC_B , KC_N , KC_M , KC_COMM , KC_DOT , KC_SLSH       ,      SC_RSPC      , KC_UP   , KC_B   ,
  KC_LCTL , KC_LGUI , KC_LALT ,                           KC_SPC                           , OSM(MOD_HYPR) , KC_RCTL , KC_LEFT , KC_DOWN , KC_RGHT
),

//    ┌──────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬────────────┬─────┐
//    │ RSET │ f1  │ f2  │ f3  │ f4  │ f5  │ f6  │ f7  │ f8  │ f9  │ f10 │ f11 │ f12 │            │     │
//    ├──────┴─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┬──────┼─────┤
//    │            │     │     │     │     │     │     │  _  │  {  │  }  │  +  │     │     │      │     │
//    ├────────────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┴──────┼─────┤
//    │            │     │     │     │  %  │  ^  │  $  │  -  │  [  │  ]  │  =  │     │  RM_TOGG   │     │
//    ├────────────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┴─────┬──────┼─────┤
//    │            │     │     │     │     │     │     │     │     │     │     │           │ volu │     │
//    ├──────┬─────┼─────┼─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┼─────┼─────┬─────┼──────┼─────┤
//    │      │     │     │                    EE_CLR                     │     │     │     │ vold │     │
//    └──────┴─────┴─────┴───────────────────────────────────────────────┴─────┴─────┴─────┴──────┴─────┘
[1] = LAYOUT_65_ansi_blocker(
  QK_BOOT , KC_F1   , KC_F2   , KC_F3   , KC_F4   , KC_F5   , KC_F6   , KC_F7   , KC_F8   , KC_F9   , KC_F10  , KC_F11  , KC_F12  ,           KC_TRNS , KC_TRNS,
       KC_TRNS      , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_UNDS , KC_LCBR , KC_RCBR , KC_PLUS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS,
       KC_TRNS      , KC_TRNS , KC_TRNS , KC_TRNS , KC_PERC , KC_CIRC , KC_DLR  , KC_MINS , KC_LBRC , KC_RBRC , KC_EQL  , KC_TRNS ,      RM_TOGG      , KC_TRNS,
       KC_TRNS      , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS ,      KC_TRNS      , KC_VOLU , KC_TRNS,
  KC_TRNS , KC_TRNS , KC_TRNS ,                                    EE_CLR                                     , KC_TRNS , KC_TRNS , KC_TRNS , KC_VOLD , KC_TRNS
)
};

#ifdef OTHER_KEYMAP_C
#    include OTHER_KEYMAP_C
#endif // OTHER_KEYMAP_C
