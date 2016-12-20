//
//  simulation_2MultiT.hpp
//  Ecoli_4.1.5
//
//  Created by Stefano Belloni on 24/05/16.
//  Copyright © 2016 Stefano Belloni. All rights reserved.
//

#ifndef simulation_2MultiT_hpp
#define simulation_2MultiT_hpp

#include <stdio.h>
#include <string>

#include "Funz_C.h"
#include "E_Coli.h"
#include "LoadBar.hpp"

int Stima_tempo(int n_c, int n_val_termine, int &j_cel_finale, int &j_cel_inizio, time_t timer1);
int initial_position(int j,long double *x, long double *x0, long double Raggio, int num_dist, int &cont_dist_5, int delta_dist_cont, long double Delta_delta_dist);
void timestamp ( );
//void loadbar(unsigned int x, unsigned int n, int time_, unsigned int w);

void funz_clear();

#ifndef NO_M_THREAD

void startThreadSimulation(E_coli *batterio, long double T_f,Funz_C *f,array<long double,2> x0,long double dt,int n_c,long double Raggio,int delta_dist, int num_dist,int const_salv, string *names_files_Ecoli_mod, string names_indice_mod, string *names_files_tau_mod, string names_file_dyn_mod, string *names_info_mod, int n_sim, int cont_gen_sim, int n_thread, int& dim_colonne);

int simulation_2MultiT(E_coli *batterio, long double T_f,Funz_C *f,long double *x0,long double dt,int n_c,long double Raggio,int delta_dist, int num_dist,int const_salv, string *names_files_Ecoli_mod, string names_indice_mod, string *names_files_tau_mod, string names_file_dyn_mod, string *names_info_mod, int n_sim, int cont_gen_sim, int n_thread);

#endif

int simulation_2(E_coli *batterio, long double T_f,Funz_C *f,long double *x0,long double dt,int n_c,long double Raggio,int delta_dist, int num_dist,int const_salv, std::string *names_files_Ecoli_mod, std::string names_indice_mod, std::string *names_files_tau_mod, std::string names_file_dyn_mod, std::string *names_info_mod, int n_sim, int cont_gen_sim, int tot_bacteria, int n_thread = 1);

std::string setNametempFiles(string name, int n_thread);

void makeDuplicate(E_coli* batterio, vector<E_coli*>& batterioCopy, Funz_C* f, vector<Funz_C*>& fCopy, int n_thread);
void deleteDuplicate(vector<E_coli*>& batterioCopy, Funz_C* f, vector<Funz_C*>& fCopy, int n_thread);

int mergeFilesSimulation(int n_thread, string *names_files_Ecoli_mod, string names_indice_mod, string *names_files_tau_mod, string names_file_dyn_mod);

#endif /* simulation_2MultiT_hpp */
