//
//  fraction_run_file.cpp
//  E_Coli2.2
//
//  Created by Stefano Belloni on 29/05/15.
/*This program is free software - GNU General Public License Verison 2*/
//

#include <iostream>
#include <sstream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>
#include <iomanip>

using namespace std;


//Funzioni max e min

#ifndef max
#define max( a, b ) ( ((a) > (b)) ? (a) : (b) )
#endif
#ifndef min
#define min( a, b ) ( ((a) < (b)) ? (a) : (b) )
#endif


// COSTANTI

#include "constants.h" //#define pi 3.141592653589793238462

/** This function calculate the fraction of run/tumble bigger then a given value.
 *
 * @param file_write: we save the data in the file pass by  file_write
 * @param cont_salti number total jumps
 * @param vector of run/tumble (t) within the range of the index i, i.e. tau_min*dx*(i-1)<t< tau_min*dx*i
 * @param n_tau_x number of divition of length run/tumble
 * @param dx time-step in divition of the run/tumble interval
 * @param tau_max maximum tau to be display, left limit of the interval [0,tau_max] where we do the fraction of run
 * @param somma_tau sum of all the tau of the same kind (up/down/const etc. gradient)
*/
void fraction_run_file(string file_write, int cont_salti, vector<int> tau_vector, int n_tau_x, long double dx, long double tau_max, long double somma_tau)
{
    
    long double tau=0;  
    long double tau_x=0;    
    const char * write = file_write.c_str();
//    int mediana=0;
//    long double tau_mediana;
    ofstream file_tau;   
    
    file_tau.open(write);
    
    tau_x=tau_max;
    tau=somma_tau;
   
    //cout << "somma_tau = " << somma_tau << endl;

    for (int i=n_tau_x-1; i>=0; i--) {
        
        tau = (long double)tau_vector[i]+tau;                
        file_tau << std::setprecision(20) << tau_x << " " << tau/(long double)cont_salti << " " << (long double)tau_vector[i]/((long double)cont_salti*dx) << endl;
        tau_x=max(0.0,tau_x-dx);
//        cont_salti++;
//        cout << "***********\n";
//        cout << "tau_x: = " << tau_x << ": " << (long double)tau/cont_salti << " " << (long double)tau_vector[i]/cont_salti << endl;
        
    //cout << "tau_x = " << tau_x << " , dx = " << dx << endl;
    //cout << "tau_vector["<<i<<"] = " << tau_vector[i] << "\n";
    //cout << "tau = " << tau << endl;
    //cout << "cont_salti = " << cont_salti << endl;    
        tau_vector[i]=0;        
        
    }
   

    //------------------------------------->  // exp(-x)  <- allora exp(-0)=1!! 
    
    //file_tau << 0.0 << " " << 1 << " " << 1 << endl;
    
    file_tau.close(); 
}
