// AJG23055 牧野唯希
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void) {
  srand((unsigned int)time(NULL));

  for (int i = 0; i < 100; i++) {
    int random = rand() % 100;
    printf("%d\n", random + 1);
  }
  return 0;
}