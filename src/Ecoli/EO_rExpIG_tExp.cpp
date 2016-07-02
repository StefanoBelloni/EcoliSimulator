//
//  EO_rExpIG_t_Exp.cpp
//  Ecoli_4.1.2
//
//  Created by Stefano Belloni on 18/08/15.
/*This program is free software - GNU General Public License Verison 2*/
//

#include <iostream>


#include "EO_rExpIG_tExp.h"
#include "EO_rIG_tExp.h"
#include "E_Coli.h"
#include "ParameterEstimation_E_Coli.h"
#include "CV_rExp_tExp.h"
#include <fstream>
#include <cmath>
#include "FunzRand.h"

#include "GlobalVariables.h"
#include "sssr.h"

#ifndef max
#define max( a, b ) ( ((a) > (b)) ? (a) : (b) )
#endif
#ifndef min
#define min( a, b ) ( ((a) < (b)) ? (a) : (b) )
#endif

#include "constants.h" //#define pi 3.141592653589793238462


EO_rExpIG_tExp::EO_rExpIG_tExp():EO_rIG_tExp(){
    Tipo_batterio = "EO-rExpIG-tExp";
    codice_batterio = EcoliType::EO_REXP_RIGEXP_TEXP;
    //    barriera_r=Exp_dist(); // E' gia' implementata come exp distribution ...
    B_0=1.6;
}

EO_rExpIG_tExp::EO_rExpIG_tExp(const EO_rExpIG_tExp& modello):EO_rIG_tExp(modello){
    
    Tipo_batterio = modello.Tipo_batterio;
    codice_batterio=modello.codice_batterio;
    barriera_r=reset_barrier();
    B_0=modello.B_0;
    B_1=modello.B_1;
    B_2=modello.B_2;
    
}



void EO_rExpIG_tExp::reset_par(){
    
    EO_rIG_tExp::reset_par();
    
    Tipo_batterio = "EO-rExpIG-tExp";
    //    barriera_r=Exp_dist(); // E' gia' implementata come exp distribution ...
    B_0=1.6;
    
}