#!/bin/sh

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"

[[ -d ${DIR} ]] && . ${DIR}/block.sh

ID=$(xinput | grep $BLOCK_INSTANCE | grep -o 'id=[0-9]*' | grep -o '[0-9]*')

state()
{
    xinput list --long $ID | grep -o disabled > /dev/null 2>&1
    echo $?
}

toggle()
{
    if [ $(state) -eq 1 ]; then
        xinput disable $ID
    else
        xinput enable $ID
    fi
}

case $BLOCK_BUTTON in
    1) toggle ;; # left click
    2) toggle ;; # middle click
    3) toggle ;; # right click
esac

echo "${BLOCK_NAME}"
echo "${BLOCK_NAME}"

if [ $(state) -eq 1 ]; then
    echo "${COLOR_GREEN}"
else
    echo "${COLOR_RED}"
fi
