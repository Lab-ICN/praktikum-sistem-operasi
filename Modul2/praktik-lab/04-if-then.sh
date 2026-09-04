#!/usr/bin/env bash

nilai=10
if [[ $nilai -lt 15 ]]; then
    printf 'Nilai %s kurang dari 15\n' "$nilai"
fi

# membandingkan dua string
shell_digunakan='bash'
shell_praktikum='bash'
shell_lain='zsh'

if [[ "$shell_digunakan" = "$shell_praktikum" ]]; then
    printf 'shell yang digunakan sesuai dengan praktikum\n'
fi

if [[ "$shell_digunakan" != "$shell_lain" ]]; then
    printf 'bash dan zsh adalah nama shell yang berbeda\n'
fi

# memeriksa jumlah argumen dengan -eq
jumlah_argumen=$#
if [[ $jumlah_argumen -eq 0 ]]; then
    path_diperiksa="$0"
else
    path_diperiksa="$1"
fi

# memeriksa nilai dengan -gt, -ge, dan -le
nilai_praktikum=80
batas_lulus=75
nilai_maksimum=100

if [[ $nilai_praktikum -gt $batas_lulus ]]; then
    printf 'nilai praktikum lebih tinggi dari batas kelulusan\n'
fi

if [[ $nilai_praktikum -ge $batas_lulus && $nilai_praktikum -le $nilai_maksimum ]]; then
    printf 'nilai praktikum berada dalam rentang kelulusan\n'
fi

# memeriksa string kosong dan tidak kosong
nama_praktikan="${2:-}"
if [[ -z "$nama_praktikan" ]]; then
    printf 'nama praktikan belum diberikan\n'
elif [[ -n "$nama_praktikan" ]]; then
    printf 'nama praktikan: %s\n' "$nama_praktikan"
fi

# memeriksa jenis path yang diberikan praktikan
if [[ -e "$path_diperiksa" || -h "$path_diperiksa" ]]; then
    printf 'path tersedia: %s\n' "$path_diperiksa"

    if [[ -h "$path_diperiksa" ]]; then
        printf 'path %s adalah symbolic link\n' "$path_diperiksa"
    elif [[ -d "$path_diperiksa" ]]; then
        printf 'path %s adalah directory\n' "$path_diperiksa"
    elif [[ -f "$path_diperiksa" ]]; then
        printf 'path %s adalah file biasa\n' "$path_diperiksa"
    fi

    if [[ -r "$path_diperiksa" ]]; then
        printf 'path tersebut dapat dibaca\n'
    fi

    if [[ -w "$path_diperiksa" ]]; then
        printf 'path tersebut dapat ditulis\n'
    fi

    if [[ -x "$path_diperiksa" ]]; then
        printf 'path tersebut dapat dieksekusi atau ditelusuri\n'
    fi
else
    printf 'path tidak ditemukan: %s\n' "$path_diperiksa"
fi
