//AJG23055 牧野唯希
#include <stdio.h>
#include <string.h>

typedef struct persons {
  char name [30];
  int height;
  float weight;
} Person;

int main (void) {

  Person p[5] = {
    {"Oda", 180, 70.0},
    {"Date", 165, 55.5},
    {"Sanada", 170, 66.3},
    {"Tokugawa", 160, 50.0},
    {"Toyotomi", 175, 60.0}
  };
  
  int i;
  float bmi;
  char name[30];

  for (i = 0; i < 5; i++) {
    printf("name%d: %s\n", i + 1, p[i].name);
  }
  putchar('\n');

  do {
    printf("Please enter name: ");
    scanf("%s", name);
    
    for (i = 0; i < 5; i++) {
      if (strcmp(name, p[i].name) == 0) {
        printf("%s's BMI is %.1f\n", p[i].name, p[i].weight * 10000 / (p[i].height * p[i].height));
      } 
    }
  
  } while (strcmp(name, "Oda") != 0 && strcmp(name, "Date") != 0 && strcmp(name, "Sanada") != 0 && strcmp(name, "Tokugawa") != 0 && strcmp(name, "Toyotomi") != 0);
  
  return 0;
}