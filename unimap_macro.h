/*
 * path:   /home/klassiker/.local/share/repos/zenith-xt-usb/unimap_macro.h
 * author: klassiker [mrdotx]
 * github: https://github.com/mrdotx/zenith-usb
 * date:   2021-03-04T14:00:01+0100
 */

#define C_INTERVAL  I(5)
#define C_WAIT      W(100)

#define O_TERMINAL  D(LGUI), T(ENT), U(LGUI), W(255)
#define O_WEB       D(LGUI), T(W), U(LGUI), C_WAIT
#define O_TOP       D(LGUI), T(T), U(LGUI), C_WAIT
#define O_DESK2     D(LGUI), T(2), U(LGUI), C_WAIT
#define O_LAYOUT    D(LGUI), T(SPC), U(LGUI), T(LEFT), T(LEFT), T(LEFT), T(ENT), C_WAIT
#define O_FOCUS     D(LGUI), T(LEFT), U(LGUI), C_WAIT
#define O_PI        D(LGUI), T(H), U(LGUI), C_WAIT
#define O_PI2       D(LGUI), D(LSFT), T(H), U(LSFT), U(LGUI), C_WAIT

#define T_EXIT      T(E), T(X), T(I), T(T), T(ENT), C_WAIT
#define T_REBOOT    T(R), T(E), T(B), T(O), T(O), T(T), T(ENT), C_WAIT
#define T_RANGER    T(R), T(G), T(ENT), C_WAIT
#define T_CINFO     T(C), T(L), T(ENT), C_WAIT
#define T_KEYBOARD  T(K), T(B), T(ENT), C_WAIT

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
                        /* open terminal, set keyboard options and close terminal */
                        O_TERMINAL, T_KEYBOARD, T_EXIT, \
                        END ) :
                    MACRO_NONE );
        case AUTOSTART:
            return (record->event.pressed ?
                    MACRO( \
                        /* set typing interval */
                        C_INTERVAL, \
                        /* open web browser, system monitor and go to desktop 2 */
                        O_WEB, O_TOP, O_DESK2, \
                        /* open terminal and execute ranger */
                        O_TERMINAL, T_RANGER, \
                        /* open another terminal and execute cinfo */
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
                        /* open terminal and execute reboot */
                        O_TERMINAL, T_REBOOT, \
                        END ) :
                    MACRO_NONE );
    }
    return MACRO_NONE;
}
