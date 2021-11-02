#!/bin/sh

# path:   /home/klassiker/.local/share/repos/zenith-xt-usb/tmk_core.sh
# author: klassiker [mrdotx]
# github: https://github.com/mrdotx/zenith-xt-usb
# date:   2021-11-02T10:53:16+0100

tput reset
rm -rf tmk_core

printf ':: git clone tmk_core and remove .git files/folders\n'
git clone git@github.com:tmk/tmk_core.git
rm -rf tmk_core/.git tmk_core/.gitignore tmk_core/.gitmodules

printf '\n:: git clone submodule lufa and remove .git files/folders\n'
git clone git@github.com:abcminiuser/lufa.git tmk_core/protocol/lufa/lufa-abcminiuser
rm -rf tmk_core/protocol/lufa/lufa-abcminiuser/.git tmk_core/protocol/lufa/lufa-abcminiuser/.gitignore

printf '\n:: git clone submodule usb host shield 2.0 and remove .git files/folders\n'
git clone git@github.com:tmk/USB_Host_Shield_2.0.git tmk_core/protocol/usb_hid/USB_Host_Shield_2.0-tmk
rm -rf tmk_core/protocol/usb_hid/USB_Host_Shield_2.0-tmk/.git tmk_core/protocol/usb_hid/USB_Host_Shield_2.0-tmk/.github tmk_core/protocol/usb_hid/USB_Host_Shield_2.0-tmk/.gitattributes tmk_core/protocol/usb_hid/USB_Host_Shield_2.0-tmk/.gitignore tmk_core/protocol/usb_hid/USB_Host_Shield_2.0-tmk/.gitmodules
