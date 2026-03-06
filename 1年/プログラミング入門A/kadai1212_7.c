//AJG23055 牧野唯希
#include <stdio.h>
#include <math.h>

int main (void) {
  int num[10] = {92, 5, 77, 39, 42, 84, 23, 64, 50, 15};
  int sum = 0;
  float ave = 0.0;

  //平均を求める
  for (int i = 0; i < 10; i++) {
    sum += num[i];
  }
    ave = sum / 10.0;
  printf("average=%.1f\n", ave);
  //分散を求める
  float var = 0;
  for (int i = 0; i < 10; i++) {
    var += (num[i] - ave) * (num[i] - ave);
  }
    var = var / 10.0;
  printf("var=%.1f\n", var);
  //標準偏差を求める
  float std = 0.0;
  std = sqrt(var);
  printf("std=%.1f\n", std);
  return 0;
}