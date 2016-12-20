//
//  simulation_interacting.cpp
//  E_Coli2.2
//
//  Created by Stefano Belloni on 23/05/15.
/*This program is free software - GNU General Public License Verison 2*/
//

//------ !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// come salvare gli indici??? cont glob etc.
//------ !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
#include <sstream>
#include <algorithm>    // std::random_shuffle

#include <cstring>
#include<ctime>

#ifndef NO_M_THREAD
#include <thread>
#endif

#include "GlobalRandomVariables.h"

#include "GlobalVariables.h"

#include "Funz_C.h"
#include "Funz_C_Par.h"
#include "Funz_C_Inter.h"
#include "E_Coli.h"
#include "ParameterEstimation_E_Coli.h"
#include "CV_rExp_tExp.h"
#include "LoadBar.hpp"

#include "Manipulation_Matrix.h"

int SolveHeat2D_Neumann2(long double **U, long double **Q, long double n_t, long double r, int n_x, int n_y, long double dt, long double kd_, long double &f_max);
void timestamp();
int Stima_tempo(int n_c, int n_val_termine, int &j_cel_finale, int &j_cel_inizio, time_t timer1);

int initial_position(int j,long double *x, long double *x0, long double Raggio, int num_dist, int &cont_dist_5, int delta_dist_cont, long double Delta_delta_dist);

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
//#define n_val_termine 110

void funz_clear();
void funz_clearAll();
void loadbar(unsigned int x, unsigned int n, unsigned int w);

/**
 * Function that performs the actual simulation of  population interacting with the ligand
 */

