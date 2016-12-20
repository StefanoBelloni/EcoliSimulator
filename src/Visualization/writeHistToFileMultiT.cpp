//
//  writeHistToFileMultiT.cpp
//  Ecoli_4.1.5
//
//  Created by Stefano Belloni on 21/05/16.
//  Copyright © 2016 Stefano Belloni. All rights reserved.
//

#include "writeHistToFileMultiT.hpp"
#include "Colori.h"
#include "LoadBar.hpp"
#include "Funz_C.h"
#include <system_error>

#include <sstream>
#include <iostream>
#include <fstream>
#include <cmath>

#ifndef NO_M_THREAD
#include <thread>
#include <array>
#endif


using namespace std;

//Funzioni max e min
#ifndef max
#define max( a, b ) ( ((a) > (b)) ? (a) : (b) )
#endif
#ifndef min
#define min( a, b ) ( ((a) < (b)) ? (a) : (b) )
#endif

int writeLog(std::string what, string msg);

#ifndef NO_M_THREAD

/*! \brief This function write the histogram of the density to file: multithread.
 */
void writeHistToFileMultiT(long double delta_y_p, long double delta_x_p, int dim_col_t, int n_salti_colonn,
                           const int& cont_sim, const int& n_dx, const int& n_dy, const int& n_c,
                           const long double& min_x, const long double& min_y,
                           const long double& dx, const long double& dy,
                           vector<vector<long double> >& x,vector<vector<long double> >& y,
                           const int& n_x_min, const int& n_x_max,
                           const int& n_y_min, const int& n_y_max,
                           int &max_z, int n_thread)
{
    
//    cout << "writeHistToFileMultiThread thread ...\n";
    
    bool display = false;
    
    if (n_thread==0) {
        n_thread=1;
        display = true;
    }

    const long double delta_y_p_init = delta_y_p;
    const long double delta_x_p_init = delta_x_p;

    
    vector<int> max_z_local(n_thread);
    vector<thread> th;
    
    int start_for=0, end_for = 0, update_for=n_salti_colonn;
    int increaseThread;
    
    increaseThread = dim_col_t/n_thread;
    
    if (increaseThread==0) {
        cout << BOLDRED <<"Error ... something went wrong ... sorry" << RESET << endl;
        return;
    }
    
    for (int i=0; i<n_thread-1; i++) {
        end_for+=increaseThread;
        
//        cout << "**************************************"
//             << "thread n. " << i << endl
//             << "start_for = " << start_for << endl
//             << "end_for = " << end_for << endl
//             << "**************************************" << endl;
        
        th.push_back(std::thread(startThred_writeHist,start_for,end_for,update_for,cont_sim, n_c, n_dx, n_dy,
                                                      dx, dy,
                                                      n_x_min, n_x_max,
                                                      n_y_min, n_y_max,
                                                      min_x, min_y,
                                                      delta_y_p, delta_x_p,
                                                      delta_y_p_init,
                                                      delta_x_p_init,
                                 std::ref(x),std::ref(y),
                                 std::ref(max_z_local[i]),(i==0)));
        start_for=end_for;
        
        
    }
    
//    cout << "**************************************"
//         << "thread main " << endl
//         << "start_for = " << start_for << endl
//         << "end_for = " << dim_col_t-1 << endl
//         << "**************************************" << endl;
    


    
    startThred_writeHist(start_for,dim_col_t-1,update_for,cont_sim, n_c, n_dx, n_dy,dx, dy,
                         n_x_min, n_x_max,
                         n_y_min, n_y_max,
                         min_x, min_y,
                         delta_y_p, delta_x_p,
                         delta_y_p_init,
                         delta_x_p_init,
                         std::ref(x),std::ref(y),
                         std::ref(max_z_local[n_thread-1]), display);

    for (int i = 0; i<n_thread-1; i++) {
//        cout << "th["<<i<<"].join();" << endl;
        try{
            th[i].join();
        }catch (std::system_error &e) {
            cout << "error:" << endl;
            cout << "std::system_error: " << e.code().message() << endl;
            return;
        }
    }
//    cout << "Ho finito gli istogrammi !" << endl;
    max_z=0;
    for (int i=0; i<n_thread; i++) {
        max_z=max(max_z, max_z_local[i]);
    }
}
//*******************************************************************************************************************************
//*******************************************************************************************************************************

/*! \brief implements the loop over time for the given thred
 */

void startThred_writeHist(const int start_for, const int end_for, const int update_for,
                          const int cont_sim, const int n_c, const int n_dx, const int n_dy,
                          const long double dx, const long double dy,
                          const int n_x_min, const int n_x_max,
                          const int n_y_min, const int n_y_max,
                          const long double min_x, const long double min_y,
                          long double delta_y_p, long double delta_x_p,
                          const long double delta_y_p_init,
                          const long double delta_x_p_init,
                          vector<vector<long double> >& x,vector<vector<long double> >& y,
                          int& max_z_local, bool display)
{
    
//    cout << "void startThred_writeHist ...\n";
    
    char buffer[52]; // The filename buffer.
    ofstream file3D_hist;
    
    vector<vector<int> > z;
    z.resize( n_dx , vector<int>( n_dy , 0 ) );
    
    int i_x,i_y;
    
    long double max_z=0.0;
    
    for (int n_colonna=start_for; n_colonna<end_for; n_colonna+=update_for) {
        
        if(display)
            loadbar(n_colonna,end_for);
        
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
            string msg("Error writing file: ");
            msg+=buffer;
            writeLog("ERROR",msg);
            return;
        }
    }
    
    max_z_local = max_z;
    
}
//*******************************************************************************************************************************
//*******************************************************************************************************************************

