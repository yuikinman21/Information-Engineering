//AJG23055 牧野唯希
#define MAX_STACK 64//スタックに入れられる最大の要素数

#include <stdio.h>
#include <stdlib.h>

//push 関数．
// s[]: スタックを表現する配列
//   l: スタックの長さ
// val: スタックに格納される整数
//戻り値はスタックにval を積んだあとのスタックの長さ
int push( int s[], int l, int v );

//print_stack 関数
//スタックに積んだ数値を出力する関数
// s[]: スタックを表現する配列
//   l: スタックの長さ
void print_stack( int s[], int l );

int main (void) {
  int stack[ MAX_STACK ];//スタックを表現する配列
  int len = 0;//スタックの長さ．最初はスタックに何も積まれていないので0
  int val;//スタックに積む整数

  //1をスタックに積む
  val = 1;
  len = push( stack, len, val );
  //確認
  print_stack( stack, len );

  //2をスタックに積む
  val = 2;
  len = push( stack, len, val );
  //確認
  print_stack( stack, len );

  //3をスタックに積む
  val = 3;
  len = push( stack, len, val );
  //確認
  print_stack( stack, len );

  //4をスタックに積む
  val = 4;
  len = push( stack, len, val );
  //確認
  print_stack( stack, len );

  return 0;
}

int push( int s[], int l, int val ){
  
  int n_val_update = 0;//スタックにval を積んだあとのスタックの長さ
  /////////////////ここからpush 関数の中身を書いて下さい///////////////////////////
  if (l < MAX_STACK) {
    s[l] = val;
    l++;
  } else {
    printf("ERROR!\n");
    exit(1);
  }
    n_val_update = l;
  /////////////////////////ここまで//////////////////////////////////////////////
  return n_val_update;
}

void print_stack( int s[], int l ){
  int i;
  if( l < 0 ){
    printf( "The length of the stack should be positive.\n" );
    exit(1);
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
