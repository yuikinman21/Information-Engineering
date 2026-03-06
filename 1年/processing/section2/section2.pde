//Proseccingでの図形の描画

//size(300, 200);
//ellipse(100, 100, 160, 160);
//rect(100, 100, 80, 80);
//line(0, 0, 100, 100); 



//【課題】Processingでの色の描画　例 

//size(250,250);

//color red = color(255,0,0);
//color black = color (0,0,0);
//color white = color (255,255,255);
//color blue = color (0,0,255);

//fill(red);
//rect(0,0,50,50);

//fill(black);
//rect(50,0,50,50);
//rect(100,0,50,50);

//fill(white);
//rect(0,50,50,50);
//rect(50,50,50,50);

//fill(black);
//rect(100,50,50,50);
//rect(0,100,50,50);

//fill(white);
//rect(50,100,50,50);

//fill(blue);
//rect(100,100,50,50);



//変数と繰り返し構文　例

 //int a, b, c;
 //a=5; b=2; c=a+b;
 //println("a=", a);
 //println("b=", b);
 //println("a+b=", a+b);
 //println("a+b=", c); 
 
 
 
//for文の例
  //size (300,300);
  //int i;
  // for(i=0; i<5; i++){
  // fill(255-50*i, 0, 50*i);
  // rect(10*i*2, 10*i*2,100-10*i, 100-10*i);
  // }


//【課題】for 文 (10*10の格子)

  //size (300,300);

  //for (int i = 0; i < 10; i++) {
  //  for ( int k = 0; k < 10; k++) {
  //    rect (i * 30,k * 30,30,30);
  //  }
  //}
  
 
 
 //条件分岐
 //size (500,500);
 
 //   int i;
 //  for(i=0; i<10; i++){
 //  if(i%2==0){
 //  fill(255,0,0);
 // rect(30*i, 0, 30, 30);
 //  }
 // else{
 // fill(0,0,255);
 // ellipse(15+30*i, 15, 30, 30);
 // }
 //  } 
 
 
 
//【課題】条件分岐 (白黒) //<>// //<>// //<>// //<>//
 
  size (300,300);
 
  color white = color (255,255,255);
  color black = color (0,0,0);

  for (int i = 0; i < 10; i++) {
    for ( int k = 0; k < 10; k++) {
      if ((i + k) % 2 == 0)
        fill (white);
      else 
        fill (black);
      rect(i * 30,k * 30,30,30);
    }
  }
  
 //【おまけ】リファクタリングby ChatGPT
 
// size(300, 300);

//color white = color(255);
//color black = color(0);

//int gridSize = 10;
//int squareSize = 30;

//for (int i = 0; i < gridSize; i++) {
//  for (int k = 0; k < gridSize; k++) {
//    fill((i + k) % 2 == 0 ? white : black);
//    rect(i * squareSize, k * squareSize, squareSize, squareSize);
//  }
//}
