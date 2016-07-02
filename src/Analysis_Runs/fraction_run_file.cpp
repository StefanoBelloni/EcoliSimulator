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
void fraction_run_file(string file_write, int cont_salti, vector<int> tau_vector, int n_tau_x, double dx, double tau_max, double somma_tau)
{
    
    double tau=0;  
    double tau_x=0;    
    const char * write = file_write.c_str();
//    int mediana=0;
//    double tau_mediana;
    ofstream file_tau;   
    
    file_tau.open(write);
    
    tau_x=tau_max;
    tau=somma_tau;
    
    for (int i=n_tau_x-1; i>=0; i--) {
        
        // Da rivedere: che converta da int into double !
        tau = tau_vector[i]+tau;                
        file_tau << tau_x << " " << (double)tau/cont_salti << " " << (double)tau_vector[i]/(cont_salti*dx) << endl;
        tau_x=max(0,tau_x-dx);
//        cont_salti++;
//        cout << "***********\n";
//        cout << "tau_x: = " << tau_x << ": " << (double)tau/cont_salti << " " << (double)tau_vector[i]/cont_salti << endl;
        
        
        tau_vector[i]=0;        
        
    }
    
    //------------------------------------->  // exp(-x)  <- allora exp(-0)=1!! 
    
    file_tau << tau_x << " " << 1 << " " << 1 << endl;
    
    file_tau.close();
    
}
