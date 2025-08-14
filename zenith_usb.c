/*
 * path:   /home/klassiker/.local/share/repos/zenith-xt-usb/zenith_usb.c
 * author: klassiker [mrdotx]
 * url:    https://github.com/mrdotx/zenith-xt-usb
 * date:   2025-08-14T03:50:13+0200
 */

#include <stdint.h>
#include <stdbool.h>
#include "print.h"
#include "util.h"
#include "debug.h"
#include "ibmpc.h"
#include "host.h"
#include "led.h"
#include "matrix.h"
#include "timer.h"
#include "action.h"
#include "zenith_usb.h"

static void matrix_make(uint8_t code);
static void matrix_break(uint8_t code);

static int8_t process_cs1(uint8_t code);
static int8_t process_cs2(uint8_t code);
static int8_t process_cs3(uint8_t code);

static uint8_t matrix[MATRIX_ROWS];
#define ROW(code)      ((code>>3)&0x0F)
#define COL(code)      (code&0x07)

static int16_t read_wait(uint16_t wait_ms)
{
    uint16_t start = timer_read();
    int16_t code;
    while ((code = ibmpc_host_recv()) == -1 && timer_elapsed(start) < wait_ms);
    return code;
}

static uint16_t read_keyboard_id(void)
{
    uint16_t id = 0;
    int16_t  code = 0;

    // temporary fix Z-150 AT should response with ID
    if (ibmpc_protocol == IBMPC_PROTOCOL_AT_Z150) return 0xFFFD;

    // Disable
    //code = ibmpc_host_send(0xF5);

    // Read ID
    code = ibmpc_host_send(0xF2);
    if (code == -1) { id = 0xFFFF; goto DONE; }     // XT or No keyboard
    if (code != 0xFA) { id = 0xFFFE; goto DONE; }   // Broken PS/2?

    // ID takes 500ms max TechRef [8] 4-41
    code = read_wait(500);
    if (code == -1) { id = 0x0000; goto DONE; }     // AT
    id = (code & 0xFF)<<8;

    // Mouse responds with one-byte 00, this returns 00FF [y] p.14
    code = read_wait(500);
    id |= code & 0xFF;

DONE:
    // Enable
    //code = ibmpc_host_send(0xF4);

    return id;
}

void hook_early_init(void)
{
    ibmpc_host_init();
    ibmpc_host_enable();
}

void matrix_init(void)
{
    debug_enable = true;

    // initialize matrix state: all keys off
    for (uint8_t i=0; i < MATRIX_ROWS; i++) matrix[i] = 0x00;

    return;
}

/*
 * keyboard recognition
 *
 * 1. Send F2 to get keyboard ID
 *      a. no ACK(FA): XT keyobard
 *      b. ACK but no ID: 84-key AT keyboard CodeSet2
 *      c. ID is AB 83: PS/2 keyboard CodeSet2
 *      d. ID is BF BF: Terminal keyboard CodeSet3
 *      e. error on recv: maybe broken PS/2
 */
