//マウス追尾アニメーション（サンプル）

//void setup(){
//    size(300,200);
//    frameRate(10);
//    }
//    void draw(){
//    ellipse(mouseX,mouseY,10,10);
//    } 



//アニメーション〇□変化（サンプル）

//int a; 
//void setup(){ 
// size(300,200); 
// frameRate(1); 
// a=0; 
// } 
// void draw(){ 
//background(200,200,200); 
// int i; 
//for(i=0; i<10; i++){ 
// if((i+a)%2==0){ 
// fill(255,0,0); 
//rect(30*i, 0, 30, 30); 
// } 
//else{ 
//fill(0,0,255); 
//ellipse(15+30*i, 15, 30, 30); 
//} 
// } 
// a=a+1; 
// } 



//【課題】赤ブロックが左右に移動するアニメーション

//int count = 0;
//color red = color(255,0,0);
//color white = color (255);

//  void setup() {
//    size (300,30);
//    frameRate(2);  
//  }
  
//  void draw() {
    
//    //10個の正方形を生成
//    for (int i = 0; i < 10; i++) {
//      fill (white);
//      rect (i * 30, 0, 30, 30);
//    }
    
//    //移動する赤い正方形を生成
//    fill(red);
    
//    if ((count / 10) % 2 == 0) {
//      if (count % 10 == 0 && count != 0) //左端の場合にcountを進める処理（最初を除く）
//        count ++;
//      rect ((count % 10) * 30, 0, 30, 30);
//    }
//    else    {
//      if (count % 10 == 0) //右端の場合にcountを進める処理
//        count++;
//      rect ((9 - (count % 10)) * 30, 0, 30, 30);
//    }    
//    count ++;
//  }



//赤い正方形が障害物をとび越えて移動（サンプル）

//int a;
//int [] s= {0,0,1,0,0,0,1,0,0,0};
//void setup(){
// size(300,200);
// frameRate(1);
// a=0;
// }
// void draw(){
//background(200,200,200);
// int i;
//for(i=0; i<10; i++){
// if(s[i]==1){
// fill(0,0,0);
// }
//else if(i==a){
//fill(255,0,0);
//}
// else{
//fill(255,255,255);
//}
//rect(30*i, 0, 30, 30);
// }
// a=a+1;
// if(a>9){
// a=0;
//}
// }



//2次元配列　迷路(サンプル)

// size(300,300); 
//int [][] s= {
//{0,1,0,1,1,1,0,0,0,0}, 
//{0,1,0,0,0,1,1,1,0,1}, 
//{0,1,1,1,0,1,0,0,0,0}, 
//{0,0,0,1,0,1,0,1,1,0}, 
//{1,1,0,1,0,1,0,1,0,0}, 
//{0,1,0,1,0,0,0,1,0,0}, 
//{0,1,0,1,0,1,1,1,0,1}, 
//{0,0,0,1,0,1,0,0,0,1}, 
//{0,1,1,1,0,1,0,1,1,1}, 
//{0,0,0,0,0,1,0,0,0,0}}; 
// int i; 
// int j; 
//  for(i=0; i<10; i++){ 
//  for(j=0; j<10; j++){ 
//   if(s[i][j]==1){ 
//    fill(0,0,0); 
//    } 
//    else{ 
//      fill(255,255,255); 
//    } 
//  rect(30*j, 30*i, 30, 30); 
//  } 
//} 



//【課題】左上から順に赤いセルが障害物を飛び越えて右下のセルまで移動するプログラム

//int count1 = 0;
//int count2 = 0;
//color black = color (0);
//color white = color (255);
//color red = color (255,0,0);

//int [ ][ ] maze = {
//                {0,1,0,1,1,1,0,0,0,0}, 
//                {0,1,0,0,0,1,1,1,0,1}, 
//                {0,1,1,1,0,1,0,0,0,0}, 
//                {0,0,0,1,0,1,0,1,1,0}, 
//                {1,1,0,1,0,1,0,1,0,0}, 
//                {0,1,0,1,0,0,0,1,0,0}, 
//                {0,1,0,1,0,1,1,1,0,1}, 
//                {0,0,0,1,0,1,0,0,0,1}, 
//                {0,1,1,1,0,1,0,1,1,1}, 
//                {0,0,0,0,0,1,0,0,0,0}}; 

