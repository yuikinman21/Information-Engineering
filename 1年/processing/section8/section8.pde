

//=======================
//プログラムにコメントを記載
//=======================
//int a=2; // aに2を代入しました．
//int b=3; // bに3を代入しました．
//// ここから計算して結果を出力
//println("a+b=", a+b); // 結果の表示
///* コメント範囲なので，次の行まで無視される
//println("a-b=", a-b);   */


//=======================
//マウスを用いた乗り物の操作
//=======================
//int cx; // 車の左上端のx座標 (cx: car_x)
//void setup() {
//  size(300, 300);
//  frameRate(10);
//}
//void draw() {
//  background(200, 200, 200);
//  cx = mouseX;
//  rect(cx, 270, 30, 30);
//}


//================================================================================================
//【例】上記の操縦の例で，左右の描画範囲を超える場合は，左右の端に固定されるよう，車の位置cxの値を適切に制御せよ．
//================================================================================================
//int cx; // 車の左上端のx座標 (cx: car_x)
//int cw = 30; // 車の幅 (cw: car_width)
//int ch = 30; // 車の高さ (ch: car_height)

//void setup() {
//  size(300, 300);
//  frameRate(10);
//}
//void draw() {
//  background(200, 200, 200);
//  cx = mouseX;
//  // 車の右端（cx+cw）の座標がウィンドウの幅（width）よりも大きければ車の幅（cw）だけ左に戻す．
//  if ((cx+cw) > width) {
//    cx = width - cw;
//  }
//  rect(cx, width-ch, cw, ch);
//}


//================
//障害物の落下の制御
//================
//int ox; // 障害物の左上端のx座標 (ox: object_x)
//int oy; // 障害物の左上端のy座標 (oy: object_y)
//int t; // 開始からの時間（フレーム） = 障害物の落下時間
//void setup() {
//  size(300, 300);
//  t=0;
//  ox=int(random(300));
//  frameRate(10);
//}
//void draw() {
//  background(200, 200, 200);
//  t = t+1;
//  oy = 10*t; // 落下速度*開始からの時間 = 時刻tでの障害物の高さ
//  rect(ox, oy, 30, 30);
//  println(oy);
//}


//=============================
//障害物の落下の制御（パラメータ化）
//=============================
//int ox; // 障害物の左上端のx座標 (ox: object_x)
//int oy; // 障害物の左上端のy座標 (oy: object_y)
//int t; // 開始からの時間（フレーム） = 障害物の落下時間

//// あとで変更する可能性がある変数はパラメータ化しておくと便利．
//int speed = 10; // 落下速度 = フレームレート
//int ow = 30; // 障害物の幅
//int oh = 30; // 障害物の高さ

//void setup() {
//  size(300, 300);
//  t=0;
//  ox=int(random(width-ow)); // windowの幅の中に障害物が入る範囲
//  frameRate(speed);
//}
//void draw() {
//  background(200, 200, 200);
//  t = t+1;
//  oy = speed * t; // 落下速度*開始からの時間 = 時刻tでの障害物の高さ
//  rect(ox, oy, ow, oh);
//  println(oy);
//}


//============================================================================================
//【例】上記の障害物の落下の例で，底に落下後は，改めて天井のどこかから障害物が再度落下するよう，改変してみよ．
//============================================================================================
//int ox; // 障害物の左上端のx座標 (ox: object_x)
//int oy; // 障害物の左上端のy座標 (oy: object_y)
//int t; // 開始からの時間（フレーム） = 障害物の落下時間

//// あとで変更する可能性がある変数はパラメータ化しておくと便利．
//int speed = 10; // 落下速度 = フレームレート
//int ow = 30; // 障害物の幅
//int oh = 30; // 障害物の高さ

//void setup() {
//  size(300, 300);
//  t=0;
//  ox=int(random(width-ow)); // windowの幅の中に障害物が入る範囲
//  frameRate(speed);
//}
//void draw() {
//  background(200, 200, 200);
//  t = t+1;
//  oy = speed*t; // 落下速度*開始からの時間 = 時刻tでの障害物の高さ

//  // oyの値が障害物の上部の高さと等しいので，windowの高さを超えたらtとoxを初期化する．
//  if (oy > height) {
//    t = 0;
//    ox=int(random(width-ow)); // windowの幅の中に障害物が入る範囲
//  }
//  rect(ox, oy, ow, oh);
//  println(oy);
//}



//===================
//車と障害物を同時に描画
//===================
//int ox; // 障害物の左上端のx座標 (ox: object_x)
//int oy; // 障害物の左上端のy座標 (oy: object_y)
//int cx; // 車の左上端のx座標 (cx: car_x)
//int t; // 開始からの時間（フレーム） = 障害物の落下時間

