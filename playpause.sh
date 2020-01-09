#!/bin/bash

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"

[[ -d ${DIR} ]] && . ${DIR}/block.sh

action()
{
    playerctl play-pause
}

case $BLOCK_BUTTON in
    1) action ;; # left click
esac

sleep 1

TXT="PLAY"
COL="${COLOR_GREEN}"

playerctl status 2>/dev/null | grep Playing > /dev/null 2>&1

if [ $? -eq 1 ]; then
    TXT="STOP"
    COL="${COLOR_RED}"
fi

echo "$TXT"
echo "$TXT"
echo "$COL"
