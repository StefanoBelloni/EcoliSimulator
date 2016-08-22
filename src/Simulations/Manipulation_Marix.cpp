//
//  Manipulation_Marix.cpp
//  E_Coli_2.3
//
//  Created by Stefano Belloni on 18/06/15.
/*  This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
02110-1301, USA. */
//

#include <iostream>
#include "Manipulation_Matrix.h"
#include <vector>
#include <cmath>


int writeLog(std::string what, std::string msg);

using std::vector;

//***********************************************************************************
//***********************************************************************************

/** Function to crate a [sizeX*sinzeY] vector*/
long double *create_vector2D(int sizeX, int sizeY){
// to access the vector v[i][j] --> v[i*sizeY+j];
    long double *array;    
    return array = new long double[sizeX*sizeY];

}

//***********************************************************************************
//***********************************************************************************


// Come in MatrixLib, ma passo i dati per referenza ...

void vectorAdd_2(long double *up, long double *v, int len, long double dt)
{
    for (int i = 0; i < len; i++) {
        up[i] += v[i]*dt;
    }
}

void matrixAdd_2(long double **Ap, long double **B, int n, int m, long double dt)
{
    for (int i = 0; i < n; i++) {
        vectorAdd_2((*Ap) + i, (*B)+i, m, dt);
    }
}


//***********************************************************************************
//***********************************************************************************

/**
 * The function calculate the product on the rhs of the equation for ADI method
 * fisrt step: L_x*U(n+*)=U(n)*L_y+Q
 * second step: L_x*U(n+1)=U(n+*)*L_y+Q
 *
 * input:
 *      **U : pointer to the matrix U = U(n), oder matrix U = U(n+*)
 *      n_x, n_y dimension matrix U -> L_y = (n_y)x(n_y)
 *      r : factor in the ADI approximation = +/- D*dt/(2dx^2).
 *          if r>0 implicit method.
 *          if r<0 explicit method.
 */

void rhs_Lap_U_Add(long double **U, int n_x, int n_y, long double r, long double **Q, long double dt, long double kd_)


{
    
    long double a_1;
    long double a_2;
    int true_=0;
    
    long double h=1-2*r;
    long double kd=kd_*dt;
//    long double kd=0;

    
    //prima riga == tutti zeros
    for (int j=0; j<n_y; j++) {
        (*U)[j]=0;
    }
    
    for (int i=1; i<n_x-1; i++) {
        
        a_1=(*U)[i*n_y+0];
        a_2=(*U)[i*n_y+1];        
//        (*U)[i*n_y+0]=(h-kd*(a_2>0))*a_1+2*r*a_2;
        
        (*U)[i*n_y+0]=0;
        
        for (int j=1; j<n_y-1; j++) {
            true_=(a_2>0)?1:0;
            
            // [discrete lapalcian minus degradation*c(t,x)] + production
            
            (*U)[i*n_y+j]=r*a_1+(h-kd*true_)*a_2+(*U)[i*n_y+j+1]*r+(*Q)[i*n_y+j]*dt;
            a_1=a_2;
            a_2=(*U)[i*n_y+j+1];
            
        }
        
//        (*U)[i*n_y+n_y-1]=2*r*a_1+(h-kd*(a_2>0))*a_2;
        (*U)[i*n_y+n_y-1]=0;
    }
    
    //ultima riga == tutti zeros
    for (int j=0; j<n_y; j++) {
        (*U)[(n_x-1)*n_y+j]=0;
    }
    
    
}

/** Function: solve_tridia
 *
 *  Applies Thomas' algorithm for solving tridiagonal matrices. The primary
 *  use of this function is for solving the system of equations that arises
 *  from Backward Euler.
 *  pd:  suPer Diagonal.
 *  dg:  DiaGonal.
 *  bd:  suB Diagonal
 *  rhs: Right Hand Side
 *  n:   Number of elements.
 *  ref. http://www.cfd-online.com/Wiki/Tridiagonal_matrix_algorithm_-_TDMA_%28Thomas_algorithm%29
 */

int solve_tridiag_Lap(long double r, long double **rhs, int n, int j, int n_y)
{
    int i;
    long double s;
    long double h=1-2*r;
    
    long double *pd = new long double[n];
    long double *dg = new long double[n];
    long double *bd = new long double[n];
        
    for (int i=0; i<n-1; i++) {
        pd[i]=r;
        dg[i]=h;
        bd[i]=r;
    }
    
    pd[0]=-1;
    dg[0]=1;
    dg[n-1]=1;
    bd[n-1]=-1;
    
//    pd[1]=2*r;
//    dg[n-1]=h;
//    bd[n-2]=2*r;
    
    // Forward substitution.
    for(i = 1; i < n; i++)
    {
        s       = bd[i]/dg[i-1];
        dg[i]  -= s*pd[i-1];
        (*rhs)[i*n_y+j] -= (*rhs)[(i-1)*n_y+j]*s;   
        
        
    }
    
    // Back substitution.
    (*rhs)[(n-1)*n_y+j] = (*rhs)[(n-1)*n_y+j]/dg[n-1];
    for(i = n - 2; i > -1; i--){
        (*rhs)[i*n_y+j] = ((*rhs)[i*n_y+j] - pd[i]*((*rhs)[(i+1)*n_y+j]))/dg[i];
        
        if (std::isnan((*rhs)[i*n_y+j])) {
            
            
            // Devo liberare la memoria nel caso esca prima!!
            delete [] pd;
            delete [] dg;
            delete [] bd;
            
            //std::string risp = "a";
            std::cout << "Error solving the PDE ...";
//            std::cout << "(i,j,n) = " << i << "," << j << "," << n << std::endl;
//            std::cout << "press a key to continue ... ";
//            std::cin >>risp;
//            std::cout << "press Enter to continue ... " << std::endl;
//            std::cin.ignore();
//            std::cin.ignore();
            
            std::string msg("Error solving the PDE");
//            msg+=setNameScriptDyn(cont_sim,save_);
            writeLog("ERROR",msg);
            
            return -1;
            
        }
//        std::cout << "rhs("<<i <<","<<j<<") = " << (*rhs)[i*n+j] << std::endl;
    }
        
    
    delete [] pd;
    delete [] dg;
    delete [] bd;
    
    return 0;
}


