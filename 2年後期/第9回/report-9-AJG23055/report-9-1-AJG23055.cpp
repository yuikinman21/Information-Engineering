//codespaceにてコンパイル
//AJG23055　牧野唯希
//vectorをインクルードするプログラムを今まで多数見てきたのですが、使い方が分かっていなかったので、今回知れて良かったです。

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>

using namespace std;

int main() {
    int n;
    cout << "乱数の個数を入力してください（100以上）: ";
    cin >> n;

    if (n < 100) {
        cout << "エラー: 100以上の整数を入力してください。" << endl;
        return 1;
    }

    vector<int> numbers;
    srand(static_cast<unsigned int>(time(0)));

    // 乱数生成
    for (int i = 0; i < n; ++i) {
        numbers.push_back(rand() % 101);
    }

    // 標本平均
    double mean = 0;
    for (int i = 0; i < n; ++i) {
        mean += numbers[i];
    }
    mean /= n;

    // 標本分散
    double variance = 0;
    for (int i = 0; i < n; ++i) {
        variance += pow(numbers[i] - mean, 2);
    }
    variance /= n;

    // 最大値と最小値
    int max = numbers[0];
    int min = numbers[0];
    for (int i = 1; i < n; ++i) {
        if (numbers[i] > max) max = numbers[i];
        if (numbers[i] < min) min = numbers[i];
    }

    // 最頻値
    vector<int> count(101, 0);
    int max_count = 0;
    for (int i = 0; i < n; ++i) {
        count[numbers[i]]++;
        if (count[numbers[i]] > max_count) {
            max_count = count[numbers[i]];
        }
    }
    vector<int> mode;
    for (int i = 0; i <= 100; ++i) {
        if (count[i] == max_count) {
            mode.push_back(i);
        }
    }

    // 中央値
    vector<int> sorted = numbers;
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (sorted[j] > sorted[j + 1]) {
                int temp = sorted[j];
                sorted[j] = sorted[j + 1];
                sorted[j + 1] = temp;
            }
        }
    }
    double median;
    if (n % 2 == 0) {
        median = (sorted[n/2 - 1] + sorted[n/2]) / 2.0;
    } else {
        median = sorted[n/2];
    }

    // 結果の出力
    cout << "標本平均: " << mean << endl;
    cout << "標本分散: " << variance << endl;
    cout << "最大値: " << max << endl;
    cout << "最小値: " << min << endl;
    cout << "最頻値: ";
    for (int i = 0; i < mode.size(); ++i) {
        cout << mode[i] << " ";
    }
    cout << endl;
    cout << "中央値: " << median << endl;

    return 0;
}