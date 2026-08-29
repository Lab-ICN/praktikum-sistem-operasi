#!/usr/bin/env bash

nilai=10
if [[ $nilai -lt 15 ]]; then
    printf 'Nilai %s kurang dari 15\n' "$nilai"
fi
