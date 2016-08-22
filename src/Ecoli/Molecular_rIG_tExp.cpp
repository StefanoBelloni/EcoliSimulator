//
//  Molecular_rIG_tExp.cpp
//  Ecoli_4.1.1
//
//  Created by Stefano Belloni on 10/08/15.
/*This program is free software - GNU General Public License Verison 2*/
//

#include <iostream>
#include "Molecular_rIG_tExp.h"
#include "sssr.h"
#include <cmath>

#ifndef max
#define max( a, b ) ( ((a) > (b)) ? (a) : (b) )
#endif
#ifndef min
#define min( a, b ) ( ((a) < (b)) ? (a) : (b) )
#endif

#include "constants.h" //#define pi 3.141592653589793238462


Molecular_rIG_tExp::Molecular_rIG_tExp():Molecular_rExp_tExp(){
    Tipo_batterio = "Molecular-rIG-tExp";
    codice_batterio = EcoliType::MOLECULAR_RIG_TEXP;
    barriera_r=reset_barrier();
    B_0=1.6;
}

Molecular_rIG_tExp::Molecular_rIG_tExp(const Molecular_rIG_tExp& modello)
        :Molecular_rExp_tExp(modello)
{
    
    Tipo_batterio = modello.Tipo_batterio;
    codice_batterio=modello.codice_batterio;
    barriera_r=reset_barrier();
    B_0=modello.B_0;
    B_1=modello.B_1;
    B_2=modello.B_2;
    
}

long double Molecular_rIG_tExp::f_sigma(){
    
    switch (tipo_sigma) 
    {
        case 0:
            
            return B_0; 
            
            break;
            
        case 1:
            
            return B_0*(1-pi/2*(atan( ( B_1*max(0,y)+B_2*min(0,y) )  )));
            
            break;
    }
    
    return 0;
    
}


int Molecular_rIG_tExp::agg_dyn(long double dt, long double t)
// E' il cuore della classe ogni batterio implementa questo in modo diverso.
{
    
    long double f=n_a*a_m*(m_0-meth)+n_a*log((1+c/K_off)/(1+c/K_on));
    
    long double a_p=a;
    long double h;
    long double meth_p=meth;
    long double y_p=y;
    long double prob_p=p_r;
    int n_iteration=1;
    dt=dt/n_iteration;
    
    for (int i=0; i<n_iteration; i++) {
        
        a=1/(1+exp(f));
        meth=meth+dt*(kCheR*(1-a)*(M_max-meth)/(M_max-meth+K_R)-kCheB*a*meth/(meth+K_B));
        y=y+dt*(k_a*a*(1-y)-k_z*y);
        h=1/(1+pow(y/y_0,H));
        //        cout << " h = " << h << endl;
        p_r=max(0.1,min(5,(h/max(.1,(1-h)))/tau_t/factor_prob));
        
        //        cout << "p_t(" << t <<") = " << p_r << endl;
        
        if (isnan(p_r) || isnan(a) || isnan(meth) || isnan(y) ) {
            
            cout << "t = " << t << endl;
            cout << "problem: Nan (m_p,y_p,a_p,p_p) = " << meth_p << " , "<< y_p << " , " << a_p << " , " << prob_p << endl;
            cout << "problem: Nan (m,y,a,p) = " << meth << " , "<< y << " , " << a << " , " << lambda_r << "," << p_r << endl;
            cout << "***\n";
            a=a_p;
            y=y_p;
            meth=meth_p;
            p_r=prob_p;
            
//            return 4;
        }
    }
    
    if (salto_==1) {
        
        long double sigma_x=f_sigma();
        long double lambda_star=lambda_r+dt*prob_p+sigma_x*deltaW_ec(dt);
        
        bool condition_salto
        =  (exp(-2*(barriera_r-lambda_r)*(barriera_r-lambda_star)/(dt*pow(sigma_x,2)))>=unifRand_ec())
        || (lambda_r>barriera_r) ;
        
        if (condition_salto) 
        {
            {            
                barriera_r=reset_barrier();
                lambda_r=0.0;
                return salto_=0;
            }
        }
        else{ lambda_r=lambda_star; }
        
        
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

void Molecular_rIG_tExp::reset_par(){
    
    Molecular_rExp_tExp::reset_par();
    
    Tipo_batterio = "Molecular-rIG-tExp";
    barriera_r=reset_barrier();
    B_0=1.6;
    
}


void Molecular_rIG_tExp::change_par(int change){
    
    Molecular_rExp_tExp::change_par(change);
    
    if (change==0) {
        
        tipo_sigma=0;
        B_0= 1.64910013340609;
        
    }else {
        
        change_sigma_par();      
        
    }      
}

void Molecular_rIG_tExp::change_sigma_par()
{
    
    int std_risp=0, risp=0;
    
    cout << "Do you want to change the function 'sigma'? \npress 0 for yes, 1 for no ";
    sssr(risp,"Do you want to change the function 'sigma'? press 0 for yes, 1 for no ");
    
    if (risp==0) {
        
        cout << "Which form of the function sigma(t) you want to use" << endl;
        cout << "0- Type Function:" << endl;
        cout << " sigma(Q):= B_00" << endl;
        cout << "1- Type Function:" << endl;
        cout << " sigma(Q):=B_00*(1-pi/2*(atan{ [ B_01*max(0,Q)+B_11*min(0,Q) ]  }))" << endl;
        sssr(tipo_sigma,"Which form of the function sigma(t)");
        
        cout << "Do you want to insert the standard deviation of the run? \npress 0 for yes, 1 for no ";
        sssr(std_risp,"Do you want to insert the standard deviation");
        
        if (std_risp==0) {
            cout << "insert the standad deviation: \n";
            sssr(B_0,"std");;
            B_0 = B_0*sqrt(pow(tau_r,3));
        }
        
        switch (tipo_sigma)
        {
            case 0:
                
                if (std_risp!=0) {
                    cout << "//***********************************************************\n//\n";
                    cout << "\n\n sigma(Q):= B_00\n";
                    
                    sssr(B_0,"B_00");;
                }
                
                
                break;
                
            case 1:
                
                cout << "//***********************************************************\n//\n";
                cout << "\n\n sigma(Q):=B_00*(1-pi/2*(atan{ [ B_01*max(0,Q)+B_11*min(0,Q) ]  }))\n";
                
                if (std_risp!=0) {
                    cout << "B_00: ";
                    sssr(B_0,"B_00: ");;
                }
                
                cout << "B_01: ";
                sssr(B_1,"B_01: ");;
                cout << "B_11: ";
                sssr(B_2,"B_11: ");;
                
                break;
        }
        
    }
    
    
    
}
