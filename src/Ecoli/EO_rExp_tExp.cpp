//
//  EO_rExp_tExp.cpp
//  Ecoli_4.1.2
//
//  Created by Stefano Belloni on 18/08/15.
/*This program is free software - GNU General Public License Verison 2*/
//

#include <iostream>

#include "E_Coli.h"
#include "EO_rExp_tExp.h"
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
EO_rExp_tExp::EO_rExp_tExp():ParameterEstimation_E_coli(){
    
    Tipo_batterio = "EO-rExp-tExp";
    codice_batterio = EcoliType::EO_REXP_REXP_TEXP;
    simulation = 0; 
    m.resize(2);
    n_dyn_var=4;
    t_e = 0.1;
    t_a=4;
    D_theta=.25;
    tau_r=0.8;
    tau_t=.1;
        
}

EO_rExp_tExp::EO_rExp_tExp(const EO_rExp_tExp& modello):ParameterEstimation_E_coli(modello){
    Tipo_batterio = modello.Tipo_batterio;
    codice_batterio=modello.codice_batterio;
    simulation = modello.simulation;
    m.resize(modello.m.size());
    n_dyn_var=modello.n_dyn_var;
    t_e = modello.t_e;
    t_a=modello.t_a;
    D_theta=modello.D_theta;
    tau_r=modello.tau_r;
    tau_t=modello.tau_t;
}

int EO_rExp_tExp::agg_dyn(long double dt, long double t)
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

void EO_rExp_tExp::change_par(int change){
    
    E_coli::change_par(change);
    
    if (change==0) {
        
//        tipo_response_c=2;
//        RC_0=1;
//        RC_1=40;       // c(RC_1+c)
//        RC_q=1;

        tipo_response_c=0;
        RC_0=1;
        RC_1=0;
        RC_q=0;
        
        tipo_lambda=0;
        A_0=0.1;   // estremo destro
        A_1=1;   // estremo sinistro (<0)
        A_2=1;    // moltiplicatore "Q>a1"
        A_3=0;   // moltiplicatore "Q<-a0"
        
        t_a=4;
        t_e=.1;
        
    }else {
        
        change_lambda_par();
        
    }
    
}

//****************************************************************************

void EO_rExp_tExp::change_lambda_par()
{
    
    int risp=0;
    
    cout << "Do you want to change the parameters of the cartoon model? \npress 0 for yes, 1 for no ";
    sssr(risp,"Do you want to change the parameters of the cartoon model? press 0 for yes, 1 for no ");

    if (risp==0) {
        cout << "Adaptation time for the cartoon model";
        sssr(t_a,"Adaptation time for the cartoon model");
        cout << "Exitation time for the cartoon model";
        sssr(t_e,"Exitation time for the cartoon model");
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
        sssr(tipo_lambda,"Which form of the function lambda(t)");
        
        
        switch (tipo_lambda) 
        {
            case 0:
                
                cout << "//***********************************************************\n//\n";
                cout << "\n\n lambda(Q):= max(A_00,(1-(A_10*max(0,Q)+A_20*min(0,Q))))/tau_r\n";                
                
                cout << "A_00: ";
                sssr(A_0,"A_00");;
                cout << "A_10: ";
                sssr(A_1,"A_10");;
                cout << "A_20: ";
                sssr(A_2,"A_20");;
                
                
                
                break;
                
            case 1:
                
                cout << "//***********************************************************\n//\n";
                cout << "\n\n (1-pi/2*(atan{ [ A_01*max(0,Q)+A_11*min(0,Q) ]  }))/tau_r\n";                
                
                cout << "A_01: ";
                sssr(A_0,"A_01");
                cout << "A_11: ";
                sssr(A_1,"A_11");
                
                break;
                
            case 2:
                
                cout << "//***********************************************************\n//\n";
                cout << "\n\n (1-2/pi*atan(pi/2*(  (Q>-A_12)*(Q<A_02)*Q+(Q<=-A_12)*(A_32*Q-(1-A_32)*A_12)+(Q>=A_02)*(A_22*Q+(1-A_22)*A_02) )))/tau\n";
                
                cout << "left extreme: A_12 ";
                sssr(A_1,"A_12");;
                
                cout << "right extreme: A_02 ";
                sssr(A_0,"A_02");;
                cout << "moltiplicator for Q>A_12: A_22 ";
                sssr(A_2,"A_22");;
                
                cout << "moltiplicator for Q<A_-02: A_32 ";
                sssr(A_3,"A_32");;
                
                
                break;
                
            case 3:
                cout << "//***********************************************************\n//\n";
                cout << "\n\n (A_1-A_2*Q)/tau\n";
                
                cout << "value: A_1 ";
                sssr(A_1,"A_1");
                
                cout << "value: A_2 ";
                sssr(A_2,"A_2");
                
            default:
                
                tipo_lambda=0;
                A_0=0.1;   // estremo destro
                A_1=1;   // estremo sinistro (<0)
                A_2=1;    // moltiplicatore "Q>a1"
                A_3=0;   // moltiplicatore "Q<-a0"
                
                break;
                
        } 
        
    }
    
}

void EO_rExp_tExp::save_dyn(std::ofstream &file_, long double t){
    
    file_ << t << " " << lambda_r << " " << lambda_t << " " << m[0] << " " << m[1] << endl;
    
}

