int main() {
  int *n;
  n = new int[10]; // int型の変数10個分のメモリ確保
  delete [] n; // 確保したメモリの開放
  return 0;
}

