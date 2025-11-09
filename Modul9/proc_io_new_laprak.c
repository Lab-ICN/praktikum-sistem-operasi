#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/proc_fs.h>
#include <linux/uaccess.h>

#define PROC_FILENAME "praktikum_io"

static char msg_buffer[50] = "Halo! Ini adalah output dari kernel module.\n";
static int msg_len = 0;

static ssize_t proc_read(struct file *file, char __user *usr_buf, size_t count, loff_t *pos)
{
    if (*pos > 0) {
        return 0;
    }

    if (copy_to_user(usr_buf, msg_buffer, msg_len)) {
        pr_err("Gagal menyalin data ke user.\n");
        return -EFAULT;
    }

    *pos = msg_len;

    pr_info("User membaca file /proc/%s\n", PROC_FILENAME);

    return msg_len;
}

static const struct proc_ops proc_file_ops = {
    .proc_read = proc_read,
};

static int __init proc_io_init(void)
{
    msg_len = strlen(msg_buffer);

    proc_create(PROC_FILENAME, 0444, NULL, &proc_file_ops);

    pr_info("Kernel Module I/O dimuat. File /proc/%s telah dibuat.\n", PROC_FILENAME);
    return 0;
}

static void __exit proc_io_exit(void)
{
    remove_proc_entry(PROC_FILENAME, NULL);

    pr_info("Kernel Module I/O dilepas. File /proc/%s telah dihapus.\n", PROC_FILENAME);
}

module_init(proc_io_init);
module_exit(proc_io_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Praktikan Sistem Operasi");
MODULE_DESCRIPTION("Contoh Modul I/O dengan /proc");