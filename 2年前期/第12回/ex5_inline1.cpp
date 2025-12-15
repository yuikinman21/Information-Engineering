#include <time.h> // 時間測定用
#include <iostream>
using namespace std;

int tasu(int x, int y) { // 足し算する関数
  return x+y;
}

inline int tasu_inline(int x, int y) { // 足し算する関数(インライン版)
  return x+y;
}

int main() {
  int sum;
  clock_t start, end; // 処理の開始時間と終了時間

  sum=0;
  start = clock(); // 開始時間測定
  for(int i=0; i<214748364; i++) {
    sum = tasu(sum,i);
  }
  end = clock(); // 終了時間測定
  cout << "Computation time without inline: " << end-start << endl;

  sum=0;
  start = clock(); // 開始時間測定
  for(int i=0; i<214748364; i++) {
    sum = tasu_inline(sum,i);
  }
  end = clock(); // 終了時間測定
  cout << "Computation time with inline: " << end-start << endl;

  return 0;
}
