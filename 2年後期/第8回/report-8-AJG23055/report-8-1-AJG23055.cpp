// AJG23055 牧野唯希
//演算子のオーバーロードについては大体どんなことをしているかは理解できた。フレンド関数については期間内に精一杯取り組んだが完全にはわからなかったので、もう少し勉強しようと思う。

#include <iostream>
#include <string>

using namespace std;

class frac {
private:
  int num; // 分子
  int den; // 分母

  int gcd(int a, int b) {
    if (b == 0) {
      return a;
    }
    return gcd(b, a % b);
  }

  void normalize() {
    if (den < 0) {
      num = -num;
      den = -den;
    }
    int g = gcd(abs(num), abs(den));
    num /= g;
    den /= g;
  }

public:
  frac(int n = 0, int d = 1) {
    if (d == 0) {
      cout << "エラー: 分母は0に出来ません！" << endl;
    }
    num = n;
    den = d;
    normalize();
  }

  frac operator+(const frac &other) const {
    return frac(num * other.den + other.num * den, den * other.den);
  }

  frac operator+(int n) const {
    return *this + frac(n);
  }

  friend frac operator+(int n, const frac &f){
    return f + n;
  }

  frac operator*(const frac &other) const {
    return frac(num * other.num, den * other.den);
  }

  frac operator*(int n) const {
    return frac(num * n, den);
  }

  friend frac operator*(int n, const frac &f) {
    return f * n;
  }

  bool operator==(const frac &other) const {
    return num * other.den == other.num * den;
  }

  friend ostream &operator<<(ostream &os, const frac &f) {
    if (f.den == 1) {
      os << f.num;
    } else if (f.num < 0) {
      os << "-" << abs(f.num) << "/" << f.den;
    } else {
      os << f.num << "/" << f.den;
    }
    return os;
  }
};

int main(void) {
    int num1, den1, num2, den2;

    cout << "1つ目の分数を入力してください" << endl;
    cout << "分子を入力: ";
    cin >> num1;
    cout << "分母を入力: ";
    cin >> den1;

    cout << "2つ目の分数を入力してください" << endl;
    cout << "分子を入力: ";
    cin >> num2;
    cout << "分母を入力: ";
    cin >> den2;

    frac f1(num1, den1);
    frac f2(num2, den2);

    cout << "\n計算結果:" << endl;
    cout << "f1 = " << f1 << endl;
    cout << "f2 = " << f2 << endl;
    cout << "f1 + f2 = " << f1 + f2 << endl;
    cout << "f1 * f2 = " << f1 * f2 << endl;
    cout << "f1 + 2 = " << f1 + 2 << endl;
    cout << "2 * f1 = " << 2 * f1 << endl;
    cout << "f1 == f2: " << (f1 == f2) << endl;

    return 0;
}