
/*
学籍番号: 
氏名: 
*/

//Add if necessary
#include <iostream>
#include <stdio.h>
#include <stdlib.h>


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




    // Gram-Schmidt & QR decomposition
    // write here...


    
    
    /* print the matrix Q resulting from gramSchmidt_QRdecomposition */
    std::cout << "Q = " << std::endl;
    std::cout << std::endl;
    // write here...





    /* print the matrix R resulting from gramSchmidt_QRdecomposition */
    std::cout << "R = " << std::endl;
    std::cout << std::endl;
    // write here...




    
    /* print the matrix Q * R */
    std::cout << "Q * R = ?" << std::endl;
    std::cout << std::endl;
    // write here...





    
    /* print Input_mat - (Q * R) */
    std::cout << "Input_mat - (Q * R) = ?" << std::endl;
    std::cout << std::endl;
    // write here...
    
    
    


    return 0;
}
