#!/bin/bash

for crc in $(unzip -v Package2.zip | grep -Eo ' [0-9a-f]{8} '); do
    if unzip -v Package1.zip | grep -q $crc; then
        echo "Package1.zip:"
	unzip -v Package1.zip | grep $crc
	echo "Package2.zip:"
	unzip -v Package2.zip | grep $crc
    fi
done
