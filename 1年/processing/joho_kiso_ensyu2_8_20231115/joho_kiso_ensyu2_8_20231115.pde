
//======================
//1個ずつの障害物退避ゲーム
//======================
int ox; // 障害物の左上端のx座標 (ox: object_x)
int oy; // 障害物の左上端のy座標 (oy: object_y)
int cx; // 車の左上端のx座標 (cx: car_x)
int t; // 開始からの時間（フレーム） = 障害物の落下時間
int T; // 開始からの時間（フレーム）（開始からの時間をリセットせずにカウント）
float sec; // 開始からの時間（秒）

// あとで変更する可能性がある変数はパラメータ化しておくと便利．
int speed = 10; // 落下速度 = フレームレート
int ow = 30; // 障害物の幅
int oh = 30; // 障害物の高さ
int cw = 30; // 車の幅
int ch = 30; // 車の高さ

void setup() {
  size(300, 300);
  t=0;
  T=0;
  sec=0;
  ox=int(random(width-ow)); // windowの幅の中に障害物が入る範囲
  frameRate(speed);
}

void draw() {
  background(200, 200, 200);
  t = t+1;
  T = T+1;
  oy = speed*t; // 落下速度*開始からの時間 = 時刻tでの障害物の高さ．

  // 障害物の描画
  if (oy > height) { // oyの値が障害物の上部の高さと等しいので，windowの高さを超えたらtとoxを初期化する．
    t = 0;
    ox=int(random(width-ow)); // windowの幅の中に障害物が入る範囲
  }
  fill(255, 255, 255);
  rect(ox, oy, ow, oh); // 障害物の描画を実行

  // 車の描画
  cx = mouseX; // マウスポインタのx座標の取得
  if ((cx+cw) > width) { // 車の右端（px+pw）の座標がウィンドウの幅（width）よりも大きければ車の幅（cw）だけ左に戻す．
    cx = width - cw;
  }
  fill(255, 255, 255);
  rect(cx, width-ch, cw, ch); // 車の描画を実行

  // 衝突判定
  // x軸方向の条件: (ox < cx+cw && ox+ow > cx)
  // y軸方向の条件: (oy+oh > height-ch && oy < height)
  if ((ox < cx+cw && ox+ow > cx)&&(oy+oh > height-ch && oy < height)) { // 衝突した場合
    // 衝突した物体の初期化
    t = 0;
    oy = 0;
    ox=int(random(width-ow)); // windowの幅の中に障害物が入る範囲

    fill(255, 0, 0);
    T = 0;
  } else { // 衝突しない場合
    fill(0, 192, 0);
  }
  rect(cx, width-ch, cw, ch); // 衝突判定後にもう一度車の描画を実行（衝突している場合は色が変わる）

  // ゲームのプレイ時間の描画
  textSize(20);
  fill(0, 0, 0);
  sec = (float)T/speed; // フレームレートから秒への変換．フレームレート = 1秒間の描画回数．
  text("Time: "+sec+" [sec]", 0, 20);
}



//========================================
//1個ずつの障害物退避ゲーム（ハイスコア表示を追加）
//========================================
//int ox; // 障害物の左上端のx座標 (ox: object_x)
//int oy; // 障害物の左上端のy座標 (oy: object_y)
//int cx; // 車の左上端のx座標 (cx: car_x)
//int t; // 開始からの時間（フレーム） = 障害物の落下時間
//int T; // 開始からの時間（フレーム）（開始からの時間をリセットせずにカウント）
//float sec; // 開始からの時間（秒）

//// あとで変更する可能性がある変数はパラメータ化しておくと便利．
//int speed = 10; // 落下速度 = フレームレート
//int ow = 30; // 障害物の幅
//int oh = 30; // 障害物の高さ
//int cw = 30; // 車の幅
//int ch = 30; // 車の高さ

//void setup() {
//  size(300, 300);
//  t=0;
//  T=0;
//  sec=0;
//  ox=int(random(width-ow)); // windowの幅の中に障害物が入る範囲
//  frameRate(speed);
//}