//  void setup() {
//    size (300,300);
//    frameRate(4); 
//  }

//  void draw() {

//    //迷路を描画
//    for (int i = 0; i < 10; i++) {
//      for (int j = 0; j < 10; j++) {
//        if( maze[i][j] == 1) {
//          fill(black);
//        }
        
//        //赤いセルを描画
//        else if (count1 == j && count2 == i) {
//          fill(red);
//        }
//        else {
//          fill(white);
//        }
//        rect(30 * j, 30 * i, 30, 30);
//      }
//    }
    
//    //赤いセルの折り返し処理
//    count1++;
//    if (count1 == 10 && count2 == 9) {
//      count1 = 0;
//      count2 = 0;
//    } 
//    else if (count1 == 10) {
//      count1 = 0;
//      count2++;
//    }
    
//  }



//【課題】右手の法則による迷路探索
  
//int x = 1;
//int y = 1;
//int count = 0;

//int direction = 0; //上：0　右：1　下：2　左：3

//color black = color (0);
//color white = color (255);
//color red = color (255,0,0);
//color start = color (0,255,0,100);
//color goal = color (0,0,255,100);

//int [ ][ ] maze = {
//                {1,1,1,1,1,1,1,1,1,1,1,1},
//                {1,0,1,0,1,1,1,0,0,0,0,1}, 
//                {1,0,1,0,0,0,1,1,1,0,1,1}, 
//                {1,0,1,1,1,0,1,0,0,0,0,1}, 
//                {1,0,0,0,1,0,1,0,1,1,0,1}, 
//                {1,1,1,0,1,0,1,0,1,0,0,1}, 
//                {1,0,1,0,1,0,0,0,1,0,0,1}, 
//                {1,0,1,0,1,0,1,1,1,0,1,1}, 
//                {1,0,0,0,1,0,1,0,0,0,1,1}, 
//                {1,0,1,1,1,0,1,0,1,1,1,1}, 
//                {1,0,0,0,0,0,1,0,0,0,0,1},
//                {1,1,1,1,1,1,1,1,1,1,1,1}
//                    }; 

//  void setup() {
//    size (300,300);
//    frameRate(6); 
//  }

//  void draw() {
//    translate(-30,-30);
    
//    //迷路を描画
//    for (int i = 0; i < 12; i++) {
//      for (int j = 0; j < 12; j++) {
//        if( maze[i][j] == 1) {
//          fill(black);
//        }
//        else {
//          fill(white);
//        }
//        rect(30 * j, 30 * i, 30, 30);
//      }
//    }
    
//    fill(start);
//    rect(30,30,30,30);
    
//    fill(goal);
//    rect(300,300,30,30);

//    //アニメーションの終了
//    if( x == 10 && y == 10) { 
//      noLoop();
//    }
    
//    //初期値の設定
//    if (count == 0) {
//      rect (30, 30, 30, 30);
//      direction = 0;
//    }
    
//    //右手の法則

//    fill(red);

//    if (count > 0) {
//      switch (direction) {
//        case 0: //上を向いているとき
//          if (maze[y][x+1] == 0) {
//            x++;
//            direction = 1;
//          } 
//          else if (maze[y-1][x] == 0) {
//            y--;
            
//          } 
//          else if (maze[y][x-1] == 0) {
//            x--;
//            direction = 3;
//          }else {
            
//            direction = 2;
//          }
//        break;
        
//        case 1: //右を向いているとき
//          if (maze[y+1][x] == 0) {
//            y++;
//            direction = 2;
//          } 
//          else if (maze[y][x+1] == 0) {
//            x++;
            
//          } 
//          else if (maze[y-1][x] == 0) {
//            y--;
//            direction =0;
//          }
//          else {
//            direction = 3;
//          }
//        break;
        
//        case 2: //下を向いているとき
//          if (maze[y][x-1] == 0) {
//            x--;
//            direction = 3;
//          }
//          else if (maze[y+1][x] == 0) {
//            y++;
            
