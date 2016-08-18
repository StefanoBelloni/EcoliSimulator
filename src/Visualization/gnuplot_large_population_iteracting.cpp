//
//  gnuplot_large_population_iteracting.cpp
//  EColi_2.4
//
//  Created by Stefano Belloni on 22/06/15.
/*This program is free software - GNU General Public License Verison 2*/
//


#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
#include <thread>
#include "Declar_funz.h"
#include <limits>
#include <ctime>

#include "Colori.h"

#include "GlobalVariables.h"
#include "sssr.h"
#include "apngasm_Global.h"
#include "Funz_C.h"
#include "Funz_C_Par.h"
#include "gnuplot_3D.h"
#include "filmato_3D_gnuplotMultiThread.hpp"
#include "multiplot_film_snapshots.h"

#ifndef min
#define min_( a, b ) ( ((a) < (b)) ? (a) : (b) )
#endif

using namespace std;

/**
 * Function to plot the data for large_interacting_population: basically is possible duplicate of gnuplot_large_population.
 * it changes how we read the file ... first loop on time or bacteria ??
 */

double histogram_3D_gnuplotV2MultiThreadV2(double max_x, double max_y, double min_x,double min_y, int n_dx, int n_dy, double dx, double dy, vector<vector<double> >& x,vector<vector<double> >& y, int n_c, int dim_col_t, int n_salti_colonne, Funz_C *f, double &maxC, int risp_Max, int cont_sim, string name_info);

