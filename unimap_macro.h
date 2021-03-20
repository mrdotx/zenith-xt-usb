/*
 * path:   /home/klassiker/.local/share/repos/zenith-xt-usb/unimap_macro.h
 * author: klassiker [mrdotx]
 * github: https://github.com/mrdotx/zenith-usb
 * date:   2021-03-20T13:03:25+0100
 */

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
#define O_DESK10    D(LGUI), T(0), U(LGUI), C_WAIT_DS
#define O_PI        D(LGUI), T(H), U(LGUI), C_WAIT_DS
#define O_PI2       D(LGUI), D(LSFT), T(H), U(LSFT), U(LGUI), C_WAIT_DS

/*  clear; */
#define T_CLEAR     \
    T(SPC), T(C), T(L), T(E), T(A), T(R), T(SCLN)
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
/* reboot */
#define T_REBOOT    \
    T(R), T(E), T(B), T(O), T(O), T(T), T(ENT), C_WAIT_DS
/* st */
#define T_ST     \
    T(S), T(T), T(ENT), C_WAIT_DS
/* ranger_cd */
#define T_RANGER    \
    T(R), T(A), T(N), T(G), T(E), T(R), \
    D(LSFT), T(MINS), U(LSFT), T(C), T(D), T(ENT), \
    C_WAIT_QS, C_WAIT_QS, C_WAIT_QS, T(QUOT), T(R), C_WAIT_DS
/* cinfo */
#define T_CINFO     \
    T(C), T(I), T(N), T(F), T(O), T(ENT), C_WAIT_DS
/* neofetch */
#define T_NEOFETCH  \
    T(N), T(E), T(O), T(F), T(E), T(T), T(C), T(H), T(ENT), C_WAIT_DS
/* lsblk && doas ventoy -u /dev/sdb */
#define T_VENTOY    \
    T(L), T(S), T(B), T(L), T(K), T(SCLN), \
    T(V), T(E), T(N), T(T), T(O), T(Y), T(SPC), T(MINS), T(H), T(ENT), C_WAIT_DS, \
    T(D), T(O), T(A), T(S), T(SPC), \
    T(V), T(E), T(N), T(T), T(O), T(Y), T(SPC), \
    T(MINS), T(U), T(SPC), \
    T(SLSH), T(D), T(E), T(V), T(SLSH), T(S), T(D), T(B), C_WAIT_DS
/* curl -H "Accept-Language: de" wttr.in */
#define T_WEATHER   \
    T(C), T(U), T(R), T(L), T(SPC), \
    T(MINS), D(LSFT), T(H), U(LSFT), T(SPC), \
    D(LSFT), T(QUOT), T(A), U(LSFT), T(C), T(C), T(E), T(P), T(T), T(MINS), \
    D(LSFT), T(L), U(LSFT), T(A), T(N), T(G), T(U), T(A), T(G), T(E), \
    D(LSFT), T(SCLN), U(LSFT), T(SPC), T(D), T(E), D(LSFT), T(QUOT), U(LSFT), T(SPC), \
    T(W), T(T), T(T), T(R), T(DOT), T(I), T(N), T(ENT), C_WAIT_DS
/* curl "https://corona-stats.online?top=25&source=2&minimal=true" */
#define T_COVID     \
    T(C), T(U), T(R), T(L), T(SPC), \
    D(LSFT), T(QUOT), U(LSFT), T(H), T(T), T(T), T(P), T(S), D(LSFT), T(SCLN), U(LSFT), \
    D(SLSH), D(SLSH), T(C), T(O), T(R), T(O), T(N), T(A), T(MINS), \
    T(S), T(T), T(A), T(T), T(S), T(DOT), T(O), T(N), T(L), T(I), T(N), T(E), \
    D(LSFT), T(SLSH), T(SLSH), U(LSFT), T(T), T(O), T(P), T(EQL), T(2), T(5), \
    D(LSFT), T(7), U(LSFT), T(S), T(O), T(U), T(R), T(C), T(E), T(EQL), T(2), \
    D(LSFT), T(7), U(LSFT), T(M), T(I), T(N), T(I), T(M), T(A), T(L), T(EQL), \
    T(T), T(R), T(U), T(E), D(LSFT), T(QUOT), U(LSFT), T(ENT), C_WAIT_DS
/* terminal_colors.sh */
#define T_TERMCOLOR \
    T(T), T(E), T(R), T(M), T(I), T(N), T(A), T(L), D(LSFT), T(MINS), U(LSFT), \
    T(C), T(O), T(L), T(O), T(R), T(S), T(DOT), T(S), T(H), T(ENT), C_WAIT_DS
