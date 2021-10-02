#!/bin/bash
# set -e 
FILES=$(find /bin -type f )
FILES+=$(find /usr/bin -type f)
 make
RED="\e[91m "
GREEN="\e[92m "
DEFAULT="\e[39m "
TOTAL=0
VALID=0
WIDHT=50

function print_green()
{
    echo -en $GREEN
    echo -en " $1"
    echo -e $DEFAULT
}

function print_red()
{
    echo -en $RED
    echo -en $1
    echo -e $DEFAULT
}

for f in $FILES; do
    file $f | grep "x86-64" &>/dev/null
    if [ "$?" == "0" ]; then
        ./woody_woodpacker $f | grep "cave available" &>/dev/null
        if [ "$?" == "0" ]; then
            printf "%-40s" "$f"
            print_green "OK"
            VALID=$(($VALID + 1))
            TOTAL=$(($TOTAL + 1))
        else
            print_red "$f"
            TOTAL=$(($TOTAL + 1))
        fi 
    else
        printf "%-40s" "$f"
        echo -e " NC"
    fi
done
echo VALID: $VALID/$TOTAL

