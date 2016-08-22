//
//  RunUpDownDivision.cpp
//  Ecoli_3.1.4
//
//  Created by Stefano Belloni on 06/07/15.
/*This program is free software - GNU General Public License Verison 2*/
//

#include <iostream>
#include <vector>
#include <cmath>

using std::vector;

/*   Run_hist_frac
 *   
 *   modifico il vettore aggiornando le nuove entrate 
 *
 *
 */


/** This function create for the write type of run/tumble (up/down etc. gradient create the cumulative function)
 *
 */

void RunUpDownDivision(vector<int> &tau_vector, int &somma_tau, int n_tau_x ,int &n_salto, long double tau, long double &tau_mean, long double &tau_var, long double dx){
    
    int index_tau_x=floor(tau/dx);    
    
    n_salto++;    
    tau_mean+=tau;
    tau_var+=tau*tau;
    
    if (index_tau_x >= n_tau_x) {
        somma_tau++;
    }else{
        tau_vector[index_tau_x]++;
    }    
}
