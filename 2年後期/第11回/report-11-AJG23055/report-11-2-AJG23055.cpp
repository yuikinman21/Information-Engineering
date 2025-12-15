//AJG23055 牧野唯希
//以下のMakefileを作成した。

// CXX = g++
// CXXFLAGS = -std=c++11 -Wall
// OBJS = report-11-2-AJG23055.o ex2image.o

// report-11-2-AJG23055.exe: $(OBJS)
//   $(CXX) $(CXXFLAGS) -o $@ $^

// %.o: %.cpp
//   $(CXX) $(CXXFLAGS) -c $<

// clean:
//   rm -f $(OBJS) report-11-2-AJG23055.exe


#include "ex2image.h"
#include <cmath>
#include <cstdio>

using namespace std;

int main() {
  ex2image img;
  img.load("block.pgm");

  int width = img.img_width();
  int height = img.img_height();

  // 3x3, 5x5, 7x7フィルタを適用
  for (int w : {3, 5, 7}) {
    ex2image result(width, height, 1);

    for (int y = 0; y < height; y++) {
      for (int x = 0; x < width; x++) {
        int sum = 0;
        int count = 0;
        for (int dy = -w/2; dy <= w/2; dy++) {
          for (int dx = -w/2; dx <= w/2; dx++) {
            int nx = x + dx;
            int ny = y + dy;
            if (nx >= 0 && nx < width && ny >= 0 && ny < height) {
              sum += img(nx, ny, 0);
              count++;
            }
          }
        }
        result(x, y, 0) = sum / count;
      }
    }

    char filename[30];
    sprintf(filename, "average-AJG23055-%d.pgm", w);
    result.write(filename);
  }

  return 0;
}
