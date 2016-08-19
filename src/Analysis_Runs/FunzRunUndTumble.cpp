//
//  FunzRunUndTumble.cpp
//  Ecoli_3.1.4
//
//  Created by Stefano Belloni on 06/07/15.
/*This program is free software - GNU General Public License Verison 2*/
//

#include <iostream>
#include <vector>

#include <limits>
#include <ctime>

#include "GlobalVariables.h"
#include "Declar_funz.h"
#include "E_Coli.h"
#include "ParameterEstimation_E_Coli.h"
#include "FunzRunUndTumble.h"
#include "Colori.h"
#include "setSizesTitles.hpp"

using namespace std;

string setNameRunMultiplot(int cont_glob_sim, int saveConforme, int tipo_grafico);
void lunch_gnuplot(string name_file_gnu);
void funz_clearAll();

/** This function is like the manu to ANALYSIS RUNS AND TUMBLES
 * @param mostly name of file where to look for data, model to compare and bacteria to llok at the barameters
 * @param which_compare is a vector
 */

void FunzRunUndTumble(double T_f, int n_c, int cont_gen_sim, int n_compare, string *names_Ecoli_mod, string names_indice_mod, string *names_tau_mod, string names_file_dyn_mod, string *names_info_mod, string *names_jumps, int sel_prog, vector<E_coli*> batteri, vector<int> &which_compare, int stat_){
    
    double meanR=0.0;
    double meanT=0.0;
        
    if (T_f>10 || n_c>10) {
        int risposta=1;
        funz_clearAll();
        cout <<BOLDRED << "*********************************\n";
        cout           << "ANALYSIS RUNS AND TUMBLES:\n";
        cout           << "*********************************\n"<<RESET;
        cout << "Do you want to produce a detailed analysis of the runs and tumbles times? \npress 0 for yes, 1 for no ";
        
		sssr(risposta,"Analysis Runs?");

        if (risposta==0) {
            
			cout << "Analysis run" << endl;
            cont_gen_sim-=n_compare;
            
            for (int i=0; i<n_compare; i++) {
                cont_gen_sim++;
                funz_clear();
                
                std::cout << "simulation number " << cont_gen_sim << endl; 
                if (sel_prog==1) {
                    std::cout << "\ntipo batterio:" << batteri[which_compare[i]]->Tipo_batterio << endl;
                }else {
                    std::cout << "\ntipo batterio:" << batteri[0]->Tipo_batterio << endl;
                }

                setNames(names_Ecoli_mod, names_indice_mod, names_tau_mod, names_file_dyn_mod, names_info_mod, which_compare[i], sel_prog, cont_gen_sim, stat_);
                
                //**********************************************************
                // RUN
                Name_jumps(names_tau_mod[0], names_jumps,1);                
                meanR = Analysis_run(names_tau_mod[0], names_jumps,1);
                
                if (meanR<0.0) {
                    cout << "\nError in Analysis_run\n";
                    return;
                }else{
                    cout << "mean = " << meanR << endl;
                }
//                gnuplot_run(names_jumps,names_info_mod[0],mean,1);
                
                //**********************************************************
                // TUMBLE
                Name_jumps(names_tau_mod[1], names_jumps,1);                
                meanT = Analysis_run(names_tau_mod[1], names_jumps,0);
                
                if (meanT<0.0) {
                    cout << "\nError in Analysis_run\n";
                    return;
                }else{
                    cout << "mean = " << meanT << endl;
                }
                
                 //**********************************************************
                
//                gnuplot_run(names_jumps,names_info_mod[0],mean,0);
                // GENERO GLI SCRIPT ...
                
                Name_jumps(names_tau_mod[0], names_jumps,1);
                gnuplot_run(names_jumps,names_info_mod[0],meanR,1,sizeTitle::NO_SAVE,cont_gen_sim);
                Name_jumps(names_tau_mod[1], names_jumps,1);
                gnuplot_run(names_jumps,names_info_mod[0],meanT,0,sizeTitle::NO_SAVE,cont_gen_sim);
                gnuplot_run_multiplot(names_info_mod[0], names_jumps,0,cont_gen_sim,1);
                gnuplot_run_multiplot(names_info_mod[0], names_jumps,0,cont_gen_sim,0);
                
                Name_jumps(names_tau_mod[0], names_jumps,1);
                gnuplot_run(names_jumps,names_info_mod[0],meanR,1,sizeTitle::SAVE,cont_gen_sim);
                Name_jumps(names_tau_mod[1], names_jumps,1);
                gnuplot_run(names_jumps,names_info_mod[0],meanT,0,sizeTitle::SAVE,cont_gen_sim);
                // 1 names_jumps ==salvo----------------------------> <------
                gnuplot_run_multiplot(names_info_mod[0], names_jumps,1,cont_gen_sim,1);
                gnuplot_run_multiplot(names_info_mod[0], names_jumps,1,cont_gen_sim,0);
                
                //**********************************************************
                
                if (automatic_==0) {
                    
                    lunch_gnuplot(setNameRunMultiplot(cont_gen_sim, sizeTitle::NO_SAVE, 1));
                    lunch_gnuplot(setNameRunMultiplot(cont_gen_sim, sizeTitle::NO_SAVE, 0));
                }
                
                risposta=0;
                
                if (risposta==0) {
                    lunch_gnuplot(setNameRunMultiplot(cont_gen_sim, sizeTitle::SAVE, 1));
                    lunch_gnuplot(setNameRunMultiplot(cont_gen_sim, sizeTitle::SAVE, 0));
                }
                
                print_and_open_run2V(names_info_mod[0],cont_gen_sim);
                
                // _u.txt files help to create plots, I remove them when I don't need them
                
                remove("r_u.txt");
                remove("r_d.txt");
                remove("r_c.txt");
                remove("r_m.txt");
                remove("r_a.txt");
                remove("t_a.txt");
                
//                Name_jumps(names_tau_mod[1], names_jumps,0); // last 0 -> delete files
//                Name_jumps(names_tau_mod[1], names_jumps,0);
            }
        }
        
        
//        // Cancello i files
//        cont_gen_sim-=n_compare;
//        for (int i=0; i<n_compare; i++) {
//            cont_gen_sim++;
//            
//            setNames(names_Ecoli_mod, names_indice_mod, names_tau_mod, names_file_dyn_mod, names_info_mod, which_compare[i], sel_prog, cont_gen_sim, stat_);
//            Name_jumps(names_tau_mod[0], names_jumps,0);
//            Name_jumps(names_tau_mod[1], names_jumps,0);
//
//        }
        
    } 
}


