//
//  GoodnessFit_PP.cpp
//  Ecoli_4.1.1
//
//  Created by Stefano Belloni on 05/08/15.
/*This program is free software - GNU General Public License Verison 2*/
//

#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <cstring>
#include "LoadBar.hpp"

//#include "Q_tau_stat.h"
#include "s_lambda.h"
#include "GlobalVariables.h"
#include "Colori.h"

#ifndef max
#define max( a, b ) ( ((a) > (b)) ? (a) : (b) )
#endif
#ifndef min
#define min( a, b ) ( ((a) < (b)) ? (a) : (b) )
#endif

using namespace std;

void loadbar(unsigned int x, unsigned int n, int time_, unsigned int w);
void timestamp ( );
int Stima_tempo(int n_c, int n_val_termine, time_t timer1);
int funz_tipo_file(vector<string> &tipo_dati, int n_col);
int plot_goodness_fit(std::string title_, int n_data, int save_, int n_iterata);
long double rescaled_time(s_lambda lambda, vector<vector<long double> >dati_rec, int n_col, int tipo_file, ifstream &file_dati, long double *m, streampos &position);
void funz_clear();

/** This function implement the test of goodness of fit for point process [Ref. Assessing Model Goodness of Fit from
 The Time-Rescaling Theorem and Its Application to Neural Spike Train Data Analysis
 Emery N. Brown, Riccardo Barbieri et al.]
 * @param lambda estimated value for the probability rate (lambda in the model)
 */

int GoodnessFit_PP(string name_file_dati, s_lambda lambda, int n_data, int n_iterata, long double &D_n, long double &cumD_n){
    
    // (dq,q_max,q_min,Q_tau_vect,name_file_dati, n_stat_tamb,n_q,tau_0_t_stima)
    
    /* ************************************************************************************
     
       Ref. 2.2 Assessing Model Goodness of Fit from 
       The Time-Rescaling Theorem and Its Application to Neural Spike Train Data Analysis
       Emery N. Brown, Riccardo Barbieri et al.     
     
       dalla redeferenza la trasformazione \Lambda->\int_{u_{k-1},u_k}\lambda(t,H)dt produce una sequenza di V.A. exponenzialim dove lambda(t,H) è la funzione-intensità stimata.
       In particolare, conosco max e min di Q ...
     
     
     cose da fare:
     
     [x] 1 - vector Resc_times_vect da fare resize ed inizializzazione
     [x] 2 - sistemare tau nel rescaled_times
     [x] 3 - plot del risulatato
     [x] 4 - cercare di stimare fit of goodness e ritornare 0 se il test è passato, 1 se no ...
     
     
     */

    int n_data_prog=0;
    int n_dataCheck=1000;
    int time_stampato=0;
    
    cout <<BOLDRED<<"\n****************************\n";
    cout << "GoodnessFit_PP ... \n";
    cout <<"\n****************************\n"<<RESET;
    cout << "Iterata : "<< n_iterata << endl;
        
    ifstream file_dati;
    file_dati.open(name_file_dati.c_str());
    
    vector<long double> Resc_times_vect;   // contain the cumulative value "z_k = 1-exp(-tau_k)"
    long double du=max(0.001,1/n_data);
    int error_good=1;
    cout << "Discretization Uniform variable: dU = " << du << endl;
    
    int n_rescale = floor(1/du);
    int U_indeX = 0;
//    long double D_n=0.0;
//    long double cumD_n=0.0;
    Resc_times_vect.resize(n_rescale);
    
    for (int i=0; i<n_rescale; i++) {
        Resc_times_vect[i] = 0.0;
    }
    
    
    long double tau=0.0;
    
    streampos position;
    
    if (!file_dati.is_open()) {
        cout << "Error in opening 'file_dati'\n";
        return -1;
    }else {
        cout << "'file_dati' opened ...\n";
        
        vector<string> tipo_dati;
        vector<vector<long double> > dati_rec;
        string temporary;
        int n_col=-1;
        
        do {
            file_dati >> temporary;
            tipo_dati.push_back(temporary);
            n_col++;
            //            cout << "temporary ... " << temporary << endl;
            
        } while (strcmp(tipo_dati[n_col].c_str(), "EOC"));        
        
        
        //        cout << "n_col = " << n_col << endl;
        
        position=file_dati.tellg();
        
        long double m[3]={0.5,0.25,0.25};
        int tipo_file = funz_tipo_file(tipo_dati, n_col);

        cout << "tipo file = " << tipo_file << endl;
        
        dati_rec.resize(2, vector<long double>( 2+n_col , 0 ));
        
        cout <<BLUE<<"\n****************************\n";
        cout << "Calculation rescaled time ...\n";
        
        time_t timer1;
        time(&timer1);
        timestamp();
        
        cout <<"****************************\n...\n"<<RESET;
        cout << "Analysis of " << n_data << " data"<< endl;
        cout <<"****************************\n";
        while (!file_dati.eof()) {
            
            loadbar(n_data_prog, n_data,time_stampato);
            
            if (n_data_prog==n_dataCheck) {
                time_stampato=Stima_tempo(n_data, n_dataCheck, timer1);
            }
        
            tau=rescaled_time(lambda, dati_rec, n_col, tipo_file, file_dati, m, position);
            tau=1-exp(-tau);
            U_indeX = min(n_rescale-1,max(0,floor(tau/du)));
            Resc_times_vect[U_indeX]+=1.0;
            n_data_prog++;
        }
        
        ofstream dati_goodness;
        dati_goodness.open("dati_goodness.dat");
        
        Resc_times_vect[0]=Resc_times_vect[0]/n_data;
        dati_goodness << 0 << " " << 0 << endl;
        
        cout << "Goodness of Fitness\n";
        
        for (int i=1; i<n_rescale; i++) {
            Resc_times_vect[i]=Resc_times_vect[i]/n_data_prog+Resc_times_vect[i-1];
            dati_goodness << i*du << " " << Resc_times_vect[i] << endl;
            cumD_n+=fabs(i*du-Resc_times_vect[i]);
            D_n=max(D_n, fabs(i*du-Resc_times_vect[i]));
        }

        dati_goodness.close();
        
        
        if (n_iterata==6||automatic_==0) {
            error_good = plot_goodness_fit(name_file_dati,n_data,automatic_,n_iterata);
            if (error_good!=0) {
                cout << "ERROR IN plot_goodness_fit\n";
                remove("dati_goodness.dat");
                return -1;
            }
        }

        
        remove("dati_goodness.dat");
    
    }
    
    file_dati.close();
    
    funz_clear();
    
    cout <<BOLDRED<<"\n****************************\n";
    cout << "GoodnessFit_PP\n";
    cout <<"\n****************************\n"<<RESET;

    // conclusion of the test
    
    if (D_n>1.358/sqrt(n_data)) {
        cout << "****************\n";
        cout << "Test Rejected :\nD_n = " << D_n << " > K_95/sqrt(n) = " << 1.358/sqrt(n_data_prog) << endl;
        cout << "D_n is " << D_n/1.358*sqrt(n_data_prog) << "% bigger then the acceptance level\n";
        cout << "The cumulative distance is: " << cumD_n << endl;
        cout << "****************\n\n";
        return 1;
    }
    cout << "****************\n";
    cout << "Test Accepted :\nD_n = " << D_n << "<= K_95/sqrt(n) = " << 1.358/sqrt(n_data_prog) << endl;
    cout << "****************\n\n";
    return 0;
}

