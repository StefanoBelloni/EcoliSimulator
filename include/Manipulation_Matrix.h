//
//  Manipulation_Matrix.h
//  E_Coli_2.3
//
//  Created by Stefano Belloni on 18/06/15.
/*This program is free software - GNU General Public License Verison 2*/
//

int solve_tridiag_Lap(long double r, long double **rhs, int n, int j, int n_y);
void rhs_Lap_U_Add(long double **U, int n_x, int n_y, long double r, long double **Q, long double dt, long double kd_);
long double *create_vector2D(int sizeX, int sizeY);

void Transpose_Matrix(long double *U, long double *U_T, int n_x, int n_y, long double &f_max);
void print_matrix(long double *U, int n_x, int n_y);
