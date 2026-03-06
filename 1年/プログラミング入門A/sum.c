// AJG23055　牧野唯希
#include <stdio.h>

int main(void) {
  int x1, x2;
  int sum;

  printf("2つの正の整数を入力せよ。(A < B)\n");
  printf("整数A：");
  scanf("%d", &x1);
  printf("整数B：");
  scanf("%d", &x2);

  sum = (x1 + x2) * (x2 - x1 + 1) / 2;

  printf("%dから%dまでの総和は%d!\n", x1, x2, sum);

  return 0;
}