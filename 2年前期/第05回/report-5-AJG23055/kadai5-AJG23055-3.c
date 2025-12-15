//AJG23055 牧野唯希

#include <stdio.h>

int main (void) {
  int num[] = {10,32,43,8,21,92,55,42,14,9};

  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      if (num[i] < num[j]) {
        int tmp = num[i];
        num[i] = num[j];
        num[j] = tmp;
      }
    }
  }
  for (int i = 0; i < 10; i++) {
    printf("%d\n", num[i]);
  }
}