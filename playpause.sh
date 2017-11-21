#!/bin/bash

action()
{
    playerctl play-pause
}

case $BLOCK_BUTTON in
    1) action ;; # left click
esac

sleep 1

TXT="PLAY"
COL="#00FF00"

playerctl status | grep Playing > /dev/null 2>&1

if [ $? -eq 1 ]; then
    TXT="STOP"
    COL="#FF0000"
fi

echo "$TXT"
echo "$TXT"
echo "$COL"

