#!/usr/bin/env bash

if [[ $# -ne 1 ]]; then
    printf 'Penggunaan: bash %s <bilangan_bulat>\n' "${0##*/}" >&2
    exit 2
fi

nilai=$1
if [[ ! $nilai =~ ^-?[0-9]+$ ]]; then
    printf 'Kesalahan: "%s" bukan bilangan bulat.\n' "$nilai" >&2
    exit 2
fi

if [[ $nilai -lt 5 ]]; then
    printf 'Nilai %s kurang dari 5\n' "$nilai"
elif [[ $nilai -lt 10 ]]; then
    printf 'Nilai %s kurang dari 10\n' "$nilai"
else
    printf 'Nilai %s lebih dari atau sama dengan 10\n' "$nilai"
fi
