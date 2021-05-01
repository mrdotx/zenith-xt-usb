/*
 * path:   /home/klassiker/.local/share/repos/zenith-xt-usb/unimap_macro.h
 * author: klassiker [mrdotx]
 * github: https://github.com/mrdotx/zenith-usb
 * date:   2021-05-01T08:52:08+0200
 */

/* general config */
#define C_INTERVAL1 I(1)
#define C_INTERVAL2 I(25)
#define C_WAIT1     W(100)
#define C_WAIT2     W(255)

/* open terminal */
#define O_TERM      C_INTERVAL2, \
    D(LGUI), T(ENT), U(LGUI), C_WAIT2
/* open floating terminal */
#define O_TERMFLOAT C_INTERVAL2, \
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
/* go to desktop 1 */
#define O_DESK1     C_INTERVAL2, \
    D(LGUI), T(1), U(LGUI), C_WAIT2
/* go to desktop 2 */
#define O_DESK2     C_INTERVAL2, \
    D(LGUI), T(2), U(LGUI), C_WAIT2
/* go to desktop 4 */
#define O_DESK4     C_INTERVAL2, \
    D(LGUI), T(4), U(LGUI), C_WAIT2
/* go to desktop 9 */
#define O_DESK9    C_INTERVAL2, \
    D(LGUI), T(9), U(LGUI), C_WAIT2
/* go to desktop 10 */
#define O_DESK10    C_INTERVAL2, \
    D(LGUI), T(0), U(LGUI), C_WAIT2
/* open ssh connection 1 */
#define O_SSH1      C_INTERVAL2, \
    D(LGUI), T(H), U(LGUI), C_WAIT2
/* open ssh connection 2 */
#define O_SSH2      C_INTERVAL2, \
    D(LGUI), D(LSFT), T(H), U(LSFT), U(LGUI), C_WAIT2

/*  clear; */
#define T_CLEAR     C_INTERVAL1, \
    T(SPC), T(C), T(L), T(E), T(A), T(R), T(SCLN)
/* reboot */
#define T_REBOOT    C_INTERVAL1, \
    T(R), T(E), T(B), T(O), T(O), T(T), T(ENT), C_WAIT1
/* st */
#define T_ST        C_INTERVAL1, \
    T(S), T(T), T(ENT), C_WAIT1
/* ranger_cd */
#define T_RANGER    C_INTERVAL1, \
    T(R), T(A), T(N), T(G), T(E), T(R), \
    D(LSFT), T(MINS), U(LSFT), T(C), T(D), T(ENT), \
    C_WAIT2, C_WAIT2, C_WAIT2, T(QUOT), T(R), C_WAIT1
/* cinfo */
#define T_CINFO     C_INTERVAL1, \
    T(C), T(I), T(N), T(F), T(O), T(ENT), C_WAIT1
/* neofetch */
#define T_NEOFETCH  C_INTERVAL1, \
    T(N), T(E), T(O), T(F), T(E), T(T), T(C), T(H), T(ENT), C_WAIT1
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
/* curl -H "Accept-Language: de" wttr.in */
#define T_WEATHER   C_INTERVAL1, \
    T(C), T(U), T(R), T(L), T(SPC), \
    T(MINS), D(LSFT), T(H), U(LSFT), T(SPC), \
    D(LSFT), T(QUOT), T(A), U(LSFT), T(C), T(C), T(E), T(P), T(T), T(MINS), \
    D(LSFT), T(L), U(LSFT), T(A), T(N), T(G), T(U), T(A), T(G), T(E), \
    D(LSFT), T(SCLN), U(LSFT), T(SPC), \
    T(D), T(E), D(LSFT), T(QUOT), U(LSFT), T(SPC), \
    T(W), T(T), T(T), T(R), T(DOT), T(I), T(N), T(ENT), C_WAIT1
/* curl "https://corona-stats.online?top=25&source=2&minimal=true" */
#define T_COVID     C_INTERVAL1, \
    T(C), T(U), T(R), T(L), T(SPC), \
    D(LSFT), T(QUOT), U(LSFT), T(H), T(T), T(T), T(P), T(S), \
    D(LSFT), T(SCLN), U(LSFT), T(SLSH), T(SLSH), \
    T(C), T(O), T(R), T(O), T(N), T(A), T(MINS), \
    T(S), T(T), T(A), T(T), T(S), T(DOT), T(O), T(N), T(L), T(I), T(N), T(E), \
    D(LSFT), T(SLSH), U(LSFT), T(T), T(O), T(P), T(EQL), T(2), T(5), \
    D(LSFT), T(7), U(LSFT), T(S), T(O), T(U), T(R), T(C), T(E), T(EQL), T(2), \
    D(LSFT), T(7), U(LSFT), T(M), T(I), T(N), T(I), T(M), T(A), T(L), T(EQL), \
    T(T), T(R), T(U), T(E), D(LSFT), T(QUOT), U(LSFT), T(ENT), C_WAIT1
/* terminal_colors.sh */
#define T_TERMCOLOR C_INTERVAL1, \
    T(T), T(E), T(R), T(M), T(I), T(N), T(A), T(L), D(LSFT), T(MINS), U(LSFT), \
    T(C), T(O), T(L), T(O), T(R), T(S), T(DOT), T(S), T(H), T(ENT), C_WAIT1
