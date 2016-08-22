//
//  CV_rExp_tExp.cpp
//  E_Coli2.0
//
//  Created by Stefano Belloni on 20/05/15.
/*This program is free software - GNU General Public License Verison 2*/
//
//****************************************************************************

#include "E_Coli.h"
#include "CV_rExp_tExp.h"
#include "ParameterEstimation_E_Coli.h"
#include <fstream>
#include <cmath>
#include "FunzRand.h"

#include "sssr.h"
#include "GlobalVariables.h"

#ifndef max
#define max( a, b ) ( ((a) > (b)) ? (a) : (b) )
#endif
#ifndef min
#define min( a, b ) ( ((a) < (b)) ? (a) : (b) )
#endif

#include "constants.h" //#define pi 3.141592653589793238462

//CV_rExp_tExp::CV_rExp_tExp():E_coli(){
CV_rExp_tExp::CV_rExp_tExp():ParameterEstimation_E_coli(){
    
    Tipo_batterio = "CV-rExp-tExp";
    codice_batterio = EcoliType::CV_REXP_TEXP;
    simulation = 0; 
    m.resize(3);
    n_dyn_var=3;
    
    D_theta = .25;
    tau_r = 0.8;
    nu_=4*(1+3*D_theta*tau_r)/(3*tau_r);
    beta_2=1;
    beta_3=-beta_2/2;
    
}

CV_rExp_tExp::CV_rExp_tExp(const CV_rExp_tExp& mod):ParameterEstimation_E_coli(mod){
    
    Tipo_batterio = mod.Tipo_batterio;
    codice_batterio=mod.codice_batterio;
    simulation = mod.simulation;
    m.resize(mod.m.size());
    n_dyn_var=mod.n_dyn_var;
    
    tipo_lambda = mod.tipo_lambda;
    A_0=mod.A_0;
    A_1=mod.A_1;
    A_2=mod.A_2;
    A_3=mod.A_3;
    
//    cout << "copy ... tau_r = " << tau_r << endl;
    
    D_theta = mod.D_theta;
    tau_r   = mod.tau_r;
    tau_t   = mod.tau_t;
    nu_     = mod.nu_;
    beta_2  = mod.beta_2;
    beta_3  = mod.beta_3;
    
}

