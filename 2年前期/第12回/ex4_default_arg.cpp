#include <iostream>
#include <math.h> // πを使うため
using namespace std;

double sph_vol(double r=1.0) { // 球の体積
  return 4.0 / 3.0 * M_PI * r * r * r;
}

int main() {
  cout << "With argument (r=2.0): " << sph_vol(2.0) << endl;
  cout << "With argument (r=1.0): " << sph_vol(1.0) << endl;
  cout << "Without argument: " << sph_vol() << endl;

  return 0;
}