//void draw() {
//  background(200, 200, 200);
//  t = t+1;
//  T = T+1;
//  oy = speed*t; // 落下速度*開始からの時間 = 時刻tでの障害物の高さ．

//  // 障害物の描画
//  if (oy > height) { // oyの値が障害物の上部の高さと等しいので，windowの高さを超えたらtとoxを初期化する．
//    t = 0;
//    ox=int(random(width-ow)); // windowの幅の中に障害物が入る範囲
//  }
//  fill(255, 255, 255);
//  rect(ox, oy, ow, oh); // 障害物の描画を実行

//  // 車の描画
//  cx = mouseX; // マウスポインタのx座標の取得
//  if ((cx+cw) > width) { // 車の右端（px+pw）の座標がウィンドウの幅（width）よりも大きければ車の幅（cw）だけ左に戻す．
//    cx = width - cw;
//  }
//  fill(255, 255, 255);
//  rect(cx, width-ch, cw, ch); // 車の描画を実行

//  // 衝突判定
//  // x軸方向の条件: (ox < cx+cw && ox+ow > cx)
//  // y軸方向の条件: (oy+oh > height-ch && oy < height)
//  if ((ox < cx+cw && ox+ow > cx)&&(oy+oh > height-ch && oy < height)) { // 衝突した場合
//    // 衝突した物体の初期化
//    t = 0;
//    oy = 0;
//    ox=int(random(width-ow)); // windowの幅の中に障害物が入る範囲

//    fill(255, 0, 0);
//    T = 0;
//  } else { // 衝突しない場合
//    fill(0, 192, 0);
//  }
//  rect(cx, width-ch, cw, ch); // 衝突判定後にもう一度車の描画を実行（衝突している場合は色が変わる）

//  // ゲームのプレイ時間の描画
//  textSize(20);
//  fill(0, 0, 0);
//  sec = (float)T/speed; // フレームレートから秒への変換．フレームレート = 1秒間の描画回数．
//  text("Time: "+sec+" [sec]", 0, 20);
//}



//============================================================================================
// 配列の基礎：1次元配列
//============================================================================================
////これまでの1変数の定義のしかた
//int a = 1;
//println(a);

////1次元配列の定義のしかた
//int[] array = new int[5];
////配列の要素の定義
//array[0] = 2;
//array[1] = 4;
//array[2] = 6;
//array[3] = 8;
//array[4] = 10;

////配列の使用
//int ans = array[0] + array[4];
//println(ans);

////配列の宣言と要素の定義は同時に可能
//int[] array1 = {2, 4, 6, 8, 10};

////for文を使った要素の定義
//int[] array2 = new int[5]; //まず配列を宣言
//for(int i=0; i<5; i++){
//  array2[i] = 2 * i;
//}

//============================================================================================
// 配列の基礎：2次元配列
//============================================================================================
////2次元配列の定義のしかた
//int[][] matrix = new int[2][4];
////配列の要素の定義
//matrix[0][0] = 1;
//matrix[0][1] = 2;
//matrix[0][2] = 3;
//matrix[0][3] = 4;
//matrix[1][0] = 5;
//matrix[1][1] = 6;
//matrix[1][2] = 7;
//matrix[1][3] = 8;

////配列の使用
////int a = matrix[0] + matrix[4];
//println(matrix[0][0]);

////配列の宣言と要素の定義は同時に可能
//int[][] matrix1 = {{1, 2, 3, 4},
//                   {5, 6, 7, 8}};

////for文を使った要素の定義
//int[][] matrix2 = new int[2][4]; //まず配列を宣言
//for(int m=0; m<2; m++){
//  for(int n=0; n<4; n++){
//    matrix2[m][n] = (m+1) * (n+1);
//}



//============================================================================================
// 配列の基礎：複数の障害物を落下させる（配列を利用しないコード）
//============================================================================================
//int ox1; // 1個目
//int oy1;
//int t1;
//int ox2; // 2個目
//int oy2; 
//int t2;
//int ox3; // 3個目
//int oy3;
//int t3;

