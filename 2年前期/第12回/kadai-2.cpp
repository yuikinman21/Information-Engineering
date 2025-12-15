// 演習課題(2)
/*
氏名：
学籍番号：
*/

#include <math.h>
#include <iostream>
using namespace std;

#define EPS 1.0e-5 // 終了条件(更新量の閾値)
#define MAX_COUNT 1000 // 終了条件(更新回数)

// ニュートン法の関数の値の計算
double func(double x, double a, double b, double c, double d) {
  // write here...

}

// ニュートン法の関数を微分した値の計算
double deriv(double x, double a, double b, double c, double d) {
  // write here...

}

// ニュートン法で解を導出する
double solve(double x, double a, double b, double c, double d) {
  // 演算の繰り返し回数のカウント
  int count = 0;
  // 更新量
  double diff;

  while (1) { // 無限ループ
    cout << count << ": x = " << x << endl;
    // ニュートン法の更新式
    // write here...



    // xの更新量
    // write here...





    // 終了判定
    if (fabs(diff)<EPS || count>MAX_COUNT) {
      // 終了
      break;
    }
  }

  // 求まった解を返す
  return x;
}


int main() {
  // 係数の入力
  cout << "Input coefficients a, b and c, and a constant d." << endl;

  // 係数 a, b, c と定数 d の定義
  // write here...


  // 係数 a, b, c と定数 d のキーボードからの入力
  // write here...



  // 初期値の入力
  cout << "Input an initial value of x: ";
  // write here...



  // ニュートン法で解を導出する(関数の戻り値は捨てている)
  // write here...

  
  
  return 0;
}
