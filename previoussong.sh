#!/bin/bash

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"

[[ -d ${DIR} ]] && . ${DIR}/block.sh

action()
{
    playerctl previous
}

case $BLOCK_BUTTON in
    1) action ;; # left click
    2) action ;; # middle click
    3) action ;; # right click
esac

echo "PREV"
echo "PREV"
echo "${COLOR_WHITE}"
