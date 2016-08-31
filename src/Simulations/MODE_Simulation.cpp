
//
//  MODE_simulation.cpp
//  Ecoli_4.1.1
//
//  Created by Stefano Belloni on 25/07/15.
/*This program is free software - GNU General Public License Verison 2*/
//

#include <iostream>
#include <vector>
#include <fstream>

#include <string.h>

#include "dirent.h"

#include <limits>
#include <ctime>
#include <cstdlib>
#include <cstring>

#include <sys/stat.h>

#include "GlobalVariables.h"
#include "GnuplotGlobal.h"

#include "Q_tau_stat.h"

#include "ParameterEstimation_E_Coli.h"
#include "CV_rExp_tExp.h"
#include "Funz_C.h"
#include "Funz_C_Par.h"
#include "CV_rIG_tExp.h"
#include "CV_rExpIG_tExp.h"
#include "EO_rExp_tExp.h"
#include "EO_rIG_tExp.h"
#include "Molecular_rExp_tExp.h"
#include "Molecular_rIG_tExp.h"
#include "Colori.h"
#include "Declar_funz.h"
#include "Funz_C_Inter.h"

#include "E_Coli.h"

int Set_Stocasticita(vector<int> &which_compare ,int statisticita);
void create_bacteria_vector(vector<E_coli*> &batteri);
void delete_bacteria_vector(vector<E_coli*> &batteri);
void delete_f_vectors(vector<Funz_C*> &f);

//****************************************************************
// MODE_simulation + Statistics
//****************************************************************

/**
 * Menu to set the parameters for the simulation, decide if interacting or independent population and run the proper simulation
 
    - in the line 154
        int tipo_funz_c_class = set_funz_c(f, sel_prog);
        we obtain the index in vector<Funz_C* > f of the function we want to use.
    - we will pass to the funnction for simulation, statistics etc. the function f[tipo_funz_c_class].
    - in the function set_funz_c(vector<Funz_C*> &f, int interacting) you actually change the parameters of the function, according to its type.
 
 */

