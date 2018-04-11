
#ifndef STACK_H__
#define STACK_H__

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

typedef struct STACK_
{
    int size;
    int alloc;
    int elem_size;

    void *d;

} STACK;

#ifdef __cplusplus
extern "C" {
#endif

STACK * stack_create(size_t elem_size);
void stack_destroy(STACK *s);

void stack_push(STACK *s, void *m);
void stack_pop(STACK *s, void *m);

#ifdef __cplusplus
}
#endif

#endif
