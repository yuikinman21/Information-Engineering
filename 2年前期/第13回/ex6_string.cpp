#include <iostream>
#include <string>	// C++のstringを使うため
#include <string.h>	// Cの文字列操作関数を使うため

using namespace std;

int main() {
  // "" で初期化
  string str1;
  // "abc" で初期化
  string str2 = "abc";
  // "def" で初期化
  string str3("def");

  // str1の変更
  str1 = str3 + "333";

  // 文字列の表示
  cout << "str1 = " << str1 << endl
       << "str2 = " << str2 << endl
       << "str3 = " << str3 << endl;

  // 文字列の長さの表示（C++スタイルとCスタイルの比較）
  cout << "str1.length() = " << str1.length() << endl
       << "strlen(str1.c_str()) = " << strlen(str1.c_str()) << endl;

  return 0;
}
