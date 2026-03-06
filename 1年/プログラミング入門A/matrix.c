//AJG23055　牧野唯希
#include <stdio.h>

int main (void) {
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

  int sum[3][3] = {0};
  int result[3][3] = {0};

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      sum[i][j] = A[i][j] + B[i][j];
    }
  }

  puts("A+B=");
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      printf("%4d", sum[i][j]);
    }
    putchar('\n');
  }
  
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      for (int k = 0; k < 3; k++) {
        result[i][j] += A[i][k] * B[k][j];
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