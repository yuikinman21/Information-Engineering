
/*
学籍番号:AJG23055 
氏名: 牧野唯希
*/

//Add if necessary
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


using namespace std;



int main () {
    
    
    /* input data for QR decomposition */
    double input_mat[][5] = {
        {2.3, -2.1, 8.0, 5.0, -4.1},
        {2.8, 1.3, 1.0, -9.2, -1.0},
        {1.1, 2.9, 3.1, -2.1, 5.1},
        {-2.1, -6.0, -2.1, 2.0, 3.0},
        {7.0, 0.5, -2.1, 2.0, -5.0},
    };


    
    
    /* print the input_mat before calling gramSchmidt_QRdecomposition */
    std::cout << "input_mat = " << std::endl;
    std::cout << std::endl;
    // write here...

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            printf("%7.3f ", input_mat[i][j]);
        }
        cout << endl;
    }

    // Gram-Schmidt & QR decomposition
    // write here...
    double Q[5][5], R[5][5];
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            Q[i][j] = input_mat[i][j];
            R[i][j] = 0;
        }
    }

    for (int j = 0; j < 5; j++) {
        for (int k = 0; k < j; k++) {
            double dot = 0;
            for (int i = 0; i < 5; i++) {
                dot += Q[i][j] * Q[i][k];
            }
            R[k][j] = dot;
            for (int i = 0; i < 5; i++) {
                Q[i][j] -= dot * Q[i][k];
            }
        }
        double norm = 0;
        for (int i = 0; i < 5; i++) {
            norm += Q[i][j] * Q[i][j];
        }
        norm = sqrt(norm);
        R[j][j] = norm;
        for (int i = 0; i < 5; i++) {
            Q[i][j] /= norm;
        }
    }

    
    
    /* print the matrix Q resulting from gramSchmidt_QRdecomposition */
    std::cout << "Q = " << std::endl;
    std::cout << std::endl;
    // write here...
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            printf("%7.3f ", Q[i][j]);
        }
        cout << endl;
    }

    /* print the matrix R resulting from gramSchmidt_QRdecomposition */
    std::cout << "R = " << std::endl;
    std::cout << std::endl;
    // write here...

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            printf("%7.3f ", R[i][j]);
        }
        cout << endl;
    }

    /* print the matrix Q * R */
    std::cout << "Q * R = ?" << std::endl;
    std::cout << std::endl;
    // write here...

    double QR[5][5];
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            QR[i][j] = 0;
            for (int k = 0; k < 5; k++) {
                QR[i][j] += Q[i][k] * R[k][j];
            }
            printf("%7.3f ", QR[i][j]);
        }
        cout << endl;
    }
    
    /* print Input_mat - (Q * R) */
    std::cout << "Input_mat - (Q * R) = ?" << std::endl;
    std::cout << std::endl;
    // write here...
    
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            printf("%7.3f ", input_mat[i][j] - QR[i][j]);
        }
        cout << endl;
    }

    return 0;
}
