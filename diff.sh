if [ "$1" ]; then
    FILE=${1}
else
    FILE=woody_woodpacker
fi


set -xepu
make
OFFSET=`./woody_woodpacker $FILE | grep "from offset" | cut -d: -f2`
echo $OFFSET
OFFSET=$(($OFFSET - 64))
binwalk -W woody ${FILE} -o ${OFFSET} | less