//AJG23055 牧野唯希
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main (void) {
  int a, i;
  srand ((unsigned) time (NULL));

  a = rand () % 5;
  printf ("%d\n", 2 * a + 1);
  
  return 0;
}