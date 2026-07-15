#include <stdio.h>
int func1(int x, int y, int *z) {
    x = x + y;
    *z = x + y;
    return x + y;
}

int func2(int *x, int *y, int *z) {
    z = x;
    *y = *x;
    return *x + *z;
}

int main() {
    int a = 1, b = -2, c = 3;
    int tmp1 = func1(a, b, &c);
    int tmp2 = func2(&a, &b, &c);
    a = tmp1 + tmp2;
    printf("a = %d, b = %d, c = %d\n", a, b, c);
    return 0;
}
