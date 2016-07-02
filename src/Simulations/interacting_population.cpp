//
//  interacting_population.cpp
//  EColi_3.1
//
//  Created by Stefano Belloni on 23/06/15.
/*This program is free software - GNU General Public License Verison 2*/
//

#include <iostream>
#include <vector>
#include <fstream>

#include <limits>
#include <ctime>

using namespace std;

#include "GlobalVariables.h"
#include "sssr.h"

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


void print_and_open_info(string name, E_coli* batterio, Funz_C* f, double T_f, double *x0,  double dt,  int n_c,  double Raggio,  int delta_dist,  int num_dist,  int const_salv, int cont_gen_sim);

/**
 * Base function to produce simulation of  population interacting with the ligand. We pass al the parameters needed, bacteria, model, names of files, type of result( just simulation, or simulate to produce statistical files.
 * From this function you call the gnuplot routine for the analysis,
 * the MATLAB program is not yet ready: we have the file for function C, we should import it and use it properly ... se one should rewrite the m-files
 * the analysis of runs.
 * It's a while loop, so you can repeat the simulation with the same parameters
 */

int interaction_population(Funz_C* f, int n_compare, string *names_Ecoli_mod, string &names_indice_mod, string *names_tau_mod, string &names_file_dyn_mod, string *names_info_mod, int tipo_simulazione, int sel_prog, vector<E_coli* > &batteri_int, double T_f, double *x0,double dt,int n_c,double Raggio,int delta_dist, int num_dist,int const_salv, string &versione_Matlab, string names_jumps[], int &cont_gen_sim, int &which_compare){
    
    // Set the right list of bacteria
    
    int stat_=1;
    
    initialization_interacting_population(tipo_simulazione, &batteri_int, n_c, cont_gen_sim);

    cont_gen_sim++;
    cout << "Set names" << endl;
    setNames(names_Ecoli_mod, names_indice_mod, names_tau_mod, names_file_dyn_mod, names_info_mod, tipo_simulazione, sel_prog, cont_gen_sim, stat_);
    cout << "Simulations" << endl;
    
    int dim_col_t=1;
    
    if (automatic_!=1) {
        print_and_open_info(names_info_mod[0], batteri_int[0], f, T_f, x0, dt, n_c, Raggio, delta_dist, num_dist, const_salv, cont_gen_sim);
    }
    
    double f_max=0;
    
    if (automatic_!=1) {
        dim_col_t=simulation_interacting(batteri_int, T_f, f, x0, dt, n_c, Raggio, delta_dist, num_dist, const_salv, names_Ecoli_mod, names_indice_mod, names_tau_mod, names_file_dyn_mod, names_info_mod, cont_gen_sim, f_max);
    }

    //*********************************           
    // GNUPLOT + MATLAB
    //********************************* 
    {
    if (dim_col_t!=-1) {
        int risp=0;
        
        std::cout << "simulation number " << cont_gen_sim << endl; 
        std::cout << "\ntipo batterio:" << batteri_int[0]->Tipo_batterio << endl;
        cout << "Plot the film via gnuplot(0) or Matlab(1) " << endl; 
        
        if (automatic_==0) {
            
            getInput( risp);
            
        }else {
            risp=0;
        }
        
        
        if (risp==0) {
            
            funz_clear();
            cout <<BOLDRED << "*********************************\n";
            cout           << "*VISUALIZATION WITH GNUPLOT:\n";
            cout           << "*********************************\n"<<RESET;
            
            setNames(names_Ecoli_mod, names_indice_mod, names_tau_mod, names_file_dyn_mod, names_info_mod, tipo_simulazione, sel_prog, cont_gen_sim, stat_);
//            gnuplot_large_population(names_info_mod, names_file_dyn_mod, T_f,n_c,dim_col_t,names_Ecoli_mod[0],f,cont_gen_sim);
            gnuplot_large_population_interacting(names_info_mod, names_file_dyn_mod, T_f,n_c,dim_col_t,names_Ecoli_mod[0],f,cont_gen_sim, f_max);
        }else {
            cout << "Matlab Program not ready yet ... habe Geduld!"<<endl;
        }
    }else {
        cout << "An Error occurred in the simulation ... " << endl;
        return -1;
    }
}
    //*********************************           
    // Analysis Runs and tumbles
    //*********************************           
    if (automatic_!=1) {

        FunzRunUndTumble(T_f,n_c,cont_gen_sim,n_compare,names_Ecoli_mod,names_indice_mod,names_tau_mod,names_file_dyn_mod, names_info_mod, names_jumps,sel_prog,batteri_int,which_compare, stat_);
        
    }    
//    int risposta=1;
    
//    cout << "Delete all files produced in the simulations ? \npress 0 for yes, 1 for no "<<endl
//         << "remember to close all the open files ... "<<endl;
//    cin >> risposta;
//    
//    if (risposta==0) {

    //*********************************           
    // MATLAB
    //*********************************           
    {
        if (n_c>1) {
 
            if (automatic_==0) {
                
                int Matlab=0;
                
                ofstream file_matlab("file_matlab.txt");            
                file_matlab << n_compare << endl;
                file_matlab << cont_gen_sim;
                file_matlab.close();
                
                funz_clear();
                cout <<BOLDRED << "*********************************\n";
                cout           << "VISUALIZATION WITH MATLAB:\n";
                cout           << "*********************************\n"<<RESET;
                
                cout << "\nDo you want to use Matlab to process the files (recomanded for large populations)?\npress 0 for yes, 1 for no ... ";
                //                cin >> Matlab;
                
                getInput( Matlab);
                
                if (Matlab==0) {            
                    
                    if (versione_Matlab=="n") {
                        cout << "write the version of Matlab installed ";
                        cin >> versione_Matlab;
                    } // Altrimenti l'ho già inizializzata.
                    
                    if (n_c>1 && Matlab==0) {
                        Matlab_from_cpp(sel_prog,versione_Matlab); 
                    }
                }
                
            }
            
        }
        
    }
    
    
        setNames(names_Ecoli_mod, names_indice_mod, names_tau_mod, names_file_dyn_mod, names_info_mod, tipo_simulazione, sel_prog, cont_gen_sim, stat_);
        
        Cancella_tutto(names_Ecoli_mod, names_indice_mod, names_tau_mod, names_file_dyn_mod, names_info_mod,1, cont_gen_sim);
            
        
//    }

    batteri_int.resize(0);
    
    return 0;
    
}
