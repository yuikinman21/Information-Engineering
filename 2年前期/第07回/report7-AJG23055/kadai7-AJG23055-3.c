//AJG23055 牧野唯希

#include <stdio.h>
#include <string.h>

void bubble_sort (char a [][256], int n) {
  int i, j;
  char tmp[256];
  for (i = 0; i < n - 1; i++) {
    for (j = 0; j < n - 1 - i; j++) {
      if (strcmp(a[j], a[j + 1]) > 0) {
        strcpy(tmp, a[j]);
        strcpy(a[j], a[j + 1]);
        strcpy(a[j + 1], tmp);

        #ifdef DEBUG

        printf("replace: %s -> %s\n", a[j], a[j + 1]);
        for (int k = 0; k < n; k++) {
          printf("%s ", a[k]);
        }
        putchar('\n');
        putchar('\n');
        #endif
        
      }
    }
  }
}

int main (void) {
  char str[][256] = {"love", "lovely", "like", "link", "list"};
  int i;

  puts("Before:");
  for (int i = 0; i < 5; i++) {
    
    printf("%s ", str[i]);
  }
  printf("\n");
  printf("\n");
  int n = 5;

  bubble_sort(str, n);

  puts("After:");
  for (i = 0; i < n; i++) {
    printf("%s ", str[i]);
  }
  putchar('\n');
  return 0;
}