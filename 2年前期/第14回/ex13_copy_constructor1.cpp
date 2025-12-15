#include <iostream>
using namespace std;

class test {
public:
  int val;
};

int main() {
  test a; // オブジェクトaを初期化
  a.val = 10; // a.valに10を代入
  cout << "a.val = " << a.val << endl;

  test b = a; // オブジェクトbを，aを代入して初期化
  a.val = 20; // コピー後，a.valに20を代入してみる
  cout << "b.val = " << b.val << endl;

  a.val = 10; // a.valに10を代入
  test c; // オブジェクトcを初期化
  c = a; // cにaを代入
  a.val = 30; // コピー後，a.valに30を代入してみる
  cout << "c.val = " << c.val << endl;

  return 0;
}