/* telnet towel.blinkenlights.nl */
#define T_STARWARS  \
    T(T), T(E), T(L), T(N), T(E), T(T), T(SPC), \
    T(T), T(O), T(W), T(E), T(L), T(DOT), \
    T(B), T(L), T(I), T(N), T(K), T(E), T(N), T(L), T(I), T(G), T(H), T(T), T(S), T(DOT), \
    T(N), T(L), T(ENT), C_WAIT_DS
/* minetest --logfile '' */
#define T_MINETEST \
    T(M), T(I), T(N), T(E), T(T), T(E), T(S), T(T), T(SPC), \
    T(MINS), T(MINS), T(L), T(O), T(G), T(F), T(I), T(L), T(E), T(SPC), \
    T(QUOT), T(QUOT), T(ENT), C_WAIT_DS
/* kodi */
#define T_KODI \
    T(K), T(O), T(D), T(I), T(ENT), C_WAIT_DS

#define AC_KEYB     ACTION_MACRO(SETKEYBOARD)
#define AC_AUTO     ACTION_MACRO(AUTOSTART)
#define AC_SSH      ACTION_MACRO(OPENSSH)
#define AC_BOOT     ACTION_MACRO(REBOOT)
#define AC_TERM     ACTION_MACRO(TERMINAL)
#define AC_VTOY     ACTION_MACRO(VENTOY)
#define AC_WTHR     ACTION_MACRO(WEATHER)
#define AC_COV      ACTION_MACRO(COVID)
#define AC_NEOF     ACTION_MACRO(NEOFETCH)
#define AC_TCOL     ACTION_MACRO(TERMCOLOR)
#define AC_STAR     ACTION_MACRO(STARWARS)
#define AC_MINE     ACTION_MACRO(MINETEST)
#define AC_KODI     ACTION_MACRO(KODI)

enum macro_id {
    SETKEYBOARD,
    AUTOSTART,
    OPENSSH,
    REBOOT,
    TERMINAL,
    VENTOY,
    WEATHER,
    COVID,
    NEOFETCH,
    TERMCOLOR,
    STARWARS,
    MINETEST,
    KODI,
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
    switch (id) {
        case SETKEYBOARD:
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
                        /* go to desktop 1 and open terminal with system info */
                        O_DESK1, O_TERM, T_CLEAR, T_CINFO, \
                        /* open web browser */
                        O_WEB, \
                        /* go to desktop 2 and open terminal with file manager */
                        O_DESK2, O_TERM, T_CLEAR, T_RANGER, \
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
        case TERMINAL:
            return (record->event.pressed ?
                    MACRO( \
                        /* set typing interval */
                        C_INTERVAL, \
                        /* open dmenu and execute terminal*/
                        O_DMENU, T_ST, \
                        END ) :
                    MACRO_NONE );
        case VENTOY:
            return (record->event.pressed ?
                    MACRO( \
                        /* set typing interval */
                        C_INTERVAL, \
                        /* open floating terminal with ventoy */
                        O_TERMFLOAT, T_CLEAR, T_VENTOY, \
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
                        /* open floating terminal with covid stats */
                        O_TERMFLOAT, T_CLEAR, T_COVID, \
                        END ) :
                    MACRO_NONE );
        case NEOFETCH:
            return (record->event.pressed ?
                    MACRO( \
                        /* set typing interval */
                        C_INTERVAL, \
                        /* open floating terminal with neofetch */
                        O_TERMFLOAT, T_CLEAR, T_NEOFETCH, \
                        END ) :
                    MACRO_NONE );
        case TERMCOLOR:
            return (record->event.pressed ?
                    MACRO( \
                        /* set typing interval */
                        C_INTERVAL, \
                        /* open floating terminal with color info */
                        O_TERMFLOAT, T_CLEAR, T_TERMCOLOR, \
                        END ) :
                    MACRO_NONE );
        case STARWARS:
            return (record->event.pressed ?
                    MACRO( \
                        /* set typing interval */
                        C_INTERVAL, \
                        /* open floating terminal with starwars */
                        O_TERMFLOAT, T_CLEAR, T_STARWARS, \
                        END ) :
                    MACRO_NONE );
        case MINETEST:
            return (record->event.pressed ?
                    MACRO( \
                        /* set typing interval */
                        C_INTERVAL, \
                        /* open dmenu, execute minetest and go to desktop 0 */
                        O_DMENU, T_MINETEST, O_DESK10, \
                        END ) :
                    MACRO_NONE );
        case KODI:
            return (record->event.pressed ?
                    MACRO( \
                        /* set typing interval */
                        C_INTERVAL, \
                        /* open dmenu, execute kodi and go to desktop 0 */
                        O_DMENU, T_KODI, O_DESK10, \
                        END ) :
                    MACRO_NONE );
    }
    return MACRO_NONE;
}