uint8_t current_protocol = 0;
uint16_t keyboard_id = 0x0000;
keyboard_kind_t keyboard_kind = NONE;
uint8_t matrix_scan(void)
{
    // scan code reading states
    static enum {
        INIT,
        WAIT_SETTLE,
        AT_RESET,
        XT_RESET,
        XT_RESET_WAIT,
        XT_RESET_DONE,
        WAIT_AA,
        WAIT_AABF,
        WAIT_AABFBF,
        READ_ID,
        SETUP,
        LOOP,
    } state = INIT;
    static uint16_t init_time;

    if (ibmpc_error) {
        xprintf("\nERR:%02X ISR:%04X ", ibmpc_error, ibmpc_isr_debug);

        // when recv error, neither send error nor buffer full
        if (!(ibmpc_error & (IBMPC_ERR_SEND | IBMPC_ERR_FULL))) {
            // keyboard init again
            if (state == LOOP) {
                xprintf("[RST] ");
                state = INIT;
            }
        }

        // clear or process error
        ibmpc_error = IBMPC_ERR_NONE;
        ibmpc_isr_debug = 0;
    }

    // check protocol change AT/XT
    if (ibmpc_protocol && ibmpc_protocol != current_protocol) {
        xprintf("\nPRT:%02X ISR:%04X ", ibmpc_protocol, ibmpc_isr_debug);

        // protocol change between AT and XT indicates that
        // keyboard is hotswapped or something goes wrong.
        // This requires initializing keyboard again probably.
        if (((current_protocol&IBMPC_PROTOCOL_XT) && (ibmpc_protocol&IBMPC_PROTOCOL_AT)) ||
            ((current_protocol&IBMPC_PROTOCOL_AT) && (ibmpc_protocol&IBMPC_PROTOCOL_XT))) {
            if (state == LOOP) {
                xprintf("[CHG] ");
                state = INIT;
            }
        }

        current_protocol = ibmpc_protocol;
        ibmpc_isr_debug = 0;
    }

    switch (state) {
        case INIT:
            ibmpc_host_disable();

            xprintf("I%u ", timer_read());
            keyboard_kind = NONE;
            keyboard_id = 0x0000;
            current_protocol = 0;

            matrix_clear();
            clear_keyboard();

            init_time = timer_read();
            state = WAIT_SETTLE;
            break;
        case WAIT_SETTLE:
            // wait for keyboard to settle after plugin
            if (timer_elapsed(init_time) > 1000) {
                state = AT_RESET;
            }
            break;
        case AT_RESET:
            ibmpc_host_isr_clear();
            ibmpc_host_enable();
            wait_ms(1); // keyboard can't respond to command without this

            // SKIDATA-2-DE(and some other keyboards?) stores 'Code Set' setting in nonvlatile memory
            // and keeps it until receiving reset. Sending reset here may be useful to clear it, perhaps.
            // https://github.com/tmk/tmk_keyboard/wiki/IBM-PC-AT-Keyboard-Protocol#select-alternate-scan-codesf0

            // reset command
            if (0xFA == ibmpc_host_send(0xFF)) {
                state = WAIT_AA;
            } else {
                state = XT_RESET;
            }
            xprintf("A%u ", timer_read());
            break;
        case XT_RESET:
            // Reset XT-initialize keyboard
            // XT: hard reset 500ms for IBM XT Type-1 keyboard and clones
            // XT: soft reset 20ms min
            // https://github.com/tmk/tmk_keyboard/wiki/IBM-PC-XT-Keyboard-Protocol#keyboard-soft-reset
            ibmpc_host_disable();   // soft reset: Clock Lo/Data Hi
            IBMPC_RST_LO();         // hard reset: Reset pin Lo

            init_time = timer_read();
            state = XT_RESET_WAIT;
            break;
        case XT_RESET_WAIT:
            if (timer_elapsed(init_time) > 500) {
                state = XT_RESET_DONE;
            }
            break;
        case XT_RESET_DONE:
            IBMPC_RST_HIZ();        // hard reset: Reset pin HiZ
            ibmpc_host_isr_clear();
            ibmpc_host_enable();    // soft reset: idle(Clock Hi/Data Hi)

            xprintf("X%u ", timer_read());
            init_time = timer_read();
            state = WAIT_AA;
            break;
        case WAIT_AA:
            // 1) Read BAT code and ID on keybaord power-up
            // For example, XT/AT sends 'AA' and Terminal sends 'AA BF BF' after BAT
            // AT 84-key: POR and BAT can take 900-9900ms according to AT TechRef [8] 4-7
            // AT 101/102-key: POR and BAT can take 450-2500ms according to AT TechRef [8] 4-39
            // 2) Read key typed by user or anything after error on protocol or scan code
            // This can happen in case of keyboard hotswap, unstable hardware, signal integrity problem or bug

            /* wait until keyboard sends any code without 10000ms timeout
            if (timer_elapsed(init_time) > 10000) {
                state = READ_ID;
            }
            */
            if (ibmpc_host_recv() != -1) {  // wait for AA
                xprintf("W%u ", timer_read());
                init_time = timer_read();
                state = WAIT_AABF;
            }
            break;
        case WAIT_AABF:
            // NOTE: we can omit to wait BF BF
            // ID takes 500ms max? TechRef [8] 4-41, though 1ms is enough for 122-key Terminal 6110345
            if (timer_elapsed(init_time) > 500) {
                state = READ_ID;
            }
            if (ibmpc_host_recv() != -1) {  // wait for BF
                xprintf("W%u ", timer_read());
                init_time = timer_read();
                state = WAIT_AABFBF;
            }
            break;
        case WAIT_AABFBF:
            if (timer_elapsed(init_time) > 500) {
                state = READ_ID;
            }
            if (ibmpc_host_recv() != -1) {  // wait for BF
                xprintf("W%u ", timer_read());
                state = READ_ID;
            }
            break;
        case READ_ID:
            keyboard_id = read_keyboard_id();
            xprintf("R%u ", timer_read());

            if (0x0000 == keyboard_id) {            // CodeSet2 AT(IBM PC AT 84-key)
                keyboard_kind = PC_AT;
            } else if (0xFFFF == keyboard_id) {     // CodeSet1 XT
                keyboard_kind = PC_XT;
            } else if (0xFFFE == keyboard_id) {     // CodeSet2 PS/2 fails to response?
                keyboard_kind = PC_AT;
            } else if (0xFFFD == keyboard_id) {     // Zenith Z-150 AT
                keyboard_kind = PC_AT_Z150;
            } else if (0x00FF == keyboard_id) {     // Mouse is not supported
                xprintf("Mouse: not supported\n");
                keyboard_kind = NONE;
#ifdef G80_2551_SUPPORT
            } else if (0xAB86 == keyboard_id ||
                       0xAB85 == keyboard_id) {     // For G80-2551 and other 122-key terminal
                // https://github.com/tmk/tmk_keyboard/wiki/IBM-PC-AT-Keyboard-Protocol#ab86
                // https://github.com/tmk/tmk_keyboard/wiki/IBM-PC-AT-Keyboard-Protocol#ab85

                if ((0xFA == ibmpc_host_send(0xF0)) &&
                    (0xFA == ibmpc_host_send(0x03))) {
                    // switch to code set 3
                    keyboard_kind = PC_TERMINAL;
                } else {
                    keyboard_kind = PC_AT;
                }
#endif
            } else if (0xBFB0 == keyboard_id) {     // IBM RT Keyboard
                // https://github.com/tmk/tmk_keyboard/wiki/IBM-PC-AT-Keyboard-Protocol#bfb0
                // TODO: LED indicator fix
                //keyboard_kind = PC_TERMINAL_IBM_RT;
                keyboard_kind = PC_TERMINAL;
            } else if (0xAB00 == (keyboard_id & 0xFF00)) {  // CodeSet2 PS/2
                keyboard_kind = PC_AT;
            } else if (0xBF00 == (keyboard_id & 0xFF00)) {  // CodeSet3 Terminal
                keyboard_kind = PC_TERMINAL;
            } else {
                keyboard_kind = PC_AT;
            }

            xprintf("\nID:%04X(%s) ", keyboard_id, KEYBOARD_KIND_STR(keyboard_kind));

            state = SETUP;
            break;
        case SETUP:
            xprintf("S%u ", timer_read());
            switch (keyboard_kind) {
                case PC_XT:
                    break;
                case PC_AT:
                    led_set(host_keyboard_leds());
                    break;
                case PC_AT_Z150:
                    // TODO: do not set indicators temporarily for debug
                    break;
                case PC_TERMINAL:
                    // Set all keys to make/break type
                    ibmpc_host_send(0xF8);
                    // This should not be harmful
                    led_set(host_keyboard_leds());
                    break;
                default:
                    break;
            }
            state = LOOP;
            xprintf("L%u ", timer_read());
        case LOOP:
            {
                uint16_t code = ibmpc_host_recv();
                if (code == -1) {
                    // no code
                    break;
                }

                // Keyboard Error/Overrun([3]p.26) or Buffer full
                // Scan Code Set 1: 0xFF
                // Scan Code Set 2 and 3: 0x00
                // Buffer full(IBMPC_ERR_FULL): 0xFF
                if (code == 0x00 || code == 0xFF) {
                    // clear stuck keys
                    matrix_clear();
                    clear_keyboard();

                    xprintf("\n[OVR] ");
                    break;
                }

                switch (keyboard_kind) {
                    case PC_XT:
                        if (process_cs1(code) == -1) state = INIT;
                        break;
                    case PC_AT:
                    case PC_AT_Z150:
                        if (process_cs2(code) == -1) state = INIT;
                        break;
                    case PC_TERMINAL:
                        if (process_cs3(code) == -1) state = INIT;
                        break;
                    default:
                        break;
                }
            }
            break;
        default:
            break;
    }
    return 1;
}

