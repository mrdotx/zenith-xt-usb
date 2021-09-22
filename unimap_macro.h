/*
 * path:   /home/klassiker/.local/share/repos/zenith-xt-usb/unimap_macro.h
 * author: klassiker [mrdotx]
 * github: https://github.com/mrdotx/zenith-usb
 * date:   2021-09-22T10:52:32+0200
 */

/* general config */
#define C_INTERVAL1 I(1)
#define C_INTERVAL2 I(25)
#define C_WAIT0     W(100)
#define C_WAIT1     W(255)
#define C_WAIT2     C_WAIT1, C_WAIT1
#define C_WAIT4     C_WAIT2, C_WAIT2

/* open terminal */
#define O_TERM      C_INTERVAL2, \
    D(LGUI), T(ENT), U(LGUI), C_WAIT1
/* open tmux */
#define O_TMUX      C_INTERVAL2, \
    D(LGUI), D(LSFT), T(ENT), U(LSFT), U(LGUI), C_WAIT1
/* open dmenu */
#define O_DMENU     C_INTERVAL2, \
    D(LSFT), T(LGUI), U(LSFT), C_WAIT1
/* open web browser */
#define O_WEB       C_INTERVAL2, \
    D(LGUI), T(W), U(LGUI), C_WAIT1
/* go to desktop 1 */
#define O_DESK1     C_INTERVAL2, \
    D(LGUI), T(1), U(LGUI), C_WAIT1
/* go to ranger repos folder*/
#define O_RANGER_R  C_INTERVAL2, \
    T(QUOT), T(R), C_WAIT1
/* change terminal font size */
#define O_FONTSIZE  C_INTERVAL2, \
    D(LCTL), D(LSFT), \
    T(EQL), T(EQL), T(EQL), T(EQL), T(EQL), T(EQL), T(EQL), T(EQL), \
    U(LSFT), U(LCTL), C_WAIT1

/*  clear; */
#define T_CLEAR     C_INTERVAL1, \
    T(SPC), T(C), T(L), T(E), T(A), T(R), T(SCLN)
/* cinfo */
#define T_CINFO     C_INTERVAL1, \
    T(C), T(I), T(N), T(F), T(O), T(ENT), C_WAIT0
/* ranger_cd */
#define T_RANGER    C_INTERVAL1, \
    T(R), T(A), T(N), T(G), T(E), T(R), \
    D(LSFT), T(MINS), U(LSFT), T(C), T(D), T(ENT), C_WAIT0
/* reboot */
#define T_REBOOT    C_INTERVAL1, \
    T(R), T(E), T(B), T(O), T(O), T(T), T(ENT), C_WAIT0

#define AC_AUTO     ACTION_MACRO(AUTOSTART)
#define AC_FONT     ACTION_MACRO(FONTSIZE)
#define AC_BOOT     ACTION_MACRO(REBOOT)

enum macro_id {
    AUTOSTART,
    FONTSIZE,
    REBOOT,
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
    switch (id) {
        case AUTOSTART:
            return (record->event.pressed ?
                MACRO( \
                    O_TMUX, O_FONTSIZE, T_CLEAR, T_CINFO, \
                    O_DESK1, O_TERM, O_WEB, \
                    T_CLEAR, T_RANGER, C_WAIT2, \
                    O_RANGER_R, C_WAIT4, \
                    O_DESK1, \
                    END ) :
                MACRO_NONE );
        case FONTSIZE:
            return (record->event.pressed ?
                MACRO( \
                    O_FONTSIZE, \
                    END ) :
                MACRO_NONE );
        case REBOOT:
            return (record->event.pressed ?
                MACRO( \
                    O_DMENU, T_REBOOT, \
                    END ) :
                MACRO_NONE );
    }
    return MACRO_NONE;
}
