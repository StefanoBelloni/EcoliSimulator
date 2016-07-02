//
//  Molecular_rExpIG_tExp.h
//  Ecoli_4.1.2
//
//  Created by Stefano Belloni on 18/08/15.
/*This program is free software - GNU General Public License Verison 2*/
//

#ifndef Ecoli_4_1_2_Molecular_rExpIG_tExp_h
#define Ecoli_4_1_2_Molecular_rExpIG_tExp_h

#include "Molecular_rExpIG_tExp.h"
#include "Molecular_rIG_tExp.h"

#include "constants.h" //#define pi 3.141592653589793238462

/**\brief Celani Shimitzu Vergassola Molecular  Model Class for a bacterium Exp-IG distribution
 */

class Molecular_rExpIG_tExp : public Molecular_rIG_tExp {
    
public:
    
    Molecular_rExpIG_tExp();
    Molecular_rExpIG_tExp(const Molecular_rExpIG_tExp& modello);
    
    //    void print_info(std::ofstream &file_save);
    void reset_par();
    double reset_barrier();
    
};

#endif