//// 今回は，これらの値はすべての物体で共通にする
//int speed = 10; // 落下速度 = フレームレート
//int ow = 30; // 障害物の幅
//int oh = 30; // 障害物の高さ

//void setup() {
//  size(300, 300);
//  t1=0; // 1個目
//  ox1=int(random(width-ow));
//  t2=0; // 2個目
//  ox2=int(random(width-ow));
//  t3=0; // 3個目
//  ox3=int(random(width-ow));
//  frameRate(speed);
//}

//void draw() {
//  background(200, 200, 200);
//  t1 = t1+1; // 1個目
//  oy1 = speed*t1;
//  t2 = t2+1; // 2個目
//  oy2 = speed*t2;
//  t3 = t3+1; // 3個目
//  oy3 = speed*t3;

//  // 1個目
//  if (oy1 > height) {
//    t1 = 0;
//    ox1=int(random(width-ow));
//  }
//  rect(ox1, oy1, ow, oh);
//  println(oy1);
  
//  // 2個目
//  if (oy2 > height) {
//    t2 = 0;
//    ox2=int(random(width-ow));
//  }
//  rect(ox2, oy2, ow, oh);
//  println(oy2);
  
//  // 3個目
//  if (oy3 > height) {
//    t3 = 0;
//    ox3=int(random(width-ow));
//  }
//  rect(ox3, oy3, ow, oh);
//  println(oy3);
//}

//============================================================================================
// 配列の基礎：複数の障害物を落下させる（配列を利用しないコード）& 各落下物に待機時間を導入
//============================================================================================
//int ox1; // 1個目
//int oy1;
//int t1;
//int oWait1; // 待機時間
//int ox2; // 2個目
//int oy2; 
//int t2;
//int oWait2; // 待機時間
//int ox3; // 3個目
//int oy3;
//int t3;
//int oWait3; // 待機時間

//// 今回は，これらの値はすべての物体で共通にする
//int speed = 10; // 落下速度 = フレームレート
//int ow = 30; // 障害物の幅
//int oh = 30; // 障害物の高さ

//void setup() {
//  size(300, 300);
//  t1=0; // 1個目
//  ox1=int(random(width-ow));
//  oWait1=int(random(10, 50)); // 待機時間を乱数で初期化
//  t2=0; // 2個目
//  ox2=int(random(width-ow));
//  oWait2=int(random(10, 50));
//  t3=0; // 3個目
//  ox3=int(random(width-ow));
//  oWait3=int(random(10, 50));
//  frameRate(speed);
//}

//void draw() {
//  background(200, 200, 200);
//  t1 = t1+1; // 1個目
//  oy1 = speed * (t1 - oWait1);
//  t2 = t2+1; // 2個目
//  oy2 = speed * (t2 - oWait2);
//  t3 = t3+1; // 3個目
//  oy3 = speed * (t3 - oWait3);

//  // 1個目
//  if (oy1 > height) {
//    t1 = 0;
//    ox1 = int(random(width-ow));
//    oWait1 = int(random(10, 50)); // 再度，待機時間を乱数で初期化
//  }
//  rect(ox1, oy1, ow, oh);
//  println(oy1);
  
//  // 2個目
//  if (oy2 > height) {
//    t2 = 0;
//    ox2=int(random(width-ow));
//    oWait2 = int(random(10, 50));
//  }
//  rect(ox2, oy2, ow, oh);
//  println(oy2);
  
//  // 3個目
//  if (oy3 > height) {
//    t3 = 0;
//    ox3=int(random(width-ow));
//    oWait3 = int(random(10, 50));
//  }
//  rect(ox3, oy3, ow, oh);
//  println(oy3);
//}


//============================================================================================
// 配列の基礎：複数の障害物を落下させる（1次元配列を利用したコード）
//============================================================================================
//// 1次元配列で変数をまとめる
//// 配列の大きさが固定であれば，数値で指定もOK
////int [] ox = new int[3];
//int nObj = 3; // 落下する障害物の数
//int [] ox = new int[nObj];
//int [] oy = new int[nObj];
//int [] t = new int[nObj]; // 障害物の落下時間
//int [] oWait = new int[nObj]; // 障害物の落下タイミング調整用

