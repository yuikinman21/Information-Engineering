//AJG23055 牧野唯希

#include <stdio.h>
enum WEEK {Monday, Tuesday, Wednesday, Thursday, Friday, Saturday, Sunday};

int main (void) {
  enum WEEK key;
  do {
    printf("Monday = 0, Tuesday = 1, Wednesday = 2, Thursday = 3, Friday = 4, Saturday = 5, Sunday = 6\n");
    printf("WEEK:");
    scanf(" %d", &key);

    switch (key) {
      case 0:
        printf("1:\n2:\n3:\n4:\n5:信号処理論\n");
        break;
  
      case 1:
        printf("1:電気回路入門\n2:\n3:常微分方程式\n4:\n5:\n");
        break;
  
      case 2:
        printf("1:基礎熱力学\n2:プログラミング言語概論\n3:\n4:応用物理実験\n5:応用物理実験\n");
        break;
  
      case 3:
        printf("1:情報理論A\n2:情報数学\n3:\n4:情報工学演習1\n");
        break;
  
      case 4:
        printf("1:基礎力学B2\n2:University English 3B\n3:\n4:\n5:\n");
        break;
  
      case 5:
        printf("白鷺祭\n");
        break;
  
      case 6:
        printf("白鷺祭\n");
        break;
  
      default:
        printf("Error! Please try again!\n");
        break;
    }
  } while (key < 0 || key > 6);
  
}