inline
bool matrix_is_on(uint8_t row, uint8_t col)
{
    return (matrix[row] & (1<<col));
}

inline
uint8_t matrix_get_row(uint8_t row)
{
    return matrix[row];
}

uint8_t matrix_key_count(void)
{
    uint8_t count = 0;
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
        count += bitpop(matrix[i]);
    }
    return count;
}

inline
static void matrix_make(uint8_t code)
{
    if (!matrix_is_on(ROW(code), COL(code))) {
        matrix[ROW(code)] |= 1<<COL(code);
    }
}

inline
static void matrix_break(uint8_t code)
{
    if (matrix_is_on(ROW(code), COL(code))) {
        matrix[ROW(code)] &= ~(1<<COL(code));
    }
}

void matrix_clear(void)
{
    for (uint8_t i=0; i < MATRIX_ROWS; i++) matrix[i] = 0x00;
}

void led_set(uint8_t usb_led)
{
    // Sending before keyboard recognition may be harmful for XT keyboard
    if (keyboard_kind == NONE) return;

    // XT keyobard doesn't support any command and it is harmful perhaps
    // https://github.com/tmk/tmk_keyboard/issues/635#issuecomment-626993437
    if (keyboard_kind == PC_XT) return;

    // It should be safe to send the command to keyboards with AT protocol
    // - IBM Terminal doesn't support the command and response with 0xFE but it is not harmful.
    // - Some other Terminals like G80-2551 supports the command.
    //   https://geekhack.org/index.php?topic=103648.msg2894921#msg2894921

    // TODO: PC_TERMINAL_IBM_RT support
    uint8_t ibmpc_led = 0;
    if (usb_led &  (1<<USB_LED_SCROLL_LOCK))
        ibmpc_led |= (1<<IBMPC_LED_SCROLL_LOCK);
    if (usb_led &  (1<<USB_LED_NUM_LOCK))
        ibmpc_led |= (1<<IBMPC_LED_NUM_LOCK);
    if (usb_led &  (1<<USB_LED_CAPS_LOCK))
        ibmpc_led |= (1<<IBMPC_LED_CAPS_LOCK);
    ibmpc_host_set_led(ibmpc_led);
}

