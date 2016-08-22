//
//  Q_tau_stat.h
//  Ecoli_4.1.0
//
//  Created by Stefano Belloni on 20/07/15.
/*This program is free software - GNU General Public License Verison 2*/
//

#ifndef Ecoli_4_1_0_Q_tau_stat_h
#define Ecoli_4_1_0_Q_tau_stat_h

#include <vector>

/** \brief This class save the statistics of the simulations*/

class Q_tau_stat
{
public:
    
    long double Q;
    long double mean;
    long double var;
    long double invX;
    int n_rec;
    long double max_tau;
    std::vector<long double> tau_measured;
    
    void reset(long double Q_ext);
    Q_tau_stat(long double Q_ext);    // constructor
    
    long double V_IG();               // V_n (n-3)/sum(1/X-1/mean(X))
    
};

/** \brief This class save the results of the test of goodness of fit.*/

class GoodFit{
public:
    int Good_Fit; 
    long double D_n;
    long double cumD_n;
    
    long double Q_min;
    long double Q_max;
    long double dQ;
    
    GoodFit(){Good_Fit=1;D_n=100.0;cumD_n=1000.0;}; // constructor
    
};

#endif
