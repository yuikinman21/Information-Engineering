#include <stdio.h>

void func (int **w, int *x, int **y, int z) {
    z = **w;
    *w = x;
    *y = *w;
    **y += z - (*x) - (**w);
}

int main() {
    int a = 2, b = 4, c = 7;
    int *ap = &a, *cp = &c;
    func (&ap, &b, &cp, c);
    printf("a = %d, b = %d, c = %d\n", a, b, c);
    return 0;
}