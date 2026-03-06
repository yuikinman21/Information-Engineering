////【演習4】水平投げ出し
//float vy, vx;
//int ox, oy;
//int [] xx = new int [5];
//int [] yy = new int [5];

//void setup() {
//  size(400,400);
//  vx = 3;
//  vy = 0;
//  ox = 200;
//  oy = 100;
//  for (int i = 0; i < 5; i++) {
//    xx[i] = 200;
//    yy[i] = 100;
//  }
//  frameRate (100);
//  noStroke();
//}

//void draw() {
//  background(200);
//  for (int i = 0; i < 5; i++) {
//    fill(250 - 20 * i, 250 - 20 * i, 250 - 20 * i);
//    rect(xx[4 - i], yy[4 - i], 30, 30);
//  }
//  fill(255);
//  rect(ox, oy, 30, 30);
//  vy += 1;
//  oy += vy;
//  ox += vx;
//  if (oy > 300 - 30) {
//    oy = 300 - 30;
//    vy *= -1;
//  }
//  if (ox > 400 - 30) {
//    ox = 400 - 30;
//    vx *= -1;
//  }
//  if (ox < 0) {
//    ox = 0;
//    vx *= -1;
//  }
//  for (int i = 0; i < 4; i++) {
//    xx[4 - i] = xx[4 - i - 1];
//    yy[4 - i] = yy[4 - i - 1];
//  }
//  xx[0] = ox;
//  yy[0] = oy;
  
//  println(oy);
//}

//【最終課題】ゲーム制作
float x, y;    //主人公蜂のx,y座標
float velX = 5.0;    //主人公蜂のx軸の初速
float velY = 0.0;    //主人公蜂のy軸の初速
float gravity = 0.4;    //主人公蜂にかかる重力
float reaction = 1;    //主人公蜂の反発力
int i = 0;  //キーボード入力エラーを防ぐための待機時間
float t = 90; //ゲーム終了後の待機時間
int score = 0;
int highscore;

int enemynum = 6; // 同時に現れる蜂の最大数(おすすめは6)
float [] enemyx = new float [enemynum];
float [] enemyy = new float [enemynum];
int [] wait = new int [enemynum];
int [] display = new int [enemynum]; //0で消える、1で表示
int gamestart = 0; // 0はゲーム前。1でゲーム開始！　2でゲーム終了

int mitsux, mitsuy; //蜜のx,y座標

//画像素材読み込み
PImage img;
PImage mitubati; //主人公蜂
PImage mitubati2; //敵蜂（左向き）
PImage mitubati3; //敵蜂（右向き）
PImage mitsu; //蜜

void setup() {
  size(900, 900);
  img = loadImage("678930.jpg"); //画像の読み込み
  mitubati = loadImage("mitubati.png");
  mitubati2 = loadImage("mitubati2.png");
  mitubati3 = loadImage ("mitubati3.png");
  mitsu = loadImage("kaseki_kohaku.png");
  
  for(int i = 0; i < enemynum; i++) { //敵蜂の初期化
    display[i] = 0;
    wait[i] = int (random(10,200));
  }
    mitsux = int (random(50, (width - 170))); //蜜の初期化
    mitsuy = int (random(50, (height - 170)));  

  noStroke();
  fill(0);
  frameRate(24);
}

