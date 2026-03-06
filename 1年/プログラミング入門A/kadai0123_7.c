//AJG23055 牧野唯希

#include <stdio.h>
#include <math.h>

struct xy {
float x;
float y;
};

float dist(float x1, float y1, float x2, float y2) {
    float dx = x2 - x1;
    float dy = y2 - y1;
    return sqrt(dx * dx + dy * dy);
}
int main (void) {

  struct xy p1, p2;
  printf("x1=");
  scanf("%f",&p1.x);
  printf("y1=");
  scanf("%f",&p1.y);
  printf("x2=");
  scanf("%f",&p2.x);
  printf("y2=");
  scanf("%f",&p2.y);
  
  float distance = dist(p1.x, p1.y, p2.x, p2.y);
  printf("距離は%fです\n", distance);
  
  return 0;
}