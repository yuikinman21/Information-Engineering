//AJG23055 牧野唯希
#include <stdio.h>

int conbination (int n, int r) {
  if (r == 0 || r == n) {
    return 1;
  } else {
    return conbination (n - 1, r - 1) + conbination (n - 1, r);
  }
}

int main(void) {
  int i, n, r;
  printf ("Input n: ");
  scanf ("%d", &n);
  printf ("Input r: ");
  scanf ("%d", &r);
  printf ("Answer: %d\n", conbination (n,r));
}