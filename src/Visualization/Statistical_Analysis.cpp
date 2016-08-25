//
//  Statistical_Analysis.cpp
//  Ecoli_3.1.4
//
//  Created by Stefano Belloni on 16/07/15.
/*This program is free software - GNU General Public License Verison 2*/
//

//**********************************************
//**********************************************

/*      THINGS TO DO  
 *      1 - decidere il formato del file (funz_tipo_file) [x];
 *      2 - DEVO SISTEMARE IL DATO T_i* del tempo di tumble da qualche parte
 *
 *
 */

//**********************************************
//**********************************************


#include <iostream>
#include "E_Coli.h"
#include <vector>
#include <cmath>
#include "Q_tau_stat.h"
#include "sssr.h"
#include "GlobalVariables.h"

#include "ParameterEstimation_E_Coli.h"
#include "ParameterEstimation_CV_rIG_tExp.h"
#include "ParameterEstimation_CV_rExp_tExp.h"


//**********************************************
//**********************************************

/*   WHICH STATISICAL ANALYSIS IS PERFORMED ?
 *   Q_tau_vect è così strutturato:
 *      
 *   Q       q_min q_min+dq q_min+2*dq ... 
 *   m        m_1    m_2       m_3     ...
 *   var      var_1  var_2     var_3   ...
 *   X-       X-_1   X-_2      X-_3    ...     <---(pag 7)   
 *   n_rec    N_1    N_2       N_3     ...
 */


//**********************************************
//**********************************************


using namespace std;

int set_parameter_Q_tau(long double &dq, long double &q_max, long double &q_min, vector<Q_tau_stat> &Q_tau_vect, int &q_0);
int reset_parameter_Q_tau(long double &dq, long double &q_max, long double &q_min, vector<Q_tau_stat> &Q_tau_vect, int n_iterata, int &q_0);
int constract_Q_tau_vect(long double dq, long double q_max, long double q_min, vector<Q_tau_stat> &Q_tau_vect, string name_file_dati, int &n_stat, int n_q, long double &tau_t_stima, long double &q_max_s, long double &q_min_s);

int Statistical_Analysis(string name_file_dati, string name_info_file, vector<int> which_compare, int n_compare, int &cont_gen_sim, string &versione_Matlab);


//**********************************
//    SET PARAMETERS Q_tau
//**********************************

int set_parameter_Q_tau(long double &dq, long double &q_max, long double &q_min, vector<Q_tau_stat> &Q_tau_vect, int &q_0){
    
    int n_q=0;
    long double Q=0.0;
    int risp=0;
    int n_old=(int)Q_tau_vect.size();
    
    
    cout << "Do you want to set the parameter for the step of the Q-variable? \npress 0 for yes, 1 for no "<<endl;

    if (automatic_==0) {
        sssr(risp,"Do you want to set the parameter for the step of the Q-variable?");
    }else{
        risp =-1;
    }

    if (risp==0) {
        cout << "Insert Q_max: ";
        sssr(q_max,"q_max");

        cout << "Insert Q_min: ";
        sssr(q_min,"q_min");

        cout << "Insert the space-step dq: ";
        sssr(dq,"dq");
        
        if (q_max<=q_min) {           
            cout << "Error inserting, default parameters ...\n";
            q_max = 1.0;
            q_min = -1.0;
        }
        

    }else {
        q_max = 1.0;
        q_min = -1.0;
        dq = 0.05;
    }
    
    cout << "[Q_m:dq:Q_M] = [" <<q_min <<":"<<dq<<":" <<q_max << "]" << endl;
    
    Q=q_min;
    
    if ((q_max-q_min)/dq<n_old) {
        Q_tau_vect.resize(0,sizeof(Q_tau_vect));
        while (Q<=q_max) {
            Q_tau_vect.push_back(Q);
            Q+=dq;
            n_q++;
            
            if (Q>=-dq&&Q<=dq) {
                q_0=n_q;
            }
        }
    }else{
    
        while (Q<=q_max && n_q<n_old) {
            Q_tau_vect[n_q].reset(Q);
            Q=Q+dq;
            n_q++;
            
            if (Q>=-dq&&Q<=dq) {
                q_0=n_q;
            }
            
        }
        while (Q<=q_max) {
            Q_tau_vect.push_back(Q);
            Q+=dq;
            n_q++;
            
            if (Q>=-dq&&Q<=dq) {
                q_0=n_q;
            }
        }
    }
//    cout << "END: Set_parameter_Q_tau ... \n"<<endl;
    
    return n_q;
}

