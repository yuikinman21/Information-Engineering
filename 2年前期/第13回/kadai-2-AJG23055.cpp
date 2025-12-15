// 第11回 演習課題(2)
/*
氏名：牧野唯希
学籍番号：AJG23055
*/

// ヘッダファイルなどを記述
#include <string>
#include <iostream>
using namespace std;


// クラスの定義
class Point { // 座標を扱うクラス
// write here...
private:
  int x;
  int y;
public:
  Point(int _x, int _y) {
    x = _x;
    y = _y;
  }
  void show() {
    cout << "Current position: (" << x << ", " << y << ")" << endl;
  }

  void moveUp() {
    y++;
  }

  void moveDown() {
    y--;
  }

  void moveLeft() {
    x--;
  }

  void moveRight() {
    x++;
  }
};

int main() {
  // write here...
  Point p(0, 0);

  string command;
  p.show();
  while (true) {
      cout << "Enter a command (up, down, left, right, show or quit): ";
      cin >> command;

      if (command == "up") {
          p.moveUp();
      } else if (command == "down") {
          p.moveDown();
      } else if (command == "left") {
          p.moveLeft();
      } else if (command == "right") {
          p.moveRight();
      } else if (command == "show") {
          p.show();
      } else if (command == "quit") {
          cout << "Quit program." << endl;
          break;
      } else {
          cout << "Invalid command." << endl;
      }
  }
  
  return 0;
}