/*******************************************************************************
 * XT: Scan Code Set 1
 *
 * See [3], [a]
 *
 * E0-escaped scan codes are translated into unused range of the matrix.(54-7F)
 *
 *     01-53: Normal codes used in original XT keyboard
 *     54-7F: Not used in original XT keyboard
 *
 *         0   1   2   3   4   5   6   7   8   9   A   B   C   D   E   F
 *     50  -   -   -   -   *   *   x   x   x   x   *   *   *   *   *   *
 *     60  *   *   *   *   x   x   x   x   x   x   x   x   x   x   x   *
 *     70  x   *   *   x   *   *   x   *   *   x   *   x   *   x   x   *
 *
 * -: codes existed in original XT keyboard
 * *: E0-escaped codes translated
 * x: Non-espcaped codes(Some are not used in real keyboards probably)
 *
 * Codes assigned in range 54-7F:
 *
 *     50  -                60  Up*                 70  KANAx
 *     51  -                61  Left*               71  Insert*
 *     52  -                62  Down*               72  Delete*
 *     53  -                63  Right*              73  ROx
 *     54  PrintScr*        64  F13x                74  Home*
 *     55  Pause*           65  F14x                75  End*
 *     56  Euro2x           66  F15x                76  F24x
 *     57  F11x             67  F16x                77  PageUp*
 *     58  F12x             68  F17x                78  PageDown*
 *     59  Keypad=x         69  F18x                79  HENKANx
 *     5A  LGUI*            6A  F19x                7A  RCTL*
 *     5B  RGUI*            6B  F20x                7B  MUHENKANx
 *     5C  APP*             6C  F21x                7C  RALT*
 *     5D  Mute*            6D  F22x                7D  JPYx
 *     5E  Volume Down*     6E  F23x                7E  Keypad,x
 *     5F  Volume Up*       6F  Keypad Enter*       7F  Keypad/ *
 */
static uint8_t cs1_e0code(uint8_t code) {
    switch(code) {
        // Original IBM XT keyboard doesn't use E0-codes probably
        // Some XT compatilble keyobards need these keys?
        case 0x37: return 0x54; // Print Screen
        case 0x46: return 0x55; // Ctrl + Pause
        case 0x5B: return 0x5A; // Left  GUI
        case 0x5C: return 0x5B; // Right GUI
        case 0x5D: return 0x5C; // Application
        case 0x20: return 0x5D; // Mute
        case 0x2E: return 0x5E; // Volume Down
        case 0x30: return 0x5F; // Volume Up
        case 0x48: return 0x60; // Up
        case 0x4B: return 0x61; // Left
        case 0x50: return 0x62; // Down
        case 0x4D: return 0x63; // Right
        case 0x1C: return 0x6F; // Keypad Enter
        case 0x52: return 0x71; // Insert
        case 0x53: return 0x72; // Delete
        case 0x47: return 0x74; // Home
        case 0x4F: return 0x75; // End
        case 0x49: return 0x77; // Page Up
        case 0x51: return 0x78; // Page Down
        case 0x1D: return 0x7A; // Right Ctrl
        case 0x38: return 0x7C; // Right Alt
        case 0x35: return 0x7F; // Keypad /

        // Shared matrix cell with other keys
        case 0x5E: return 0x70; // Power (KANA)
        case 0x5F: return 0x79; // Sleep (HENKAN)
        case 0x63: return 0x7B; // Wake  (MUHENKAN)

        default:
           xprintf("!CS1_E0_%02X!\n", code);
           return code;
    }
    return 0x00;
}

