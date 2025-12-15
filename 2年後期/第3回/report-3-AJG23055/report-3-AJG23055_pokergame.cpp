//AJG23055 牧野唯希

#include "report-3-AJG23055_pokergame.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;

PokerGame::PokerGame(int initialMoney, int maxMoney) : money(initialMoney), maxMoney(maxMoney), deckIndex(0) {
    srand(static_cast<unsigned int>(time(nullptr)));
    shuffle_deck();
}

void PokerGame::shuffle_deck() {
    for (int i = 0; i < 52; ++i) {
        deck[i] = i;
    }
    for (int i = 51; i > 0; --i) {
        int j = rand() % (i + 1);
        int temp = deck[i];
        deck[i] = deck[j];
        deck[j] = temp;
    }
    deckIndex = 0;
}

void PokerGame::draw_cards() {
    for (int i = 0; i < 5; ++i) {
        if (deckIndex >= 52) {
            shuffle_deck();
        }
        int cardIndex = deck[deckIndex++];
        mark[i] = "SHDC"[cardIndex / 13];
        number[i] = cardIndex % 13 + 1;
    }
}

void PokerGame::play_game() {
    while (!is_game_over()) {
        cout << "現在の所持金: " << money << "円" << endl;
        int bet;
        cout << "かけ金を入力してください: ";
        cin >> bet;

        if (bet > money) {
            cout << "所持金を超えるかけ金は設定できません。" << endl;
            continue;
        }

        draw_cards();
        print_cards();
        exchange_cards();
        print_cards();

        int payout = get_payout(bet);
        money += payout - bet;

        cout << "払い戻し: " << payout << "円" << endl;
    }

    if (money >= maxMoney) {
        cout << "おめでとうございます！最大金額に達しました。" << endl;
    } else {
        cout << "所持金がなくなりました。ゲームオーバーです。" << endl;
    }
}

void PokerGame::exchange_cards() {
    for (int i = 0; i < 5; ++i) {
        int choice;
        cout << (i+1) << "番目のカードを交換しますか？ (0: 交換しない，1: 交換する): ";
        cin >> choice;
        if (choice == 1) {
            if (deckIndex >= 52) {
                shuffle_deck();
            }
            int cardIndex = deck[deckIndex++];
            mark[i] = "SHDC"[cardIndex / 13];
            number[i] = cardIndex % 13 + 1;
        }
    }
}

int PokerGame::get_payout(int bet) {
    int result = decision();
    int multiplier = 0;
    switch (result) {
        case 10: multiplier = 250; break; // ロイヤルストレートフラッシュ
        case 9: multiplier = 50; break;   // ストレートフラッシュ
        case 8: multiplier = 25; break;   // フォーカード
        case 7: multiplier = 10; break;   // フルハウス
        case 6: multiplier = 5; break;    // フラッシュ
        case 5: multiplier = 4; break;    // ストレート
        case 4: multiplier = 3; break;    // スリーカード
        case 3: multiplier = 2; break;    // ツーペア
        case 2: multiplier = 6; break;    // Jacks or Better
        case 1: multiplier = 1; break;    // ワンペア
        default: multiplier = 0; break;   // ノーペア
    }
    return bet * multiplier;
}

bool PokerGame::is_game_over() const {
    return money <= 0 || money >= maxMoney;
}