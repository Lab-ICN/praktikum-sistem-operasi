#!/usr/bin/env bash

# Jangan memakai `for data in $(ls)` karena nama yang mengandung spasi
# akan terpecah menjadi beberapa bagian.
ditemukan=false
for path in ./*; do
    [[ -e $path ]] || continue
    ditemukan=true
    printf 'Entri adalah %s\n' "${path#./}"
done

if [[ $ditemukan == false ]]; then
    printf 'Direktori ini kosong.\n'
fi