/*! \brief it writes the histogram of the function c to file: multithread.
 */

void writeFunzCToFileMultiT(long double delta_y_p, long double delta_x_p, int dim_col_t, int n_salti_colonn,
                            const int cont_sim, const int n_dx, const int n_dy,
                            const long double min_x, const long double min_y,
                            const long double dx, const long double dy,
                            const int n_x_min, const int n_x_max,
                            const int n_y_min, const int n_y_max,
                            long double& maxC,
                            const long double Dt,
                            Funz_C *f,
                            int n_thread)
{
    const long double delta_y_p_init = delta_y_p;
    const long double delta_x_p_init = delta_x_p;
    
    vector<long double> max_C_local(n_thread);
    vector<thread> th;
    
    int start_for=0, end_for = 0, update_for=n_salti_colonn;
    int increaseThread;
    increaseThread = dim_col_t/n_thread;
    
    if (increaseThread==0) {
        cout << BOLDRED <<"Error ... something went wrong ... sorry" << RESET << endl;
        stringstream msg;
        msg.str("");
        msg << "Error lunching multithread."<< endl;
        
        writeLog("ERROR",msg.str());
        return;
    }
    for (int i=0; i<n_thread-1; i++) {
        end_for+=increaseThread;
//        cout << "**************************************"
//        << "thread n. " << i << endl
//        << "start_for = " << start_for << endl
//        << "end_for = " << end_for << endl
//        << "**************************************" << endl;
        
        th.push_back(std::thread(startThred_writeFunC,start_for, end_for, update_for, cont_sim, dx, dy, n_x_min, n_dx+n_x_max, n_dy+n_y_min, n_y_max, min_x, min_y, delta_y_p, delta_x_p, delta_y_p_init, delta_x_p_init, Dt, f, std::ref(max_C_local[i])));
        start_for=end_for;
    }
//    cout << "**************************************"
//    << "thread main " << endl
//    << "start_for = " << start_for << endl
//    << "end_for = " << dim_col_t-1 << endl
//    << "**************************************" << endl;

    startThred_writeFunC(start_for, end_for, update_for, cont_sim, dx, dy, n_x_min, n_dx+n_x_max, n_dy+n_y_min, n_y_max, min_x, min_y, delta_y_p, delta_x_p, delta_y_p_init, delta_x_p_init, Dt, std::ref(f), std::ref(max_C_local[n_thread-1]));
    
    for (int i = 0; i<n_thread-1; i++) {
//        cout << "th["<<i<<"].join();" << endl;
        try{
            th[i].join();
        }catch (std::system_error &e) {
            cout << "th["<<i<<"].join();" << endl;
            cout << "error:" << endl;
            cout << "std::system_error: " << e.code().message() << endl;
            
            stringstream msg;
            msg.str("");
            msg << "std::system_error: " << e.code().message() << endl;
            
            writeLog("ERROR: joining thread ",msg.str());
            
            return;
        }
    }
    maxC = 0.0;
    for (int i=0; i<n_thread; i++) {
        maxC=max(maxC, max_C_local[i]);
    }
}
//*******************************************************************************************************************************
//*******************************************************************************************************************************

/*! \brief implements the loop over time for the given thred
 *
 * NOTE: remember that here n_dx+n_x_max = n_x_max
 */

void startThred_writeFunC(const int start_for, const int end_for, const int update_for,
                          const int cont_sim,
                          const long double dx, const long double dy,
                          const int n_x_min, const int n_x_max,
                          const int n_y_min, const int n_y_max,
                          const long double min_x, const long double min_y,
                          long double delta_y_p, long double delta_x_p,
                          const long double delta_y_p_init,
                          const long double delta_x_p_init,
                          long double Dt, Funz_C* f, long double& maxC)
{
    char buffer[52]; // The filename buffer.
    ofstream file3D_c;
    array<long double,2> x_0;
    long double c=0;
    int i_x=0,i_y=0;
    
    for (int n_colonna=start_for; n_colonna<end_for; n_colonna+=update_for) {

        snprintf(buffer, sizeof(char) * 52, "sim%03dfilm3Dc%i.dat",cont_sim, n_colonna+1);
        file3D_c.open(buffer);
        if (!file3D_c.is_open()) {
            cout << "ERRORE NELLA SCRITTURA DEL FILE" << endl;
            
            string msg("Error reading file:");
            msg+=buffer;
            writeLog("ERROR",msg);
            
            return;
        }
        // initial data histogram ...
        delta_x_p = delta_x_p_init;
        delta_y_p = delta_y_p_init;
        
        //    Salvo i dati sul file numero "n_colonna"
        for (i_x=-n_x_min; i_x</*n_dx+*/n_x_max; i_x++) {
            for (i_y=-n_y_min; i_y</*n_dy+*/n_y_max; i_y++) {
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
}
#endif
