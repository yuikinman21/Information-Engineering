// AJG23055 牧野唯希
#include <stdio.h>

int main(void) {
  int x1, x2;

  printf("二つの1以上の整数を入力せよ。\n");
  printf("整数1：");
  scanf("%d", &x1);
  printf("整数2：");
  scanf("%d", &x2);

  printf("和：%d\n", x1 + x2);
  printf("差：%d\n", x1 - x2);
  printf("積：%d\n", x1 * x2);
  printf("商：%d\n", x1 / x2);
  printf("剰余：%d\n", x1 % x2);

  return 0;
}