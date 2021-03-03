/*
 * path:   /home/klassiker/.local/share/repos/zenith-xt-usb/unimap_plain.c
 * author: klassiker [mrdotx]
 * github: https://github.com/mrdotx/zenith-usb
 * date:   2021-03-03T21:06:33+0100
 */

#include "unimap_trans.h"

/* function definition */
#define AC_LT1      ACTION_LAYER_TOGGLE(1)
#define AC_LTK1     ACTION_LAYER_TAP_KEY(2, KC_INS)
#define AC_LTK2     ACTION_LAYER_TAP_KEY(2, KC_0)

#define AC_MON      ACTION_KEY(MOD_LGUI | KC_P)
#define AC_PLUS     ACTION_KEY(MOD_LSFT | KC_EQL)
#define AC_AST      ACTION_KEY(MOD_LSFT | KC_8)

#define AC_M0       ACTION_MACRO(SETKB)
#define AC_M1       ACTION_MACRO(AUTOSTART)
#define AC_M2       ACTION_MACRO(OPENSSH)

/* macro definition */
#define C_INTERVAL  I(5)

#define O_TERMINAL  D(LGUI), T(ENT), U(LGUI), W(250)
#define O_WEB       D(LGUI), T(W), U(LGUI), W(100)
#define O_TOP       D(LGUI), T(T), U(LGUI), W(100)
#define O_DESK2     D(LGUI), T(2), U(LGUI), W(100)
#define O_LAYOUT    D(LGUI), T(SPC), U(LGUI), T(LEFT), T(LEFT), T(LEFT), T(ENT), W(100)
#define O_FOCUS     D(LGUI), T(LEFT), U(LGUI), W(100)
#define O_PI        D(LGUI), T(H), U(LGUI), W(100)
#define O_PI2       D(LGUI), D(LSFT), T(H), U(LSFT), U(LGUI), W(100)

#define T_CLEAR     T(SPC), T(C), T(L), T(E), T(A), T(R)
#define T_EXIT      T(SPC), T(E), T(X), T(I), T(T)
#define T_RANGER    T(SPC), T(R), T(A), T(N), T(G), T(E), T(R)
#define T_CINFO     T(SPC), T(C), T(I), T(N), T(F), T(O)
#define T_XSET      T(SPC), T(X), T(S), T(E), T(T), T(SPC), \
                    T(R), T(SPC), \
                    T(R), T(A), T(T), T(E), T(SPC), \
                    T(2), T(0), T(0), T(SPC), \
                    T(5), T(0)
#define T_SETXKBMAP T(SPC), T(S), T(E), T(T), T(X), T(K), T(B), T(M), T(A), T(P), T(SPC), \
                    T(MINS), T(M), T(O), T(D), T(E), T(L), T(SPC), \
                    T(P), T(C), T(1), T(0), T(5), T(SPC), \
                    T(MINS), T(L), T(A), T(Y), T(O), T(U), T(T), T(SPC), \
                    T(U), T(S), T(COMM), T(D), T(E), T(SPC), \
                    T(MINS), T(O), T(P), T(T), T(I), T(O), T(N), T(SPC), \
                    T(G), T(R), T(P), D(LSFT), T(SCLN), U(LSFT), T(C), T(A), T(P), T(S), D(LSFT), T(MINS), U(LSFT), T(S), T(W), T(I), T(T), T(C), T(H)

enum macro_id {
    SETKB,
    AUTOSTART,
    OPENSSH,
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
    switch (id) {
        case SETKB:
            return (record->event.pressed ?
                    MACRO( \
                        /* set typing interval */
                        C_INTERVAL, \
                        /* open terminal, execute xset/setxkmap and close terminal */
                        O_TERMINAL, T_XSET, T(SCLN), T_SETXKBMAP, T(SCLN), T_EXIT, T(ENT), \
                        END ) :
                    MACRO_NONE );
        case AUTOSTART:
            return (record->event.pressed ?
                    MACRO( \
                        /* set typing interval */
                        C_INTERVAL, \
                        /* open web browser, system monitor and go to desktop 2 */
                        O_WEB, O_TOP, O_DESK2, \
                        /* open terminal, clear terminal and execute ranger */
                        O_TERMINAL, T_CLEAR, T(SCLN), T_RANGER, T(ENT), W(100), \
                        /* open another terminal, clear terminal and execute cinfo */
                        O_TERMINAL, T_CLEAR, T(SCLN), T_CINFO, T(ENT), W(100), \
                        /* change terminal layout and window focus */
                        O_LAYOUT, O_FOCUS, \
                        END ) :
                    MACRO_NONE );
        case OPENSSH:
            return (record->event.pressed ?
                    MACRO( \
                        /* set typing interval */
                        C_INTERVAL, \
                        /* open ssh to hermes and prometheus */
                        O_PI, O_PI2, \
                        END ) :
                    MACRO_NONE );
    }
    return MACRO_NONE;
}

/* keymap definition */
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
    NO,       F11, F12, NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,            NO,  SLEP,NO,           NO,  NO,  NO,
    BTN3,M1,  M2,  NO,BRTD,BRTI,  MON, CUT, NO,  NO,  NO,  NO,  NO,  NO,  NO,       NO,  NO,  NO,      PWR, NO,  NO,  WH_U,
    NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,       BSLS,     NO,  NO,  NO,      BTN1,MS_U,BTN2,WH_D,
    BTLD,NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,       NO,  NO,                          MS_L,MS_D,MS_R,NO,
    TRNS,NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  ACL0,ACL1,ACL2,     NO,  TRNS,          NO,           WH_L,MS_D,WH_R,NO,
    NO,  NO,  NO,  NO,            F21,           NO,  NO  ,NO,  NO,  NO,  NO,       NO,  NO,  NO,           TRNS,M0,  NO
    ),
};
