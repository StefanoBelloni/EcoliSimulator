////
////  Matlab_large_population.cpp
////  E_Coli2.2
////
////  Created by Stefano Belloni on 02/06/15.
/*This program is free software - GNU General Public License Verison 2*/
////
//
//#include <string>
//#include <sstream>
//#include <iostream>
//#include <vector>
//#include <fstream>
//#include <cmath>
//
//#include "GlobalVariables.h"
//#include "sssr.h"
//
//#include "Funz_C.h"
//#include "Funz_C_Par.h"
//
//using namespace std;
//
//long double histogram_3D_gnuplot(long double max_x, long double max_y, long double min_x,long double min_y, int n_dx, int n_dy, long double dx, long double dy, vector<vector<long double> > x,vector<vector<long double> > y, int n_c, int dim_col_t, int n_salti_colonne, Funz_C *f);
//
//void Matlab_large_population(long double T_f, int n_c, int dim_col_t, string names, Funz_C *f) 
//// Nelle variabili -> da aggiungere quanto relativo ai salti per batterio
//{
//    
//    //****************************************************************************
//    //                           VARIABILI VARIE
//    //**************************************************************************** 
//    
//    int risp;
//    
//    long double min_x=10000;
//    long double max_x=-10000;
//    
//    long double min_y=10000;
//    long double max_y=-10000;
//    long double max_z=0;
//    
//    // Lettura riga file.
//    string temp_string;
////    char comma = ','; // dummy variable per leggere dal file e dividerlo nelle sue parti fondamentali.
//    
//    vector< vector<long double> > x_t,y_t; // matrici equivalenti a P(2,i,j) in Matlab_program    
//    
//    cout << "GNUPLOT" << endl;
//    
//    
//    // Files da leggere
//    
//    ifstream posizione;        
//    posizione.open(names.c_str());
//    
//    //****************************************************************************
//    //                        INIZIALIZZAZIONE PARAMETRI
//    //****************************************************************************
//    
//    
//    x_t.resize( dim_col_t, vector<long double>( n_c , 0 ) );     // x_t[0 < cont_temp < dim_col_t][0 < j< n_c]  <--  come accedere alla matrice!! 
//    y_t.resize( dim_col_t , vector<long double>( n_c , 0 ) );
//    
//    
//    
//    
//    for (int j=0; j<n_c; j++) {
//        for (int i=0; i<dim_col_t; i++) {            
//            
//            // Leggo una riga del file (formattato così "x,y\n" ) e la divido nelle due sue parti "x" "," "y"
//            getline(posizione,temp_string); 
//            std::istringstream ss(temp_string);
//            
//            //            cout << "debug, lettura file" << endl;
//            
//            ss >> x_t[i][j]>> y_t[i][j] >> risp; 
//            
//            min_x=min(min_x,x_t[i][j]);
//            min_y=min(min_y,y_t[i][j]);
//            max_x=max(max_x,x_t[i][j]);
//            max_y=max(max_y,y_t[i][j]);
//            
//        }
//    }
//    
//    // Creo i files per fare il filmato.
//    
//    long double dx;
//    long double dy;
//    
//    if (n_c>4000) {
//        dx=(max_x-min_x)/sqrt(n_c);
//        dy=(max_y-min_y)/sqrt(n_c);
//    }else {
//        dx=0.01;
//        dy=0.01;
//    }
//    
//    
//    
//    long double x_delta_hist=min_x;
//    long double y_delta_hist=min_y;
//    
//    int n_dx=0;
//    int n_dy=0;
//    
//    while (x_delta_hist<=max_x) {
//        n_dx++;
//        x_delta_hist+=dx;
//    }
//    
//    while (y_delta_hist<=max_y) {
//        n_dy++;
//        y_delta_hist+=dy;
//    }
//    
//    
//    max_z=histogram_3D_gnuplot(max_x, max_y, min_x, min_y,n_dx ,n_dy , dx, dy, x_t, y_t, n_c, dim_col_t, 1,f);
//    
//    // Riproduzione Filmato.
//    
//    cout << "Filmato  3d gnuplot" << endl;
//    
//    
//    // Plot baricentro.
//    
//    cout << "plot the baricenter trajectory? \npress 0 for yes, 1 for no ";
//    sssr(risp);
//    if (risp==0) {
//        //        baricentro_plot(x_t,y_t,n_c,dim_col_t);
//    }        
//    
//    
//    // Analysis runs
//    
//    cout << "plot the Analysis of the jumps? \npress 0 for yes, 1 for no ";
//    sssr(risp);
//    
//    if (risp==0) {
//        //        gnuplot_analysis_run();
//    }
//    
//}
