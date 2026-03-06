// AJG23055 牧野唯希

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void) {
  int max = 1000;
  double pi = 3.141592;
  double x, y, z, w;

  for (int i = 0; i < 3; i++) {
    int count = 0;
    srand(time(NULL));

    for (int j = 0; j < max; j++) {
      x = (double)rand() / RAND_MAX;
      y = (double)rand() / RAND_MAX;
      z = x * x + y * y;
      if (z <= 1) {
        count++;
      }
    }
    w = (double)count / max * 4;
    printf("The probability that plotted points are in the sector is %f.\n",w / 4);
    printf("π = %f (%d attempts)\n", w, max);

    if (pi > w) {
      printf("The absolute value of π is %f\n", pi - w);
    } else {
      printf("The absolute value of π is %f\n", w - pi);
    }

    max *= 10;
    putchar('\n');
  }

  return 0;
}
