//
//  StatisticalAnalysis.h
//  Ecoli_4.1.1
//
//  Created by Stefano Belloni on 06/08/15.
/*This program is free software - GNU General Public License Verison 2*/
//

#include "Q_tau_stat.h"
#include "s_lambda.h"
#include "E_Coli.h"
#include "Funz_C.h"

int set_parameter_Q_tau(double &dq, double &q_max, double &q_min, vector<Q_tau_stat> &Q_tau_vect, int &q_0);
int reset_parameter_Q_tau(double &dq, double &q_max, double &q_min, vector<Q_tau_stat> &Q_tau_vect, int n_iterate, int n_stat_tumb, int &q_0);
int constract_Q_tau_vect(double dq, double q_max, double q_min, vector<Q_tau_stat> &Q_tau_vect, string name_file_dati, int &n_stat, int n_q, double &tau_0_t_stima,double &q_max_s, double &q_min_s);
int simulation_independent_setting(E_coli *batterio,double T_f,Funz_C *f,double *x0,double dt,int n_c,double Raggio,int delta_dist, int num_dist,int const_salv,string *names_Ecoli_mod, string names_indice_mod, string *names_tau_mod, string names_file_dyn_mod, string *names_info_mod, int i, int &cont_gen_sim, int stat_);
void inizializzazione_parametri(int sel_prog, double &T_f, int &n_c, double* x0, int &num_dist,double &Raggio, int &delta_dist, int &const_salv, double &dt, string name_file,vector<Funz_C*> &f, int &tipo_funz_c_class, int &tipo_response_c, double &RC_0, double &RC_1, int &RC_q);
int plot_tau_Q(std::string title_, std::vector<Q_tau_stat> &vet_stat, int save_, int n_iterate);
int GoodnessFit_PP(string name_file_dati, s_lambda lambda, int n_data, int n_iterate,double &D_n, double &cumD_n);
void create_lambda(s_lambda &s_lambda_r, vector<Q_tau_stat> &vector_lambda, int n_vect, int tipo_sim);
int MovingLeastSquares(int set_epsilon, s_lambda &lambda);
//not moving!!! ------------------------------------------!!!!!!!!!!!!!!
int MovingLeastSquares(int set_epsilon, s_lambda &lambda, int not_moving);
// weight according to occurence !!
int MovingLeastSquares(s_lambda &lambda);
int plot_lambda(std::string title_, s_lambda &lambda, int save_, int n_iterate);

void updateTest(GoodFit &Test, double cumD_n, double D_n, double q_max, double q_min, double dq);
void timestamp();
int DynFitting(string &name_file_dati, double &tau_0_t_stima, s_lambda &lambda, int which_compare, double &D_n, double &cumD_n);
int ManualFitting(string &name_file_dati, double &tau_0_t_stima, s_lambda &lambda, int which_compare, double &D_n, double &cumD_n);