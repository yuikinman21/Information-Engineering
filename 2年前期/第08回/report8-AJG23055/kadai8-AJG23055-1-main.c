//AJG23055 牧野唯希

#include <stdio.h>

#include "kadai8-AJG23055-1.h"

int main (void) {
  double a, b, result = 0;
  printf("a=");
  scanf("%lf", &a);
  printf("b=");
  scanf("%lf", &b);
  result = add(a, b);
  printf("a+b=%lf\n", result);
  result = sub(a, b);
  printf("a-b=%lf\n", result);
  result = mul(a, b);
  printf("a*b=%lf\n", result);
  result = div(a, b);
  printf("a/b=%lf\n", result);
  
}