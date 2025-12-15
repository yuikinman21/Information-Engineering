//AJG23055 牧野唯希
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void replace_and_write (FILE *input_file, FILE *output_file, char target) {
    int c;
    while ((c = fgetc(input_file)) != EOF) {
        if (c == target) {
            fputc(toupper(c), output_file);
        } else {
            fputc(c, output_file);
        }
    }
}

int main (int argc, char *argv[]) {

  if (argc != 4) {
    printf("ERROR\n");
    return 1;
  }

  char *input_filename = argv[1];
  char *output_filename = argv[2];
  char target_char = argv[3][0];

  if (!islower(target_char)) {
    printf("Error\n");
    return 1;
  }

  FILE *input_file = fopen(argv[1], "r");
  if (input_file == NULL) {
      printf("Error");
      return 1;
  }

  FILE *output_file = fopen(argv[2], "w");
  if (output_file == NULL) {
      printf("Error");
      fclose(input_file);
      return 1;
  }

  replace_and_write(input_file, output_file, target_char);
  fclose(input_file);
  fclose(output_file);

  printf("Conversion completed successfully.\n");

    return 0;
}