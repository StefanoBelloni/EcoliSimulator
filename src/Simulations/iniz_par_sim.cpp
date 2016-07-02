//
//  iniz_par_sim.cpp
//  E_Coli2.0
//
//  Created by Stefano Belloni on 20/05/15.
/*This program is free software - GNU General Public License Verison 2*/
//

#include <iostream>
#include "Colori.h"
#include <cmath>
#include "E_Coli.h"
#include "ParameterEstimation_E_Coli.h"
#include "CV_rExp_tExp.h"
#include "sssr.h"
#include "GlobalVariables.h"

using namespace std;

void funz_clear();
void timestamp();

/**
 * This function ititialize the parameters for a simulation. The initialization is done manually, i.e. if I'm reading the answer vector, I read it, otherwise I wait for an imput
 */


void inizializzazione_parametri(int sel_prog, double &T_f, int &n_c, double* x0, int &num_dist,double &Raggio, int &delta_dist, int &const_salv, double &dt)
{
    
//    int condition_if=0;
    n_c=1;
    const_salv=1;
    
    funz_clear();
    
    double sec_save;
//    int N=1;
    
    // MENU INIZIALE: INSERIMENTO DATI SIMULAZIONE
    
    
//    cout << BOLDRED << "WELLCOME:\n\n" << RESET << endl;
    cout << BOLDRED << "*************************************\n"
    << " SIMULATION MENU\n"
    << "*************************************\n" << RESET;
    timestamp ( );
    
    
    cout << BLUE << "\nInsert the duration in sec. of the diffusive-scale process:\n";
    cout << BOLDRED << "NOTE:\n" << RESET;
    cout << "You selected a scale parameter equal to epsilon = "<< epsilon << endl;
    cout << "The time you insert, is then rescaled as follows T_f_simulation = T_f/epsilon^2\n to obtain the final time use to run the simulation\n" << BLUE << "\nT_f = ";
//    cout << "The time you insert, is then rescaled as follows T_f*epsilon^2 = T_f(DiffusiveScale)\n to obtain the time use for the plots and the analysis\n" << BLUE << "T_f = ";
    // Dipends on which time I expect the user to insert ...
    sssr(T_f,"Insert the duration in sec. of the simulation: T_f(Diffusive-scale) ");
    T_f=T_f/(epsilon*epsilon);
    
    /*
    cout << "\nInsert the number N for the step of the simulation: dt = 2^-N\nN = ";
    cin>> N;
    dt=1/pow(2.0,N);
    */
    cout << "\nInsert the time-step of the simulation: dt = ";
    sssr(dt,"time-step of the simulation: dt");
    
    cout << "\nInsert the initial position (deterministic): \n";    
    cout << "\nx0= ";
    sssr(x0[0],"x0");
    
    cout << "\ny0= ";
    sssr(x0[1],"y0");
    
    cout << "\nInsert the number of individuals in the population: n_c = ";
    sssr(n_c,"n_c");
      
    if(n_c!=1){
        cout << "\nWhich distribution around the initial position do you want for the population:\n1->delta_dirac\n2->uniform\n3->x_uniform,y_delta\n4->y_uniform,x_delta\n5->x_sum_delta,y_delta...\n\nn_dis = ";
        sssr(num_dist,"Which distribution around the initial position");
        
        if (num_dist!=1) {
            cout << "\n--->Radius of the distribution: R = ";
            sssr(Raggio,"Radius of the distribution: R");
        }
        if (num_dist==5) {
            cout << "\n---> Number of sources n_sources = ";
            sssr(delta_dist," Number of sources n_sources");
        }
        
//        if (sel_prog==5) {
//            condition_if=1;
//        }
        
//        if (condition_if==0) {
//            
//        }
    }
    
    cout << "\n How often do you want to save the data: Default every "<< dt<<" sec. (not rescaled-time)\n"
         << "non-rescaled T_f for a simulation is T_f_Sim = " << T_f << endl;
    cout << "Insert the seconds: D_save_t = ";
    sssr(sec_save,"How often do you want to save the data");
    const_salv=floor(sec_save/dt);
    
    cout << RESET;
}

#include <fstream>
#include <vector>

/**
 * This function ititialize the parameters for a simulation from a file.
 * It is uesd in int Statistical_Analysis(string name_file_dati, string name_info_file, vector<int> which_compare, int n_compare, int &cont_gen_sim, string &versione_Matlab, int n_c)
 * It might be used to read from file in a different way from the default, so the parameters and not the imput.
 */

void inizializzazione_parametri(int sel_prog, double &T_f, int &n_c, double* x0, int &num_dist,double &Raggio, int &delta_dist, int &const_salv, double &dt, string name_file, vector<Funz_C*> &f, int &tipo_funz_c_class, int &tipo_response_c, double &RC_0, double &RC_1, int &RC_q){
    
    ifstream file_info_stat;
    int change=0;
    
    
    file_info_stat.open(name_file.c_str());
    
    if (!file_info_stat.is_open()) {
        
        cout << BOLDRED << "ERROR OPENING FILE: Insert Parameters Manually." << RESET << endl;
        
        inizializzazione_parametri(sel_prog,T_f,n_c,x0,num_dist,Raggio,delta_dist,const_salv,dt);
        // RC_0 etc dovrebbero essere di default (?!?)
        
    }else{
    
        file_info_stat  >> T_f
                        >> dt
                        >> x0[0]
                        >> x0[1]
                        >> n_c
                        >> num_dist
                        >> Raggio
                        >> delta_dist
                        >> const_salv
                        >> tipo_response_c
                        >> RC_0
                        >> RC_1
                        >> RC_q
                        >> change; 
        
        streampos position = file_info_stat.tellg();
        
        if (change==0) {
            tipo_funz_c_class=0;
        }else {
            tipo_funz_c_class=1;
        }
        
        f[tipo_funz_c_class]->read_info_stat(change, file_info_stat, position);
 
    }
}
