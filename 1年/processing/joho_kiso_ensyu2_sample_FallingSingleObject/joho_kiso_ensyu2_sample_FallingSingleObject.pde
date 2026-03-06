int ox; // 障害物の左上端のx座標 (ox: object_x)
int oy; // 障害物の左上端のy座標 (oy: object_y)
int t; // 開始からの時間（フレーム） = 障害物の落下時間

// あとで変更する可能性がある変数はパラメータ化しておくと便利．
int speed = 10; // 落下速度 = フレームレート
int ow = 30; // 障害物の幅
int oh = 30; // 障害物の高さ

void setup() {
  size(300, 300);
  t=0;
  ox=int(random(width-ow)); // windowの幅の中に障害物が入る範囲
  frameRate(speed);
}
void draw() {
  background(200, 200, 200);
  t = t+1;
  oy = speed*t; // 落下速度*開始からの時間 = 時刻tでの障害物の高さ

  // oyの値が障害物の上部の高さと等しいので，windowの高さを超えたらtとoxを初期化する．
  if (oy > height) {
    t = 0;
    ox=int(random(width-ow)); // windowの幅の中に障害物が入る範囲
  }
  rect(ox, oy, ow, oh);
  println(oy);
}
