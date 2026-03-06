//AJG23055 牧野唯希

#include <stdio.h>
#define ORI 2023

int main (void) {
  int ori[ORI] = {0}; //檻の状態
  int count = 0; //犬のカウント
  int num[ORI]; //檻の番号

  for (int i = 0; i < ORI; i++) {
    num[i] = i + 1;
  }

  for (int t = 1; t <= ORI; t++) {
    if (t == 1) {
      for (int i = 0; i < ORI; i++) {
        ori[i] = 1;
      }
    } else {
      for (int i = 0 ; i < ORI ; i++) {
        if (ori[i] == 0 && t % num[i] == 0) {
          ori[i] = 1;
      } else if (ori[i] == 1 && t % num[i] == 0) {
          ori[i] = 0;
      }
      }
    }
  }

  for (int i = 0; i < ORI; i++) {
    if (ori[i] == 1) {
      count++;
    }
  }
  printf("The number of dogs in the cage is %d.\n", count);
}