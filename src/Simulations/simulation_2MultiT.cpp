//
//  simulation_2MultiT.cpp
//  Ecoli_4.1.5
//
//  Created by Stefano Belloni on 24/05/16.
//  Copyright © 2016 Stefano Belloni. All rights reserved.
//
/* This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 2
 of the License.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 02110-1301, USA. */


#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
#include <sstream>
#include <thread>
#include <system_error>
#include <sys/stat.h>
#include "GlobalVariables.h"
#include <cstring>
#include "simulation_2MultiT.hpp"
#include <unistd.h>

#include "CV_rExp_tExp.h"
#include "CV_rIG_tExp.h"
#include "CV_rExpIG_tExp.h"
#include "EO_rExp_tExp.h"
#include "EO_rIG_tExp.h"
#include "EO_rExpIG_tExp.h"
#include "Molecular_rExp_tExp.h"
#include "Molecular_rExpIG_tExp.h"
#include "Molecular_rIG_tExp.h"
#include "ParameterEstimation_CV_rExp_tExp.h"
#include "ParameterEstimation_CV_rIG_tExp.h"
#include "GlobalRandomVariables.h"

using namespace std;

//Funzioni max e min
#ifndef max
#define max( a, b ) ( ((a) > (b)) ? (a) : (b) )
#endif
#ifndef min
#define min( a, b ) ( ((a) < (b)) ? (a) : (b) )
#endif
#include "constants.h" //#define pi 3.141592653589793238462
#define n_val_termine 200



/*! \brief Function that performs the actual simulation of independent population */


int simulation_2MultiT(E_coli *batterio, long double T_f,Funz_C *f,long double *x0,long double dt,int n_c,long double Raggio,int delta_dist, int num_dist,int const_salv, string *names_files_Ecoli_mod, string names_indice_mod, string *names_files_tau_mod, string names_file_dyn_mod, string *names_info_mod, int n_sim, int cont_gen_sim, int n_thread)
{
    
    
    
    vector<thread> th;
    std::vector<int> num_colonne_parzial(n_thread-1);
    
    int n_c_thread = n_c/n_thread;
    
    cout << "number threads = " << n_thread << endl;
    cout << "number cells for thread: " << n_c_thread <<endl;
    cout << "batterio: " << batterio->Tipo_batterio <<endl;
    
    
    vector<E_coli*> batterioCopia;
    vector<Funz_C*> funzCcopy;
    vector<std::array<long double, 2> > x_0;
    array<long double, 2> x__temp;
    x__temp[0]=x0[0];
    x__temp[1]=x0[1];
    
    makeDuplicate(batterio, batterioCopia, f, funzCcopy, n_thread);
    
    // the threads start
    for(int i=0;i<n_thread-1;i++){
        
//        cout << BOLDBLACK<< "batterio copia therad n. " << i <<": "<< endl
//        << "            -> " << BOLDRED << batterioCopia[i]->Tipo_batterio << endl << RESET
//        << "            -> ";
//        batterioCopia[i]->debugFunction();
        x_0.push_back(x__temp);
        th.push_back(std::thread(startThreadSimulation,batterioCopia[i],T_f,f,x__temp,dt,n_c_thread,Raggio,delta_dist,num_dist,const_salv, names_files_Ecoli_mod, names_indice_mod, names_files_tau_mod, names_file_dyn_mod, names_info_mod,n_sim, cont_gen_sim,i,std::ref(num_colonne_parzial[i])));
        
//        th[i].join();
        

    }
    
    cout << "number cells for the main thread: " << n_c_thread+n_c%n_c_thread <<endl;
    
    int dim_col_t = simulation_2(batterio,T_f,f,x0,dt,n_c_thread+n_c%n_c_thread,Raggio,delta_dist,num_dist,const_salv, names_files_Ecoli_mod, names_indice_mod, names_files_tau_mod, names_file_dyn_mod, names_info_mod,n_sim, cont_gen_sim, n_c, n_thread);
    if(dim_col_t == -1){
        cout << "Error in main thread number." << endl;
        return -1;
    }
    
    // join and get values ...
    for (unsigned int i=0; i<th.size(); i++) {

//        cout << "join in startThreadSimulation ... " << endl;
//        cout << "th["<<i<<"].join();" << endl;

        
        try {
            th[i].join();
            if (num_colonne_parzial[i]==-1) {
                cout << "Error in thread number " << i << endl;
                return -1;
            }
        }
        catch (std::system_error &e) {
            cout << "error:" << endl;
            cout << "std::system_error: " << e.code().message() << endl;
            return -1;
        }

    }
    
    int err_files =  mergeFilesSimulation(n_thread,names_files_Ecoli_mod, names_indice_mod, names_files_tau_mod, names_file_dyn_mod);
    
    
    deleteDuplicate(batterioCopia, f, funzCcopy, n_thread);
    
    funz_clear();

    if (err_files!=0) {
        cout << "Error merging the files ... " << endl;
        return -1;
    }
    
    return dim_col_t;
    
}

