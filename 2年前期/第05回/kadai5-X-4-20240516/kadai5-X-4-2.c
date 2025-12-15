#define MAX_STACK 64//スタックに入れられる最大の要素数

#include <stdio.h>
#include <stdlib.h>

//pop 関数．
// s[]: スタックを表現する配列
// l[2]: l[0] がスタックの長さを表し，l[1] がpop した後のスタックの長さ 
int pop( int s[], int l[2] );

//print_stack 関数
//スタックに積んだ数値を出力する関数
// s[]: スタックを表現する配列
//   l: スタックの長さ
void print_stack( int s[], int l );

int main( void ){
  int stack[ MAX_STACK ];//スタックを表現する配列
  int len = 0;//スタックの長さ．最初はスタックに何も積まれていないので0
  int val;//pop されてきた整数を格納する変数
  int l[ 2 ];//pop の時に使う新旧のスタックの長さを代入する配列．l[0] スタックの長さ，l[1] pop 後のスタックの長さ
  int i;
  
  //テスト用にスタックに予め4つほど整数を積んでおく
  stack[0] = 1;
  stack[1] = 2;
  stack[2] = 3;
  stack[3] = 4;
  //スタックの長さは4
  len = 4;
  
  // スタックの長さを保存
  l[0]=len;
  l[1]=len-1;

  //スタック表示
  print_stack( stack, len );

  //4回スタックからpop する
  for( i=0; i<4; i++ ){
    val = pop( stack, l );
	len = l[0];
    printf( "%d\n", val );
    //スタック表示
    print_stack( stack, len );
  }
  
  return 0;
}

int pop( int s[], int l[2] ){
  
  int val = 0;//popした値
  l[1]=l[0];
  //////////ここからpop 関数の中身を書いて下さい．////////////////////////////////
  


  //////////////////////////ここまで///////////////////////////////////////////
  return val;
}

void print_stack( int s[], int l ){
  int i;
  if( l < 0 ){
    printf( "The length of the stack should be positive.\n" );
    exit( -1 );
  }
  else{
    printf( "[" );
    for( i=0; i<l; i++ ){
      printf( "%d", s[i] );
      if( i != ( l-1 ) ){
	printf( " " );
      }
    }
    printf( "]\n" );
  }
}