static int8_t process_cs1(uint8_t code)
{
    static enum {
        INIT,
        E0,
        // Pause: E1 1D 45, E1 9D C5 [a]
        E1,
        E1_1D,
        E1_9D,
    } state = INIT;

    switch (state) {
        case INIT:
            switch (code) {
                case 0xE0:
                    state = E0;
                    break;
                case 0xE1:
                    state = E1;
                    break;
                default:
                    if (code < 0x80)
                        matrix_make(code);
                    else
                        matrix_break(code & 0x7F);
                    break;
            }
            break;
        case E0:
            switch (code) {
                case 0x2A:
                case 0xAA:
                case 0x36:
                case 0xB6:
                    //ignore fake shift
                    state = INIT;
                    break;
                default:
                    if (code < 0x80)
                        matrix_make(cs1_e0code(code));
                    else
                        matrix_break(cs1_e0code(code & 0x7F));
                    state = INIT;
                    break;
            }
            break;
        case E1:
            switch (code) {
                case 0x1D:
                    state = E1_1D;
                    break;
                case 0x9D:
                    state = E1_9D;
                    break;
                default:
                    state = INIT;
                    break;
            }
            break;
        case E1_1D:
            switch (code) {
                case 0x45:
                    matrix_make(0x55); // Pause
                    state = INIT;
                    break;
                default:
                    state = INIT;
                    break;
            }
            break;
        case E1_9D:
            switch (code) {
                case 0xC5:
                    matrix_break(0x55); // Pause
                    state = INIT;
                    break;
                default:
                    state = INIT;
                    break;
            }
            break;
        default:
            state = INIT;
    }
    return 0;
}

/*******************************************************************************
 * AT, PS/2: Scan Code Set 2
 *
 * Exceptional Handling
 * --------------------
 * Some keys should be handled exceptionally. See [b].
 *
 * Scan codes are varied or prefix/postfix'd depending on modifier key state.
 *
 * 1) Insert, Delete, Home, End, PageUp, PageDown, Up, Down, Right, Left
 *     a) when Num Lock is off
 *     modifiers | make                      | break
 *     ----------+---------------------------+----------------------
 *     Ohter     |                    <make> | <break>
 *     LShift    | E0 F0 12           <make> | <break>  E0 12
 *     RShift    | E0 F0 59           <make> | <break>  E0 59
 *     L+RShift  | E0 F0 12  E0 F0 59 <make> | <break>  E0 59 E0 12
 *
 *     b) when Num Lock is on
 *     modifiers | make                      | break
 *     ----------+---------------------------+----------------------
 *     Other     | E0 12              <make> | <break>  E0 F0 12
 *     Shift'd   |                    <make> | <break>
 *
 *     Handling: These prefix/postfix codes are ignored.
 *
 *
 * 2) Keypad /
 *     modifiers | make                      | break
 *     ----------+---------------------------+----------------------
 *     Ohter     |                    <make> | <break>
 *     LShift    | E0 F0 12           <make> | <break>  E0 12
 *     RShift    | E0 F0 59           <make> | <break>  E0 59
 *     L+RShift  | E0 F0 12  E0 F0 59 <make> | <break>  E0 59 E0 12
 *
 *     Handling: These prefix/postfix codes are ignored.
 *
 *
 * 3) PrintScreen
 *     modifiers | make         | break
 *     ----------+--------------+-----------------------------------
 *     Other     | E0 12  E0 7C | E0 F0 7C  E0 F0 12
 *     Shift'd   |        E0 7C | E0 F0 7C
 *     Control'd |        E0 7C | E0 F0 7C
 *     Alt'd     |           84 | F0 84
 *
 *     Handling: These prefix/postfix codes are ignored, and both scan codes
 *               'E0 7C' and 84 are seen as PrintScreen.
 *
 * 4) Pause
 *     modifiers | make(no break code)
 *     ----------+--------------------------------------------------
 *     Other     | E1 14 77 E1 F0 14 F0 77
 *     Control'd | E0 7E E0 F0 7E
 *
 *     Handling: Both code sequences are treated as a whole.
 *               And we need a ad hoc 'pseudo break code' hack to get the key off
 *               because it has no break code.
 *
 * Notes:
 * 'Hanguel/English'(F1) and 'Hanja'(F2) have no break code. See [a].
 * These two Korean keys need exceptional handling and are not supported for now.
 *
 */