/*! \brief set the name of the temporary files ... */

string setNametempFiles(string name, int n_thread){
    
    char buffer[12];
    snprintf(buffer, sizeof(char) * 12,"temp%d_", n_thread);
    string temp = name;
    temp=buffer+temp;
    
    return temp;
}

/*! start a thread of simulation. */

void startThreadSimulation(E_coli *batterio, long double T_f,Funz_C *f,array<long double,2> x0,long double dt,int n_c,long double Raggio,int delta_dist, int num_dist,int const_salv, string *names_files_Ecoli_mod, string names_indice_mod, string *names_files_tau_mod, string names_file_dyn_mod, string *names_info_mod, int n_sim, int cont_gen_sim, int n_thread, int& dim_line_save)
{
    
    
    long double errore = 0.000000001;
    
    seedRandomObj(n_thread+1,this_thread::get_id());

    int n=n_thread+1;
    if (!same_seed) {
        //        cout << "other seed " << endl;
        batterio->engine_altro      = &rnd_ecoli.random_engines[n];
        batterio->engine_barrier    = &rnd_ecoli.random_engines[n];
        batterio->engine_theta      = &rnd_ecoli.random_engines[n];
    }else{
        
        cout << BOLDRED << "same seed ... " << endl << RESET;
        
        batterio->engine_altro = &rnd_ecoli.random_engines[n];
        batterio->engine_barrier = &rnd_ecoli.random_engines_barrier[n];
        batterio->engine_theta = &rnd_ecoli.random_engines_theta[n];
    }

    
    // FILES
    ofstream file_Ecoli[3];
    ofstream file_tau[2];
    ofstream file_index;
    ofstream file_dyn;
    
    stringstream sstm;

    // VARIABILI VARIE
    // Variabili salti
    int n_m0=batterio->N_dyn_var();
    vector<long double> m0;
    long double c_iniziale_prec=-10;
    //-------->
    m0.resize(n_m0);
    
    int i=0;
    int i_temp=0;
    
    int sign_p=2;
    int dim_col_t=1;
    
    // Variabili up/down gradient
    int n_files_open=0;
    int n_files=0;

    // DATI PER LARGE DISTRIBUTION
    long double Delta_delta_dist;
    int delta_dist_cont,cont_dist_5;
    unsigned int cont_temp;
    unsigned int cont_salvataggio_pos=0,cont_temp_glob;//,cont_string_bat;
    
    string temp_str;

    //Apro i files e 'setto' i nuovi nomi
    for (i=0; i<3; i++) {
        my_mutex.lock();
        temp_str = names_files_Ecoli_mod[i];
        my_mutex.unlock();
        
        file_Ecoli[i].open(setNametempFiles(temp_str,n_thread).c_str(), std::ios_base::binary);
        n_files++;
        if (file_Ecoli[i].is_open()) {n_files_open+=1;}
    }
    // Indice
    my_mutex.lock();
    temp_str = names_indice_mod;
    my_mutex.unlock();
    
    file_index.open(setNametempFiles(temp_str,n_thread).c_str(), std::ios_base::binary);
    n_files++;
    if (file_index.is_open()) {n_files_open+=1;}
    // tau
    for (i=0; i<2; i++) {
        
        my_mutex.lock();
        temp_str = names_files_tau_mod[i];
        my_mutex.unlock();
        
        file_tau[i].open(setNametempFiles(temp_str,n_thread).c_str(), std::ios_base::binary);
        n_files++;
        
        if (file_tau[i].is_open()) {n_files_open+=1;}
    }
    // dyn
    my_mutex.lock();
    temp_str = names_file_dyn_mod;
    my_mutex.unlock();
    
    file_dyn.open(setNametempFiles(temp_str,n_thread).c_str(), std::ios_base::binary);
    n_files++;
    if (file_dyn.is_open()) {n_files_open+=1;}
    
 
    //   INIZIALIZZAZIONE PARAMETRI
    
    long double t=0;                    //tempo cronometro batterio
    //cont_string_bat=0;
    int max_index_T=floor(T_f/dt);
    
    // INIZIALIZZAIONE ALCUNE VARIABILI
    delta_dist_cont=fmax(floor(n_c/delta_dist),1);
    
    if (delta_dist_cont!=1){
        Delta_delta_dist=Raggio/(delta_dist-1);
    }
    else{
        Delta_delta_dist=Raggio;
    }
    
    cont_dist_5=delta_dist_cont-1;
    
    // VARIABILI "DINAMICHE"
    cont_temp_glob=0;
    
    string titolo;
    titolo = batterio->Tipo_batterio+names_info_mod[0];
    titolo.erase(titolo.end()-4, titolo.end());
    // CONTROLLO APERTURA FILES
    if (n_files!=n_files_open){
        my_mutex.lock();
        std::cout << "Function: startThreadSimulation " << std::endl;
        std::cout << "thread  = " << n_thread << std::endl;
        std::cout << "ERROR: can't open file for writing." << std::endl;
        std::cout << "n_files = " << n_files << " and f_files_open = " << n_files_open << endl;
        my_mutex.unlock();
        dim_line_save = -1;
        return ;
    }

    for(int j=0;j<n_c;j++){
        
        cont_temp=0;
        
        if (j==1) {
            dim_col_t=cont_temp_glob;
        }
        
        //  INIZIALIAZIONE DATI INIZIALI
        sign_p=2;
        t=0;
//        initial_position(j,batterio->X(),x0,Raggio,num_dist,cont_dist_5,delta_dist_cont,Delta_delta_dist);
//        my_mutex.lock();
        batterio->initial_position_ec(j,x0,Raggio,num_dist,cont_dist_5,delta_dist_cont,Delta_delta_dist);
//        my_mutex.unlock();
        batterio->start_simulation(f);
        batterio->stationary_dyn(dt, m0, fabs(batterio->C()-c_iniziale_prec)>errore);
        c_iniziale_prec=batterio->C_iniziale();
        batterio->save_E_coli(file_Ecoli, t);
        
//        if (batterio->X()[0]>2.1 || batterio->X()[0]<1.9){
//            my_mutex.lock();
//            cout << "thread n. " << n_thread << endl
//            << "batterio n. " << j << endl
//            << "(x0,y0) = " << batterio->X()[0] << " , " << batterio->X()[0] << ")" << endl;
//            my_mutex.unlock();
//        }
        
        file_index << cont_temp_glob << endl;
        
        cont_temp_glob++;
        cont_salvataggio_pos=const_salv;
        
         // Ciclo per la simulazione da t=0 a t=T_f
        for (i_temp=0; i_temp<max_index_T; i_temp++){
            t+=dt;
            batterio->aggiornamento(dt, t, f, sign_p, file_tau, file_Ecoli[1]);
            
            if (cont_temp==cont_salvataggio_pos){
//        if (n_Kthread==1){
//            my_mutex.lock();
//            cout << "thread n. " << n_thread << endl
//            << "batterio n. " << n_thread*n_c+j << endl
//            << "(x,y)(" << t <<") = " << batterio->X()[0] << " , " << batterio->X()[0] << ")" << endl;
//            my_mutex.unlock();
//        }
                batterio->save_E_coli(file_Ecoli, t);
                batterio->save_dyn(file_dyn, t);
                cont_salvataggio_pos=cont_salvataggio_pos+const_salv;
                cont_temp_glob++;
            }
            
            cont_temp++;
        }
        
        // CHIUDO I SALVATAGGI
        batterio->save_E_coli(file_Ecoli, t);
        cont_temp_glob++;
        batterio->save_dyn(file_dyn, t);
    }
    
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
    
    dim_line_save = dim_col_t;

//    my_mutex.lock();
//    cout <<"End Thread ... " << endl;
//     cout << "dim_col_t_parziale[" << i << "] = " << dim_col_t << endl;
//    cout << batterio->Tipo_batterio << endl;
//    my_mutex.unlock();
    
}



