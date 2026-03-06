//AJG23055 牧野唯希

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
  int y = atof(argv[1]), m = atof(argv[2]), d = atof(argv[3]), w;
  char *a[7] = { "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

  if (m < 3) {
    y--;
    m += 12;
  }
  
  w = (y + y / 4 - y / 100 + y / 400 + (13 * m + 8) / 5 + d) % 7;
  printf("%s\n", a[w]);
  
  return 0;
}