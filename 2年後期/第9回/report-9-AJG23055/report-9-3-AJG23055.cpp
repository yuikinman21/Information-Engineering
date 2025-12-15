//codespaceにてコンパイル
//AJG23055　牧野唯希
//vectorをうまく使って平均値を求められたと思います。最も近い値を求めるところがかなり難しかったですが、何とか完成させることが出来てよかったです。

#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int main() {
    vector<int> numbers;
    int input;
    int count = 0;

    cout << "整数を入力してください（0で終了）：" << endl;

    while (true) {
        cout << ++count << "番目の数字を入力してください: ";
        cin >> input;
        if (input == 0) break;
        numbers.push_back(input);
    }

    if (numbers.empty()) {
        cout << "数字が入力されませんでした。" << endl;
        return 0;
    }

    // 平均値の計算
    double sum = 0;
    for (int num : numbers) {
        sum += num;
    }
    double average = sum / numbers.size();

    cout << "入力された数字の平均は" << average << "です" << endl;

    // 平均値に最も近い値を探す
    double min_diff = abs(numbers[0] - average);
    vector<int> closest_indices = {1};

    for (int i = 1; i < numbers.size(); ++i) {
        double diff = abs(numbers[i] - average);
        if (diff < min_diff) {
            min_diff = diff;
            closest_indices.clear();
            closest_indices.push_back(i + 1);
        } else if (diff == min_diff) {
            closest_indices.push_back(i + 1);
        }
    }

    cout << "これは、";
    for (int i = 0; i < closest_indices.size(); ++i) {
        cout << closest_indices[i];
        if (i < closest_indices.size() - 1) {
            cout << ", ";
        }
    }
    cout << "番目に入力された値に最も近いです" << endl;

    return 0;
}