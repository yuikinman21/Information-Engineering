// 演習課題(3)
/*
氏名：牧野唯希
学籍番号：AJG23055
*/

#include <iostream>
using namespace std;

//
// 出力は，以下の形式で完全数のみ表示する．
//
// （完全数と判定した数字） is a perfect number.
// 

// write here...

int perfection(int n) {
  int sum = 0; 
  for (int i = 1; i < n; i++) {
    if (n % i == 0) {
      sum += i;
    }
  }
  if (sum == n) {
    return 1;
  } else {
    return 0;
  }
}

int main() {

  for (int i = 1; i <= 100; i++) {
    if (perfection(i) == 1) {
      cout << i << " is a perfect number." << endl;
    }
  }
  return 0;
}


