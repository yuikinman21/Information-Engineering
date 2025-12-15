#include <stdio.h>

int main(void) {
  char mychar = 55;
  int mydt = 1234;

  char *pt_c;
  int *pt_i;
  char *pt_c2;
  
  pt_c = &mychar;
  pt_i = &mydt;
  pt_c2 = (char*)pt_i;
  
  printf( "pt_c: %p, %d\n", pt_c, (int)*pt_c );
  printf( "pt_i: %p, %d\n", pt_i, *pt_i );
  printf( "pt_c2: %p, %d\n", pt_c2, (int)*pt_c2 );

  return 0;
}
