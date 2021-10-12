#!/bin/bash
set -x
for n in {0..8000}; do
    echo $n
    rm -f woody
    gcc -Wall -Wextra -Werror -fsanitize=address -D BASEIMAGE=$n src/*.c  -o woody_woodpacker
    ./woody_woodpacker woody_woodpacker
    ./woody | grep -v AddressSanitizer
    if [ $? != 0 ]; then
        break
    fi
done