//AJG23055 牧野唯希

#include <stdio.h>

  int main (void) {
    
    int x1, x2, y;

    float z, w1, w2, theta;


    do {
      printf ("x1(0 or 1):");
      scanf ("%d", &x1);

      if (x1 != 0 && x1 != 1) {
        printf("ERROR! Please try again!\n");
      }
      
    }  while (x1 != 0 && x1 != 1);

    do {
      printf ("x2(0 or 1):");
      scanf ("%d", &x2);

      if (x2 != 0 && x2 != 1) {
        printf("ERROR! Please try again!\n");
      }

    }  while (x2 != 0 && x2 != 1);

    printf("x1 = %d, x2 = %d\n", x1, x2);

    //w1 = 0.5, w2 = 0.5 theta = 0.7
    w1 = 0.5;
    w2 = 0.5;
    theta = 0.7;
    z = w1 * x1 + w2 * x2;

    if (z <= theta) {
      y = 0;
    }
    else {
      y = 1;
    }

    printf("In case of x1=%d, x2 = %d, the output of AND gate is y = %d\n", x1, x2, y);

    //w1 = 0.5, x2 = 0.5 theta = 0.3
    theta = 0.3;

    if (z <= theta) {
      y = 0;
    }
    else {
      y = 1;
    }
    printf("In case of x1=%d, x2 = %d, the output of OR gate is y = %d\n", x1, x2, y);

    return 0;
  }