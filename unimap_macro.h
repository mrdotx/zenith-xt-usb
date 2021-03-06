/*:
 * path:   /home/klassiker/.local/share/repos/zenith-xt-usb/unimap_macro.h
 * author: klassiker [mrdotx]
 * github: https://github.com/mrdotx/zenith-usb
 * date:   2021-03-06T19:40:19+0100
 */

#define C_INTERVAL  I(5)
#define C_WAIT      W(100)

#define O_TERMINAL  D(LGUI), T(ENT), U(LGUI), W(255)
#define O_DMENU     D(LSFT), T(LGUI), U(LSFT), C_WAIT
#define O_WEB       D(LGUI), T(W), U(LGUI), C_WAIT
#define O_TOP       D(LGUI), T(T), U(LGUI), C_WAIT
#define O_DESK2     D(LGUI), T(2), U(LGUI), C_WAIT
#define O_LAYOUT    D(LGUI), T(SPC), U(LGUI), T(LEFT), T(LEFT), T(LEFT), T(ENT), C_WAIT
#define O_FOCUS     D(LGUI), T(LEFT), U(LGUI), C_WAIT
#define O_PI        D(LGUI), T(H), U(LGUI), C_WAIT
#define O_PI2       D(LGUI), D(LSFT), T(H), U(LSFT), U(LGUI), C_WAIT

#define T_REBOOT    T(R), T(E), T(B), T(O), T(O), T(T), T(ENT), C_WAIT
#define T_RANGER    T(R), T(G), T(ENT), C_WAIT
#define T_CINFO     T(C), T(L), T(ENT), C_WAIT

/* xset r rate 200 50; setxkbmap -model pc105 -layout us,de -option grp:caps_switch */
#define T_KEYBOARD  T(X), T(S), T(E), T(T), T(SPC), \
                    T(R), T(SPC), \
                    T(R), T(A), T(T), T(E), T(SPC), \
                    T(2), T(0), T(0), T(SPC), \
                    T(5), T(0), T(SCLN), T(SPC), \
                    T(S), T(E), T(T), T(X), T(K), T(B), T(M), T(A), T(P), T(SPC), \
                    T(MINS), T(M), T(O), T(D), T(E), T(L), T(SPC), \
                    T(P), T(C), T(1), T(0), T(5), T(SPC), \
                    T(MINS), T(L), T(A), T(Y), T(O), T(U), T(T), T(SPC), \
                    T(U), T(S), T(COMM), T(D), T(E), T(SPC), \
                    T(MINS), T(O), T(P), T(T), T(I), T(O), T(N), T(SPC), \
                    T(G), T(R), T(P), D(LSFT), T(SCLN), U(LSFT), T(C), T(A), T(P), T(S), D(LSFT), T(MINS), U(LSFT), T(S), T(W), T(I), T(T), T(C), T(H), T(ENT), C_WAIT

#define AC_M0       ACTION_MACRO(SETKB)
#define AC_M1       ACTION_MACRO(AUTOSTART)
#define AC_M2       ACTION_MACRO(OPENSSH)
#define AC_M3       ACTION_MACRO(REBOOT)

enum macro_id {
    SETKB,
    AUTOSTART,
    OPENSSH,
    REBOOT,
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
                        /* open web browser, system monitor and go to desktop 2 */
                        O_WEB, O_TOP, O_DESK2, \
                        /* open terminal and open ranger */
                        O_TERMINAL, T_RANGER, \
                        /* open another terminal and open cinfo */
                        O_TERMINAL, T_CINFO, \
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
        case REBOOT:
            return (record->event.pressed ?
                    MACRO( \
                        /* set typing interval */
                        C_INTERVAL, \
                        /* open dmenu and execute reboot */
                        O_DMENU, T_REBOOT, \
                        END ) :
                    MACRO_NONE );
    }
    return MACRO_NONE;
}
