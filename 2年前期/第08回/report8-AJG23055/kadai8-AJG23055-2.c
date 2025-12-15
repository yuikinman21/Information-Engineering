//AJG23055 牧野唯希

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main (void) {
  int n;
  int sum = 0, max, min;
  double ave, var = 0.0, median;

  printf("Enter the number of elements: ");
  scanf("%d", &n);

  int *array = (int *)malloc(n * sizeof(int));
  srand(time(NULL));
  for (int i = 0; i < n; i++) {
    array[i] = rand() % 100;
  }

  max = array[0];
  min = array[0];

  for (int i = 0; i < n; i++) {
    if (array[i] > max) {
      max = array[i];
    }
    if (array[i] < min) {
      min = array[i];
    }
    sum += array[i];
  }

  ave = (double)sum / n;

  for (int i = 0; i < n; i++) {
    var += (array[i] - ave) * (array[i] - ave);
  }
  var /= n;

  for (int i = 0; i < n - 1; i++) {
    for (int j = 0; j < n - i - 1; j++) {
      if (array[j] > array[j + 1]) {
        int temp = array[j];
        array[j] = array[j + 1];
        array[j + 1] = temp;
      }
    }
  }
  
  if (n % 2 == 0) {
    median = (array[n / 2 - 1] + array[n / 2]) / 2.0;
  } else {
    median = array[n / 2];
  }

  printf("Maximum: %d\n", max);
  printf("Minimum: %d\n", min);
  printf("Average: %.2f\n", ave);
  printf("Variance: %.2f\n", var);
  printf("Median: %.2f\n", median);
  
  free(array);
  return 0;
}