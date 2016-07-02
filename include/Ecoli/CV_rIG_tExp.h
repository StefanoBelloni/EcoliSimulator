//
//  CV_rIG_tExp.h
//  E_Coli2.1
//
//  Created by Stefano Belloni on 22/05/15.
/*This program is free software - GNU General Public License Verison 2*/
//

#ifndef E_Coli2_1_CV_rIG_tExp_h
#define E_Coli2_1_CV_rIG_tExp_h

#include "CV_rExp_tExp.h"

#include "constants.h" //#define pi 3.141592653589793238462


/** \brief Celani Vergassola Kernel Model Class for a bacterium IG run Distribution
 * CLASS implementig the model Celani Vergassola using a IG distribution for the run distribution
 * and exponential for the tumble distribution.
 * It reimplements the dysplay of internal dinamics and the internal dynamic itself
 *
 */

class CV_rIG_tExp : public CV_rExp_tExp {
    
public:
    
    CV_rIG_tExp();
    CV_rIG_tExp(const CV_rIG_tExp& modello);
    
    void change_par(int change);
    void change_sigma_par();
    /** variance for the underlying diffussion rate to tumble */
    virtual double f_sigma();

    void print_info(std::ofstream &file_save);
//    void gnuplotFunzInternalDynalmic(std::string title, int save_, int gen_con_sim);
    int saveIntDyn(std::string nameFile);
    void reset_par();
    /** reset threshold deterministical to level 1*/
    double reset_barrier();
    int agg_dyn(double dt, double t);
    
    void debugFunction();
    
protected:
    
    // 
    int tipo_sigma;
    double B_0;
    double B_1;
    double B_2;
    

//    void save_dyn(std::ofstream &file_, double t);
    

};


#endif
