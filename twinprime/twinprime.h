#ifndef TWIN_PRIME_H
#define TWIN_PRIME_H

/* bits of an unsigned int */
extern unsigned int size_of_ui;

/* bit mask, 2^p */
extern unsigned int flag_ui[32];

/* if one digital number is prime */
extern unsigned int *if_prime;

#ifdef __cplusplus
extern "C" {
#endif

typedef struct Range_
{
    unsigned id;
    unsigned low;
    unsigned up;

} Range;

int is_prime(unsigned int num);

int is_not_marked(unsigned int num);
void mark_non_prime(unsigned int num);

void *twin_create(void *rg);

void print_all_primes(unsigned int rmax);
void print_all_twin_primes(unsigned int rmax, int gap);

#ifdef __cplusplus
}
#endif

#endif
