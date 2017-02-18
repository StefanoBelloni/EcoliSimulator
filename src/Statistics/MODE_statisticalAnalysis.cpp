//
//  MODE_statisticalAnalysis.cpp
//  Ecoli_4.1.1
//
//  Created by Stefano Belloni on 25/07/15.
/*This program is free software - GNU General Public License Verison 2*/
//

#include <iostream>
#include <vector>
#include <fstream>

#include <string.h>

//#include "dirent.h"

#include <limits>
#include <ctime>
#include <cstdlib>
#include <cstring>

#include <sys/stat.h>

#include "GlobalVariables.h"
#include "GnuplotGlobal.h"

#include "Q_tau_stat.h"
#include "E_Coli.h"
#include "ParameterEstimation_E_Coli.h"
#include "CV_rExp_tExp.h"
#include "Funz_C.h"
#include "Funz_C_Par.h"
#include "CV_rIG_tExp.h"
#include "CV_rExpIG_tExp.h"
#include "Molecular_rExp_tExp.h"
#include "Colori.h"
#include "Declar_funz.h"
#include "Funz_C_Inter.h"

int Set_Stocasticita(vector<int> &which_compare ,int statisticita);

/**
 * Menu to set the parameters for the statistical Analysis.
 */

int MODE_statisticalAnalysis(string &versione_Matlab, int &cont_gen_sim, vector<string> *pt_name_file_satistics, vector<string> *pt_name_info_satistics, int n_c){
    
    
    string name_file_dati;
    
    vector<int> which_compare;      
    int n_compare = Set_Stocasticita(which_compare, 1);

    
    int n_name_dati=(int)(*pt_name_file_satistics).size();
    
    if (automatic_==1) {
        Statistical_Analysis("automatic", "automatic", which_compare, n_compare, cont_gen_sim, versione_Matlab, n_c);
    }else {
        for (int i=0; i<n_name_dati; i++) {
            Statistical_Analysis((*pt_name_file_satistics)[i], (*pt_name_info_satistics)[i], which_compare, n_compare, cont_gen_sim, versione_Matlab, n_c);
        }

    }
    
    
    
    return 0;
    
}