//// 今回は，これらの値はすべての物体で共通にする
//int speed = 10; // 落下速度 = フレームレート
//int ow = 30; // 障害物の幅
//int oh = 30; // 障害物の高さ

//void setup() {
//  size(300, 300);
//  // 障害物の個数分だけ初期化
//  for (int i=0; i<nObj; i++) {
//    t[i] = 0;
//    ox[i] = int(random(width-ow)); // windowの幅の中に障害物が入る範囲
//    oWait[i] = int(random(0, 50)); // 障害物落下の待機時間
//  }
//  frameRate(speed);
//}

//void draw() {
//  background(200, 200, 200);
//  for (int i=0; i<nObj; i++) { // 障害物の個数分だけ描画
//    t[i] = t[i]+1;
//    // 落下速度*(開始からの時間-待機時間) = 時刻tでの障害物の高さ．
//    oy[i] = speed * (t[i]-oWait[i]);
//    if (oy[i] > height) {
//      t[i] = 0;
//      ox[i]=int(random(width-ow)); // windowの幅の中に障害物が入る範囲
//      oWait[i]=int(random(10, 50)); // 障害物落下の待機時間
//    }
//    rect(ox[i], oy[i], ow, oh);
//  }
//  println(oy[0], oy[1], oy[2]);
//}



//===============================================================================
//【課題例】複数の障害物を退避するゲーム
// 障害物が複数個，落下してくるゲームを作成せよ．前節の例では，1個の障害物のみを考えていたが，
// 配列を使って，複数の障害物を同時に考えてみよう．
//===============================================================================
//int cx; // 車の左上端のx座標 (cx: car_x)
//int T; // 開始からの時間（フレーム）（開始からの時間をリセットせずにカウント）
//float sec; // 開始からの時間（秒）
//float highScore; // ゲームのハイスコア記録用

//// あとで変更する可能性がある変数はパラメータ化しておくと便利．
//int speed = 10; // 落下速度 = フレームレート
//int ow = 30; // 障害物の幅
//int oh = 30; // 障害物の高さ
//int cw = 30; // 車の幅
//int ch = 30; // 車の高さ

//// 複数の障害物に対応
//int nObj = 20; // 落下する障害物の数
//int [] ox = new int[nObj];
//int [] oy = new int[nObj];
//int [] t = new int[nObj]; // 障害物の落下時間
//int [] oWait = new int[nObj]; // 障害物の落下タイミング調整用
//int cFlag = 0; // Collision Flag 0:正常 1:衝突


//void setup() {
//  size(300, 300);
//  frameRate(speed);
//  T=0;
//  sec=0;
//  highScore=0;

//  // 障害物の個数分だけ初期化
//  for (int i=0; i<nObj; i++) {
//    ox[i]=int(random(width-ow)); // windowの幅の中に障害物が入る範囲
//    t[i]=0;
//    oWait[i]=int(random(0, 50)); // 障害物落下の待機時間
//  }
//}

//void draw() {
//  background(200, 200, 200);
//  T = T+1;

//  for (int i=0; i<nObj; i++) { // 障害物の個数分だけ描画
//    t[i] = t[i]+1;

//    if (t[i] > oWait[i]) {
//      oy[i] = speed * (t[i]-oWait[i]); // 落下速度*(開始からの時間-待機時間) = 時刻tでの障害物の高さ．
//      // 障害物の描画
//      if (oy[i] > height) { // oyの値が障害物の上部の高さと等しいので，windowの高さを超えたらtとoxを初期化する．
//        t[i] = 0;
//        ox[i]=int(random(width-ow)); // windowの幅の中に障害物が入る範囲
//        oWait[i]=int(random(10, 50)); // 障害物落下の待機時間
//      }
//      fill(255, 255, 255);
//      rect(ox[i], oy[i], ow, oh); // 障害物の描画を実行
//    }
//  }

