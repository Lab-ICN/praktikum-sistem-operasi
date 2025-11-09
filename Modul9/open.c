#include <errno.h>
#include <fcntl.h>
#include <stdio.h>

extern int errno;

int main() {
    // Jika file tidak ada di direktori,
    // maka file foo.txt akan dibuat.
    int fd = open("foo.txt", O_RDONLY | O_CREAT, 0644);
    printf("fd = %d\n", fd);

    if (fd == -1) {
        // Menampilkan nomor error
        printf("Error Number: %d\n", errno);
        // Menampilkan detail kesalahan dari sistem
        perror("Program");
    }

    return 0;
}
