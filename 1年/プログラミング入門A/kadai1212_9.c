// AJG23055 牧野唯希
#include <stdio.h>

int main (void) {
  int x = 7;
  int y = 3;

  int *px = &x;
  int *py = &y;

  printf("x = %d, y = %d\n", x, y);
  printf("x %% y =%d\n", *px % *py);

  return 0;  
} 