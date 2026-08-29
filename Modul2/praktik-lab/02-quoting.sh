#!/usr/bin/env bash

# Double quote tetap melakukan substitusi variabel dan perintah.
hari="$(date +%A)"
tanggal="$(date +%d-%m-%Y)"
mata_kuliah="Sistem Operasi"

printf 'Hari ini adalah hari %s.\n' "$hari"
printf 'Tanggal %s saya belajar "%s".\n' "$tanggal" "$mata_kuliah"

# Single quote menampilkan karakter di dalamnya secara literal.
printf '%s\n' 'Teks ini ditulis secara literal dengan single quote.'
