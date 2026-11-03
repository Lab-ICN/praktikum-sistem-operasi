// Source: https://gist.github.com/ahmadnafi30/2b5b6f3fdf32e3a92859f42b03a19af1
// Original author: @ahmadnafi30
// Modified for lab practicum purposes

#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *fh;
    fh = fopen("Praktikum_IX.txt", "w");

    if (fh == NULL) {
        puts("Can't open that file!");
        exit(1);
    }

    fprintf(fh, "testing");
    fclose(fh);

    return 0;
}
