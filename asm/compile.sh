#!/bin/bash
# rm *.o 2>/dev/null
# rm woody 2>/dev/null
# nasm -felf64 woody.s
# nasm -felf64 main.s
# ld woody.o main.o -o woody
# ./woody
# rm *.o woody >/dev/null


nasm -felf64 woody.s   
ld -melf_x86_64 woody.o
objdump -D woody.o