//  // 車の描画
//  cx = mouseX; // マウスポインタのx座標の取得
//  if ((cx+cw) > width) { // 車の右端（px+pw）の座標がウィンドウの幅（width）よりも大きければ車の幅（cw）だけ左に戻す．
//    cx = width - cw;
//  }
//  //fill(255, 255, 255);
//  //rect(cx, width-ch, cw, ch); // 車の描画を実行 // 衝突判定後にも描画を行っているので，ここでは不要．

//  // 衝突判定
//  // x軸方向の条件: (ox < cx+cw && ox+ow > cx)
//  // y軸方向の条件: (oy+oh > height-ch && oy < height)
//  for (int i=0; i<nObj; i++) {
//    if ((ox[i] < cx+cw && ox[i]+ow > cx)&&(oy[i]+oh > height-ch && oy[i] < height)) { // 衝突した場合
//      // 衝突した物体の初期化
//      t[i] = 0;
//      oy[i] = 0;
//      ox[i]=int(random(width-ow)); // windowの幅の中に障害物が入る範囲
//      oWait[i]=int(random(10, 50)); // 障害物落下の待機時間

//      T = 0;
//      cFlag = 1; // 衝突のフラグを立てる
//    }
//  }
//  if (cFlag == 1) { // 衝突のフラグが立っている場合
//    fill(255, 0, 0);
//    cFlag = 0; // フラグを初期化
//  } else {
//    fill(255, 255, 255);
//  }
//  rect(cx, width-ch, cw, ch); // 衝突判定後にもう一度車の描画を実行（衝突している場合は色が変わる）

//  // ゲームのプレイ時間の描画
//  textSize(20);
//  fill(0, 0, 0);
//  sec = (float)T/speed; // フレームレートから秒への変換．フレームレート = 1秒間の描画回数．
//  text("Time: "+sec+" [sec]", 0, 20);

//  // ゲームのハイスコアの保持と描画
//  if (sec > highScore) {
//    highScore = sec;
//  }
//  textSize(20);
//  fill(255, 0, 0);
//  text("High Score: "+highScore, 0, 40);
//}









//
// 以下，参考コード
//


//===============================================================================
// 課題例を改良したもの（障害物を回避し続けた時間を競う）
// - 車の色を変更
// - 車のヒットポイントの実装
//===============================================================================
//int cx; // 車の左上端のx座標 (cx: car_x)
//int T; // 開始からの時間（フレーム）（開始からの時間をリセットせずにカウント）
//float sec; // 開始からの時間（秒）
//float highScore; // ゲームのハイスコア記録用
//int cHP; // 車のヒットポイント

//// あとで変更する可能性がある変数はパラメータ化しておくと便利．
//int speed = 10; // 落下速度 = フレームレート
//int ow = 30; // 障害物の幅
//int oh = 30; // 障害物の高さ
//int cw = 30; // 車の幅
//int ch = 30; // 車の高さ
//int initcHP = 3; // 車のヒットポイントの初期値

//// 複数の障害物に対応
//int nObj = 20; // 落下する障害物の数
//int [] ox = new int[nObj];
//int [] oy = new int[nObj];
//int [] t = new int[nObj]; // 障害物の落下時間
//int [] oWait = new int[nObj]; // 障害物の落下タイミング調整用
//int cFlag = 0; // Collision Flag 0:正常 1:衝突


//void setup() {
//  size(300, 300);
//  frameRate(speed);
//  T=0;
//  sec=0;
//  highScore=0;
//  cHP = initcHP;

//  // 障害物の個数分だけ初期化
//  for (int i=0; i<nObj; i++) {
//    ox[i]=int(random(width-ow)); // windowの幅の中に障害物が入る範囲
//    t[i]=0;
//    oWait[i]=int(random(0, 50)); // 障害物落下の待機時間
//  }
//}

//void draw() {
//  background(200, 200, 200);
//  T = T+1;

//  for (int i=0; i<nObj; i++) { // 障害物の個数分だけ描画
//    t[i] = t[i]+1;

