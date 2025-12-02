// AJG23055 牧野唯希

#include <stdio.h>

int main(void) {
  int a;
  int ans = 10;

  do {
    printf("Please type in an integer (0 ~ 10):");
    scanf("%d", &a);

    if (a < 0 || a >ans) {
      printf("\aError!\n");
      continue;
    }
  
    if (a == ans) {
      printf("Congratulations!\n");
    } else {
      if (a < ans) {
        printf("Greater than %d.\n", a);
      } else {
        printf("Less than %d.\n", a);
      }
    }
  } while (a != ans);
  return 0;
}