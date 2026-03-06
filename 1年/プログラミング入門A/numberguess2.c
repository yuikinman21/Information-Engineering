//AJG23055 牧野唯希

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main (void) {
  int a;
  int count = 0;
  srand((unsigned int)time(NULL));
  int ans = (rand() % 10 + 1);

  do {
    printf("Please type in an integer (0 ~ 10):");
    scanf("%d", &a);

    if (a < 0 || a >10) {
      printf("\aError!\n");
      count++;
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
    count++;
  } while (a != ans);
  printf("Number of trials: %d\n", count);
  return 0;
  
}