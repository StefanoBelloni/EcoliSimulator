//
//  simulation_indipendent_2.cpp
//  E_Coli2.1
//
//  Created by Stefano Belloni on 23/05/15.
/*This program is free software - GNU General Public License Verison 2*/
//

#include <iostream>
#include <thread>
#include <sstream>

#include "GlobalVariables.h"
#include "sssr.h"

#include "CV_rExp_tExp.h"
#include "E_Coli.h"
#include "ParameterEstimation_E_Coli.h"
#include "CV_rIG_tExp.h"
#include "Funz_C.h"
#include <vector>
#include <fstream>
#include "Colori.h"
#include "simulation_2MultiT.hpp"

#ifndef min
#define min_( a, b ) ( ((a) < (b)) ? (a) : (b) )
#endif

using namespace std;

void timestamp();
void print_and_open_info(string name, E_coli* batterio, Funz_C* f, long double T_f, long double *x0,  long double dt,  int n_c,  long double Raggio,  int delta_dist,  int num_dist,  int const_salv, int cont_gen_sim);
int simulation_2(E_coli *batterio, long double T_f,Funz_C *f,array<long double,2> x0,long double dt,int n_c,long double Raggio,int delta_dist, int num_dist,int const_salv, string *names_files_Ecoli_mod, string names_indice_mod, string *names_files_tau_mod, string names_file_dyn_mod, string *names_info_mod, int n_sim, int cont_gen_sim, int tot_bacteria, int n_thread);
int writeLog(string what, string msg);

/**
 * Function call to set the parameter of the bacteria: afterwords it start the simulation
 */



int simulation_independent_setting(E_coli *batterio,long double T_f,Funz_C *f,long double *x0,long double dt,int n_c,long double Raggio,int delta_dist, int num_dist,int const_salv,string *names_Ecoli_mod, string names_indice_mod, string *names_tau_mod, string names_file_dyn_mod, string *names_info_mod, int i, int &cont_gen_sim)
{
    
    int change_parameters;
//    int risposta;
    // Parameter setting 
    if (batterio->simulation!=1) {
        batterio->reset_par();
    }

    
    
    std::cout << "simulation number " << cont_gen_sim << endl; 
    cout << "\n****************************************\n";
    timestamp();
    cout << "Type bacterium: "<< batterio->Tipo_batterio << endl;
    
    
    
    
    if (batterio->simulation==0) {
        
        cout << "\nDo you want to change the parameters?"<< endl
             << "0 to use the default" << endl
    //         << "1 setting of the previous simulation" << endl
    //         << "2 take file from a file" << endl
             << "1 edit manually parameters" << endl;
        
        sssr(change_parameters,"Do you want to change the parameters?");
        batterio->change_par(change_parameters);
    }
    
//    cout << "Do you want to plot the response function (with gnuplot) ? \npress 0 for yes, 1 for no ";
//    cin >> risposta;
    // Simulations
//    cout << "sono prossimo ad iniziare le simulationi" << endl;
    
    if (automatic_!=1) {
        
        // LOG FILE
    if (verbose){
       stringstream msg;
       msg.str("");
       msg << "Simulation number " << cont_gen_sim << endl
       << "      Type bacterium: "<< batterio->Tipo_batterio << endl;
       msg << "      Type function: " << f->num_funz << endl;
       msg << "      Number bacteria: " << n_c << endl;
       msg << "      Final Time Experiment: " << T_f << " sec";
       
       writeLog("SIMULATION INDIPENDENT POPULATION",msg.str());
    } 
        print_and_open_info(names_info_mod[0], batterio, f, T_f, x0, dt, n_c, Raggio, delta_dist, num_dist, const_salv,cont_gen_sim);
        if (automatic_==0){
            batterio->gnuplotFunzInternalDynalmic(names_info_mod[0],0,cont_gen_sim);
        }else {
            batterio->gnuplotFunzInternalDynalmic(names_info_mod[0],1,cont_gen_sim);
        }
        
    }
    
    auto start = chrono::steady_clock::now();
    
    int simulation_return=0;
    
    if (automatic_!=1) {
        
        if (n_c>=1000 && T_f >= 50 && multithread) {
            
            int nthread = min_(n_thread_available,std::thread::hardware_concurrency());
            
            cout << BOLDRED << "Simulation Multi-thread: the number of threads is " << nthread << RESET << endl;
            
            simulation_return = simulation_2MultiT(batterio,T_f,f,x0,dt,n_c,Raggio,delta_dist,num_dist,const_salv, names_Ecoli_mod, names_indice_mod, names_tau_mod, names_file_dyn_mod, names_info_mod,i, cont_gen_sim,nthread);
        }else{
        
            simulation_return = simulation_2(batterio,T_f,f,x0,dt,n_c,Raggio,delta_dist,num_dist,const_salv, names_Ecoli_mod, names_indice_mod, names_tau_mod, names_file_dyn_mod, names_info_mod,i, cont_gen_sim,n_c);
        }
        
        
        auto end = chrono::steady_clock::now();
        auto diff = end - start;
        
        
        cout <<BOLDBLACK << "***************************************************\n";
        cout << "Seconds needed to complete the simulation:\n     ";
        cout << chrono::duration <long double, milli> (diff).count()/1000 << " seconds" << endl;
        cout << "***************************************************\n"<<RESET;
       if (verbose){ 
       stringstream msg;        
       msg.str("");
       msg << chrono::duration <long double, milli> (diff).count()/1000 << " seconds";
       writeLog("Simulation terminated in: ",msg.str());
       }
    }
    
    

//    stringstream msg;
    
    // LOG FILE
    
    
    
    return simulation_return;
    
}
