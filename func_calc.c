//AJG23055 牧野唯希
#include <stdio.h>
#include <stdlib.h>

void calc(double a, double b) {
  printf("a + b =%f\n", a + b);
  printf("a - b =%f\n", a - b);
  printf("a * b =%f\n", a * b);
  printf("a / b =%f\n", a / b);  
}

int main (int argc, char **argv) {
  double a = atof(argv[1]);
  double b = atof(argv[2]);

  calc(a,b);

  return 0;
}