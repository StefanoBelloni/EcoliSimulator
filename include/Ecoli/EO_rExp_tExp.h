//
//  EO_rExp_tExp.h
//  Ecoli_4.1.1
//
//  Created by Stefano Belloni on 18/08/15.
/*This program is free software - GNU General Public License Verison 2*/
//

#ifndef Ecoli_4_1_1_EO_rExp_tExp_h
#define Ecoli_4_1_1_EO_rExp_tExp_h

#include <iostream>
#include <vector>

#include "FunzRand.h"
#include "Funz_C.h"
#include "E_Coli.h"
#include "ParameterEstimation_E_Coli.h"


/**  \brief Erban-Othmer Model Model Class for a bacterium:
 Class implementing Erban-Othmer Model with exponential run and exponential tumble in the steady state, using a cartoon for the internal dynamics
 
 \f{equation}{
 \begin{aligned}
 \frac{d}{dt}y_{1}(t)&=\frac{G(c(t,x))-(y_{1}+y_{2})}{\tau_{a}}\\
 \frac{d}{dt}y_{2}(t)&=\frac{G(c(t,x))-y_{2}}{\tau_{e}}
 \end{aligned}
 \f}
 
 */

class EO_rExp_tExp : public ParameterEstimation_E_coli {
    
protected:
    
//    long double D_theta;
    long double t_e;
    long double t_a;
    
    //Parametri funzione lambda
    int tipo_lambda;
    long double A_0;
    long double A_1; 
    long double A_2; 
    long double A_3;
    
//    long double y_2;
    vector<long double> m;
    
    int writeScriptgnuplotSingle(std::string tipo, std::string *names_files_Ecoli_mod, std::string *names_files_tau_mod, std::string *names_info_mod, std::string &names_file_dyn_mod, long double T_f, int con_gen_sim, int save_);
    
public:
    
    EO_rExp_tExp();
    EO_rExp_tExp(const EO_rExp_tExp& modello);
    
    void change_par(int change);
    void change_lambda_par();
    virtual long double f_lambda();
    void stationary_dyn(long double dt, std::vector<long double> &m0, int changed_pos);
    
    int agg_dyn(long double dt, long double t);
    void agg_dyint(long double dt, long double t);
    
    void save_dyn(TmpFile &file_, long double t);
    
    void gnuplot_single(std::string *names_files_Ecoli_mod, std::string &names_indice_mod, std::string *names_files_tau_mod, std::string &names_file_dyn_mod, std::string *names_info_mod, long double T_f, Funz_C *f, int save_, int con_gen_sim);
//    void gnuplotFunzInternalDynalmic(std::string buffer, int save_, int cont_gen_sim);
    int saveIntDyn(std::string nameFile);
    
    void reset_par();
    
    void print_info(std::ofstream &file_save);
    
};

#endif
