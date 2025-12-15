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
    size = _size;
    array = new int[size]; // 配列のメモリ確保
  }

  ~dyn_mem() { // デストラクタ
    if (size!=0) { // 配列にメモリが確保されている場合のみ，メモリを開放する
      delete [] array;
      size = 0;
    }
  }
};

int main() {
  dyn_mem dm1(3); // オブジェクトの作成(大きさが3の配列のメモリを確保)
  dm1.array[0] = 10;
  dm1.array[1] = 3;
  dm1.array[2] = 8;

  dyn_mem dm2(3); // オブジェクトの作成(大きさが3の配列のメモリを確保)
  dm2 = dm1; // オブジェクト dm1 を dm2 にコピー
  
  for (int i=0; i<dm2.size; i++) { // dm2の配列を表示
    cout << "dm2.array[" << i << "] = " << dm2.array[i] << endl;
  }

  cout << "----------" << endl;

  dm1.array[0] = -1; // dm1 のメンバの値を変更してみる
  cout << "dm1.array[0] = " << dm1.array[0] << endl;
  cout << "dm2.array[0] = " << dm2.array[0] << endl;
  
  return 0;
}
