// 第12回 演習課題(1)
/*
氏名：牧野唯希
学籍番号：AJG23055
*/

#include <iostream>
#include <time.h>
using namespace std;

// 時を表すクラス
class time_hms {
  // write here...
private:
  int hour;
  int min;
  int sec;

public:
  time_hms(int _hour, int _min, int _sec) {
    hour = _hour;
    min = _min;
    sec = _sec;
  }

  int get_hour() { return hour; }

  int get_min() { return min; }

  int get_sec() { return sec; }

  void add(time_hms &obj) {
    hour += obj.hour;
    min += obj.min;
    sec += obj.sec;

    if (sec >= 60) {
      min += sec / 60;
      sec = sec % 60;
    }

    if (min >= 60) {
      hour += min / 60;
      min = min % 60;
    }
  }
};

int main() {
  // write here...
  time_t t = time(NULL);
  struct tm *local = localtime(&t);
  int hour = local->tm_hour;
  int min = local->tm_min;
  int sec = local->tm_sec;
  time_hms time1(hour, min, sec);
  time_hms time2(3, 35, 40);
  cout << "time1: " << time1.get_hour() << ":" << time1.get_min() << ":"
       << time1.get_sec() << endl;
  cout << "time2: " << time2.get_hour() << ":" << time2.get_min() << ":"
       << time2.get_sec() << endl;
  time1.add(time2);
  cout << "time1 (time2 is added): " << time1.get_hour() << ":"
       << time1.get_min() << ":" << time1.get_sec() << endl;

  return 0;
}
