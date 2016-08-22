//
//  Molecular_rExp_tExp.h
//  E_Coli2.2
//
//  Created by Stefano Belloni on 01/06/15.
/*This program is free software - GNU General Public License Verison 2*/
//

#ifndef E_Coli2_2_Molecular_rExp_tExp_h
#define E_Coli2_2_Molecular_rExp_tExp_h

#include "E_Coli.h"
#include "ParameterEstimation_E_Coli.h"

/**  \brief Celani Shimitzu Vergassola Molecular  Model Class for a bacterium
 
 Class implementing Celani Shimitzu Vergassola Molecular model
 
 This model is taken from <b>CSV11</b> [A. Celani, T.S. Shimizu and M. Vergassola, Molecular and functional aspects of bacterial chemotaxis, J. Stat. Phys. 144, 219-240 (2011).], and implement the <tt>mean field</tt> approximation for the molecular-base model of the internal dynamic of the bacterium. The generalization to the Inverse gaussian and exponential-inverse gaussian is straightforward.
 
 The chemotactic transduction pathway is conveniently modeled by the following set of mean-field equations:
 \f{align}{
 a&=G(m,L),\\
 \frac{d}{dt}m&=F(a,m),\\
 \frac{d}{dt}y&=k_a a(1-y)-k_zy,\\
 \frac{d}{dt}p_r&=\frac{1-\frac{p_r}{h(y)}}{\tau_t}.
 \f}
 
 The detailed expressions for the functions that appear above are
 \f{align*}{
 G(m,L)&=\frac{1}{1+e^{f(m,L)}},\\
 f(m,L)&=n_a\alpha_m(m_0-m)+n_a\ln\frac{1+\frac{L}{K_{off}}}{1+\frac{L}{K_{on}}},\\
 F(a,m)&=k_r[\textrm{CheR}](1-a)\frac{M-a}{M-m+K_R}-k_b[\textrm{CheB}]a\frac{m}{m+K_B};\\
 h(y)&=\frac{1}{1+\Big(\frac{y}{y_0}\Big)^H}.
 \f}
 
 
 */

class Molecular_rExp_tExp : public ParameterEstimation_E_coli
{
    
protected:

    // CSV11 VARIABILI
    /** see model in detailed description*/
    long double a_m;
    /** see model in detailed description*/
    long double m_0;
    /** see model in detailed description*/
    long double K_off;
    /** see model in detailed description*/
    long double K_on;
    /** see model in detailed description*/
    long double n_a;
    /** see model in detailed description*/
    long double M_max;
    /** see model in detailed description*/
    long double A_max;
    /** see model in detailed description*/
    long double L_max;
    /** see model in detailed description*/
    long double y_max;
    /** see model in detailed description*/
    long double K_R;
    /** see model in detailed description*/
    long double K_B;
    /** see model in detailed description*/
    long double kCheR;
    /** see model in detailed description*/
    long double kCheB;
    //    long double y_0;
    //    long double y_0;
    /** see model in detailed description*/
    long double y_0;
    /** see model in detailed description*/
    long double k_a;
    /** see model in detailed description*/
    long double k_z;
    /** see model in detailed description*/
    long double H;
    //*************************
    
    /** Internal variable methalination level: see model in detailed description*/
    long double meth;
    /** Internal variable: see model in detailed description*/
    long double a;
    /** Internal variable: see model in detailed description*/
    long double y;
    /** Internal variable: see model in detailed description*/
    long double p_r;
    /** factor to adjust initial value for probability rate, it's make stable the process, it's like play with y_0 */
    long double factor_prob;
    
    int writeScriptgnuplotSingle(string tipo, string *names_files_Ecoli_mod, string *names_files_tau_mod, string *names_info_mod, string &names_file_dyn_mod, long double T_f, int con_gen_sim, int save_);
    
public:
    
    Molecular_rExp_tExp();
    Molecular_rExp_tExp(const Molecular_rExp_tExp& modello);
    void stationary_dyn(long double dt, std::vector<long double> &m0, int changed_pos);
    void change_par(int change);
    void change_molecular();
    friend long double F_CSV(Molecular_rExp_tExp *batterio, long double m_s, long double L_use);
    int agg_dyn(long double dt, long double t);
    void agg_dyint(long double dt, long double t);
    void save_dyn(std::ofstream &file_, long double t);
    void gnuplot_single(string *names_files_Ecoli_mod, string &names_indice_mod, string *names_files_tau_mod, string &names_file_dyn_mod, string *names_info_mod, long double T_f, Funz_C *f, int save_, int con_gen_sim);
    void print_info(std::ofstream &file_save);
    void reset_par();
    
};


#endif
