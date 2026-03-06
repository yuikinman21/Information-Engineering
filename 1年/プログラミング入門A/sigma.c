// AJG23055 牧野唯希

#include <stdio.h>

int main(void) {

  int first = 1;
  int last = 100;
  int sigma;

  for (int i = first; i <= last; i++) {
    sigma += i * i;
  }
  printf("1^2+2^2+...+100^2 = %d\n", sigma);
}