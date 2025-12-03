//AJG23055 牧野唯希

#include <stdio.h>
#include <stdlib.h>

void swap (int* a, int* b) {
  printf("a = %d, b = %d\n", *a, *b);
  int temp;
  temp = *a;
  *a = *b;
  *b = temp;

  printf("a = %d, b = %d\n", *a, *b);
} 

int main (int argc, char **argv) {
  int a = atof(argv[1]);
  int b = atof(argv[2]);

  swap(&a,&b);

  return 0;
}