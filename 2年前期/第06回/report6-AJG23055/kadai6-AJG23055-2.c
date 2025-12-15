//AJG23055 牧野唯希
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

double average (int a[10]) {
  int i, sum = 0;
  for (i = 0; i < 10; i++)
    sum += a[i];
  return sum / 10.0;
}

int main (void) {
  int a, i;
  int sumple[10];
  
  srand ((unsigned) time (NULL));
  for (int i = 0; i < 10; i++) {
    a = rand () % 101;
    sumple[i] = a;
    printf("%d\n", sumple[i]);
  }
  
  printf ("Average: %.1f\n", average (sumple));
  return 0;
}