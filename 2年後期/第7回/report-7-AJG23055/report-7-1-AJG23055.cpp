//AJG23055 牧野唯希
//最初はクラスという概念がなかなか理解しがたく苦労したが、最近は使えるようになってきた。関係演算子の出力方法をどうしようか少し迷ったが、無難な感じに出力することにした。

#include <iostream>

using namespace std;

class Complex {
  private:
    double real;
    double imag;

  public:
    Complex(double r = 0.0, double i = 0.0) : real(r), imag(i) {}

    Complex operator+(const Complex& other) const {
        return Complex(real + other.real, imag + other.imag);
    }

    Complex operator-(const Complex& other) const {
        return Complex(real - other.real, imag - other.imag);
    }

    Complex operator*(const Complex& other) const {
        return Complex(
          real * other.real - imag * other.imag,
          real * other.imag + imag * other.real
        );
    }
    Complex operator/(const Complex& other) const {
        double denominator = other.real * other.real + other.imag * other.imag;
        return Complex(
          (real * other.real + imag * other.imag) / denominator,
          (imag * other.real - real * other.imag) / denominator
        );
    }

    bool operator == (const Complex& other) const {
        return real == other.real && imag == other.imag;
    }

    void display() const {
        cout << real << " + " << imag << "i" << endl;
    }
};

int main() {
  Complex c1(1.0, 2.0);
  Complex c2(0.3, -8.7);
  Complex c3(1.0, 2.0);

  cout << "c1: ";
  c1.display();
  cout << "c2: ";
  c2.display();
  cout << "c3: ";
  c3.display();
  Complex c4 = c1 + c2;
  cout << "c1 + c2: ";
  c4.display();
  Complex c5 = c1 - c2;
  cout << "c1 - c2: ";
  c5.display();
  Complex c6 = c1 * c2;
  cout << "c1 * c2: ";
  c6.display();
  Complex c7 = c1 / c2;
  cout << "c1 / c2: ";
  c7.display();
  
  cout << "c1 == c3: " << (c1 == c3) << endl;
  cout << "c1 == c2: " << (c1 == c2) << endl;
  
  return 0;

}
