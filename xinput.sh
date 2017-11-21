#!/bin/sh

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

printf "$BLOCK_NAME\n"
printf "$BLOCK_NAME\n"

if [ $(state) -eq 1 ]; then
    printf "#00FF00\n"
else
    printf "#FF0000\n"
fi
