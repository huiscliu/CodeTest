
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <getopt.h>
#include <string.h>
#include <limits.h>
#include <pthread.h>

#include "twinprime.h"

int main(int argc, char *argv[])
{
    int option;
    int print_twin_primes = 1;
    unsigned int rmax = UINT_MAX;
    int num_threads = 1;
    unsigned int i, bs, bs_ui;
    Range *rg;
    pthread_t *ptd;
    int gap = 2;

    /* option */
    while ((option = getopt(argc, argv, "qm:c:Pg:")) != -1) {
        switch (option) {
            case 'q':
                print_twin_primes = 0;
                break;

            case 'm':
                rmax = strtoul(optarg, NULL, 10);
                assert(rmax > 1);
                break;

            case 'g':
                gap = atoi(optarg);
                assert(gap > 0);
                break;

            case 'c':
                num_threads = atoi(optarg);
                assert(num_threads > 0);
                break;

            default:
                break;
        }
    }

    /* partition work */
    size_of_ui = sizeof(unsigned int) * 8;
    rg = malloc(sizeof(*rg) * num_threads);

    bs_ui = rmax /  size_of_ui + 1;
    bs = (bs_ui + num_threads - 1) / num_threads;

    for (i = 0; i < (unsigned int)num_threads; i++) {
        rg[i].id = i;
        rg[i].low = i * bs * size_of_ui + 1;
        rg[i].up = (i + 1) * bs * size_of_ui;

        if (rg[i].up > rmax) rg[i].up = rmax;
        if (rg[i].up <= rg[i].low) rg[i].up = rmax;
    }

    /* set mask */
    for (i = 0; i < size_of_ui; i++) {
        flag_ui[i] = 1 << i;
    }

    /* if_prime */
    if_prime = malloc(sizeof(*if_prime) * bs_ui);

    /* init, all 1-bits */
    for (i = 0; i < bs_ui; i++) if_prime[i] = ~0;

    /* create num_threads threads */
    ptd = malloc(sizeof(*ptd) * num_threads);

    for (i = 0; i < (unsigned int) num_threads; i++) {
        pthread_create(ptd + i, NULL, twin_create, rg + i);
    }

    /* join num_threads, wait threads to complete */
    for (i = 0; i < (unsigned int)num_threads; i++) {
        pthread_join(ptd[i], NULL);
    }

    /* get all twin primes */
    if (print_twin_primes) print_all_twin_primes(rmax, gap);

    /* free */
    free(rg);
    free(if_prime);
    free(ptd);

    return 0;
}
