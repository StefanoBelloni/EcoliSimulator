//
//  Cancella_tutto.cpp
//  E_Coli2.2
//
//  Created by Stefano Belloni on 03/06/15.
/*This program is free software - GNU General Public License Verison 2*/
//

#include <iostream>
#include <vector>
#include <fstream>

using namespace std;
string setBaricenterName(int cont_gen_sim);

/**
 * delete all files created: .dat info, Call_Matlab%d.txt etc. it became redundant with the function void last_deleting();
 * It is used at the end of the simulations, see
 * int independent_population(Funz_C* f, int n_compare, string *names_Ecoli_mod, string &names_indice_mod, string *names_tau_mod, string &names_file_dyn_mod, string *names_info_mod, int sel_prog, vector<int> &which_compare, vector<E_coli* > &batteri, long double T_f, long double *x0, long double dt,int n_c, long double Raggio,int delta_dist, int num_dist,int const_salv, string &versione_Matlab, string names_jumps[], int &cont_gen_sim, int n_stat, vector<string> *pt_name_file_satistics, vector<string> *pt_name_info_satistics)
 * int interaction_population(Funz_C* f, int n_compare, string *names_Ecoli_mod, string &names_indice_mod, string *names_tau_mod, string &names_file_dyn_mod, string *names_info_mod, int tipo_simulazione, int sel_prog, vector<E_coli* > &batteri_int, long double T_f, long double *x0,long double dt,int n_c,long double Raggio,int delta_dist, int num_dist,int const_salv, string &versione_Matlab, string names_jumps[], int &cont_gen_sim, int &which_compare)
 */

void Cancella_tutto(string *names_Ecoli_mod, string names_indice_mod, string *names_tau_mod, string names_file_dyn_mod, string *names_info_mo, int n_sim, int n_sim_gen){
    
//    int i=0;
//    const char * c; 
//    
//    for (i=0; i<3; i++) {        
//        c = names_Ecoli_mod[i].c_str();
//        remove(c);
//    }
//    // Indice
//    c = names_indice_mod.c_str();
//    remove(c);
//    // tau    
//    for (i=0; i<2; i++) {        
//        c = names_tau_mod[i].c_str();
//        remove(c);
//    }
//    // dyn
//    c = names_file_dyn_mod.c_str();
//    remove(c);
//    // info
//    for (i=0; i<4; i++) {        
//        c = names_info_mo[i].c_str();
//        remove(c);
//    }
//    
//    names_info_mo[0].erase(names_info_mo[0].end()-4, names_info_mo[0].end());
//    names_info_mo[0] = names_info_mo[0] + "-info.txt";
//    
//    c = names_info_mo[i].c_str();
//    remove(c);
    
    char buffer[32];

    snprintf(buffer, sizeof(char) * 32,"Call_Matlab%d-sim-%03d.txt", n_sim,n_sim_gen);
    remove(buffer);
    
    snprintf(buffer, sizeof(char) * 32,"Call_Matlab%d.txt", 1);
    remove(buffer);
    
//    remove("plot_batterium.gnu");
//    remove("run.gnu");
//    remove("3D_hist.gnu");
//    remove("play_video.gnu");
//    remove("file_matlab.txt");
//    remove("file_gnu.gnu");
////    remove("baricentro_plot.dat");
//    // da sostituire con il corretto file baricentro
//    remove(setBaricenterName(n_sim_gen).c_str());
//    remove("baricentro_plot.gnu");
//    remove("run2.gnu");
//    remove("run1.gnu");
//    remove("dynamic.gnu");
//    remove("fit.log");

    
}
