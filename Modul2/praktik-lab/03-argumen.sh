#!/usr/bin/env bash

a=10
printf 'Nilai a: %s\n' "$a"
printf 'Jumlah argumen: %s\n' "$#"
printf 'Argumen 1: %s\n' "${1:-<tidak ada>}"
printf 'Argumen 2: %s\n' "${2:-<tidak ada>}"
if [[ $# -eq 0 ]]; then
    printf 'Semua argumen: <tidak ada>\n'
else
    printf 'Semua argumen:'
    printf ' <%s>' "$@"
    printf '\n'
fi
