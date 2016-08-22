//
//  Q_tau_stat.cpp
//  Ecoli_4.1.0
//
//  Created by Stefano Belloni on 20/07/15.
/*This program is free software - GNU General Public License Verison 2*/
//

#include <iostream>
#include "Q_tau_stat.h"

Q_tau_stat::Q_tau_stat(long double Q_ext){
    
    Q = Q_ext;
    
//    std::cout << "**************\n";
//    std::cout << "Q = " << Q << std::endl; 
    
    mean=0.0;
    var=0.0;
    invX=0.0;
    n_rec=0;
    max_tau=0.0;
//    tau_measured
    
    
}

void Q_tau_stat::reset(long double Q_ext){
    
    Q = Q_ext;
    
    //    std::cout << "**************\n";
    //    std::cout << "Q = " << Q << std::endl; 
    
    mean=0.0;
    var=0.0;
    invX=0.0;
    n_rec=0;
    max_tau=0.0;
    //    tau_measured
    
    
}

long double Q_tau_stat::V_IG(){
    
    return (n_rec-3)/(invX-1/mean);
    
    
}
