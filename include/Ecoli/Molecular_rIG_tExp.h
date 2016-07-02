//
//  Molecular_rIG_tExp.h
//  Ecoli_3.1.4
//
//  Created by Stefano Belloni on 14/07/15.
/*This program is free software - GNU General Public License Verison 2*/
//

#ifndef Ecoli_3_1_4_Molecular_rIG_tExp_h
#define Ecoli_3_1_4_Molecular_rIG_tExp_h

#include "Molecular_rExp_tExp.h"

/**\brief Celani Shimitzu Vergassola Molecular  Model Class for a bacterium IG distribution
*/
class Molecular_rIG_tExp : public Molecular_rExp_tExp{
    
public:
    
    Molecular_rIG_tExp();
    Molecular_rIG_tExp(const Molecular_rIG_tExp& modello);
    
    int agg_dyn(double dt, double t);
    
    void reset_par();
    
    
    void change_par(int change);
    void change_sigma_par();
    double f_sigma();

    int tipo_sigma;
    double B_0;
    double B_1;
    double B_2;
    
    double reset_barrier();
//    void print_info(std::ofstream &file_save);
//    void gnuplotFunzInternalDynalmic(string title, int save_, int gen_con_sim);
//    int saveIntDyn(string nameFile);
    
};

#endif