static uint8_t cs2_e0code(uint8_t code) {
    switch(code) {
        // E0 prefixed codes translation See [a].
        case 0x11: return 0x0F; // right alt
        case 0x14: return 0x17; // right control
        case 0x1F: return 0x19; // left GUI
        case 0x27: return 0x1F; // right GUI
        case 0x2F: return 0x5C; // apps
        case 0x4A: return 0x60; // keypad /
        case 0x5A: return 0x62; // keypad enter
        case 0x69: return 0x27; // end
        case 0x6B: return 0x53; // cursor left
        case 0x6C: return 0x2F; // home
        case 0x70: return 0x39; // insert
        case 0x71: return 0x37; // delete
        case 0x72: return 0x3F; // cursor down
        case 0x74: return 0x47; // cursor right
        case 0x75: return 0x4F; // cursor up
        case 0x7A: return 0x56; // page down
        case 0x7D: return 0x5E; // page up
        case 0x7C: return 0x7F; // Print Screen
        case 0x7E: return 0x00; // Control'd Pause

        case 0x21: return 0x65; // volume down
        case 0x32: return 0x6E; // volume up
        case 0x23: return 0x6F; // mute
        case 0x10: return 0x08; // (WWW search)     -> F13
        case 0x18: return 0x10; // (WWW favourites) -> F14
        case 0x20: return 0x18; // (WWW refresh)    -> F15
        case 0x28: return 0x20; // (WWW stop)       -> F16
        case 0x30: return 0x28; // (WWW forward)    -> F17
        case 0x38: return 0x30; // (WWW back)       -> F18
        case 0x3A: return 0x38; // (WWW home)       -> F19
        case 0x40: return 0x40; // (my computer)    -> F20
        case 0x48: return 0x48; // (email)          -> F21
        case 0x2B: return 0x50; // (calculator)     -> F22
        case 0x34: return 0x08; // (play/pause)     -> F13
        case 0x3B: return 0x10; // (stop)           -> F14
        case 0x15: return 0x18; // (previous track) -> F15
        case 0x4D: return 0x20; // (next track)     -> F16
        case 0x50: return 0x28; // (media select)   -> F17
        case 0x5E: return 0x50; // (ACPI wake)      -> F22
        case 0x3F: return 0x57; // (ACPI sleep)     -> F23
        case 0x37: return 0x5F; // (ACPI power)     -> F24

        // https://github.com/tmk/tmk_keyboard/pull/636
        case 0x03: return 0x18; // Help        DEC LK411 -> F15
        case 0x04: return 0x08; // F13         DEC LK411
        case 0x0B: return 0x20; // Do          DEC LK411 -> F16
        case 0x0C: return 0x10; // F14         DEC LK411
        case 0x0D: return 0x19; // LCompose    DEC LK411 -> LGUI
        case 0x79: return 0x6D; // KP-         DEC LK411 -> PCMM
        case 0x83: return 0x28; // F17         DEC LK411
        default: return (code & 0x7F);
    }
}

