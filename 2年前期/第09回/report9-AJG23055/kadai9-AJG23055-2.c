// AJG23055 牧野唯希

#include "kadai9-AJG23055-2.h"
#include <stdio.h>
#include <math.h>

extern int n;

double length(double vector[]) {
  double length = 0.0;
  for (int i = 0; i < n; i++) {
    length += vector[i] * vector[i];
  }
  length = sqrt(length);
  return length;
}

void unit_vector(double vector[], double unit_vector[]) {
    double vector_length = length(vector);
    for (int i = 0; i < n; i++) {
        unit_vector[i] = vector[i] / vector_length;
    }
  for (int i = 0; i < n; i++) {
    printf("%lf ", unit_vector[i]);
  }
}

double naiseki(double vector1[], double vector2[]) {
  double result = 0.0;
  for (int i = 0; i < n; i++) {
    result += vector1[i] * vector2[i];
  }
  return result;
}

double henkaku(double vector1[], double vector2[]) {
  double henkaku;
  double length_vector1 = length(vector1);
  double length_vector2 = length(vector2);
  double naiseki_result = naiseki(vector1, vector2);

  henkaku = naiseki_result / (length_vector1 * length_vector2);
  return acos(henkaku);
}
