#!/usr/bin/env bash

# Double quote tetap melakukan substitusi variabel dan perintah.
hari="$(date +%A)"
tanggal="$(date +%d-%m-%Y)"
mata_kuliah="Sistem Operasi"

printf 'Hari ini adalah hari %s.\n' "$hari"
printf 'Tanggal %s saya belajar "%s".\n' "$tanggal" "$mata_kuliah"

# Single quote menampilkan karakter di dalamnya secara literal.
printf '%s\n' 'Teks ini ditulis secara literal dengan single quote.'

# pemisah perintah dengan ;
printf 'membuka materi praktikum\n'; printf 'membaca materi praktikum\n'

# eksekusi background dengan &
(sleep 1; printf 'pencadangan laporan selesai\n') &
printf 'proses utama tetap berjalan\n'
wait

# pengelompokan perintah dengan ()
direktori_awal="$PWD"
(
    cd /tmp || exit 1
    printf 'direktori di dalam subshell: %s\n' "$PWD"
)
printf 'direktori shell utama tetap: %s\n' "$direktori_awal"

# pipeline dengan |
jumlah_lulus="$(printf 'lulus\nremedial\nlulus\n' | grep -c '^lulus$')"
printf 'hasil pipeline: %s\n' "$jumlah_lulus"

# menyimpan keluaran baru dengan >
file_hasil='hasil-quoting.txt'
printf 'baris pertama\n' > "$file_hasil"

# menambahkan keluaran dengan >>
printf 'baris kedua\n' >> "$file_hasil"

# membaca file sebagai input dengan <
jumlah_baris="$(wc -l < "$file_hasil")"
printf 'jumlah baris pada file: %s\n' "$jumlah_baris"

# memberikan input beberapa baris dengan <<
cat <<EOF
catatan praktikum
mata kuliah: $mata_kuliah
hasil penjumlahan: $((5 + 3))
EOF

# backtick juga melakukan substitusi perintah, tetapi bentuk $() lebih mudah dibaca
tahun_lama=`date +%Y`
printf 'tahun dari backtick: %s\n' "$tahun_lama"

# escape character menampilkan karakter khusus sebagai teks
printf '%s\n' "harga modul adalah \$10"

# single quote menampilkan metakarakter sebagai teks biasa
printf '%s\n' 'karakter ; & () | > >> < << tidak dijalankan sebagai perintah'
