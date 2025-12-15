//AJG23055 牧野唯希
#include <stdio.h>
#include <string.h>

int main (void) {
  char a[100];
  char b[100];

  printf("Input a first word: ");
  scanf("%s", a);
  printf("Input a second word: ");
  scanf("%s", b);
  if (strcmp(a, b) == 0) {
    printf("\nYou entered the same word twice.\n");
  } else {
    printf("\nYou entered two different words.\n");
  }
  
  return 0;
}