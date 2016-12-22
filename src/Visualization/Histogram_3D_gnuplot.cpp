//
//  Histogram_3D_gnuplot.cpp
//  E_Coli2.2
//
//  Created by Stefano Belloni on 01/06/15.
/*This program is free software - GNU General Public License Verison 2*/
//

#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
#include <cstdio>
#include <cstdlib>

#ifndef NO_M_THREAD
#include <array>
#endif

#include "LoadBar.hpp"
#include "GlobalVariables.h"
#include "Funz_C.h"
#include "Funz_C_Par.h"

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

/**
 * This function create the 3d histogram of the density of the population and the surface of the function c.
 * If interacting_population, fun c was already saved while solving the PDE
 * We might pass the vector< vecotos as reference to avoid the copy ... they are big matrix
 * @param max_(var) min_(var) limit of the domain
 * @param n_d(var) number of division of the axis-var
 * @param d(var) size step
 * @param x,y vector of positions
 * @param n_c number bacteria
 * @param dim_col_t how many time-points are saved.
 * @param n_salti_colonne how many time-point jumps between two data to be saved and plot
 */

long double histogram_3D_gnuplot(long double max_x, long double max_y, long double min_x,long double min_y, int n_dx, int n_dy, long double dx, long double dy, vector<vector<long double> > x,vector<vector<long double> > y, int n_c, int dim_col_t, int n_salti_colonne, Funz_C *f, long double &maxC, string name_file_info)
{
    
    maxC=-1000;
    
    if (f->interact==0)
        maxC=5;
    
    int i_x,i_y,i_c; // Contatori vari.
//    long double delta_x=0;
    long double delta_x_p=dx; // estremi intervallo x histogram
//    long double delta_y=0;
    long double delta_y_p=dy; // estremi intervallo y histogram
//    int found=0; // se ho sistemato il batterio considerato --> setto la variabile pari a 1.
    int max_z=0;
    
    long double Dt=0.1;
#if NO_M_THREAD
    long double x_0[2];
#else
    array<long double,2> x_0;
#endif    
//    long double T_f=1.0;
    long double c=0.0;
    int num_funz=0;
    
    char buffer[52]; // The filename buffer.
    
    vector<vector<int> > z;
    
    
    // Non è il file con le informazione richieste questo file!!!
    ifstream file_info(name_file_info.c_str());
    
    ofstream file3D_hist;
    ofstream file3D_c;
    
    cout << BOLDBLACK << "\nELABOAZIONE DATI FILMATO" << RESET<< endl;
    
    z.resize( n_dx , vector<int>( n_dy , 0 ) );
    
    cout << "Matrix for z created" << endl;
    
    // Recupero i dati dal file sulle caratteristiche tecniche.
    string title;
    int n_data = 1;
    
    file_info >> title;
    file_info >> num_funz;
    file_info >> Dt;
    file_info >> n_data; // const_salv
    Dt=Dt*n_data;
    file_info.close();
    
    cout << "Number Frames "<< dim_col_t << endl;
    
    for (int n_colonna=0; n_colonna<dim_col_t-1; n_colonna+=n_salti_colonne) {
        
        loadbar(n_colonna,dim_col_t);
        
        // Preparazione matrice e nomi ... z.resize( n_dx , vector<int>( n_dy , 0 ) ); non sembra reinizializzare a 0!!
        
//        cout << "Colonna " << n_colonna << endl;
        
        snprintf(buffer, sizeof(char) * 52, "film3Dh%i.dat", n_colonna+1);
        
        file3D_hist.open(buffer);
        
        if (f->interact!=0) {
            snprintf(buffer, sizeof(char) * 52, "film3Dc%i.dat", n_colonna+1);            
            file3D_c.open(buffer);
            if (!file3D_c.is_open()) {
                cout << "ERRORE NELLA SCRITTURA DEL FILE" << endl;
                return -2;
            }
        }
        

        
        if (file3D_hist.is_open()){
            
            for (i_c=0; i_c<n_c; i_c++) { // controllo ogni batterio
                
//                find the index, and add the presence of a bacterium for that index
                
                i_x=max(0,min(n_dx-1,floor((x[n_colonna][i_c]-min_x)/dx)));
                i_y=max(0,min(n_dy-1,floor((y[n_colonna][i_c]-min_y)/dy)));
                z[i_x][i_y]++;
                
            }
            
            delta_x_p=min_x+dx/2;
            delta_y_p=min_y+dy/2;
            
            //**************************************************
            //    Salvo i dati sul file numero "n_colonna"
            //**************************************************
            
            for (i_x=0; i_x<n_dx; i_x++) {
                for (i_y=0; i_y<n_dy; i_y++) {
                    x_0[0]=delta_x_p;
                    x_0[1]=delta_y_p;
                    max_z=max(max_z,z[i_x][i_y]);
                    file3D_hist << delta_x_p << " " << delta_y_p << " " << z[i_x][i_y] << endl;
                    
                    if (f->interact!=0) {
                        c = f->new_F_C(Dt*n_colonna,x_0);
                        maxC = fmax(c,maxC);
                        file3D_c << delta_x_p << " " << delta_y_p << " " << c << endl;
//                        cout << "file3Dc" << endl;
                    }
                    
                    delta_y_p+=dy;
                    z[i_x][i_y]=0;
                }
                file3D_hist << endl;
                file3D_c << endl;
                delta_y_p=min_y+dy/2;
                delta_x_p+=dx;
                
            }
            
            // Necessario per leggere e scrivere diversi file con un solo ifstream!
            
            file3D_hist.close();
            file3D_c.close();
            
        }else{
            cout << "ERRORE NELLA SCRITTURA DEL FILE" << endl;
            return -2;
        }
    }
    
    cout << "\ncreation file 3D histograms ... \n";
    
    return max_z;
}


