//AJG23055 牧野唯希

#include <stdio.h>

int main (void) {
  int onigiri = 128;
  int pan = 116;
  int shiharai = 1000;
  int sum;
  int otsuri;

  sum = (onigiri * 2 + pan) * 1.08;
  otsuri = shiharai - sum;

  printf("128円のおにぎり二つと116円のパン1つを購入するのに、1000円支払った時合計は%d円で、おつりは%d円です。(消費税は8%%として計算)\n",sum, otsuri);
}