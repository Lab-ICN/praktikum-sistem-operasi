#include <errno.h>
#include <limits.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int num_accts = 1024;
static int num_trans = 10000;
static int think_time = 50;
static int num_threads = 2;
static int use_lock = 0;

struct acct_t {
    int bal;
};

struct worker_arg {
    unsigned int seed;
};

static struct acct_t *accts;
static pthread_mutex_t accounts_lock = PTHREAD_MUTEX_INITIALIZER;

static void print_usage(const char *program)
{
    fprintf(stderr,
            "usage: %s [-a <accts>] [-i <transactions>] [-t <think-time>] "
            "[-n <threads>] [--safe|--unsafe]\n",
            program);
}

static int parse_positive_or_zero(const char *text, int allow_zero, int *value)
{
    char *end = NULL;
    long parsed;

    errno = 0;
    parsed = strtol(text, &end, 10);
    if (errno != 0 || end == text || *end != '\0' || parsed > INT_MAX ||
        parsed < (allow_zero ? 0 : 1)) {
        return -1;
    }

    *value = (int)parsed;
    return 0;
}

static int parse_arguments(int argc, char **argv)
{
    for (int index = 1; index < argc; index++) {
        int *destination = NULL;
        int allow_zero = 0;

        if (strcmp(argv[index], "--safe") == 0) {
            use_lock = 1;
            continue;
        }
        if (strcmp(argv[index], "--unsafe") == 0) {
            use_lock = 0;
            continue;
        }

        if (strcmp(argv[index], "-a") == 0) {
            destination = &num_accts;
        } else if (strcmp(argv[index], "-i") == 0) {
            destination = &num_trans;
            allow_zero = 1;
        } else if (strcmp(argv[index], "-t") == 0) {
            destination = &think_time;
            allow_zero = 1;
        } else if (strcmp(argv[index], "-n") == 0) {
            destination = &num_threads;
        } else {
            return -1;
        }

        if (++index >= argc ||
            parse_positive_or_zero(argv[index], allow_zero, destination) != 0) {
            return -1;
        }
    }

    return 0;
}

static void transfer_money(unsigned int *seed)
{
    int acct_id_from = (int)(rand_r(seed) % (unsigned int)num_accts);
    int acct_id_to = (int)(rand_r(seed) % (unsigned int)num_accts);
    int amount = (int)(rand_r(seed) % 100U);

    if (use_lock) {
        pthread_mutex_lock(&accounts_lock);
    }

    if (accts[acct_id_from].bal > amount) {
        accts[acct_id_from].bal -= amount;
        accts[acct_id_to].bal += amount;
    }

    if (use_lock) {
        pthread_mutex_unlock(&accounts_lock);
    }

    {
        volatile int delay = amount * think_time;
        while (delay-- > 0) {
            /* Simulasi waktu pemrosesan di luar critical section. */
        }
    }
}

static void *transact(void *argument)
{
    struct worker_arg *worker = argument;

    for (int index = 0; index < num_trans; index++) {
        transfer_money(&worker->seed);
    }

    return NULL;
}

int main(int argc, char **argv)
{
    pthread_t *threads = NULL;
    struct worker_arg *arguments = NULL;
    int original_sum = 0;
    int sum = 0;
    int created = 0;
    int result = EXIT_FAILURE;

    if (parse_arguments(argc, argv) != 0) {
        print_usage(argv[0]);
        return EXIT_FAILURE;
    }

    fprintf(stderr, "%s: -a %d -i %d -t %d -n %d mode=%s\n",
            argv[0], num_accts, num_trans, think_time, num_threads,
            use_lock ? "safe" : "unsafe");

    srand(1);
    accts = malloc((size_t)num_accts * sizeof(*accts));
    threads = malloc((size_t)num_threads * sizeof(*threads));
    arguments = malloc((size_t)num_threads * sizeof(*arguments));
    if (accts == NULL || threads == NULL || arguments == NULL) {
        perror("malloc gagal");
        goto cleanup;
    }

    for (int index = 0; index < num_accts; index++) {
        accts[index].bal = rand() % 1000;
        original_sum += accts[index].bal;
    }

    for (int index = 0; index < num_threads; index++) {
        int error;

        arguments[index].seed = (unsigned int)(index + 1);
        error = pthread_create(&threads[index], NULL, transact,
                               &arguments[index]);
        if (error != 0) {
            fprintf(stderr, "pthread_create gagal: %s\n", strerror(error));
            goto join_created_threads;
        }
        created++;
    }

join_created_threads:
    for (int index = 0; index < created; index++) {
        int error = pthread_join(threads[index], NULL);
        if (error != 0) {
            fprintf(stderr, "pthread_join gagal: %s\n", strerror(error));
            goto cleanup;
        }
    }

    if (created != num_threads) {
        goto cleanup;
    }

    for (int index = 0; index < num_accts; index++) {
        sum += accts[index].bal;
    }

    if (sum != original_sum) {
        fprintf(stderr, "RACE CONDITION! original_sum = %d, sum = %d\n",
                original_sum, sum);
    } else {
        fprintf(stderr, "Values are still consistent\n");
    }

    result = (use_lock && sum != original_sum) ? EXIT_FAILURE : EXIT_SUCCESS;

cleanup:
    free(arguments);
    free(threads);
    free(accts);
    pthread_mutex_destroy(&accounts_lock);
    return result;
}
