//【実験】別の迷路で挑戦!（成功ver）

//int x = 1;
//int y = 1;
//int count = 0;

//int direction = 0; //上：0　右：1　下：2　左：3

//color black = color (0);
//color white = color (255);
//color red = color (255,0,0);
//color start = color(0,255,0);
//color goal = color (0,0,255);

//int [ ][ ] maze = {
//                {1,1,1,1,1,1,1,1,1,1,1,1},
//                {1,0,0,0,0,1,0,0,0,1,0,1}, 
//                {1,1,0,1,0,0,1,1,0,0,0,1}, 
//                {1,0,0,0,1,0,0,0,1,0,1,1}, 
//                {1,1,1,0,0,1,1,0,0,0,0,1}, 
//                {1,0,0,0,1,0,0,1,1,1,0,1}, 
//                {1,0,1,1,1,1,0,0,1,0,0,1}, 
//                {1,0,0,0,0,1,1,0,0,1,1,1}, 
//                {1,0,1,1,0,0,0,1,0,0,0,1}, 
//                {1,0,0,1,0,1,0,0,1,0,1,1}, 
//                {1,1,0,0,0,0,1,0,0,0,1,1},
//                {1,1,1,1,1,1,1,1,1,1,1,1}
//                    }; 
                    
//int [][] root = new int [12][12];

//  void setup() {
//    size (300,300);
//    frameRate(10); 
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
//    rect(180,150,30,30);
    
//    //アニメーションの終了
//    if( x == 6 && y == 5) { 
//      direction = 4;
//      noLoop();
//    }
    
//    //初期値の設定
//    if (count == 0) {
//      rect (30, 30, 30, 30);
//      direction = 0;
//    }
    
//    //左手の法則
    
//    fill (red);
    
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
  


//【実験】左手の法則で解けない場合

//int x = 1;
//int y = 1;
//int count = 0;

//int direction = 0; //上：0　右：1　下：2　左：3

//color black = color (0);
//color white = color (255);
//color red = color (255,0,0);
//color start = color(0,255,0);
//color goal = color (0,0,255);

//int [ ][ ] maze = {
//                {1,1,1,1,1,1,1,1,1,1,1,1},
//                {1,0,0,0,1,0,0,0,0,1,0,1}, 
//                {1,0,1,0,0,1,0,1,0,0,0,1}, 
//                {1,0,0,1,0,0,0,1,0,1,1,1}, 
//                {1,1,0,0,0,1,1,1,0,0,1,1}, 
//                {1,0,1,0,1,0,0,1,1,0,1,1}, 
//                {1,0,0,0,1,0,0,1,0,0,0,1}, 
//                {1,0,1,0,0,1,0,0,0,1,0,1}, 
//                {1,0,1,1,0,0,1,1,1,0,0,1}, 
//                {1,0,0,0,1,0,0,0,1,0,1,1}, 
//                {1,0,1,0,0,0,1,0,0,0,1,1},
//                {1,1,1,1,1,1,1,1,1,1,1,1}
//                    }; 
                    
//int [][] root = new int [12][12];

//  void setup() {
//    size (300,300);
//    frameRate(10); 
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
//    rect(180,150,30,30);
    
//    //アニメーションの終了
//    if( x == 6 && y == 5) { 
//      direction = 4;
//      noLoop();
//    }
    
//    //初期値の設定
//    if (count == 0) {
//      rect (30, 30, 30, 30);
//      direction = 0;
//    }
    
//    //左手の法則
    
//    fill (red);
    
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
  
  
  
////【実験】右手の法則で解けない場合

//int x = 1;
//int y = 1;
//int count = 0;

//int direction = 0; //上：0　右：1　下：2　左：3

//color black = color (0);
//color white = color (255);
//color red = color (255,0,0);
//color start = color(0,255,0);
//color goal = color (0,0,255);

