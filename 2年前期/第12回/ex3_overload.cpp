#include <iostream>
using namespace std;

unsigned int hiku(unsigned int x, unsigned int y) {
  return x-y;
}

int hiku(int x, int y) {
  return x-y;
}


int main() {
  unsigned int a=60;
  unsigned int b=200;

  cout << "In case of unsigned int: " << hiku(a, b) << endl;
  cout << "In case of int: " << hiku((int)a, (int)b) << endl;

  return 0;
}
