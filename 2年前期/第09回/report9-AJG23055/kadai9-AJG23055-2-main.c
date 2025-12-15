//AJG23055 牧野唯希

#include <stdio.h>
#include <math.h>

#include "kadai9-AJG23055-2.h"

int n;

int main(void) {
    printf("n=");
    scanf("%d", &n);

    double vector1[n], vector2[n];

    printf("vector1\n");
    for (int i = 0; i < n; i++) {
        printf("v1[%d]=", i + 1);
        scanf("%lf", &vector1[i]);
    }

    printf("vector2\n");
    for (int i = 0; i < n; i++) {
        printf("v2[%d]=", i + 1);
        scanf("%lf", &vector2[i]);
    }

    double length_vector1 = length(vector1);
    double length_vector2 = length(vector2);

    printf("length_vector1=%lf\n", length_vector1);
    printf("length_vector2=%lf\n", length_vector2);

    double e_vector1[] = {0.0}, e_vector2[] = {0.0}; 
    printf("e_vector1\n");
    unit_vector(vector1, e_vector1);
    printf("\ne_vector2\n");
    unit_vector(vector2, e_vector2);
    putchar('\n');
    double naiseki_value = naiseki(vector1, vector2);
    printf("naiseki=%lf\n", naiseki_value);

    double henkaku_value = henkaku(vector1, vector2);
    printf("henkaku=%lf\n", henkaku_value);

    return 0;
}
