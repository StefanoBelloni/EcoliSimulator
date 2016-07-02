//
//  EO_rExpIG_t_Exp.h
//  Ecoli_4.1.2
//
//  Created by Stefano Belloni on 18/08/15.
/*This program is free software - GNU General Public License Verison 2*/
//

#ifndef Ecoli_4_1_2_EO_rExpIG_tExp_h
#define Ecoli_4_1_2_EO_rExpIG_tExp_h

#include "EO_rIG_tExp.h"

#include "constants.h" //#define pi 3.141592653589793238462

/**  \brief Erban-Othmer Model Model Class for a bacterium Exp-IG distribution
 Class implementing Erban-Othmer Model with exponential-IG compound run and exponential tumble in the steady state, using a cartoon for the internal dynamics */

class EO_rExpIG_tExp : public EO_rIG_tExp {
    
public:
    
    EO_rExpIG_tExp();
    EO_rExpIG_tExp(const EO_rExpIG_tExp& modello);
    
    void print_info(std::ofstream &file_save);
    void reset_par();
    double reset_barrier();
    
};

#endif
