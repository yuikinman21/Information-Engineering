// 第12回 演習課題(2)の解
/*
氏名：牧野唯希
学籍番号：AJG23055
*/

#include <iomanip>  // setwのため
#include <iostream> // coutのため
using namespace std;

class kuku_array {
  // write here...
public:
  int **array;
  int size;

  kuku_array() {
    size = 0;
    array = nullptr;
  }

  kuku_array(int _size) {
    size = _size;
    array = new int *[size];
    for (int i = 0; i < size; i++) {
      array[i] = new int[size];
    }
  }

  ~kuku_array() {
    for (int i = 0; i < size; i++) {
      delete[] array[i];
    }
  }

  void kuku_array_print() {
    cout << "  |  1  2  3  4  5  6  7  8  9" << endl;
    cout << "-------------------------------" << endl;

    for (int i = 0; i < size; i++) {
      cout << setw(2) << i + 1 << "|";
      for (int j = 0; j < size; j++) {
        cout << setw(3) << array[i][j];
      }
      cout << endl;
    }
  }
};

int main() {

  // 九九オブジェクトobj1の生成
  // write here...
  kuku_array obj1(9);

  // 九九を計算して、obj1の配列に入れる
  // write here...
  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      obj1.array[i][j] = (i + 1) * (j + 1);
    }
  }

  // 九九オブジェクトobj2にobj1の中身をコピーする
  // write here...
  kuku_array obj2(9);
  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      obj2.array[i][j] = obj1.array[i][j];
    }
  }

  // obj2に保持されている九九を表示する
  // write here...
  obj2.kuku_array_print();

  return 0;
}
