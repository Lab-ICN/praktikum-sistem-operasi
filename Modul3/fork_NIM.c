#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main(void)
{
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork gagal");
        return EXIT_FAILURE;
    }

    if (pid == 0) {
        printf("This is being printed from the child process\n");
        printf("Child PID: %ld, Parent PID: %ld\n",
               (long)getpid(), (long)getppid());
        return EXIT_SUCCESS;
    }

    printf("This is being printed in the parent process.\n"
           "The process identifier (PID) of the child is %ld\n",
           (long)pid);

    return EXIT_SUCCESS;
}
