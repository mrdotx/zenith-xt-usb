/*:
 * path:   /home/klassiker/.local/share/repos/zenith-xt-usb/unimap_macro.h
 * author: klassiker [mrdotx]
 * github: https://github.com/mrdotx/zenith-usb
 * date:   2021-03-10T13:01:05+0100
 */

#define AC_KB       ACTION_MACRO(SETKB)
#define AC_AUTO     ACTION_MACRO(AUTOSTART)
#define AC_SSH      ACTION_MACRO(OPENSSH)
#define AC_BOOT     ACTION_MACRO(REBOOT)
#define AC_WT       ACTION_MACRO(WEATHER)
#define AC_CV       ACTION_MACRO(COVID)
#define AC_CO       ACTION_MACRO(TCOLOR)

#define C_INTERVAL  I(5)
#define C_WAIT_DS   W(100)
#define C_WAIT_QS   W(255)

#define O_TERM      D(LGUI), T(ENT), U(LGUI), C_WAIT_QS
#define O_TERMFLOAT D(LGUI), D(LSFT), T(ENT), U(LSFT), U(LGUI), C_WAIT_QS
#define O_DMENU     D(LSFT), T(LGUI), U(LSFT), C_WAIT_QS
#define O_WEB       D(LGUI), T(W), U(LGUI), C_WAIT_QS
#define O_DESK1     D(LGUI), T(1), U(LGUI), C_WAIT_DS
#define O_DESK2     D(LGUI), T(2), U(LGUI), C_WAIT_DS
#define O_DESK4     D(LGUI), T(4), U(LGUI), C_WAIT_DS
#define O_PI        D(LGUI), T(H), U(LGUI), C_WAIT_DS
#define O_PI2       D(LGUI), D(LSFT), T(H), U(LSFT), U(LGUI), C_WAIT_DS

#define T_CLEAR     T(SPC), T(C), T(L), T(E), T(A), T(R), T(SCLN)

#define T_REBOOT    T(R), T(E), T(B), T(O), T(O), T(T), T(ENT), C_WAIT_DS
#define T_RANGER    T(R), T(G), T(ENT), C_WAIT_QS, C_WAIT_QS, T(QUOT), T(R), C_WAIT_DS
#define T_CINFO     T(C), T(L), T(ENT), C_WAIT_DS
#define T_WEATHER   T(W), T(T), T(ENT), C_WAIT_DS
#define T_COVID     T(C), T(V), T(ENT), C_WAIT_DS
#define T_TCOLOR    T(C), T(O), T(ENT), C_WAIT_DS

/* xset r rate 200 50; */
/* setxkbmap -model pc105 -layout us,de -option grp:caps_switch */
#define T_KEYBOARD  \
    T(X), T(S), T(E), T(T), T(SPC), \
    T(R), T(SPC), \
    T(R), T(A), T(T), T(E), T(SPC), \
    T(2), T(0), T(0), T(SPC), \
    T(5), T(0), T(SCLN), \
    T(S), T(E), T(T), T(X), T(K), T(B), T(M), T(A), T(P), T(SPC), \
    T(MINS), T(M), T(O), T(D), T(E), T(L), T(SPC), \
    T(P), T(C), T(1), T(0), T(5), T(SPC), \
    T(MINS), T(L), T(A), T(Y), T(O), T(U), T(T), T(SPC), \
    T(U), T(S), T(COMM), T(D), T(E), T(SPC), \
    T(MINS), T(O), T(P), T(T), T(I), T(O), T(N), T(SPC), \
    T(G), T(R), T(P), D(LSFT), T(SCLN), U(LSFT), \
    T(C), T(A), T(P), T(S), D(LSFT), T(MINS), U(LSFT), \
    T(S), T(W), T(I), T(T), T(C), T(H), T(ENT), C_WAIT_DS

enum macro_id {
    SETKB,
    AUTOSTART,
    OPENSSH,
    REBOOT,
    WEATHER,
    COVID,
    TCOLOR,
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
    switch (id) {
        case SETKB:
            return (record->event.pressed ?
                    MACRO( \
                        /* set typing interval */
                        C_INTERVAL, \
                        /* open dmenu and set keyboard options */
                        O_DMENU, T_KEYBOARD, \
                        END ) :
                    MACRO_NONE );
        case AUTOSTART:
            return (record->event.pressed ?
                    MACRO( \
                        /* set typing interval */
                        C_INTERVAL, \
                        /* open web browser */
                        O_WEB, \
                        /* go to desktop 2 and open terminal with file manager */
                        O_DESK2, O_TERM, T_CLEAR, T_RANGER, \
                        /* go to desktop 1 and open terminal with system info */
                        O_DESK1, O_TERM, T_CINFO, \
                        /* refresh desktops */
                        O_DESK4, O_DESK2, O_DESK1, \
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
        case REBOOT:
            return (record->event.pressed ?
                    MACRO( \
                        /* set typing interval */
                        C_INTERVAL, \
                        /* open dmenu and execute reboot */
                        O_DMENU, T_REBOOT, \
                        END ) :
                    MACRO_NONE );
        case WEATHER:
            return (record->event.pressed ?
                    MACRO( \
                        /* set typing interval */
                        C_INTERVAL, \
                        /* open floating terminal with weather info */
                        O_TERMFLOAT, T_CLEAR, T_WEATHER, \
                        END ) :
                    MACRO_NONE );
        case COVID:
            return (record->event.pressed ?
                    MACRO( \
                        /* set typing interval */
                        C_INTERVAL, \
                        /* open floating terminal with covid info */
                        O_TERMFLOAT, T_CLEAR, T_COVID, \
                        END ) :
                    MACRO_NONE );
        case TCOLOR:
            return (record->event.pressed ?
                    MACRO( \
                        /* set typing interval */
                        C_INTERVAL, \
                        /* open floating terminal with color info */
                        O_TERMFLOAT, T_CLEAR, T_TCOLOR, \
                        END ) :
                    MACRO_NONE );
    }
    return MACRO_NONE;
}
