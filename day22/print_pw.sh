#!/bin/bash

start_offset="0x124b"
start=$start_offset
if [ ! -z $1 ]; then
	start="$1"
fi

function get_byte_and_addr_offset() {
	local addr=$1

	res="$(xxd -p -s $addr padawanlock | head -n 1)"
	local byte="${res:26:2}"
	local offset="0x${res:38:2}${res:36:2}${res:34:2}${res:32:2}"
    offset=$(python3 twos_comp.py $offset)
	offset=$(( offset + 20 ))

	printf "%s %s" "$byte" "$offset"
}

function print_res() {
	local byte="$1"
	local char="$(echo "$1" | xxd -p -r)"
	local addr="$2"
	printf "Byte: %s\nChar: %s\nAddr Offset: %x\n" $byte $char $addr
}
	
addr=$start
char=''
while [ ! "$char" == "7d" ]; do
	res=( $(get_byte_and_addr_offset $addr) )
	char="${res[0]}"
	print_res ${res[0]} ${res[1]}
	addr=$(( addr + res[1] ))
done | grep 'Char' | sed 's/Char: \(.\).*/\1/g' | xxd -p | sed 's/0a//g' | xxd -p -r

echo ""
exit 0
