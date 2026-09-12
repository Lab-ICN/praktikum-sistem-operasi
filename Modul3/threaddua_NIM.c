#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define WORK_ITERATIONS 0xFFFFFFFFUL
#define THREAD_COUNT 2

static pthread_t thread_ids[THREAD_COUNT];

static void *do_something(void *argument)
{
    volatile unsigned long work;
    pthread_t id = pthread_self();

    (void)argument;

    if (pthread_equal(id, thread_ids[0])) {
        printf("First thread processing\n");
    } else {
        printf("Second thread processing\n");
    }

    for (work = 0; work < WORK_ITERATIONS; work++) {
        /* Beban kerja sengaja dikosongkan untuk diamati melalui top. */
    }

    return NULL;
}

int main(void)
{
    for (int index = 0; index < THREAD_COUNT; index++) {
        int error = pthread_create(&thread_ids[index], NULL,
                                   do_something, NULL);
        if (error != 0) {
            fprintf(stderr, "Can't create thread: [%s]\n", strerror(error));
        } else {
            printf("Thread created successfully\n");
        }
    }

    /* Sesuai contoh modul: main menunggu lima detik sebelum selesai. */
    sleep(5);
    return EXIT_SUCCESS;
}
