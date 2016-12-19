//
//  Molecular_rExpIG_tExp.cpp
//  Ecoli_4.1.2
//
//  Created by Stefano Belloni on 18/08/15.
/*This program is free software - GNU General Public License Verison 2*/
//

#include <iostream>
#include "Molecular_rIG_tExp.h"
#include "Molecular_rExpIG_tExp.h"

Molecular_rExpIG_tExp::Molecular_rExpIG_tExp():Molecular_rIG_tExp(){
    Tipo_batterio = "Molecular-rExpIG-tExp";
    codice_batterio = EcoliType::MOLECULAR_RIGEXP_TEXP;
    //    barriera_r=Exp_dist(); // E' gia' implementata come exp distribution ...
    B_0=1.6;
}

Molecular_rExpIG_tExp::Molecular_rExpIG_tExp(const Molecular_rExpIG_tExp& modello)
                        :Molecular_rIG_tExp()
{
    
    Tipo_batterio = modello.Tipo_batterio;
    codice_batterio=modello.codice_batterio;
    barriera_r=reset_barrier();
    B_0=modello.B_0;
    B_1=modello.B_1;
    B_2=modello.B_2;
}



void Molecular_rExpIG_tExp::reset_par(){
    
    Molecular_rIG_tExp::reset_par();
    
    Tipo_batterio = "Molecular-rExpIG-tExp";
    //    barriera_r=Exp_dist(); // E' gia' implementata come exp distribution ...
    B_0=1.6;
    
}
