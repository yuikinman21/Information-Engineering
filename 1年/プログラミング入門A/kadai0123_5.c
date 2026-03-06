//AJG23055 牧野唯希


#include <stdio.h>

void trans (int a[3][3]) {
  int i,j;
  int trans[3][3];
  for(i = 0; i < 3; i++){
    for(j = 0; j < 3; j++){
     trans[j][i]=a[i][j];
    }
  }

  printf ("\ntM = \n");
  for(i = 0; i < 3; i++){
    for(j = 0; j < 3; j++){
      printf("%d  ",trans[i][j]);
      if(j == 2)
          printf("\n");
    }
  }
}

int main(void){

  int i, j;

  int m[3][3] = {{1, 3, 5}, {7, 9, 2}, {4, 6, 8}};

  printf("\nM = \n");
  for(i = 0; i < 3; i++){
    for(j = 0; j < 3; j++){
      printf("%d  ", m[i][j]);
      if(j == 2)
          putchar ('\n');
    }
  }

  trans(m);

  return 0;

}