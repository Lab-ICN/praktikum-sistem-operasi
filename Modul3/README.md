# Modul 3 - Process dan Thread

Folder ini berisi versi lengkap kode pada Modul 3. Gunakan berkas dengan
akhiran `_NIM.c` sebagai acuan utama, kemudian ganti `NIM` pada nama berkas
dengan NIM masing-masing sebelum pengumpulan.

## Daftar program

| Berkas | Bagian modul | Tujuan |
| --- | --- | --- |
| `Loop_NIM.c` | Process, langkah g-m | Membuat proses tanpa akhir untuk diamati dengan `ps`, `pstree`, dan `top`. |
| `fork_NIM.c` | Process, langkah n-t | Membuat child process dengan `fork()` serta menampilkan PID parent dan child. |
| `threadsatu_NIM.c` | Thread, langkah a-d | Menjalankan dua thread pencetak pesan secara bersamaan. |
| `threaddua_NIM.c` | Thread, langkah e-k | Membuat dua worker thread dan mengenali keduanya melalui thread ID. |
| `singlethread_NIM.c` | Thread, langkah l-n | Menjalankan simulasi transaksi rekening secara sekuensial. |
| `threadtiga_NIM.c` | Thread, langkah o-p | Menjalankan simulasi yang sama dengan beberapa thread untuk mempelajari race condition dan mutex. |

## Kompilasi

Kompilasi program yang ingin digunakan melalui terminal:

```bash
gcc Loop_NIM.c -o Loop_NIM
gcc fork_NIM.c -o fork_NIM
gcc threadsatu_NIM.c -pthread -o threadsatu_NIM
gcc threaddua_NIM.c -pthread -o threaddua_NIM
gcc singlethread_NIM.c -o singlethread_NIM
gcc threadtiga_NIM.c -pthread -o threadtiga_NIM
```

## Cara menjalankan dan mengamati

### 1. Infinite loop

```bash
./Loop_NIM
```

Program akan terus berjalan. Dari terminal kedua, cari dan amati prosesnya:

```bash
ps -ax
pstree
top
kill -9 <PID>
```

### 2. Parent dan child process

```bash
./fork_NIM
```

Keluaran parent dan child dapat muncul dalam urutan berbeda karena keduanya
dijadwalkan oleh sistem operasi.

### 3. Dua thread pencetak pesan

```bash
./threadsatu_NIM
```

Program ini berjalan tanpa akhir. Hentikan dengan `Ctrl+C`. Susunan pesan
`Hello!!` dan `How are you?` dapat berubah pada setiap eksekusi.

### 4. Dua worker thread

```bash
./threaddua_NIM
```

Program membuat dua thread yang menjalankan beban kerja CPU. Seperti pada kode
modul, fungsi `main()` menunggu selama lima detik menggunakan `sleep(5)` lalu
selesai. Perhatikan bahwa proses ikut berhenti jika worker belum selesai.

### 5. Simulasi single-thread

```bash
./singlethread_NIM
./singlethread_NIM -a 1024 -i 10000 -t 50
```

Karena seluruh transfer dijalankan berurutan, jumlah total saldo tetap
konsisten.

### 6. Simulasi multithread

Mode tanpa mutex untuk mengamati kemungkinan race condition:

```bash
./threadtiga_NIM -a 64 -i 100000 -t 50 -n 8 --unsafe
```

Mode dengan mutex untuk melindungi data bersama:

```bash
./threadtiga_NIM -a 64 -i 100000 -t 50 -n 8 --safe
```

`-a` menentukan jumlah rekening, `-i` jumlah transaksi per thread, `-t`
besar simulasi waktu pemrosesan, dan `-n` jumlah thread. Mode bawaan adalah
`--unsafe` agar masalah sinkronisasi dapat diamati terlebih dahulu.
