//
//  ParameterEstimation_E_coli.cpp
//  Ecoli_4.1.0
//
//  Created by Stefano Belloni on 22/07/15.
/*This program is free software - GNU General Public License Verison 2*/
//

#include <iostream>
#include "ParameterEstimation_E_Coli.h"
//#include "E_Coli.h"

ParameterEstimation_E_coli::ParameterEstimation_E_coli():E_coli(){    
    
//    cout << "Normal Costructor ... " << endl;
    Tipo_batterio = "E_coli-rExp-tExp-P";
    codice_batterio = EcoliType::PAR_E_COLI;
    simulation = 1;
//    cout << Tipo_batterio << endl;
//    cout << "modello: x[0]=" << x[0] << endl;
//    cout << "         x[0]+1.0 = " << x[0]+1.0 << endl;
};


ParameterEstimation_E_coli::ParameterEstimation_E_coli(const E_coli& m):E_coli(m){
    
//    cout << "Copy-costructor ..." << endl;
    Tipo_batterio = "E_coli-rExp-tExp-P";
    codice_batterio=m.codice_batterio;
//    cout << Tipo_batterio << endl;
//    cout << "copia: x[0] = " << x[0] << endl;
//    x[0]+=1.0;
//    cout << "       x[0] = x[0]+1.0 = " << x[0] << endl;
    simulation = 1;
    
}