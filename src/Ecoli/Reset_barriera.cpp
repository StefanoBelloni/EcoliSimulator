//
//  Reset_barriera.cpp
//  Ecoli_4.1.2
//
//  Created by Stefano Belloni on 18/08/15.
/*This program is free software - GNU General Public License Verison 2*/
//

#include <iostream>
#include "E_Coli.h"
#include "Molecular_rIG_tExp.h"
#include "CV_rExpIG_tExp.h"
#include "CV_rIG_tExp.h"
#include "EO_rExp_tExp.h"
#include "EO_rIG_tExp.h"
#include "EO_rExpIG_tExp.h"
#include "Molecular_rExpIG_tExp.h"

//*****************************************
//  Reset_barriera-> TUMBLE
//*****************************************

double E_coli::reset_barrier_t(){    
    return Exp_dist_ec();
}

//*****************************************
//  Reset_barriera-> RUN
//*****************************************

double E_coli::reset_barrier(){    
    return Exp_dist_ec();
}

double CV_rIG_tExp::reset_barrier(){
    return 1.0;    
}
double CV_rExpIG_tExp::reset_barrier(){
    return Exp_dist_ec();
}

double Molecular_rIG_tExp::reset_barrier(){
    return 1.0;
}
double Molecular_rExpIG_tExp::reset_barrier(){
    return Exp_dist_ec();
}

double EO_rIG_tExp::reset_barrier(){
    return 1.0;    
}
double EO_rExpIG_tExp::reset_barrier(){
    return Exp_dist_ec();
}


//double EO_rExp_tExp::reset_barrier(){
//    return Exp_dist();
//}

