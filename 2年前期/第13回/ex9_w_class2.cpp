#include <string>
#include <iostream>
using namespace std;

class Account {
private:
  string name; // 名前
  int balance; // 残高

public:
  // コンストラクタ  
  Account(string _name, int _balance) {
    name = _name; // 名前を初期化
    balance = _balance; // 残高を初期化
  }
  // 名前を調べる
  string get_name() {
    return name;
  }
  // 残高を調べる
  int get_balance() {
    return balance;
  }
  // 預ける
  void deposit(int amnt) {
    balance += amnt;
  }
  // おろす
  void withdraw(int amnt) {
    balance -= amnt;
  }
};

int main() {
  Account suzuki("鈴木龍一", 123000); // 鈴木さんの口座のオブジェクト作成
  Account tanaka("田中恵美", 256000); // 田中さんの口座のオブジェクト作成

  suzuki.deposit(10000); // 鈴木さんの残高を10000円増やす
  tanaka.withdraw(2000); // 田中さんの残高を2000円減らす

  cout << suzuki.get_name() << "様の残高は"
       << suzuki.get_balance() << "円です．" << endl;
  cout << tanaka.get_name() << "様の残高は"
       << tanaka.get_balance() << "円です．" << endl;
  
  return 0;
}
