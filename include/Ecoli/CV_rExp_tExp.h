//
//  CV_rExp_tExp.h
//  E_Coli2.0
//
//  Created by Stefano Belloni on 20/05/15.
/*This program is free software - GNU General Public License Verison 2*/
//

#ifndef E_Coli2_0_CV_rExp_tExp_h
#define E_Coli2_0_CV_rExp_tExp_h

#include <iostream>
#include "FunzRand.h"
#include "Funz_C.h"
#include "E_Coli.h"
#include "ParameterEstimation_E_Coli.h"

/** \brief Celani Vergassola Kernel Model Class for a bacterium:
 *
 *
 * Class implementing Celani Vergassola Kernel Model with exponential run and exponential tumble in the steady state
 */

class CV_rExp_tExp : public ParameterEstimation_E_coli {
    
protected:
    
//    double D_theta;
    /** parameter in the Celani Vergassola Model: 
     - m[2]=m[2]+dt*(2*m[1]-nu_*m[2]);
     - m[1]=m[1]+dt*(m[0]-nu_*m[1]);
     - m[0]=m[0]+dt*(c-nu_*m[0]);
     - Q=pow(nu_,2)*beta_2*m[1]+pow(nu_,3)*beta_3*m[2];
     
     \f{equation}{
     \frac{d}{dt}m_{k}=-\nu\cdot m_{k} + \delta^{k}_{0} c + (1-\delta^{k}_{0})k\cdot m_{k-1},
     \f}
     \f{equation}{
     \mathcal{Q}(t)=\sum_{k=1}^{k_{N}}\beta_{k}\nu^{k+1}m_{k}(t)
     \f}
     
     */
    double nu_;
    /** parameter in the Celani Vergassola Model:
     - m[2]=m[2]+dt*(2*m[1]-nu_*m[2]);
     - m[1]=m[1]+dt*(m[0]-nu_*m[1]);
     - m[0]=m[0]+dt*(c-nu_*m[0]);
     - Q=pow(nu_,2)*beta_2*m[1]+pow(nu_,3)*beta_3*m[2];
     
     \f{equation}{
     \frac{d}{dt}m_{k}=-\nu\cdot m_{k} + \delta^{k}_{0} c + (1-\delta^{k}_{0})k\cdot m_{k-1},
     \f}
     \f{equation}{
     \mathcal{Q}(t)=\sum_{k=1}^{k_{N}}\beta_{k}\nu^{k+1}m_{k}(t)
     \f}
     
     */
    double beta_2;
    /** parameter in the Celani Vergassola Model:
     - m[2]=m[2]+dt*(2*m[1]-nu_*m[2]);
     - m[1]=m[1]+dt*(m[0]-nu_*m[1]);
     - m[0]=m[0]+dt*(c-nu_*m[0]);
     - Q=pow(nu_,2)*beta_2*m[1]+pow(nu_,3)*beta_3*m[2];     
     
     \f{equation}{
     \frac{d}{dt}m_{k}=-\nu\cdot m_{k} + \delta^{k}_{0} c + (1-\delta^{k}_{0})k\cdot m_{k-1},
     \f}
     \f{equation}{
     \mathcal{Q}(t)=\sum_{k=1}^{k_{N}}\beta_{k}\nu^{k+1}m_{k}(t)
     \f}
     
     */
    double beta_3;
    
    //Parametri funzione lambda
    /** type of function: if you want to add new function change the function f_lambda() accordingly*/
    int tipo_lambda;
    /** One of the parameter for the function lambda:
      - in tipo_lambda=2;
         -A_0;   // estremo destro
     */
    double A_0;
    /** One of the parameter for the function lambda:
       - tipo_lambda=2;
        - A_1   // estremo sinistro (<0)
     */
    double A_1;
    /** One of the parameter for the function lambda:
     - tipo_lambda=2;
        - A_2    // moltiplicatore "Q>a1"
     */
    double A_2;
    /** One of the parameter for the function lambda:
     - tipo_lambda=2;
        - A_3  // moltiplicatore "Q<-a0"
     */
    double A_3;
    
    /** Memory term in celani vergassola
     Q=pow(nu_,2)*beta_2*m[1]+pow(nu_,3)*beta_3*m[2];
     \f{equation}{
       \mathcal{Q}(t)=\sum_{k=1}^{k_{N}}\beta_{k}\nu^{k+1}m_{k}(t)
     \f}
     */
    double Q;
    /** vector of the internal dynamic variables: they satisfy
     \f{equation}{
     \frac{d}{dt}m_{k}=-\nu\cdot m_{k} + f_{k},
     \f}
     featuring a relaxation term and a forcing term \f$f_{k} = k\cdot m_{k-1}\f$ for \f$k\geq1\f$ and \f$f_{0}= c\f$ for \f$k=0\f$.

     */
    vector<double> m;
    
    int writeScriptgnuplotSingle(std::string tipo, std::string *names_files_Ecoli_mod, std::string *names_files_tau_mod, std::string *names_info_mod, std::string &names_file_dyn_mod, double T_f, int con_gen_sim, int save_);
//    int writeScriptLunchgnuplotSingle(std::string tipo, int save_, int con_gen_sim);
    
public:
    
    CV_rExp_tExp();
    CV_rExp_tExp(const CV_rExp_tExp& modello);
    
    void change_par(int change);
    void change_lambda_par();
    /** probability mean rate to tumble <br>
      It uses the parameter Q
     @return return the value \f$\lambda(Q)\f$
     */
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
    
    void debugFunction();
    
};

#endif