/* telnet towel.blinkenlights.nl */
#define T_STARWARS  C_INTERVAL1, \
    T(T), T(E), T(L), T(N), T(E), T(T), T(SPC), \
    T(T), T(O), T(W), T(E), T(L), T(DOT), \
    T(B), T(L), T(I), T(N), T(K), T(E), T(N), \
    T(L), T(I), T(G), T(H), T(T), T(S), T(DOT), \
    T(N), T(L), T(ENT), C_WAIT1
/* kodi */
#define T_KODI      C_INTERVAL1, \
    T(K), T(O), T(D), T(I), T(ENT), C_WAIT1
/* minetest --logfile '' */
#define T_MINETEST  C_INTERVAL1, \
    T(M), T(I), T(N), T(E), T(T), T(E), T(S), T(T), T(SPC), \
    T(MINS), T(MINS), T(L), T(O), T(G), T(F), T(I), T(L), T(E), T(SPC), \
    T(QUOT), T(QUOT), T(ENT), C_WAIT1

#define AC_AUTO     ACTION_MACRO(AUTOSTART)
#define AC_SSH      ACTION_MACRO(OPENSSH)
#define AC_BOOT     ACTION_MACRO(REBOOT)
#define AC_TERM     ACTION_MACRO(TERMINAL)
#define AC_FONT     ACTION_MACRO(FONTSIZE)
#define AC_VTOY     ACTION_MACRO(VENTOY)
#define AC_WTHR     ACTION_MACRO(WEATHER)
#define AC_COV      ACTION_MACRO(COVID)
#define AC_NEOF     ACTION_MACRO(NEOFETCH)
#define AC_NEXT     ACTION_MACRO(BOOTNEXT)
#define AC_TCOL     ACTION_MACRO(TERMCOLOR)
#define AC_STAR     ACTION_MACRO(STARWARS)
#define AC_KODI     ACTION_MACRO(KODI)
#define AC_MINE     ACTION_MACRO(MINETEST)

enum macro_id {
    AUTOSTART,
    OPENSSH,
    REBOOT,
    TERMINAL,
    FONTSIZE,
    VENTOY,
    WEATHER,
    COVID,
    NEOFETCH,
    BOOTNEXT,
    TERMCOLOR,
    STARWARS,
    KODI,
    MINETEST,
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
    switch (id) {
        case AUTOSTART:
            return (record->event.pressed ?
                    MACRO( \
                        O_DESK2, O_TERM, T_CLEAR, T_CINFO, \
                        O_WEB, \
                        O_DESK1, O_TERM, T_CLEAR, T_RANGER, \
                        O_DESK4, O_DESK1, O_DESK2, \
                        END ) :
                    MACRO_NONE );
        case OPENSSH:
            return (record->event.pressed ?
                    MACRO( \
                        O_SSH1, O_SSH2, \
                        END ) :
                    MACRO_NONE );
        case REBOOT:
            return (record->event.pressed ?
                    MACRO( \
                        O_DMENU, T_REBOOT, \
                        END ) :
                    MACRO_NONE );
        case TERMINAL:
            return (record->event.pressed ?
                    MACRO( \
                        O_DMENU, T_ST, \
                        END ) :
                    MACRO_NONE );
        case FONTSIZE:
            return (record->event.pressed ?
                    MACRO( \
                        O_FONTSIZE, \
                        END ) :
                    MACRO_NONE );
        case VENTOY:
            return (record->event.pressed ?
                    MACRO( \
                        O_TERMFLOAT, T_CLEAR, T_VENTOY, \
                        END ) :
                    MACRO_NONE );
        case WEATHER:
            return (record->event.pressed ?
                    MACRO( \
                        O_TERMFLOAT, T_CLEAR, T_WEATHER, \
                        END ) :
                    MACRO_NONE );
        case COVID:
            return (record->event.pressed ?
                    MACRO( \
                        O_TERMFLOAT, T_CLEAR, T_COVID, \
                        END ) :
                    MACRO_NONE );
        case NEOFETCH:
            return (record->event.pressed ?
                    MACRO( \
                        O_TERMFLOAT, T_CLEAR, T_NEOFETCH, \
                        END ) :
                    MACRO_NONE );
        case BOOTNEXT:
            return (record->event.pressed ?
                    MACRO( \
                        O_TERMFLOAT, T_CLEAR, T_BOOTNEXT, \
                        END ) :
                    MACRO_NONE );
        case TERMCOLOR:
            return (record->event.pressed ?
                    MACRO( \
                        O_TERMFLOAT, T_CLEAR, T_TERMCOLOR, \
                        END ) :
                    MACRO_NONE );
        case STARWARS:
            return (record->event.pressed ?
                    MACRO( \
                        O_TERMFLOAT, T_CLEAR, T_STARWARS, \
                        END ) :
                    MACRO_NONE );
        case KODI:
            return (record->event.pressed ?
                    MACRO( \
                        O_DMENU, T_KODI, O_DESK9, \
                        END ) :
                    MACRO_NONE );
        case MINETEST:
            return (record->event.pressed ?
                    MACRO( \
                        O_DMENU, T_MINETEST, O_DESK10, \
                        END ) :
                    MACRO_NONE );
    }
    return MACRO_NONE;
}
