/*
 * path:   /home/klassiker/.local/share/repos/zenith-xt-usb/unimap_macro.h
 * author: klassiker [mrdotx]
 * github: https://github.com/mrdotx/zenith-usb
 * date:   2021-07-10T20:00:26+0200
 */

/* general config */
#define C_INTERVAL1 I(1)
#define C_INTERVAL2 I(25)
#define C_WAIT1     W(100)
#define C_WAIT2     W(255)
#define C_WAIT3     W(255), W(255)

/* open terminal */
#define O_TERM      C_INTERVAL2, \
    D(LGUI), T(ENT), U(LGUI), C_WAIT2
/* open info terminal */
#define O_TERMINFO  C_INTERVAL2, \
    D(LGUI), D(LSFT), T(ENT), U(LSFT), U(LGUI), C_WAIT2
/* change terminal font size */
#define O_FONTSIZE  C_INTERVAL2, \
    D(LCTL), D(LSFT), \
    T(EQL), T(EQL), T(EQL), T(EQL), T(EQL), T(EQL), T(EQL), T(EQL), \
    U(LSFT), U(LCTL), C_WAIT2
/* open dmenu */
#define O_DMENU     C_INTERVAL2, \
    D(LSFT), T(LGUI), U(LSFT), C_WAIT2
/* open web browser */
#define O_WEB       C_INTERVAL2, \
    D(LGUI), T(W), U(LGUI), C_WAIT2
/* go to desktop 2 */
#define O_DESK2     C_INTERVAL2, \
    D(LGUI), T(2), U(LGUI), C_WAIT2
/* go to desktop 3 */
#define O_DESK3     C_INTERVAL2, \
    D(LGUI), T(3), U(LGUI), C_WAIT2
/* go to desktop 4 */
#define O_DESK4     C_INTERVAL2, \
    D(LGUI), T(4), U(LGUI), C_WAIT2
/* open ssh connection 1 */
#define O_SSH1      C_INTERVAL2, \
    D(LGUI), T(H), U(LGUI), C_WAIT2
/* open ssh connection 2 */
#define O_SSH2      C_INTERVAL2, \
    D(LGUI), D(LSFT), T(H), U(LSFT), U(LGUI), C_WAIT2
/* open ranger repos folder*/
#define O_RANGER_R  C_INTERVAL2, \
    T(QUOT), T(R), C_WAIT2

/*  clear; */
#define T_CLEAR     C_INTERVAL1, \
    T(SPC), T(C), T(L), T(E), T(A), T(R), T(SCLN)
/* setxkbmap -model pc105 -layout us,de -option grp:caps_switch;xset r rate 200 50 */
#define T_KEYBOARD C_INTERVAL1, \
    T(S), T(E), T(T), T(X), T(K), T(B), T(M), T(A), T(P), T(SPC), \
    T(MINS), T(M), T(O), T(D), T(E), T(L), T(SPC), \
    T(P), T(C), T(1), T(0), T(5), T(SPC), \
    T(MINS), T(L), T(A), T(Y), T(O), T(U), T(T), T(SPC), \
    T(U), T(S), T(COMM), T(D), T(E), T(SPC), \
    T(MINS), T(O), T(P), T(T), T(I), T(O), T(N), T(SPC), \
    T(G), T(R), T(P), D(LSFT), T(SCLN), U(LSFT), \
    T(C), T(A), T(P), T(S), D(LSFT), T(MINS), U(LSFT), \
    T(S), T(W), T(I), T(T), T(C), T(H), T(SCLN), \
    T(X), T(S), T(E), T(T), T(SPC), T(R), T(SPC), \
    T(R), T(A), T(T), T(E), T(SPC), \
    T(2), T(0), T(0), T(SPC), T(5), T(0), T(ENT), C_WAIT1
/* ranger_cd */
#define T_RANGER    C_INTERVAL1, \
    T(R), T(A), T(N), T(G), T(E), T(R), \
    D(LSFT), T(MINS), U(LSFT), T(C), T(D), T(ENT), C_WAIT1
/* cinfo */
#define T_CINFO     C_INTERVAL1, \
    T(C), T(I), T(N), T(F), T(O), T(ENT), C_WAIT1
/* reboot */
#define T_REBOOT    C_INTERVAL1, \
    T(R), T(E), T(B), T(O), T(O), T(T), T(ENT), C_WAIT1
/* doas efistub.sh -b */
#define T_BOOTNEXT  C_INTERVAL1, \
    T(D), T(O), T(A), T(S), T(SPC), \
    T(E), T(F), T(I), T(S), T(T), T(U), T(B), T(DOT), T(S), T(H), T(SPC), \
    T(MINS), T(B), T(ENT), C_WAIT1
/* lsblk;doas ventoy -u /dev/sdb */
#define T_VENTOY    C_INTERVAL1, \
    T(L), T(S), T(B), T(L), T(K), T(SCLN), \
    T(V), T(E), T(N), T(T), T(O), T(Y), T(SPC), \
    T(MINS), T(H), T(ENT), C_WAIT1, \
    T(D), T(O), T(A), T(S), T(SPC), \
    T(V), T(E), T(N), T(T), T(O), T(Y), T(SPC), \
    T(MINS), T(U), T(SPC), \
    T(SLSH), T(D), T(E), T(V), T(SLSH), T(S), T(D), T(B), C_WAIT1
