/*This program is free software - GNU General Public License Verison 2*/
//

#ifndef E_Coli2_2_Funz_C_Inter_h
#define E_Coli2_2_Funz_C_Inter_h

#include "Funz_C.h"
#include "Funz_C_Par.h"
#include <iostream>
#include <vector>


/** \brief Function used in the  population interacting with the ligand setting
 
 In case the program mode selected is <tt> population interacting with the ligand</tt> the Ligand concentration follows the following equation:
 
 \f[
 \frac{\partial}{\partial t}c(t,x,y)=D_c\Delta_{(x,y)}c(t,x,y)-K_c c(t,x,y)+K_p\sum_{i=1}^{n_c}\delta_{(t,x,y)}(p^i_b(t,x,y))
 \f]
 
 
 where \f$p^i_b\f$ is the position of the bacterium number \f$i\f$.
 
 The simulation is performed using an ADI method where the boundary conditions are of Neumann's type. The method is as follows:
 Let \f$U=(q_{i,j})_{i=1...n_x,j=1...n_y}\f$ be the matrix of the mesh for the rectangular domain and \f$Q\f$ the matrix of the source. Let \f$L_x^{n_x}\f$ be the Laplacian-matrix is the \f$x\f$ direction, it is a \f$n_x\times n_x\f$ matrix  (similar for \f$y\f$), then using the Thompson's Algorithm for the resulting tridiagonal system we solve the PDE in two steps:
 
 \f[
 L^{n_x}_x\otimes U = (U\otimes L^{n_y}_y)^T +\frac{dt\cdot Q}{2}
 \f]
 
 
 \f[
 L^{n_y}_y\otimes U^T = (U^T\otimes L^{n_x}_x)^T+\frac{dt\cdot Q^T}{2}
 \f]
 
 
 where with \f$\otimes\f$ we indicate the <tt>matrix</tt> product, and with \f$Q^T\f$ the transpose of \f$Q\f$.
 
 */

class Funz_C_Inter : public Funz_C_Par {
public:
    
//    vector<vector<long double> > f_c;    
    
    Funz_C_Inter();
    ////~Funz_C_Inter();    
    
    
    void set_parameter(); 
//    void get_coordinate(long double *x, int *n);
    /** it returns the value of the discretized version of c(t,x) on a grid*/
    long double new_F_C(long double t, std::array<long double,2> x);
    void print_fc(std::ofstream &file_save, long double t);
    void print_info(std::ofstream &file_save);

    
};

#endif
