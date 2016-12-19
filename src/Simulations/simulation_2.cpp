//
//  simulation_2.cpp
//  E_Coli2.1
//
//  Created by Stefano Belloni on 23/05/15.
/*This program is free software - GNU General Public License Verison 2*/
//

#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
#include <sstream>
#include <ctime>
#ifndef NO_M_THREAD
#include <thread>
#endif
#include <cstring>

#include "Funz_C.h"
#include "Funz_C_Par.h"
#include "E_Coli.h"
#include "ParameterEstimation_E_Coli.h"
#include "CV_rExp_tExp.h"
#include "GlobalVariables.h"
#include "GlobalRandomVariables.h"

#include "LoadBar.hpp"

int Stima_tempo(int n_c, int n_val_termine, int &j_cel_finale, int &j_cel_inizio, time_t timer1);
int initial_position(int j,long double *x, long double *x0, long double Raggio, int num_dist, int &cont_dist_5, int delta_dist_cont, long double Delta_delta_dist);
void timestamp ( );
void funz_clearAll();
void loadbar(unsigned int x, unsigned int n, int time_, unsigned int w);

using namespace std;

//Funzioni max e min
#ifndef max
#define max( a, b ) ( ((a) > (b)) ? (a) : (b) )
#endif
#ifndef min
#define min( a, b ) ( ((a) < (b)) ? (a) : (b) )
#endif

// COSTANTI

#include "constants.h" //#define pi 3.141592653589793238462
#define n_val_termine 200

void funz_clear();

/**
 * Function that performs the actual simulation of independent population
 */


