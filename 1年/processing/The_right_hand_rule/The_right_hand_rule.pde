//【課題】右手の法則による迷路探索
  
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
    
    //右手の法則

    fill(red);

    if (count > 0) {
      switch (direction) {
        case 0: //上を向いているとき
          if (maze[y][x+1] == 0) {
            x++;
            direction = 1;
          } 
          else if (maze[y-1][x] == 0) {
            y--;
            
          } 
          else if (maze[y][x-1] == 0) {
            x--;
            direction = 3;
          }else {
            
            direction = 2;
          }
        break;
        
        case 1: //右を向いているとき
          if (maze[y+1][x] == 0) {
            y++;
            direction = 2;
          } 
          else if (maze[y][x+1] == 0) {
            x++;
            
          } 
          else if (maze[y-1][x] == 0) {
            y--;
            direction =0;
          }
          else {
            direction = 3;
          }
        break;
        
        case 2: //下を向いているとき
          if (maze[y][x-1] == 0) {
            x--;
            direction = 3;
          }
          else if (maze[y+1][x] == 0) {
            y++;
            
          }
          else if (maze[y][x+1] == 0) {
            x++;
            direction = 1;
          }
          else {
            
            direction = 0;
          }
          
        break;
        
        case 3: //左を向いているとき
          if (maze[y-1][x] == 0) {
            y--;
            direction = 0;
          }
          else if (maze[y][x-1] == 0) {
            x--;
            
          }
          else if (maze[y+1][x] == 0) {
            y++;
            direction = 2;
          }
          else {
            direction = 1;
          }
          
        break;
      }
      rect(x * 30, y * 30, 30, 30);      
    }
    count++;
    println(direction);
  }
