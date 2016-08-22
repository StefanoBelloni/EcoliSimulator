//
//  Funz_C_Preview.cpp
//  Ecoli_4.1.4
//
//  Created by Stefano Belloni on 26/10/15.
//  Copyright © 2015 Stefano Belloni. All rights reserved.
//

//**********************************************************************************

#include <iostream>
#include <limits>
#include <ctime>
#include "Declar_funz.h"
#include "Funz_C.h"
#include "Colori.h"
#include "Declar_funz.h"

using std::cout;
using std::cin;
using std::endl;
using std::streamsize;
using std::numeric_limits;

void cancell_histFile(int n_frame_max);

void Funz_C::preview_F_C(){
    
    // SETTING.
    
    long double T_f=0.0L;
    long double dt=0.0L;
    long double Max_fc=0.0L;
    int n_frame_max;//=(int)T_f/dt;
    
//    cout << "void Funz_C::preview_F_C(long double T_f, long double dt)\n";
    
    cout << BOLDBLUE << "\n*************************************\n"
    << " PREVIEW LIGAND CONCENTRATION MENU\n"
    << "*************************************\n" << RESET;
    
    cout << "What's the time orizon of the visualization of the Ligand Concentration? ";
    getInput( T_f);
    
    cout << "What's the time-step between two frames? ";
    getInput( dt);
    
    if (max_x<=min_x||max_x<=min_x) {
        cout << "Error inserting x and y limits: default values used.\n ";
        max_x=5;
        min_x=-5;
        max_y=5;
        min_y=5;
    }
    
    cout << "\nWhat's the space-step dx=dy for the plots?\n ";
    cout << "x_max = " << max_x << endl;
    cout << "y_max = " << max_y << endl;
    cout << "x_min = " << min_x << endl;
    cout << "y_min = " << min_y << endl;
    cout << "dx = ";
    
    getInput( this->dx);
    
    this->dy=this->dx;
    
    n_frame_max=(int)T_f/dt;
    
    cout << "Max_fc = Histogram_3D_FunzC(this, T_f, dt);\n";
    
    Max_fc = Histogram_3D_FunzC(this, dt, n_frame_max)+1;
    
    cout << "Funz c is n. " << num_funz << endl;
    cout << "Max value for f is equal to " << Max_fc << endl;
    
    gnuplotFunC(Max_fc, dt, n_frame_max);
    
    cancell_histFile(n_frame_max);
    
    
}