/*! \brief This function create a duplicate of the base bacterium and f_c:
 */

void makeDuplicate(E_coli* batterio, vector<E_coli*>& batterioCopy, Funz_C* f, vector<Funz_C*>& fCopy, int n_thread){
    
    switch (batterio->codice_batterio) {
        
        {case EcoliType::E_COLI :
            for (int i = 0; i<n_thread-1; i++) {
                batterioCopy.push_back( new E_coli(*dynamic_cast<E_coli*>(batterio)));
            }
            break;
        }
        {case EcoliType::CV_REXP_TEXP :
            for (int i = 0; i<n_thread-1; i++) {
                batterioCopy.push_back( new CV_rExp_tExp(*dynamic_cast<CV_rExp_tExp*>(batterio)));
            }
            break;
        }
        {case EcoliType::CV_RIG_TEXP :
            for (int i = 0; i<n_thread-1; i++) {
                batterioCopy.push_back( new CV_rIG_tExp(*dynamic_cast<CV_rIG_tExp*>(batterio)));
            }
            break;
        }
        {case EcoliType::CV_RIGEXP_TEXP :
            for (int i = 0; i<n_thread-1; i++) {
                batterioCopy.push_back( new CV_rExpIG_tExp(*dynamic_cast<CV_rExpIG_tExp*>(batterio)));
            }
            break;
        }
        {case EcoliType::MOLECULAR_REXP_TEXP :
            for (int i = 0; i<n_thread-1; i++) {
                batterioCopy.push_back( new Molecular_rExp_tExp(*dynamic_cast<Molecular_rExp_tExp*>(batterio)));
            }
            break;
        }
        {case EcoliType::MOLECULAR_RIG_TEXP :
            for (int i = 0; i<n_thread-1; i++) {
                batterioCopy.push_back( new Molecular_rIG_tExp(*dynamic_cast<Molecular_rIG_tExp*>(batterio)));
            }
            break;
        }
        {case EcoliType::MOLECULAR_RIGEXP_TEXP :
            for (int i = 0; i<n_thread-1; i++) {
                batterioCopy.push_back( new Molecular_rExpIG_tExp(*dynamic_cast<Molecular_rExpIG_tExp*>(batterio)));
            }
            break;
        }
        {case EcoliType::EO_REXP_REXP_TEXP :
            for (int i = 0; i<n_thread-1; i++) {
                batterioCopy.push_back( new EO_rExp_tExp(*dynamic_cast<EO_rExp_tExp*>(batterio)));
            }
            break;
        }
        {case EcoliType::EO_REXP_RIG_TEXP :
            for (int i = 0; i<n_thread-1; i++) {
                batterioCopy.push_back( new EO_rIG_tExp(*dynamic_cast<EO_rIG_tExp*>(batterio)));
            }
            
            break;
        }
        {case EcoliType::EO_REXP_RIGEXP_TEXP :
            for (int i = 0; i<n_thread-1; i++) {
                batterioCopy.push_back( new EO_rExpIG_tExp(*dynamic_cast<EO_rExpIG_tExp*>(batterio)));
            }
            break;
        }
        {case EcoliType::PAR_E_COLI :
            for (int i = 0; i<n_thread-1; i++) {
                batterioCopy.push_back( new ParameterEstimation_E_coli(*dynamic_cast<ParameterEstimation_E_coli*>(batterio)));
            }
            break;
        }
        {case EcoliType::PAR_CV_REXP_TEXP :
            for (int i = 0; i<n_thread-1; i++) {
                batterioCopy.push_back( new ParameterEstimation_CV_rExp_tExp(*dynamic_cast<ParameterEstimation_CV_rExp_tExp*>(batterio)));
            }
            break;
        }
        {case EcoliType::PAR_CV_RIG_TEXP :
            for (int i = 0; i<n_thread-1; i++) {
                batterioCopy.push_back( new ParameterEstimation_CV_rIG_tExp(*dynamic_cast<ParameterEstimation_CV_rIG_tExp*>(batterio)));
            }
            break;
        }
        {case EcoliType::PAR_CV_RIGEXP_TEXP :
            for (int i = 0; i<n_thread-1; i++) {
                batterioCopy.push_back( new ParameterEstimation_E_coli(*dynamic_cast<ParameterEstimation_E_coli*>(batterio)));
            }
            break;
        }
        default:
            for (int i = 0; i<n_thread-1; i++) {
                batterioCopy.push_back( new E_coli(*dynamic_cast<E_coli*>(batterio)));
            }
            break;
    }
    
    if (f->change_par==1) {
        for (int i = 0; i<n_thread-1; i++) {
            fCopy.push_back( new Funz_C_Par(*dynamic_cast<Funz_C_Par*>(f)));
        }
    }else{
        for (int i = 0; i<n_thread-1; i++) {
            fCopy.push_back( new Funz_C(*dynamic_cast<Funz_C*>(f)));
        }
    }
    
//
    
    
}

