////解析的手法
//int x, y; //物体のx座標とy座標
//int g;
//int t; //経過時間
//int H; //高さ

//void setup (){
//  size(400,400);
//  x = 200;
//  y = 100;
//  g = 10; //重力加速度
//  H = 10;
//  frameRate(10);
//}

//void draw (){
//  background (200);
//  rect(x, y, 30, 30);
//  y = 100 + t * t; 
  
//  t++;
//}

////オイラー法

//int vy;
//int ox, oy;

//void setup() {
//  size(400,400);
//  vy = 0;
//  ox = 200;
//  oy = 100;
//  frameRate (10);
//}

//void draw() {
//  background(200);
//  rect(ox, oy, 30, 30);
//  vy += 2;
//  oy += vy;
//  if (oy > 300 - 30) {
//    oy = 300 - 30;
//  }
//}

////オイラー法

//int vy;
//int ox, oy;

//void setup() {
//  size(400,400);
//  vy = 0;
//  ox = 200;
//  oy = 100;
//  frameRate (10);
//}

//void draw() {
//  background(200);
//  rect(ox, oy, 30, 30);
//  vy += 2;
//  oy += vy;
//  if (oy > 300 - 30) {
//    oy = 300 - 30;
//    vy *= -1;
//  }
//}

////【演習1】オイラー法(0.01秒/フレーム)

//float vy;
//int ox, oy;

//void setup() {
//  size(400,400);
//  vy = 0;
//  ox = 200;
//  oy = 100;
//  frameRate (100);
//}

//void draw() {
//  background(200);
//  rect(ox, oy, 30, 30);
//  vy += 0.2;
//  oy += vy;
//  if (oy > 300 - 30) {
//    oy = 300 - 30;
//    vy *= -1;
//  }
//}

////水平投げ出し運動

//int vx, vy, ox, oy;

//void setup () {
//  size(400,400);
//  vx = 4;
//  vy = 0;
//  ox = oy = 100;
//  frameRate(10);
//}

//void draw () {
//  background (200);
//  rect(ox, oy, 30, 30);
//  vy += 2;
//  oy = oy + vy;
//  if (oy > 300 - 30) {
//    oy = 300 - 30;
//    vy *= -1;
//  }
//  ox += vx;
//}

////【演習2】水平投げ出し運動(壁あり)

//int vx, vy, ox, oy;

//void setup () {
//  size(400,400);
//  vx = 4;
//  vy = 0;
//  ox = oy = 100;
//  frameRate(10);
//}

//void draw () {
//  background (200);
//  rect(ox, oy, 30, 30);
//  vy += 2;
//  oy = oy + vy;
//  if (oy > 300 - 30) {
//    oy = 300 - 30;
//    vy *= -1;
//  }
//  if (ox > 300 - 30) {
//    vx *= -1;
//  } else if (ox < 100) {
//    vx *= -1;
//  }
//  ox += vx;
//}

////円運動

//int f;
//float x, y;

//void setup() {
//  size(400,400);
//  f = 0;
//  x = 300.0;
//  y = 200.0;
//  frameRate(100);
//}

//void draw () {
//  background(200);
//  ellipse(x, y, 30, 30);
//  f++;
//  x = 300 + 100 * cos(0.05 * f);
//  y = 200 + 100 * sin(0.05 * f);
//}

////【演習3】円運動

//int f;
//float x, y;

//void setup() {
//  size(400,400);
//  f = 0;
//  x = 300.0;
//  y = 200.0;
//  frameRate(100);
//}

//void draw () {
//  background(200);
//  line(300,200,x,y);
//  ellipse(x, y, 30, 30);
//  f++;
//  x = 300 + 100 * cos(0.05 * f);
//  y = 200 + 100 * sin(0.05 * f);
//}

////円運動の残像

//int f;
//float[] xx = new float[5];
//float[] yy = new float[5];

//float x, y;

//void setup() {
//  size(400,400);
//  f = 0;
//  for (int i = 0; i < 5; i++) {
//    xx[i] = 300.0;
//    yy[i] = 200.0;
//  }
//  x = 300.0;
//  y = 200.0;
  
//  noStroke();
//  frameRate(100);
//}

//void draw() {
//  background (255);
//  for(int i = 0; i < 5; i++) {
//    fill(250 - 20 * i, 250 - 20 * i, 250 - 20 * i);
//    ellipse(xx[4 - i], yy[4 - i], 30, 30);
//  }
//  fill(0);
//  ellipse(x, y, 30, 30);
//  f++;
//  x = 200 + 100 * cos(0.05 * f);
//  y = 200 + 100 * sin(0.05 * f);
  
//  for (int i = 0; i < 4; i++) {
//    xx[4 - i] = xx[4 - i - 1];
//    yy[4 - i] = yy[4 - i - 1];
//  }
//  xx[0] = x;
//  yy[0] = y;
//}


//【演習4】自由落下

float vy;
int ox, oy;
int [] xx = new int [5];
int [] yy = new int [5];

void setup() {
  size(400,400);
  vy = 0;
  ox = 200;
  oy = 100;
  for (int i = 0; i < 5; i++) {
    xx[i] = 200;
    yy[i] = 100;
  }
  frameRate (100);
  noStroke();
}

void draw() {
  background(200);
  for (int i = 0; i < 5; i++) {
    fill(250 - 20 * i, 250 - 20 * i, 250 - 20 * i);
    rect(xx[4 - i], yy[4 - i], 30, 30);
  }
  fill(255);
  rect(ox, oy, 30, 30);
  vy += 0.2;
  oy += vy;
  if (oy > 300 - 30) {
    oy = 300 - 30;
    vy *= -1;
  }
  for (int i = 0; i < 4; i++) {
    xx[4 - i] = xx[4 - i - 1];
    yy[4 - i] = yy[4 - i - 1];
  }
  xx[0] = ox;
  yy[0] = oy;
}
