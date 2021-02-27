/*
 * path:   /home/klassiker/.local/share/repos/zenith-xt-usb/unimap_plain.c
 * author: klassiker [mrdotx]
 * github: https://github.com/mrdotx/zenith-usb
 * date:   2021-02-27T20:41:34+0100
 */

#include "unimap_trans.h"

#define AC_T1  ACTION_LAYER_TOGGLE(1)
#define AC_LT1 ACTION_LAYER_TAP_KEY(1, KC_TAB)
#define AC_LT2 ACTION_LAYER_TAP_KEY(2, KC_INS)

#ifdef KEYMAP_SECTION_ENABLE
const action_t actionmaps[][UNIMAP_ROWS][UNIMAP_COLS] __attribute__ ((section (".keymap.keymaps"))) = {
#else
const action_t actionmaps[][UNIMAP_ROWS][UNIMAP_COLS] PROGMEM = {
#endif
    UNIMAP(
              NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,
    ESC,      F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, NO,  NO,            NO,  MUTE,NO,             NO,  NO,  NO,
    GRV, 1,   2,   3,   4,   5,   6,   7,   8,   9,   0,   MINS,EQL, NO,  BSPC,     NO,  NO,  NO,      T1,    NO,PSCR,VOLD,
    LT1, Q,   W,   E,   R,   T,   Y,   U,   I,   O,   P,   LBRC,RBRC,     LGUI,     NO,  NO,  NO,      HOME,  UP,PGUP,VOLU,
    CAPS,A,   S,   D,   F,   G,   H,   J,   K,   L,   SCLN,QUOT,     NO,  ENT,                         LEFT,DOWN,RGHT,NO,
    LSFT,NO,  Z,   X,   C,   V,   B,   N,   M,   COMM,DOT, SLSH,     NO,  RSFT,          NO,           END, PAUS,PGDN,NO,
    LCTL,NO  ,LALT,NO,            SPC,           NO,  NO,  NO  ,NO  ,NO,  NO,       NO,  NO,  NO,           LT2, DEL, NO
    ),
    /* function keys and num pad with tab key TAB(LT1) and layer toggle NUM LOCK(T1) */
    UNIMAP(
              NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,
    TRNS,     F11, F12, F13, F14, F15, F16, F17, F18, F19, F20, NO,  NO,            NO,  SLCK,NO,           NO,  NO,  NO,
    RGUI,P1,  P2,  P3,  P4,  P5,  P6,  P7,  P8,  P9,  P0,  TRNS,TRNS,NO,  TRNS,     NO,  NO,  NO,      TRNS,NO,  PAST,PMNS,
    TAB, TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,     BSLS,     NO,  NO,  NO,      7,   8,   9,   PPLS,
    BTLD,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,     NO,  TRNS,                        4,   5,   6,   NO,
    TRNS,NO,  TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,PDOT,TRNS,     NO,  TRNS,          NO,           1,   2,   3,   NO,
    TRNS,NO,  TRNS,NO,            TRNS,          NO,  NO  ,NO,  NO,  NO,  NO,       NO,  NO,  NO,           0,   DOT, NO
    ),
    /* mouse functions with tap key INS(LT2) */
    UNIMAP(
              NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,
    TRNS,     TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,NO,  NO,            NO,  TRNS,NO,           NO,  NO,  NO,
    TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,NO,  TRNS,     NO,  NO,  NO,      TRNS,NO,  TRNS,WH_U,
    TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,     TRNS,     NO,  NO,  NO,      BTN2,MS_U,BTN3,WH_D,
    TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,     NO,  TRNS,                        MS_L,MS_D,MS_R,NO,
    TRNS,NO,  TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,     NO,  TRNS,          NO,           BTN1,WH_L,WH_R,NO,
    TRNS,NO,  TRNS,NO,            TRNS,          NO,  NO  ,NO,  NO,  NO,  NO,       NO,  NO,  NO,           TRNS,TRNS,NO
    ),
};