/*! \brief clean references ... */
void deleteDuplicate(vector<E_coli*>& batterioCopy, Funz_C* f, vector<Funz_C*>& fCopy, int n_thread){
    
    for (int i = 0; i<n_thread-1; i++)
        delete batterioCopy[i];

}

/*! \brief This function merges the files together.
 */

int mergeFilesSimulation(int n_thread, string *names_files_Ecoli_mod, string names_indice_mod, string *names_files_tau_mod, string names_file_dyn_mod){
    
    // Metto i dati tutti insieme
    string temp_str;
    //Apro i files e 'setto' i nuovi nomi
    
    cout << "Mearge all files together ... " << endl;
    
    string s_cwd(getcwd(NULL,0));
    cout << "CWD is: " << s_cwd << endl;
    
    for (int j=0;j<n_thread-1;j++){
        
        ifstream file_temp;
        ofstream file_temp_main;
        
        // Indice
        temp_str = names_indice_mod;
        file_temp.open(setNametempFiles(temp_str,j).c_str(), std::ios_base::binary);
        file_temp_main.open(temp_str.c_str(), std::ios_base::binary | std::ios_base::app|std::ios_base::ate);
        
        if (!file_temp_main.is_open()) {
            cout << "Error opening file (main):  " << temp_str << endl;
            cerr << "open failure: " << strerror(errno) << '\n';
            //            cout << "Press a Key" << endl;
            //            cin >> temp_str;
            //            exit(1);
            return -1;
        }
        
        if (!file_temp.is_open()) {
            cout << "Error opening file (temp):  " << setNametempFiles(temp_str,j) << endl;
            cerr << "open failure: " << strerror(errno) << '\n';
            //            cout << "Press a Key" << endl;
            //            cin >> temp_str;
            //            exit(1);
            return -1;
        }
        
        file_temp_main << file_temp.rdbuf();
        // close ...
        file_temp.close();
        file_temp_main.close();
        file_temp.clear();
        file_temp_main.clear();
        remove(setNametempFiles(temp_str,j).c_str());
        
        
        for (int i=0; i<3; i++) {
            
            //            cout << "temp files for thread n. " << j << endl;
            
            temp_str = names_files_Ecoli_mod[i];
            file_temp.open(setNametempFiles(temp_str,j).c_str(), std::ifstream::in | std::ios_base::binary);
            file_temp_main.open(temp_str.c_str(), std::ios_base::binary | std::ios_base::app |std::ios_base::ate);
            // instead of std::ios_base::ate flag:
            //            file_temp_main.seekp(0, std::ios_base::end);
            
            if (!file_temp_main.is_open()) {
                cout << "Error opening file (main):  " << temp_str << endl;
                cerr << "open failure: " << strerror(errno) << '\n';
                //            cout << "Press a Key" << endl;
                //            cin >> temp_str;
                //                exit(1);
                return -1;
            }
            
            if (!file_temp.is_open()) {
                cout << "Error opening file (temp):  " << setNametempFiles(temp_str,j) << endl;
                cerr << "open failure: " << strerror(errno) << '\n';
                cout << "Press a Key" << endl;
                //            cin >> temp_str;
                //                exit(1);
                return -1;
            }
            
            // concatenate ...
            file_temp_main << file_temp.rdbuf();
            // close ...
            file_temp.close();
            file_temp_main.close();
            file_temp.clear();
            file_temp_main.clear();
            remove(setNametempFiles(temp_str,j).c_str());
            
        }
        
        
        // tau
        for (int i=0; i<2; i++) {
            temp_str = names_files_tau_mod[i];
            file_temp.open(setNametempFiles(temp_str,j).c_str(), std::ios_base::binary);
            file_temp_main.open(temp_str.c_str(), std::ios_base::binary | std::ios_base::app|std::ios_base::ate);
            
            if (!file_temp_main.is_open()) {
                cout << "Error opening file (main):  " << temp_str << endl;
                cerr << "open failure: " << strerror(errno) << '\n';
                //            cout << "Press a Key" << endl;
                //            cin >> temp_str;
                //                exit(1);
                return -1;
            }
            
            if (!file_temp.is_open()) {
                cout << "Error opening file (temp):  " << setNametempFiles(temp_str,j) << endl;
                cerr << "open failure: " << strerror(errno) << '\n';
                cout << "Press a Key" << endl;
                //            cin >> temp_str;
                //                exit(1);
                return -1;
            }
            
            file_temp_main << file_temp.rdbuf();
            // close ...
            file_temp.close();
            file_temp_main.close();
            file_temp.clear();
            file_temp_main.clear();
            remove(setNametempFiles(temp_str,j).c_str());
        }
        // dyn
        temp_str = names_file_dyn_mod;
        file_temp.open(setNametempFiles(temp_str,j).c_str(), std::ios_base::binary);
        file_temp_main.open(names_file_dyn_mod.c_str(), std::ios_base::binary | std::ios_base::app|std::ios_base::ate);
        
        if (!file_temp_main.is_open()) {
            cout << "Error opening file (main):  " << temp_str << endl;
            cerr << "open failure: " << strerror(errno) << '\n';
            //            cout << "Press a Key" << endl;
            //            cin >> temp_str;
            //            exit(1);
            return -1;
        }
        
        if (!file_temp.is_open()) {
            cout << "Error opening file (temp):  " << setNametempFiles(temp_str,j) << endl;
            cerr << "open failure: " << strerror(errno) << '\n';
            //            cout << "Press a Key" << endl;
            //            //            cin >> temp_str;
            //            exit(1);
            return -1;
        }
        
        file_temp_main<< file_temp.rdbuf();
        // close ...
        file_temp.close();
        file_temp_main.close();
        file_temp.clear();
        file_temp_main.clear();
        remove(setNametempFiles(temp_str,j).c_str());
        
    }

    return 0;
    
}
