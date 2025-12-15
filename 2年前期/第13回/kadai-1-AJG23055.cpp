// 第11回 演習課題(1)
/*
氏名：牧野唯希
学籍番号：AJG23055
*/

// ヘッダファイルなどを記述
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

// クラスの定義
class Score {
// write here...
private:
  string name;
  int math;
  int science;
  int english;

public:
  Score() {}
  Score(string _name, int _math, int _science, int _english) {
    name = _name;
    math = _math;
    science = _science;
    english = _english;
  }

  string get_name() {
    return name;
  }
  double get_average() {
    return (math + science + english) / 3.0;
  }

};


int main() {
  
  // ファイルを開く
  // write here...
  ifstream fin("kadai-1_score.txt");
  if (!fin) {
    cout << "Cannot open input file." << endl;
  }


  // データの読み込みとクラスへの登録
  // write here...
  
  Score scores[3];
  for (int i = 0; i < 3; i++) {
    string name;
    int math, science, english;
    fin >> name >> math >> science >> english;
    scores[i] = Score(name, math, science, english);
  }



  // 人毎に平均点の算出と表示
  // The average score of (人名): (点数） で出力する．
    /*
    想定する出力：
    The average score of Suzuki: 70
    The average score of Takeda: 80
    The average score of Yamada: 63.3333
    */
  // write here...
  for (int i = 0; i < 3; i++) {
    cout << "The average score of " << scores[i].get_name() << ": " << scores[i].get_average() << endl;
  }
    
  return 0;
}
