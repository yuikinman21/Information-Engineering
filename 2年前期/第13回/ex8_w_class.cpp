#include <string>
#include <iostream>
using namespace std;

class Account {
public:
  string name; // 名前
  int balance; // 残高
};

int main() {
  Account suzuki; // 鈴木さんの口座のオブジェクト
  Account tanaka; // 田中さんの口座のオブジェクト

  suzuki.name = "鈴木龍一"; // 鈴木さんの名前
  suzuki.balance = 123000; // 鈴木さんの残高

  tanaka.name = "田中恵美"; // 田中さんの名前
  tanaka.balance = 256000; // 田中さんの残高

  suzuki.balance += 10000; // 鈴木さんの残高を10000円増やす
  tanaka.balance -= 2000; // 田中さんの残高を2000円減らす

  cout << suzuki.name << "様の残高は" << suzuki.balance << "円です．" << endl;
  cout << tanaka.name << "様の残高は" << tanaka.balance << "円です．" << endl;
  
  return 0;
}
