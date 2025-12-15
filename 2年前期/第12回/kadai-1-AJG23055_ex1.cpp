// 演習課題(1)
/*
氏名：牧野唯希
学籍番号：AJG23055
*/

#include <iostream>	// coutのため
#include <iomanip>	// setwのため
using namespace std;

int main() {

  // newで2次元配列を確保
  // write here...
  int *n;
  n = new int[81];

  // 九九を計算して、配列に入れる
  // write here...
  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      n[i * 9 + j] = (i + 1) * (j + 1);
    }
  }

  // 1〜9の表示(横軸の表示)
  // write here...
  cout << "  |  1  2  3  4  5  6  7  8  9" << endl;

  // 横線の表示
  // write here...
  cout << "-------------------------------" << endl;


  // 九九本体の表示
  
  /*
  目標とする出力：
    |  1  2  3  4  5  6  7  8  9
  -------------------------------
    1|  1  2  3  4  5  6  7  8  9
    2|  2  4  6  8 10 12 14 16 18
    3|  3  6  9 12 15 18 21 24 27
    4|  4  8 12 16 20 24 28 32 36
    5|  5 10 15 20 25 30 35 40 45
    6|  6 12 18 24 30 36 42 48 54
    7|  7 14 21 28 35 42 49 56 63
    8|  8 16 24 32 40 48 56 64 72
    9|  9 18 27 36 45 54 63 72 81
  */
  
  // write here...
  for (int i = 0; i < 9; i++) {
    cout << setw(2) << i + 1 << "|";
    for (int j = 0; j < 9; j++) {
      cout << setw(3) << n[i * 9 + j];
    }
    cout << endl;
  }
  
  // deleteで2次元配列を解放
  // write here...
  delete [] n;


  return 0;
}
