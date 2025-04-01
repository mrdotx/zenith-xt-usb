#!/bin/sh

# path:   /home/klassiker/.local/share/repos/zenith-xt-usb/tmk_core.sh
# author: klassiker [mrdotx]
# github: https://github.com/mrdotx/zenith-xt-usb
# date:   2025-04-01T07:15:22+0200

tmk_core_path="$HOME/.local/share/repos/zenith-xt-usb/tmk_core"

# color variables
reset="\033[0m"
bold="\033[1m"
blue="\033[94m"
cyan="\033[96m"

printf '%b%b::%b %bremove folder%b %b%s%b\n' \
        "$bold" "$blue" "$reset" "$bold" "$reset" "$cyan" "$tmk_core_path" "$reset"
rm -rf "$tmk_core_path"

printf '%b%b::%b %bclone tmk_core and remove .git files/folders%b\n' \
        "$bold" "$blue" "$reset" "$bold" "$reset"
git clone \
    git@github.com:tmk/tmk_core.git \
    "$tmk_core_path"
rm -rf \
    "$tmk_core_path/.git" \
    "$tmk_core_path/.gitignore" \
    "$tmk_core_path/.gitmodules"

printf '%b%b::%b %bclone submodule lufa and remove .git files/folders%b\n' \
        "$bold" "$blue" "$reset" "$bold" "$reset"
git clone \
    git@github.com:abcminiuser/lufa.git \
    "$tmk_core_path/protocol/lufa/lufa-abcminiuser"
rm -rf \
    "$tmk_core_path/protocol/lufa/lufa-abcminiuser/.git" \
    "$tmk_core_path/protocol/lufa/lufa-abcminiuser/.gitignore"

printf '%b%b::%b %bclone submodule usb host shield 2.0 and remove .git files/folders%b\n' \
        "$bold" "$blue" "$reset" "$bold" "$reset"
git clone \
    git@github.com:tmk/USB_Host_Shield_2.0.git \
    "$tmk_core_path/protocol/usb_hid/USB_Host_Shield_2.0-tmk"
rm -rf \
    "$tmk_core_path/protocol/usb_hid/USB_Host_Shield_2.0-tmk/.git" \
    "$tmk_core_path/protocol/usb_hid/USB_Host_Shield_2.0-tmk/.github" \
    "$tmk_core_path/protocol/usb_hid/USB_Host_Shield_2.0-tmk/.gitattributes" \
    "$tmk_core_path/protocol/usb_hid/USB_Host_Shield_2.0-tmk/.gitignore" \
    "$tmk_core_path/protocol/usb_hid/USB_Host_Shield_2.0-tmk/.gitmodules"
