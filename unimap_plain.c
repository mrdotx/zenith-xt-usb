/*
 * path:   /home/klassiker/.local/share/repos/zenith-xt-usb/unimap_plain.c
 * author: klassiker [mrdotx]
 * github: https://github.com/mrdotx/zenith-usb
 * date:   2021-03-02T18:54:19+0100
 */

#include "unimap_trans.h"

enum macro_id {
    SETKB,
    AUTOSTART,
    OPENSSH,
};

#define AC_LT1  ACTION_LAYER_TOGGLE(1)
#define AC_LTK1 ACTION_LAYER_TAP_KEY(2, KC_INS)
#define AC_LTK2 ACTION_LAYER_TAP_KEY(2, KC_0)

#define AC_MON  ACTION_KEY(MOD_LGUI | KC_P)
#define AC_PLUS ACTION_KEY(MOD_LSFT | KC_EQL)
#define AC_AST  ACTION_KEY(MOD_LSFT | KC_8)

#define AC_M0   ACTION_MACRO(SETKB)
#define AC_M1   ACTION_MACRO(AUTOSTART)
#define AC_M2   ACTION_MACRO(OPENSSH)

#ifdef KEYMAP_SECTION_ENABLE
const action_t actionmaps[][UNIMAP_ROWS][UNIMAP_COLS] __attribute__ ((section (".keymap.keymaps"))) = {
#else
const action_t actionmaps[][UNIMAP_ROWS][UNIMAP_COLS] PROGMEM = {
#endif
    UNIMAP(
              NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,
    ESC,      F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, NO,  NO,            NO,  MUTE,NO,           NO,  NO,  NO,
    GRV, 1,   2,   3,   4,   5,   6,   7,   8,   9,   0,   MINS,EQL, NO,  BSPC,     NO,  NO,  NO,      LT1, NO,  PSCR,VOLD,
    TAB, Q,   W,   E,   R,   T,   Y,   U,   I,   O,   P,   LBRC,RBRC,     LGUI,     NO,  NO,  NO,      HOME,UP,  PGUP,VOLU,
    CAPS,A,   S,   D,   F,   G,   H,   J,   K,   L,   SCLN,QUOT,     NO,  ENT,                         LEFT,DOWN,RGHT,NO,
    LSFT,NO,  Z,   X,   C,   V,   B,   N,   M,   COMM,DOT, SLSH,     NO,  RSFT,          NO,           END, DOWN,PGDN,NO,
    LCTL,NO,  LALT,NO,            SPC,           NO,  NO,  NO  ,NO  ,NO,  NO,       NO,  NO,  NO,           LTK1,DEL, NO
    ),
    /* num pad with layer toggle NUM LOCK(LT1) */
    UNIMAP(
              NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,
    TRNS,     TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,NO,  NO,            NO,  SLCK,NO,           NO,  NO,  NO,
    TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,NO,  TRNS,     NO,  NO,  NO,      TRNS,NO,  AST, MINS,
    TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,     LGUI,     NO,  NO,  NO,      7,   8,   9,   PLUS,
    TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,     NO,  TRNS,                        4,   5,   6,   NO,
    TRNS,NO,  TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,     NO,  TRNS,          NO,           1,   2,   3,   NO,
    TRNS,NO,  TRNS,NO,            TRNS,          NO,  NO  ,NO,  NO,  NO,  NO,       NO,  NO,  NO,           LTK2,DOT, NO
    ),
    /* function, macros and mouse with tap key INS(LTK1) or 0(LTK2) */
    UNIMAP(
              NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,
    NO,       F11, F12, NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,            NO,  SLEP,NO,           NO,  NO,  NO,
    BTN3,M1,  M2,  NO,  NO,  NO,  MON, CUT, NO,  NO,  NO,  NO,  NO,  NO,  NO,       NO,  NO,  NO,      PWR, NO,  NO,  WH_U,
    NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,       BSLS,     NO,  NO,  NO,      BTN1,MS_U,BTN2,WH_D,
    BTLD,NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,       NO,  NO,                          MS_L,MS_D,MS_R,NO,
    NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  ACL0,ACL1,ACL2,     NO,  NO,            NO,           WH_L,MS_D,WH_R,NO,
    NO,  NO,  NO,  NO,            F21,           NO,  NO  ,NO,  NO,  NO,  NO,       NO,  NO,  NO,           TRNS,M0,  NO
    ),
};

/* macro definitions */
const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
    switch (id) {
        case SETKB:
            return (record->event.pressed ?
                    MACRO( \
                        /* set interval */
                        I(5), \
                        /* open terminal and wait for x milliseconds */
                        D(LGUI), T(ENT), U(LGUI), W(255), \
                        /* type ' xset r rate 200 50;' */
                        T(SPC), \
                        T(X), T(S), T(E), T(T), T(SPC), \
                        T(R), T(SPC), \
                        T(R), T(A), T(T), T(E), T(SPC), \
                        T(2), T(0), T(0), T(SPC), \
                        T(5), T(0), T(SCLN), \
                        /* type ' setxkbmap -model pc105 -layout us,de -option grp:caps_switch;' */
                        T(SPC),
                        T(S), T(E), T(T), T(X), T(K), T(B), T(M), T(A), T(P), T(SPC), \
                        T(MINS), T(M), T(O), T(D), T(E), T(L), T(SPC), \
                        T(P), T(C), T(1), T(0), T(5), T(SPC), \
                        T(MINS), T(L), T(A), T(Y), T(O), T(U), T(T), T(SPC), \
                        T(U), T(S), T(COMM), T(D), T(E), T(SPC), \
                        T(MINS), T(O), T(P), T(T), T(I), T(O), T(N), T(SPC), \
                        T(G), T(R), T(P), D(LSFT), T(SCLN), U(LSFT), T(C), T(A), T(P), T(S), D(LSFT), T(MINS), U(LSFT), T(S), T(W), T(I), T(T), T(C), T(H), T(SCLN), \
                        /* type ' exit' and press enter (close terminal) */
                        T(SPC), \
                        T(E), T(X), T(I), T(T), T(ENT), \
                        END ) :
                    MACRO_NONE );
        case AUTOSTART:
            return (record->event.pressed ?
                    MACRO( \
                        /* set interval */
                        I(5), \
                        /* open webbrowser */
                        D(LGUI), T(W), U(LGUI), \
                        /* open system monitor */
                        D(LGUI), T(T), U(LGUI), \
                        /* go to desktop 2 */
                        D(LGUI), T(2), U(LGUI), \
                        /* open terminal and wait for x milliseconds */
                        D(LGUI), T(ENT), U(LGUI), W(255), W(255), \
                        /* type ' ranger' and press enter */
                        T(SPC), \
                        T(R), T(A), T(N), T(G), T(E), T(R), T(ENT), \
                        /* open another terminal and wait for x milliseconds */
                        D(LGUI), T(ENT), U(LGUI), W(255), \
                        /* type ' cinfo', press enter and wait for x milliseconds*/
                        T(SPC), \
                        T(C), T(I), T(N), T(F), T(O), T(ENT), W(100), \
                        /* change terminal layout, wait for x milliseconds and change focus */
                        D(LGUI), T(SPC), U(LGUI), T(LEFT), T(LEFT), T(LEFT), T(ENT), W(100), \
                        D(LGUI), T(LEFT), U(LGUI), \
                        END ) :
                    MACRO_NONE );
        case OPENSSH:
            return (record->event.pressed ?
                    MACRO( \
                        /* set interval */
                        I(5), \
                        /* open ssh to hermes */
                        D(LGUI), T(H), U(LGUI), \
                        /* open ssh to prometheus */
                        D(LGUI), D(LSFT), T(H), U(LSFT), U(LGUI), \
                        END ) :
                    MACRO_NONE );
    }
    return MACRO_NONE;
}
