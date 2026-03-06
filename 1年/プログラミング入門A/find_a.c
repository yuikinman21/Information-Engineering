//AJG23055 牧野唯希
#include <stdio.h>

int main (void) {
  char find_a[1000];
  printf("文字列を入力してください\n(半角英数字のみ。スペースは不可):");
  scanf("%s", find_a);

  int count = 0;
  for (int i = 0; find_a[i] != '\0'; i++) {
    if (find_a[i] == 'a') {
      count++;
    }
  }

  printf("文字列に含まれるaの数は%d個\n", count);

  return 0;  
}