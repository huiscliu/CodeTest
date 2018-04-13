
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

int ** mat_gen(int row, int col)
{
    int i, j;
    int **A;
    int zero = 0;

    assert(row > 0);
    assert(col > 0);

    srand(time(0));

    A = malloc(sizeof(*A) * row);
    for (i = 0; i < row; i++) A[i] = malloc(sizeof(int) * col);

    for (i = 0; i < row; i++) {
        for (j = 0; j < col; j++) {
            A[i][j] = rand() % 2;

            if (A[i][j] == 0) zero = 1;
        }
    }

    if (!zero) {
        i = rand() % row;
        j = rand() % col;

        A[i][j] = 0;
    }

    return A;
}

int ** mat_dis(int **A, int r, int c)
{
    int **B;
    int i, j;

    B = malloc(sizeof(*B) * r);
    for (i = 0; i < r; i++) B[i] = malloc(sizeof(int) * c);

    for (i = 0; i < r; i++) {
        for (j = 0; j < c; j++) {
            B[i][j] = A[i][j];
        }
    }
}

int main(int argc, char **argv)
{
    int **A;

    assert(argc > 2);

    A = mat_gen(atoi(argv[1]), atoi(argv[2]));

    return 0;
}
