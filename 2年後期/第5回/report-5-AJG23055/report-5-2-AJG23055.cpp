//AJG23055 牧野唯希

#include<stdio.h>
#define N 2000


int sumDivisor(int i) {
    int j;
    int sum = 1;

    for (j = 2; j < i; j++) {
        if (i % j == 0) {
            sum += j;
        }
    }
    return sum;
}
int main(void) {
    int i, k;

    printf("友愛数:");
    for (i = 1; i <= N; i++) {
        k = sumDivisor(i);
        if (i == sumDivisor(k) && i < k) {
            printf("(%d：%d), ", i, k);
        }
    }
    printf("\n");
  
    return 0;
}