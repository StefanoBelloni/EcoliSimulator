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
    
//    double D_theta;
    double t_e;
    double t_a;
    
    //Parametri funzione lambda
    int tipo_lambda;
    double A_0;
    double A_1; 
    double A_2; 
    double A_3;
    
//    double y_2;
    vector<double> m;
    
    int writeScriptgnuplotSingle(std::string tipo, std::string *names_files_Ecoli_mod, std::string *names_files_tau_mod, std::string *names_info_mod, std::string &names_file_dyn_mod, double T_f, int con_gen_sim, int save_);
    
public:
    
    EO_rExp_tExp();
    EO_rExp_tExp(const EO_rExp_tExp& modello);
    
    void change_par(int change);
    void change_lambda_par();
    virtual double f_lambda();
    void stationary_dyn(double dt, std::vector<double> &m0, int changed_pos);
    
    int agg_dyn(double dt, double t);
    void agg_dyint(double dt, double t);
    
    void save_dyn(std::ofstream &file_, double t);
    
    void gnuplot_single(std::string *names_files_Ecoli_mod, std::string &names_indice_mod, std::string *names_files_tau_mod, std::string &names_file_dyn_mod, std::string *names_info_mod, double T_f, Funz_C *f, int save_, int con_gen_sim);
//    void gnuplotFunzInternalDynalmic(std::string buffer, int save_, int cont_gen_sim);
    int saveIntDyn(std::string nameFile);
    
    void reset_par();
    
    void print_info(std::ofstream &file_save);
    
};

#endif
