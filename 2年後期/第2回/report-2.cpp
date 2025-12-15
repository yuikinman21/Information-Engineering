#include <iostream>
#include <string>

class Account {
protected:
  string name; // 名前
  int balance; // 円残高（単位：円）

public:
  // コンストラクタ  
  Account(string _name, int _balance) {
    name = _name;       // 名前を初期化
    balance = _balance; // 円残高を初期化
  }
  // 名前を調べる
  string get_name() {
    return name;
  }
  // 円残高を調べる
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
