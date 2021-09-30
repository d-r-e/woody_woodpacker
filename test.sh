#!/bin/bash
# set -e 
FILES=$(find /bin -type f )
FILES+=$(find /usr/bin -type f)
 make
TOTAL=0
VALID=0
for f in $FILES; do
    file $f | grep "x86-64" &>/dev/null
    if [ "$?" == "0" ]; then
        ./woody_woodpacker $f | grep cave &>/dev/null
        if [ "$?" == "0" ]; then
            echo -en "\e[92m OK\e[39m: "
            echo "$f"
            VALID=$(($VALID + 1))
            TOTAL=$(($TOTAL + 1))
        else
            echo -en "\e[91m KO\e[39m: "
            echo "$f"
            TOTAL=$(($TOTAL + 1))
        fi 
    else
        echo "not compatible"
    fi
done
echo VALID: $VALID/$TOTAL

