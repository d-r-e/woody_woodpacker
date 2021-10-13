#!/bin/bash
FILES=$(find /usr/bin/ -type f)
make
for f in $FILES; do
    echo $f
    ./woody_woodpacker $f
done