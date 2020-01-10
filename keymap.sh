#!/bin/sh

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"

[[ -d ${DIR} ]] && . ${DIR}/block.sh

KEYMAP="$(setxkbmap -query | grep layout | awk -F':' '{ gsub(/^[ \t]*/, "", $2); print $2 }')"

GERMAN="de"
ENGLISH="us"

toggle()
{
    if [ "$KEYMAP" = "$GERMAN" ]; then
        setxkbmap $ENGLISH
    elif [ "$KEYMAP" = "$ENGLISH" ]; then
        setxkbmap $GERMAN
    fi
}

case $BLOCK_BUTTON in
    1) toggle ;; # left click
    2) toggle ;; # middle click
    3) toggle ;; # right click
esac

KEYMAP=$(setxkbmap -query | grep layout | awk -F':' '{ gsub(/^[ \t]*/, "", $2); print $2 }')

LAYOUT="??"

if [ "$KEYMAP" = "$GERMAN" ]; then
    LAYOUT="DE"
elif [ "$KEYMAP" = "$ENGLISH" ]; then
    LAYOUT="US"
fi

echo "$LAYOUT"
echo "$LAYOUT"
echo "${COLOR_WHITE}"
