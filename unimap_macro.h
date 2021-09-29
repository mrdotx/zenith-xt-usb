/*
 * path:   /home/klassiker/.local/share/repos/zenith-xt-usb/unimap_macro.h
 * author: klassiker [mrdotx]
 * github: https://github.com/mrdotx/zenith-usb
 * date:   2021-09-28T20:54:34+0200
 */

/* general config */
#define C_INTERVAL1 I(1)
#define C_INTERVAL2 I(12)
#define C_WAIT1     W(100)
#define C_WAIT2     W(255)

/* open autostart */
#define O_AUTOSTART C_INTERVAL2, \
    D(LSFT), D(LGUI), T(PSCR), U(LGUI), U(LSFT), C_WAIT2
/* open dmenu */
#define O_DMENU     C_INTERVAL2, \
    D(LSFT), T(LGUI), U(LSFT), C_WAIT2
/* change terminal font size */
#define O_FONTSIZE  C_INTERVAL2, \
    D(LCTL), D(LSFT), \
    T(EQL), T(EQL), T(EQL), T(EQL), T(EQL), T(EQL), T(EQL), T(EQL), \
    U(LSFT), U(LCTL), C_WAIT2

/* reboot */
#define T_REBOOT    C_INTERVAL1, \
    T(R), T(E), T(B), T(O), T(O), T(T), T(ENT), C_WAIT1

#define AC_AUTO     ACTION_MACRO(AUTOSTART)
#define AC_BOOT     ACTION_MACRO(REBOOT)
#define AC_FONT     ACTION_MACRO(FONTSIZE)

enum macro_id {
    AUTOSTART,
    REBOOT,
    FONTSIZE,
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
    switch (id) {
        case AUTOSTART:
            return (record->event.pressed ?
                MACRO( \
                    O_AUTOSTART, \
                    END ) :
                MACRO_NONE );
        case REBOOT:
            return (record->event.pressed ?
                MACRO( \
                    O_DMENU, T_REBOOT, \
                    END ) :
                MACRO_NONE );
        case FONTSIZE:
            return (record->event.pressed ?
                MACRO( \
                    O_FONTSIZE, \
                    END ) :
                MACRO_NONE );
    }
    return MACRO_NONE;
}
