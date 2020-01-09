#!/bin/sh

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"

[[ -d ${DIR} ]] && . ${DIR}/block.sh

changes="$(git -C "$HOME/$BLOCK_INSTANCE" status -s | wc -l)"

printf "%s\\n" "$changes"
printf "%s\\n" "$changes"

if [ "$changes" -eq "0" ]; then
    printf "%s\\n" "${COLOR_GREEN}"
else
    printf "%s\\n" "${COLOR_RED}"
fi
