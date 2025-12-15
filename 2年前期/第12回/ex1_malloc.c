#include <stdlib.h> /* mallocを使うときのお約束 */

int main() {
  int *n;
  n = (int *)malloc(sizeof(int)*10); /* int型の変数10個分のメモリ確保 */
  free(n); /* 確保したメモリの開放 */
  return(0);
}

