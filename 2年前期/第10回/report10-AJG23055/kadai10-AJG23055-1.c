//AJG23055 牧野唯希

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ELEMENT 1000
#define MAX 100

int main(void) {
  int num[ELEMENT];
  int *pt = num;
  int count[MAX] = {0};

  srand((unsigned int)time(NULL));
  
  for (int i; i < ELEMENT; i++) {
    num[i] = rand() % MAX;

  }
  
  for (int i; i<ELEMENT; i++) {
    for (int j = 0; j < MAX; j++) {
      if (*(pt + i) == j) {
        count[j]++;
      }
    }

  }

  for (int i; i < MAX; i++) {
    printf("%2d is %2d times.\n", i, count[i]);
    
  }

  
  return 0;
  
}