//
//  s_lambda.h
//  Ecoli_4.1.0
//
//  Created by Stefano Belloni on 20/07/15.
/*This program is free software - GNU General Public License Verison 2*/
//

#ifndef Ecoli_4_1_0_s_lambda_h
#define Ecoli_4_1_0_s_lambda_h

#include <iostream>
#include <vector>


using namespace std;

/** \brief This class implements the discretization of the function lambda (theory)
 * It is not yet 100% finished 
 */

class s_lambda{
    
    public:
    
    std::vector<long double> lambda;
    std::vector<long double> sigma;
    std::vector<long double> syntetic_indeX;    
    
    std::vector<int> n_data;
    
    long double Q_max;
    long double Q_min;
    
    int distr;   // distr = 0 -> exponential
    long double CumDen;
    long double Cumlambda;
    
    
    long double dQ;
    
    int n_records;
    int pos_steady;
    
    string I_distribution;   // quale distribuzione per l'intervallo di confidenza
    
    // Method
    
    /** empirical probability rate to tumble for the level of the memory term equal to Q*/
    long double s_funz_lambda(long double Q);  //return the proper lambda
    /** variance of the diffusion controlling tumble events*/
    long double s_funz_sigma(long double Q);
    
    /** calculate the statistical intensity*/
    long double StatIntensity(long double dt, long double t, long double Q);
    
    s_lambda();
    /** \brief This function reset the function lambda */
    void reset_lambda(); 
};

#endif
