#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
    int sz;

    int fd = open("foo.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0)
    {
        perror("r1");
        exit(1);
    }

    sz = write(fd, "hello geeks\n", strlen("hello geeks\n"));
    printf("called write(%d, \"hello geeks\\n\", %ld). it returned %d\n",
           fd, strlen("hello geeks\n"), sz);

    close(fd);
    return 0;
}