//AJG23055 牧野唯希

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main (void) {
  printf ("Number of stones:");
  int stone;
  scanf ("%d", &stone);
  int n;

  printf ("Game Start!!!\n");

  do {
      printf ("\n<<Your turn>>\n");
      printf ("Number of stones: %d\n", stone);
      do {
        printf ("How many stones do you take?(1~3):");
        scanf ("%d", &n);
        if (n < 1 || n > 3) {
          printf ("You can take 1~3 stones!\n");
        }
      } while (n < 1 || n > 3);
    stone = stone - n;
    printf("Number of stones: %d\n", stone);
    if (stone <= 0) {
      printf ("You lose.\n");
    } else {
      printf("\n<<Computer's turn>>\n");
      srand ((unsigned int) time (NULL));
      n =  (rand() % 3) + 1;
      if (n > stone) {
        n = stone;
      }
      printf ("computer take %d stones.\n", n);
      stone = stone - n;
      if (stone == 0) {
        printf("You win!\n");
      }
    }
  } while (stone > 0);

  return 0;
}