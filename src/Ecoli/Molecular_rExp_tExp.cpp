//
//  Molecular_rExp_tExp.cpp
//  E_Coli2.2
//
//  Created by Stefano Belloni on 01/06/15.
/*This program is free software - GNU General Public License Verison 2*/
//

#include <iostream>
#include <cmath>
#include <fstream>

#include "FunzRand.h"
#include "Funz_C.h"
#include "E_Coli.h"
#include "ParameterEstimation_E_Coli.h"
#include "Molecular_rExp_tExp.h"
#include "ParameterEstimation_E_Coli.h"
#include "sssr.h"

#ifndef max
#define max( a, b ) ( ((a) > (b)) ? (a) : (b) )
#endif
#ifndef min
#define min( a, b ) ( ((a) < (b)) ? (a) : (b) )
#endif

using namespace std;

int SecantMethodForEquation(Molecular_rExp_tExp *batterio, long double& x, long double x0, long double x1, long double c);

Molecular_rExp_tExp::Molecular_rExp_tExp():ParameterEstimation_E_coli(){
    
    Tipo_batterio = "Molecular-rExp-tExp";
    codice_batterio = EcoliType::MOLECULAR_REXP_TEXP;
    simulation = 0;
    a_m=2;
    m_0=0.5;
    K_off=18;
    K_on=3;
    n_a=4;
    
    M_max=4;
    A_max=10;
    L_max=5;
    y_max=1;
    
    K_R=0.02;
    K_B=0.02;
    
    kCheR=0.1;
    kCheB=0.2;
//    y_0=0.696729639775898;
//    y_0=0.4;
    y_0=0.520504;
    k_a=3;
    k_z=2;
    H=10;
    
    a=0.723682;
    y=0.520505;
    meth=0.00469009;
    
    n_dyn_var=4;
    tau_r=0.8;
    
    p_r=1/tau_r;
    
}


Molecular_rExp_tExp::Molecular_rExp_tExp(const Molecular_rExp_tExp& model):ParameterEstimation_E_coli(model)
{
    
    Tipo_batterio = model.Tipo_batterio;
    codice_batterio=model.codice_batterio;
    simulation = model.simulation;
    a_m=model.a_m;
    m_0=model.m_0;
    K_off=model.K_off;
    K_on=model.K_on;
    n_a=model.n_a;
    
    M_max=model.M_max;
    A_max=model.A_max;
    L_max=model.L_max;
    y_max=model.y_max;
    
    K_R=model.K_R;
    K_B=model.K_B;
    
    kCheR=model.kCheR;
    kCheB=model.kCheB;
    //    y_0=0.696729639775898;
    //    y_0=0.4;
    y_0=model.y_0;
    k_a=model.k_a;
    k_z=model.k_z;
    H=model.H;
    
    a=0.723682;
    y=0.520505;
    meth=0.00469009;
    
    n_dyn_var=model.n_dyn_var;
    tau_r=model.tau_r;
    tau_t = model.tau_t;
    
    p_r=1/tau_r;
    
}

int Molecular_rExp_tExp::agg_dyn(long double dt, long double t)
// E' il cuore della classe ogni batterio implementa questo in modo diverso.
{
    
    if (salto_==1) {
        
//        long double prob = pow(y_0/y,H)*0.0246600002466;
//        prob=1/prob;
//        lambda_r+=prob*dt;
        
        
//        cout << "c = " << c << endl;
//        cout << "prob = " << prob_p << endl;
        
        lambda_r+=dt*p_r;

        if (lambda_r>barriera_r) {
            barriera_r=reset_barrier();
            lambda_r=0.0;
            return salto_=0;
        }
        
    }else if(salto_==-1){
        lambda_t+=dt/tau_t;
        if (lambda_t>=barriera_t) {
//            barriera_t=min(Exp_dist(),1.5);
            barriera_t=reset_barrier_t();

            lambda_t=0.0;
            return salto_=2;
        }
    }
    return salto_;    
}