//          }
//          else if (maze[y][x+1] == 0) {
//            x++;
//            direction = 1;
//          }
//          else {
            
//            direction = 0;
//          }
          
//        break;
        
//        case 3: //左を向いているとき
//          if (maze[y-1][x] == 0) {
//            y--;
//            direction = 0;
//          }
//          else if (maze[y][x-1] == 0) {
//            x--;
            
//          }
//          else if (maze[y+1][x] == 0) {
//            y++;
//            direction = 2;
//          }
//          else {
//            direction = 1;
//          }
          
//        break;
//      }
//      rect(x * 30, y * 30, 30, 30);      
//    }
//    count++;
//    println(direction);
//  }
  
  
  
//【課題】左手の法則による迷路探索
  
int x = 1;
int y = 1;
int count = 0;

int direction = 0; //上：0　右：1　下：2　左：3

color black = color (0);
color white = color (255);
color red = color (255,0,0);
color start = color (0,255,0,100);
color goal = color (0,0,255,100);

int [ ][ ] maze = {
                {1,1,1,1,1,1,1,1,1,1,1,1},
                {1,0,1,0,1,1,1,0,0,0,0,1}, 
                {1,0,1,0,0,0,1,1,1,0,1,1}, 
                {1,0,1,1,1,0,1,0,0,0,0,1}, 
                {1,0,0,0,1,0,1,0,1,1,0,1}, 
                {1,1,1,0,1,0,1,0,1,0,0,1}, 
                {1,0,1,0,1,0,0,0,1,0,0,1}, 
                {1,0,1,0,1,0,1,1,1,0,1,1}, 
                {1,0,0,0,1,0,1,0,0,0,1,1}, 
                {1,0,1,1,1,0,1,0,1,1,1,1}, 
                {1,0,0,0,0,0,1,0,0,0,0,1},
                {1,1,1,1,1,1,1,1,1,1,1,1}
                    }; 

  void setup() {
    size (300,300);
    frameRate(6); 
  }

  void draw() {
    translate(-30,-30);
    
    //迷路を描画
    for (int i = 0; i < 12; i++) {
      for (int j = 0; j < 12; j++) {
        if( maze[i][j] == 1) {
          fill(black);
        }
        else {
          fill(white);
        }
        rect(30 * j, 30 * i, 30, 30);
      }
    }
    
    fill(start);
    rect(30,30,30,30);
    
    fill(goal);
    rect(300,300,30,30);

    //アニメーションの終了
    if( x == 10 && y == 10) { 
      noLoop();
    }
    
    //初期値の設定
    if (count == 0) {
      rect (30, 30, 30, 30);
      direction = 0;
    }
    
    //左手の法則
    fill (red);
    
    if (count > 0) {
      switch (direction) {
        case 0: //上を向いているとき
          if (maze[y][x-1] == 0) {
            x--;
            direction = 3;
          } 
          else if (maze[y-1][x] == 0) {
            y--;
            
          } 
          else if (maze[y][x+1] == 0) {
            x++;
            direction = 1;
          }else {
            
            direction = 2;
          }
        break;
        
        case 1: //右を向いているとき
          if (maze[y-1][x] == 0) {
            y--;
            direction = 0;
          } 
          else if (maze[y][x+1] == 0) {
            x++;
            
          } 
          else if (maze[y+1][x] == 0) {
            y++;
            direction =2;
          }
          else {
            direction = 3;
          }
        break;
        
        case 2: //下を向いているとき
          if (maze[y][x+1] == 0) {
            x++;
            direction = 1;
          }
          else if (maze[y+1][x] == 0) {
            y++;
            
          }
          else if (maze[y][x-1] == 0) {
            x--;
            direction = 3;
          }
          else {
            
            direction = 0;
          }
          
        break;
        
        case 3: //左を向いているとき
          if (maze[y+1][x] == 0) {
            y++;
            direction = 2;
          }
          else if (maze[y][x-1] == 0) {
            x--;
            
          }
          else if (maze[y-1][x] == 0) {
            y--;
            direction = 0;
          }
          else {
            direction = 1;
          }
          
        break;
      }
      rect(x * 30, y * 30, 30, 30);      
    }
    count++;
    println("direction=", direction);
  }
  
  
  
