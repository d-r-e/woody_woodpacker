set -xe

if [ "$1" ]; then
    FILE=${1}
else
    FILE=woody_woodpacker
fi
make
OFFSET=`./woody_woodpacker $FILE | grep "from offset" | cut -d: -f2`
echo $OFFSET
OFFSET=$(($OFFSET - 32))
binwalk -W woody ${FILE} -o $OFFSET| less