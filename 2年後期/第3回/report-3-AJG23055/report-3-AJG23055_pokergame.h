//AJG23055 牧野唯希

#ifndef REPORT_3_POKERGAME_H
#define REPORT_3_POKERGAME_H

#include "report-3_poker.h"

class PokerGame : public Poker {
private:
    int money;              // 現在の所持金
    int maxMoney;           // 最大設定金額
    int deck[52];           // デッキを表す配列
    int deckIndex;          // 次に引くカードのインデックス

public:
    PokerGame(int initialMoney, int maxMoney);
    void draw_cards();
    void play_game();
    void exchange_cards();
    int get_payout(int bet);
    bool is_game_over() const;
    void shuffle_deck();
};

#endif // REPORT_3_POKERGAME_H