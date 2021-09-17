#!/bin/bash
rm *.o >/dev/null
rm woody >/dev/null
nasm -felf64 woody.s
nasm -felf64 main.s
ld woody.o main.o -o woody
./woody
rm *.o woody >/dev/null
