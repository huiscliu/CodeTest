
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct Point {
    int x;
    int y;
};

/**
 * Definition for a point.
 * struct Point {
 *     int x;
 *     int y;
 * }
 */

int get_unused_point(int i, int j, int k)
{
    int l, m;

    assert(i < j);

    l = i;
    m = j - i - 1 + l;

    if (k <= l) {
        return k - 1;
    }
    else if (k > m) {
        return k - m + j;
    }
    else {
        return k - l + i;
    }
}

int maxPoints(struct Point *points, int pointsSize)
{
    int i, j, k, m, rm = pointsSize - 2;
    int n, mx = 0;
    struct Point *p;

    if (pointsSize <= 2) return pointsSize;

    /* shorter one */
    p = points;

    for (i = 0; i < pointsSize; i++) {
        for (j = i + 1; j < pointsSize; j++) {
            n = 2;

            for (k = 1; k <= rm; k++) {
                m = get_unused_point(i, j, k);

                /* vertical */
                if (p[i].x == p[j].x) {
                    if (p[m].x == p[i].x) n++;
                }
                else if ((p[i].y - p[j].y) * (p[i].x - p[m].x) == (p[i].x - p[j].x) * (p[i].y - p[m].y)) {
                    n++;
                }
            }

            if (n > mx) mx = n;
        }
    }

    return mx;
}


int main()
{
    {
        struct Point pts[] = {{0, 0}, {1,1}, {2, 3}, {2, 2}, {3, 4}, {3, 3}, {4, 4}, {4, 5}};
        int num = 0;

        num = maxPoints(pts, 8);

        printf("max: %d\n", num);
    }

    {
        struct Point pts[] = {{0, 65536}, {1,65536}, {65536, 0}};
        int num = 0;

        num = maxPoints(pts, 3);

        printf("max: %d\n", num);
    }

    return 0;
}
