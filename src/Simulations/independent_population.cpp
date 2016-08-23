//
//  simulation_indep.cpp
//  E_Coli_2.3
//
//  Created by Stefano Belloni on 11/06/15.
/*This program is free software - GNU General Public License Verison 2*/
//

#include <iostream>
#include <vector>
#include <fstream>

#include <limits>
#include <ctime>

#include "GlobalVariables.h"
#include "sssr.h"

using namespace std;

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
#include "apngasm_Global.h"

#define SAVE 0

//***************************************************************************************
// independent_population save statistics
//***************************************************************************************

int compareModels(std::vector<E_coli* > &batteri, std::vector<int> &which_compare, int cont_gen_sim, int save_);

/**
 * Base function to produce simulation of independent population. We pass al the parameters needed, bacteria, model, names of files, type of result( just simulation, or simulate to produce statistical files.
 * From this function you call the gnuplot routine for the analysis,
 * the MATLAB program
 * the analysis of runs.
 * It's a while loop, so you can repeat the simulation with the same parameters
 */

int independent_population(Funz_C* f, int n_compare, string *names_Ecoli_mod, string &names_indice_mod, string *names_tau_mod, string &names_file_dyn_mod, string *names_info_mod, int sel_prog, vector<int> &which_compare, vector<E_coli* > &batteri, long double T_f, long double *x0, long double dt,int n_c, long double Raggio,int delta_dist, int num_dist,int const_salv, string &versione_Matlab, string names_jumps[], int &cont_gen_sim, int n_stat, vector<string> *pt_name_file_satistics, vector<string> *pt_name_info_satistics){

    int another_one=0;
    int dim_col_t=1;   
    int stat_=1;
    
    int gnuplot_risp=0;
    int Matlab=0;

    while (another_one==0) {
        
        funz_clear();
        
        //*********************************           
        //          SIMULATION
        //********************************* 
        {
            for (int i=0;i<n_compare;i++) {                        
                cont_gen_sim++;
                setNames(names_Ecoli_mod, names_indice_mod, names_tau_mod, names_file_dyn_mod, names_info_mod,which_compare[i], sel_prog, cont_gen_sim, stat_);
                
//                if (same_seed) {
//                    seed();
//                }
                
                dim_col_t=simulation_independent_setting(batteri[which_compare[i]], T_f, f, x0, dt, n_c, Raggio, delta_dist, num_dist, const_salv, names_Ecoli_mod, names_indice_mod, names_tau_mod, names_file_dyn_mod, names_info_mod,i,cont_gen_sim);
                
                if (dim_col_t==-1) {
                    cout << "ERROR: dim_col_t = " << endl;
                    cout << "line 91, File simulation_indep.cpp" << endl;
                    
                    string msg("Error simulating indepepent population:");
                    writeLog("ERROR",msg);
                    
                    return -1;
                }
            }
        }
        
        //*********************************           
        //     SAVE STATISTICS (IF YES)
        //*********************************
        if(pt_name_file_satistics!=0){
            cont_gen_sim-=n_compare;
            for (int i=0;i<n_compare;i++) {                        
                cont_gen_sim++;
                    File_statistics(batteri[which_compare[i]], T_f, f, x0, dt, n_c, Raggio, delta_dist, num_dist, const_salv, names_Ecoli_mod, names_indice_mod, names_tau_mod, names_file_dyn_mod, names_info_mod,i,cont_gen_sim, pt_name_file_satistics, pt_name_info_satistics);
            }
                
        }
        
        
        //*********************************           
        //          GNUPLOT POPULATION
        //*********************************         
        {
            
        funz_clear();
        cout <<BOLDRED << "*********************************\n";
        cout           << "*VISUALIZATION WITH GNUPLOT:\n";
        cout           << "*********************************\n"<<RESET;

            
        cout << BOLDBLUE << "\nThe Analysis of the Simulation will proceed as follow:";
		if (n_c==1){
			cout << "\n 1- Analysis of the trajectory (with video) and internal dynamics;";
			cout << "\n 2- Analysis of the statistics of runs and tumbles\n";
		}else{
        	cout << "\n 1- Analysis of the density of the population: empirical density (with video), barycenter (speed), m.s.d etc. ";
			cout << "\n 2- Analysis of the statistics of runs and tumbles\n";
        }
		cout << RESET << "\nDo you want to perform step 1 using gnuplot for the visualization?\npress 0 for yes, 1 for no: ";
        //if (automatic_==0) {
//            cin >> gnuplot_risp;    
            //getInput( gnuplot_risp);
        //}else {
            //gnuplot_risp=0;
        //}
        
		sssr(gnuplot_risp,"Do you want to perform step 1 using gnuplot for the visualization");
    

        
        if (gnuplot_risp==0) {
            
            //*********************************
            
            if (n_c==1){
                
                cout << "Gnuplot single" << endl;
                cont_gen_sim-=n_compare;
                for (int i=0;i<n_compare;i++) {                        
                                            
                    cont_gen_sim++;
                    setNames(names_Ecoli_mod, names_indice_mod, names_tau_mod, names_file_dyn_mod, names_info_mod, which_compare[i], sel_prog, cont_gen_sim, stat_);
                    
                    if (automatic_==0) {
                        std::cout << "simulation number " << cont_gen_sim << endl; 
                        std::cout << "\ntipo batterio:" << batteri[which_compare[i]]->Tipo_batterio << endl;
                        batteri[which_compare[i]]->gnuplot_single(names_Ecoli_mod, names_indice_mod, names_tau_mod, names_file_dyn_mod, names_info_mod,T_f,f,0,cont_gen_sim);
                    }
                    
                    gnuplot_risp=0;
                    
                    if (automatic_!=1) {
                        std::cout << "simulation number " << cont_gen_sim << endl; 
                        std::cout << "\ntipo batterio:" << batteri[which_compare[i]]->Tipo_batterio << endl;
                        if (gnuplot_risp==0) {
                            batteri[which_compare[i]]->gnuplot_single(names_Ecoli_mod, names_indice_mod, names_tau_mod, names_file_dyn_mod, names_info_mod,T_f,f,1,cont_gen_sim);
                        }
                    }
                    if (no_apngams) {
                        batteri[which_compare[i]]->gnuplot_single_film_gif(names_Ecoli_mod, names_indice_mod, names_tau_mod, names_file_dyn_mod, names_info_mod,T_f,f,cont_gen_sim);
                    }else{
                        batteri[which_compare[i]]->gnuplot_single_film(names_Ecoli_mod, names_indice_mod, names_tau_mod, names_file_dyn_mod, names_info_mod,T_f,f,cont_gen_sim);
                    }
                    
                    
                        
                }
            }
            
            //*********************************           
            
            else {
                cout << "Film ..." << endl;
                cont_gen_sim-=n_compare;
                for (int i=0;i<n_compare;i++) {
                    cont_gen_sim++;
                    std::cout << "simulation number " << cont_gen_sim << endl; 
                    std::cout << "\ntipo batterio:" << batteri[which_compare[i]]->Tipo_batterio << endl;
                    setNames(names_Ecoli_mod, names_indice_mod, names_tau_mod, names_file_dyn_mod, names_info_mod, which_compare[i], sel_prog, cont_gen_sim, stat_);
                    
//                    if (f->interact!=0) {
                        cout << BOLDBLUE << "Do you want to cover all the domain of the experiment, or just where the bacteria arrived?\n";
                        cout << RED<< " Estimation of covered Domain:\n   (min_x,min_y,max_x,max_y)         = ("
                                   << x0[0]-Raggio-(batteri[0]->V())*T_f << ","
                                   << x0[1]-Raggio-(batteri[0]->V())*T_f << ","
                                   << x0[0]+Raggio+(batteri[0]->V())*T_f << ","
                                   << x0[0]+Raggio+(batteri[0]->V())*T_f << ")\n";
                        cout << YELLOW <<"Experiment Domain:\n   (DomMin_x,DomMin_y,DomMax_x,DomMax_y) = (" << f->min_x << "," << f->min_y << "," << f->max_x << "," << f->max_y << ")" << RESET            ;
                        cout<<"\npress 0 for all domain, 1 for otherwise ";
                        
//                        The answer is in the next function gnuplot_large_population
//                        sssr(risp_Max,"all domain of the experiment");
//                    }
                    
                    gnuplot_large_population(names_info_mod, names_file_dyn_mod, T_f,n_c,dim_col_t,names_Ecoli_mod[0],f,cont_gen_sim);
                    
                    // Up-gain Ligand !!!
                    
                }
                
                // We compare the different Model if more then two simulations were performed.
                
                if (n_compare>1) {
                    
                    int risposta=1;
                    
                    funz_clear();
                    cout <<BOLDRED << "*********************************\n";
                    cout           << "COMPARISON MEAN AND VARIANCE MODELS:\n";
                    cout           << "*********************************\n"<<RESET;
                    cout << "Do you want to produce a detailed Comparison of mean and variances of the models? \npress 0 for yes, 1 for no ";
                    
                    if (automatic_==0) {
                        //                    cin >> risposta;
                        
                        getInput( risposta);
                        
                    }else {
                        risposta=0;
                    }
                    
                    if (risposta==0) {
                        
                        if (automatic_==0) {
                            compareModels(batteri, which_compare, cont_gen_sim-n_compare,!SAVE);
                        }
                    
                        compareModels(batteri, which_compare, cont_gen_sim-n_compare,SAVE);

                    }
                
                }
                
            }
        }
        
        //*********************************           
        // Analysis Runs and tumbles
        //*********************************           
            //if (automatic_!=1) {
                
                FunzRunUndTumble(T_f,n_c,cont_gen_sim,n_compare,names_Ecoli_mod,names_indice_mod,names_tau_mod,names_file_dyn_mod, names_info_mod, names_jumps,sel_prog,batteri,which_compare, stat_);
                
            //}
        }
        
        //*********************************           
        //           MATLAB
        //*********************************           
        {
        if (n_c>1) {
            
            if (automatic_==0) {
                
                
                ofstream file_matlab("file_matlab.txt");            
                file_matlab << n_compare << endl;
                file_matlab << cont_gen_sim;
                file_matlab.close();
                
                funz_clear();
                cout <<BOLDRED << "*********************************\n";
                cout           << "*VISUALIZATION WITH MATLAB:\n";
                cout           << "*********************************\n"<<RESET;
                
                cout << "\nDo you want to use Matlab to perform step 1 and 2?\npress 0 for yes, 1 for no ... ";
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
        
        //*********************************           
        //         Another one?   
        //*********************************           
        {
            funz_clear();
            cout << "\n\nDo you want to simulate another trajectory? \npress 0 for yes, 1 for no ";
            sssr(another_one,"Do you want to simulate another trajectory? press 0 for yes, 1 for no");
            funz_clear();
            
            cont_gen_sim-=n_compare;        
            for (int i=0;i<n_compare;i++) {                        
                cont_gen_sim++;
                setNames(names_Ecoli_mod, names_indice_mod, names_tau_mod, names_file_dyn_mod, names_info_mod, which_compare[i], sel_prog, cont_gen_sim, stat_);            
                Cancella_tutto(names_Ecoli_mod, names_indice_mod, names_tau_mod, names_file_dyn_mod, names_info_mod,i, cont_gen_sim);
            }
            

        
        }
        
    }
            
    return dim_col_t;
}


