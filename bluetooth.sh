#!/bin/bash

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"

[[ -d ${DIR} ]] && . ${DIR}/block.sh

state()
{
    systemctl status bluetooth.service > /dev/null 2>&1
    echo $?
}

toggle()
{
    if [ $(state) -eq 0 ]; then
        sudo systemctl stop bluetooth.service
        killall blueman-applet
    else
        sudo systemctl start bluetooth.service
        nohup blueman-applet > /tmp/blueman-applet.log 2>&1 &
    fi
}

case $BLOCK_BUTTON in
    1) toggle ;; # left click, toggle
    2) toggle ;; # middle click, toggle
    3) toggle ;; # right click, toggle
esac

echo "BLUE"
echo "BLUE"

if [ $(state) -eq 0 ]; then
    echo "${COLOR_GREEN}"
else
    echo "${COLOR_RED}"
fi

