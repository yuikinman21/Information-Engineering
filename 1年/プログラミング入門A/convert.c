//AJG23055 牧野唯希
#include <stdio.h>

int main (void) {

  char str[32];
  char *pt = str;

  printf("Input a word:");
  scanf("%s", str);

  for (int i = 0; i < 32; i++) {
    if ('A' <= *(pt + i) && *(pt + i) <= 'Z') {
      *(pt + i) = *(pt + i) + 32;
    
    } else if ('a' <= *(pt + i) && *(pt + i) <= 'z') {
      *(pt + i) = *(pt + i) - 32;
    }
  }
  
  printf("%s\n",str);

  return 0;
}