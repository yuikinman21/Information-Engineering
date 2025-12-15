//AJG23055 牧野唯希

int main (void) {
  float tall[5] = {158.3, 189.5, 167.2, 177.4, 146.8};
  float sum = 0;
  float ave = 0;
  float bunsan = 0;

  for (int i = 0; i < 5; i++) {
    sum += tall[i];
  }
  ave = sum / 5;

  for (int i = 0; i < 5; i++) {
    bunsan += (tall[i] - ave) * (tall[i] - ave);
  }
  bunsan /= 5;
  printf( "平均：%.1f\n分散：%.1f\n", ave, bunsan);
}