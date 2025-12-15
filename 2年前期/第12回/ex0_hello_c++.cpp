#include <iostream> // Cのstdio.hに相当
using namespace std; // 名前空間stdを使う。とりあえずお約束

int main() {
  cout << "Hello C++!" << endl; // 出力の構文。coutは標準出力

  int n; // 宣言は、使う前ならプログラムのどこにあってもよい
  cout << "n = ";
  cin >> n; // 入力の構文。cinは標準入力
  int s = 0;
  for (int i=1; i<=n; i++) s+=i;
  cout << "sum(1.." << n << ") = " << s << endl;
  return 0;
}
