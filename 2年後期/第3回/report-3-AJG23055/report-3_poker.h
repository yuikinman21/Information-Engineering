//AJG23055 牧野唯希

class Poker {

protected:
  char mark[5];  // カードのマーク (S:スペード, H:ハート, D:ダイヤ, C:クラブ)
  int number[5]; // カードの番号 (1, 2, ..., 13)

public:
  Poker(); // コンストラクタ
    
  void input_cards(); // 引くカードを入力

  void print_cards(); // 引いたカードを表示

  int flush(); // フラッシュ判定 return 1:フラッシュ return 0:フラッシュでない

  int straight(); // ストレート判定 return 1:ストレート return 0:ストレートでない

  int pair(); // 同一数字に関係するハンドを判定
    // return 1:ワンペア 2:ツーペア 3:スリーカード 4:フルハウス 5:フォーカード 0:該当なし

  int decision(); // ハンドを判定

}; // class Poker
