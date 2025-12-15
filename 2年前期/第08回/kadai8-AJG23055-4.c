#include <stdio.h>
#include <stdint.h>

int main(void) {
    char mychar = 55;
    int mydt = 1234;

    char *pt_c;
    int *pt_i;

    pt_c = &mychar;
    pt_i = &mydt;

    printf("pt_c: %p, %d\n", (void*)pt_c, (int)*pt_c);
    printf("pt_i: %p, %d\n", (void*)pt_i, *pt_i);

    // 各バイトを表示するために、pt_iをcharポインタにキャストしてアクセス
    unsigned char *pt_byte = (unsigned char *)pt_i;
    printf("pt_i first byte: %p, %u\n", (void*)pt_byte, (unsigned int)pt_byte[0]);
    printf("pt_i second byte: %p, %u\n", (void*)pt_byte + 1, (unsigned int)pt_byte[1]);
    printf("pt_i third byte: %p, %u\n", (void*)pt_byte + 2, (unsigned int)pt_byte[2]);
    printf("pt_i fourth byte: %p, %u\n", (void*)pt_byte + 3, (unsigned int)pt_byte[3]);

    return 0;
}
