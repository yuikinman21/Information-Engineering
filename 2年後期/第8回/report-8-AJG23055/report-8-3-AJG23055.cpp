//AJG23055 牧野唯希
//

#include <iostream>
#include <string>

using namespace std;

class NumberGame {
  private:
    string answer;

    bool isValidNumber(const string& num) {
        if (num.length() != 4) return false;

        for (int i = 0; i < 4; ++i) {
            if (!isdigit(num[i])) return false;
        }

        for (int i = 0; i < 3; ++i) {
            for (int j = i + 1; j < 4; ++j) {
                if (num[i] == num[j]) return false;
            }
        }

        return true;
    }

    void getHitAndBlow(const string& guess, int& hit, int& blow) {
        hit = 0;
        blow = 0;
        for (int i = 0; i < 4; i++) {
            if (guess[i] == answer[i]) {
                hit++;
            } else {
                for (int j = 0; j < 4; j++) {
                    if (guess[i] == answer[j]) {
                        blow++;
                        break;
                    }
                }
            }
        }
    }

  public:
    NumberGame() : answer("1234") {}  // 正解は1234

    void play() {
        string guess;
        int hit, blow;

        cout << "4桁の数字を当ててください。\n";

        while (true) {
            cout << "予想する数字を入力してください: ";
            cin >> guess;

            if (!isValidNumber(guess)) {
                cout << "無効な入力です。4桁の重複しない数字を入力してください。\n";
                continue;
            }

            getHitAndBlow(guess, hit, blow);

            if (hit == 4) {
                cout << "正解です\n";
                break;
            } else {
                cout << "ヒット数 = " << hit << " ブロー数 = " << blow << "\n";
            }
        }
    }
};

int main() {
    NumberGame game;
    game.play();
    return 0;
}
