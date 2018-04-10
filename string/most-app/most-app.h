
#ifndef MOST_APP_H__
#define MOST_APP_H__

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

/* bounded arrary */
typedef struct BdAry_
{
    int size;
    char **att;

} BdAry;

/* stat Pair, times that att appear */
typedef struct Pair_
{
    int size;
    char *att;

} Pair;

#ifdef __cplusplus
extern "C" {
#endif

/* sort Pair */
int pair_cmp(const void *ag1, const void *ag2);

/* sort appear times: reverse order */
int pair_num_cmp(const void *ag1, const void *ag2);

/* sort excluding */
int string_cmp(const void *ag1, const void *ag2);

/* main function */
BdAry * bdary_find_most_appear(char *text, BdAry *ecd);

#ifdef __cplusplus
}
#endif

#endif
