//
//  Declar_funz.h
//  E_Coli2.0
//
//  Created by Stefano Belloni on 20/05/15.
/*This program is free software - GNU General Public License Verison 2*/
//
//****************************************************************************************

#include "E_Coli.h"
#include "ParameterEstimation_E_Coli.h"
#include "mainFunctions.h"

#ifndef DefFunz_h
#define DefFunz_h

void timestamp ( );
void initial_page();

bool Verifica_gnuplot();
void initial_page();
void Scrittura_m_files();

int signum_f(long double x);

//************
void inizializzazione_parametri(int sel_prog, long double &T_f, int &n_c, long double* x0, int &num_dist,long double &Raggio, int &delta_dist, int &const_salv, long double &dt);
void inizializzazione_parametri(int sel_prog, long double &T_f, int &n_c, long double* x0, int &num_dist,long double &Raggio, int &delta_dist, int &const_salv, long double &dt, std::string name_file,std::vector<Funz_C*> &f, int &tipo_funz_c_class, int &tipo_response_c, long double &RC_0, long double &RC_1, int &RC_q);
//************

void setNames(std::string *names_files_Ecoli_mod, std::string &names_indice_mod, std::string *names_files_tau_mod, std::string &names_file_dyn_mod, std::string *names_info_mod, int tipo_simulazione, int sel_prog, int cont_gen_sim, int stat_);

int simulation_independent_setting(E_coli *batterio,long double T_f,Funz_C *f,long double *x0,long double dt,int n_c,long double Raggio,int delta_dist, int num_dist,int const_salv,std::string *names_Ecoli_mod, std::string names_indice_mod, std::string *names_tau_mod, std::string names_file_dyn_mod, std::string *names_info_mod, int n_sim, int &cont_gen_sim);

int simulation_2(E_coli *batterio, long double T_f,Funz_C *f,long double *x_0,long double dt,int n_c,long double Raggio,int delta_dist, int num_dist,int const_salv, string *names_files_Ecoli_mod, string names_indice_mod, string *names_files_tau_mod, string names_file_dyn_mod, string *names_info_mod, int n_sim, int cont_gen_sim, int tot_bacteria, int n_thread);

int simulation_interacting(std::vector<E_coli*> batterio, long double T_f,Funz_C *f,long double *x0,long double dt,int n_c,long double Raggio,int delta_dist, int num_dist,int const_salv, std::string *names_files_Ecoli_mod, std::string names_indice_mod, std::string *names_files_tau_mod, std::string names_file_dyn_mod, std::string *names_info_mod, int cont_gen_sim, long double &f_max);

void Name_jumps(std::string name_file_read, std::string names[], int delete_);
long double Analysis_run(std::string name_file_read, std::string names[], int run);
void gnuplot_run(std::string names[], std::string nome_info, long double mean, int tipo_run, int save_, int cont_sim);

void gnuplot_large_population(std::string file_info[], std::string name_dyn ,long double T_f, int n_c, int dim_col_t, std::string names, Funz_C *f, int cont_gen_sim);
void gnuplot_large_population_interacting(std::string file_info[], std::string name_dyn, long double T_f, int n_c, int dim_col_t, std::string names, Funz_C *f, int cont_gen_sim, long double maxC);
int Matlab_from_cpp(int sel_prog, std::string versione_Matlab);

void Cancella_tutto(std::string *names_Ecoli_mod, std::string names_indice_mod, std::string *names_tau_mod, std::string names_file_dyn_mod, std::string *names_info_mo, int i, int n_gen_sim);

void gnuplot_run_multiplot(std::string nome_info, std::string names[], int save_, int cont_glob_sim, int tipo_grafico);

void Histogram_2D(std::string name_info[], std::string name_files_tau_mod[], int save_, int cont_glob_sim);

//*****************
int independent_population(Funz_C* f, int n_compare, std::string *names_Ecoli_mod, std::string &names_indice_mod, std::string *names_tau_mod, std::string &names_file_dyn_mod, std::string *names_info_mod, int sel_prog, std::vector<int> &which_compare, std::vector<E_coli* > &batteri, long double T_f, long double *x0, long double dt,int n_c, long double Raggio,int delta_dist, int num_dist,int const_salv, std::string &versione_Matlab, std::string names_jumps[], int &cont_gen_sim, int stat_ = 1, std::vector<std::string> *pt_name_file_satistics = 0, std::vector<std::string> *pt_name_info_satistics = 0);

//*****************