//*************************************************************

/**
 * it calculate the rescaled time using a pice-wise linear approximation in the memory parameter Q(t) in Vergassola celani
 */

long double rescaled_time(s_lambda lambda, vector<vector<long double> >dati_rec, int n_col, int tipo_file, ifstream &file_dati, long double *m, streampos &position)
{
 
    long double tau=0.0;
    
    long double D_theta=.25;
    long double tau_r=1/(3*D_theta);
    long double nu_=4*(1+3*D_theta*tau_r)/(3*tau_r);
    long double beta_2=1;
    long double beta_3=-beta_2/2;
    //long double Q=pow(nu_,2)*beta_2*m[1]+pow(nu_,3)*beta_3*m[2];
    long double Q=0;
    long double t=0.0;
    
    long double c=0.0,d_c=0.0;
    long double dt=0.0;
    
    lambda.CumDen=0.0;
    lambda.Cumlambda=0.0;
    
    switch (tipo_file) {
        {
        case 1:
            /*  VARIENTE 1: (prima approssimazione ... valori solo in prossimità dei salti)
             *   valori:        t_1 c_1    dc_1    T_1  T*1    
             *                  t_2 c_2    dc_2    T_2  T*2
             */         

            
            file_dati.clear();
            file_dati.seekg(position);
            
            for (int i=0; i<n_col; i++) {
                file_dati >> dati_rec[1][i];
            }
            
            c= dati_rec[1][1];
            d_c= dati_rec[1][2];
            dt= dati_rec[1][3];
            
            // if beginning, i.e. a new bacteria is studied set Q(0) = 0
            // the data are bacteria-wise first all about the fisrt bacterium, then the second and so on.
            // if time old is bigger then the recent
            // data dati_rec[0][...] old
            // data dati_rec[1][...] newly read
            
            if (dati_rec[0][0]>=dati_rec[1][0]) {
                
                m[0]=0.5;
                m[1]=0.25;
                m[2]=0.25;
                //Q=0;
                
            }
            
            d_c=(d_c-c)/dt;
            
            long double dt_=0.05;
            int n_dt=max(1, floor(dt/dt_));
            
            dt_ = (n_dt>1)?dt_:dt;
            
            // approx new Q(t)
            
            for (int i=0; i<=n_dt; i++) {
                
                t+=dt_;
                m[2]=m[2]+dt_*(2*m[1]-nu_*m[2]);
                m[1]=m[1]+dt_*(m[0]-nu_*m[1]);
                m[0]=m[0]+dt_*(c-nu_*m[0]);
                
                c+=dt_*d_c;                
                Q=pow(nu_,2)*beta_2*m[1]+pow(nu_,3)*beta_3*m[2];
                
                tau+=dt_*lambda.StatIntensity(dt_,t, Q);
                
            }
            
            position=file_dati.tellg();
            
            break;
        }
        {
        default:
            break;
        }
    }    
    
    
    for (int i=0; i<n_col; i++) {
        dati_rec[0][i]=dati_rec[1][i];
    }
    
    return tau;
    
}
