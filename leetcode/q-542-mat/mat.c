
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

typedef struct Pair_
{
    int i;
    int j;
} Pair;

int ** mat_gen(int row, int col)
{
    int i, j;
    int **A;
    int zero = 0;

    assert(row > 0);
    assert(col > 0);

    srand(time(0));

    A = malloc(sizeof(*A) * row);
    assert(A != NULL);

    for (i = 0; i < row; i++) {
        A[i] = malloc(sizeof(int) * col);
        assert(A[i] != NULL);
    }

    for (i = 0; i < row; i++) {
        for (j = 0; j < col; j++) {
            A[i][j] = rand() % 2;

            if (A[i][j] == 0) zero = 1;
            printf("%3d ", A[i][j]);
        }
        printf("\n");
    }

    if (!zero) {
        i = rand() % row;
        j = rand() % col;

        A[i][j] = 0;
    }

    return A;
}

int mat_get_dis(int **B, int i, int j, int r, int c, int round)
{
    int k = -1, d = -1;

    if (B[i][j] >= 0) {
        return B[i][j];
    }

    /* dis: up */
    if (i > 0 && B[i - 1][j] >= 0) {
        k = B[i - 1][j];

        if (d < 0) {
            d = k;
        }
        else if (d >= 0 && d > k) {
            d = k;
        }
    }

    /* dis: down */
    if (i < r - 1  && B[i + 1][j] >= 0) {
        k = B[i + 1][j];

        if (d < 0) {
            d = k;
        }
        else if (d >= 0 && d > k) {
            d = k;
        }
    }

    /* dis: left */
    if (j > 0 && B[i][j - 1] >= 0) {
        k = B[i][j - 1];

        if (d < 0) {
            d = k;
        }
        else if (d >= 0 && d > k) {
            d = k;
        }
    }

    /* dis: right */
    if (j < c - 1 && B[i][j + 1] >= 0) {
        k = B[i][j + 1];

        if (d < 0) {
            d = k;
        }
        else if (d >= 0 && d > k) {
            d = k;
        }
    }

    if (d >= 0) {
        if (d <= round) {
            B[i][j] = 1 + d;
        }
        else {
            d = -1;
        }
    }

    return d;
}

int ** mat_dis(int **A, int r, int c)
{
    int **B;
    int i, j;
    Pair *td; /* to be determined */
    int s, m, d, round;

    assert(A != NULL);
    assert(r > 0);
    assert(c > 0);

    B = malloc(sizeof(*B) * r);
    assert(B != NULL);

    for (i = 0; i < r; i++) {
        B[i] = malloc(sizeof(int) * c);
        assert(B[i] != NULL);
    }

    /* aux mem */
    td = malloc(sizeof(*td) * r * c);

    s = 0;
    for (i = 0; i < r; i++) {
        for (j = 0; j < c; j++) {
            if (A[i][j] == 0) {
                B[i][j] = 0;
            }
            else {
                B[i][j] = -1;

                td[s].i = i;
                td[s].j = j;

                s++;
            }
        }
    }

    /* width first search */
    round = 0;
    while (s > 0) {
        m = 0;
        for (i = 0; i < s; i++) {
            d = mat_get_dis(B, td[i].i, td[i].j, r, c, round);

            if (d < 0) {
                td[m].i =  td[i].i;
                td[m].j =  td[i].j;
                m++;
            }
        }

        s = m;
        round += 1;
    }

    free(td);

    return B;
}

int main(int argc, char **argv)
{
    int **A, **B;
    int r, c;
    int i, j;

    assert(argc > 2);

    r = atoi(argv[1]);
    c = atoi(argv[2]);

    printf("\nRandom 0-1 matrix:\n");
    A = mat_gen(r, c);

    printf("\nResult matrix:\n");
    B = mat_dis(A, r, c);

    /* print results */
    for (i = 0; i < r; i++) {
        for (j = 0; j < c; j++) {
            printf("%3d ", B[i][j]);
        }

        free(B[i]);
        free(A[i]);
        printf("\n");
    }

    free(B);
    free(A);

    return 0;
}
