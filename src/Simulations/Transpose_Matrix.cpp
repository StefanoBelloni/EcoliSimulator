//
//  Transpose_Matrix.cpp
//  EColi_3.1.2
//
//  Created by Stefano Belloni on 01/07/15.
/*This program is free software - GNU General Public License Verison 2*/
//

#include <iostream>
#include <iomanip>

using namespace std;

/**This function calculate the transpose of a Matrix
 * @param U pointer to the original matrix
 * @param U_T pointer to the traspose matrix
 */

void Transpose_Matrix(long double *U, long double *U_T, int n_x, int n_y, long double &f_max){
    
    for (int i=0; i<n_x; i++) {
        for (int j=0; j<n_y; j++) {
            U_T[j*n_x+i]=U[i*n_y+j];
            f_max = std::max(U_T[j*n_x+i], f_max);
        }
    }
    
    
}

/**This function print a matrix in a tidy way*/
void print_matrix(long double *U, int n_x, int n_y){
    
    for (int i=0; i<n_x; i++) {
        for (int j=0; j<n_y; j++) {
            std::cout << setw(4) << setiosflags(ios::fixed) << setprecision(3) << U[i*n_y+j] << ",";
        }
        std::cout << " - end \n";
    }
    
    std::cout << "\nPremi uno o due volte Invio ... ";
    std::cin.ignore();
    std::cin.ignore();
    
}
