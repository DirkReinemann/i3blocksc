#!/bin/bash

usage()
{
    echo "i3blocks bash script helper"
    echo
    echo "Usage: $0 [Options]"
    echo
    echo "Options:"
    printf "  %-20s %s\n" "-t" "run all scripts and measure their time"
    exit 1
}

millis() {
    echo $(($(date +%s%N)/1000000))
}

timeall()
{
    T=0

    for FILE in $(ls -1 | grep -E '.*\.(sh|o)'); do
        T1=$(millis)
        RES=$(exec ./$FILE > /dev/null 2>&1)
        EXITCODE=$?
        T2=$(millis)
        TA=$(echo "$T1 $T2" | awk '{ time=($2-$1)/1000; printf "%2.3f", time }')

        if [ $EXITCODE -eq 0 ]; then
            printf "\e[39m%-40s" "$FILE"
        else
            printf "\e[39m%-40s" "$FILE"
        fi

        if [ $(($T2-$T1)) -lt 1000 ]; then
            printf "\e[32m%-20s\n" "$TA"
        else
            printf "\e[31m%-20s\n" "$TA"
        fi

        T=$(echo "$T1 $T2 $T" | awk '{ time=(($2-$1)/1000)+$3; printf "%2.4f", time }')
    done

    printf "\e[39m\n%-40s%-20s\n" "" "$T"
}

if [ $# == 0 ]; then
    usage
fi

while getopts "t" OPT; do
    case $OPT in
    t)
        timeall
        ;;
    \?)
        usage
        ;;
    :)
        usage
        ;;
    esac
done

exit 0
