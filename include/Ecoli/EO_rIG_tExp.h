//
//  EO_rIG_tExp.h
//  Ecoli_4.1.2
//
//  Created by Stefano Belloni on 18/08/15.
/*This program is free software - GNU General Public License Verison 2*/
//

#ifndef Ecoli_4_1_2_EO_rIG_tExp_h
#define Ecoli_4_1_2_EO_rIG_tExp_h

#include "constants.h" //#define pi 3.141592653589793238462

#include "EO_rExp_tExp.h"


/** \brief Erban-Othmer Model Model Class for a bacterium IG distribution
 Class implementing Erban-Othmer Model with IG run and exponential tumble in the steady state, using a cartoon for the internal dynamics */

class EO_rIG_tExp : public EO_rExp_tExp {
    
public:
    
    EO_rIG_tExp();
    EO_rIG_tExp(const EO_rIG_tExp& modello);
    
    
    void change_par(int change);
    void change_sigma_par();
    virtual long double f_sigma();
    
    // 
    int tipo_sigma;
    long double B_0;
    long double B_1;
    long double B_2;
    
    int agg_dyn(long double dt, long double t);
    
    void print_info(std::ofstream &file_save);
//    void gnuplotFunzInternalDynalmic(std::string title, int save_, int gen_con_sim);
    int saveIntDyn(std::string nameFile);
    void reset_par();
    long double reset_barrier();
};



#endif