//int [ ][ ] maze = {
//                {1,1,1,1,1,1,1,1,1,1,1,1},
//                {1,0,0,0,1,0,0,0,0,1,0,1}, 
//                {1,0,1,0,0,1,0,1,0,0,0,1}, 
//                {1,0,0,1,0,0,0,1,0,1,1,1}, 
//                {1,1,0,0,0,1,1,1,0,0,1,1}, 
//                {1,0,1,0,1,0,0,1,1,0,1,1}, 
//                {1,0,0,0,1,0,0,1,0,0,0,1}, 
//                {1,0,1,0,0,1,0,0,0,1,0,1}, 
//                {1,0,1,1,0,0,1,1,1,0,0,1}, 
//                {1,0,0,0,1,0,0,0,1,0,1,1}, 
//                {1,0,1,0,0,0,1,0,0,0,1,1},
//                {1,1,1,1,1,1,1,1,1,1,1,1}
//                    }; 
                    
//int [][] root = new int [12][12];

//  void setup() {
//    size (300,300);
//    frameRate(10); 
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
//    rect(180,150,30,30);
    
//    //アニメーションの終了
//    if( x == 6 && y == 5) { 
//      direction = 4;
//      noLoop();
//    }
    
//    //初期値の設定
//    if (count == 0) {
//      fill(red);
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


//【発展課題1】迷路の全探索  途中です！！！
  
int x = 1;
int y = 1;
int count = 0;

color black = color (0);
color white = color (255);
color red = color (255,0,0);
color start = color(0,255,0);
color goal = color (0,0,255);

int [ ][ ] maze = {
                {1,1,1,1,1,1,1,1,1,1,1,1},
                {1,0,0,0,1,0,0,0,0,1,0,1}, 
                {1,0,1,0,0,1,0,1,0,0,0,1}, 
                {1,0,0,1,0,0,0,1,0,1,1,1}, 
                {1,1,0,0,0,1,1,1,0,0,1,1}, 
                {1,0,1,0,1,0,0,1,1,0,1,1}, 
                {1,0,0,0,1,0,0,1,0,0,0,1}, 
                {1,0,1,0,0,1,0,0,0,1,0,1}, 
                {1,0,1,1,0,0,1,1,1,0,0,1}, 
                {1,0,0,0,1,0,0,0,1,0,1,1}, 
                {1,0,1,0,0,0,1,0,0,0,1,1},
                {1,1,1,1,1,1,1,1,1,1,1,1}
                    }; 
                    
boolean check = true;

  void setup() {
    size (300,300);
    frameRate(100); 
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
          //maze[i][j]が0または2の時に実行
          fill(white);
        }
        rect(30 * j, 30 * i, 30, 30);
      }
    }
    
    fill(start);
    rect(30,30,30,30);
    
    fill(goal);
    rect(180,150,30,30);
    
    //アニメーションの終了
    if( x == 6 && y == 5) { 
      noLoop();
    }
    
    //初期値の設定
    if (count == 0) {
      fill(red);
      rect (30, 30, 30, 30);
      maze[x][y] = 2;
    }

    
    //全探索アルゴリズム
    if (count != 0) {
      float dise = random(4);
      //println(int(dise));
      
      switch (int(dise)) {
        
        case 0: //上
          if (maze[y-1][x] == 0 || maze[y-1][x] == 2) {
            y--;
          }
        break;
        
        case 1: //右
          if (maze[y][x+1] == 0 || maze[y][x+1] == 2) {
            x++;
          }
        
        break;
        
        case 2: //下
          if (maze[y+1][x] == 0 || maze[y+1][x] == 2) {
            y++;
          }
        
        break;
        
        case 3://左
          if(maze[y][x-1] == 0 || maze [y][x-1] == 2) {
            x--;
          }
        
        break;

      }
      maze[y][x] = 2;
      fill(red);
      rect(x * 30, y * 30, 30, 30);
      
      for (int i = 0; i < 12; i++) {
        for (int j = 0; j < 12; j++) {
          //println(maze[i][j]);
          if(maze[i][j] == 0) {
            check = false;
          }
        }
      }
    }
    count++;

}
  
    
    
    
    
    
    
    
//【発展課題2】スタートや他所に戻る落とし穴　（落とし穴に落ちた場所を障害物とみなすとか？）
