//AJG23055 牧野唯希

#include <stdio.h>

int main (void) {
  int i, j;
  int sum = 0;

  int judge = 0;

  for (i = 2; i <= 100; ++i) {
    judge = 0;
    for (j = 2; j < i; ++j) {
      if (i % j == 0) {
        judge = 1;
        break;
      }
    }
    if (judge == 0) {
      sum += i;
      printf("%3d,", i);
    }
  }
  putchar ('\n');

  printf("sum = %d\n", sum);

  

  return 0;
}

