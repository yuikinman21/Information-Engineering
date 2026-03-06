//AJG23055 牧野唯希

#include <stdio.h>

int main(void) {

  int x1, x2, y1, y2;

  double PI = 3.141592;
  double area;

  printf("2次元座標平面上での2点の座標(x1,x2),(y1,y2)を入力してください。\n");
  printf("x1:");
  scanf("%d", &x1);
  printf("x2:");
  scanf("%d", &x2);
  printf("y1:");
  scanf("%d", &y1);
  printf("y2:");
  scanf("%d", &y2);
  area = ((y1 - x1) * (y1 - x1) + (y2 - x2) * (y2 - x2)) * PI / 4;
  printf("2点を結ぶ直線を直径とする円の面積は%f\n", area);

  return 0;
}