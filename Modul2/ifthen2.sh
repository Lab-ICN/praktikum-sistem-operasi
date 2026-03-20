#!/bin/bash

nilai=$1

if [[ $nilai -lt 5 ]]; then
    echo "Nilai $nilai kurang dari 5"
elif [[ $nilai -lt 10 ]]; then
    echo "Nilai $nilai kurang dari 10"
else
    echo "Nilai $nilai lebih dari atau sama dengan 10"
fi