int MODE_simulation(string &versione_Matlab, int &cont_gen_sim, vector<string> *pt_name_file_satistics, vector<string> *pt_name_info_satistics){
    
    
    //**********************************************************************************************************80
    //**********************************************************************************************************80
    
    int sel_prog=1;                     // quale programma eseguire

    vector<E_coli* > batteri;
    vector<Funz_C* > f;
    vector<E_coli* > batteri_int;
    
    create_bacteria_vector(batteri);                 // 9  [.]
    
    f.push_back(new Funz_C);
    f.push_back(new Funz_C_Par);
    f.push_back(new Funz_C_Inter);
    
    //*************************
    // Set name of default.
    //*************************
    
    string names_Ecoli_mod[3]; 
    string names_indice_mod;
    string names_tau_mod[2];
    string names_file_dyn_mod;
    string names_info_mod[4];
    string names_jumps[5];
    
    //****************************************************************************
    //                VARIABILI PER INIZIALIZZARE I PARAMETRI
    //****************************************************************************
    
    long double dt=0.01;                     // Time steps
    long double T_f=1;                         // Tempo finale
    int n_c=1;                          // Numero batteri
    long double x0[2]={0,0};                   // Valori deterministici iniziali
    int num_dist=1;                       // Numero distribuzione iniziale
    long double Raggio=0;                      // Raggio distribuzioni
    int delta_dist=1;                     // Numero sorgente
    int const_salv=1;                     // Ogni quanto tempo (cont_salv*dt) salvo 
    
    //**********************************************************************************************************80
    //**********************************************************************************************************80
    
    //******************************
    // RESET THE PARAMETERS

    for (int i=0; i<7; i++) {
        batteri[i]->change_par(0);
    }
    
    for (int i=0; i<3; i++) {
        f[i]->reset_parameter();
    }
    
    //******************************
    

    
    //TIPO SIMULAZIONE (Batterio singolo, Large Population etc. ) 
    
    funz_clear();

    cout<< BOLDRED << "\n\n--------------------------------------------------" <<endl
    << "-               Ecoli - Program.                 -"   << endl
    << "--------------------------------------------------\n\n" << RESET <<endl;
    
    cout << BOLDBLUE << "Chose from the following alternatives:" << endl 
    << "1- Simulation independent population;" << endl 
    << "2- Simulation large population interacting with the ligand" << endl;
    
    sssr(sel_prog,"Simulation independent/interacting");

    
    vector<int> which_compare;      
    int n_compare = Set_Stocasticita(which_compare, 0);

//    vector<int> which_compare;
//    int n_compare = Set_Stocasticita(which_compare, 0);
    
    funz_clear();
    int diffTimeScale=-1;
    cout << BOLDBLUE << "Do you want to perform a simulation with diffusive time-scale parameters?\n" << RESET << endl;
    cout << BOLDRED<< "NOTE:\n"<< RESET << "speed_Diff = epsilon*speed and time_Diff=t/epsilon^2\n";
    cout << "The default parameters for the speed is 0.016 [mm/s] and the time is measured in seconds\n" << BOLDBLUE;
    cout <<  "\npress 0 for yes, 1 for no ";
    sssr(diffTimeScale,"diffusive time-scale parameters:");
    if (diffTimeScale==0){
        cout << "Insert the value of the scale parameter, epsilon\n";
        cout << BOLDRED << "NOTE\n";
        cout << BLUE    << "The default parameters for the speed is 0.016 [mm/s] and the time is measured in seconds\n" << RESET;
        cout << "epsilon = ";
        sssr(epsilon,"diffusive time-scale parameters:");
    }else{
        epsilon=1;
    }
    
    funz_clear();
    int tipo_funz_c_class = set_funz_c(f, sel_prog);
    funz_clear();
    inizializzazione_parametri(sel_prog,T_f,n_c,x0,num_dist,Raggio,delta_dist,const_salv,dt);
    
    funz_clear();
    
//    inizializzazione_parametri(sel_prog,T_f,n_c,x0,num_dist,Raggio,delta_dist,const_salv,dt);
//    funz_clear();
    
    
    switch (sel_prog) {
            
        {
        case 1:
            
//            int tipo_funz_c_class = set_funz_c(f, sel_prog);
            
            int n_stat=1;
            
            int error_indep_pop = independent_population(f[tipo_funz_c_class], n_compare, names_Ecoli_mod, names_indice_mod, names_tau_mod, names_file_dyn_mod, names_info_mod,  sel_prog, which_compare, batteri,  T_f, x0,  dt,  n_c,  Raggio,  delta_dist,  num_dist,  const_salv, versione_Matlab, names_jumps,cont_gen_sim, n_stat, pt_name_file_satistics, pt_name_info_satistics);
            
            if (error_indep_pop==-1) {
                cout << BOLDRED << "Error in the simulation (error_indep_pop) " << RESET << endl;
                return -1;
            }
            
            break;
        }
            
        {
        case 2:
            
//            int tipo_funz_c_class = set_funz_c(f, sel_prog);
            
            for (int i=0; i<n_compare; i++) {
            
//                if (same_seed) {
//                    seed();
//                }
                
                int error_inter_pop = interaction_population(f[tipo_funz_c_class], n_compare, names_Ecoli_mod, names_indice_mod, names_tau_mod, names_file_dyn_mod, names_info_mod, which_compare[i] , sel_prog, batteri_int,  T_f, x0,  dt,  n_c,  Raggio,  delta_dist,  num_dist,  const_salv, versione_Matlab, names_jumps, cont_gen_sim, which_compare[i]);

                
                if (error_inter_pop==-1) {
                    cout << "Error in the simulation (error_inter_pop) ";
                    return -1;
                }
            }
            
            break;
            
        }                
            
        {
        default:
            
            cout << "ERROR ... \n";
            
            break;
        }          
            
    }

    delete_bacteria_vector(batteri);    
    delete_f_vectors(f);
   
    return n_c;
    
}


