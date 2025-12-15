//AJG23055 牧野唯希
//実行時間を計る部分はスライドを参考にしながら作成した。実行結果に明確な差が生まれて良かった。実行回数を増やすとさらに差が明確になった。

#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

struct sum_n {
    int n[10000];
    int num;
};

int sum(sum_n s) {
    int i, sum = 0;
    for (i = 0; i < s.num; i++) {
        sum += s.n[i];
    }
    return sum;
}

void sum_reference(sum_n &s) {
    int i, sum = 0;
    for (i = 0; i < s.num; i++) {
        sum += s.n[i];
    }
    s.n[s.num] = sum;
}


int main (void) {
    clock_t start, end;
    double diff;
    int a;
    long l;
    
    sum_n s;
    int i;
    s.num = 1000;
    srand(time(NULL));
    for (i = 0; i < 1000; i++) {
        s.n[i] = rand() % 1000 + 1;
    }

    start = clock();
    cout << sum(s) << endl;
    end = clock();
    diff = (double)(end - start)/CLOCKS_PER_SEC;
    cout << "sum():" << diff << "ms" << endl;
    
    start = clock();
    sum_reference(s);
    cout << s.n[s.num] << endl;
    end = clock();
    diff = (double)(end - start)/CLOCKS_PER_SEC;
    cout << "sum_reference():" << diff << "ms" << endl;
}