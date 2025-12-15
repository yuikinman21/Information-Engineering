//AJG23055 牧野唯希
//C++を使ってコードを書くのが久しぶりで、前期のC++の資料を見たりして思い出しながらコード作成を行った。コンパイルの仕方から思い出して行ったが、最終的には大威を満たすコードを書くことが出来て良かった。

#include <iostream>
#include <string>

using namespace std;

class Account {
protected:
  string name; // 名前
  int balance; // 円残高（単位：円）

public:
  // コンストラクタ  
  Account(string _name, int _balance) {
    name = _name;       // 名前を初期化
    balance = _balance; // 円残高を初期化
  }
  // 名前を調べる
  string get_name() {
    return name;
  }
  // 円残高を調べる
  int get_balance() {
    return balance;
  }
  // 預ける
  void deposit(int amnt) {
    balance += amnt;
  }
  // おろす
  void withdraw(int amnt) {
    balance -= amnt;
  }
};

class AccountFx: public Account {

  public:
  int balance_cent;
  float ex_rate;

    AccountFx(string _name, int _balance, int _balance_cent, float _ex_rate)
    :Account ( _name, _balance) {
      balance_cent = _balance_cent;
      ex_rate = _ex_rate;
    }
    
    void ex_to_cent(int yen) {
      if (yen <= balance) {
          int cent = static_cast<int>(yen / ex_rate);
          balance -= yen;
          balance_cent += cent;
      }
    }
    
    void ex_to_yen(int cent) {
      if (cent <= balance_cent) {
          int yen = static_cast<int>(cent * ex_rate);
          balance_cent -= cent;
          balance += yen;
      }
    }
    
    int get_balance_cent() {
      return balance_cent;
    }
    
    void update_ex_rate(double _ex_rate) {
      ex_rate = _ex_rate;
    }

    float get_ex_rate() {
      return ex_rate;
    }
};

int main()  {
  AccountFx mf("Makino Yuiki", 123123, 0, 0.95);

  cout << "現在のレートは" << mf.get_ex_rate() << "です" << endl;
  cout << "現在の残高は" << mf.get_balance() << "円です" << endl;
  cout << "現在のセント残高は" << mf.get_balance_cent() << "セントです" << endl;
  
  mf.ex_to_cent(10000);
  cout << "\n10000円をセントに換算した" << endl;
  cout << "現在の残高は" << mf.get_balance() << "円です" << endl;
  cout << "現在のセント残高は" << mf.get_balance_cent() << "セントです" << endl;
  
  mf.ex_to_yen(5000);
  cout << "\n5000セントを円に換算した" << endl;
  cout << "現在の残高は" << mf.get_balance() << "円です" << endl;
  cout << "現在のセント残高は" << mf.get_balance_cent() << "セントです" << endl;
  
  mf.update_ex_rate(1.05);
  cout << "\nレートを1.05倍に更新しました" << endl;
  
  
  mf.ex_to_cent(10000);
  cout << "\n10000円をセントに換算した" << endl;
  cout << "現在の残高は" << mf.get_balance() << "円です" << endl;
  cout << "現在のセント残高は" << mf.get_balance_cent() << "セントです" << endl;
  
  mf.ex_to_yen(10000);
  cout << "\n10000セントを円に換算した" << endl;
  cout << "現在の残高は" << mf.get_balance() << "円です" << endl;
  cout << "現在のセント残高は" << mf.get_balance_cent() << "セントです" << endl;
  
  return 0;
}