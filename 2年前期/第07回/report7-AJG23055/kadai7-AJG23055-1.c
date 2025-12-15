//AJG23055 牧野唯希

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int counter(int i, int check) {
  int static sum = 0;
  if (i == check) {
    sum++;
  }
  return sum;
}

int main (int argc, char *argv[]) {

  char *num_char = argv[1];
  int num = atoi(num_char);

  char *check_char = argv[2];
  int check = atoi(check_char);
  
  if (argc != 3) {
    printf("ERROR!\n");
    return 1;

  } else if (check < 0 || check > 9) {
    printf("ERROR!\n");
    return 1;
    
  } else if (num <= 0) {
    printf("ERROR!\n");
    return 1;
  }

  int a, i, count = 0;
  srand ((unsigned) time (NULL));

  printf ("rand = ");
  for (i = 0; i < num; i++) {
    a = rand() % 10;
    printf ("%d,", a);

    counter(a,check);
  }
  putchar ('\n');

  printf ("The number of %d: %d\n", check, counter(a,check));
  

  return 0;
}