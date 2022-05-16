/*
 * path:   /home/klassiker/.local/share/repos/zenith-xt-usb/unimap_macro.h
 * author: klassiker [mrdotx]
 * github: https://github.com/mrdotx/zenith-usb
 * date:   2022-05-16T10:10:34+0200
 */

/* general config */
#define C_INTERVAL I(15)
#define C_WAIT     W(255)

/* open i3_exit */
#define O_I3_EXIT   C_INTERVAL, \
    D(LCTL), D(LALT), D(DEL), U(DEL), U(LALT), U(LCTL), T(R)
/* change terminal font size */
#define O_FONTSIZE  C_INTERVAL, \
    D(LCTL), D(LSFT), \
    T(EQL), T(EQL), T(EQL), T(EQL), T(EQL), T(EQL), T(EQL), T(EQL), \
    U(LSFT), U(LCTL), C_WAIT

#define AC_FONT     ACTION_MACRO(FONTSIZE)

enum macro_id {
    FONTSIZE,
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
    switch (id) {
        case FONTSIZE:
            return (record->event.pressed ?
                MACRO( \
                    O_FONTSIZE, \
                    END ) :
                MACRO_NONE );
    }
    return MACRO_NONE;
}
