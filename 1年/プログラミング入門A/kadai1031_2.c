//AJG23055 牧野唯希

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main (void) {
  double x, y, z;

  srand(time(NULL));
  x = (double)rand()/RAND_MAX;
  y = (double)rand()/RAND_MAX;
  z = x*x + y*y;

  if (z <= 1) {
    printf("The point (%f, %f) is in the sector.\n", x, y);
  }
  else {
    printf("The point (%f, %f) is outside the sector.\n", x, y);
  }
  return 0;
}