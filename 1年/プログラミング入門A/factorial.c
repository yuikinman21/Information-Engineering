//AJG23055　牧野唯希

#include <stdio.h>

int factorial(int n) {
  int m;
  if (n == 0) {
    return 1;
  }
  m = factorial(n - 1);
  return n * m;
}

int main(void) {
  for (int i = 1; i < 11; i++) {
    printf("%d! = %d\n", i, factorial(i));
  }
  return 0;

}