void Molecular_rExp_tExp::stationary_dyn(long double dt, std::vector<long double> &m0,int changed_pos){
    
    t_r=0.0;
    t_t=0.0;
    
    if (changed_pos==0) {
        
        meth=m0[0];
        y=m0[1];
        a=m0[2];
        p_r=m0[3];
        
//        cout << "Initial Parameters: (m,a,y) = " <<meth <<" , " <<a <<" , " <<y <<" . " << endl;
        
    }else {
    
//        cout << "Change intial concentration ... ";
        
        SecantMethodForEquation(this,meth,0.004,0.005,c);
        a=1/(1+(kCheB*meth*(M_max-meth+K_R))/(kCheR*(meth+K_B)*(M_max-meth)));
        y=k_a*a/(k_a*a+k_z);
        
        // METHOD 1 ::: CHANGE ALSO IN agg_dynint
        long double h=1/(1+pow(y/y_0,H));
        p_r=(h/(1-h))/tau_t;
        
        factor_prob = tau_r*p_r;
        
        // METHOD 2
//        long double h=pow(y_0/y,H)*tau_t;
//        p_r=1/tau_t;
//        
//        factor_prob = tau_r/h;
        
//        cout << "initial value (p_r,factor_prob) = " << p_r << " , " << factor_prob << endl;
//        cout << "initial value (y, h) = " << y << " , " << h << endl;
        
        if (isnan(meth) || isnan(a) || isnan(y) || isnan(p_r)) {
            
            cout << "Error in the stationary initial solution (m,a,y) = " <<meth <<" , " <<a <<" , " <<y <<" , " << " , " << p_r << endl;
            
            a=0.723682;
            y=0.520505;
            meth=0.00469009;
            p_r = 1/tau_r;
            
            cout << "Default parameters: (m,a,y) = " <<meth <<" , " <<a <<" , " <<y <<" , " << p_r << endl;
        }

        //changed_pos=0;
        
        m0[0]=meth;
        m0[1]=y;
        m0[2]=a;
        m0[3]=p_r;
        
//        this->stationary_dyn(dt,m0,changed_pos);
        
    }
    
}

void Molecular_rExp_tExp::save_dyn(std::ofstream &file_, long double t){
    
    file_ << t << " " << lambda_r << " " << lambda_t << " " << meth << " " << y << " " << a << " " << p_r << endl;
    
}



void Molecular_rExp_tExp::reset_par(){
    
    E_coli::reset_par();
    
    Tipo_batterio = "Molecular-rExp-tExp";
    
    a_m=2;
    m_0=0.2;
    K_off=18;
    K_on=3;
    n_a=4;
    
    M_max=4;
    A_max=10;
    L_max=5;
    y_max=1;
    
    K_R=0.02;
    K_B=0.02;
    
    kCheR=0.1;
    kCheB=0.2;
    // y_0=0.696729639775898;
    y_0=0.4;
    //    y_0=0.520504;
    k_a=3;
    k_z=2;
    H=10;
    
    a=0.723682;
    y=0.520505;
    meth=0.00469009;
    
    n_dyn_var=4;
    tau_r=0.8;
    
    p_r=1/tau_r;
     
}


void Molecular_rExp_tExp::change_par(int change){
    
    E_coli::change_par(change);
    
    if (change==0) {
        
        reset_par();
        
    }else {
        
        change_molecular();
        
    }
    
}

void Molecular_rExp_tExp::change_molecular(){
    
    int risp=0;
    cout << "Do you want to change the parameters of the molecular implementation?\npress 0 for yes, 1 for no ";
    sssr(risp, "detailed parames molecular");
    
    if (risp==0) {
        cout << "Look at the documentation:\n";
        
        cout << "a_m";
        sssr(a_m,"a_m");
        cout << "m_0";
        sssr(m_0,"m_0");
        cout << "K_off";
        sssr(K_off,"Koff");
        cout << "K_on";
        sssr(K_on,"K_on");
        cout << "n_a";
        sssr(n_a,"n_a");
        cout << "M_max";
        sssr(M_max,"M_max");
        cout << "A_max";
        sssr(A_max,"A_max");
        cout << "L_max";
        sssr(L_max,"L_Max");
        cout << "y_max";
        sssr(y_max,"y_max");
        cout << "K_R";
        sssr(K_R,"K_R");
        cout << "K_B";
        sssr(K_B,"K_B");
        cout << "kCheR";
        sssr(kCheR,"KCheR");
        cout << "kCheB";
        sssr(kCheB,"kCheB");
        cout << "y_0";
        sssr(y_0,"y0");
        cout << "k_a";
        sssr(k_a,"k_a");
        cout << "k_z";
        sssr(k_z,"k_z");
        cout << "H";
        sssr(H,"H");
    }
    
    
    
}
