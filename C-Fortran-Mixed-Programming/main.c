
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

/* Fortran interface with underscore
 *
 * btw: different compiler has different convention */

extern void ftn_axpy_(double *a, double *x, double *y, int *n);
extern void ftn_amxpy_(double *a, int *Ap, int *Aj, double *Ax, double *x, double *y, int *n);

/* y = a*x + y */
void c_axpy(double a, double *x, double *y, int n)
{
    int i;

    for (i = 0; i < n; i++) y[i] += a * x[i];
}

/* y = a*A*x + y */
void c_amxpy(double a, int *Ap, int *Aj, double *Ax, double *x, double *y, int n)
{
    int i;

#pragma omp parallel for
    for (i = 0; i < n; i++) {
        double t = 0.;
        int j, end = Ap[i + 1];

        for (j = Ap[i]; j < end; j++) t = Ax[j] * x[Aj[j]];

        y[i] = a * t + y[i];
    }
}

double time_diff(struct timeval x , struct timeval y)
{
	double x_ms , y_ms , diff;

	x_ms = (double)x.tv_sec + (double)x.tv_usec * 1e-6;
	y_ms = (double)y.tv_sec + (double)y.tv_usec * 1e-6;

	diff = (double)y_ms - (double)x_ms;

	return diff;
}

double get_time(void)
{
    struct timeval x;

    gettimeofday(&x, NULL);

    return x.tv_sec + x.tv_usec * 1e-6;
}

int main(int argc, char **argv)
{
    double *vx;
    double *vy;
    double *fvx;
    double *fvy;
    double a = 3.2;
    int i, n, nnz;
    double t;

    int *Ap;
    int *Aj;
    double *Ax;

    if (argc == 1) {
        n = 1000000;
    }
    else {
        n = atoi(argv[1]);

        if (n <= 0) n = 1000000;
    }

    vx = malloc(n * sizeof(*vx));
    vy = malloc(n * sizeof(*vx));
    fvx = malloc(n * sizeof(*vx));
    fvy = malloc(n * sizeof(*vx));

    for (i = 0; i < n; i++) {
        vx[i] = fvx[i] = 1.;
        vy[i] = fvy[i] = i;
    }

    /* c */
    t = get_time();
    c_axpy(a, vx, vy, n);
    t = get_time() - t;
    printf("axpy: C   time: %e s\n", t);

    /* fortran */
    t = get_time();
    ftn_axpy_(&a, fvx, fvy, &n);
    t = get_time() - t;
    printf("axpy: For time: %e s\n", t);

    /* generate csr */
    srand(0);

    Ap = malloc((n + 1) * sizeof(*Ap));
    Ap[0] = 0;
    for (i = 0; i < n; i++) Ap[i + 1] = Ap[i] + 1 + rand() % 20;

    nnz = Ap[n];
    Aj = malloc(nnz * sizeof(*Aj));
    Ax = malloc(nnz * sizeof(*Ax));

    for (i = 0; i < nnz; i++) {
        Aj[i] = rand() % n;
        Ax[i] = 4 * (0.5 - rand() * 1. / RAND_MAX);
    }

    printf("\n");

    /* amxpy */
    t = get_time();
    c_amxpy(a, Ap, Aj, Ax, vx, vy, n);
    t = get_time() - t;
    printf("amxpy: C   time: %e s\n", t);

    t = get_time();
    ftn_amxpy_(&a, Ap, Aj, Ax, fvx, fvy, &n);
    t = get_time() - t;
    printf("amxpy: For time: %e s\n", t);

    return 0;
}
