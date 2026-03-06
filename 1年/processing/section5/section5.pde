
//【発展課題1】迷路の全探索（改良したい版）

int x = 1;
int y = 1;
int count = 0;

int max; //上下左右の中で一番点数が低い方向　上:0　右:1　下:2　左:3
int max2; //上下左右の点数を格納する

int goalX = 6;
int goalY = 5;

color black = color (0);
color white = color (255);
color red = color (255, 0, 0);
color start = color(0, 255, 0);
color goal = color (0, 0, 255);

int [ ][ ] maze = {
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
  {1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1},
  {1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 1},
  {1, 0, 0, 1, 0, 0, 0, 1, 0, 1, 1, 1},
  {1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 1, 1},
  {1, 0, 1, 0, 1, 0, 0, 1, 1, 0, 1, 1},
  {1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1},
  {1, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 1},
  {1, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1},
  {1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 1},
  {1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1},
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};

boolean check = true;

void setup() {
  size (300, 300);
  frameRate(100);
}

void draw() {
  translate(-30, -30);

  //迷路を描画
  for (int i = 0; i < 12; i++) {
    for (int j = 0; j < 12; j++) {
      if ( maze[i][j] == 1) {
        fill(black);
      } else {
        //maze[i][j]が0または2の時に実行
        fill(white);
      }
      rect(30 * j, 30 * i, 30, 30);
    }
  }

  fill(start);
  rect(30, 30, 30, 30);

  fill(goal);
  rect(30 * goalX, 30 * goalY, 30, 30);

  //アニメーションの終了
  if ( x == goalX && goalY == 5) {
    noLoop();
  }

  //初期値の設定
  if (count == 0) {
    fill(red);
    rect (30, 30, 30, 30);
    maze[x][y] = 2;
  }


  //全探索アルゴリズム
  float daze = random(3);

    //上下左右のなかで一番点数が低い方へ進む（ただし1は除く）
    //どの方向が一番点数が低いか考える
  
  max = 0;
  max2 = 0;
    
  //if (maze [y-1][x] != 1) {
  //  max = 0;
  //  max2 = maze [y - 1][x];
  //}
  //if (maze [y][x+1] != 1 && max2 > maze [y][x+1]) {
  //  max = 1;
  //  max2 = maze [y][x+1];
  //}
  //if (maze[y+1][x] != 1 && max2 > maze[y+1][x]) {
  //  max = 2;
  //  max2 = maze[y + 1][x];
  //}
  //if (maze[y][x-1] != 1 && max2 > maze[y][x-1]) {
  //  max = 3;
  //  max2 = maze[y][x-1];
  //}
  
  println(max);
  
  //進める方向に進む
  switch(max) {
    case 0:
    
  }
}
