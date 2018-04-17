
#include <stdio.h>
#include <stdlib.h>

struct Point {
    int x;
    int y;
};

/**
 * Definition for a point.
 * struct Point {
 *     int x;
 *     int y;
 * } */
int maxPoints(struct Point *points, int pointsSize)
{
    int i, j;
    struct Point *tp;
    int num = 0;

    if (pointsSize <= 2) return pointsSize;

    for (i = 0; i < pointsSize; i++) {
        for (j = i + 1; j < pointsSize; j++) {
        }
    }

    return num;
}


int main()
{
    struct Point pts[] = {{0, 0}, {1,1}, {2, 3}, {2, 2}, {3, 4}};
    int num = 0;

    num = maxPoints(pts, 5);

    printf("max: %d\n", num);

    return 0;
}
