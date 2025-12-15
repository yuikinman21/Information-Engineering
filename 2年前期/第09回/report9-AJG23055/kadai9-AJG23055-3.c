//AJG23055 牧野唯希

#include <stdio.h>

#define N 5

// 学生の研究室希望リスト
int student_pres[N][N] = {
    {2, 1, 4, 3, 0},
    {3, 1, 4, 2, 0},
    {2, 1, 0, 4, 3},
    {0, 2, 1, 4, 3},
    {3, 0, 1, 2, 4}
};

// 研究室の学生希望リスト
int lab_pres[N][N] = {
    {0, 3, 2, 1, 4},
    {4, 1, 2, 0, 3},
    {3, 2, 0, 4, 1},
    {3, 2, 4, 1, 0},
    {3, 2, 0, 1, 4}
};

// 学生と研究室の配属状況
int student_wariate[N];
int lab_wariate[N];

void first_wariate() {
    for (int i = 0; i < N; i++) {
        student_wariate[i] = -1;
        lab_wariate[i] = -1;
    }
}
//-1は未所属の意味

int find_student_pre_rank(int lab, int student) {
    for (int i = 0; i < N; i++) {
        if (lab_pres[lab][i] == student) {
            return i;
        }
    }
    return -1;
}

void assign_students() {
    int free_students = N;

    while (free_students > 0) {
        for (int student = 0; student < N; student++) {
            if (student_wariate[student] == -1) {
                for (int choice = 0; choice < N; choice++) {
                    int preferred_lab = student_pres[student][choice];
                    if (lab_wariate[preferred_lab] == -1) {
                        student_wariate[student] = preferred_lab;
                        lab_wariate[preferred_lab] = student;
                        free_students--;
                        break;
                    } else {
                        int current_student = lab_wariate[preferred_lab];
                        int current_rank = find_student_pre_rank(preferred_lab, current_student);
                        int new_rank = find_student_pre_rank(preferred_lab, student);

                        if (new_rank < current_rank) {
                            student_wariate[current_student] = -1;
                            student_wariate[student] = preferred_lab;
                            lab_wariate[preferred_lab] = student;
                            break;
                        }
                    }
                }
            }
        }
    }
}

void print_wariate() {
    for (int i = 0; i < N; i++) {
        printf("学生 %d は 研究室 %d に配属されました\n", i, student_wariate[i]);
    }
}

int main() {
    first_wariate();
    assign_students();
    print_wariate();
    return 0;
}
