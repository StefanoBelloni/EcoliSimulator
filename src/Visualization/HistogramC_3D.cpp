//
//  HistogramC_3D.cpp
//  Ecoli_4.1.4
//
//  Created by Stefano Belloni on 26/10/15.
//  Copyright © 2015 Stefano Belloni. All rights reserved.
//

#include <stdio.h>
#include <cstdlib>
#include "Funz_C.h"


#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>

#ifndef NO_M_THREAD
#include <array>
#endif

#include "LoadBar.hpp"
#include "Funz_C.h"
#include "Funz_C_Par.h"

#include "GlobalVariables.h"
#include "GnuplotGlobal.h"
#include "apngasm_Global.h"

using namespace std;

//Funzioni max e min
#ifndef max
#define max( a, b ) ( ((a) > (b)) ? (a) : (b) )
#endif
#ifndef min
#define min( a, b ) ( ((a) < (b)) ? (a) : (b) )
#endif
//


//vector<vector<long double> > x,y hanno dim_col_t colonne e n_c righe, le accedo come x[colonne][righe]


// COSTANTI

#include "constants.h" //#define pi 3.141592653589793238462

void loadbar(unsigned int x, unsigned int n, unsigned int w);

//****************************************************************************************
//      Histogram_3D_FunzC
//****************************************************************************************

/** Function to create the histogram for the function c, it is used to PREVIEW LIGAND CONCENTRATION. (void Funz_C::preview_F_C())
 */

long double Histogram_3D_FunzC(Funz_C *f, long double dt, int n_frame_max){
// COSTANTI

int i_x,i_y; // Contatori vari.
//    long double delta_x=0;
long double delta_x_p; // estremi intervallo x histogram
//    long double delta_y=0;
long double delta_y_p; // estremi intervallo y histogram
//    int found=0; // se ho sistemato il batterio considerato --> setto la variabile pari a 1.
long double max_fc=-1.0;

long double t=0.0;
long double fc=0.0;
    
#if NO_M_THREAD
long double x_0[2];
#else
array<long double,2> x_0;
#endif
    
char buffer[52]; // The filename buffer.

//ifstream file_info("info_traj.dat");

ofstream file3D_hist;
ofstream file3D_c;

    long double x_delta_hist=f->min_x;
    long double y_delta_hist=f->min_y;
    
    int n_dx=0;
    int n_dy=0;
    
    while (x_delta_hist<=f->max_x) {
        n_dx++;
        x_delta_hist+=f->dx;
    }
    
    while (y_delta_hist<=f->max_y) {
        n_dy++;
        y_delta_hist+=f->dy;
    }
    
    //delta_x_p=f->min_x;
    //delta_y_p=f->min_y;
    
cout << BOLDBLACK << "\nELABOAZIONE DATI FILMATO" << RESET<< endl;
// Recupero i dati dal file sulle caratteristiche tecniche.


for (int n_frame=0; n_frame<n_frame_max; n_frame++) {
    
    loadbar(n_frame,n_frame_max);
    
        snprintf(buffer, sizeof(char) * 52, "film3Dc%i.dat", n_frame+1);
        file3D_c.open(buffer);
        if (!file3D_c.is_open()) {
            cout << "ERRORE NELLA SCRITTURA DEL FILE" << endl;
            return -2;
        }
    
        
        delta_x_p=f->min_x+ f->dx/2;
        delta_y_p=f->min_y+ f->dy/2;
        
        //**************************************************
        //    Salvo i dati sul file numero "n_colonna"
        //**************************************************
        
        for (i_x=0; i_x<n_dx; i_x++) {
            for (i_y=0; i_y<n_dy; i_y++) {
                x_0[0]=delta_x_p;
                x_0[1]=delta_y_p;
                //max_z=max(max_z,z[i_x][i_y]);
                
                fc = f->new_F_C(t,x_0);
                
                max_fc=max(max_fc,fc);
                
//                cout << "max_fc=max(max_fc,fc);" << max_fc<< "=max("<<max_fc<<","<<fc<<")\n";
                
                file3D_c << delta_x_p << " " << delta_y_p << " " << fc << endl;
                    //                        cout << "file3Dc" << endl;
                
                delta_y_p+=f->dy;
            }
            
            file3D_hist << endl;
            file3D_c << endl;
            delta_y_p=f->min_y+f->dy/2;
            delta_x_p+=f->dx;
            
        }
        
        // Necessario per leggere e scrivere diversi file con un solo ifstream!
        
        file3D_hist.close();
        file3D_c.close();
    
    
    t+=dt;
}

cout << "\ncreation file 3D histograms ... \n";

return max_fc;
    
}


//****************************************************************************************
//      Gnuplot F_c max
//****************************************************************************************

void Funz_C::gnuplotFunC(long double max_fc, long double dt, int n_frames){
    
    ofstream file_3D_hist;
    ofstream file_play_video;
    
    file_3D_hist.open("3D_hist.gnu");
    file_play_video.open("play_video.gnu");
    
    cout  <<"\nplay video without saving ...\n";
    
    file_3D_hist << gnuplotSetTerminalPlot << endl;
    
    file_3D_hist << "nome2 = \"Ligand Concentration, T = "<<dt<<"*\".b.\"\"" << endl;
    file_3D_hist << "nome1 = \"film3Dc\".b.\".dat\"" << endl
                 << "set title nome2" << endl
//                 << "set pm3d map" << endl
                 << "set pm3d interpolate 2,2" << endl;
    

    if (max_fc>100.0) {
        // "Logrithmic"
        file_3D_hist << "set format z '%e'" << endl;
        file_3D_hist << "set zrange [ " << 1 << ":" << max_fc << "]" << endl;
    }else{
        file_3D_hist << "set zrange [ " << 0 << ":" << max_fc << "]" << endl;
    }
    
    file_3D_hist << "set xrange [ " << min_x<<":"<<max_x<< "]" << endl
                 << "set yrange [ " << min_y<<":"<<max_y<< "]" << endl ;
    
    
    
    
    //***************************************************************************
    
    file_3D_hist << "set cbrange [0:"<<max_fc<<"]"<<endl
//                 << "set palette rgb 21,22,23"<<endl;
                 << "set palette rgbformulae 33,13,10"<<endl;
//                 << "set palette rgb 3,2,2"<<endl;
    //***************************************************************************
    
    file_3D_hist << "splot nome1 with pm3d notitle" << endl;
//    << "unset multiplot" << endl;
    
    file_3D_hist << "pause .1" << endl;
    
    file_3D_hist<< "b=b+1" << endl
    << "if(b<" << n_frames << ") reread;"<< endl;
    
    file_3D_hist.close();

    file_play_video << "b=1;" << endl
    << "load \"3D_hist.gnu\"" << endl
    << "pause mouse any" << endl;

    
    file_play_video<< "quit" <<endl;
    
    file_play_video.close();
    
    string command = gnuplotOpen + "play_video.gnu";
    
    cout << "PLOT GNUPOLT" << endl;
    cout << " ... \n";
    
    system(command.c_str());
    
    cout << " ... \n";
    
    
}