int CV_rExp_tExp::agg_dyn(long double dt, long double t)
// E' il cuore della classe ogni batterio implementa questo in modo diverso.
{
    if (salto_==1) {
  
        lambda_r+=dt*f_lambda();
        if (lambda_r>=barriera_r) {
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

//****************************************************************************

void CV_rExp_tExp::change_par(int change){
    
    E_coli::change_par(change);
    
    if (change==0) {

        tipo_lambda=2;
        A_0=0.2;   // estremo destro
        A_1=0.2;   // estremo sinistro (<0)
        A_2=5;    // moltiplicatore "Q>a1"
        A_3=.7;   // moltiplicatore "Q<-a0"

    }else {
        
        change_lambda_par();
        
    }
    
}

//****************************************************************************

void CV_rExp_tExp::change_lambda_par()
{
    
    int risp=0;
    
    cout << "Do you want to change the parameters of the function Q(t)? \npress 0 for yes, 1 for no ";
    sssr(risp,"Do you want to change the parameters of the function Q(t)? press 0 for yes, 1 for no ");
    
    if (risp==0) {
        
        cout << "Memory pesistence  time exp(-nu_*t) "; 
        sssr(nu_,"Memory pesistence  time exp(-nu_*t) ");
        cout << "coefficient beta_2 ";
        sssr(beta_2,"coefficient beta_2 ");
        cout << "coefficient beta_3 ";
        sssr(beta_3,"coefficient beta_3 ");
        
    }
    
    cout << "Do you want to change the function 'lambda(Q)'? \npress 0 for yes, 1 for no ";
    sssr(risp,"Do you want to change the function 'lambda(Q)'? press 0 for yes, 1 for no ");
    
    if (risp==0) {
        
        cout << "Which form of the function lambda(t) you wnat to use" << endl; 
        cout << "0- Type Function:" << endl;
        cout << " lambda(Q):= max(A_00,(1-(A_10*max(0,Q)+A_20*min(0,Q))))/tau_r" << endl;    
        cout << "1- Type Function:" << endl;
        cout << " lambda(Q):= (1-pi/2*(atan{ [ A_10*max(0,Q)+A_20*min(0,Q) ]  }))/tau_r" << endl;  
        cout << "2- Type Function:" << endl;
        cout << "lambda(Q):= (1-2/pi*atan(pi/2*(  (Q>-A_12)*(Q<A_02)*Q+(Q<=-A_12)*(A_32*Q-(1-A_32)*A_12)+(Q>=A_02)*(A_22*Q+(1-A_22)*A_02) )))/tau" << endl;
        cout << "3- Type Function:" << endl;
        cout << " lambda(Q):= (A_00-A_10*Q)/tau_r" << endl;  
//        cout << "4- Type Function: change only the mean " << endl;
        sssr(tipo_lambda,"Which form of the function lambda(t) you wnat to use");
        
        switch (tipo_lambda) 
        {
            case 0:
                
                cout << "//***********************************************************\n//\n";
                cout << "\n\n lambda(Q):= max(A_00,(1-(A_10*max(0,Q)+A_20*min(0,Q))))/tau_r\n";                
                
                cout << "A_00: ";
                sssr(A_0,"A_00: ");;
                cout << "A_10: ";
                sssr(A_1,"A_10: ");;
                cout << "A_20: ";
                sssr(A_2,"A_20: ");;
                
                
                
                break;
                
            case 1:
                
                cout << "//***********************************************************\n//\n";
                cout << "\n\n (1-pi/2*(atan{ [ A_01*max(0,Q)+A_11*min(0,Q) ]  }))/tau_r\n";                
                
                cout << "A_01: ";
                sssr(A_0,"A_01: ");
                cout << "A_11: ";
                sssr(A_1,"A_11: ");
                
                break;
                
            case 2:
                
                cout << "//***********************************************************\n//\n";
                cout << "\n\n (1-2/pi*atan(pi/2*(  (Q>-A_12)*(Q<A_02)*Q+(Q<=-A_12)*(A_32*Q-(1-A_32)*A_12)+(Q>=A_02)*(A_22*Q+(1-A_22)*A_02) )))/tau\n";
                
                cout << "left extreme: A_12 ";
                sssr(A_1,"A_12: ");;
                
                cout << "right extreme: A_02 ";
                sssr(A_0,"A_02: ");;
                                cout << "moltiplicator for Q>A_12: A_22 ";
                sssr(A_2,"A_22: ");;
                
                cout << "moltiplicator for Q<A_-02: A_32 ";
                sssr(A_3,"A_32: ");;
                
                
                break;
                
            case 3:
                cout << "//***********************************************************\n//\n";
                cout << "\n\n (A_1-A_2*Q)/tau\n";
                
                cout << "value: A_1 ";
                sssr(A_1,"A_1: ");
                
                cout << "value: A_2 ";
                sssr(A_2,"A_2: ");
                
            default:
                
                tipo_lambda=2;
                A_0=.2;   // estremo destro
                A_1=.2;   // estremo sinistro (<0)
                A_2=5;    // moltiplicatore "Q>a1"
                A_3=.7;   // moltiplicatore "Q<-a0"
                
                break;
                
        } 
        
    }
       
}

void CV_rExp_tExp::save_dyn(std::ofstream &file_, long double t){
    
    file_ << t << " " << lambda_r << " " << lambda_t << " " << Q << endl;
    
}

long double CV_rExp_tExp::f_lambda(){
    
//    my_mutex.lock();
//    cout << "tipo lambda = " << tipo_lambda << endl;
//    my_mutex.unlock();
    
    switch (tipo_lambda) {
        case 0:
            
//            my_mutex.lock();
//            cout << "l = " << max(A_0,(1-(A_1*max(0,Q)+A_2*min(0,Q))))/tau_r << endl;
//            my_mutex.unlock();
            
            return max(A_0,(1-(A_1*max(0,Q)+A_2*min(0,Q))))/tau_r;
            
            break;
            
        case 1:
//            my_mutex.lock();
//            cout << "l = " << min(5.0,(1-pi/2*(atan( ( A_0*max(0,Q)+A_1*min(0,Q) )  )))/tau_r) << endl;
//            my_mutex.unlock();
            return min(5.0,(1-pi/2*(atan( ( A_0*max(0,Q)+A_1*min(0,Q) )  )))/tau_r);
            break;
            
        case 2:
            
//            return (1-2/pi*atan(pi/2*(  (Q>-A_1)*(Q<A_0)*Q+(Q<=-A_1)*(A_3*Q-(1-A_3)*A_1)+(Q>=A_0)*(A_2*Q+(1-A_2)*A_0) )))/(tau_r);
//            my_mutex.lock();
//            cout << "l = " << min(3.3,max(0.15,(1-2/pi*atan(pi/2*(  (Q>-A_1)*(Q<A_0)*Q+(Q<=-A_1)*(A_3*Q-(1-A_3)*A_1)+(Q>=A_0)*(A_2*Q+(1-A_2)*A_0) )))/(tau_r))) << endl;
//            my_mutex.unlock();
            return min(3.3,max(0.15,(1-2/pi*atan(pi/2*(  (Q>-A_1)*(Q<A_0)*Q+(Q<=-A_1)*(A_3*Q-(1-A_3)*A_1)+(Q>=A_0)*(A_2*Q+(1-A_2)*A_0) )))/(tau_r)));
            
            break;
         case 3:   
            
            // nel caso si voglia A_0=0 ...
//            my_mutex.lock();
//            cout << "l = " << max(0.0,A_0-A_1*Q)/tau_r << endl;
//            my_mutex.unlock();
            return max(0.0,A_0-A_1*Q)/tau_r;
            
        default:
//            my_mutex.lock();
//            cout << "l = " << 1/tau_r << endl;
//            my_mutex.unlock();

            return 1/tau_r;
    }
    
}

//****************************************************************************

void CV_rExp_tExp::stationary_dyn(long double dt, std::vector<long double> &m0,int changed_pos){
    
    t_r=0.0;
    t_t=0.0;
    
    if (changed_pos==0) {
        
        m[0]=m0[0];
        m[1]=m0[1];
        m[2]=m0[2];
        
        Q=pow(nu_,2)*beta_2*m[1]+pow(nu_,3)*beta_3*m[2];
        
    }else {
        long double T=10.0L;
        long double t=0.0L;
        
        m0[0]=c;
        m0[1]=c/2;
        m0[2]=c/2;
        
        while(t<=T) {
            m0[2]=m0[2]+dt*(2*m0[1]-nu_*m0[2]);
            m0[1]=m0[1]+dt*(m0[0]-nu_*m0[1]);
            m0[0]=m0[0]+dt*(c-nu_*m0[0]); 
            t=t+dt;    
        }
        
        changed_pos=0;
        this->stationary_dyn(dt,m0,changed_pos);
        
    }
    
}

void CV_rExp_tExp::reset_par(){
    
    E_coli::reset_par();
    
    Tipo_batterio = "CV-rExp-tExp";
    
    m.resize(3);
    n_dyn_var=3;
    
    D_theta=.25;
//    tau_r=1/(3*D_theta);
    tau_r = 0.8;
    nu_=4*(1+3*D_theta*tau_r)/(3*tau_r);
    beta_2=1;
    beta_3=-beta_2/2;
    
    tipo_lambda=2;
    A_0=.2;   // estremo destro
    A_1=.2;   // estremo sinistro (<0)
    A_2=5;    // moltiplicatore "Q>a1"
    A_3=.7;   // moltiplicatore "Q<-a0"
    
}

