//
//  gnuplot_large_population.cpp
//  E_Coli2.2
//
//  Created by Stefano Belloni on 01/06/15.
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


#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>

#ifndef NO_M_THREAD
#include <thread>
#endif

#include <iomanip>

#include <limits>
#include <ctime>

#include "Colori.h"
#include "Declar_funz.h"
#include "Funz_C.h"
#include "Funz_C_Par.h"
#include "gnuplot_3D.h"
#include "filmato_3D_gnuplotMultiThread.hpp"
#include "histogram3DMultiThreadV2.hpp"
#include "multiplot_film_snapshots.h"
#include "filmato_3D_gnuplot_gif.hpp"
#include "GlobalVariables.h"
#include "sssr.h"
#include "apngasm_Global.h"

#ifdef min
#define min_( a, b ) ( ((a) < (b)) ? (a) : (b) )
#endif

using namespace std;

int writeLog(string what, string msg);

/**
 * Function to plot the data for large_population.
 */
// There is a function gnuplot_large_population_iteracting, but it has been absorbed in this one!

void gnuplot_large_population(string file_info[], string name_dyn, long double T_f, int n_c, int dim_col_t, string names, Funz_C *f, int cont_gen_sim) 
// Nelle variabili -> da aggiungere quanto relativo ai salti per batterio
{
    int risp;
    long double min_x=10000;
    long double max_x=-10000;
    long double min_y=10000;
    long double max_y=-10000;
    long double max_z=0.0;
    long double maxC = 0.0;

#ifndef NO_M_THREAD
    unsigned int nthread = min_(n_thread_available,std::thread::hardware_concurrency());
#endif
    // Lettura riga file.
    string temp_string;
    vector< vector<long double> > x_t,y_t,sign_c_t; // matrici equivalenti a P(2,i,j) in Matlab_program
    // Files da leggere
    ifstream posizione;        
    posizione.open(names.c_str());

    //this is the answear to the previous question ...
    int risp_Max=1;
    sssr(risp_Max,"all domain of the experiment");
    
    if (automatic_!=1) {
        try {
            x_t.resize( dim_col_t, vector<long double>( n_c , 0 ) );     // x_t[0 < cont_temp < dim_col_t][0 < j< n_c]  <--  come accedere alla matrice!!
            y_t.resize( dim_col_t , vector<long double>( n_c , 0 ) );
            sign_c_t.resize( dim_col_t , vector<long double>( n_c , 0 ) );
        }catch(bad_alloc &e) {
            cout << "error resizing ... " << endl;
            cout << "in gnuplot_large_population.cpp, line 110" << endl;
            return;
        }
        
        for (int j=0; j<n_c; j++) {
            for (int i=0; i<dim_col_t; i++) {
                // Leggo una riga del file (formattato così "x,y\n" ) e la divido nelle due sue parti "x" "," "y"
                getline(posizione,temp_string); 
                std::stringstream ss(temp_string);
                ss.precision(20);
                
                ss >> x_t[i][j] >> y_t[i][j] >> sign_c_t[i][j];
//                cout << std::setprecision(25) << x_t[i][j] << endl;
                min_x=min(min_x,x_t[i][j]);
                min_y=min(min_y,y_t[i][j]);
                max_x=max(max_x,x_t[i][j]);
                max_y=max(max_y,y_t[i][j]);
            }
        }
        
        long double max_x_=max(max_x,max_y);
        long double max_y_=max_x;
        long double min_x_=min(min_x,min_y);
        long double min_y_=min_x;
        
        // Creo i files per fare il filmato.

        long double dx;
        long double dy;
        
        if (n_c>100) {
            dx=(max_x_-min_x_)/sqrt(n_c);
            dy=(max_y_-min_y_)/sqrt(n_c);
        }else {
            dx=0.1;
            dy=0.1;
        }
    
        if (dx<0.0001) {
            dx = 0.001;
        }
        if (dy<0.0001) {
            dy = 0.001;
        }
  
        long double x_delta_hist=min_x;
        long double y_delta_hist=min_y;
        
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
        #if NO_M_THREAD     
        time_t start;     
        time(&start); 
        #else     
        auto start = chrono::steady_clock::now(); 
        #endif

#if NO_M_THREAD
       max_z=histogram_3D_gnuplotV2(max_x, max_y, min_x, min_y,n_dx ,n_dy , dx, dy, x_t, y_t, n_c, dim_col_t, 1,f,maxC, risp_Max,cont_gen_sim,file_info[0]);
#else
        if (nthread<=1 || !multithread) {
            cout << BOLDRED << "No Multithread ... " << endl << RESET;
            max_z=histogram_3D_gnuplotV2(max_x, max_y, min_x, min_y,n_dx ,n_dy , dx, dy, x_t, y_t, n_c, dim_col_t, 1,f,maxC, risp_Max,cont_gen_sim,file_info[0]);
        }else{
            cout << BOLDRED << "Multithread ... " << endl << RESET;
            max_z = histogram_3D_gnuplotV2MultiThreadV2(max_x, max_y, min_x, min_y,n_dx ,n_dy , dx, dy, x_t, y_t, n_c, dim_col_t, 1,f,maxC, risp_Max,cont_gen_sim, file_info[0]);
        }
#endif

#if NO_M_THREAD
    time_t end;
    double diff;
    time(&end);
    diff=difftime(start,end); // gives in seconds
#else
    auto end = chrono::steady_clock::now();
    auto diff = end - start;
#endif

        cout <<BOLDBLACK << "***************************************************\n";
        cout << "Seconds needed to complete the creation and saving of the film:\n     ";
#if NO_M_THREAD
        cout << diff << " seconds" << endl;
#else
        cout << chrono::duration <long double, milli> (diff).count()/1000 << " seconds" << endl;
#endif        
        cout << "***************************************************\n"<<RESET;
        
        
        // LOG FILE
        if (verbose){
       stringstream msg;
       msg.str("");
#if NO_M_THREAD
        msg << diff << " seconds";
#else
        msg << chrono::duration <long double, milli> (diff).count()/1000 << " seconds";
#endif           
       writeLog("HISTOGRAMS: data elaborated and saved to file in ",msg.str());
        } 
        int error = percSignFunzC(sign_c_t,n_c,dim_col_t,file_info[0]);
        if (error!=0) {
            cout << "\nerror in function percSignFunzC(vector< vector<long double> > c_t, int n_c, int dim_col_t)\n";
        }
    }


    if (risp_Max==0) {
        max_x=f->max_x; max_y=f->max_y; min_x=f->min_x; min_y=f->min_y;
    }
    if (no_apngams) {
        cout << BOLDRED << "no_apngams ... " << endl << RESET;
        filmato_3D_gnuplot_gif(file_info, max_x, max_y, min_x, min_y, max_z, dim_col_t,f,cont_gen_sim,maxC);
    }else{
#if NO_M_THREAD
        filmato_3D_gnuplot(file_info, max_x, max_y, min_x, min_y, max_z, dim_col_t,f,cont_gen_sim,maxC);
#else    
        if (!multithread) {
            cout << BOLDRED << "No Multithread ... " << endl << RESET;
            filmato_3D_gnuplot(file_info, max_x, max_y, min_x, min_y, max_z, dim_col_t,f,cont_gen_sim,maxC);
        }else{
            cout << BOLDRED << "Multithread ... " << endl << RESET;
            filmato_3D_gnuplotMultiT(file_info, max_x, max_y, min_x, min_y, max_z, dim_col_t,f,cont_gen_sim,maxC);
        }
#endif
    }    
    // multiplot snapshots
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
    
    if (automatic_!=1 && risp==0) {
        baricentro_plot(file_info[0],x_t,y_t,n_c,dim_col_t, cont_gen_sim);
    }
    // One might add a better way to see internal dynamics ...
    // This one was just to give an idea of the value of Q when we do the statistical analysis of the data ...
    if (automatic_==0) {
        cout << "plot the Distribution of the internal dynamic ? \npress 0 for yes, 1 for no ";
        getInput( risp);
    }else {
        risp=0;
    }

    if (automatic_!=1 && risp==0) {
        Histogram_Dynamic(file_info[0], name_dyn, cont_gen_sim);
    }

    
}
