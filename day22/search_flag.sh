#!/bin/bash

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


for line in $(cat candidate_addrs.txt); do
	addr=$(printf '0x%x' $(( line - 0x100b )))
	addr="0x89c707"

	init=$addr
	echo -n "."
	res=( $(get_byte_and_addr_offset $addr) )
	addr=$(( addr + res[1] ))
	res=( $(get_byte_and_addr_offset $addr) )
	if [ "${res[0]}" == "56" ]; then
		addr=$(( addr + res[1] ))
        	res=( $(get_byte_and_addr_offset $addr) )
		if [ "${res[0]}" == "32" ]; then
			addr=$(( addr + res[1] ))
                	res=( $(get_byte_and_addr_offset $addr) )
			if [ "${res[0]}" == "30" ]; then 
                        	addr=$(( addr + res[1] ))
                        	res=( $(get_byte_and_addr_offset $addr) )
				echo ""
				echo "Flag start address: $init"
				echo "PIN: $(( (init - 0x124b) / 20 ))"
				echo -n "Flag: "
				./print_pw.sh $init
				exit 0
			fi
		fi
	fi
done

echo "Failed to find HV20"
exit 1
