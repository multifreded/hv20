#!/bin/bash 

if [ -z "$1" ]; then >&2 echo "Missing text string."; exit 1; fi

# Iterates through list of encodings of iconv(1)
for enc in $(iconv -l); do 
	echo "Encoding: $enc"

	echo -n "$1" \
	| iconv -t "$enc" 2>/dev/null || echo -n "ERROR"

	read -r                   # Waits for key press
done
