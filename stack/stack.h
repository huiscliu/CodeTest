
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
    int magic;

    void *d;

} STACK;

#define STACK_MAGIC 0x20180410

#ifdef __cplusplus
extern "C" {
#endif

STACK * stack_create(size_t elem_size);
void stack_destroy(STACK *s);

void stack_push(STACK *s, void *m);
void stack_pop(STACK *s, void *m);

int stack_get_size(STACK *s);
int stack_get_elem_size(STACK *s);

#ifdef __cplusplus
}
#endif

#endif