static int8_t process_cs2(uint8_t code)
{
    // scan code reading states
    static enum {
        INIT,
        F0,
        E0,
        E0_F0,
        // Pause
        E1,
        E1_14,
        E1_F0,
        E1_F0_14,
        E1_F0_14_F0,
    } state = INIT;

    switch (state) {
        case INIT:
            switch (code) {
                case 0xE0:
                    state = E0;
                    break;
                case 0xF0:
                    state = F0;
                    break;
                case 0xE1:
                    state = E1;
                    break;
                case 0x83:  // F7
                    matrix_make(0x02);
                    state = INIT;
                    break;
                case 0x84:  // Alt'd PrintScreen
                    matrix_make(0x7F);
                    state = INIT;
                    break;
                case 0xAA:  // Self-test passed
                case 0xFC:  // Self-test failed
                    // replug or unstable connection probably
                default:    // normal key make
                    state = INIT;
                    if (code < 0x80) {
                        matrix_make(code);
                    } else {
                        matrix_clear();
                        xprintf("!CS2_INIT!\n");
                        return -1;
                    }
            }
            break;
        case E0:    // E0-Prefixed
            switch (code) {
                case 0x12:  // to be ignored
                case 0x59:  // to be ignored
                    state = INIT;
                    break;
                case 0xF0:
                    state = E0_F0;
                    break;
                default:
                    state = INIT;
                    if (code < 0x80) {
                        matrix_make(cs2_e0code(code));
                    } else {
                        matrix_clear();
                        xprintf("!CS2_E0!\n");
                        return -1;
                    }
            }
            break;
        case F0:    // Break code
            switch (code) {
                case 0x83:  // F7
                    matrix_break(0x02);
                    state = INIT;
                    break;
                case 0x84:  // Alt'd PrintScreen
                    matrix_break(0x7F);
                    state = INIT;
                    break;
                default:
                    state = INIT;
                    if (code < 0x80) {
                        matrix_break(code);
                    } else {
                        matrix_clear();
                        xprintf("!CS2_F0!\n");
                        return -1;
                    }
            }
            break;
        case E0_F0: // Break code of E0-prefixed
            switch (code) {
                case 0x12:  // to be ignored
                case 0x59:  // to be ignored
                    state = INIT;
                    break;
                default:
                    state = INIT;
                    if (code < 0x80) {
                        matrix_break(cs2_e0code(code));
                    } else {
                        matrix_clear();
                        xprintf("!CS2_E0_F0!\n");
                        return -1;
                    }
            }
            break;
        // Pause make: E1 14 77
        case E1:
            switch (code) {
                case 0x14:
                    state = E1_14;
                    break;
                case 0xF0:
                    state = E1_F0;
                    break;
                default:
                    state = INIT;
            }
            break;
        case E1_14:
            switch (code) {
                case 0x77:
                    matrix_make(0x00);
                    state = INIT;
                    break;
                default:
                    state = INIT;
            }
            break;
        // Pause break: E1 F0 14 F0 77
        case E1_F0:
            switch (code) {
                case 0x14:
                    state = E1_F0_14;
                    break;
                default:
                    state = INIT;
            }
            break;
        case E1_F0_14:
            switch (code) {
                case 0xF0:
                    state = E1_F0_14_F0;
                    break;
                default:
                    state = INIT;
            }
            break;
        case E1_F0_14_F0:
            switch (code) {
                case 0x77:
                    matrix_break(0x00);
                    state = INIT;
                    break;
                default:
                    state = INIT;
            }
            break;
        default:
            state = INIT;
    }
    return 0;
}

/*
 * Terminal: Scan Code Set 3
 *
 * See [3], [7] and
 * https://github.com/tmk/tmk_keyboard/wiki/IBM-PC-AT-Keyboard-Protocol#scan-code-set-3
 */
