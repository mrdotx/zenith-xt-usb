/*
 * path:   /home/klassiker/Projects/repos/zenith-xt-usb/zenith_usb.h
 * author: klassiker [mrdotx]
 * url:    https://github.com/mrdotx/zenith-xt-usb
 * date:   2026-06-14T04:59:41+0200
 */

#ifndef IBMPC_USB_H
#define IBMPC_USB_H

typedef enum { NONE, PC_XT, PC_AT, PC_TERMINAL, PC_AT_Z150 } keyboard_kind_t;
#define KEYBOARD_KIND_STR(kind) \
    (kind == PC_XT ? "XT" :   \
     kind == PC_AT ? "AT" :   \
     kind == PC_TERMINAL ? "TERMINAL" :   \
     kind == PC_AT_Z150 ? "AT_Z150" :  \
     "NONE")

extern uint16_t keyboard_id;
extern keyboard_kind_t keyboard_kind;

#endif
