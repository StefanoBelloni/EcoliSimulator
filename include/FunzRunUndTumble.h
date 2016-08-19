//
//  FunzRunUndTumble.h
//  Ecoli_4.1.1
//
//  Created by Stefano Belloni on 28/07/15.
/*This program is free software - GNU General Public License Verison 2*/
//

#include <string>

void print_and_open_run2V(std::string name, int cont_gen_sim);
void print_and_open_run(std::string name, int cont_gen_sim);
void funz_clear();
void setNames(std::string *names_files_Ecoli_mod, std::string &names_indice_mod, std::string *names_files_tau_mod, std::string &names_file_dyn_mod, std::string *names_info_mod, int tipo_simulazione, int sel_prog, int cont_gen_sim, int stat_);
void Name_jumps(std::string name_file_read, std::string names[], int delete_);
double Analysis_run(std::string name_file_read, std::string names[], int run);
void gnuplot_run(std::string names[], std::string nome_info, double mean, int tipo_run, int save_, int cont_sim);
void gnuplot_run_multiplot(std::string nome_info, std::string names[], int save_, int cont_glob_sim, int tipo_grafico);

