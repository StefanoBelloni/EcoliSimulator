//
//  Internal_dynamic.cpp
//  Ecoli_4.1.2
//
//  Created by Stefano Belloni on 18/08/15.
/*This program is free software - GNU General Public License Verison 2*/
//

#include <iostream>
#include <cmath>

#include "E_Coli.h"
#include "CV_rExp_tExp.h"
#include "Molecular_rExp_tExp.h"
#include "EO_rExp_tExp.h"

#ifndef max
#define max( a, b ) ( ((a) > (b)) ? (a) : (b) )
#endif
#ifndef min
#define min( a, b ) ( ((a) < (b)) ? (a) : (b) )
#endif

void E_coli::agg_dyint(long double dt, long double t){
    
}

void CV_rExp_tExp::agg_dyint(long double dt, long double t){
    
    int n_iteration=5;
    dt=dt/n_iteration;
    
    for (int i=0; i<n_iteration; i++) {
    
        m[2]=m[2]+dt*(2*m[1]-nu_*m[2]);
        m[1]=m[1]+dt*(m[0]-nu_*m[1]);
        m[0]=m[0]+dt*(c-nu_*m[0]);
    
        Q=pow(nu_,2)*beta_2*m[1]+pow(nu_,3)*beta_3*m[2];
        
    }
    
//    my_mutex.lock();
//    for (int i = 0 ; i<3; i++) {
//        cout << "m [" << i << "] = " << m[i] << endl;
//    }
//    cout << "sum: " << pow(nu_,2)*beta_2*m[1] << ", " << pow(nu_,3)*beta_3*m[2] << endl;
//    cout << "Q = " << Q << endl;
//    my_mutex.unlock();
    
}

void Molecular_rExp_tExp::agg_dyint(long double dt, long double t){
    
    
    long double f;
    long double a_p=a;
    long double h;
    long double meth_p=meth;
    long double y_p=y;
    long double prob_p=p_r;
    int n_iteration=1;
    dt=dt/n_iteration;
    
    for (int i=0; i<n_iteration; i++) {
    
        // if changed, change also stationary_dyn!!
        
        // METHOD 1
        
          f = n_a*a_m*(m_0-meth)+n_a*log((1+c/K_off)/(1+c/K_on));
        a=1/(1+exp(f));
        meth=meth+dt*(kCheR*(1-a)*(M_max-meth)/(M_max-meth+K_R)-kCheB*a*meth/(meth+K_B));
        y=y+dt*(k_a*a*(1-y)-k_z*y);
        h=1/(1+pow(y/y_0,H));
//        cout << " h = " << h << endl;
        
//        p_r=max(0.1,min(5,(h/max(.1,(1-h)))/tau_t/factor_prob));
        
        p_r = h/(1-h)/tau_t/factor_prob;
        
        // Si potrebbe migliorare questo punto !!!
        
        if (isnan(p_r)||p_r>5) {
            p_r=5;
        }
        if (p_r<.1) {
            p_r=.1;
        }
        
//        cout << "p_t(" << t <<") = " << p_r << endl;
        
        // METHOD 2 also in
        /*Quantitative Modeling of Escherichia coli Chemotactic
         Motion in Environments Varying in Space and Time
         Lili Jiang1,3, Qi Ouyang1,2, Yuhai Tu1,3
         */
        
//        f = n_a*a_m*(m_0-meth)+n_a*log((1+c/K_off)/(1+c/K_on));
//        a=1/(1+exp(f));
//        meth=meth+dt*(kCheR*(1-a)*(M_max-meth)/(M_max-meth+K_R)-kCheB*a*meth/(meth+K_B));
//        y=y+dt*(k_a*a*(1-y)-k_z*y);
//        h=pow(y_0/y,H)*tau_t*factor_prob;
////        cout << " h = " << h << endl;
//        p_r=max(0.1,min(5,1/h));

        
        if (isnan(p_r) || isnan(a) || isnan(meth) || isnan(y) ) {
            
            cout << "t = " << t << endl;
            cout << "problem: Nan (m_p,y_p,a_p,p_p) = " << meth_p << " , "<< y_p << " , " << a_p << " , " << prob_p << endl;
            cout << "problem: Nan (m,y,a,p) = " << meth << " , "<< y << " , " << a << " , " << lambda_r << "," << p_r << endl;
            cout << "***\n";
            a=a_p;
            y=y_p;
            meth=meth_p;
            p_r=prob_p;
            
            }
        }
    
}


void EO_rExp_tExp::agg_dyint(long double dt, long double t){
    
    int n_iteration=5;
    dt=dt/n_iteration;
    
    for (int i=0; i<n_iteration; i++) {
    
        m[0] = m[0] + dt*(c-(m[0]+m[1]))/t_a ;
        m[1] = m[1] + dt*(c-m[1])/t_e;
    
    }
    
}
