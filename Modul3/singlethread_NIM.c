#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int num_accts = 1024;
static int num_trans = 10000;
static int think_time = 50;

struct acct_t {
    int bal;
};

static struct acct_t *accts;

static void print_usage(const char *program)
{
    fprintf(stderr,
            "usage: %s [-a <accts>] [-i <transactions>] [-t <think-time>]\n",
            program);
}

static int parse_nonnegative_int(const char *text, int allow_zero, int *value)
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
    if (!(argc == 1 || argc == 3 || argc == 5 || argc == 7)) {
        return -1;
    }

    for (int index = 1; index < argc; index += 2) {
        int allow_zero = strcmp(argv[index], "-a") != 0;
        int parsed;

        if (index + 1 >= argc ||
            parse_nonnegative_int(argv[index + 1], allow_zero, &parsed) != 0) {
            return -1;
        }

        if (strcmp(argv[index], "-a") == 0) {
            num_accts = parsed;
        } else if (strcmp(argv[index], "-i") == 0) {
            num_trans = parsed;
        } else if (strcmp(argv[index], "-t") == 0) {
            think_time = parsed;
        } else {
            return -1;
        }
    }

    return 0;
}

static void *transact(void *dummy)
{
    (void)dummy;

    for (int index = 0; index < num_trans; index++) {
        int acct_id_from = rand() % num_accts;
        int acct_id_to = rand() % num_accts;
        int amount = rand() % 100;

        if (accts[acct_id_from].bal > amount) {
            volatile int delay;

            accts[acct_id_from].bal -= amount;
            accts[acct_id_to].bal += amount;

            delay = amount * think_time;
            while (delay-- > 0) {
                /* Simulasi waktu pemrosesan. */
            }
        }
    }

    return NULL;
}

int main(int argc, char **argv)
{
    int original_sum = 0;
    int sum = 0;

    if (parse_arguments(argc, argv) != 0) {
        print_usage(argv[0]);
        return EXIT_FAILURE;
    }

    fprintf(stderr, "%s: -a %d -i %d -t %d\n",
            argv[0], num_accts, num_trans, think_time);

    srand(1);
    accts = malloc((size_t)num_accts * sizeof(*accts));
    if (accts == NULL) {
        perror("malloc gagal");
        return EXIT_FAILURE;
    }

    for (int index = 0; index < num_accts; index++) {
        accts[index].bal = rand() % 1000;
        original_sum += accts[index].bal;
    }

    transact(NULL);

    for (int index = 0; index < num_accts; index++) {
        sum += accts[index].bal;
    }

    if (sum != original_sum) {
        fprintf(stderr, "ERROR! original_sum = %d, sum = %d\n",
                original_sum, sum);
    } else {
        fprintf(stderr, "Values are still consistent\n");
    }

    free(accts);
    return sum == original_sum ? EXIT_SUCCESS : EXIT_FAILURE;
}
