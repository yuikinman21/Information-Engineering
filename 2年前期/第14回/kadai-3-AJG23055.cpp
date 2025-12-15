// 第12回 演習課題(3)
/*
氏名：牧野唯希
学籍番号：AJG23055
*/

#include <cstdlib> // rand関数のため
#include <ctime>
#include <iomanip> //少数表示用
#include <iostream>
using namespace std;

class random_number {
  // write here...
public:
  random_number() { srand(static_cast<unsigned int>(time(nullptr))); }

  double generate() {
    return static_cast<double>(rand()) / RAND_MAX * 2.0 - 1.0;
  }
};

// 2x2の正方形と直径2の円を考える。円の中心は原点とする。
int main() {
  // write here...
  random_number rng;
  int trials;
  cout << "Input the number of trials: ";
  cin >> trials;
  int inside = 0;

  for (int i = 0; i < trials; ++i) {
    double x = rng.generate();
    double y = rng.generate();
    if (x * x + y * y <= 1.0) {
      ++inside;
    }
  }

  double pi_estimate = 4.0 * inside / trials;

  cout << "trial: " << trials << endl;
  cout << "inside = " << inside << endl;
  cout << "A estimate of pi is " << fixed << setprecision(5) << pi_estimate
       << endl;

  return 0;
}