int interaction_population(Funz_C* f, int n_compare, std::string *names_Ecoli_mod, std::string &names_indice_mod, std::string *names_tau_mod, std::string &names_file_dyn_mod, std::string *names_info_mod, int tipo_simulazione, int sel_prog, std::vector<E_coli* > &batteri_int, long double T_f, long double *x0,long double dt,int n_c,long double Raggio,int delta_dist, int num_dist,int const_salv, std::string &versione_Matlab, std::string names_jumps[], int &cont_gen_sim, int &which_compare);


void initialization_interacting_population(int tipo_simulazione, std::vector<E_coli* > *batteri_int, int n_c, int cont_gen_sim);
void clean_interacting_population(int tipo_simulazione, vector<E_coli* > *batteri_int, int n_c, int cont_gen_sim);
//*****************
void FunzRunUndTumble(long double T_f, int n_c, int cont_gen_sim, int n_compare, std::string *names_Ecoli_mod, std::string names_indice_mod, std::string *names_tau_mod, std::string names_file_dyn_mod, std::string *names_info_mod, std::string *names_jumps, int sel_prog, std::vector<E_coli*> batteri, std::vector<int> &which_compare, int stat_);
void FunzRunUndTumble(long double T_f, int n_c, int cont_gen_sim, int n_compare, std::string *names_Ecoli_mod, std::string names_indice_mod, std::string *names_tau_mod, std::string names_file_dyn_mod, std::string *names_info_mod, std::string *names_jumps, int sel_prog, std::vector<E_coli*> batteri, int which_compare, int stat_);
//*****************

void sssr(int &valore, std::string text);
void sssr(long double &valore, std::string text);
void set_parameters_DEMO();
    
void Write_LateX_file(std::string name_file, std::ofstream &file_teX);
void LateX_Preambolo(std::ofstream &file_teX);
int LateX_Corpo(ofstream &file_teX, const char final[]);

void funz_clear();
void funz_clearAll();
void set_gnuplot_Matlab_apngas(std::string &versione_Matlab);
int set_MODE_Program(std::string &versione_Matlab, int &demo_mode, int readfromfile);
int menu_simulation();
int set_funz_c(std::vector<Funz_C*> &f, int interacting);

void last_deleting();

int signum_f(long double x);

//************************************************************
// STATTISTICAL FUNCTIONS
//************************************************************


int Statistical_Analysis(std::string name_file_dati, std::string name_info_dati, std::vector<int> which_compare, int n_compare, int &cont_gen_sim, std::string &versione_Matlab, int n_c);
//***************
int MODE_simulation(std::string &versione_Matlab, int &cont_gen_sim, std::vector<std::string> *pt_name_file_satistics = 0 , std::vector<std::string> *pt_name_info_satistics = 0);

int MODE_statisticalAnalysis(std::string &versione_Matlab, int &cont_gen_sim, std::vector<std::string> *pt_name_file_satistics, std::vector<std::string> *pt_name_info_satistics, int n_c);

void File_statistics(E_coli *batterio,long double T_f,Funz_C *f,long double *x0,long double dt,int n_c,long double Raggio,int delta_dist, int num_dist,int const_salv,std::string *names_Ecoli_mod, std::string names_indice_mod, std::string *names_tau_mod, std::string names_file_dyn_mod, std::string *names_info_mod, int i, int &cont_gen_sim,std::vector<std::string> *pt_name_file_satistics, std::vector<std::string> *pt_name_info_satistics);

int save_path(std::string versione_MATLAB);
int import_path(std::string versione_MATLAB);
int save_risposte();

void pritn_path(std::string versione_MATLAB);


int read_file_par(int demo_mode);


int SetMainFolder(int demo_mode);
int SetFolder_LateX(int demo_mode, int number_routine);
int SetFolderData(int demo_mode, int number_routine);
void CopyEcoliFiles();

int FunzBiginEnd(int &number_routine, int &cont_gen_sim, int &read_par_file, std::string &versione_Matlab,std::vector<std::string> *pt_name_file_satistics, std::vector<std::string> *pt_name_info_satistics, int &demo_mode, int &stat_sim);

int ConditionEnd(int &read_par_file, int &stat_sim, int &BiginEnd);
void GestioneArgv(int argc, const char * argv[], std::string &versione_Matlab, int &readfromFile);
void ErrorImportPath(std::string &versione_Matlab);
int Congedo(int number_routine);
void ReadableFileRisp(int &stat_sim, int demo_mode);
void helpMenu();

template<typename T>
void getInput(T &risposta);

#endif
