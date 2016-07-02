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
    
    std::vector<double> lambda;
    std::vector<double> sigma;
    std::vector<double> syntetic_indeX;    
    
    std::vector<int> n_data;
    
    double Q_max;
    double Q_min;
    
    int distr;   // distr = 0 -> exponential
    double CumDen;
    double Cumlambda;
    
    
    double dQ;
    
    int n_records;
    int pos_steady;
    
    string I_distribution;   // quale distribuzione per l'intervallo di confidenza
    
    // Method
    
    /** empirical probability rate to tumble for the level of the memory term equal to Q*/
    double s_funz_lambda(double Q);  //return the proper lambda
    /** variance of the diffusion controlling tumble events*/
    double s_funz_sigma(double Q);
    
    /** calculate the statistical intensity*/
    double StatIntensity(double dt, double t, double Q);
    
    s_lambda();
    
};

#endif
