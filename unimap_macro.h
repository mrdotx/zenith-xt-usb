/*
 * path:   /home/klassiker/.local/share/repos/zenith-xt-usb/unimap_macro.h
 * author: klassiker [mrdotx]
 * github: https://github.com/mrdotx/zenith-usb
 * date:   2021-03-04T08:45:21+0100
 */

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
#define T_RANGER    T(SPC), T(R), T(G)
#define T_CINFO     T(SPC), T(C), T(L)
#define T_KEYBOARD  T(SPC), T(K), T(B)

#define AC_M0       ACTION_MACRO(SETKB)
#define AC_M1       ACTION_MACRO(AUTOSTART)
#define AC_M2       ACTION_MACRO(OPENSSH)

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
                        /* open terminal, set keyboard options and close terminal */
                        O_TERMINAL, T_KEYBOARD, T(SCLN), T_EXIT, T(ENT), \
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
                        /* open another terminal and execute cinfo */
                        O_TERMINAL, T_CINFO, T(ENT), W(100), \
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
