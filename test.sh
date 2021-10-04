#!/bin/bash
set -epu
rm -f woody
gcc src/*.c -Wall -Wextra -Werror -o woody_woodpacker
./woody_woodpacker $1
echo
file woody
echo
# ./woody