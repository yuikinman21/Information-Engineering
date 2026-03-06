//コメントを記載（サンプル）

//int a=2; // a に 2 を代入しました． 
//int b=3; // b に 3 を代入しました． 
//// ここから計算して結果を出力 
//println("a+b=", a+b); // 結果の表示 
///* コメント範囲なので，次の行まで無視される 
//println("a-b=", a-b); */ 



// マウスを用いた乗り物の操作（サンプル）

//int cx; // 車の左上端の x 座標 
//void setup(){ 
// size(300,300); 
// frameRate(10); 
// } 
// void draw(){
//   background(200,200,200); 
// cx = mouseX; 
// rect(cx,270,30,30); 
// }



// 【課題】マウスを用いた乗り物の操作

//int cx; // 車の左上端の x 座標 
//void setup(){ 
// size(300,300); 
// frameRate(10); 
// } 
// void draw(){
//   background(200,200,200); 
// cx = mouseX; 
// if (cx > 270)
//   cx = 270;  //この一行を追加
// rect(cx,270,30,30); 
 
// }



// 障害物の落下の制御（サンプル）

//int ox; // 障害物の左上端の x 座標 
//int oy; // 障害物の左上端の y 座標 
//int t; // 開始からの時間（フレーム） 
//void setup(){ 
// size(300,300); 
// t=0; 
// ox=int(random(300)); 
// frameRate(10); 
// } 
// void draw(){
//   background(200,200,200); 
// t = t+1; 
//oy = 10*t; // 落下速度*開始からの時間 = 時刻t での障害物の高さ 
// rect(ox,oy,30,30); 
// }
 
 
 
//【課題】障害物の落下の制御（改変版）

//int ox; // 障害物の左上端の x 座標 
//int oy; // 障害物の左上端の y 座標 
//int t; // 開始からの時間（フレーム）

//void setup(){ 
// size(300,300); 
// t=0; 
// ox=int(random(270)); 
// frameRate(60); 
// } 
 
// void draw(){
//   background(200,200,200); 
// t = t+1; 
//oy = 10*t; // 落下速度*開始からの時間 = 時刻t での障害物の高さ 
// rect(ox,oy,30,30); 
 
// //落下後に再度落下するプログラム
// if (oy == 270) { 
//  t = 0;
//  ox = int (random(270));
// }
// }
 
 
 
//【課題】車と障害物の衝突ゲーム
 
//int cx; // 車の左上端の x 座標 
//int ox; // 障害物の左上端の x 座標 
//int oy; // 障害物の左上端の y 座標 
//int t; // 開始からの時間（フレーム）

//void setup(){ 
//  size(300,300); 
//  frameRate(10); 
//  t=0; 
//  ox=int(random(270)); 
//  frameRate(10); 
// }
 
//void draw(){
//  background(200,200,200); 
//  cx = mouseX; 
//  if (cx > 270)
//  cx = 270;  //この一行を追加
  
  

//  t = t+1; 
//  oy = 10*t; // 落下速度*開始からの時間 = 時刻t での障害物の高さ 
//  rect(ox,oy,30,30); 
   
//  //落下後に再度落下するプログラム
//  if (oy == 270) { 
//    t = 0;
//    ox = int (random(270));
//   }
 
//  if (ox < cx + 30 && ox + 30 > cx && oy + 30 > 300 - 30 && oy < 300) {
//    fill (255, 0, 0);
//  } else {
//    fill (255);
//  }
//  rect(cx,270,30,30); 
//  fill (255);
//}



//描画領域に文字を表示（サンプル）

  //size(300,300); 
  //int t=5; 
  //textSize(24); 
  //fill(0,0,0); 
  //text("t is "+t,100,200); 
  
  

//【課題】ゲーム開始からの時間表示

int cx; // 車の左上端の x 座標 
int ox; // 障害物の左上端の x 座標 
int oy; // 障害物の左上端の y 座標 
int t; // 開始からの時間（フレーム）
int t2; // 落下開始からの時間（フレーム）
int framerate = 200;
float highscore = 0; //ハイスコア