/**
 * This function create a "hitsogram-Percentage" of bacteria going up down or constant gradient
 */

int percSignFunzC(vector< vector<long double> > c_t, int n_c, int dim_col_t, string nameInfo){
    
    cout << "\nElaboration file 'PercUpDownh.dat'" << endl;
    
    int const_salv;
    string temp;
    long double Dt;
    ifstream file_info;
    
    file_info.open(nameInfo.c_str());
    file_info >> temp;
    file_info >> const_salv;
    file_info >> Dt;
    file_info >> const_salv;
    
    Dt=Dt*const_salv*(epsilon*epsilon);
    file_info.close();
    
    string name = "PercUpDownh.dat"; // The filename buffer.
    ofstream fileP;
    vector<vector<long double> > z;
    z.resize( dim_col_t , vector<long double>( 4 , 0 ) );
    
    fileP.open(name.c_str());
    
    if (fileP.is_open()){
        
        
        for (int n_colonna=0; n_colonna<dim_col_t-1; n_colonna++) {
            
            loadbar(n_colonna,dim_col_t);
            
            for (int i_c=0; i_c<n_c; i_c++) {
                
                z[n_colonna][c_t[n_colonna][i_c]+1]++;
                
            }
            
            
            fileP << Dt*n_colonna << " " << z[n_colonna][0]/n_c
                                   << " " << z[n_colonna][1]/n_c
                                   << " " << z[n_colonna][2]/n_c
                                   << " " << z[n_colonna][3]/n_c << endl;
            
//            cout << Dt*n_colonna << " " << z[n_colonna][0]/n_c
//            << " " << z[n_colonna][1]/n_c
//            << " " << z[n_colonna][2]/n_c << endl;
        }
        

        fileP.close();
        
        
    }else{
        cout << "ERRORE NELLA SCRITTURA DEL FILE" << endl;
        return -2;
    }
    
    
    return 0;
    
}