//// あとで変更する可能性がある変数はパラメータ化しておくと便利．
//int speed = 10; // 落下速度 = フレームレート
//int ow = 30; // 障害物の幅
//int oh = 30; // 障害物の高さ
//int cw = 30; // 車の幅
//int ch = 30; // 車の高さ

//void setup() {
//  size(300, 300);
//  t=0;
//  ox=int(random(width-ow)); // windowの幅の中に障害物が入る範囲
//  frameRate(speed);
//}

//void draw() {
//  background(200, 200, 200);
//  t = t+1;
//  oy = speed*t; // 落下速度*開始からの時間 = 時刻tでの障害物の高さ．

//  // 障害物の描画
//  if (oy > height) { // oyの値が障害物の上部の高さと等しいので，windowの高さを超えたらtとoxを初期化する．
//    t = 0;
//    ox=int(random(width-ow)); // windowの幅の中に障害物が入る範囲
//  }
//  fill(255, 255, 255);
//  rect(ox, oy, ow, oh);

//  // 車の描画
//  cx = mouseX;
//  if ((cx+cw) > width) { // 車の右端（px+pw）の座標がウィンドウの幅（width）よりも大きければ車の幅（cw）だけ左に戻す．
//    cx = width - cw;
//  }
//  fill(255, 255, 255);
//  rect(cx, width-ch, cw, ch);
//}




//=========================================================================================
// 車と障害物の衝突の判定
//【例】前々節の車，および前節の障害物を組み合わせたゲームにおいて，時刻tでの車と障害物の衝突判定を行い，
// 衝突しているときは車の正方形を赤色で塗りつぶして表示せよ．
////=========================================================================================
//int ox; // 障害物の左上端のx座標 (ox: object_x)
//int oy; // 障害物の左上端のy座標 (oy: object_y)
//int cx; // 車の左上端のx座標 (cx: car_x)
//int t; // 開始からの時間（フレーム） = 障害物の落下時間

//// あとで変更する可能性がある変数はパラメータ化しておくと便利．
//int speed = 10; // 落下速度 = フレームレート
//int ow = 30; // 障害物の幅
//int oh = 30; // 障害物の高さ
//int cw = 30; // 車の幅
//int ch = 30; // 車の高さ

//void setup() {
//  size(300, 300);
//  t=0;
//  ox=int(random(width-ow)); // windowの幅の中に障害物が入る範囲
//  frameRate(speed);
//}

//void draw() {
//  background(200, 200, 200);
//  t = t+1;
//  oy = speed*t; // 落下速度*開始からの時間 = 時刻tでの障害物の高さ．

//  // 障害物の描画
//  if (oy > height) { // oyの値が障害物の上部の高さと等しいので，windowの高さを超えたらtとoxを初期化する．
//    t = 0;
//    ox=int(random(width-ow)); // windowの幅の中に障害物が入る範囲
//  }
//  fill(255, 255, 255);
//  rect(ox, oy, ow, oh);

//  // 車の描画
//  cx = mouseX;
//  if ((cx+cw) > width) { // 車の右端（px+pw）の座標がウィンドウの幅（width）よりも大きければ車の幅（cw）だけ左に戻す．
//    cx = width - cw;
//  }
//  fill(255, 255, 255);
//  rect(cx, width-ch, cw, ch);

//  // 衝突判定
//  // x軸方向の条件: (ox < cx+cw && ox+ow > cx)
//  // y軸方向の条件: (oy+oh > height-ch && oy < height)
//  if ((ox < cx+cw && ox+ow > cx)&&(oy+oh > height-ch && oy < height)) {
//    fill(255, 0, 0);
//  } else {
//    fill(255, 255, 255);
//  }
//  rect(cx, width-ch, cw, ch);
//}


//======================
//描画領域に文字を表示する
//======================
//size(300, 300);
//int t=5;
//textSize(24);
//fill(0, 0, 0);
//text("t is "+t, 100, 200);


//===============================================================================
//【例】前節のゲームで，開始からの時間を表示せよ．ただし，開始からの時間は秒（second）で表示せよ．
//===============================================================================
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
//  rect(ox, oy, ow, oh);

//  // 車の描画
//  cx = mouseX;
//  if ((cx+cw) > width) { // 車の右端（px+pw）の座標がウィンドウの幅（width）よりも大きければ車の幅（cw）だけ左に戻す．
//    cx = width - cw;
//  }
//  fill(255, 255, 255);
//  rect(cx, width-ch, cw, ch);

