//AJG23055 牧野唯希

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENT 100
#define SIZE 256

typedef struct {
  char student_id[SIZE];
  char last_name[SIZE];
  char first_name[SIZE];
  char birthday[SIZE];
  char phone_number[SIZE];
} Student;

Student students[MAX_STUDENT];
int student_count = 0;

void load_first_date(const char *file_name) {
  FILE *file = fopen(file_name, "r");
  if (file == NULL) {
    printf("Failed to open file.\n");
    return;
  }

  while (fscanf(file, "%s %s %s %s %s", students[student_count].student_id,students[student_count].last_name,students[student_count].first_name,students[student_count].birthday,students[student_count].phone_number) == 5) {
    student_count++;
  }
  fclose(file);
}

void add_student() {
  if (student_count >= MAX_STUDENT) {
    printf("Maximum number of students reached.\n");
    return;
  }
  
  Student new_student;
  printf("Enter student ID: ");
  scanf("%s", new_student.student_id);

  for (int i = 0; i < student_count; i++) {
    if (strcmp(students[i].student_id, new_student.student_id) == 0) {
      printf("Error: Student ID already exists.\n");
      return;
    }
  }
  printf("Enter last name: ");
  scanf("%s", new_student.last_name);
  printf("Enter first name: ");
  scanf("%s", new_student.first_name);
  printf("Enter birthday: ");
  scanf("%s", new_student.birthday);
  printf("Enter phone number: ");
  scanf("%s", new_student.phone_number);

  students[student_count] = new_student;
  student_count++;
}

void delete_student() {
  char student_id[SIZE];
  printf("Enter student ID to delete: ");
  scanf("%s", student_id);
  int found = 0;
  for (int i = 0; i < student_count; i++) {
    if (strcmp(students[i].student_id, student_id) == 0) {
      found = 1;
      for (int j = i; j < student_count - 1; j++) {
        students[j] = students[j + 1];
      }
      student_count--;
      printf("Student deleted.\n");
      break;
    }
  }

  if (!found) {
    printf("Student not found.\n");
  }
}

void search_student() {
  char search_term[SIZE];
  printf("Enter search_term:");
  scanf("%s", search_term);

  int found = 0;
  for (int i = 0; i < student_count; i++) {
    if (strstr(students[i].student_id, search_term) ||
      strstr(students[i].last_name, search_term) ||
      strstr(students[i].first_name, search_term) ||
      strstr(students[i].birthday, search_term) || 
      strstr(students[i].phone_number, search_term)) {

      putchar('\n');
      printf("Student found!\n");
      putchar('\n');
      printf("Student ID: %s\n", students[i].student_id);
      printf("Last Name: %s\n", students[i].last_name);
      printf("First Name: %s\n", students[i].first_name);
      printf("Birthday: %s\n", students[i].birthday);
      printf("Phone Number: %s\n", students[i].phone_number);
      putchar('\n');
      found = 1;
    }
  }

  if (!found) {
    printf("No student found.\n");
  }
}


int main (int argc, char *argv[]) {
  if (argc != 2) {
    printf("ERROR!\n");
    return 1;
  }

  load_first_date(argv[1]);

  while(1) {
    int choice;
    printf("1. Add student, 2. Delete student, 3. Search student, 4. Exit\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
      case 1:
        add_student();
      break;

      case 2:
        delete_student();
      break;
      
      case 3:
        search_student();
      break;

      case 4:
        printf("Exiting program.\n");
        return 0;
      default:
        printf("Invalid choice. Please try again.\n");
    }
  }
  return 0;
}