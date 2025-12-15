//AJG23055 牧野唯希

#include <stdio.h>

int main (void) {
  int ticket;
  printf("おつりを計算します\n");
  printf("入金は1000円です\n");
  do {
    printf("購入した券の金額を入力してください(10円単位): ");
    scanf("%d", &ticket);
  
    if (ticket % 10 != 0) {
      printf("10円単位で入力してください\n");
    }
    if (ticket > 1000) {
      printf("1000円以下で入力してください\n");
    }
  } while (ticket % 10 != 0 || ticket > 1000);

  int change = 1000 - ticket;
  int coin500 = change / 500;
  change = change % 500;
  int coin100 = change / 100;
  change = change % 100;
  int coin50 = change / 50;
  change = change % 50;
  int coin10 = change / 10;
  change = change % 10;
  
  printf("おつりは以下のようになります\n");
  printf("500円玉: %d枚\n", coin500);
  printf("100円玉: %d枚\n", coin100);
  printf("50円玉: %d枚\n", coin50);
  printf("10円玉: %d枚\n", coin10);

  return 0;
}