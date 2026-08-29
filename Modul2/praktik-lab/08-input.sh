#!/usr/bin/env bash

read -r -p 'Nama: ' nama
read -r -p 'NIM: ' nim

printf 'Halo, %s (%s)!\n' "$nama" "$nim"
