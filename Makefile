# path:   /home/klassiker/.local/share/repos/zenith-xt-usb/Makefile
# author: klassiker [mrdotx]
# github: https://github.com/mrdotx/zenith-usb
# date:   2021-02-27T18:38:52+0100

# Target file name (without extension).
TARGET = zenith_usb

# Directory common source filess exist
TMK_DIR = tmk_core

# Directory keyboard dependent files exist
TARGET_DIR = .

# project specific files
SRC = protocol/ibmpc.c \
      zenith_usb.c

CONFIG_H = config.h

# MCU name
# MCU = at90usb1286
# MCU = atmega32u2
MCU = atmega32u4

# Processor frequency.
#     This will define a symbol, F_CPU, in all source code files equal to the
#     processor frequency in Hz. You can then use this symbol in your source code to
#     calculate timings. Do NOT tack on a 'UL' at the end, this will be done
#     automatically to create a 32-bit value in your source code.
#
#     This will be an integer division of F_USB below, as it is sourced by
#     F_USB after it has run through any CPU prescalers. Note that this value
#     does not *change* the processor frequency - it should merely be updated to
#     reflect the processor speed set externally so that the code can use accurate
#     software delays.
F_CPU = 16000000

#
# LUFA specific
#
# Target architecture (see library "Board Types" documentation).
ARCH = AVR8

# Input clock frequency.
#     This will define a symbol, F_USB, in all source code files equal to the
#     input clock frequency (before any prescaling is performed) in Hz. This value may
#     differ from F_CPU if prescaling is used on the latter, and is required as the
#     raw input clock is fed directly to the PLL sections of the AVR for high speed
#     clock generation for the USB and other AVR subsections. Do NOT tack on a 'UL'
#     at the end, this will be done automatically to create a 32-bit value in your
#     source code.
#
#     If no clock division is performed on the input clock inside the AVR (via the
#     CPU clock adjust registers or the clock division fuses), this will be equal to F_CPU.
F_USB = $(F_CPU)

# This improves response of keyboard when wakeup
OPT_DEFS += -DSUSPEND_MODE_STANDBY

# Boot Section Size in *bytes*
#   Teensy halfKay   512
#   Teensy++ halfKay 1024
#   Atmel DFU loader 4096
#   LUFA bootloader  4096
#   USBaspLoader     2048
# Bootloader size can be calculated from fuse bits
#BOOTLOADER_SIZE ?= 4096
#OPT_DEFS += -DBOOTLOADER_SIZE=$(BOOTLOADER_SIZE)

# Build Options
#   comment out to disable the options.
#
# BOOTMAGIC_ENABLE ?= yes # Virtual DIP switch configuration(+1000)
MOUSEKEY_ENABLE = yes  # Mouse keys(+4700)
EXTRAKEY_ENABLE = yes  # Audio control and System control(+450)
CONSOLE_ENABLE = yes   # Console for debug(+400)
COMMAND_ENABLE = yes   # Commands for debug and configuration
NKRO_ENABLE = yes      # USB Nkey Rollover

KEYMAP_SECTION_ENABLE = yes
UNIMAP_ENABLE = yes

# Optimize size but this may cause error "relocation truncated to fit"
#EXTRALDFLAGS = -Wl,--relax

#
# Keymap file
#
ifdef UNIMAP_ENABLE
    KEYMAP_FILE = unimap
else
    ifdef ACTIONMAP_ENABLE
	KEYMAP_FILE = actionmap
    else
	KEYMAP_FILE = keymap
    endif
endif
ifdef KEYMAP
    SRC := $(KEYMAP_FILE)_$(KEYMAP).c $(SRC)
else
    SRC := $(KEYMAP_FILE)_plain.c $(SRC)
endif

# Search Path
VPATH += $(TARGET_DIR)
VPATH += $(TMK_DIR)

include $(TMK_DIR)/protocol.mk
include $(TMK_DIR)/protocol/lufa.mk
include $(TMK_DIR)/common.mk
include $(TMK_DIR)/rules.mk
