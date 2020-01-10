#!/bin/sh

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"

[[ -d ${DIR} ]] && . ${DIR}/block.sh

case $BLOCK_BUTTON in
    1) brightnesscontrol -d ;; # left click, decrease
    3) brightnesscontrol -i ;; # right click, increase
    4) brightnesscontrol -i ;; # scroll up, increase
    5) brightnesscontrol -d ;; # scroll down, decrease
esac

PERCENT=$(brightnesscontrol -s)

echo "$PERCENT"
echo "$PERCENT"
echo "${COLOR_WHITE}"
