//
//  s_lambda.cpp
//  Ecoli_4.1.0
//
//  Created by Stefano Belloni on 21/07/15.
/*This program is free software - GNU General Public License Verison 2*/
//

#include "s_lambda.h"
#include <iostream>
#include <cmath>

#include "constants.h" //#define pi 3.141592654

#ifndef max
#define max( a, b ) ( ((a) > (b)) ? (a) : (b) )
#endif
#ifndef min
#define min( a, b ) ( ((a) < (b)) ? (a) : (b) )
#endif

double InvGauss(double t, double m, double s);
double Gauss(double t, double sigma, double m);
double GaussMax(double t, double sigma, double m, double w, double Max);
//double ConditionalProb(double t, double w, double lQ, double l, double sqrt_s, double m);
//**********************************************************************
//**********************************************************************


double s_lambda::s_funz_lambda(double Q){
    
    // min(n_records-1,max(1,floor((Q-Q_min)/dQ))) -> trova l'indice datto in lambda.
    
    if (n_records==0) {
        return lambda[0];
    }else {
        return lambda[min(n_records-1,max(0,floor((Q-Q_min)/dQ)))];
    }
    
    return 0.8;
}

//**********************************************************************
//**********************************************************************

double s_lambda::s_funz_sigma(double Q){
    
    // min(n_records-1,max(1,floor((Q-Q_min)/dQ))) -> trova l'indice datto in lambda.
    
    if (n_records==0) {
        return sigma[0];
    }else {
        return sigma[min(n_records-1,max(0,floor((Q-Q_min)/dQ)))];
    }
    
    return 1.6;
}

//**********************************************************************
//**********************************************************************

double s_lambda::StatIntensity(double dt, double t, double Q){
    
//    return s_funz_lambda(Q);
    
    if (distr==0) {
        
        return s_funz_lambda(Q);
        
    }else if (t>0.0){
        
        // DISTRIBUZIONE BROWNIAN BRIDGE !!!
        
//        if (Cumlambda>=1.0) {
//            return 0.0;
//        }
        
//        double dx=0.01;
//        double x=1.0;
//        double l=0.0;
//        double x0=min(1-Cumlambda,1.0);
//        int n_x=floor(x0/dx);
//        n_x+=floor((2*1.6)/dx);
//        
//        for (int i=0; i<n_x; i++) {
//            x-=dx;
//            l += dx*InvGauss(t, (1-x)/s_funz_lambda(Q), pow(1-x/s_funz_sigma(Q),2))*Gauss(t, 1.6, Cumlambda-x);
//            
//            if (isnan(l)) {
//                return s_funz_lambda(Q);
//            }
//            
//        }

        
        double dw=0.1;
        double dm=0.1;
        double l=0.0;
        double l1=0.0;
        
        double Max_=1.0;
        double w=1.0;
        
        int cont_w=floor(4/dw);
        int cont_M=floor(1/dm);
        int i_w=0;
//        double err=0.0001;
        
        /** If 
         Ref. -> Part II: The Joint Distribution For A Brownian Motion And Its Maximum And Minimum - Gary Schurman
        
         */
        Max_-=dm;
        
//        cout << "Intensity calculation...\n";
        
        for (int i_M=0; i_M<cont_M; i_M++) 
        {
            
            w=Max_;
            i_w=0;
            while (i_w<cont_w && w>=-3) 
            {
                l1 = dm*dw*InvGauss(t, (1-w)/s_funz_lambda(Q), pow((1-w)/s_funz_sigma(Q),2))*GaussMax(t, s_funz_sigma(Q), Cumlambda, w, Max_);
                
//                l1 = dm*dw*ConditionalProb(t, w, s_funz_lambda(Q), l, s_funz_sigma(Q),Max_);
                
                w-=dw;
                
                if (isnan(l1)) {
                    cout << "NaN-NaN-NaN-NaN-NaN-NaN-NaN-NaN\nt="<< t;
                    cout << "\nl1 =  "<< l1 <<"\ncumDen = "<< CumDen <<"\ncumLambda = " << Cumlambda << endl;
                    
                    l+= dm*dw*s_funz_lambda(Q);
                    
                }else {
                    l+=l1;
                }
                
                i_w++;
            }
            
            Max_-=dm;
        }
        
        Cumlambda=Cumlambda+dt*s_funz_lambda(Q);
//        CumDen = CumDen + dt*l;
        
//        cout << "***********\nt="<< t;
//        cout << "\nl =  "<< l <<"\ncumDen = "<<CumDen <<"\ncumLambda = " <<Cumlambda << endl;
        
        if (CumDen>=0.99999) {
            
            cout <<"*******************\n";
            cout << "t = " << t << endl;
            
            return 0.0;
        }
        
        return l/(1-CumDen);
    }
    
    return 1/.8;
}

//*****************************************************************

double InvGauss(double t, double m, double s){    
    
    return sqrt(s/(2*pi*pow(t,3)))*exp(-s/(2*m*m*t)*pow(t-m,2));
}

s_lambda::s_lambda(){
    
    Q_max=-10000;
    Q_min= 10000;
    dQ=0.001;
    
}

//*****************************************************************

double Gauss(double t, double sigma, double m){

    sigma=t*sigma*sigma;
    m=m*m;
    
    return sqrt(1/(2*pi*sigma))*exp(-m/(2*sigma));

}

//*****************************************************************

double GaussMax(double t, double sigma, double m, double w, double Max_){
    
    double v=t*sigma*sigma;
    return 2*(2*Max_-w)*sqrt(1/(2*pi*v*v*v))*exp(m*w-m*m*v/2-pow(2*Max_-w,2)/(2*v));
    
}

//*****************************************************************

//double ConditionalProb(double t, double w, double lQ, double l, double sqrt_s, double m){
//    double s=sqrt_s*sqrt_s;
//    double Ris=2*(1-l)*(2*m-l)*exp(-(t*(t-2-lQ*lQ*lQ+4*lQ*m*m+l*(2*t-4*l*(m+lQ)+((l-2+2*t)*l+1)/l)))/(2*s*t))/(2*pi*pow(sqrt_s,5)*pow(t,3));
//    if (isnan(Ris)) return 0.0;
//    else return Ris;
//    
//    
//}