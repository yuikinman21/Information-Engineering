//AJG23055 牧野唯希

#include <stdio.h> 

int main(void) {
  int i;

  for (i = 0; i < 1000; i++) {
    if (i % 31 == 0) {
      printf("%d\n", i);
    }
  }
  return 0;
}