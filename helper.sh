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
    t=0
    shopt -s nullglob
    for file in *[sh,o]; do
        t1=$(millis)
        ./"$file" > /dev/null 2>&1
        exitcode=$?
        t2=$(millis)
        ta=$(echo "$t1 $t2" | awk '{ time=($2-$1)/1000; printf "%2.3f", time }')

        if [ $exitcode -eq 0 ]; then
            printf "\e[39m%-40s" "$file"
        else
            printf "\e[39m%-40s" "$file"
        fi

        if [ $((t2-t1)) -lt 1000 ]; then
            printf "\e[32m%-20s\n" "$ta"
        else
            printf "\e[31m%-20s\n" "$ta"
        fi

        t=$(echo "$t1 $t2 $t" | awk '{ time=(($2-$1)/1000)+$3; printf "%2.4f", time }')
    done

    printf "\e[39m\n%-40s%-20s\n" "" "$t"
}

if [ $# == 0 ]; then
    usage
fi

while getopts "t" opt; do
    case $opt in
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