void draw() {
  image(img, 0, 0, (width * 4 / 3), width);
  //フェードする時はtrue、しない場合はfalse
  //fade(false);
  
  //スタート画面-------------------------------------------------------------------------------
  if (gamestart == 0) {
    fill(169,117,0);
    textSize(75);
    textAlign(CENTER);
    text("PLEASE CLICK WITH \nTHE MOUSE BUTTON!",450,450);
    textSize(50);
    text("High Score:" + highscore,450,50);
    text("Score:" + score,700,50);
    if(mousePressed) {
      gamestart = 1;
      if (mouseX > 780) {
        x = 780;
      }else {
      x = mouseX;
      }
      y = mouseY;
    }
  } else if (gamestart == 1){
    
    //ゲーム開始後-----------------------------------------------------------------------------
    
    for (int i = 0; i < enemynum; i++) {
      if (i % 2 == 1 && display[i] == 0 && wait[i] == 0) { //奇数の時左端に召喚
        enemyx[i] = -120;
        enemyy[i] = int (random(height - 120)); 
        display[i] = 1;
      } else if (i % 2 == 0 && display[i] == 0 && wait[i]== 0) { //偶数の時右端に召喚
        enemyx[i] = width; //右端に召喚
        enemyy[i] = int (random(height - 120));
        display[i] = 1;
      }
    }
  
    //主人公蜂のアルゴリズム-------------------------------------------------------------
    image(mitubati, x, y, 120, 120); //主人公蜂の描画
    velY += gravity;    //スピードに重力が加算される
    x += velX;//主役蜂にスピードを加算
    y += velY;
    
    //蜂が横にぶつかったら逆向きになる
    if (x > (width - 120) || x < 0) {
      velX = -velX;
    }
    
    //主人公蜂が下にぶつかったら逆向きになる
    if (y > (height - 120)) {
      velY *= -reaction;    
      y = (height - 120);    
    }
    
    //もしマウスを押されたら、主人公蜂は上に飛び上がる
    if (mousePressed) {
      if(i == 0) {
          if(mouseX > (x + 60)){
            velY = -7.0;
            velX = 7.0;
          } else {
            velY = -7.0;
            velX = -7.0;
          }
        i += 5;
      }else if (i != 0) {
        i--;
      }
    } else if (i != 0) {
      i--;
    }
    //蜜のアルゴリズム--------------------------------------------------------------
      if (mitsux < (x + 100) && (mitsux + 50) > x && mitsuy < (y + 100) && (mitsuy + 50) > y) {
        mitsux = int (random(50, (width - 170)));
        mitsuy = int (random(50, (height - 170)));
        score += 10;
      }
      text("Score:" + score,700,50);
      text("High Score:" + highscore, 450,50);
      image(mitsu, mitsux, mitsuy, 50, 50); //蜜の描画
    //敵蜂のアルゴリズム----------------------------------------------------------------^
    
      for (int i = 1; i < enemynum; i += 2) {//敵蜂を右に進める
        if(wait[i] == 0) {
          enemyx[i]+=7;
          image(mitubati3, enemyx[i], enemyy[i], 120, 120); //敵蜂を表示
        }
        if (enemyx[i] > width) {
            wait[i] = int (random(10,200));
            enemyx[i] = -120;
            enemyy[i] = int (random(height - 120)); 
        }
        
        //当たり判定
        if (enemyx[i] < (x + 100) && (enemyx[i] + 100) > x && enemyy[i] < (y + 100) && (enemyy[i] + 100) > y) {
          gamestart = 2;
        }
      }
  
      for (int i = 0; i < enemynum; i += 2) {//敵蜂を左に進める
        if(wait[i] == 0) {
          enemyx[i]-=7;
          image(mitubati2,enemyx[i], enemyy[i], 120, 120);//敵蜂を表示
        }
        if (enemyx[i] < -120) {
          wait[i] = int (random(10,200));
          enemyx[i] = width;
          enemyy[i] = int (random(height - 120)); 
        }
        
        //当たり判定
        if (enemyx[i] < (x + 100) && (enemyx[i] + 100) > x && enemyy[i] < (y + 100) && (enemyy[i] + 100) > y) {
          gamestart = 2;
        }
      }

    //その他のプログラム-------------------------------------------------------------
    
    for (int i = 0; i < enemynum; i++) { //wait[i]を下げる
      if (wait[i] > 0) {
        wait[i]--;
      }
    }

    //ゲーム終了画面のプログラム---------------------------------------------------------
  } else if (gamestart == 2) {
    if(highscore < score) {
      highscore = score;
    }
    textSize(75);
    text("Score:" + score,450,400);
    text("High Score:" + highscore,450, 500);
    
    if(t < 0) {
      t = 90;
      score = 0;
      for(int i = 0; i < enemynum; i++) {
        display[i] = 0;
        wait[i] = int (random(10,200));
        enemyx[i] = width;
        enemyy[i] = height;
      }
      mitsux = int (random(50, (width - 170)));
      mitsuy = int (random(50, (height - 170)));  
      gamestart = 0;
    }
    t--;
    text(t / 24,450,600);
  }
}
