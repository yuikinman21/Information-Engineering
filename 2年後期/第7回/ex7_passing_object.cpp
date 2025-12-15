#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>

using namespace std;

class strtype {

private:
  char *p;

public:
  // コンストラクタ
  strtype(char *s) {
    int l;   
    l = strlen(s); // 文字列の長さを調べて，l に格納
    p = new char[l+1]; // 文字列の長さ分だけchar 型のメモリを確保
   
    if(!p) { // メモリが確保されていなかった場合
      cout << "メモリの割当に失敗しました．プログラムを終了します．\n" << endl;
      exit(1); // プログラムを終了
    }

    strcpy(p, s);
  }

  ~strtype() {delete [] p;} // デストラクタ

  char *get() {return p;} // p が指すメモリ領域のアドレスを返す
};

void show(strtype x) {
  char *s;
  s = x.get();  // オブジェクトx のデータメンバp が指すメモリ領域のアドレスをポインタ変数s に格納
  cout << s << endl;
}
  
int main(void) {
  char a_s[] = "Hello";
  strtype a(a_s);
  show(a);
  show(a); // エラーが起こる

  return 0;
}