long double EO_rExp_tExp::f_lambda(){
    
    switch (tipo_lambda) {
        case 0:
            return max(A_0,(1-(A_1*max(0,m[0])+A_2*min(0,m[0]))))/tau_r;                
            
            break;
            
        case 1:
            return min(5.0,(1-pi/2*(atan( ( A_0*max(0,m[0])+A_1*min(0,m[0]) )  )))/tau_r);            
            break;
            
        case 2:
            
            //            return (1-2/pi*atan(pi/2*(  (Q>-A_1)*(Q<A_0)*Q+(Q<=-A_1)*(A_3*Q-(1-A_3)*A_1)+(Q>=A_0)*(A_2*Q+(1-A_2)*A_0) )))/(tau_r);
            
            return min(3.3,max(0.15,(1-2/pi*atan(pi/2*(  (m[0]>-A_1)*(m[0]<A_0)*m[0]+(m[0]<=-A_1)*(A_3*m[0]-(1-A_3)*A_1)+(m[0]>=A_0)*(A_2*m[0]+(1-A_2)*A_0) )))/(tau_r)));
            
            break;
        case 3:   
            
            // nel caso si voglia A_0=0 ...
            
            return max(0.0,A_0-A_1*m[0])/tau_r;
            
        default:
            
            return 1/tau_r;
    }
    
}

//****************************************************************************

void EO_rExp_tExp::stationary_dyn(long double dt, std::vector<long double> &m0,int changed_pos){
    
    t_r=0.0;
    t_t=0.0;
    
    if (changed_pos==0) {
        m[0]=m0[0];
        m[1]=m0[1];
        
    }else {
        
        m[1]=c;
        m[0]=0;
        
        //changed_pos=0;
        //this->stationary_dyn(dt,m0,changed_pos);
        
    }
    
}

/*
 //void EO_rExp_tExp::print_info(std::ofstream &file_save){
 //    
 //    E_coli::print_info(file_save);
 //    
 //    file_save <<"\n***************\n";
 //    file_save << "- see documentation for a clearer explanation."<<endl;    
 //    file_save << "The function lambda(Q) is: "<<endl << "     ";
 //    
 //    switch (tipo_lambda) {
 //        case 0:
 //            file_save << "max("<<A_0<<",(1-("<<A_1<<"*max(0,Q)+"<<A_2<<"*min(0,Q))))/"<<tau_r << endl;                
 //            
 //            break;
 //            
 //        case 1:
 //            file_save << "min(5.0,(1-pi/2*(atan( ( "<<A_0<<"*max(0,Q)+"<<A_1<<"*min(0,Q) )  )))/"<<tau_r<<")"<<endl;            
 //            break;
 //            
 //        case 2:
 //            file_save << "min(3.3,max(0.15,(1-2/pi*atan(pi/2*(  (Q>-A_1)*(Q<A_0)*Q+(Q<=-A_1)*(A_3*Q-(1-A_3)*A_1)+(Q>=A_0)*(A_2*Q+(1-A_2)*A_0) )))/(tau_r)))"<<endl;
 //            file_save << "with parameters:"<<endl; 
 //            file_save <<"A_0 = "<< A_0 <<" estremo destro"<<endl
 //                      <<"A_1 = "<<A_1  <<" estremo sinistro (<0)" << endl 
 //                      <<"A_2 = "<<A_2  <<" moltiplocatore Q>A_1 " << endl 
 //                      <<"A_3 = "<<A_3  <<" moltiplocatore Q<-A_0" << endl ;
 //            break;
 //            
 //        default:
 //            
 //            file_save << "min(3.3,max(0.15,(1-2/pi*atan(pi/2*(  (Q>-A_1)*(Q<A_0)*Q+(Q<=-A_1)*(A_3*Q-(1-A_3)*A_1)+(Q>=A_0)*(A_2*Q+(1-A_2)*A_0) )))/(tau_r)))"<<endl;
 //            file_save << "with parameters:"<<endl; 
 //            file_save <<"A_0 = "<< A_0 <<" estremo destro"<<endl
 //            <<"A_1 = "<<A_1  <<" estremo sinistro (<0)" << endl 
 //            <<"A_2 = "<<A_2  <<" moltiplocatore Q>A_1 " << endl 
 //            <<"A_3 = "<<A_3  <<" moltiplocatore Q<-A_0" << endl;
 //            
 //            break;
 //
 //    }
 //    
 //    
 //    
 //}
 */

void EO_rExp_tExp::reset_par(){
    
    E_coli::reset_par();
    
    Tipo_batterio = "EO-rExp-tExp";
    
    m.resize(2);
    n_dyn_var=2;
    
    D_theta=.25;
    tau_r=0.8;
    tau_t = 0.1;
    t_a=3;
    t_e=0.1;
    
    tipo_lambda=2;
    A_0=.2;   // estremo destro
    A_1=.2;   // estremo sinistro (<0)
    A_2=5;    // moltiplicatore "Q>a1"
    A_3=.7;   // moltiplicatore "Q<-a0"
    
    c_iniziale=0;


//    tipo_response_c=2;
//    RC_0=1;
//    RC_1=40;       // c(RC_1+c)
//    RC_q=1;
    
    
    tipo_response_c=0;
    RC_0=1;
    RC_1=0;
    RC_q=0;
    
}

