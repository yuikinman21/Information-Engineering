// AJG23055 牧野唯希

#include <stdio.h>

int main(void) {
  int i;
  int sosu;
  int check;

  do {
    printf("Please type in an integer: ");
    scanf("%d", &i);

    if (i <= 1) {
      printf("Please type in an integer greater than 1.\n");
    }

    if (i == 2) {
      printf("2 is a prime number.\n");
    }
    for (int j = 2; j < i; j++) {
      if (i % j == 0) {
        printf("%d is not a prime number.\n", i);
        j = i;
        sosu = 1;
      }
    }
    if (sosu != 1) {
      printf("%d is a prime number.\n", i);
    }
    
    printf("Do you want to continue? (0: no, 1: yes) ");
    scanf("%d", &check);
  } while (check != 0);
}