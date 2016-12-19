//
//  histogram_3d_gnuplotV2.cpp
//  Ecoli_4.1.5
//
//  Created by Stefano Belloni on 31/03/16.
//  Copyright © 2016 Stefano Belloni. All rights reserved.
//

#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
#include <system_error>


#ifndef NO_M_THREAD
#include <thread>
#endif


#include "LoadBar.hpp"
#include "GlobalVariables.h"
#include "Funz_C.h"

#include <array>

#include "writeHistToFileMultiT.hpp"

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

//void wait_for_key ();
void writeHistToFile(long double delta_y_p, long double delta_x_p, int dim_col_t, int n_salti_colonne,
                    const int& cont_sim, const int& n_dx, const int& n_dy, const int& n_c,
                    const long double& min_x, const long double& min_y,
                    const long double& dx, const long double& dy,
                    vector<vector<long double> >& x,vector<vector<long double> >& y,
                    const int& n_x_min, const int& n_x_max,
                    const int& n_y_min, const int& n_y_max,int &max_z);

void writeFunzCToFile(long double delta_y_p, long double delta_x_p, int dim_col_t, int n_salti_colonne,
                      const int cont_sim, const int n_dx, const int n_dy,
                      const long double min_x, const long double min_y,
                      const long double dx, const long double dy,
                      const int n_x_min, const int n_x_max,
                      const int n_y_min, const int n_y_max,
                      long double& maxC,
                      const long double Dt,
                      Funz_C *f);


/*! Second version of histogram_3D_gnuplot*/

