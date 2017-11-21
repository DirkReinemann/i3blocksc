#!/bin/bash

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
echo ""

