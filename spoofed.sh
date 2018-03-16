#!/bin/bash

INTERFACE=${BLOCK_INSTANCE}

CURRENT=$(macchanger $INTERFACE | grep Current | awk '{ print $3 }')
PERMANENT=$(macchanger $INTERFACE | grep Permanent | awk '{ print $3 }')

echo "MAC"
echo "MAC"

[ "$CURRENT" == "$PERMANENT" ] && echo "#FF0000" || echo "#00FF00"
