//AJG23055 牧野唯希

#include <stdio.h>

int main (void) {
  int x = 11, y = 14;

  int *p_x = &x;
  int *p_y = &y;
  int temp;

  printf("x = %d, y = %d\n", x, y); //x = 11, y = 14

  temp = *p_x;
  *p_x = *p_y;
  *p_y = temp;
  
  printf("x = %d, y = %d\n", x, y); //x = 14, y = 11

  return 0;
}