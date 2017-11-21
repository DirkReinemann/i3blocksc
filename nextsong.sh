#!/bin/bash

action()
{
    playerctl next
}

case $BLOCK_BUTTON in
    1) action ;; # left click
    2) action ;; # middle click
    2) action ;; # right click
esac

echo "NEXT"
echo "NEXT"
echo ""

