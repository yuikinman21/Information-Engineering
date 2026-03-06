//AJG23055 牧野唯希
#include <stdio.h>
#include <string.h>

typedef struct Player{
  char name[40];
  int number;
  char position[3];

}Player;

int main(void){
  
  Player p[11] = {
  {"Gonda",12,"GK"},
  {"Miura",2,"DF"},
  {"Muroya",3,"DF"},
  {"Yamanaka",5,"DF"},
  {"Makino",20,"DF"},
  {"Haraguchi",8,"MF"},
  {"Ito",14,"MF"},
  {"Morita",17,"MF"},
  {"Misao",18,"FW"},
  {"Sugimoto",11,"FW"},
  {"Kitagawa",13,"FW"}
  };
  
  char word[30];

  do {
  printf("Please enter: (number,position)\n");
  scanf("%s", word);
    
      if(strcmp(word,"number") == 0){
        for (int i = 0; i < 11; i++) {
          printf("%s %d\n", p[i].name, p[i].number);
        }
      } else if (strcmp(word,"position") == 0) {
        for (int i = 0; i < 11; i++) {
          printf("%s %s\n", p[i].name, p[i].position);
        }
      } else {
        printf("ERROR! Please Try Again!\n");
      }
  } while (strcmp(word,"number") != 0 && strcmp(word,"position") != 0);

  return 0;
}