static int8_t process_cs3(uint8_t code)
{
    static enum {
        READY,
        F0,
#ifdef G80_2551_SUPPORT
        // G80-2551 four extra keys around cursor keys
        G80,
        G80_F0,
#endif
    } state = READY;

    switch (state) {
        case READY:
            switch (code) {
                case 0xF0:
                    state = F0;
                    break;
                case 0x83:  // PrintScreen
                    matrix_make(0x02);
                    break;
                case 0x84:  // Keypad *
                    matrix_make(0x7F);
                    break;
                case 0x85:  // Muhenkan
                    matrix_make(0x0B);
                    break;
                case 0x86:  // Henkan
                    matrix_make(0x06);
                    break;
                case 0x87:  // Hiragana
                    matrix_make(0x00);
                    break;
                case 0x8B:  // Left GUI
                    matrix_make(0x01);
                    break;
                case 0x8C:  // Right GUI
                    matrix_make(0x09);
                    break;
                case 0x8D:  // Application
                    matrix_make(0x0A);
                    break;
#ifdef G80_2551_SUPPORT
                case 0x80:  // G80-2551 four extra keys around cursor keys
                    state = G80;
                    break;
#endif
                default:    // normal key make
                    if (code < 0x80) {
                        matrix_make(code);
                    } else {
                        xprintf("!CS3_READY!\n");
                        return -1;
                    }
            }
            break;
        case F0:    // Break code
            switch (code) {
                case 0x83:  // PrintScreen
                    matrix_break(0x02);
                    state = READY;
                    break;
                case 0x84:  // Keypad *
                    matrix_break(0x7F);
                    state = READY;
                    break;
                case 0x85:  // Muhenkan
                    matrix_break(0x0B);
                    state = READY;
                    break;
                case 0x86:  // Henkan
                    matrix_break(0x06);
                    state = READY;
                    break;
                case 0x87:  // Hiragana
                    matrix_break(0x00);
                    state = READY;
                    break;
                case 0x8B:  // Left GUI
                    matrix_break(0x01);
                    state = READY;
                    break;
                case 0x8C:  // Right GUI
                    matrix_break(0x09);
                    state = READY;
                    break;
                case 0x8D:  // Application
                    matrix_break(0x0A);
                    state = READY;
                    break;
                default:
                    state = READY;
                    if (code < 0x80) {
                        matrix_break(code);
                    } else {
                        xprintf("!CS3_F0!\n");
                        return -1;
                    }
            }
            break;
#ifdef G80_2551_SUPPORT
        /*
         * G80-2551 terminal keyboard support
         * https://deskthority.net/wiki/Cherry_G80-2551
         * https://github.com/tmk/tmk_keyboard/wiki/IBM-PC-AT-Keyboard-Protocol#g80-2551-in-code-set-3
         */
        case G80:   // G80-2551 four extra keys around cursor keys
            switch (code) {
                case (0x26):    // TD= -> JYEN
                    matrix_make(0x5D);
                    break;
                case (0x25):    // page with edge -> NUHS
                    matrix_make(0x53);
                    break;
                case (0x16):    // two pages -> RO
                    matrix_make(0x51);
                    break;
                case (0x1E):    // calc -> KANA
                    matrix_make(0x00);
                    break;
                case (0xF0):
                    state = G80_F0;
                    return 0;
                default:
                    // Not supported
                    matrix_clear();
                    break;
            }
            state = READY;
            break;
        case G80_F0:
            switch (code) {
                case (0x26):    // TD= -> JYEN
                    matrix_break(0x5D);
                    break;
                case (0x25):    // page with edge -> NUHS
                    matrix_break(0x53);
                    break;
                case (0x16):    // two pages -> RO
                    matrix_break(0x51);
                    break;
                case (0x1E):    // calc -> KANA
                    matrix_break(0x00);
                    break;
                default:
                    // Not supported
                    matrix_clear();
                    break;
            }
            state = READY;
            break;
#endif
    }
    return 0;
}

/*
 * IBM PC Keyboard Protocol Resources:
 *
 * [a] Microsoft USB HID to PS/2 Translation Table - Scan Code Set 1 and 2
 * http://download.microsoft.com/download/1/6/1/161ba512-40e2-4cc9-843a-923143f3456c/translate.pdf
 *
 * [b] Microsoft Keyboard Scan Code Specification - Special rules of Scan Code Set 1 and 2
 * http://download.microsoft.com/download/1/6/1/161ba512-40e2-4cc9-843a-923143f3456c/scancode.doc
 *
 * [1] PS/2 Reference Manuals - Collection of IBM Personal System/2 documents.
 * http://www.mcamafia.de/pdf/pdfref.htm
 *
 * [2] Keyboard and Auxiliary Device Controller - Signal Timing and Format
 * http://www.mcamafia.de/pdf/ibm_hitrc07.pdf
 *
 * [3] Keyboards(101- and 102-key) - Keyboard Layout, Scan Code Set, POR, and Commands.
 * http://www.mcamafia.de/pdf/ibm_hitrc11.pdf
 *
 * [4] IBM PC XT Keyboard Protocol
 * https://github.com/tmk/tmk_keyboard/wiki/IBM-PC-XT-Keyboard-Protocol
 *
 * [5] IBM Keyboard Scan Code by John Elliott - 83-key, 84-key, 102-key and 122-key
 * https://www.seasip.info/VintagePC/index.html
 *
 * [6] IBM 1391406 Keyboard - Scan Code Set 2 of 102-key PS/2 keyboard
 * https://www.seasip.info/VintagePC/ibm_1391406.html
 *
 * [7] The IBM 6110344 Keyboard - Scan Code Set 3 of 122-key terminal keyboard
 * https://www.seasip.info/VintagePC/ibm_6110344.html
 *
 * [8] IBM PC AT Technical Reference 1986
 * http://bitsavers.org/pdf/ibm/pc/at/6183355_PC_AT_Technical_Reference_Mar86.pdf
 *
 * [y] TrackPoint Engineering Specifications for version 3E
 * https://web.archive.org/web/20100526161812/http://wwwcssrv.almaden.ibm.com/trackpoint/download.html
 *
 * [z] [Soarer's XT/AT/PS2/Terminal to USB converter]
 * https://geekhack.org/index.php?topic=17458.0
 *
 */
