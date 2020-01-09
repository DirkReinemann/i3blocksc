#!/bin/bash

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"

[[ -d ${DIR} ]] && . ${DIR}/block.sh

case $BLOCK_BUTTON in
    3) volumecontrol -m ;; # right click, mute/unmute
    4) volumecontrol -i ;; # scroll up, increase
    5) volumecontrol -d ;; # scroll down, decrease
esac

CUR=$(volumecontrol -s)

VOL=$(echo "$CUR" | awk '{ print $1 }')
MUT=$(echo "$CUR" | awk '{ print $2 }')

if [ "$MUT" == "MUTE" ]; then
    VOL=$MUT
fi

echo "$VOL"
echo "$VOL"

if [ "$VOL" == "MUTE" ]; then
    echo "${COLOR_RED}"
else
    echo "#FFFFFF"
fi
