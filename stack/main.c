
#include "stack.h"

int main()
{
    int ts = 10;

    {
        STACK *s = stack_create(sizeof(int));
        int y, i;

        printf("------------- test, int -------------\n");
        for (i = 0; i < ts; i++) {
            y = i + 3;
            stack_push(s, &y);
            printf("pushed int: %3d, stack size: %d\n", y, stack_get_size(s));
        }

        printf("\n");

        for (i = 0; i < ts; i++) {
            stack_pop(s, &y);
            printf("poped  int: %3d, stack size: %d\n", y, stack_get_size(s));
        }

        stack_destroy(s);
    }

    {
        STACK *s = stack_create(sizeof(double));
        double y;
        int i;

        printf("\n------------- test, double -------------\n");
        for (i = 0; i < ts; i++) {
            y = i * i;
            stack_push(s, &y);
            printf("pushed double: %3g, stack size: %d\n", y, stack_get_size(s));
        }

        printf("\n");

        for (i = 0; i < ts; i++) {
            stack_pop(s, &y);
            printf("poped  double: %3g, stack size: %d\n", y, stack_get_size(s));
        }

        stack_destroy(s);
    }

    return 0;
}
