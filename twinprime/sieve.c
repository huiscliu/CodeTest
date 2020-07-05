#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>

/* dec */
int sieve_get(unsigned int *sieve, unsigned b);
void make(unsigned int *sieve, unsigned int P2, unsigned int P3);
int is_prime(unsigned int *sieve, unsigned int p);
void cal_loc(unsigned int num, int *loc, int *rloc);
int check_result_is_prime(unsigned int *sieve, unsigned int num);

int sieve_get(unsigned int *sieve, unsigned b)
{
    return (sieve[b >> 5] >> (b & 31)) & 1;
}

void make(unsigned int *sieve, unsigned int P2, unsigned int P3)
{
    unsigned int i, j, k;
    memset(sieve, 0, sizeof(*sieve));

    for (k = 1; k <= P3; k++)
        if (sieve_get(sieve, k) == 0)
            for (j = 2 * k + 1, i = 2 * k * (k + 1); i < P2; i += j)
                sieve[i >> 5] |= 1 << (i & 31);
}

int is_prime(unsigned int *sieve, unsigned int p)
{
    return p == 2 || (p > 2 && (p & 1) == 1 && (sieve_get(sieve, (p - 1) >> 1) == 0));
}

void cal_loc(unsigned int num, int *loc, int *rloc)
{
    /* assume 32-bit unsigned int */
    *loc = num >> 5;
    *rloc = num & 31;
}

/* bit is 1 */
int check_result_is_prime(unsigned int *sieve, unsigned int num)
{
    int loc, rloc;

    cal_loc(num, &loc, &rloc);
    return (sieve[loc] & (1 << rloc));
}

int main(int argc, char **argv)
{
    unsigned int i, n;
    unsigned int rmax = 100000000;
    unsigned int sieve_size;
    unsigned int P2, P3;
    unsigned int *sieve;
    unsigned int very = 0;

    if (argc == 2) rmax = strtoul(argv[1], NULL, 10);

    /* setup cache */
    sieve_size = rmax / 32 + 1;
    sieve = malloc(sizeof(*sieve) * sieve_size);
    for (i = 0; i < sieve_size; i++) sieve[i] = 0;

    P2 = ceil(rmax / 2.);
    P3 = ceil(ceil(sqrt(rmax)) / 2.);

    make(sieve, P2, P3);

    for (n = 0, i = 1; i <= rmax && i > 0; i++) if (is_prime(sieve, i)) n++;

    for (i = 1; i <= rmax / 2 && i > 0; i++) {
        if(check_result_is_prime(sieve, i)) very++;
    }

    printf("The number of primes below %u is %u.\n", rmax, n);
    printf("The number of primes below %u is %u.\n", rmax, rmax / 2 - very);

    return 0;
}
