#!/bin/bash
INPUT="$1"
DDDD=$(date "+%y-%m-%d...%N")
OUTPUT="$(basename "${INPUT%.*}")"
mogrify -format gif $INPUT
gifsicle --lossy=30 --optimize=25 --output "${INPUT}.gif" --resize-height 300 "${OUTPUT}.gif"
cp ${OUTPUT}.gif ~/Downloads/sticks/${DDDD}.gif
