/*
 * path:   /home/klassiker/.local/share/repos/zenith-xt-usb/config.h
 * author: klassiker [mrdotx]
 * github: https://github.com/mrdotx/zenith-usb
 * date:   2021-02-28T12:53:40+0100
 */

#ifndef CONFIG_H
#define CONFIG_H

#include <avr/interrupt.h>

#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0x1bee
#define DEVICE_VER      0x0001
#define MANUFACTURER    t.m.k.
#define PRODUCT         Zenith keyboard converter
#define DESCRIPTION     convert Zenith keyboard to USB

/* matrix size */
#define MATRIX_ROWS 16  // keycode bit: 6-3
#define MATRIX_COLS 8   // keycode bit: 2-0

/* key combination for command */
#define IS_COMMAND() ( \
    keyboard_report->mods == (MOD_BIT(KC_LSHIFT) | MOD_BIT(KC_RSHIFT)) \
)

// G80-2551 terminal keyboard support
#define G80_2551_SUPPORT

/*
 * Pin and interrupt configuration
 */
#if defined(__AVR_ATmega32U4__) || defined(__AVR_ATmega32U2__) || defined(__AVR_AT90USB1286__)
/* clock line */
#define IBMPC_CLOCK_PORT  PORTD
#define IBMPC_CLOCK_PIN   PIND
#define IBMPC_CLOCK_DDR   DDRD
#define IBMPC_CLOCK_BIT   1
/* data line */
#define IBMPC_DATA_PORT   PORTD
#define IBMPC_DATA_PIN    PIND
#define IBMPC_DATA_DDR    DDRD
#define IBMPC_DATA_BIT    0
/* reset line */
#define IBMPC_RST_PORT    PORTB
#define IBMPC_RST_PIN     PINB
#define IBMPC_RST_DDR     DDRB
#define IBMPC_RST_BIT1    6
#define IBMPC_RST_BIT2    7

/* reset for XT Type-1 keyboard: low pulse for 500ms */
#define IBMPC_RST_HIZ() do { \
    IBMPC_RST_PORT &= ~(1<<IBMPC_RST_BIT1);  \
    IBMPC_RST_DDR  &= ~(1<<IBMPC_RST_BIT1);  \
    IBMPC_RST_PORT &= ~(1<<IBMPC_RST_BIT2);  \
    IBMPC_RST_DDR  &= ~(1<<IBMPC_RST_BIT2);  \
} while (0)

#define IBMPC_RST_LO() do { \
    IBMPC_RST_PORT &= ~(1<<IBMPC_RST_BIT1);  \
    IBMPC_RST_DDR  |=  (1<<IBMPC_RST_BIT1);  \
    IBMPC_RST_PORT &= ~(1<<IBMPC_RST_BIT2);  \
    IBMPC_RST_DDR  |=  (1<<IBMPC_RST_BIT2);  \
} while (0)

/* interrupt for clock line */
#define IBMPC_INT_INIT()  do {  \
    EICRA |= ((1<<ISC11) |      \
              (0<<ISC10));      \
} while (0)

/* NOTE: clear flag and enabling to ditch unwanted interrupt */
#define IBMPC_INT_ON()  do {    \
    EIFR  |= (1<<INTF1);        \
    EIMSK |= (1<<INT1);         \
} while (0)

#define IBMPC_INT_OFF() do {    \
    EIMSK &= ~(1<<INT1);        \
} while (0)

#define IBMPC_INT_VECT    INT1_vect

#else
#error "No pin configuration in config.h"
#endif

#endif
