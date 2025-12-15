// 演習課題(2)
/*
氏名：牧野唯希
学籍番号：AJG23055
*/

#include <math.h>
#include <iostream>
using namespace std;

#define EPS 1.0e-5 // 終了条件(更新量の閾値)
#define MAX_COUNT 1000 // 終了条件(更新回数)

// ニュートン法の関数の値の計算
double func(double x, double a, double b, double c, double d) {
  // write here...
  return a * x * x * x + b * x * x + c * x + d;
}

// ニュートン法の関数を微分した値の計算
double deriv(double x, double a, double b, double c, double d) {
  // write here...
  return 3 * a * x * x + 2 * b * x + c;
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
    x = x - func(x, a, b, c, d) / deriv(x, a, b, c, d);

    // xの更新量
    // write here...
    diff = fabs(func(x, a, b, c, d));


    // 終了判定
    if (fabs(diff)<EPS || count>MAX_COUNT) {
      // 終了
      break;
    }
    count++;
  }

  // 求まった解を返す
  return x;
}


int main() {
  // 係数の入力
  cout << "Input coefficients a, b and c, and a constant d." << endl;

  // 係数 a, b, c と定数 d の定義
  // write here...
  double a, b, c, d;
  cin >> a >> b >> c >> d;

  // 係数 a, b, c と定数 d のキーボードからの入力
  // write here...
  cout << "a = " << a << ", b = " << b << ", c = " << c << ", d = " << d << endl;


  // 初期値の入力
  cout << "Input an initial value of x: ";
  // write here...
  double x;
  cin >> x;


  // ニュートン法で解を導出する(関数の戻り値は捨てている)
  // write here...
  double ans = solve(x, a, b, c, d);
  cout << "Answer: " << ans << endl;
  
  
  return 0;
}
