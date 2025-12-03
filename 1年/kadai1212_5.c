//AJG23055 牧野唯希
#include <stdio.h>

int main (void) {
  int sum = 0;
  
  for (int i = 1; i <= 10; i++) {
    sum += i * (i + 1) * (i + 2) / 6;
  }

  printf("%d\n",sum);

  return 0;
}