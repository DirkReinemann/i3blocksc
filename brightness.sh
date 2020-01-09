#!/bin/sh

case $BLOCK_BUTTON in
    1) brightnesscontrol -d ;; # left click, decrease
    3) brightnesscontrol -i ;; # right click, increase
    4) brightnesscontrol -i ;; # scroll up, increase
    5) brightnesscontrol -d ;; # scroll down, decrease
esac

PERCENT=$(brightnesscontrol -s)

echo "$PERCENT"
echo "$PERCENT"
echo "#FFFFFF"
