//AJG23055 牧野唯希

#include <stdio.h>
#include <stdlib.h>

//データのセルの構造体
typedef struct _CELL{
  int data;
  struct _CELL* next;
} CELL;

//空のセルを作成する．
CELL* create_cell( void );
//連結リストでpの後にデータを挿入する．
void insert( CELL* p, int data);
//p が指す要素の次の要素を消去して，メモリも削除する
void delete( CELL* p );

//2つの連結リストをくっつける
void combine( CELL* header1, CELL* header2 );
//1つの連結リストを2つに分割する．
void divide( CELL* header1, CELL* header2, CELL* p );

//連結リストの出力
void print_list( CELL* header );
//リストをすべて消去してメモリをリリースする
void release_list( CELL* header );

int main( int argc, char* argv[] ){

  //先頭は構造体の実態（中に入っているデータはゴミ）で表現．
  CELL header, header2;
  CELL *p, *p_prev;
  int data;
  FILE* fp;

  header.next = NULL;
  //コマンドライン引数で指定したファイルを読み込む
  if( ( fp = fopen( argv[1], "r" ) ) ==NULL ){
    printf( "cannot open the file!: %s\n", argv[1] );
    exit( -1 );
  }

  p = &header;
  //データを読み込む
  while( fscanf( fp, "%d", &data ) !=EOF ){
    //insert 関数で末尾にデータを付加することで，連結リストのデータを読み込む．
    insert( p, data );
    p = p->next;
  }

  fclose( fp );

  //ファイルから読み込んだ結果を出力
  printf( "Initial list:\n" );
  print_list( &header );

  //連結リストから30を見つける
  p = &header;
  while( p->next != NULL ){
    p = p->next;
    if( p->data == 30 ){
      break;
    }
  }
  //連携リストの30 の後に18 を挿入する．
  insert( p, 18 );
  printf( "Insert 18 after 30\n" );
  print_list( &header );


  //連結リストを30 の後で分割
  divide( &header, &header2, p );

  //分割したリストの表示
  printf( "Divide the list after 30.\n" );  
  print_list( &header );
  print_list( &header2 );

  //2つの連結リストを分割した時と前後を逆にして統合
  combine( &header2, &header );

  printf( "Combine the lists\n" );
  //統合したリストを出力
  print_list( &header2 );
  //こちらは空．試しに表示する
  print_list( &header );

  //連結リストから100 を見つける．
  p = &header2;
  while( p->next != NULL ){
    p_prev = p;
    p=p->next;
    if( p->data == 100 ){
      break;
    }
  }
  //100の要素を消去
  delete( p_prev );
  //消去した結果を出力
  printf( "Delete 100 from the list.\n" );
  print_list( &header2 );

  //リストのすべてを開放
  release_list( &header2 );

  //念のため全部開放されたか出力
  printf( "Release the list.\n" );
  print_list( &header2 );

  return 0;
}

//////////////////以下の関数を完成させて下さい．//////////////////////////////////////

CELL* create_cell(void) {
    CELL *p = (CELL*)malloc(sizeof(CELL));
    if (p == NULL) {
        perror("Failed to allocate memory");
        exit(EXIT_FAILURE);
    }
    p->next = NULL;
    return p;
}

void insert(CELL* p, int data) {
    CELL *new_cell = create_cell();
    new_cell->data = data;
    new_cell->next = p->next;
    p->next = new_cell;
}

void delete(CELL* p_prev) {
    if (p_prev->next != NULL) {
        CELL *to_delete = p_prev->next;
        p_prev->next = to_delete->next;
        free(to_delete);
    }
}

void combine(CELL* header1, CELL* header2) {
    CELL *p = header1;
    while (p->next != NULL) {
        p = p->next;
    }
    p->next = header2->next;
    header2->next = NULL;
}

void divide(CELL* header1, CELL* header2, CELL* p) {
    header2->next = p->next;
    p->next = NULL;
}

void release_list(CELL* header) {
    CELL *p = header->next;
    while (p != NULL) {
        CELL *to_delete = p;
        p = p->next;
        free(to_delete);
    }
    header->next = NULL;
}
//////////////////////作成する関数ここまで/////////////////////////////

///////////////////リストを出力する関数//////////////////////
void print_list(CELL* header) {
    CELL *p = header->next;
    if (p == NULL) {
        printf("The list is empty.\n");
    } else {
        while (p != NULL) {
            printf("%d ", p->data);
            p = p->next;
        }
        printf("\n");
    }
}