/* terminal_colors.sh */
#define T_TERMCOLOR C_INTERVAL1, \
    T(T), T(E), T(R), T(M), T(I), T(N), T(A), T(L), D(LSFT), T(MINS), U(LSFT), \
    T(C), T(O), T(L), T(O), T(R), T(S), T(DOT), T(S), T(H), T(ENT), C_WAIT1
/* neofetch */
#define T_NEOFETCH  C_INTERVAL1, \
    T(N), T(E), T(O), T(F), T(E), T(T), T(C), T(H), T(ENT), C_WAIT1
/* curl "wttr.in/?AFq2&lang=de" */
#define T_WEATHER   C_INTERVAL1, \
    T(C), T(U), T(R), T(L), T(SPC), D(LSFT), T(QUOT), U(LSFT), \
    T(W), T(T), T(T), T(R), T(DOT), T(I), T(N), \
    T(SLSH), D(LSFT), T(SLSH), T(A), T(F), U(LSFT), T(Q), T(2), \
    D(LSFT), T(7), U(LSFT), T(L), T(A), T(N), T(G), T(EQL), T(D), T(E), \
    D(LSFT), T(QUOT), U(LSFT), T(ENT), C_WAIT1
/* curl -s "https://corona-stats.online?top=30&source=2&minimal=true" \ head -n32 */
#define T_COVID     C_INTERVAL1, \
    T(C), T(U), T(R), T(L), T(SPC), T(MINS), T(S), T(SPC), \
    D(LSFT), T(QUOT), U(LSFT), T(H), T(T), T(T), T(P), T(S), \
    D(LSFT), T(SCLN), U(LSFT), T(SLSH), T(SLSH), \
    T(C), T(O), T(R), T(O), T(N), T(A), T(MINS), \
    T(S), T(T), T(A), T(T), T(S), T(DOT), T(O), T(N), T(L), T(I), T(N), T(E), \
    D(LSFT), T(SLSH), U(LSFT), T(T), T(O), T(P), T(EQL), T(3), T(0), \
    D(LSFT), T(7), U(LSFT), T(S), T(O), T(U), T(R), T(C), T(E), T(EQL), T(2), \
    D(LSFT), T(7), U(LSFT), T(M), T(I), T(N), T(I), T(M), T(A), T(L), T(EQL), \
    T(T), T(R), T(U), T(E), D(LSFT), T(QUOT), U(LSFT), \
    T(SPC), D(LSFT), T(BSLS), U(LSFT), T(SPC), \
    T(H), T(E), T(A), T(D), T(SPC), T(MINS), T(N), T(3), T(2), T(ENT), C_WAIT1

#define AC_KEYB     ACTION_MACRO(KEYBOARD)
#define AC_AUTO     ACTION_MACRO(AUTOSTART)
#define AC_FONT     ACTION_MACRO(FONTSIZE)
#define AC_BOOT     ACTION_MACRO(REBOOT)
#define AC_NEXT     ACTION_MACRO(BOOTNEXT)
#define AC_SSH      ACTION_MACRO(OPENSSH)
#define AC_VTOY     ACTION_MACRO(VENTOY)
#define AC_TCOL     ACTION_MACRO(TERMCOLOR)
#define AC_NEOF     ACTION_MACRO(NEOFETCH)
#define AC_WTHR     ACTION_MACRO(WEATHER)
#define AC_COV      ACTION_MACRO(COVID)

enum macro_id {
    KEYBOARD,
    AUTOSTART,
    FONTSIZE,
    REBOOT,
    BOOTNEXT,
    OPENSSH,
    VENTOY,
    TERMCOLOR,
    NEOFETCH,
    WEATHER,
    COVID,
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
    switch (id) {
        case KEYBOARD:
            return (record->event.pressed ?
                    MACRO( \
                        O_DMENU, T_KEYBOARD, \
                        END ) :
                    MACRO_NONE );
        case AUTOSTART:
            return (record->event.pressed ?
                    MACRO( \
                        O_TERMINFO, O_FONTSIZE, T_CLEAR, T_CINFO, \
                        O_WEB, \
                        O_DESK2, O_TERM, T_CLEAR, T_RANGER, C_WAIT3, \
                        O_RANGER_R, \
                        O_DESK4, O_DESK2, O_DESK3, \
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
        case BOOTNEXT:
            return (record->event.pressed ?
                    MACRO( \
                        O_TERMINFO, T_CLEAR, T_BOOTNEXT, \
                        END ) :
                    MACRO_NONE );
        case OPENSSH:
            return (record->event.pressed ?
                    MACRO( \
                        O_SSH1, O_SSH2, \
                        END ) :
                    MACRO_NONE );
        case VENTOY:
            return (record->event.pressed ?
                    MACRO( \
                        O_TERMINFO, T_CLEAR, T_VENTOY, \
                        END ) :
                    MACRO_NONE );
        case TERMCOLOR:
            return (record->event.pressed ?
                    MACRO( \
                        O_TERMINFO, T_CLEAR, T_TERMCOLOR, \
                        END ) :
                    MACRO_NONE );
        case NEOFETCH:
            return (record->event.pressed ?
                    MACRO( \
                        O_TERMINFO, T_CLEAR, T_NEOFETCH, \
                        END ) :
                    MACRO_NONE );
        case WEATHER:
            return (record->event.pressed ?
                    MACRO( \
                        O_TERMINFO, T_CLEAR, T_WEATHER, \
                        END ) :
                    MACRO_NONE );
        case COVID:
            return (record->event.pressed ?
                    MACRO( \
                        O_TERMINFO, T_CLEAR, T_COVID, \
                        END ) :
                    MACRO_NONE );
    }
    return MACRO_NONE;
}
