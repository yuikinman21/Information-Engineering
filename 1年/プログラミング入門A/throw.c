//AJG23055 牧野唯希

#include <stdio.h>
#include <math.h>

int main (void) {
  
  float V, A; //初速度V[m/s], 角度A[deg]
  float g = 9.8;
  float pi = 3.141592;
  float L;

  printf("初速度V[m/s]を入力してください:");
  scanf("%f", &V);
  printf("角度A[deg]を入力してください:");
  scanf("%f", &A);

  L = V*V*sin(2*A*pi/180)/g;

  printf("初速V=%f[m/s], 角度A=%f[deg]のとき、ボールが落下する地点までの距離L[m]]は%f[m]です。\n", V, A, L);

  return 0;
}