void gnuplot_large_population_interacting(string file_info[], string name_dyn, double T_f, int n_c, int dim_col_t, string names, Funz_C *f, int cont_gen_sim, double maxC)
// Nelle variabili -> da aggiungere quanto relativo ai salti per batterio
{
    int risp;
    
    // big number to be set to the proper limit of the domain
    double min_x=10000;
    double max_x=-10000;
    double min_y=10000;
    double max_y=-10000;
    double max_z=0;
    
    // Lettura riga file.
    string temp_string;
    //    char comma = ','; // dummy variable per leggere dal file e dividerlo nelle sue parti fondamentali.
    
    vector< vector<double> > x_t,y_t,sign_c_t;; // matrix equivalent to P(2,i,j) in Matlab_program
    
    cout << "GNUPLOT" << endl;
    
    
    // Files da leggere
    
    ifstream posizione;        
    posizione.open(names.c_str());
    if (automatic_!=1) {
        
    
        x_t.resize( dim_col_t, vector<double>( n_c , 0 ) );     // x_t[0 < cont_temp < dim_col_t][0 < j< n_c]  <--  come accedere alla matrice!! 
        y_t.resize( dim_col_t , vector<double>( n_c , 0 ) );
        sign_c_t.resize( dim_col_t , vector<double>( n_c , 0 ) );
        
        
        
        
        for (int i=0; i<dim_col_t; i++) {            
            for (int j=0; j<n_c; j++) {
                // Leggo una riga del file (formattato così "x,y\n" ) e la divido nelle due sue parti "x" "," "y"
                getline(posizione,temp_string); 
                std::istringstream ss(temp_string);
                
                //            cout << "debug, lettura file" << endl;
                
                ss >> x_t[i][j] >> y_t[i][j] >> sign_c_t[i][j];
                
                //            std::cout << "(x,y)_"<<j<<"("<< i << ") = " << x_t[i][j] << " , " << y_t[i][j] << std::endl;
                
                min_x=min(min_x,x_t[i][j]);
                min_y=min(min_y,y_t[i][j]);
                max_x=max(max_x,x_t[i][j]);
                max_y=max(max_y,y_t[i][j]);
                
            }
        }
        
        double max_x_=max(max_x,max_y);
        double max_y_=max_x;
        double min_x_=min(min_x,min_y);
        double min_y_=min_x;
        
        // Creo i files per fare il filmato.
        
        double dx;
        double dy;

        dx=(max_x_-min_x_)/pow(2*n_c,1/3.);
        dy=(max_y_-min_y_)/pow(2*n_c,1/3.);

        if (dx<0.0001) {
            dx = 0.001;
        }
        if (dy<0.0001) {
            dy = 0.001;
        }
        
        
        
        double x_delta_hist=min_x;
        double y_delta_hist=min_y;
        
        int n_dx=0;
        int n_dy=0;
        
        while (x_delta_hist<=max_x) {
            n_dx++;
            x_delta_hist+=dx;
        }
        
        while (y_delta_hist<=max_y) {
            n_dy++;
            y_delta_hist+=dy;
        }

        int nthread = min_(n_thread_available,std::thread::hardware_concurrency());
        
        if (nthread<=1) {
            max_z=histogram_3D_gnuplotV2(max_x, max_y, min_x, min_y,n_dx ,n_dy , dx, dy, x_t, y_t, n_c, dim_col_t, 1,f,maxC, 1,cont_gen_sim, file_info[0]);
        }else{
            max_z = histogram_3D_gnuplotV2MultiThreadV2(max_x, max_y, min_x, min_y,n_dx ,n_dy , dx, dy, x_t, y_t, n_c, dim_col_t, 1,f,maxC, 1,cont_gen_sim,file_info[0]);
        }
        
        int error = percSignFunzC(sign_c_t,n_c,dim_col_t,file_info[0]);
        
        if (error!=0) {
            cout << "\nerror in function percSignFunzC(vector< vector<double> > c_t, int n_c, int dim_col_t)\n";
        }
        
    }

    // Play Film

    
    max_x=f->max_x;
    max_y=f->max_y;
    min_x=f->min_x;
    min_y=f->min_y;
    
//    filmato_3D_gnuplot(file_info, max_x, max_y, min_x, min_y, max_z, dim_col_t,f, cont_gen_sim,maxC);
//    filmato_3D_gnuplotMultiT(file_info, max_x, max_y, min_x, min_y, max_z, dim_col_t,f,cont_gen_sim,maxC);
    
    if (no_apngams) {
        cout << BOLDRED << "no_apngams ... " << endl << RESET;
        filmato_3D_gnuplot_gif(file_info, max_x, max_y, min_x, min_y, max_z, dim_col_t,f,cont_gen_sim,maxC);
    }else{
        if (!multithread) {
            cout << BOLDRED << "No Multithread ... " << endl << RESET;
            filmato_3D_gnuplot(file_info, max_x, max_y, min_x, min_y, max_z, dim_col_t,f,cont_gen_sim,maxC);
        }else{
            cout << BOLDRED << "Multithread ... " << endl << RESET;
            filmato_3D_gnuplotMultiT(file_info, max_x, max_y, min_x, min_y, max_z, dim_col_t,f,cont_gen_sim,maxC);
        }
    }
    
    // TO move outside ...
    cout << "Du you want to plot the density at time T=j*T_f/n, j=0...n? \npress 0 for yes, 1 for no ";
    sssr(risp,"Du you want to plot the density at time T=j*T_f/n, j=0...n? press 0 for yes, 1 for no ");
    if (risp==0) {
        gnuplot_Multiplot(f,dim_col_t,cont_gen_sim, file_info[0],min_x, max_x, min_y, max_y,  max_z, maxC);
    }
    
    // Plot baricentro.
    
    if (automatic_==0) {
        funz_clear();
        cout << "plot the baricenter trajectory and the mean square displacement? \npress 0 for yes, 1 for no ";
        getInput( risp);
    }else {
        risp=0;
    }
    
    // barycenter
    
    if (automatic_!=1) {
        if (risp==0) {
            baricentro_plot(file_info[0],x_t,y_t,n_c,dim_col_t);
        }
    }

	funz_clear();
//    if (automatic_==0) {
//        
//        cout << "plot the Distribution of the internal dynamic ? \npress 0 for yes, 1 for no ";
//        getInput( risp)){
//            cout << "Invalid value ...  ";
//            cin.clear();
//            cin.ignore(numeric_limits<streamsize>::max(), '\n');
//            cout << "\nEnter again ... " << endl;
//        }
//    }else {
//        risp=0;
//    }
//    
//    if (automatic_!=1) {
//        if (risp==0) {
//            Histogram_Dynamic(file_info[0], name_dyn);
//        }
//    }
    
    
}
