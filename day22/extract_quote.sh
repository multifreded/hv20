#!/bin/bash

cat $1 | grep -o 'unaff_EBX.*$' | grep -o '0x..;$' | sed 's/0x\(..\);/\1/g' | xxd -p | sed 's/0a/20/g' | xxd -p -r | xxd -p -r

echo "";
