//
//  CV_rExpIG_tExp.h
//  E_Coli2.2
//
//  Created by Stefano Belloni on 01/06/15.
/*This program is free software - GNU General Public License Verison 2*/
//

#ifndef E_Coli2_2_CV_rExpIG_tExp_h
#define E_Coli2_2_CV_rExpIG_tExp_h

#include "CV_rIG_tExp.h"

#include "constants.h" //#define pi 3.141592653589793238462

/** \brief Celani Vergassola Kernel Model Class for a bacterium ExpIG run dustribution
 * CLASS implementig the model Celani Vergassola using a Exponential-IG-compound distribution for the run distribution
 * and exponential for the tumble distribution.
 * It reimplements the dysplay of internal dinamics and the internal dynamic itself
 *
 */

class CV_rExpIG_tExp : public CV_rIG_tExp {
    
public:
    
    CV_rExpIG_tExp();
    CV_rExpIG_tExp(const CV_rExpIG_tExp& modello);
    
    void print_info(std::ofstream &file_save);
    void reset_par();
    double reset_barrier();

};

#endif