int reset_parameter_Q_tau(long double &dq, long double &q_max, long double &q_min, vector<Q_tau_stat> &Q_tau_vect, int n_iterata, int n_tumb, int &q_0){
    
    long double Q=0;
    int n_old=(int)Q_tau_vect.size();
    int n_q=0;
    
    
    // se risetto il max ed il minimo secondo il calcolo ...
    if (n_iterata==6) {
        
//        n_old=0;
        dq = max(.001L,min((q_max-q_min)/sqrt(n_tumb),0.1L));
        
        q_max+=dq;
        q_min-=dq;
        cout << "reset: tipo iterata [minQ,maxQ]:\n";
        
    }else if (n_iterata==7){

        cout << "reset: Last set (Best Fit):\n";
        
        
    }else {
        int signum=2;
        if (n_iterata<0) {
            signum=1;
        }
        
        //    Q_tau_vect.resize(0,sizeof(Q_tau_vect));
        
        //    cout << "Dim Q_tau_vect = " << Q_tau_vect.size()<< endl; 
        
        Q=(q_max-q_min);
        
        if (signum==1 && n_iterata>-1) {
            
            cout << "resert: tipo, iterate <0\n";
            
            Q=Q/2;
        }
        
        
        cout << "*******\n";
        cout << "Reset parameters ... \n";
        
        
        long double q_max_1 =q_max+pow(-1.0,signum)*Q/(pow(2.0, n_iterata));
        long double q_min_1 =q_min-pow(-1.0,signum)*Q/(pow(2.0, n_iterata));
        
        if (q_max>q_min) {
            q_max=q_max_1;
            q_min=q_min_1;
        }
        
        dq = min((q_max-q_min)/sqrt(n_tumb),0.1L);
        
        
        
    }
    
    
    cout << "[Q_m:dq:Q_M] = [" <<q_min <<":"<<dq<<":" <<q_max << "]" << endl;
    
    
        Q=q_min;
        
        // sarebbe sufficientes olo il controllo 'n_q<n_old',
        // ma la prudenza non è mai troppa   
        if ((q_max-q_min)/dq<n_old) {
            Q_tau_vect.resize(0,sizeof(Q_tau_vect));
            while (Q<=q_max) {
                Q_tau_vect.push_back(Q);
                Q+=dq;
                n_q++;
                
                if (Q>=-dq&&Q<=dq) {
                    q_0=n_q;
                }
            }
        }else{
            
            while (Q<=q_max && n_q<n_old) {
                Q_tau_vect[n_q].reset(Q);
                Q=Q+dq;
                n_q++;
                
                if (Q>=-dq&&Q<=dq) {
                    q_0=n_q;
                }
            }
            while (Q<=q_max) {
                Q_tau_vect.push_back(Q);
                Q+=dq;
                n_q++;
                
                if (Q>=-dq&&Q<=dq) {
                    q_0=n_q;
                }
            }
        }
        
//    cout << "Q = " << endl;
//    
//    for (int i=0; i<n_q; i++) {
//        cout << Q_tau_vect[i].Q << " ";
//    }
    
//    cout << endl;
    
    return n_q;
}

//**********************************
//    CONSTRACT Q_tau
//**********************************

#include <fstream>
#include <cstring>

int funz_tipo_file(vector<string> &tipo_dati, int n_col);
void set_Q_tau_vec(vector<Q_tau_stat> &Q_tau_vect, int n_q, int &n_stat_tumb, vector<vector<long double> >&dati_rec, int n_col, int tipo_file, ifstream &file_dati, long double dq, long double q_max, long double q_min, long double *m, streampos &position, long double &tau_0_t_stima, long double &q_max_s,long double &q_min_s);

int constract_Q_tau_vect(long double dq, long double q_max, long double q_min, vector<Q_tau_stat> &Q_tau_vect, string name_file_dati, int &n_stat_tumb, int n_q, long double &tau_t_stima, long double &q_max_s,long double &q_min_s)
/*   I file devono essere così formattati 
 *   nome variable: t    c   delta_c   tau tumble  EOC (=EndOfColumn)     <- senza spazi bianchi
 *   VARIENTE 1:
 *   valori:        t_1  c_1    dc_1    T_1  T_1*                         <- divisi da uno spazio bianco    
 *                  t_2  c_2    dc_2    T_2  T_2*                         <- divisi da uno spazio bianco        
 *
 *   VARIANTE 2:    t_1 c_1    d_c_1   -1,  se non ho un salto, altrimenti lunghezza salto, i.e.
 *                  t_2 c_2    d_c_2   T_2, se non ho un salto, altrimenti lunghezza salto, i.e.
 *                  t_3 c_4    d_c_4   -1, se non ho un salto, altrimenti lunghezza salto, i.e.
 *                  t_4 c_4    d_c_4   -1, se non ho un salto, altrimenti lunghezza salto, i.e.
 *                  t_5 c_5    d_c_5   T_3, se non ho un salto, altrimenti lunghezza salto, i.e.
 */


