//AJG23055 牧野唯希

#include <stdio.h>
#include <string.h>
#define NUMBER 3

typedef struct persons {
  char name [30];
  int height;
  float weight;
  float bmi;
} Person;

//関数については教科書p343を参考にした。

void swap_Person(Person *x, Person *y) {
  Person temp = *x;
  *x = *y;
  *y = temp;
}

void sort_by_height(Person a[], int n) {
  for (int i = 0; i < n - 1; i++) {
    for (int j = n - 1; j > i; j--) {
      if (a[j - 1].height < a[j].height) {
        swap_Person(&a[j - 1], &a[j]);
      }
    }
  }
}

void sort_by_weight(Person a[], int n) {
  for (int i = 0; i < n - 1; i++) {
    for (int j = n - 1; j > i; j--) {
      if (a[j - 1].weight > a[j].weight) {
        swap_Person(&a[j - 1], &a[j]);
      }
    }
  }
}

void sort_by_bmi(Person a[], int n) {
  for (int i = 0; i < n - 1; i++) {
    for (int j = n - 1; j > i; j--) {
      if (a[j - 1].bmi < a[j].bmi) {
        swap_Person(&a[j - 1], &a[j]);
      }
    }
  }
}

int main (void) {

  Person p[NUMBER] = {
    {"Oda", 180, 70.0, 21.6},
    {"Date", 165, 55.5, 20.4},
    {"Sanada", 170, 66.3, 22.9},
  };

  sort_by_height(p, NUMBER);

  puts("身長の高い順に並び変えました。\n");
  for (int i = 0; i < NUMBER; i++) {
      printf("%-8s %6d\n", p[i].name, p[i].height);
  }

  putchar('\n');
  
  sort_by_weight(p, NUMBER);

  puts("体重の低い順に並び変えました。\n");
  for (int i = 0; i < NUMBER; i++) {
      printf("%-8s %6.1f\n", p[i].name, p[i].weight);
  }

  sort_by_bmi(p, NUMBER);

  putchar('\n');

  puts("BMIの高い順に並び変えました。\n");
  for (int i = 0; i < NUMBER; i++) {
      printf("%-8s %6.1f\n", p[i].name, p[i].bmi);
  }
  // for (i = 0; i < 3; i++) {
  //   printf("%s's BMI is %.1f\n", p[i].name, p[i].weight * 10000 / (p[i].height * p[i].height));
  //   }

  return 0;
}