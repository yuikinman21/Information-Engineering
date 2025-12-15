#ifndef KADAI15_H // 1, 2, 31行目は二重インクルードを防ぐ工夫
#define KADAI15_H // 興味があれば「二重インクルード」をインターネット等で調べて下さい

class Poker {

protected:
    char mark[5];  // カードのマーク (S:スペード, H:ハート, D:ダイヤ, C:クラブ)
    int number[5]; // カードの番号 (1, 2, ..., 13)

public:
    // 引くカードを入力
    void input_cards();

    // 引いたカードを表示
    void print_cards();

    // フラッシュ判定
    int flush();

    // ストレート判定
    int straight();

    // 同一数字に関係するハンドを判定
    int pair();

    // ハンドを判定
    int decision();

}; // class Poker

#endif
