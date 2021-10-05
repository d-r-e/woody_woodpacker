#!/usr/bin/env bash
#nasm -fbin $1 -o /proc/self/fd/1 | xxd -p
# nasm -felf64 $1 -o /proc/self/fd/1 | xxd -p | tr -d '\n' |  sed "s/.\{2\}/0x&,/g" ; echo #| sed 's/^/\\x/' ; echo ""
nasm -felf64 ${1:-woody.s}
ofile=$(echo ${1-woody.s} | cut -d. -f1).o

objdump -d $ofile | grep '[0-9a-f]:'|grep -v 'file'|cut -f2 -d:|cut -f1-6 -d' '|tr -s ' '|tr '\t' ' '|sed 's/ $//g'|sed 's/ /\\x/g'|paste -d '' -s |sed 's/^/"/'|sed 's/$/"/g' |tr -d '\"' | sed "s/.\{4\}/\'&\',/g"