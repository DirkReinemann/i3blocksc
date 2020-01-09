#!/bin/bash

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"

[[ -d ${DIR} ]] && . ${DIR}/block.sh

IP="$(curl -s http://ipecho.net/plain || echo '0.0.0.0')"
LOCATION=""
COLOR="${COLOR_RED}"

if [ "$IP" != "0.0.0.0" ]; then
    LOCATION="$(geoiplookup "$IP" | awk -F': ' '{ print $2 }')"
    COLOR="${COLOR_GREEN}"
fi

echo "$IP $LOCATION"
echo "$IP $LOCATION"
echo "$COLOR"

exit 0
