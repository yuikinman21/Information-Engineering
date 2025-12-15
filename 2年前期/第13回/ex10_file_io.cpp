#include <iostream>
#include <fstream>	// ファイル入出力に使う
#include <stdlib.h>	// exitのため

using namespace std;

int main() {
  // 入力ファイルを開く
  ifstream fin("ex10_input.txt");
  // ファイルが開けたかどうかの確認
  if (!fin) {
    cout << "Cannot open input file." << endl;
    exit(0);
  }

  // 出力ファイルを開く(追記モード)
  ofstream fout("ex10_output.txt", ios::app);
  // ファイルが開けたかどうかの確認
  if (!fout) {
    cout << "Cannot open output file." << endl;
    exit(0);
  }

  // 入力ファイルの最後まで順番に値を読み込み、
  // それぞれ10を足して出力ファイルに追記する
  int val;
  while ( !fin.eof() ) {	// ファイルの最後までのループ
    fin >> val;
    fout << val+10 << " ";
  }
  fout << endl;

  return 0;
}
