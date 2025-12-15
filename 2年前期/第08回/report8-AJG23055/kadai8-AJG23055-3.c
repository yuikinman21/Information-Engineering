//AJG23055 牧野唯希

#include <stdio.h>

void replace( int *x, int *y );

int main( void ){
  int a = 10;
  int b = 6;

  printf( "a=%d, b=%d\n",a, b );

  replace( &a, &b );

  printf( "a=%d, b=%d\n",a, b );

  return 0;

}

void replace( int *x, int *y ){

  int z;

  z = *x;
  *x = *y;
  *y = z;

}

