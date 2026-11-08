#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/proc_fs.h>
#include <linux/uaccess.h>
#include <linux/errno.h>
#include <linux/minmax.h>

#define PROC_FILENAME "praktikum_io"

/* Pesan yang diberikan ketika file virtual dibaca */
static const char msg_buffer[] =
    "Halo! Ini adalah output dari kernel module.\n";

static const size_t msg_len = sizeof(msg_buffer) - 1;

/*
 * Menangani operasi pembacaan file /proc/praktikum_io
 */
static ssize_t proc_read(struct file *file,
                         char __user *usr_buf,
                         size_t count,
                         loff_t *pos)
{
    size_t bytes;

    /* Pastikan posisi baca valid */
    if (*pos < 0)
        return -EINVAL;

    /* Tidak ada data yang diminta */
    if (count == 0)
        return 0;

    /* Akhir file (EOF) */
    if (*pos >= (loff_t)msg_len)
        return 0;

    /*
     * Batasi data berdasarkan:
     * 1. Jumlah byte yang diminta (count)
     * 2. Sisa data yang belum dibaca
     */
    bytes = min_t(size_t, count,
                  msg_len - (size_t)*pos);

    /* Salin data dari kernel space ke user space */
    if (copy_to_user(usr_buf,
                     msg_buffer + (size_t)*pos,
                     bytes)) {
        pr_err("Gagal menyalin data ke user.\n");
        return -EFAULT;
    }

    /* Perbarui posisi pembacaan */
    *pos += bytes;

    pr_info("User membaca file /proc/%s\n",
            PROC_FILENAME);

    return bytes;
}

/* Daftar operasi yang didukung file virtual */
static const struct proc_ops proc_file_ops = {
    .proc_read = proc_read,
};

/*
 * Dijalankan ketika kernel module dimuat
 */
static int __init proc_io_init(void)
{
    /* Membuat file virtual di direktori /proc */
    if (!proc_create(PROC_FILENAME, 0444,
                     NULL, &proc_file_ops)) {
        pr_err("Gagal membuat /proc/%s\n",
               PROC_FILENAME);
        return -ENOMEM;
    }

    pr_info("Kernel Module I/O dimuat. File /proc/%s telah dibuat.\n",
            PROC_FILENAME);

    return 0;
}

/*
 * Dijalankan ketika kernel module dilepas
 */
static void __exit proc_io_exit(void)
{
    /* Hapus file virtual dari /proc */
    remove_proc_entry(PROC_FILENAME, NULL);

    pr_info("Kernel Module I/O dilepas. File /proc/%s telah dihapus.\n",
            PROC_FILENAME);
}

/* Registrasi fungsi inisialisasi dan keluar */
module_init(proc_io_init);
module_exit(proc_io_exit);

/* Informasi kernel module */
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Praktikan Sistem Operasi");
MODULE_DESCRIPTION("Contoh Modul I/O dengan /proc");
MODULE_VERSION("1.0");
