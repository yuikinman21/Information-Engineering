//codespaceにてコンパイル
//AJG23055　牧野唯希
//mapやiteratorなどは今まで使ったことがなかったので、かなり苦労しましたが、何とか完成させることが出来て良かったです。

#include <iostream>
#include <map>
#include <string>

using namespace std;

void add_height(map<string, double>& heights) {
    string name;
    double height;
    cout << "名前を入力してください: ";
    cin >> name;
    cout << "身長を入力してください (cm): ";
    cin >> height;
    heights[name] = height;
    cout << name << "さんの身長 " << height << " cm を追加しました。" << endl;
}

void search_height(const map<string, double>& heights) {
    string name;
    cout << "検索する人の名前を入力してください: ";
    cin >> name;
    
    map<string, double>::const_iterator it = heights.find(name);

    if (it != heights.end()) {
        cout << name << "さんの身長は " << it->second << " cm です。" << endl;
    } else {
        cout << name << "さんの身長データは見つかりませんでした。" << endl;
    }
}

void delete_height(map<string, double>& heights) {
    string name;
    cout << "削除する人の名前を入力してください: ";
    cin >> name;

    map<string, double>::iterator it = heights.find(name);

    if (it != heights.end()) {
        heights.erase(it);
        cout << name << "さんの身長データを削除しました。" << endl;
    } else {
        cout << name << "さんの身長データは見つかりませんでした。" << endl;
    }
}

void average_height(const map<string, double>& heights) {
    if (heights.empty()) {
        cout << "データがありません。" << endl;
        return;
    }

    double sum = 0.0;
    map<string, double>::const_iterator it;
    for (it = heights.begin(); it != heights.end(); ++it) {
        sum += it->second;
    }

    double average = sum / heights.size();
    cout << "平均身長は " << average << " cm です。" << endl;
}

int main() {
    map<string, double> heights;
    int choice;

    while (true) {
        cout << "\n1. 身長を追加\n2. 身長を検索\n3. 身長を削除\n4. 平均身長を計算\n5. 終了\n選択してください: ";
        cin >> choice;

        switch (choice) {
            case 1:
                add_height(heights);
                break;
            case 2:
                search_height(heights);
                break;
            case 3:
                delete_height(heights);
                break;
            case 4:
                average_height(heights);
                break;
            case 5:
                return 0;
            default:
                cout << "無効な選択です。" << endl;
        }
    }

    return 0;
}