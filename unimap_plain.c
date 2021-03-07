/*
 * path:   /home/klassiker/.local/share/repos/zenith-xt-usb/unimap_plain.c
 * author: klassiker [mrdotx]
 * github: https://github.com/mrdotx/zenith-usb
 * date:   2021-03-07T09:53:52+0100
 */

#include "unimap_trans.h"
#include "unimap_macro.h"

#define AC_LT1      ACTION_LAYER_TOGGLE(1)
#define AC_LTK1     ACTION_LAYER_TAP_KEY(2, KC_INS)
#define AC_LTK2     ACTION_LAYER_TAP_KEY(2, KC_0)

#define AC_MON      ACTION_KEY(MOD_LGUI | KC_P)
#define AC_PLUS     ACTION_KEY(MOD_LSFT | KC_EQL)
#define AC_AST      ACTION_KEY(MOD_LSFT | KC_8)

#ifdef KEYMAP_SECTION_ENABLE
const action_t actionmaps[][UNIMAP_ROWS][UNIMAP_COLS] __attribute__ ((section (".keymap.keymaps"))) = {
#else
const action_t actionmaps[][UNIMAP_ROWS][UNIMAP_COLS] PROGMEM = {
#endif
    /* [0] default layer */
    UNIMAP(
              NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,
    ESC,      F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, NO,  NO,            NO,  MUTE,NO,           NO,  NO,  NO,
    GRV, 1,   2,   3,   4,   5,   6,   7,   8,   9,   0,   MINS,EQL, NO,  BSPC,     NO,  NO,  NO,      LT1, NO,  PSCR,VOLD,
    TAB, Q,   W,   E,   R,   T,   Y,   U,   I,   O,   P,   LBRC,RBRC,     LGUI,     NO,  NO,  NO,      HOME,UP,  PGUP,VOLU,
    CAPS,A,   S,   D,   F,   G,   H,   J,   K,   L,   SCLN,QUOT,     NO,  ENT,                         LEFT,DOWN,RGHT,NO,
    LSFT,NO,  Z,   X,   C,   V,   B,   N,   M,   COMM,DOT, SLSH,     NO,  RSFT,          NO,           END, DOWN,PGDN,NO,
    LCTL,NO,  LALT,NO,            SPC,           NO,  NO,  NO  ,NO  ,NO,  NO,       NO,  NO,  NO,           LTK1,DEL, NO
    ),
    /* [1] num pad with layer toggle NUM LOCK(LT1) */
    UNIMAP(
              NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,
    TRNS,     TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,NO,  NO,            NO,  SLCK,NO,           NO,  NO,  NO,
    TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,NO,  TRNS,     NO,  NO,  NO,      TRNS,NO,  AST, MINS,
    TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,     LGUI,     NO,  NO,  NO,      7,   8,   9,   PLUS,
    TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,     NO,  TRNS,                        4,   5,   6,   NO,
    TRNS,NO,  TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,     NO,  TRNS,          NO,           1,   2,   3,   NO,
    TRNS,NO,  TRNS,NO,            TRNS,          NO,  NO  ,NO,  NO,  NO,  NO,       NO,  NO,  NO,           LTK2,DOT, NO
    ),
    /* [2] functions, macros and mouse with tap key INS(LTK1) or 0(LTK2) */
    UNIMAP(
              NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,
    NO,       F11, F12, MON, CUT, NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,            NO,  SLEP,NO,           NO,  NO,  NO,
    BOOT,NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,       NO,  NO,  NO,      PWR, NO,  AUTO,BRTD,
    NO,  NO,  WT,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,       BSLS,     NO,  NO,  NO,      BTN3,MS_U,WH_U,BRTI,
    BTLD,NO,  NO,  NO,  NO,  NO,  SSH, NO,  NO,  NO,  WH_L,WH_R,     NO,  BTN1,                        MS_L,MS_D,MS_R,NO,
    TRNS,NO,  NO,  NO,  CV,  NO,  NO,  NO,  NO,  ACL0,ACL1,ACL2,     NO,  TRNS,          NO,           BTN2,MS_D,WH_D,NO,
    NO,  NO,  NO,  NO,            F21,           NO,  NO  ,NO,  NO,  NO,  NO,       NO,  NO,  NO,           TRNS,KB,  NO
    ),
};