int simulation_2(E_coli *batterio, long double T_f,Funz_C *f,long double *x_0,long double dt,int n_c,long double Raggio,int delta_dist, int num_dist,int const_salv, string *names_files_Ecoli_mod, string names_indice_mod, string *names_files_tau_mod, string names_file_dyn_mod, string *names_info_mod, int n_sim, int cont_gen_sim, int tot_bacteria, int n_thread)
{        
//    funz_clear();      
    
     #ifndef NO_M_THREAD
    seedRandomObj(0,this_thread::get_id());
    #else
    seedRandomObj(0,rand());
    #endif 
//    cout << "same seed true = " << true << ", seed: " << same_seed << endl;
    
    int n=0;
    if (!same_seed) {
        cout << "other seed " << endl;
        batterio->engine_altro      = &rnd_ecoli.random_engines[n];
        batterio->engine_barrier    = &rnd_ecoli.random_engines[n];
        batterio->engine_theta      = &rnd_ecoli.random_engines[n];
    }else{
    
        batterio->engine_altro = &rnd_ecoli.random_engines[n];
        batterio->engine_barrier = &rnd_ecoli.random_engines_barrier[n];
        batterio->engine_theta = &rnd_ecoli.random_engines_theta[n];
    }
    

    
    char buffer[52];
    int time_stampato=(n_c==1)?0:1;
    array<long double,2> x0;
    x0[0]=x_0[0];
    x0[1]=x_0[1];
    long double errore = 0.000000001;
    
    snprintf(buffer, sizeof(char) * 52,"Call_Matlab%d-sim-%03d.txt", n_sim,cont_gen_sim);
    
    ofstream file_call_Matlab;
    file_call_Matlab.open(buffer);
    
    //****************************************************************************
    //                           VARIABILI VARIE
    //**************************************************************************** 
    
    // Variabili salti
    int n_m0=batterio->N_dyn_var();
    //int change_pos=0;
    // se change_pos == 0 allora ho cambiato la posizione e ricalcolo la dinamica stazionaria
    vector<long double> m0;
    long double c_iniziale_prec=-10;
    m0.resize(n_m0);
    
    int i=0;
    int i_temp=0;
    
    int sign_p=2;
    int dim_col_t=1;
    
    // Variabili up/down gradient
    
    int n_files_open=0;
    int n_files=0;
    // contatori salti.
    
    //**************************************************************************
    // DATI PER LARGE DISTRIBUTION
    //**************************************************************************
    
    // VARIABLES
    
    long double Delta_delta_dist;
    int delta_dist_cont,cont_dist_5;
    unsigned int cont_temp;
    unsigned int cont_salvataggio_pos=0,cont_temp_glob;//,cont_string_bat;
    
    int j_cel_finale=min(n_c,n_val_termine);
    int j_cel_inizio=0;
    int primo_1=0;
    
    //****************************************************************************
    // FILES
    //****************************************************************************
    // Analysis general
    
    ofstream file_Ecoli[3];
    ofstream file_tau[2];
    ofstream file_index;
    ofstream file_dyn;
    ofstream file_info[4];
    
    stringstream sstm;
    
//    sstm.str("");
    
//    cout << "NOMI FILES ..." << endl;
//    snprintf(buffer, sizeof(char) * 52,"temp%d_", cont_gen_sim);
//    sstm << buffer << names_files_Ecoli_mod[i];
//    
//
//    string temp = names_files_Ecoli_mod[i];
//    temp=buffer+temp;
//
//    cout << "nome: " << names_files_Ecoli_mod[i] << endl;
//    cout << "nome(sstm): " << sstm.str() << endl;
//    cout << "nome(string): " << temp << endl;
    
    
    //Apro i files
    {
    for (i=0; i<3; i++) {        
        sstm.str("");
        
        my_mutex.lock();
        sstm << names_files_Ecoli_mod[i];
        my_mutex.unlock();
        
        file_Ecoli[i].open(sstm.str().c_str(), std::ios_base::binary);
        n_files++;
        if (file_Ecoli[i].is_open()) {n_files_open+=1;}
    }
    // Indice
    sstm.str("");
    
    my_mutex.lock();
    sstm << names_indice_mod;
    my_mutex.unlock();
        
    file_index.open(sstm.str().c_str(), std::ios_base::binary);
    n_files++;
    if (file_index.is_open()) {n_files_open+=1;}
    // tau    
    for (i=0; i<2; i++) {        
        sstm.str("");
        my_mutex.lock();
        sstm << names_files_tau_mod[i];
        my_mutex.unlock();
        file_tau[i].open(sstm.str().c_str(), std::ios_base::binary);
        n_files++;
        if (file_tau[i].is_open()) {n_files_open+=1;}
    }
    // dyn
    sstm.str("");
    my_mutex.lock();
    sstm << names_file_dyn_mod;
    my_mutex.unlock();
        
    file_dyn.open(sstm.str().c_str(), std::ios_base::binary);
    n_files++;
    if (file_dyn.is_open()) {n_files_open+=1;}
    
    // info
    for (i=0; i<4; i++) {        
        sstm.str("");
        my_mutex.lock();
        sstm << names_info_mod[i];
        my_mutex.unlock();
        file_info[i].open(sstm.str().c_str(), std::ios_base::binary);
        n_files++;
        if (file_info[i].is_open()) {n_files_open+=1;}
    }
    }
    
//    file_dyn << "#Questo è il file dove salvo la dinamica delle variabili interne" << endl;
    //****************************************************************************
    // VARIABILI TEMPO: DATA ORA
    
    time_t timer1;
    
    char buf[256];
    
    time(&timer1);
    strcpy(buf,ctime(&timer1));
    buf[strlen(buf)-1]='\0';

    //****************************************************************************
    //                      INIZIALIZZAZIONE PARAMETRI
    //****************************************************************************
    
    
    long double t=0;                    //tempo cronometro batterio 
    //cont_string_bat=0;
    int max_index_T=floor(T_f/dt);
//    int n_salv=0;
    // INIZIALIZZAIONE ALCUNE VARIABILI    
    
    delta_dist_cont=fmax(floor(n_c/delta_dist),1);
    
    if (delta_dist_cont!=1)
        Delta_delta_dist=Raggio/(delta_dist-1);
    else
        Delta_delta_dist=Raggio;
    
    cont_dist_5=delta_dist_cont-1;
    
    
    // VARIABILI "DINAMICHE"
    
    //cont_temp=0;
    cont_temp_glob=0;


    
    funz_clear();
    funz_clearAll();
    
    
    std::cout << BOLDRED;
        my_mutex.lock();
    std::cout << "******************************************************" << endl;
    std::cout            << "*     SIMULATION INDEPENDENT POPULATION OF ECOLI     *" << endl;
    std::cout            << "******************************************************\n";
    my_mutex.unlock();
    std::cout<< RESET << endl;
            my_mutex.lock();
    //std::cout <<  "****************************" << endl;
    std::cout            << "      ";
    timestamp();
    std::cout            << "      Simulation number " << cont_gen_sim << endl;
    std::cout            << "      Tipo batterio: " << batterio->Tipo_batterio << endl;
    std::cout            << "      Tipo function: " << f->num_funz << endl;
    std::cout            << "      Number bacteria: " << tot_bacteria << endl;
    std::cout            << "      Final Time Experiment: " << T_f << " sec"<< endl;
    std::cout            << "      Number threads: " << n_thread << "."<< endl;
    //std::cout <<  "****************************" << endl;

    std::cout            << "\n------------------ SIMULATION BEGINS ----------------\n";
    
    my_mutex.unlock();
    std::cout  << RESET << std::endl;
    
    
    string titolo;
    titolo = batterio->Tipo_batterio+names_info_mod[0];
    
    titolo.erase(titolo.end()-4, titolo.end());
    
    if (n_files==n_files_open)  // CONTROLLO APERTURA FILES    
        
    {     
        
        file_info[0] << titolo << endl;
        
        // Divido in batteri in due gruppi e stimo il tempo per terminare la simulazione.
        
        while (primo_1<2) 
        {
            time(&timer1);
            
            for(int j=j_cel_inizio;j<j_cel_finale;j++){
                
//                cout << "thread: main, batterio n. " << j << "\r" << flush;;

                //questa è quella giusta!
                loadbar(j,n_c, time_stampato);
    
//                loadbar(j,n_c);
                cont_temp=0;
                
                if (j==1) {
                    dim_col_t=cont_temp_glob;
                }
                
                //  INIZIALIAZIONE DATI INIZIALI
                sign_p=2;
                t=0;
                
                //change_pos=...
//                initial_position(j,batterio->X(),x0,Raggio,num_dist,cont_dist_5,delta_dist_cont,Delta_delta_dist);
//                my_mutex.lock();
                batterio->initial_position_ec(j,x0,Raggio,num_dist,cont_dist_5,delta_dist_cont,Delta_delta_dist);
//                my_mutex.unlock();
                
                batterio->start_simulation(f);
                batterio->stationary_dyn(dt, m0, fabs(batterio->C()-c_iniziale_prec)>errore);
                c_iniziale_prec=batterio->C_iniziale();
                batterio->save_E_coli(file_Ecoli, t);
                
                file_index << cont_temp_glob << endl;

                cont_temp_glob++;
                cont_salvataggio_pos=const_salv;
                
                for (i_temp=0; i_temp<max_index_T; i_temp++) // Ciclo per la simulazione da t=0 a t=T_f
                {
                    t+=dt;
//                    cout << "t = " << t << endl;
                    batterio->aggiornamento(dt, t, f, sign_p, file_tau, file_Ecoli[1]);
//                    cout << "aggiornato ..." << endl;
                    if (cont_temp==cont_salvataggio_pos)
                    {
                        
                        batterio->save_E_coli(file_Ecoli, t);
                     
//                        if (n_c==1) {
                            batterio->save_dyn(file_dyn, t);
//                        } 
                        
                        cont_salvataggio_pos=cont_salvataggio_pos+const_salv;
                        cont_temp_glob++;
                        
                    }
                    
                    //****************************************************************************80
                    
                    cont_temp++;
//                    cout << "qui ..." << endl;
                    
                }
                
                //**************************
                // CHIUDO I SALVATAGGI
                
//                if (cont_salvataggio_pos-const_salv!=max_index_T-2) {
                    batterio->save_E_coli(file_Ecoli, t);
                    cont_temp_glob++;
//                    if (n_c==1) {
                        batterio->save_dyn(file_dyn, t);
//                    } 
//                }
                
                
//                if (batterio->salto_==1) {
//                    batterio->save_run(t,file_tau[0],dt);
//                    
//                }else {
//                    batterio->save_tumble(t,file_tau[1],dt);
//                }
//                

                //**************************
                
                if (j==0) {
//                    cout << "const_salv = " << const_salv << endl;
                    file_info[0] << cont_temp_glob << endl;
                    file_info[0] << dt << endl;
                    file_info[0] << const_salv;
                }

                
            
            }
            
            if (n_val_termine>n_c) {
                primo_1=2;;
                
            }
            
            //****************************************************************************
            //                  STIMO TEMPO PER TERMINARE LA SIMULAZIONE
            //****************************************************************************
            
            if (primo_1==0) {
                cout << "\r"<< flush;;
                time_stampato=Stima_tempo(n_c,n_val_termine,j_cel_finale,j_cel_inizio,timer1);
//                Stima_tempo(n_c,n_val_termine,j_cel_finale,j_cel_inizio,timer1);
            }
            
            primo_1++;
            
            //****************************************************************************
            
        }
        
        
        //****************************************************************************
        //                     SALVO INFORMAZIONI GENERALI
        //****************************************************************************
             
        file_index << const_salv << endl;
        
        file_call_Matlab << names_files_Ecoli_mod[0] << endl;
        file_call_Matlab << names_indice_mod << endl;
        file_call_Matlab << names_files_tau_mod[0] << endl;
        file_call_Matlab << names_files_tau_mod[1] << endl;        
        file_call_Matlab << T_f << endl;
        file_call_Matlab << dt*const_salv << endl;
        file_call_Matlab << f->num_funz << endl;
        file_call_Matlab << f->interact << endl;
        file_call_Matlab << dim_col_t << endl;
        file_call_Matlab << n_c << endl;
        
        //****************************************************************************
        //                              CHIUDO I FILES
        //****************************************************************************
        
        std::cout << "\n\n---------------- END SIMULATION ------------\n" << std::endl;
        
        
        //Chiudo i files
        
        for (i=0; i<3; i++) {        
            file_Ecoli[i].close();
        }
        // Indice
        file_index.close();
        
        // tau    
        for (i=0; i<2; i++) {        
            file_tau[i].close();
        }
        // dyn
        file_dyn.close();
        // info
        for (i=0; i<4; i++) {        
            file_info[i].close();
        }
        
        //****************************************************************************
        
        
        //****************************************************************************
        
    }
    else
    {
        // otherwise print a message
        std::cout << "Function: simulation_2" << std::endl;
        std::cout << "ERROR: can't open file for writing." << std::endl;
        return -1;
    }
    
//    funz_clear();
    
    return dim_col_t;
    
}

