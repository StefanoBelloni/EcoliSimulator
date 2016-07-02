//
//  ParameterEstimation_CV_rIG_tExp.cpp
//  Ecoli_4.1.0
//
//  Created by Stefano Belloni on 21/07/15.
/*This program is free software - GNU General Public License Verison 2*/
//

#include <iostream>
#include <vector>
#include "ParameterEstimation_CV_rIG_tExp.h"
#include "s_lambda.h"
#include "Q_tau_stat.h"

#include "FunzRand.h"
#include "Funz_C.h"
#include "Funz_C_Inter.h"

double ParameterEstimation_CV_rIG_tExp::f_lambda(){
    
    return s_lambda_r.s_funz_lambda(Q);
    
};

double ParameterEstimation_CV_rIG_tExp::f_sigma(){
    
//    cout << "Q_max = " << s_lambda_r.Q_max << endl;
//    cout << "Q_min = " << s_lambda_r.Q_min << endl;
    
    return s_lambda_r.s_funz_sigma(Q);
    
};

ParameterEstimation_CV_rIG_tExp::ParameterEstimation_CV_rIG_tExp():CV_rIG_tExp(){
    
    Tipo_batterio = "P-CV-rIG-tExp";
    codice_batterio = EcoliType::PAR_CV_RIG_TEXP;
    simulation = 1;
    
};

ParameterEstimation_CV_rIG_tExp::ParameterEstimation_CV_rIG_tExp(const ParameterEstimation_CV_rIG_tExp& modello):CV_rIG_tExp(modello){
    
    Tipo_batterio = modello.Tipo_batterio;
    codice_batterio = modello.codice_batterio;
    simulation = modello.simulation;
    
}
