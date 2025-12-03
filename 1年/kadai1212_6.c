//AJG23055 牧野唯希
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main (void) {
  int a;
  srand((unsigned int) time(NULL));
  float sum = 0;

  for (int i =0; i < 5; i++) {
    a = rand();
    printf("%d\n",a % 101);
    sum += (a % 101);
  }
  printf("average=%.1f\n", sum / 5.0);
  return 0;
}