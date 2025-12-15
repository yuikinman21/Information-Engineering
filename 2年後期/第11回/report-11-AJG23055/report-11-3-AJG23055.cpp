//AJG23055 牧野唯希
//以下のMakefileを作成して実行した。
// CC = g++
// CFLAGS = -std=c++11 -Wall
// OBJS = report-11-3-AJG23055.o ex2image.o

// report-11-3-AJG23055.exe: $(OBJS)
//   $(CC) $(CFLAGS) -o $@ $^

// %.o: %.cpp
//   $(CC) $(CFLAGS) -c $<

// clean:
//   rm -f $(OBJS) report-11-3-AJG23055.exe

#include "ex2image.h"
#include <cmath>

int main() {
  ex2image img;
  img.load("block.pgm");

  int width = img.img_width();
  int height = img.img_height();

  ex2image result(width, height, 1);

  int sobelX[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
  int sobelY[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

  int maxMag = 0;

  for (int y = 1; y < height - 1; y++) {
    for (int x = 1; x < width - 1; x++) {
      int gx = 0, gy = 0;
      for (int dy = -1; dy <= 1; dy++) {
        for (int dx = -1; dx <= 1; dx++) {
          int pixel = img(x + dx, y + dy, 0);
          gx += pixel * sobelX[dy+1][dx+1];
          gy += pixel * sobelY[dy+1][dx+1];
        }
      }
      int mag = std::sqrt(gx*gx + gy*gy);
      result(x, y, 0) = mag;
      if (mag > maxMag) maxMag = mag;
    }
  }

  // 画素値を0-255に正規化
  for (int y = 0; y < height; y++) {
    for (int x = 0; x < width; x++) {
      result(x, y, 0) = result(x, y, 0) * 255 / maxMag;
    }
  }

  result.write("mag-AJG23055.pgm");

  return 0;
}