//  // 衝突判定
//  // x軸方向の条件: (ox < cx+cw && ox+ow > cx)
//  // y軸方向の条件: (oy+oh > height-ch && oy < height)
//  if ((ox < cx+cw && ox+ow > cx)&&(oy+oh > height-ch && oy < height)) {
//    fill(255, 0, 0);
//  } else {
//    fill(255, 255, 255);
//  }
//  rect(cx, width-ch, cw, ch);

//  // ゲームのプレイ時間の描画
//  textSize(20);
//  fill(0, 0, 0);
//  sec = T/(float)speed; // フレームレートから秒への変換．フレームレート = 1秒間の描画回数．
//  text("Time: "+sec+" [sec]", 0, 20);
//}



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


//【課題】ゲーム開始からの時間表示(先週やったもの)

//int cx; // 車の左上端の x 座標 
//int ox; // 障害物の左上端の x 座標 
//int oy; // 障害物の左上端の y 座標 
//int t; // 開始からの時間（フレーム）
//int t2; // 落下開始からの時間（フレーム）
//int framerate = 200;
//float highscore = 0; //ハイスコア
//int vertical = 300;
//int horizontal = 300;

//void setup(){ 
//  size(300,300); 
//  frameRate(framerate); 
//  t=0; 
  
//  ox=int(random(horizontal - 30)); 
//  frameRate(framerate); 
// }
 
//void draw(){
//  background(200,200,200); 
//  cx = mouseX; 
//  if (cx > horizontal - 30)
//  cx = (horizontal - 30);  //この一行を追加
  
  

//  t += 1; 
//  t2 += 1;
//  oy = 10 * t2; // 落下速度*開始からの時間 = 時刻t での障害物の高さ 
//  fill(255);
//  rect(ox,oy,30,30); 
   
//  //落下後に再度落下するプログラム
//  if (oy == vertical) { 
//    t2 = 0;
//    ox = int (random(horizontal - 30));
//   }
 
//  //衝突表示
//  if (ox < cx + 30 && ox + 30 > cx && oy + 30 > vertical - 30 && oy < vertical) {
//    fill (255, 0, 0); 
//    if ((float)t/framerate > highscore) {
//      highscore = (float)t/framerate;
//    }
//    t = 0;
//  } else {
//    fill (0, 255, 0);
//  }
//  rect(cx,vertical - 30,30,30); 
  
//  //時間表示
//  textSize(24);
//  fill(0);
//  text( ((float)t/framerate) +"sec", 120,20);
  
//    //ハイスコア表示

//    fill (255, 0, 0);
//    text("Highscore:" + highscore + "sec", 120, 50);
  
//}



////これまでの1変数の定義の仕方
//int a = 1;
//println(a);



////1次元配列の定義の仕方
//int[] array = new int [5];

////配列の要素の定義
//array[0] = 2;
//array[1] = 4;
//array[2] = 6;
//array[3] = 8;
//array[4] = 10;

////配列の使用
//int ans = array[0] + array[4];
//println(ans);


//int[] array1 = {2, 4, 6, 8, 10};

////for 文を使った要素の定義
//int[] array2 = new int[5];
//for (int i = 0; i < 5; i++) {
//  array2[i] = 2 * i;
//}


//配列の基礎

//int[][] matrix = new int[2][4];

//matrix[0][0] = 1;
//matrix[0][1] = 2;
//matrix[0][2] = 3;
//matrix[0][3] = 4;
//matrix[1][0] = 5;
//matrix[1][1] = 6;
//matrix[1][2] = 7;
//matrix[1][3] = 8;

////配列の使用
//int a = matrix[0][0] + matrix[1][3];
//println(a);



//配列の基礎２

//int [][] matrix1 = {{1, 2, 3, 4},{5, 6, 7, 8}};

//int[][] matrix2 = new int[2][4];
//for (int m = 0; m < 2; m++) {
//  for (int n = 0; n < 4; n++) {
//    matrix2[m][n] = (m + 1) * (n + 1);
//  }
//}



//int ox1; // 障害物の左上端のx座標 (ox: object_x)
//int oy1; // 障害物の左上端のy座標 (oy: object_y)
//int t1; // 開始からの時間（フレーム） = 障害物の落下時間
//int oWait1;

//int ox2; // 障害物の左上端のx座標 (ox: object_x)
//int oy2; // 障害物の左上端のy座標 (oy: object_y)
//int t2; // 開始からの時間（フレーム） = 障害物の落下時間
//int oWait2;

