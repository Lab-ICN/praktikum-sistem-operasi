#!/usr/bin/env bash

a=1
while [[ $a -le 5 ]]; do
    printf 'Nilai a: %s\n' "$a"
    ((a += 1))
done