{
    
    cout << "constract of Q_tau_vect ... \n";
    
    ifstream file_dati;
    file_dati.open(name_file_dati.c_str());
    
    streampos position;
    
    if (!file_dati.is_open()) {
        cout << "Error in opening 'file_dati'\n";
        return -1;
    }else {
        
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

        position=file_dati.tellg();
        
        long double m[3];
        int tipo_file = funz_tipo_file(tipo_dati, n_col);
        
        cout << "tipo file = " << tipo_file << endl;
        
        dati_rec.resize(2, vector<long double>( 2+n_col , 0 ));
        
        while (!file_dati.eof()) {
            
            // A seconda del tipo di file devo usare funzioni differenti
            set_Q_tau_vec(Q_tau_vect,n_q,n_stat_tumb,dati_rec,n_col,tipo_file,file_dati,dq,q_max,q_min,m,position,tau_t_stima, q_max_s, q_min_s);

        }
        
        // Calcolo le medie, var etc.
        
//        int found=0;
//        int j=1;
        
        for (int i=0; i<n_q; i++) {
            if (Q_tau_vect[i].n_rec!=0) {
//                cout << "Q = " << Q_tau_vect[i].Q << "::";
//                cout << "NON EMPTY records ... *******************************************\n";

                Q_tau_vect[i].mean=Q_tau_vect[i].mean/Q_tau_vect[i].n_rec;
                Q_tau_vect[i].invX=Q_tau_vect[i].invX/Q_tau_vect[i].n_rec;
                Q_tau_vect[i].var=(Q_tau_vect[i].var-pow(Q_tau_vect[i].mean,2))/Q_tau_vect[i].n_rec;
            }else {
//                cout << "Q = " << Q_tau_vect[i].Q << "::";
//                cout << "Empty records ... \n";
                
                    
            }

        }
        
        
        
        
    }
    
    file_dati.close();
    
  
    return 0;
    
}



//**********************************
//    SET Q_tau_VECTOR
//**********************************

#include <cmath>

#ifndef max
#define max( a, b ) ( ((a) > (b)) ? (a) : (b) )
#endif
#ifndef min
#define min( a, b ) ( ((a) < (b)) ? (a) : (b) )
#endif

long double Calculate_Q1(long double *m, long double dt, long double c, long double d_c, long double dQ);

void set_Q_tau_vec(vector<Q_tau_stat> &Q_tau_vect, int n_q, int &n_stat_tumb, vector<vector<long double> >&dati_rec, int n_col, int tipo_file, ifstream &file_dati, long double dq, long double q_max, long double q_min, long double *m, streampos &position, long double &tau_0_t_stima, long double &q_max_s, long double &q_min_s)

/*   WHICH STATISICAL ANALYSIS IS PERFORMED ?
 *   Q_tau_vect è così strutturato:
 *      
 *   Q       q_min q_min+dq q_min+2*dq ... 
 *   m        m_1    m_2       m_3     ...
 *   var      var_1  var_2     var_3   ...
 *   X-       X-_1   X-_2      X-_3    ...     <---(pag 7)   
 *   n_rec    N_1    N_2       N_3     ...
 */

