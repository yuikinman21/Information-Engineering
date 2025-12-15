//AJG23055 牧野唯希

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define N 6
#define MAX 1000
#define epsilon 1.0e-10


int main(void) {
    int i, j;
    double Norm, y[N];
    double A[N][N] = {
        {1.0, 1.0, 3.0, 3.0, 5.0, 5.0},
        {1.0, 1.0, 3.0, 1.0, 1/3.0, 1/3.0},
        {1/3.0, 1/3.0, 1.0, 1/5.0, 1/3.0, 1/3.0},
        {1/3.0, 1.0, 5.0, 1.0, 1.0, 3.0},
        {1/5.0, 3.0, 3.0, 1.0, 1.0, 1/3.0},
        {1/5.0, 3.0, 3.0, 1/3.0, 3.0, 1.0}};

    do {
        double x[N] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};

    } while (0);
    return 0;
}