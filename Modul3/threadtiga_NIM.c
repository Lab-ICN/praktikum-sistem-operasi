#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>

static int num_accts = 1024; // number of bank accounts
static int num_trans = 10000; // number of transactions
static int think_time = 50; // amount of "thinking time"

struct acct_t {
    int bal;
};

struct acct_t *accts;

void *transact(void *dummy)
{
    int i;
    for (i = 0; i < num_trans; i++) {
        int acct_id_from = rand() % num_accts;
        int acct_id_to = rand() % num_accts;
        int amt = rand() % 100;

        if (accts[acct_id_from].bal > amt) {
            accts[acct_id_from].bal -= amt;
            accts[acct_id_to].bal += amt;

            amt *= think_time;
            while (amt--) ;
        }
    }

    return NULL;
}

int main(int argc, char **argv)
{
    if (!(argc == 1 || argc == 3 || argc == 5 || argc == 7)) {
        fprintf(stderr, "usage: %s [-a <accts>] [-i <transactions>] [-t <think-time>]\n", argv[0]);
        exit(-1);
    }

    int i;
    for (i = 1; i < argc; i++) {
        if (!strcmp(argv[i], "-a")) {
            num_accts = atoi(argv[i+1]); i++;
        } else if (!strcmp(argv[i], "-i")) {
            num_trans = atoi(argv[i+1]); i++;
        } else if (!strcmp(argv[i], "-t")) {
            think_time = atoi(argv[i+1]); i++;
        } else {
            fprintf(stderr, "usage: %s [-a <accts>] [-i <transactions>] [-t <think-time>]\n", argv[0]);
            exit(-1);
        }
    }

    fprintf(stderr, "%s: -a %d -i %d -t %d\n", argv[0], num_accts, num_trans, think_time);

    srand(1);
    accts = (struct acct_t *)malloc(num_accts * sizeof(struct acct_t));

    int original_sum = 0;
    for (i = 0; i < num_accts; i++) {
        accts[i].bal = rand() % 1000;
        original_sum += accts[i].bal;
    }

    pthread_t tid1, tid2;
    pthread_create(&tid1, NULL, transact, NULL);
    pthread_create(&tid2, NULL, transact, NULL);
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);

    int sum = 0;
    for (i = 0; i < num_accts; i++) {
        sum += accts[i].bal;
    }

    if (sum != original_sum) {
        fprintf(stderr, "ERROR! original_sum = %d, sum = %d\n", original_sum, sum);
    } else {
        fprintf(stderr, "Values are still consistent\n");
    }

    return 0;
}
