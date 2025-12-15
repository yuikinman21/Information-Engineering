//AJG23055 牧野唯希
//sort()を使うことで短く作ることが出来たと思う。ifではなく、boolを使ったのも自分的にいいと思った。

#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;

bool isKomachi(int n) {
    string s = to_string(n);
    sort(s.begin(), s.end());
    return s == "123456789";
}

int main(void) {
    for (int i = 1; i <= 99999; ++i) {
        long long square = static_cast<long long>(i) * i;
        if (isKomachi(square) && (square <= 987654321)) {
            cout << "自然数: " << i << ", 小町数: " << square << endl;
        }
    }
    return 0;
}