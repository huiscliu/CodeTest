
#include "stack.h"

int main()
{
    {
        STACK *s = stack_create(sizeof(int));
        int y, i;

        printf("------------- test, int -------------\n");
        for (i = 0; i < 20; i++) {
            stack_push(s, &i);
            printf("pushed int: %d\n", i);
        }

        printf("\n");

        for (i = 0; i < 20; i++) {
            stack_pop(s, &y);
            printf("poped  int: %d\n", y);
        }

        stack_destroy(s);
    }

    {
        STACK *s = stack_create(sizeof(double));
        double y;
        int i;

        printf("\n------------- test, double -------------\n");
        for (i = 0; i < 20; i++) {
            y = i * i;
            stack_push(s, &y);
            printf("pushed double: %g\n", y);
        }

        printf("\n");

        for (i = 0; i < 20; i++) {
            stack_pop(s, &y);
            printf("poped  double: %g\n", y);
        }

        stack_destroy(s);
    }

    return 0;
}
