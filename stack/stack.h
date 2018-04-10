
#ifndef STACK_H__
#define STACK_H__

#include <stdio.h>
#include <stdlib.h>

typedef struct SNODE_
{
    size_t size;
    void *d;

} SNODE;

typedef struct STACK_
{
    int size;
    int alloc;
    SNODE *n;

} STACK;

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif

#endif
