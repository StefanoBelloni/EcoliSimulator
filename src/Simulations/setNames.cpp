//
//  setNames.cpp
//  E_Coli2.0
//
//  Created by Stefano Belloni on 22/05/15.
/*This program is free software - GNU General Public License Verison 2*/
//

#include <iostream>
#include <sstream>
#include <string>
#include "FunzRunUndTumble.h"

using namespace std;

/**
 * This function set the names for the file with data of position, directions etc. that are going to be processed. 
 */

void setNames(std::string *names_files_Ecoli_mod, string &names_indice_mod, string *names_files_tau_mod, string &names_file_dyn_mod, string *names_info_mod, int tipo_simulazione, int sel_prog, int cont_gen_sim, int stat_){

    // stat_==0 --> stat_sim mod 
    
    int i=0;
    
    string names_files_Ecoli[3] =  {"X","theta","c"};
    string names_indice         =  "indice";
    string names_files_tau[2]   =  {"tau_r", "tau_t"};
    string names_file_dyn       =  "dyn";
    string names_info[4]        =  {"Ecoli","info_tau","info_tech", "parametri"};
    
    stringstream sstm;

    char buffer_sim[16];

    if (stat_==0) {
        snprintf(buffer_sim, sizeof(char) * 16,"simStat-%03d-",cont_gen_sim);        
    }else{
        snprintf(buffer_sim, sizeof(char) * 16,"sim-%03d-",cont_gen_sim);        
    }
    char buffer[32];
    // Ecoli
    
    for (i=0; i<3; i++) {        
        snprintf(buffer, sizeof(char) * 32,"-%d-%d.dat", tipo_simulazione,sel_prog);        
        names_files_Ecoli_mod[i]=buffer_sim+names_files_Ecoli[i]+buffer;
    }
    // Indice
    snprintf(buffer, sizeof(char) * 32,"-%d-%d.dat", tipo_simulazione,sel_prog);
    names_indice_mod=buffer_sim+names_indice+buffer;
    // tau    
    for (i=0; i<2; i++) {        
        snprintf(buffer, sizeof(char) * 32,"-%d-%d.dat", tipo_simulazione,sel_prog);
        names_files_tau_mod[i]=buffer_sim+names_files_tau[i]+buffer;
    }
    // dyn
    snprintf(buffer, sizeof(char) * 32,"-%d-%d.dat", tipo_simulazione,sel_prog);
    names_file_dyn_mod=buffer_sim+names_file_dyn+buffer;
    // info
    for (i=0; i<4; i++) {        
        snprintf(buffer, sizeof(char) * 32,"-%d-%d.dat", tipo_simulazione,sel_prog);
        names_info_mod[i]=buffer_sim+names_info[i]+buffer;
    }
}
