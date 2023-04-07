/*
 * path:   /home/klassiker/.local/share/repos/zenith-xt-usb/unimap_macro.h
 * author: klassiker [mrdotx]
 * github: https://github.com/mrdotx/zenith-xt-usb
 * date:   2023-04-06T18:28:47+0200
 */

/* general config */
#define C_INTERVAL I(15)
#define C_WAIT     W(255)

/* increase terminal font size */
#define O_INCREASETERMINALFONTSIZE  C_INTERVAL, \
    D(LCTL), D(LSFT), \
    T(EQL), T(EQL), T(EQL), T(EQL), \
    U(LSFT), U(LCTL), C_WAIT
/* decrease terminal font size */
#define O_DECREASETERMINALFONTSIZE  C_INTERVAL, \
    D(LCTL), \
    T(MINS), T(MINS), T(MINS), T(MINS), \
    U(LCTL), C_WAIT

#define AC_ITFS     ACTION_MACRO(INCREASETERMINALFONTSIZE)
#define AC_DTFS     ACTION_MACRO(DECREASETERMINALFONTSIZE)

enum macro_id {
    INCREASETERMINALFONTSIZE,
    DECREASETERMINALFONTSIZE,
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
    switch (id) {
        case INCREASETERMINALFONTSIZE:
            return (record->event.pressed ?
                MACRO( \
                    O_INCREASETERMINALFONTSIZE, \
                    END ) :
                MACRO_NONE );
        case DECREASETERMINALFONTSIZE:
            return (record->event.pressed ?
                MACRO( \
                    O_DECREASETERMINALFONTSIZE, \
                    END ) :
                MACRO_NONE );
    }
    return MACRO_NONE;
}