//    if (t[i] > oWait[i]) {
//      oy[i] = speed * (t[i]-oWait[i]); // 落下速度*(開始からの時間-待機時間) = 時刻tでの障害物の高さ．
//      // 障害物の描画
//      if (oy[i] > height) { // oyの値が障害物の上部の高さと等しいので，windowの高さを超えたらtとoxを初期化する．
//        t[i] = 0;
//        ox[i]=int(random(width-ow)); // windowの幅の中に障害物が入る範囲
//        oWait[i]=int(random(10, 50)); // 障害物落下の待機時間
//      }
//      fill(255, 255, 255);
//      rect(ox[i], oy[i], ow, oh); // 障害物の描画を実行
//    }
//  }

//  // 車の描画
//  cx = mouseX; // マウスポインタのx座標の取得
//  if ((cx+cw) > width) { // 車の右端（px+pw）の座標がウィンドウの幅（width）よりも大きければ車の幅（cw）だけ左に戻す．
//    cx = width - cw;
//  }
//  //fill(255, 255, 255);
//  //rect(cx, width-ch, cw, ch); // 車の描画を実行 // 衝突判定後にも描画を行っているので，ここでは不要．

//  // 衝突判定
//  // x軸方向の条件: (ox < cx+cw && ox+ow > cx)
//  // y軸方向の条件: (oy+oh > height-ch && oy < height)
//  for (int i=0; i<nObj; i++) {
//    if ((ox[i] < cx+cw && ox[i]+ow > cx)&&(oy[i]+oh > height-ch && oy[i] < height)) { // 衝突した場合
//      // 衝突した物体の初期化
//      t[i] = 0;
//      oy[i] = 0;
//      ox[i]=int(random(width-ow)); // windowの幅の中に障害物が入る範囲
//      oWait[i]=int(random(10, 50)); // 障害物落下の待機時間

//      cFlag = 1; // 衝突のフラグを立てる

//      // ヒットポイント管理
//      cHP = cHP - 1; // ヒットポイントの減少
//      if (cHP == 0) { // ヒットポイントが0になったら初期化
//        T = 0;
//        cHP = initcHP;
//      }
//    }
//  }

//  if (cFlag == 1) { // 衝突のフラグが立っている場合
//    fill(255, 0, 0);
//    cFlag = 0; // フラグを初期化
//  } else {
//    fill(0, 192, 0);
//  }
//  rect(cx, width-ch, cw, ch); // 衝突判定後にもう一度車の描画を実行（衝突している場合は色が変わる）

//  // 車のヒットポイントの表示
//  for (int i=0; i<cHP; i++) {
//    fill(0, 192, 0);
//    rect(280-20*i, 5, 15, 15);
//  }

//  // ゲームのプレイ時間の描画
//  textSize(20);
//  fill(0, 0, 0);
//  sec = (float)T/speed; // フレームレートから秒への変換．フレームレート = 1秒間の描画回数．
//  text("Time: "+sec+" [sec]", 0, 20);

//  // ゲームのハイスコアの保持と描画
//  if (sec > highScore) {
//    highScore = sec;
//  }
//  textSize(20);
//  fill(255, 0, 0);
//  text("High Score: "+highScore, 0, 40);
//}




//===============================================================================
// 課題例を改良したもの（障害物をキャッチした回数を競う）
// - ゲームデザインの変更
//  ・障害物をキャッチした回数をカウント．キャッチできない場合にヒットポイントが減少．
//===============================================================================
//int cx; // 車の左上端のx座標 (cx: car_x)
//int highScore; // ゲームのハイスコア記録用
//int cHP; // 車のヒットポイント
//int nCollision; // 衝突回数記録用

//// あとで変更する可能性がある変数はパラメータ化しておくと便利．
//int speed = 10; // 落下速度 = フレームレート
//int ow = 30; // 障害物の幅
//int oh = 30; // 障害物の高さ
//int cw = 50; // 車の幅
//int ch = 20; // 車の高さ
//int initcHP = 3; // 車のヒットポイントの初期値