//int ox3; // 障害物の左上端のx座標 (ox: object_x)
//int oy3; // 障害物の左上端のy座標 (oy: object_y)
//int t3; // 開始からの時間（フレーム） = 障害物の落下時間
//int oWait3;


//// あとで変更する可能性がある変数はパラメータ化しておくと便利．
//int speed = 30; // 落下速度 = フレームレート
//int ow = 30; // 障害物の幅
//int oh = 30; // 障害物の高さ

//void setup() {
//  size(300, 300);
//  t1=0;
//  ox1=int(random(width-ow)); // windowの幅の中に障害物が入る範囲
//  oWait1 = int (random(10,50));
  
//  t2=0;
//  ox2=int(random(width-ow)); // windowの幅の中に障害物が入る範囲
//  oWait2 = int(random(10,50));
  
//  t3=0;
//  ox3=int(random(width-ow)); // windowの幅の中に障害物が入る範囲
//  oWait3 = int(random(10,50));
  
//  frameRate(speed);
//}
//void draw() {
//  background(200, 200, 200);
//  t1 = t1+1;
//  oy1 = speed * (t1 - oWait1); // 落下速度*開始からの時間 = 時刻tでの障害物の高さ

//  // oyの値が障害物の上部の高さと等しいので，windowの高さを超えたらtとoxを初期化する．
//  if (oy1 > height) {
//    t1 = 0;
//    ox1=int(random(width-ow)); // windowの幅の中に障害物が入る範囲
//  }
//  rect(ox1, oy1, ow, oh);
//  println(oy1);
  
//  t2 = t2+1;
//  oy2 = speed * (t2 - oWait2); // 落下速度*開始からの時間 = 時刻tでの障害物の高さ

//  // oyの値が障害物の上部の高さと等しいので，windowの高さを超えたらtとoxを初期化する．
//  if (oy2 > height) {
//    t2 = 0;
//    ox2=int(random(width-ow)); // windowの幅の中に障害物が入る範囲
//  }
//  rect(ox2, oy2, ow, oh);
//  println(oy2);
  
//  t3 = t3+1;
//  oy3 = speed * (t3 - oWait3); // 落下速度*開始からの時間 = 時刻tでの障害物の高さ

//  // oyの値が障害物の上部の高さと等しいので，windowの高さを超えたらtとoxを初期化する．
//  if (oy3 > height) {
//    t3 = 0;
//    ox3=int(random(width-ow)); // windowの幅の中に障害物が入る範囲
//  }
//  rect(ox3, oy3, ow, oh);
//  println(oy3);
//}




//【課題】障害物の数を増やして統合する
int nObj = 3;
int [] ox = new int[nObj];
int [] oy = new int[nObj];
int [] t = new int [nObj];
int [] oWait = new int[nObj];

int cx; // 車の左上端の x 座標 
int t1; // 開始からの時間（フレーム）

int highscore = 0; //ハイスコア




// あとで変更する可能性がある変数はパラメータ化しておくと便利．
float speed = 10; // 落下速度 = フレームレート
int ow = 30; // 障害物の幅
int oh = 30; // 障害物の高さ

void setup() {
  size(300, 300);
  
  for (int i = 0; i < nObj; i++) {
    t[i] = 0;
    ox[i] = int (random(width - ow));
    oWait[i] = int(random(0,50));
  }
  frameRate(speed);
}

void draw() {
  background(200, 200, 200);

  cx = mouseX; 
  if (cx > height - 30)
  cx = (width - 30);  //この一行を追加
  t1++;
  
  
  
  for ( int i = 0; i < nObj; i++) {
    t[i]++;
    oy[i] = speed * (t[i] - oWait[i]);
    
    
      //衝突表示
    if (ox[i] < cx + 30 && ox[i] + 30 > cx && oy[i] + 30 > height - 30 && oy[i] < height) {
      fill (255, 0, 0); 
      if ((float)t/speed > highscore) {
        highscore = (float)t/speed;
      }
      t1 = 0;
    } else {
      fill (0, 255, 0);
    }
    rect(cx,height - 30,30,30); 
  
  
    if (oy[i] > height) {
      t[i] = 0;
      ox[i] = int(random(width - ow));
      oWait[i] = int (random(10,50));
    }
    fill(255);
    rect(ox[i], oy[i], ow, oh);
  }
  
    //時間表示
  textSize(24);
  fill(0);
  //text( ((float)t/speed) +"sec", 120,20);
  
    //ハイスコア表示

    fill (255, 0, 0);
    text("Highscore:" + highscore + "sec", 120, 50);
  
  println(oy[0], oy[1], oy[2]);
}
