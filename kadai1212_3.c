//AJG23055 牧野唯希
#include <stdio.h>

int main (void) {
  printf("Input an Integer:");
  int num;
  scanf("%d",&num);

  if(num%2==0){
    printf("Even number\n");
  } else {
    printf("Odd number\n");
  }

  return 0;
}