#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void *thread1(void *argument)
{
    (void)argument;

    while (1) {
        printf("Hello!!\n");
    }

    return NULL;
}

static void *thread2(void *argument)
{
    (void)argument;

    while (1) {
        printf("How are you?\n");
    }

    return NULL;
}

static void report_pthread_error(const char *operation, int error_code)
{
    fprintf(stderr, "%s gagal: %s\n", operation, strerror(error_code));
}

int main(void)
{
    pthread_t tid1;
    pthread_t tid2;
    int status;

    status = pthread_create(&tid1, NULL, thread1, NULL);
    if (status != 0) {
        report_pthread_error("pthread_create thread1", status);
        return EXIT_FAILURE;
    }

    status = pthread_create(&tid2, NULL, thread2, NULL);
    if (status != 0) {
        report_pthread_error("pthread_create thread2", status);
        return EXIT_FAILURE;
    }

    status = pthread_join(tid1, NULL);
    if (status != 0) {
        report_pthread_error("pthread_join thread1", status);
        return EXIT_FAILURE;
    }

    status = pthread_join(tid2, NULL);
    if (status != 0) {
        report_pthread_error("pthread_join thread2", status);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
