#include <string> // stringを使うために必要
#include <iostream> // 入出力に必要
using namespace std; // お約束

int main() {
  string suzuki_name = "鈴木龍一"; // 鈴木さんの名前
  int suzuki_balance = 123000; // 鈴木さんの残高

  string tanaka_name = "田中恵美"; // 田中さんの名前
  int tanaka_balance = 256000; // 田中さんの残高

  suzuki_balance += 10000; // 鈴木さんの残高を10000円増やす
  tanaka_balance -= 2000; // 田中さんの残高を2000円減らす

  cout << suzuki_name << "様の残高は" << suzuki_balance << "円です．" << endl;
  cout << tanaka_name << "様の残高は" << tanaka_balance << "円です．" << endl;
  
  return 0;
}
