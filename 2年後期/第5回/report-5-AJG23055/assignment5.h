//AJG23055 牧野唯希

#include <string>
using namespace std;

// 量り売りの基本クラス
class base {

protected:
  // 名前
  string name;
  // 重さ当たりの価格 (単価)
  double unit_price;

public:
  // コンストラクタ
  base(string nm, double up) {
    name = nm;
    unit_price = up;
  }
  
  // 名前を返す関数
  string get_name() {
    return name;
  }

  // 値段を返す関数 (純粋仮想関数)
  virtual double get_price(double weight) = 0;

};
