//
//  SolveHeat2D_Neumann.cpp
//  E_Coli_2.3
//
//  Created by Stefano Belloni on 18/06/15.
/*This program is free software - GNU General Public License Verison 2*/
//

#include <iostream>
#include "Manipulation_Matrix.h"


// randoimize bacteria !!!

/** This function solve the 2D Heat Equation with Neumann boundary using the he Alternating Direction Implicit (ADI) method.
 * @param U pointer to the matrix of solution
 * @param Q pointer to the matrix of source/sink of Equation
 * @param n_t number of iteration of the solver
 * @param n_x,n_y number grid points (in x and y)
 * @param dt time step
 * @param kd_,r parameters of the finite laplacian
 */

int SolveHeat2D_Neumann2(double **U, double **Q, double n_t, double r, int n_x, int n_y, double dt, double kd_, double &f_max){
    
    // Loop on the time !!!
    int error_=0;
    double dt_2=0.5*dt;
    double *U_T;
    double *Q_T;
    
    double temp=0;
    
    U_T = new double[n_x*n_y];
    Q_T = new double[n_x*n_y];
    
    double **pU_T=&U_T;
    double **pQ_T=&Q_T;
    
    
    
    //    int s=-1;
    
    
//    std::cout << "Q = \n";
//    print_matrix(*Q, n_x,n_y);
    
    for (int i_t=0; i_t<n_t; i_t++) {            
        
//        std::cout << "**********************************************";
//        std::cout << "\nt = " << i_t << "\n";;
//        std::cout << "**********************************************\n";
        
        rhs_Lap_U_Add(U, n_x, n_y, r, Q, dt_2, kd_); 

//        std::cout << "U*L+Q = \n";        
//        print_matrix(*U, n_x,n_y);

//        std::cout << "Q = \n";
//        print_matrix(*Q, n_x,n_y);
        
        for (int i=1; i<n_y-1; i++) {
            error_=solve_tridiag_Lap(-r, U, n_x, i, n_y);
            if (error_==-1) {
                delete [] Q_T;
                delete [] U_T;
                return -1;
            }
        }
        
//        std::cout << "(U+Q)/Lap_x = \n";
//        print_matrix(*U, n_x,n_y);
        
        // i 4 Angoli
        
        (*U)[0*n_y+0]     = (*U)[1*n_y+1];
        (*U)[(n_x-1)*n_y+0] = (*U)[(n_x-2)*n_y+1];        
        (*U)[0*n_y+n_y-1] = (*U)[1*n_y-2];
        (*U)[(n_x-1)*n_y+n_y-1] = (*U)[(n_x-2)*n_y-2];
        
        // Sistemo il bordo.
        for (int i_x = 1; i_x<n_x-1; i_x++) {
            (*U)[i_x*n_y+0]     = (*U)[i_x*n_y+1];
            (*U)[i_x*n_y+n_y-1] = (*U)[i_x*n_y+n_y-2];        
        }
        
//        std::cout << "U|bordo = \n";
//        print_matrix(*U, n_x,n_y);
        
        
        // DEVO TRASPORRE LA MATRICE E FARE LE STESSE COSE
        
        Transpose_Matrix(*U, U_T, n_x, n_y,temp);
        Transpose_Matrix(*Q, Q_T, n_x, n_y,temp);
        
//        std::cout << "U_T = \n";
//        print_matrix(U_T, n_y,n_x);
        
        rhs_Lap_U_Add(pU_T, n_y, n_x, r, pQ_T, dt_2, kd_);
        
//        std::cout << "U_T = \n";
//        print_matrix(U_T, n_y,n_x);
        
        // TODO :::::: check ::::::
        
        for (int i=1; i<n_y-1; i++) {
            error_=solve_tridiag_Lap(-r, pU_T, n_y, i, n_x);
            if (error_==-1) {
                delete [] Q_T;
                delete [] U_T;
                return -1;
            }
        }
        
//        std::cout << "(U_T+Q_T)/Lap_y = \n";
//        print_matrix(U_T, n_y,n_x);
        
        // i 4 Angoli
        
        U_T[0*n_y+0]     = U_T[1*n_y+1];
        U_T[(n_x-1)*n_y+0] = U_T[(n_x-2)*n_y+1];        
        U_T[0*n_y+n_y-1] = U_T[1*n_y-2];
        U_T[(n_x-1)*n_y+n_y-1] = U_T[(n_x-2)*n_y-2];
        
        Transpose_Matrix(U_T, *U, n_y, n_x, f_max);
        
//        std::cout << "U = \n";
//        print_matrix(*U, n_x,n_y);
        
        
//        for (int i_x = 1; i_x<n_x-1; i_x++) {
//            (*U)[i_x*n_y+0]     = (*U)[i_x*n_y+1];
//            (*U)[i_x*n_y+n_y-1] = (*U)[i_x*n_y+n_y-2];        
//        }
//        
        
        
        for (int i_y = 1; i_y<n_y-1; i_y++) {
            (*U)[0*n_y+i_y]     = (*U)[1*n_y+i_y];
            (*U)[(n_x-1)*n_y+i_y] = (*U)[(n_x-2)*n_y+i_y];        
        }
        

//        std::cout << "U|bordo = \n";
//        print_matrix(*U, n_y,n_x);
        
        
//        rhs_Lap_U_Add2_tr(U, n_x, n_y, r, Q, dt_2); 
//
//        for (int i=1; i<n_x-1; i++) {
//            error_=solve_tridiag_Lap_tr(-r, U, n_y, i);
//            if (error_==-1) {                    
//                return -1;
//            }
//        }
//        
//        // BC left/right
//        for (int i_x = 0; i_x<n_x; i_x++) {        
//            (*U)[i_x*n_y+0]     = (*U)[i_x*n_y+1]; 
//            (*U)[i_x*n_y+n_y-1] = (*U)[i_x*n_y+n_y-2];
//        }
        
        
    }
    
    delete [] Q_T;
    delete [] U_T;
    
    return 0;
}
