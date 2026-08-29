# Modul 2 - Shell Scripting

Modul ini membantu mahasiswa mempelajari dasar shell scripting menggunakan
GNU Bash pada sistem GNU/Linux. Contoh di folder `praktik-lab` dapat langsung
dijalankan untuk mempelajari setiap konsep secara bertahap.

## Tujuan Pembelajaran

Setelah menyelesaikan modul ini, mahasiswa diharapkan mampu:

1. membuat dan menjalankan skrip Bash pada VPS;
2. menggunakan quoting, variabel, dan argumen;
3. menggunakan percabangan dan perulangan;
4. membaca input dari pengguna;
5. menghubungkan program melalui standard input, standard output, dan pipe;
6. menjelaskan cara kerja serta keluaran skrip yang dibuat.

## Struktur Folder

```text
Modul2/
|-- README.md
`-- praktik-lab/
|   |-- 01-header.sh
|   |-- 02-quoting.sh
|   |-- 03-argumen.sh
|   |-- 04-if-then.sh
|   |-- 05-if-elif-else.sh
|   |-- 06-for-loop.sh
|   |-- 07-while-loop.sh
|   `-- 08-input.sh
```

## Prasyarat

Siapkan:

- akun dan alamat IP VPS dari asisten praktikum;
- koneksi SSH sebagaimana dijelaskan pada Modul 1;
- eduVPN jika VPS diakses dari luar jaringan Universitas Brawijaya;
- Bash dan editor teks seperti `nano`, `vim`, atau `vi` pada VPS;
- Git jika ingin mengambil materi langsung dari GitHub.

Jangan menuliskan kata sandi pada skrip, README, commit, atau tangkapan layar.

## Langkah 1 - Masuk ke VPS

Hubungkan perangkat ke jaringan kampus atau eduVPN, kemudian buka Terminal
atau Command Prompt dan jalankan:

```bash
ssh userNIM@IP_VPS
```

Ganti `userNIM` dan `IP_VPS` dengan akun serta alamat yang diberikan asisten.
Keberhasilan login ditandai dengan berubahnya prompt terminal menjadi prompt
mesin VPS.

Untuk memeriksa identitas sesi, jalankan:

```bash
whoami
hostname
date
```

## Langkah 2 - Memastikan Bash Tersedia

Jalankan:

```bash
bash --version
echo "$SHELL"
ps -p $$ -o comm=
```

- `bash --version` menampilkan versi Bash.
- `echo "$SHELL"` menampilkan login shell pengguna.
- `ps -p $$ -o comm=` menampilkan shell yang menjalankan sesi saat ini.

Masuk ke Bash jika sesi saat ini memakai shell lain:

```bash
bash
```

## Langkah 3 - Mengambil Materi dari GitHub

Untuk pengambilan pertama:

```bash
git clone https://github.com/Lab-ICN/praktikum-sistem-operasi.git
cd praktikum-sistem-operasi/Modul2
```

Jika repositori sudah pernah diunduh:

```bash
cd praktikum-sistem-operasi
git pull --ff-only
cd Modul2
```

Periksa lokasi saat ini:

```bash
pwd
ls
```

## Langkah 4 - Menjalankan Praktik Lab

Masuk ke folder contoh:

```bash
cd praktik-lab
```

Jalankan contoh secara berurutan:

| Urutan | Berkas | Konsep | Perintah |
|---|---|---|---|
| 1 | `01-header.sh` | shebang dan versi Bash | `bash 01-header.sh` |
| 2 | `02-quoting.sh` | single quote, double quote, substitusi | `bash 02-quoting.sh` |
| 3 | `03-argumen.sh` | variabel dan argumen | `bash 03-argumen.sh satu dua` |
| 4 | `04-if-then.sh` | percabangan sederhana | `bash 04-if-then.sh` |
| 5 | `05-if-elif-else.sh` | beberapa kondisi | `bash 05-if-elif-else.sh 7` |
| 6 | `06-for-loop.sh` | perulangan berkas | `bash 06-for-loop.sh` |
| 7 | `07-while-loop.sh` | perulangan berdasarkan kondisi | `bash 07-while-loop.sh` |
| 8 | `08-input.sh` | input interaktif | `bash 08-input.sh` |

Jangan hanya menyalin keluaran. Buka setiap skrip dan cocokkan tiap bagian
kode dengan hasilnya:

```bash
nano 03-argumen.sh
```

Keluar dari `nano` dengan `Ctrl+X`. Pilih `N` jika tidak ingin menyimpan
perubahan pada contoh.

## Langkah 5 - Menjalankan Skrip Secara Langsung

Perintah `bash nama-skrip.sh` tidak memerlukan hak eksekusi. Untuk menjalankan
skrip melalui `./nama-skrip.sh`, berikan hak eksekusi terlebih dahulu:

```bash
chmod +x 01-header.sh
./01-header.sh
```

Baris pertama berikut menentukan interpreter ketika skrip dijalankan secara
langsung:

```bash
#!/usr/bin/env bash
```

## Penjelasan Konsep

### Quoting

- `'teks'` mempertahankan isi sebagai teks literal.
- `"teks $variabel"` tetap melakukan substitusi variabel.
- `$(perintah)` mengganti ekspresi dengan keluaran perintah.
- Selalu tulis `"$variabel"` ketika nilainya dapat mengandung spasi.

### Variabel dan Argumen

```bash
nama="Budi Santoso"
printf 'Nama: %s\n' "$nama"
```

Parameter penting:

- `$#`: jumlah argumen;
- `$1`, `$2`: argumen pertama dan kedua;
- `"$@"`: seluruh argumen tanpa merusak batas setiap argumen;
- `${10}`: argumen ke-10 dan seterusnya.

### Percabangan

```bash
if [[ kondisi ]]; then
    # dijalankan jika kondisi benar
elif [[ kondisi_lain ]]; then
    # dijalankan jika kondisi lain benar
else
    # dijalankan jika semua kondisi salah
fi
```

Operator angka yang sering digunakan: `-eq`, `-ne`, `-lt`, `-le`, `-gt`,
dan `-ge`. Operator berkas yang digunakan dalam tugas: `-f`, `-r`, `-w`,
dan `-x`.

### Perulangan

`for` sesuai untuk mengolah sekumpulan nilai. `while` sesuai untuk mengulang
selama suatu kondisi masih benar. Saat memproses nama berkas, jangan gunakan
`for file in $(ls)` karena nama yang mengandung spasi akan terpecah.

### Input, Output, dan Pipe

- Standard input adalah data yang diterima program.
- Standard output adalah keluaran normal program.
- `|` meneruskan standard output program pertama ke standard input program
  kedua.

Contoh:

```bash
printf '6\n' | bash skrip-penerima-input.sh
```

## Masalah yang Sering Terjadi

### `Permission denied`

Jalankan dengan Bash atau berikan hak eksekusi:

```bash
bash nama-skrip.sh
chmod +x nama-skrip.sh
```

### `bad interpreter: No such file or directory`

Berkas mungkin memakai akhir baris Windows. Perbaiki dengan:

```bash
sed -i 's/\r$//' nama-skrip.sh
```

### Nama berkas dengan spasi terpecah

Gunakan double quote pada variabel:

```bash
printf '%s\n' "$file"
```

## Referensi

- [GNU Bash Reference Manual](https://www.gnu.org/software/bash/manual/)
- [GNU Coreutils Manual](https://www.gnu.org/software/coreutils/manual/)
- [Shell Command Language - The Open Group](https://pubs.opengroup.org/onlinepubs/9799919799/utilities/V3_chap02.html)
