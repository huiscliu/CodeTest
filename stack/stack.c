
#include "stack.h"

static void stack_check(STACK *s)
{
    if (s == NULL) return;

    if (s->magic != STACK_MAGIC) {
        fprintf(stderr, "stack not initialized yet: %d\n", __LINE__);
        exit(1);
    }
}

STACK * stack_create(size_t elem_size)
{
    STACK *s;

    assert(elem_size > 0);
    
    s = malloc(sizeof(*s));
    if (s == NULL) {
        fprintf(stderr, "failed to allocate memory: %d\n", __LINE__);
        exit(1);
    }

    s->size = 0;
    s->elem_size = elem_size;
    s->alloc = 64;
    s->magic = STACK_MAGIC;

    s->d = malloc(elem_size * s->alloc);
    if (s->d == NULL) {
        fprintf(stderr, "failed to allocate memory: %d\n", __LINE__);
        exit(1);
    }

    return s;
}

void stack_destroy(STACK *s)
{
    if (s == NULL) return;

    stack_check(s);
    if (s->alloc == 0) return;

    free(s->d);
    free(s);
}

void stack_push(STACK *s, void *m)
{
    assert(s != NULL);
    assert(m != NULL);

    stack_check(s);

    if (s->size >= s->alloc) {
        s->alloc += 64;

        s->d = realloc(s->d, s->elem_size * s->alloc);
        if (s->d == NULL) {
            fprintf(stderr, "failed to allocate memory: %d\n", __LINE__);
            exit(1);
        }
    }

    memcpy(s->d + s->size * s->elem_size, m, s->elem_size);
    s->size += 1;
}

void stack_pop(STACK *s, void *m)
{
    assert(s != NULL);
    assert(m != NULL);
    assert(s->size > 0);

    stack_check(s);

    memcpy(m, s->d + (s->size - 1) * s->elem_size, s->elem_size);
    s->size -= 1;
}

int stack_get_size(STACK *s)
{
    assert(s != NULL);
    stack_check(s);

    return s->size;
}

int stack_get_elem_size(STACK *s)
{
    assert(s != NULL);
    stack_check(s);

    return s->elem_size;
}
