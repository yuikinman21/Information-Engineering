//AJG23055 牧野唯希
#include <stdio.h>

int main (void) {
  printf("Please input your age:");

  int age;

  scanf("%d", &age);

  if(age <= 3) {
    printf("The admission fee is free.\n");
  } else if(age <= 12)  {
    printf("The admission fee is 250 yen.\n");
  } else {
    printf("The admission fee is 400 yen.\n");
  }

  return 0;
}