int simulation_interacting(vector<E_coli*> batterio, long double T_f,Funz_C *f,long double* x_0,long double dt,int n_c,long double Raggio,int delta_dist, int num_dist,int const_salv, string *names_files_Ecoli_mod, string names_indice_mod, string *names_files_tau_mod, string names_file_dyn_mod, string *names_info_mod, int cont_gen_sim, long double &f_max)
{     
    // In file_fc salvo la funzione c(t,x,y) come "x y f(x,y)"
    
    f_max = 0.0;

#if NO_M_THREAD
    long double x0[2];
#else
    array<long double,2> x0;
#endif    
    
    x0[0]=x_0[0];
    x0[1]=x_0[1];
   const_salv++;
	funz_clear();
    
    char buffer[52];
//    int time_stampato=0;
    
    ofstream call_gnuplot;
    string gnuplot_call="gnuplot file_c_t.gnu";  
    
    snprintf(buffer, sizeof(char) * 52,"Call_Matlab%d.txt", 1);
    
    ofstream file_call_Matlab;
    file_call_Matlab.open(buffer);
    
    // inizializzo gli indici per accedere ai batteri, così mischio solo questi indici...
    vector<int> indici_b(n_c);
    for (int i=0; i<n_c; i++) {
        indici_b[i]=i;
    }
    
    long double errore = 0.00001;
    
    int error_=0;
    int dim_col_t=-1;
    int i=0;
//    char buffer[52];
//    int i_temp=0;
    
    //int change_pos=0;
    long double c_iniziale_prec=-1;
    
    //int cont_string_bat=0;
    
    int n_m0=batterio[0]->N_dyn_var();
//    int change_pos=0; // se change_pos == 0 allora ho cambiato la posizione e ricalcolo la dinamica stazionaria
    vector<long double> m0;
    
    m0.resize(n_m0);
    
    vector<int> sign_p(n_c,2);
    
    long double t=0.0L;                    //tempo cronometro batterio
    //cont_string_bat=0;
    int max_index_T=floor(T_f/dt);
    int n_val_termine=floor(max_index_T*.01)+10;
    // Variabili up/down gradient
    
    int n_files_open=0;
    int n_files=0;
    
    // VARIABLES
    
    long double Delta_delta_dist;
    int delta_dist_cont,cont_dist_5;
//    unsigned int cont_temp;
//    unsigned int cont_salvataggio_pos=0,cont_temp_glob;
    
    delta_dist_cont=fmax(floor(n_c/delta_dist),1);
    
    if (delta_dist!=1)
        Delta_delta_dist=Raggio/(delta_dist-1);
    else
        Delta_delta_dist=Raggio;
    cont_dist_5=delta_dist_cont-1;
    
    // Initial Condition
    
    //****************************************************************************
    // FILES
    //****************************************************************************
    
    // Analysis general
    
    ofstream file_Ecoli[3];
    ofstream file_tau[2];
    ofstream file_index;
    ofstream file_fc;
    ofstream file_info[3];
    
    stringstream sstm;
    
    //Apro i files
    
    for (i=0; i<3; i++) {        
        sstm.str("");
        sstm << names_files_Ecoli_mod[i];
        file_Ecoli[i].open(sstm.str().c_str());
        n_files++;
        if (file_Ecoli[i].is_open()) {n_files_open+=1;}
    }
    // Indice
    sstm.str("");
    sstm << names_indice_mod;
    file_index.open(sstm.str().c_str());
    n_files++;
    if (file_index.is_open()) {n_files_open+=1;}
    
    // tau    
    for (i=0; i<2; i++) {        
        sstm.str("");
        sstm << names_files_tau_mod[i];
        file_tau[i].open(sstm.str().c_str());
        n_files++;
        if (file_tau[i].is_open()) {n_files_open+=1;}
    }
    
    // info
    for (i=0; i<3; i++) {        
        sstm.str("");
        sstm << names_info_mod[i];
        file_info[i].open(sstm.str().c_str());
        n_files++;
        if (file_info[i].is_open()) {n_files_open+=1;}
    }
    
    //******************************************************************************
    //******************************************************************************
    
    if (n_files==n_files_open)  // CONTROLLO APERTURA FILES    
        
    {
       
        dim_col_t=0;

        funz_clear();
        funz_clearAll();
        std::cout << BOLDRED << "***************************************************************************" << endl;
        std::cout            << "*     SIMULATION OF A POPULATION  OF ECOLI INTERACTING WITH THE LIGAND     *" << endl;
        std::cout            << "***************************************************************************\n" << RESET << endl;
        //std::cout <<  "****************************" << endl;
        std::cout            << "      ";
        timestamp();
        std::cout            << "      Simulation number " << cont_gen_sim << endl;
        std::cout            << "      Tipo batterio: " << batterio[0]->Tipo_batterio << endl;
        std::cout            << "      Tipo function: " << f->num_funz << endl;
        std::cout            << "      Number bacteria: " << n_c << endl;
        std::cout            << "      Final Time Experiment: " << T_f << " sec\n"<< endl;
        
        //std::cout <<  "****************************" << endl;
        
        
        
//        std::cout << "simulation number " << cont_gen_sim << endl; 
//        std::cout << "\ntipo batterio:" << batterio[0]->Tipo_batterio << endl;
//        cout <<"****************************************"<<endl;
//        cout << "           SIMULATION" << endl;
//        cout <<"****************************************"<<endl;
        
        long double D_c=f->D_c;   //
        
        // Adjact this from the theory to decide how many time subdivide dt and solve the PDE's there for stability reason
        // TODO: the number of iteratin can be decided by the theory and the parameters of th Diffusion equation ...
        // since it is incoditionally stable, 1 should works!!!
        int n_t= 1;
        const int n_witout_PDE = 10;
        int PDE_iter=0;
        long double dt_=dt*n_witout_PDE;///(long double)n_t;
        
        
        long double r=D_c*dt_/pow(f->dx,2);
//        n_t=max(1,floor(r/.2));
//        cout << "      PDE solution update every "<< dt_ << " seconds" << endl;
//        r=D_c*dt_/pow(f->dx,2);
        
#if NO_M_THREAD
        long double x_f[2];
#else
        array<long double,2> x_f;
#endif        
        long double dx=f->dx;
        
        int n_x=f->n_x;
        int n_y=f->n_y;
        
        // Creo la matrice della soluzione della PDE !!
        long double *U = create_vector2D(n_x, n_y);
        f->f_c = &U;
        
        // Creo la matrice della forzante della PDE !!
        long double *Q = create_vector2D(n_x, n_y);
        f->q_c = &Q;
        
        //***************************************************
        //              INITIAL CONDITIONS
        //***************************************************
        // Ligand
        
        
        cout <<"      Initial data ... Ligand concentration \r" << std::flush;
            // Initial Value.
            for (int i_x = 1; i_x<n_x-1; i_x++) {
                
//                cout << "***************" << endl;
//                cout << "i = "<< i_x << endl; 
                
                for (int i_y = 1; i_y<n_y-1; i_y++) {
                    x_f[0]=f->min_x+i_x*dx;
                    x_f[1]=f->min_y+i_y*dx;
                    U[i_x*n_y+i_y] = f->Funz_C::new_F_C(t, x_f);
                    f_max = max(f_max, U[i_x*n_y+i_y]);
                    Q[i_x*n_y+i_y]=0.0;//max(0,f->degradation_rate*U[i_x*n_y+i_y]);
//                    cout << U[i_x*n_y+i_y] << " "; 
                    
                }
//                cout << endl;
            }
        
            // B.C.     
            for (int i_x = 0; i_x<n_x; i_x++) {        
                U[i_x*n_y+0]     = U[i_x*n_y+1]; 
                U[i_x*n_y+n_y-1] = U[i_x*n_y+n_y-2];
            }  
            
            for (int i_y = 0; i_y<n_y; i_y++) {
                U[0*n_y+i_y]     = U[1*n_y+i_y];
                U[(n_x-1)*n_y+i_y] = U[(n_x-2)*n_y+i_y];        
            }
        
//        cout << "\nDato iniziale:\n"; 
//        print_matrix(U, n_x, n_y);
        
        
        // Batteri

        cout <<"      Initial data ... population of bacteria          \r"<< std::flush;
        
        int cont_temp_glob=1;
        
        file_index << cont_temp_glob << endl;
        
        
        string titolo;
        titolo = batterio[0]->Tipo_batterio+names_info_mod[0];        
        titolo.erase(titolo.end()-4, titolo.end());
        file_info[0] << titolo << endl;

#ifndef NO_M_THREAD
    seedRandomObj(0,this_thread::get_id());
#else
    seedRandomObj(0,rand());
#endif  

        for(int j=0;j<n_c;j++)
        {                       
            batterio[indici_b[j]]->engine_altro = &rnd_ecoli.random_engines[0];
            batterio[indici_b[j]]->engine_barrier = &rnd_ecoli.random_engines[0];
            batterio[indici_b[j]]->engine_theta = &rnd_ecoli.random_engines[0];
            
            //change_pos=
//            initial_position(j,batterio[indici_b[j]]->X(),x0,Raggio,num_dist,cont_dist_5,delta_dist_cont,Delta_delta_dist);

            batterio[indici_b[j]]->initial_position_ec(j,x0,Raggio,num_dist,cont_dist_5,delta_dist_cont,Delta_delta_dist);
            
            batterio[indici_b[j]]->start_simulation(f);
            batterio[indici_b[j]]->stationary_dyn(dt, m0, fabs(batterio[indici_b[j]]->C()-c_iniziale_prec)>errore);
            c_iniziale_prec=batterio[indici_b[j]]->C_iniziale();
            batterio[indici_b[j]]->save_E_coli(file_Ecoli, t);
            
            cont_temp_glob++;
            
        }
        
        cout << "                                                                         " << endl;
        
//        cout << "Print f("<<t<<",:,:)" << endl;                    

        // Print f
        // Cambio il nome e salvo f_c
        
        snprintf(buffer, sizeof(char) * 52, "sim%03dfilm3Dc%i.dat",cont_gen_sim, dim_col_t+1);
        sstm.str("");
        file_fc.open(buffer);        
        f->print_fc(file_fc, t);        
        file_fc.close();
        
        //***********************************************************************
//        if (automatic_!=0) {
//         
//            call_gnuplot.open("file_c_t.gnu");
//            call_gnuplot << "set terminal x11" << endl;
//            call_gnuplot<< "set pm3d interpolate 2,2" << endl;
////            call_gnuplot << "set pm3d map" << endl;
//            call_gnuplot <<  "nome = \""<<buffer<<"\"" << endl;
//            call_gnuplot << "set xrange [ " << f->min_x<<":"<<f->max_x<< "]" << endl
//            << "set yrange [ " << f->min_y<<":"<<f->max_y<< "]" << endl
//            <<  "set title 'Ligang' " << endl
//            << "splot nome with pm3d" << endl
//            << "pause .4" << endl;
//            call_gnuplot.close();
//            //                    cout << "f Printed " << endl;
//            system(gnuplot_call.c_str());
//        }
        //***********************************************************************
        
//        cout << "f Printed " << endl;
        
        file_index << cont_temp_glob << endl;
        cont_temp_glob++;
        
        // VARIABILI TEMPO: DATA ORA
        
        time_t timer1;
        
        char buf[256];
        
        time(&timer1);
        strcpy(buf,ctime(&timer1));
        buf[strlen(buf)-1]='\0';
        
        int j_temp_finale=min(max_index_T,n_val_termine);
        int j_temp_inizio=0;
        int primo_1=0;

        //***************************************************
        
//        cout << "Beginning of the simulation ... " << endl;
        
        std::cout            << "------------------ SIMULATION BEGINS ----------------\n" << RESET << std::endl;
        
        int cont_salvataggio_pos=const_salv;
        
//        cout << "t = " << t << " ... ";
        
        while (primo_1<2) 
        {
            time(&timer1);
        
            for(int i_temp=j_temp_inizio;i_temp<j_temp_finale;i_temp++)
            {
                
                std::random_shuffle ( indici_b.begin(), indici_b.end() );
                
//                loadbar(i_temp, max_index_T,time_stampato);
                loadbar(i_temp, max_index_T);
                t+=dt;
//                cout << "t = " << t << endl;
                
                //************
                //Se creo la matrice Q=0 senz azzerare il loop, devo liberare la matrice alla fine di ogni loop
                // sembra più efficiente !!
//                cout << "create Q " << endl;
//                Q = create_vector2D(n_x, n_y);
//                f->q_c = &Q;
//                cout << "Q created " << endl;
                //************
                
                // loop Batteri
                for(int j=0;j<n_c;j++) {
                    
                    batterio[indici_b[j]]->aggiornamento(dt, t, f, sign_p[indici_b[j]], file_tau, file_Ecoli[1]);
                    
                    if (i_temp==cont_salvataggio_pos)
                    {        
                        cont_temp_glob++;
                        batterio[indici_b[j]]->save_E_coli(file_Ecoli, t);      
                    }                

                }
                // print c(t,x,y)
                if (i_temp==cont_salvataggio_pos)
                {                         
                    //cout << t << " ";
                    
                    dim_col_t++;
                    
                    cont_salvataggio_pos=cont_salvataggio_pos+const_salv;                    
                    file_index << cont_temp_glob << endl;
                    
                    // Print f
                    // Cambio il nome e salvo f_c
                    
//                    cout << "Print f("<<t<<",:,:)" << endl;                    
                    
                    snprintf(buffer, sizeof(char) * 52, "sim%03dfilm3Dc%i.dat", cont_gen_sim, dim_col_t+1);
                    sstm.str("");
                    file_fc.open(buffer);
                    f->print_fc(file_fc, t);                    
                    file_fc.close();  
                    
                    //cout << "... ";
                    
                    //***********************************************
                    
//                    if (automatic_!=0) {
//                        
//                    
//                        call_gnuplot.open("file_c_t.gnu");
//                        call_gnuplot << "set terminal x11" << endl;
////                        call_gnuplot << "set pm3d map" << endl;
//                        call_gnuplot<< "set pm3d interpolate 2,2" << endl;
//                        call_gnuplot <<  "nome = \""<<buffer<<"\"" << endl;
//                        call_gnuplot << "set xrange [ " << f->min_x<<":"<<f->max_x<< "]" << endl
//                                     << "set yrange [ " << f->min_y<<":"<<f->max_y<< "]" << endl
//                                     <<  "set title 'Ligang' " << endl
//                                     << "splot nome with pm3d" << endl
//                                     << "pause .4" << endl;
//                        call_gnuplot.close();
//    //                    cout << "f Printed " << endl;
//                        system(gnuplot_call.c_str());
//                    
//                    }
                    //***********************************************
                    
                }
                
//                cout << "Solve PDE at t = " << t << endl;
                
                if (PDE_iter>n_witout_PDE) {
//                    cout << "Solve PDE at t = " << t << "\r"<< std::flush;
                    error_=SolveHeat2D_Neumann2(f->f_c, f->q_c, n_t, r, n_x, n_y, dt_, f->degradation_rate, f_max);
                    if (error_==-1) {
                        return -1;
                    }
                
                    // B.C. rinforzo!! e azzero la matrice Q ...	
                    for (int i_x = 0; i_x<n_x; i_x++) {
                        for (int i_y = 0; i_y<n_y; i_y++) {
                            Q[i_x*n_y+i_y] = 0.0;// -max(0.0,f->degradation_rate*U[i_x*n_y+i_y]);;
                        }
                    }
                    PDE_iter=0;
                }
                
                PDE_iter++;
                
                /**/
                
                //************
//                delete [] Q;
                //************
                
                if (i_temp==0) {
                    file_info[0] << cont_temp_glob << endl;
                    file_info[0] << dt << endl;
                    file_info[0] << const_salv;
                }
                
            }
        
            
            if (n_val_termine>max_index_T) {
                primo_1=2;;
                
            }
            
            //****************************************************************************
            //                  STIMO TEMPO PER TERMINARE LA SIMULAZIONE
            //****************************************************************************
            
            if (primo_1==0) {
                cout << "\r"<< flush;;
//                time_stampato=Stima_tempo(max_index_T,n_val_termine,j_temp_finale,j_temp_inizio,timer1);
                Stima_tempo(max_index_T,n_val_termine,j_temp_finale,j_temp_inizio,timer1);
            }
            
            primo_1++;
            
            
        }
        
            
            
        // Delete the array dynamiccaly allocated!!
        
    //    freeMatrix(Q,n_x,n_y);
        delete [] U;
        delete [] Q;
        
        std::cout << "\n\n---------------- END SIMULATION ------------\n" << std::endl;
        
        
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
        file_fc.close();
        // info
        for (i=0; i<3; i++) {
            file_info[i].close();
        }
        
    
    }
        
    //**********************************************
    
    remove("gnuplot file_c_t.gnu");
    
    funz_clear();
    
    return dim_col_t;
    
}
