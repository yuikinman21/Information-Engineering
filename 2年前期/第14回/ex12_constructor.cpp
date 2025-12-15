#include <iostream>
using namespace std;

// オブジェクト作成時に動的にメモリを確保し，破棄時にメモリを開放するクラス
class dyn_mem {
public:
  int *array; // 配列用のポインタ
  int size; // 配列の大きさ

  dyn_mem() { // デフォルトコンストラクタ
    size = 0; // 配列のサイズが指定されないときは，配列のメモリを確保しない
              // 確保していない配列のメモリ開放を避けるために，sizeを0にしておく
  }

  dyn_mem(int _size) { // コンストラクタ
    cout << "Constructor is called." << endl;
    size = _size;
    cout << "Memory is allocated." << endl;
    array = new int[size]; // 配列のメモリ確保
  }

  ~dyn_mem() { // デストラクタ
    cout << "Destructor is called." << endl;
    if (size!=0) { // 配列にメモリが確保されている場合のみ，メモリを開放する
      cout << "Memory is released." << endl;
      delete [] array;
      size = 0;
    }
  }
};

int main() {

  {
    cout << "--A--" << endl;
    dyn_mem dm(10); // オブジェクトの作成(大きさが10の配列のメモリを確保)
    cout << "--B--" << endl;
  }
  cout << "--C--" << endl;
  
  return 0;
}