void setup(){ 
  size(300,900); 
  frameRate(framerate); 
  t=0; 
  
  ox=int(random(270)); 
  frameRate(framerate); 
 }
 
void draw(){
  background(200,200,200); 
  cx = mouseX; 
  if (cx > 270)
  cx = 270;  //この一行を追加
  
  

  t += 1; 
  t2 += 1;
  oy = 10 * t2; // 落下速度*開始からの時間 = 時刻t での障害物の高さ 
  fill(255);
  rect(ox,oy,30,30); 
   
  //落下後に再度落下するプログラム
  if (oy == 900) { 
    t2 = 0;
    ox = int (random(270));
   }
 
  //衝突表示
  if (ox < cx + 30 && ox + 30 > cx && oy + 30 > 900 - 30 && oy < 900) {
    fill (255, 0, 0); 
    if ((float)t/framerate > highscore) {
      highscore = (float)t/framerate;
    }
    t = 0;
  } else {
    fill (0, 255, 0);
  }
  rect(cx,870,30,30); 
  
  //時間表示
  textSize(24);
  fill(0);
  text( ((float)t/framerate) +"sec", 120,20);
  
    //ハイスコア表示

    fill (255, 0, 0);
    text("Highscore:" + highscore + "sec", 120, 50);
  
}


  



//障害物回避ゲーム（サンプル）
/*
int ox; // 障害物の左上端の x 座標 (ox: object_x) 
int oy; // 障害物の左上端の y 座標 (oy: object_y) 
int cx; // 車の左上端の x 座標 (cx: car_x) 
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
 t = 0; 
 T = 0; 
 sec = 0; 
 ox=int(random(width - ow)); // window の幅の中に障害物が入る範囲 
 frameRate(speed); 
} 
void draw() { 
 background(200, 200, 200); 
 t = t + 1; 
 T = T + 1; 
 oy = speed * t; // 落下速度*開始からの時間 = 時刻 t での障害物の高さ． 
 // 障害物の描画 
 if (oy > height) { // oy の値が障害物の上部の高さと等しいので，window の高さを超えたら t と ox を初期化する． 
 t = 0; 
 ox=int(random(width - ow)); // window の幅の中に障害物が入る範囲 
 } 
 fill(255, 255, 255); 
 rect(ox, oy, ow, oh); // 障害物の描画を実行 
 // 車の描画 
 cx = mouseX; // マウスポインタの x 座標の取得 
 if ((cx + cw) > width) { // 車の右端（px+pw）の座標がウィンドウの幅（width）よりも大きければ車の幅（cw）だけ左に戻す． 
 cx = width - cw; 
 } 
 fill(255, 255, 255); 
 rect(cx, width - ch, cw, ch); // 車の描画を実行 
 // 衝突判定 
 // x 軸方向の条件: (ox < cx+cw && ox+ow > cx)
 // y 軸方向の条件: (oy+oh > height-ch && oy < height) 
 if ((ox < cx + cw && ox + ow > cx)&&(oy + oh > height - ch && oy < height)) { // 衝突した場合 
 // 衝突した物体の初期化 
 t = 0; 
 oy = 0; 
 ox = int(random(width - ow)); // window の幅の中に障害物が入る範囲 
 fill(255, 0, 0); 
 T = 0; 
 } else { // 衝突しない場合 
 fill(0, 192, 0); 
 } 
 rect(cx, width - ch, cw, ch); // 衝突判定後にもう一度車の描画を実行（衝突している場合は色が変わる） 
 // ゲームのプレイ時間の描画 
 textSize(20); 
 fill(0, 0, 0); 
 sec = (float)T / speed; // フレームレートから秒への変換．フレームレート = 1 秒間の描画回数． 
 text("Time: "+sec+" [sec]", 0, 20); 
} */
