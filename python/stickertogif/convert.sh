#!/bin/bash
# Adapted from https://gist.github.com/Potherca/18423260e2c9a4324c9ecb0c0a284066

INPUT="$1"
DDDD=$(date "+%y-%m-%d...%N")
OUTPUT="$(basename "${INPUT%.*}")"
ffmpeg -i "${INPUT}" \
        -vf "fps=10,split[s0][s1];[s0]palettegen[p];[s1][p]paletteuse" \
        -loop -1 \
        "${OUTPUT}.gif"
gifsicle --lossy=30 --optimize=25 --output "${OUTPUT}.gif" --resize-height 300 "${OUTPUT}.gif"
cp ${OUTPUT}.gif ~/Downloads/sticks/${DDDD}.gif
