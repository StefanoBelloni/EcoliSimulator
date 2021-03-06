//
//  Funz_C_Inter.cpp
//  E_Coli2.2
//
//  Created by Stefano Belloni on 26/05/15.
/*This program is free software - GNU General Public License Verison 2*/
//

#include <iostream>
#include <fstream>
#include <cmath>
#include "Funz_C_Inter.h"

#ifndef NO_M_THREAD
#include <array> 
#endif

#include "GlobalVariables.h"
#include "sssr.h"

#ifndef max
#define max( a, b ) ( ((a) > (b)) ? (a) : (b) )
#endif
#ifndef min
#define min( a, b ) ( ((a) < (b)) ? (a) : (b) )
#endif

//long double **createZeroMatrix(int n, int m);

using std::cout;
using std::endl;

void Funz_C_Inter::set_parameter(){
    
    int risp=0;
    Funz_C::set_parameter();
    
    cout << "Do you want to change parameters of the function? \npress 0 for yes, 1 for no ";
    sssr(risp,"Do you want to change parameters of the function? press 0 for yes, 1 for no ");
    
    if (risp==0) {
        Funz_C_Par::set_parameter();
        change_par=1;
    }else {
        change_par=0;
    }
    
    interact=0;
    
    cout << "What dx do you want to applay to the mesh? (dx=dy) "<< endl; 
    sssr(dx,"What dx do you want to applay to the mesh? (dx=dy) ");
    
    if (interact==0) {
        cout <<"Which is the degradation rate of the PDE model of the Evolution of Ligand\nDefault is 0.05 "<< endl;
        sssr(degradation_rate,"Which is the degradation rate of the PDE model of the Evolution of Ligand");
    }
    
    dy=dx; //si potrebbe eliminare questo, ma si deve cambiare r in PDE solver 

    n_x=0;
    n_y=0;
    
    long double x=min_x;
    
    while (x<=max_x) {
        x+=dx;
        n_x++;
    }
    
    x=min_y;
    
    while (x<=max_y) {
        x+=dy;
        n_y++;
    }

    // non inizializzo this->f_c ed this->q_c
    
    
}

Funz_C_Inter::Funz_C_Inter(){
    
//    cout << "Creato!!" << endl;
    
}

#if NO_M_THREAD
long double Funz_C_Inter::new_F_C(long double t, long double* x)
#else
long double Funz_C_Inter::new_F_C(long double t, std::array<long double,2> x)
#endif
{
    
    int n_x[4];
    get_coordinate1(x,n_x);
	// I calculate the mean around the points
	// TODO: one should whight better the meen according to x-x_i (resp y) ...
    return ((*f_c)[n_x[0]*n_y+n_x[1]]+
			(*f_c)[n_x[0]*n_y+n_x[3]]+
			(*f_c)[n_x[2]*n_y+n_x[1]]+
			(*f_c)[n_x[2]*n_y+n_x[3]])/4;
    
}

void Funz_C_Inter::print_fc(std::ofstream &file_save, long double t){

    int n=max(1,floor(.1/dx));
    
    for (int i=0; i<n_x; i=i+n) {
        for (int j=0; j<n_y; j=j+n) {

            file_save << min_x+i*dx << " " << min_y+j*dy << " " << (*f_c)[i*n_y+j] << endl;
            
        }
        
        file_save << endl;
    }
    
}

