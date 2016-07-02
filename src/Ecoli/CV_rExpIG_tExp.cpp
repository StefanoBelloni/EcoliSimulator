//
//  CV_rExpIG_tExp.cpp
//  E_Coli2.2
//
//  Created by Stefano Belloni on 01/06/15.
/*This program is free software - GNU General Public License Verison 2*/
//

#include "CV_rExpIG_tExp.h"
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


CV_rExpIG_tExp::CV_rExpIG_tExp():CV_rIG_tExp(){
    Tipo_batterio = "CV-rExpIG-tExp";
    codice_batterio = EcoliType::CV_RIGEXP_TEXP;
    barriera_r = reset_barrier();
//    barriera_r=Exp_dist(); // E' gia' implementata come exp distribution ...
    B_0=1.6;
}

CV_rExpIG_tExp::CV_rExpIG_tExp(const CV_rExpIG_tExp& modello):CV_rIG_tExp(modello){
    Tipo_batterio = modello.Tipo_batterio;
    codice_batterio = modello.codice_batterio;
    barriera_r = reset_barrier();
    //    barriera_r=Exp_dist(); // E' gia' implementata come exp distribution ...
//    B_0=1.6;
}

void CV_rExpIG_tExp::reset_par(){
    
    CV_rExp_tExp::reset_par();
    
    Tipo_batterio = "CV-rExpIG-tExp";
    
    //    barriera_r=Exp_dist(); // E' gia' implementata come exp distribution ...
    B_0=1.6;
    
}

