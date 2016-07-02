//
//  ParameterEstimation_CV_rExp_tExp.cpp
//  Ecoli_4.1.0
//
//  Created by Stefano Belloni on 21/07/15.
/*This program is free software - GNU General Public License Verison 2*/
//

#include <iostream>
#include "ParameterEstimation_CV_rExp_tExp.h"

double ParameterEstimation_CV_rExp_tExp::f_lambda(){
    
    return s_lambda_r.s_funz_lambda(Q);
    
};


ParameterEstimation_CV_rExp_tExp::ParameterEstimation_CV_rExp_tExp():CV_rExp_tExp(){
    
    Tipo_batterio = "P-CV-rExp-tExp";
    codice_batterio = EcoliType::PAR_CV_REXP_TEXP;
    simulation = 1;
    
};

ParameterEstimation_CV_rExp_tExp::ParameterEstimation_CV_rExp_tExp(const ParameterEstimation_CV_rExp_tExp& modello):CV_rExp_tExp(modello){
    
    Tipo_batterio = modello.Tipo_batterio;
    codice_batterio=modello.codice_batterio;
    simulation = modello.simulation;
    
}