//AJG23055 牧野唯希

#include <stdio.h>

#define sq(a) a*a
#define sq_fixed(a) ((a)*(a))

int main(void) {

  int result = sq(5+2);
  int result_fixed= sq_fixed(5+2);
  
  printf("Original:a*a=%d\n",result);
  printf("Fixed   :a*a=%d\n",result_fixed);

  return 0;
}