//【発展課題1】迷路の全探索

//int x = 1;
//int y = 1;
//int count = 0;

//int direction = 0; //上：0　右：1　下：2　左：3

//color black = color (0);
//color white = color (255);
//color red = color (255,0,0);

//int [ ][ ] maze = {
//                {1,1,1,1,1,1,1,1,1,1,1,1},
//                {1,0,0,0,0,0,0,0,0,0,0,1}, 
//                {1,0,1,1,1,0,1,1,1,0,1,1}, 
//                {1,0,1,0,0,0,1,0,0,0,0,1}, 
//                {1,0,1,1,1,0,1,0,1,1,0,1}, 
//                {1,0,0,0,1,1,1,0,1,0,0,1}, 
//                {1,0,1,0,1,0,1,0,1,0,0,1}, 
//                {1,1,1,1,1,0,1,1,1,0,1,1}, 
//                {1,0,0,0,0,0,1,0,0,0,1,1}, 
//                {1,0,1,1,1,1,1,0,1,1,1,1}, 
//                {1,0,0,0,0,0,0,0,0,0,0,1},
//                {1,1,1,1,1,1,1,1,1,1,1,1}
//                    }; 
                    
//int [][] root = new int [12][12];

//  void setup() {
//    size (300,300);
//    frameRate(6); 
//  }

//  void draw() {
//    translate(-30,-30);
    
//    //迷路を描画
//    for (int i = 0; i < 12; i++) {
//      for (int j = 0; j < 12; j++) {
//        if( maze[i][j] == 1) {
//          fill(black);
//        }
//        else {
//          fill(white);
//        }
//        rect(30 * j, 30 * i, 30, 30);
//      }
//    }

//    fill (red);
    
//    //アニメーションの終了
//    if( x == 5 && y == 6) { 
//      noLoop();
//    }
    
//    //初期値の設定
//    if (count == 0) {
//      rect (30, 30, 30, 30);
//      direction = 0;
//    }
    
//    //左手の法則
//    if (count > 0) {
//      switch (direction) {
//        case 0: //上を向いているとき
//          if (maze[y][x-1] == 0) {
//            x--;
//            direction = 3;
//          } 
//          else if (maze[y-1][x] == 0) {
//            y--;
            
//          } 
//          else if (maze[y][x+1] == 0) {
//            x++;
//            direction = 1;
//          }else {
            
//            direction = 2;
//          }
//        break;
        
//        case 1: //右を向いているとき
//          if (maze[y-1][x] == 0) {
//            y--;
//            direction = 0;
//          } 
//          else if (maze[y][x+1] == 0) {
//            x++;
            
//          } 
//          else if (maze[y+1][x] == 0) {
//            y++;
//            direction =2;
//          }
//          else {
//            direction = 3;
//          }
//        break;
        
//        case 2: //下を向いているとき
//          if (maze[y][x+1] == 0) {
//            x++;
//            direction = 1;
//          }
//          else if (maze[y+1][x] == 0) {
//            y++;
            
//          }
//          else if (maze[y][x-1] == 0) {
//            x--;
//            direction = 3;
//          }
//          else {
            
//            direction = 0;
//          }
          
//        break;
        
//        case 3: //左を向いているとき
//          if (maze[y+1][x] == 0) {
//            y++;
//            direction = 2;
//          }
//          else if (maze[y][x-1] == 0) {
//            x--;
            
//          }
//          else if (maze[y-1][x] == 0) {
//            y--;
//            direction = 0;
//          }
//          else {
//            direction = 1;
//          }
          
//        break;
//      }
//      rect(x * 30, y * 30, 30, 30);      
//    }
    
//    count++;
//    println("direction=", direction);
//  }
  
  
  
//  【発展課題2】スタートや他所に戻る落とし穴　（落とし穴に落ちた場所を障害物とみなすとか？）
  
  
  
  
