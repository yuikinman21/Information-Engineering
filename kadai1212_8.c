// AJG23055 牧野唯希
#include <stdio.h>

int main(void) {
  int i;
  char moji[100];

  printf("Please enter a string:");
  scanf("%s", moji);

  for (i = 0; moji[i] != '\0'; i++)
    ;

  printf("The number of characters is %d.\n", i);

  return 0;
}