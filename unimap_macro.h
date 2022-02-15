/*
 * path:   /home/klassiker/.local/share/repos/zenith-xt-usb/unimap_macro.h
 * author: klassiker [mrdotx]
 * github: https://github.com/mrdotx/zenith-usb
 * date:   2022-02-15T09:11:28+0100
 */

/* general config */
#define C_INTERVAL1 I(1)
#define C_INTERVAL2 I(15)
#define C_WAIT1     W(100)
#define C_WAIT2     W(255)

/* open i3_exit */
#define O_I3_EXIT   C_INTERVAL2, \
    D(LCTL), D(LALT), D(DEL), U(DEL), U(LALT), U(LCTL), T(R)
/* change terminal font size */
#define O_FONTSIZE  C_INTERVAL2, \
    D(LCTL), D(LSFT), \
    T(EQL), T(EQL), T(EQL), T(EQL), T(EQL), T(EQL), T(EQL), T(EQL), \
    U(LSFT), U(LCTL), C_WAIT2

#define AC_BOOT     ACTION_MACRO(REBOOT)
#define AC_FONT     ACTION_MACRO(FONTSIZE)

enum macro_id {
    REBOOT,
    FONTSIZE,
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
    switch (id) {
        case REBOOT:
            return (record->event.pressed ?
                MACRO( \
                    O_I3_EXIT, \
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
