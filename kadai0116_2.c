//AJG23055 牧野唯希

#include <stdio.h>
#include <stdlib.h>

int fibonacci(int n) {
  int m = 0;
  if (n == 0) {
    return 0;
  } else if (n == 1) {
    return 1;
  }
  m = fibonacci(n - 1) + fibonacci(n - 2);
  return m;

}

int main (int argc, char **argv) {
  int n = atof (argv[1]);

  for (int i = 0; i <= n; i++) {
    printf ("F%d = %d\n",i, fibonacci(i));
  }
  return 0;
}