//// 複数の障害物に対応
//int nObj = 10; // 落下する障害物の数
//int [] ox = new int[nObj];
//int [] oy = new int[nObj];
//int [] t = new int[nObj]; // 障害物の落下時間
//int [] oWait = new int[nObj]; // 障害物の落下タイミング調整用
//int cFlag = 0; // Collision Flag 0:正常 1:衝突


//void setup() {
//  size(300, 300);
//  frameRate(speed);
//  highScore=0;
//  cHP = initcHP;
//  nCollision = 0;

//  // 障害物の個数分だけ初期化
//  for (int i=0; i<nObj; i++) {
//    ox[i]=int(random(width-ow)); // windowの幅の中に障害物が入る範囲
//    t[i]=0;
//    oWait[i]=int(random(0, 100)); // 障害物落下の待機時間
//  }
//}

//void draw() {
//  background(200, 200, 200);

//  for (int i=0; i<nObj; i++) { // 障害物の個数分だけ描画
//    t[i] = t[i]+1;

//    if (t[i] > oWait[i]) {
//      oy[i] = speed * (t[i]-oWait[i]); // 落下速度*(開始からの時間-待機時間) = 時刻tでの障害物の高さ．
//      // 障害物の描画
//      if (oy[i] > height) { // oyの値が障害物の上部の高さと等しいので，windowの高さを超えたらtとoxを初期化する．
//        t[i] = 0;
//        ox[i]=int(random(width-ow)); // windowの幅の中に障害物が入る範囲
//        oWait[i]=int(random(10, 100)); // 障害物落下の待機時間
//      }
//      fill(255, 255, 255);
//      ellipse(ox[i], oy[i], ow, oh); // 障害物の描画を実行
//    }
//  }

//  // 車の描画
//  cx = mouseX; // マウスポインタのx座標の取得
//  if ((cx+cw) > width) { // 車の右端（px+pw）の座標がウィンドウの幅（width）よりも大きければ車の幅（cw）だけ左に戻す．
//    cx = width - cw;
//  }

//  // 衝突判定
//  // x軸方向の条件: (ox < cx+cw && ox+ow > cx)
//  // y軸方向の条件: (oy+oh > height-ch && oy < height)
//  for (int i=0; i<nObj; i++) {
//    if ((ox[i] < cx+cw && ox[i]+ow > cx)&&(oy[i]+oh > height-ch && oy[i] < height)) { // 衝突した場合
//      // 衝突した物体の初期化
//      t[i] = 0;
//      oy[i] = 0;
//      ox[i]=int(random(width-ow)); // windowの幅の中に障害物が入る範囲
//      oWait[i]=int(random(10, 100)); // 障害物落下の待機時間

//      cFlag = 1; // 衝突のフラグを立てる

//      nCollision = nCollision + 1; // 衝突回数のカウント
//    }
//  }

//  // ヒットポイント管理
//  for (int i=0; i<nObj; i++) { // 全ての物体をチェック
//    if (oy[i] == height) { // 物体が画面外に出た場合
//      cHP = cHP - 1; // ヒットポイントの減少
//      if (cHP == 0) { // ヒットポイントが0になったら初期化
//        nCollision = 0;
//        cHP = initcHP;
//      }
//    }
//  }

//  if (cFlag == 1) { // 衝突のフラグが立っている場合
//    fill(255, 0, 0);
//    cFlag = 0; // フラグを初期化
//  } else {
//    fill(0, 192, 0);
//  }
//  rect(cx, width-ch, cw, ch); // 衝突判定後にもう一度車の描画を実行（衝突している場合は色が変わる）

//  // 車のヒットポイントの表示
//  for (int i=0; i<cHP; i++) {
//    fill(0, 192, 0);
//    rect(280-20*i, 5, 15, 15);
//  }

//  // 障害物との衝突回数の描画
//  textSize(20);
//  fill(0, 0, 0);
//  text("# of objects: "+nCollision, 0, 20);

//  // ゲームのハイスコアの保持と描画
//  if (nCollision > highScore) {
//    highScore = nCollision;
//  }
//  textSize(20);
//  fill(255, 0, 0);
//  text("High Score: "+highScore, 0, 40);
//}