{
    
    long double Q=0;
    int index_Q;
    switch (tipo_file) {
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
            
            
            if (dati_rec[0][0]>=dati_rec[1][0]) {
/*
                cout << "Stationary Dynamic ...\n";
                long double T=10;
                long double t=0;
                long double dt=0.1;
                long double D_theta=.25;
                long double tau_r=1/(3*D_theta);
                long double nu_=4*(1+3*D_theta*tau_r)/(3*tau_r);
*/
                m[0]=0.5L;
                m[1]=0.25L;
                m[2]=0.25L;
/*
                while(t<=T) {
                    m[2]=m[2]+dt*(2*m[1]-nu_*m[2]);
                    m[1]=m[1]+dt*(m[0]-nu_*m[1]);
                    m[0]=m[0]+dt*(1-nu_*m[0]); 
                    t=t+dt;    
                }
                cout << m[0] << "," << m[1] << "," << m[2] <<"\n";
*/
                Q=0.0L;
                
            }else {
                Q=Calculate_Q1(m,dati_rec[1][3],dati_rec[1][1],dati_rec[1][2],dq);
            }

            q_max_s=max(Q, q_max_s);
            q_min_s=min(Q, q_min_s);
            
            position=file_dati.tellg();
            
            break;
            
        default:
            
            // Nulla!
            
            break;
    }    
    
    index_Q=max(0,min(n_q-1,floor((Q-q_min)/dq)));
    
    Q_tau_vect[index_Q].mean+=dati_rec[1][3];
    Q_tau_vect[index_Q].var+=dati_rec[1][3]*dati_rec[1][3];
    Q_tau_vect[index_Q].invX+=1/max(dati_rec[1][3],.01);
    Q_tau_vect[index_Q].n_rec++;
//    Q_tau_vect[index_Q].tau_measured.push_back(dati_rec[1][3]);
    Q_tau_vect[index_Q].max_tau+=dati_rec[1][3];
    tau_0_t_stima+=dati_rec[1][4];
    n_stat_tumb++;
    
    
    for (int i=0; i<n_col; i++) {
        dati_rec[0][i]=dati_rec[1][i];
    }
    
    
    
}


//**********************************
// FUNZ FIPO FILE
//**********************************

int funz_tipo_file(vector<string> &tipo_dati, int n_col){

//    t    c   delta_c   tau tumble   EOC
    
    string string_1[6] = {"t", "c", "delta_c", "tau", "tumble" , "EOC"};
    
    int n=-1;
    
    if (n_col==5) {
        
        for (int i=0; i<n_col+1; i++) {

            
            if(strcmp(string_1[i].c_str(), tipo_dati[i].c_str())==0){
                n++;
                
            }
        }
        
        if (n==n_col) {
            return 1;
        }
        
    }
    
    
    return -1;
}


//**********************************
//    CALCULATE_Q
//**********************************


long double Calculate_Q1(long double *m, long double dt, long double c, long double d_c, long double dQ){
    
    long double D_theta=.25;
    long double tau_r=1/(3*D_theta);
    long double nu_=4*(1+3*D_theta*tau_r)/(3*tau_r);
    long double beta_2=1;
    long double beta_3=-beta_2/2;
//    long double Q_=pow(nu_,2)*beta_2*m[1]+pow(nu_,3)*beta_3*m[2];
    long double Q_=0.0;
//    long double Q_1 = -1.0;
    long double Q=0.0;
    long double w=0.0;
    long double cum_w=0.0;
    
//    if (Q_<=dQ && Q_>=-dQ) {
//        Q_1=0.0;
//    }
    
    d_c=(d_c-c)/dt;
    
    long double dt_=0.1;
    int n_dt=max(1, floor(dt/dt_));
    
    dt_ = (n_dt>1)?dt_:dt;
    
    Q_=Q;
    cum_w+=1.0;
    for (int i=0; i<n_dt; i++) {
        m[2]=m[2]+dt_*(2*m[1]-nu_*m[2]);
        m[1]=m[1]+dt_*(m[0]-nu_*m[1]);
        m[0]=m[0]+dt_*(c-nu_*m[0]);
        c+=dt_*d_c;
        
        Q=pow(nu_,2)*beta_2*m[1]+pow(nu_,3)*beta_3*m[2];
        if (Q<=dQ && Q>=-dQ) {
            w=1.0;
            cum_w+=w;
        }else if (Q>dQ){
            w=1.0;
            cum_w+=w;
        }else {
            w=1.0;
            cum_w+=w;
        }
        Q_+=w*Q;
        
 //----->> !!!!!!!       
//        if (i>=n_dt/2.0 && i<=(n_dt+1)/2.0) {
//            Q_1=Q;
//            
////            cout << "Q_1 = " << Q_1 << "i=
//        }
        
    }
    
    // calcolo una sorta di media di Q ...
    
//    cout << "Q = " << Q_ << ",Q_/n_dt = "<< Q_/n_dt << endl;
    
//    if (Q_1==0.0) {
//        return 0.0;
//    }
    
    return Q_/cum_w;

}

    

//**********************************
