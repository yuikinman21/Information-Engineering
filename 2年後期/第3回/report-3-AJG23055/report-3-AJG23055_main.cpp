//AJG23055 牧野唯希

#include <iostream>

#include "report-3-AJG23055_pokergame.h"

using namespace std;


int main (void) {
    int initialMoney, maxMoney;

    cout << "最初の所持金を設定してください: ";
    cin >> initialMoney;

    cout << "最大金額を設定してください: ";
    cin >> maxMoney;

    PokerGame game(initialMoney, maxMoney);
    game.play_game();

    

}