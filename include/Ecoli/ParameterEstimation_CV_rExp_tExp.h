//
//  ParameterEstimation_CV_rExp_tExp.h
//  Ecoli_4.1.0
//
//  Created by Stefano Belloni on 21/07/15.
/*This program is free software - GNU General Public License Verison 2*/
//

#ifndef Ecoli_4_1_0_ParameterEstimation_CV_rExp_tExp_h
#define Ecoli_4_1_0_ParameterEstimation_CV_rExp_tExp_h

#include <iostream>
#include <vector>
#include "E_Coli.h"
#include "CV_rExp_tExp.h"
#include "s_lambda.h"
#include "Q_tau_stat.h"

#include "FunzRand.h"
#include "Funz_C.h"
#include "Funz_C_Inter.h"

/** \brief Class for Statistical Analysis of a bacterium for CV_rExp_tExp:
 *Base class for statistical estimation and simulation
 */

class ParameterEstimation_CV_rExp_tExp : public CV_rExp_tExp{
    
    public:
    
//    s_lambda s_lambda_r;
//    long double s_lambda_t;
    
//    string distribution_I_r;    
//    long double I_tau_r[2];
//    string distribution_I_t;
//    long double I_tau_t[2];
    
    // methods
    
//    friend s_lambda s_F_lambda_r(E_coli *batterio, vector<Q_tau_stat> vector_lambda, int n_vect, int funz_L);
    long double f_lambda();  // virtual from CV_rExp_tExp
    void s_F_lambda_r(vector<Q_tau_stat> vector_lambda, int n_vect);
//    void gnuplotFunzInternalDynalmic(string title, int save_, int gen_con_sim);
    int saveIntDyn(string nameFile);
    
    ParameterEstimation_CV_rExp_tExp();
    ParameterEstimation_CV_rExp_tExp(const ParameterEstimation_CV_rExp_tExp& modello);
    
    void print_info(std::ofstream &file_save);
    
};


#endif