long double histogram_3D_gnuplotV2(long double max_x, long double max_y, long double min_x,long double min_y, int n_dx, int n_dy, long double dx, long double dy, vector<vector<long double> >& x,vector<vector<long double> >& y, int n_c, int dim_col_t, int n_salti_colonne, Funz_C *f, long double &maxC, int risp_Max, int cont_sim, string name_file_info)
{
    if (f->interact!=0)
        maxC=0;
    
    int i_x,i_y,i_c; // Contatori vari.
    //    long double delta_x=0;
    long double delta_x_p=dx; // estremi intervallo x histogram
    //    long double delta_y=0;
    long double delta_y_p=dy; // estremi intervallo y histogram
    //    int found=0; // se ho sistemato il batterio considerato --> setto la variabile pari a 1.
    int max_z=0;
    
    long double Dt=0.1;
    array<long double,2> x_0;
    long double T_f=1.0;
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
    
    file_info >> Dt;
    file_info >> num_funz;
    file_info >> T_f;
    file_info.close();
    
    cout << "Number Frames "<< dim_col_t << endl;
    
    
    int n_x_min=0;
    int n_y_min = 0;
    
    int n_x_max = 0;
    int n_y_max = 0;
    
    
    if (risp_Max == 0){
        
        n_x_min = floor((min_x-f->min_x)/dx);
        n_y_min = floor((min_y-f->min_y)/dx);
        
        n_x_max = floor((f->max_x-min_x)/dx);
        n_y_max = floor((f->max_y-min_y)/dx);
        
        delta_x_p=f->min_x+dx/2;
        delta_y_p=f->min_y+dy/2;
        
        
        
    }else{
        
        delta_x_p=min_x+dx/2;
        delta_y_p=min_y+dy/2;
    }
    
    const long double delta_y_p_init = delta_y_p;
    const long double delta_x_p_init = delta_x_p;
    
    for (int n_colonna=0; n_colonna<dim_col_t-1; n_colonna+=n_salti_colonne) {
        
        loadbar(n_colonna,dim_col_t);
        
        // Preparazione matrice e nomi ... z.resize( n_dx , vector<int>( n_dy , 0 ) ); non sembra reinizializzare a 0!!

        snprintf(buffer, sizeof(char) * 52, "sim%03dfilm3Dh%i.dat",cont_sim, n_colonna+1);
        
        file3D_hist.open(buffer);
        
        if (f->interact!=0) {
            // TODO: name sim in interacting ...
            snprintf(buffer, sizeof(char) * 52, "sim%03dfilm3Dc%i.dat",cont_sim, n_colonna+1);
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
            
//            delta_x_p=f->min_x+dx/2;
//            delta_y_p=f->min_y+dy/2;
            
            // initial data histogram ...
            delta_x_p = delta_x_p_init;
            delta_y_p = delta_y_p_init;
            
            //**************************************************
            //    Salvo i dati sul file numero "n_colonna"
            //**************************************************
            
            
            
            for (i_x=-n_x_min; i_x<n_dx+n_x_max; i_x++) {
                for (i_y=-n_y_min; i_y<n_dy+n_y_max; i_y++) {
                    
                    x_0[0]=delta_x_p;
                    x_0[1]=delta_y_p;

                    if (i_x>=0 && i_x<n_dx && i_y>=0 && i_y<n_dy) {
                        max_z=max(max_z,z[i_x][i_y]);
                        file3D_hist << delta_x_p << " " << delta_y_p << " " << z[i_x][i_y] << endl;
                        z[i_x][i_y]=0;
                    }else{
                        file3D_hist << delta_x_p << " " << delta_y_p << " " << 0 << endl;
                    }
                    
                    if (f->interact!=0) {
                        c = f->new_F_C(Dt*n_colonna,x_0);
                        maxC = fmax(c,maxC);
                        file3D_c << delta_x_p << " " << delta_y_p << " " << c << endl;

                    }
                    
                    delta_y_p+=dy;

                }
                
                file3D_hist << endl;
                file3D_c << endl;
                delta_y_p=delta_y_p_init;  //senza +dy/2 c'è gia alla dichiarazione di delta_y_p_init ...
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

#ifndef NO_M_THREAD

/*! \brief This is a variation of histogram_3D_gnuplotV2, where we use mutithread ...
 * one thread create the histogram for the density, the other create the surface for the function c (if it is no_interaction mode).
 */

long double histogram_3D_gnuplotV2MultiThread(long double max_x, long double max_y, long double min_x,long double min_y, int n_dx, int n_dy, long double dx, long double dy, vector<vector<long double> >& x,vector<vector<long double> >& y, int n_c, int dim_col_t, int n_salti_colonne, Funz_C *f, long double &maxC, int risp_Max, int cont_sim, string name_file_info)
{    
    if (f->interact!=0)
        maxC=0;
    
    long double delta_x_p=dx; // estremi intervallo x histogram
    //    long double delta_y=0;
    long double delta_y_p=dy; // estremi intervallo y histogram
    //    int found=0; // se ho sistemato il batterio considerato --> setto la variabile pari a 1.
    int max_z=0;
    long double Dt=0.1;
//    long double T_f=1.0;
    int num_funz=0;
    int n_x_min=0;
    int n_y_min = 0;
    int n_x_max = 0;
    int n_y_max = 0;

    // Non è il file con le informazione richieste questo file!!!
    ifstream file_info(name_file_info.c_str());
    ofstream file3D_hist;
    ofstream file3D_c;
    cout << BOLDBLACK << "\nELABOAZIONE DATI FILMATO" << RESET<< endl;
//    vector<vector<int> > z;
//    z.resize( n_dx , vector<int>( n_dy , 0 ) );
    
    cout << "Matrix for z created" << endl;
    
    // Recupero i dati dal file sulle caratteristiche tecniche.
    
//    file_info >> Dt;
//    file_info >> num_funz;
//    file_info >> T_f;
//    file_info.close();

    string title;
    int n_data = 1;
    
    file_info >> title;
    file_info >> num_funz;
    file_info >> Dt;
    file_info >> n_data; // const_salv
    Dt=Dt*n_data;
    file_info.close();
    
    cout << "Number Frames "<< dim_col_t << endl;
    if (risp_Max == 0){
        n_x_min = floor((min_x-f->min_x)/dx);
        n_y_min = floor((min_y-f->min_y)/dx);
        n_x_max = floor((f->max_x-min_x)/dx);
        n_y_max = floor((f->max_y-min_y)/dx);
        delta_x_p=f->min_x+dx/2;
        delta_y_p=f->min_y+dy/2;
    }else{
        delta_x_p=min_x+dx/2;
        delta_y_p=min_y+dy/2;
    }
    
    std::thread t;
    
    int n_thread = min(n_thread_available,std::thread::hardware_concurrency());
    
//    cout << "n.thread writeHist/FunzCToFile start = " << n_thread << endl;
    
    n_thread-=2;
    
    n_thread=n_thread/2;
    
    bool no_multithread = false;
    
    if (n_thread!=0) {
        no_multithread = dim_col_t/n_thread<10;
    }else{
        no_multithread=true;
    }

    long double maxC_temp = maxC;
    
    if (f->interact!=0) {
        if (no_multithread) {
            t = std::thread(writeFunzCToFile,delta_y_p,delta_x_p,dim_col_t,n_salti_colonne,cont_sim,n_dx,n_dy,min_x,min_y,dx,dy,n_x_min,n_x_max,n_y_min,n_y_max,std::ref(maxC_temp),Dt,f);
        }
    }
    
    if (no_multithread) {
        writeHistToFile(delta_y_p,delta_x_p,dim_col_t,n_salti_colonne, cont_sim,n_dx,n_dy,n_c,min_x,min_y,dx,dy,x,y,n_x_min,n_x_max,n_y_min,n_y_max,max_z);
    }else{
        writeHistToFileMultiT(delta_y_p,delta_x_p,dim_col_t,n_salti_colonne,
                          cont_sim,n_dx,n_dy,n_c,min_x,min_y,dx,dy,x,y,n_x_min,n_x_max,n_y_min,n_y_max,max_z,n_thread);
    }    
    try {
        t.join();
    }catch (std::system_error &e) {
        cout << "join writeFunzCToFile" << endl;
        cout << "std::system_error: " << e.code().message() << endl;
        return -1;
    }
    
    
    maxC = maxC_temp;
    
    cout << "\ncreation file 3D histograms terminated ... \n";
    
//    cout << "max_z = " << max_z << endl;
    
    return max_z;
}

#endif

/*! \brief This function write the histogram of the density to file.
 */

void writeHistToFile(long double delta_y_p, long double delta_x_p, int dim_col_t, int n_salti_colonne,
                    const int& cont_sim, const int& n_dx, const int& n_dy, const int& n_c,
                    const long double& min_x, const long double& min_y,
                    const long double& dx, const long double& dy,
                    vector<vector<long double> >& x,vector<vector<long double> >& y,
                    const int& n_x_min, const int& n_x_max,
                    const int& n_y_min, const int& n_y_max,
                    int &max_z)
{
    
    cout << "writeHistToFile thread ...\n";
    
    char buffer[52]; // The filename buffer.
    ofstream file3D_hist;
    const long double delta_y_p_init = delta_y_p;
    const long double delta_x_p_init = delta_x_p;
    vector<vector<int> > z;
    z.resize( n_dx , vector<int>( n_dy , 0 ) );
    array<long double,2> x_0;
    int i_x=0,i_y=0;

    
    for (int n_colonna=0; n_colonna<dim_col_t-1; n_colonna+=n_salti_colonne) {
        
        
        loadbar(n_colonna,dim_col_t);
        
        // Preparazione matrice e nomi ... z.resize( n_dx , vector<int>( n_dy , 0 ) ); non sembra reinizializzare a 0!!
        
        //        cout << "Colonna " << n_colonna << endl;
        
        snprintf(buffer, sizeof(char) * 52, "sim%03dfilm3Dh%i.dat",cont_sim, n_colonna+1);
        
        file3D_hist.open(buffer);
        
        if (file3D_hist.is_open()){
            
            for (int i_c=0; i_c<n_c; i_c++) { // controllo ogni batterio
                
                //                find the index, and add the presence of a bacterium for that index
                
                i_x=max(0,min(n_dx-1,floor((x[n_colonna][i_c]-min_x)/dx)));
                i_y=max(0,min(n_dy-1,floor((y[n_colonna][i_c]-min_y)/dy)));
                z[i_x][i_y]++;
                
            }
            
            //            delta_x_p=f->min_x+dx/2;
            //            delta_y_p=f->min_y+dy/2;
            
            // initial data histogram ...
            delta_x_p = delta_x_p_init;
            delta_y_p = delta_y_p_init;
            
            //**************************************************
            //    Salvo i dati sul file numero "n_colonna"
            //**************************************************
            
            
            
            for (i_x=-n_x_min; i_x<n_dx+n_x_max; i_x++) {
                for (i_y=-n_y_min; i_y<n_dy+n_y_max; i_y++) {
                    
                    x_0[0]=delta_x_p;
                    x_0[1]=delta_y_p;
 
                    if (i_x>=0 && i_x<n_dx && i_y>=0 && i_y<n_dy) {
                        max_z=max(max_z,z[i_x][i_y]);
                        file3D_hist << delta_x_p << " " << delta_y_p << " " << z[i_x][i_y] << endl;
                        z[i_x][i_y]=0;
                    }else{
                        file3D_hist << delta_x_p << " " << delta_y_p << " " << 0 << endl;
                    }
                    
                    
                    
                    delta_y_p+=dy;

                }
                
                file3D_hist << endl;

                delta_y_p=delta_y_p_init;  //senza +dy/2 c'è gia alla dichiarazione di delta_y_p_init ...
                delta_x_p+=dx;
                
            }
            
            // Necessario per leggere e scrivere diversi file con un solo ifstream!
            
            file3D_hist.close();

            
        }else{
            cout << "ERRORE NELLA SCRITTURA DEL FILE" << endl;
            return;
        }
    }
    
//    cout << "max_z = " << max_z << endl;
    
//    return max_z;
    
}


/*! \brief This function write the histogram of the density to file.
 */

void writeFunzCToFile(long double delta_y_p, long double delta_x_p, int dim_col_t, int n_salti_colonne,
                     const int cont_sim, const int n_dx, const int n_dy,
                     const long double min_x, const long double min_y,
                     const long double dx, const long double dy,
                     const int n_x_min, const int n_x_max,
                     const int n_y_min, const int n_y_max,
                     long double& maxC,
                     const long double Dt,
                     Funz_C *f)
{
    
    cout << "writeFunzCToFile thread ...\n";
    
    char buffer[52]; // The filename buffer.
    ofstream file3D_c;
    const long double delta_y_p_init = delta_y_p;
    const long double delta_x_p_init = delta_x_p;
    array<long double,2> x_0;
    long double c=0;
    int i_x=0,i_y=0;
    
    
    for (int n_colonna=0; n_colonna<dim_col_t-1; n_colonna+=n_salti_colonne) {
        loadbar(n_colonna,dim_col_t);
        // TODO: name sim in interacting ...
        snprintf(buffer, sizeof(char) * 52, "sim%03dfilm3Dc%i.dat",cont_sim, n_colonna+1);
        file3D_c.open(buffer);
        if (!file3D_c.is_open()) {
            cout << "ERRORE NELLA SCRITTURA DEL FILE" << endl;
            return;
        }
        // initial data histogram ...
        delta_x_p = delta_x_p_init;
        delta_y_p = delta_y_p_init;
        //    Salvo i dati sul file numero "n_colonna"
        for (i_x=-n_x_min; i_x<n_dx+n_x_max; i_x++) {
            for (i_y=-n_y_min; i_y<n_dy+n_y_max; i_y++) {
                x_0[0]=delta_x_p;
                x_0[1]=delta_y_p;
                c = f->new_F_C(Dt*n_colonna,x_0);
                maxC = fmax(c,maxC);
                file3D_c << delta_x_p << " " << delta_y_p << " " << c << endl;
                delta_y_p+=dy;
            }
            file3D_c << endl;
            delta_y_p=delta_y_p_init;  //senza +dy/2 c'è gia alla dichiarazione di delta_y_p_init ...
            delta_x_p+=dx;
        }
            // Necessario per leggere e scrivere diversi file con un solo ifstream!
            file3D_c.close();
    }
    
    //    return max_z;
    
}

