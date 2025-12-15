// AJG23055 牧野唯希

#include <stdio.h>
#include <stdlib.h>

#include "kadai15-AJG23055.h" // 課題資料で指定しているヘッダファイルの名前に要修正

void Poker::input_cards() { // 引くカードを入力

  for (int i = 0; i < 5; i++) {
    bool valid_input;
    do {
      valid_input = true;
      printf("%d番目のカードを入力して下さい (マーク, 数字)\n", (i + 1));
      scanf(" %c, %d", &mark[i], &number[i]);

      if (mark[i] != 'S' && mark[i] != 'H' && mark[i] != 'D' && mark[i] != 'C') {
        printf("入力したマークは無効です\n");
        valid_input = false;
      }

      if (number[i] < 1 || number[i] > 13) {
        printf("入力した数字は無効です\n");
        valid_input = false;
      }

      // 重複チェック
      for (int j = 0; j < i; j++) {
        if (mark[i] == mark[j] && number[i] == number[j]) {
          printf("カードが重複しています\n");
          valid_input = false;
        }
      }
    } while (valid_input == false);
  }

  return;
} // void input_cards()

void Poker::print_cards() { // 引いたカードを表示

  for (int i = 0; i < 5; i++) {
    printf("-%d-  ", (i + 1));
  }
  printf("\n");

  for (int i = 0; i < 5; i++) {
    printf("%c", mark[i]);
    printf("%2d  ", number[i]);
  }
  printf("\n");

  return;
} // void print_cards()

int Poker::flush() { // フラッシュ判定 return 1:フラッシュ return
                     // 0:フラッシュでない
  for (int i = 1; i < 5; i++) {
    if (mark[i] != mark[0]) {
      return 0;
    }
  }
  return 1;
}

int Poker::straight() { // ストレート判定 return 1:ストレート retur 0:ストレートでない
    int temp;
    for (int i = 0; i < 5; i++) {
      for (int j = i+1; j < 5; j++) {
        if (number[i] > number[j]) {
            temp = number[i];
            number[i] = number[j];
            number[j] = temp;
        }
      }
    }
    for (int i = 1; i < 5; i++) {
      if (number[i] != number[i-1] + 1) {

        //特殊ケース
        if (number[0] == 1 && number[1] == 10 && number[2] == 11 && number[3] == 12 && number[4] == 13) {
          return 1;
        }
        
        return 0;
      }
    }
    return 1;
}

int Poker::pair() { // 同一数字に関係するハンドを判定
  // return 1:ワンペア 2:ツーペア 3:スリーカード 4:フルハウス 5:フォーカード
  // 0:該当なし

  // 5:フォーカード
  for (int i = 0; i < 2; i++) {
    // 数字がソートされているためnumber[0]またはnumber[4]のみの数字が異なる
    if (number[i] == number[i + 3]) {
      return 5;
    }
  }

  // 4:フルハウス
  // フルハウスに該当する場合，4を返すよう(return 4)プログラムを作成
  if ((number[0] == number[2] && number[3] == number[4]) || (number[0] == number[1] && number[2] == number[4])) {
    return 4;
  }

  // 3:スリーカード
  for (int i = 0; i < 3; i++) {
    if (number[i] == number[i + 2]) {
      return 3;
    }
  }

  // 2:ツーペア
  // ツーペアに該当する場合，2を返すよう(return 2)プログラムを作成
  if (number[0] == number[1] && number[2] == number[3] || number[0] == number[1] && number[3] == number[4] || number[1] == number[2] && number[3] == number[4]) {
    return 2;
  }
  // 1:ワンペア
  // ワンペアに該当する場合，1を返すよう(return 1)プログラムを作成

  for (int i = 0; i < 5; i++) {
    if (number[i] == number[i + 1]) {
      return 1;
    }
  }

  return 0;
} // int pair()

int Poker::new_hand() {

  //新しいハンド:ハンドが全て偶数
  for (int i = 0; i < 5; i++) {
    if (number[i] % 2 == 1) 
      return 0;
  }

  return 1;
}

int Poker::decision() { // ハンドを判定

  int decision1, decision2;

  decision1 = flush();
  decision2 = straight();

  if (decision1 == 1 && decision2 == 1) {
    if (number[0] == 10) { // 左のif文に論理を追加せよ
      printf("ロイヤルストレートフラッシュ\n");
      return 10;

    } else {
      printf("ストレートフラッシュ\n");
      return 9;
    }
  } else if (decision1 == 1) {
    printf("フラッシュ\n");
    return 6;

  } else if (decision2 == 1) {
    printf("ストレート\n");
    return 5;
  }

  decision1 = pair();

  if (decision1 == 5) {
    printf("フォーカード\n");
    return 8;
  } else if (decision1 == 4) {
    printf("フルハウス\n");
    return 7;
  } else if (decision1 == 3) {
    printf("スリーカード\n");
    return 4;
  } else if (decision1 == 2) {
    printf("ツーペア\n");
    return 3;
  } else if (decision1 == 1) {
    printf("ワンペア\n");
    return 1;
  }

  decision1 = new_hand();
  if (decision1 == 1) {
    printf("グース―\n");
    return 11;
  }

  printf("残念でした…\n");

  return 0;
} // int decision()

int main() {

  Poker poker;

  poker.input_cards();

  poker.print_cards();

  int dummy_decision = poker.decision();

  return 0;
}
