#!/bin/sh

changes="$(git -C "$HOME/$BLOCK_INSTANCE" status -s | wc -l)"

printf "%s\\n" "$changes"
printf "%s\\n" "$changes"

if [ "$changes" -eq "0" ]; then
    printf "%s\\n" "#00FF00"
else
    printf "%s\\n" "#FF0000"
fi
