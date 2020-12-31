#!/bin/bash

wrapped_pp="$1"
pw_list="$2"

no_of_workers=10
list_len="$(cat "$pw_list" | wc -l | xargs)"
block_len="$(echo "$list_len / $no_of_workers" | bc)"

function chk_pw() {
    printf "%s" "$1" | 1>/dev/null 2>&1 ecryptfs-unwrap-passphrase "$wrapped_pp" - 
    if [ $? -eq 0 ]; then
        printf "\nPassword:\n"
        printf "\n$pw\n"
        printf "\nPassphrase:\n"
        passphrase="$(printf "%s" "$pw" | ecryptfs-unwrap-passphrase "$wrapped_pp" -)"
        printf "\n$passphrase\n"
    else
        echo -n "."
    fi
}

function chk_pw_block() {
    for pw in $(head -n $((block_len * $1)) "$pw_list" | tail -n $block_len); do
        chk_pw "$pw"
    done
}

worker=0
while [ $worker -lt $no_of_workers ]; do
    (( worker = worker + 1 ))
    chk_pw_block $worker &
done

wait
exit 0

