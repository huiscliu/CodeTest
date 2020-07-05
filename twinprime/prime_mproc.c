
#define _XOPEN_SOURCE

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <getopt.h>
#include <string.h>
#include <limits.h>
#include <sys/wait.h>
#include <sys/shm.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "twinprime.h"

int main(int argc, char *argv[])
{
    int option;
    int print_twin_primes = 1;
    unsigned int rmax = UINT_MAX;
    int num_procs = 1;
    unsigned int i, bs, bs_ui;
    Range *rg;
    int gap = 2;

    /* shared memory */
    int shmid;

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
                num_procs = atoi(optarg);
                assert(num_procs > 0);
                break;

            default:
                break;
        }
    }

    /* partition work */
    size_of_ui = sizeof(unsigned int) * 8;
    rg = malloc(sizeof(*rg) * num_procs);

    bs_ui = rmax /  size_of_ui + 1;
    bs = (bs_ui + num_procs - 1) / num_procs;

    for (i = 0; i < (unsigned int)num_procs; i++) {
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

    /* create shared memory, and attached to if_prime */
    shmid = shm_open("ella", O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
    if (shmid == -1) {
        perror("shm_open");
        return -1;
    }

    /* set size */
    ftruncate(shmid, sizeof(*if_prime) * bs_ui);

    if_prime = mmap(NULL, sizeof(*if_prime) * bs_ui,
            PROT_READ | PROT_WRITE, MAP_SHARED, shmid, 0);

    if(if_prime == (void*)-1)  {  
        fprintf(stderr, "shmat failed\n");  
        exit(EXIT_FAILURE);  
    }

    /* init, all 1-bits */
    for (i = 0; i < bs_ui; i++) if_prime[i] = ~0;

    /* create number procs */
    for (i = 0; i < (unsigned int)num_procs; i++) {
        switch(fork()) {
            case -1:
                perror("fork");
                break;

            case 0:
                twin_create(rg + i);
                exit(0);
                break;

            default:
                break;
        }
    }

    /* wait procs to complete */
    while(wait(NULL) != -1);

    /* get all twin primes */
    if (print_twin_primes) print_all_twin_primes(rmax, gap);

    /* free */
    free(rg);

    /* shared memory */
    munmap(if_prime, sizeof(*if_prime) * bs_ui);
    shm_unlink("ella");

    return 0;
}
