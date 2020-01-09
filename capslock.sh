#!/bin/bash

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"

[[ -d ${DIR} ]] && . ${DIR}/block.sh

toggle() {
    xdotool key Caps_Lock
}

case $BLOCK_BUTTON in
    1) toggle ;; # left click
    2) toggle ;; # middle click
    3) toggle ;; # right click
esac

echo "CAPS"
echo "CAPS"

xset -q | grep "Caps Lock: *on" > /dev/null 2>&1 && echo "${COLOR_GREEN}" || echo "${COLOR_RED}"
