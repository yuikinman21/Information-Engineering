//AJG23055 牧野唯希

#include <stdio.h>
#include <stdlib.h>

double calc(int n) {
    double kakuritsu = 1.0;
    for (int i = 0; i < n; i++) {
        kakuritsu *= (365.0 - i) / 365.0;
    }
    return 1.0 - kakuritsu;
}

int main(void) {
    int n = 1;
    while (1) {
        double kakuritsu = calc(n);
        if (kakuritsu >= 0.5) {
            printf("N = %d\n", n);
            break;
        }
        n++;
    }
    return 0;
}