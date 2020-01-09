#!/bin/bash

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"

[[ -d ${DIR} ]] && . ${DIR}/block.sh

SSID="$(iwgetid | awk '{ print $2 }' | awk -F':' '{ print $2 }' | tail -c +2 | head -c -2)"
COLOR="${COLOR_GREEN}"

if [ -z "$SSID" ]; then
    SSID="down"
    COLOR="${COLOR_RED}"
fi

echo "$SSID"
echo "$SSID"
echo "$COLOR"
