#!/bin/sh

case $BLOCK_BUTTON in
    1) amixer sset Capture toggle > /dev/null 2>&1 ;; # left click
    2) amixer sset Capture toggle > /dev/null 2>&1 ;; # middle click
    3) amixer sset Capture toggle > /dev/null 2>&1 ;; # right click
esac

amixer get Capture | grep "^[ ]*Front Left" | grep "\[off\]" > /dev/null 2>&1
MIC=$?

echo "MIC"
echo "MIC"

if [ $MIC -eq 1 ]; then
    echo "#00FF00"
else
    echo "#FF0000"
fi
