//
//  ParameterEstimation_E_Coli.h
//  Ecoli_4.1.0
//
//  Created by Stefano Belloni on 20/07/15.
/*This program is free software - GNU General Public License Verison 2*/
//

#ifndef Ecoli_4_1_0_ParameterEstimation_E_Coli_h
#define Ecoli_4_1_0_ParameterEstimation_E_Coli_h

#include <iostream>
#include <vector>
#include "E_Coli.h"
#include "ParameterEstimation_E_Coli.h"
#include "s_lambda.h"
#include "Q_tau_stat.h"

#include "FunzRand.h"
#include "Funz_C.h"
#include "Funz_C_Inter.h"

// s_ means stima_di_

/** \brief Base Class for Statistical Analysis of a bacterium:
 *Base class for statistical estimation and simulation 
 */

class ParameterEstimation_E_coli : public E_coli{
   
public:
    
    ParameterEstimation_E_coli();
    ParameterEstimation_E_coli(const E_coli& modello);

protected:
    
    double s_lambda_t;
    
    int GoodFit;
    double KS_D_n;
    double KS_L1;
    
    string distribution_I_r;    
    double I_tau_r[2];
    string distribution_I_t;
    double I_tau_t[2];
    
    // methods
    
public:
    
    void s_F_lambda_r(vector<Q_tau_stat> vector_lambda, int n_vect);
    void set_GoodnessFit(int Good, double D_n, double cumD_n);
//    int agg_dyn(double dt, double t);
    
    
};




#endif
