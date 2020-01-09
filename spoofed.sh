#!/bin/bash

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"

[[ -d ${DIR} ]] && . ${DIR}/block.sh

INTERFACE=${BLOCK_INSTANCE}

CURRENT=$(macchanger $INTERFACE | grep Current | awk '{ print $3 }')
PERMANENT=$(macchanger $INTERFACE | grep Permanent | awk '{ print $3 }')

echo "MAC"
echo "MAC"

[ "$CURRENT" == "$PERMANENT" ] && echo "${COLOR_RED}" || echo "${COLOR_GREEN}"
