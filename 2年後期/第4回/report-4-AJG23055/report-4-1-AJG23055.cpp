//AJG23055 牧野唯希

#include <iostream>
#include <stdio.h>
#include <fstream>
#include <cmath>

using namespace std;

double ALPHA = 0.1;
double x = 2.0;
double eps = 0.0001;
int n = 500;

double f(double x) {
    return x * x + x + 2;
}

double df(double x) {
    return 2 * x + 1;
}

double newton_method(double x0) {
    double x1 = x0 - ALPHA * df(x0);
    int i = 0;
  cout << "f(x) = x*x + x + 2" << endl;
  
    while (abs(x1 - x0) > eps && i <= n) {
      
        printf("%5d: x = %+f   f(x) = %f   grad = %+f\n", i,x1, f(x1), x1-x0);
        x0 = x1;
        x1 = x0 - ALPHA * df(x0);      
        i++;
    }
    return x1;
}

int main() {
    double x0 = 2.0;
    double x1 = newton_method(x0);

    return 0;
}