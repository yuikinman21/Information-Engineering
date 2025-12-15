#include <string>
#include <iostream>
using namespace std;

class Account {
public:
  string name; // 名前
  int balance; // 残高
};

int main() {
  Account *suzukip;
  suzukip = new Account(); // Account型のオブジェクトを作成

  suzukip->name = "鈴木龍一"; // 鈴木さんの名前
  suzukip->balance = 123000; // 鈴木さんの残高
  cout << suzukip->name << "様の残高は" << suzukip->balance << "円です．" << endl;

  delete suzukip; // 確保したメモリの開放
  return 0;
}

