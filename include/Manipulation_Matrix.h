//
//  Manipulation_Matrix.h
//  E_Coli_2.3
//
//  Created by Stefano Belloni on 18/06/15.
/*This program is free software - GNU General Public License Verison 2*/
//

int solve_tridiag_Lap(double r, double **rhs, int n, int j, int n_y);
void rhs_Lap_U_Add(double **U, int n_x, int n_y, double r, double **Q, double dt, double kd_);
double *create_vector2D(int sizeX, int sizeY);

void Transpose_Matrix(double *U, double *U_T, int n_x, int n_y, double &f_max);
void print_matrix(double *U, int n_x, int n_y);
