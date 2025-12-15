//AJG23055 牧野唯希
#include <stdio.h>

int main (void) {
  int a;

  for (int i = 1; i <= 9; i++) {
    for (int j = 1; j <= 9; j++) {
      a = i * j;
      printf ("%3d", a);
    }
    printf ("\n");
  }
}