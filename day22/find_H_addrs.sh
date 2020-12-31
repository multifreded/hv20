#!/bin/bash

grep 'c60348' padawanlock.as | grep -o '^0x........' > candidate_addrs.txt
