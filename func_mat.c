//AJG23055 牧野唯希
#include <stdio.h>

void calc_mat (int a[3][3], int b[3][3]) {
  int result[3][3] = {0};
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      for (int k = 0; k < 3; k++) {
        result[i][j] += a[i][k] * b[k][j];
      }
    }
  }
  
  puts("AB=");
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      printf("%4d", result[i][j]);
    }
    putchar('\n');
  }
}

int main(void) {
  int A[3][3] = {
  {3,0,1},
  {1,2,0},
  {0,1,-1}
  };

  int B[3][3] = {
  {1,2,3},
  {4,5,6},
  {7,8,9}
  };

  calc_mat(A, B);
  
  return 0;
}