//*******************************************************************************************************

/** This function is like the manu to ANALYSIS RUNS AND TUMBLES
 * @param mostly name of file where to look for data, model to compare and bacteria to llok at the barameters
 * @param which_compare is an int
 */

void FunzRunUndTumble(double T_f, int n_c, int cont_gen_sim, int n_compare, string *names_Ecoli_mod, string names_indice_mod, string *names_tau_mod, string names_file_dyn_mod, string *names_info_mod, string *names_jumps, int sel_prog, vector<E_coli*> batteri, int which_compare, int stat_){
    
    double meanR=0.0;
    double meanT=0.0;
    
    if (T_f>10 || n_c>10) {
        int risposta=1;
        funz_clear();
        cout << "ANALYSIS RUNS AND TUMBLES:\n";
        cout << "Do you want to produce a detailed analysis of the runs and tumbles times? \npress 0 for yes, 1 for no ";
        
		sssr(risposta,"Analysis Runs?");
                
		if (risposta==0) {

            cout << "Analysis run" << endl;
            
                funz_clear();
                
                std::cout << "simulation number " << cont_gen_sim << endl;
                if (sel_prog==1) {
                    std::cout << "\ntipo batterio:" << batteri[which_compare]->Tipo_batterio << endl;
                }else {
                    std::cout << "\ntipo batterio:" << batteri[0]->Tipo_batterio << endl;
                }
                
                
                setNames(names_Ecoli_mod, names_indice_mod, names_tau_mod, names_file_dyn_mod, names_info_mod, which_compare, sel_prog, cont_gen_sim, stat_);
                
                // RUN
                Name_jumps(names_tau_mod[0], names_jumps,1);
                meanR = Analysis_run(names_tau_mod[0], names_jumps,1);
                
                
                if (meanR<0.0) {
                    cout << "\nError in Analysis_run\n";
                    return;
                }else{
                    cout << "mean = " << meanR << endl;
                }
                
//                gnuplot_run(names_jumps,names_info_mod[0],mean,1);
            
                //                gnuplot_run(names_jumps,names_info_mod[0],mean,1);
                
                // TUMBLE
                Name_jumps(names_tau_mod[1], names_jumps,1);
                meanT = Analysis_run(names_tau_mod[1], names_jumps,0);
                if (meanT<0.0) {
                    cout << "\nError in Analysis_run\n";
                    return;
                }else{
                    cout << "mean = " << meanT << endl;
                }
                
//                gnuplot_run(names_jumps,names_info_mod[0],mean,0);
            
                //                gnuplot_run(names_jumps,names_info_mod[0],mean,0);
                
                if (automatic_==0) {
                    Name_jumps(names_tau_mod[0], names_jumps,1);
                    gnuplot_run(names_jumps,names_info_mod[0],meanR,1,sizeTitle::NO_SAVE,cont_gen_sim);
                    Name_jumps(names_tau_mod[1], names_jumps,1);
                    gnuplot_run(names_jumps,names_info_mod[0],meanT,0,sizeTitle::NO_SAVE,cont_gen_sim);
                    
                    gnuplot_run_multiplot(names_info_mod[0], names_jumps,0,cont_gen_sim,1);
                    gnuplot_run_multiplot(names_info_mod[0], names_jumps,0,cont_gen_sim,0);
                    
                }
                
                risposta=0;
                
                if (risposta==0) {
                    Name_jumps(names_tau_mod[0], names_jumps,1);
                    gnuplot_run(names_jumps,names_info_mod[0],meanR,1,sizeTitle::SAVE,cont_gen_sim);
                    Name_jumps(names_tau_mod[1], names_jumps,1);
                    gnuplot_run(names_jumps,names_info_mod[0],meanT,0,sizeTitle::SAVE,cont_gen_sim);
                    // 1 names_jumps ==salvo----------------------------> <------
                    gnuplot_run_multiplot(names_info_mod[0], names_jumps,1,cont_gen_sim,1);
                    gnuplot_run_multiplot(names_info_mod[0], names_jumps,1,cont_gen_sim,0);
                }
                
                print_and_open_run2V(names_info_mod[0],cont_gen_sim);
                
                remove("r_u.txt");
                remove("r_d.txt");
                remove("r_c.txt");
                remove("r_m.txt");
                remove("r_a.txt");
                remove("t_a.txt");
                
//                Name_jumps(names_tau_mod[1], names_jumps,0); // last 0 -> delete files
//                Name_jumps(names_tau_mod[1], names_jumps,0);
            
                
                
                
            
//            }
        }
        
        
        // Cancello i files
//        cont_gen_sim-=n_compare;
//        for (int i=0; i<n_compare; i++) {
//            cont_gen_sim++;
        
//            setNames(names_Ecoli_mod, names_indice_mod, names_tau_mod, names_file_dyn_mod, names_info_mod, which_compare, sel_prog, cont_gen_sim, stat_);
//            Name_jumps(names_tau_mod[0], names_jumps,0);
//            Name_jumps(names_tau_mod[1], names_jumps,0);
        
//        }
        
    }
    
    
    
    
    
}





