//AJG23055 牧野唯希
//参照を使った書き方の方が楽で分かりやすかったため、今後使っていこうと思った。

#include <iostream>

using namespace std;

void swap(int &a, int &b) {
  int tmp = a;
  a = b;
  b = tmp;
  
}

int main() {
  int a = 1;
  int b = 2;

  cout << "a = " << a << endl;
  cout << "b = " << b << endl;
  
  swap(a,b);
  cout << "swap(a,b)" << endl;

  cout << "a = " << a << endl;
  cout << "b = " << b << endl;

  return 0;
}