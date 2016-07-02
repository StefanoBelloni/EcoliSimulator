//
//  CV_rIG_tExp.cpp
//  E_Coli2.1
//
//  Created by Stefano Belloni on 22/05/15.
/*This program is free software - GNU General Public License Verison 2*/
//

#include "CV_rIG_tExp.h"
#include "E_Coli.h"
#include "ParameterEstimation_E_Coli.h"
#include "CV_rExp_tExp.h"
#include <fstream>
#include <cmath>
#include "FunzRand.h"

#include "GlobalVariables.h"
#include "sssr.h"

#ifndef max
#define max( a, b ) ( ((a) > (b)) ? (a) : (b) )
#endif
#ifndef min
#define min( a, b ) ( ((a) < (b)) ? (a) : (b) )
#endif

#include "constants.h" //#define pi 3.141592653589793238462
//#define t_min 0.05
//#define probIG_t_minQp 0.00000107383
//#define probIG_t_minQn 0.00000209821

//#define t_min 0.1
//#define probIG_t_minQp 0.000418136
//#define probIG_t_minQn 0.0056818

CV_rIG_tExp::CV_rIG_tExp():CV_rExp_tExp(){
    Tipo_batterio = "CV-rIG-tExp";
    codice_batterio = EcoliType::CV_RIG_TEXP;
    barriera_r=reset_barrier();
    B_0=1.6;
}

CV_rIG_tExp::CV_rIG_tExp(const CV_rIG_tExp& modello):CV_rExp_tExp(modello){
    Tipo_batterio = modello.Tipo_batterio;
    codice_batterio=modello.codice_batterio;
    barriera_r=reset_barrier();
    tipo_sigma=modello.tipo_sigma;
    B_0=modello.B_0;
    B_1=modello.B_1;
    B_2=modello.B_2;
}

#define barriera_r_inf -100

int CV_rIG_tExp::agg_dyn(double dt, double t)
// E' il cuore della classe ogni batterio implementa questo in modo diverso.
{
    
//    cout << "Q_max(CV_rIG_tExp::agg_dyn) = "<< s_lambda_r.Q_max << endl;

//    cout << "m = " << m[0] << "," << m[1] << "," << m[2] << endl;
//    cout << "Q = " << Q << endl;
    
    if (salto_==1) {
        
        double sigma_x=f_sigma();
        double lambda_star=lambda_r+dt*f_lambda()+sigma_x*deltaW_ec(dt);
        
//        if (lambda_r>barriera_r) {            
//            cout << "t = " << t << endl;
//            cout << "l_r = " << lambda_r << endl;
//            cout << "b_r = " << barriera_r << endl;
//            
//        }
        
        bool condition_salto
            =  (exp(-2*(barriera_r-lambda_r)*(barriera_r-lambda_star)/(dt*pow(sigma_x,2)))>=unifRand_ec())
            || (lambda_r>barriera_r) ;
//            || (exp(-2*(barriera_r_inf-lambda_r)*(barriera_r_inf-lambda_star)/(dt*pow(sigma_x,2)))>=unifRand()) 
//            || (lambda_r<barriera_r_inf);
        
        
        
        if (condition_salto) 
        {
//            if ((t-t_r<t_min)) {
//                
//                cout << "*******************************\n";
//                cout << "t = " << t << endl;
//                cout << "t-t_r = " << t-t_r << endl;
//                
//                if (Q>=0) {
//                    if (unifRand()<probIG_t_minQp) 
//                    {
//                        barriera_r=1;
//                        lambda_r=0.0;
//                        return salto_=0; 
//                    }else{ lambda_r=0.0; }
//                }else{
//                    if (unifRand()<probIG_t_minQn) 
//                    {
//                        barriera_r=1;
//                        lambda_r=0.0;
//                        return salto_=0; 
//                    }else { lambda_r=0.0; }
//                }
//   
//            }
//            else
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

double CV_rIG_tExp::f_sigma(){

    switch (tipo_sigma) 
    {
        case 0:
            
            return B_0; 
            
            break;
            
        case 1:
            
            return B_0*(1-pi/2*(atan( ( B_1*max(0,Q)+B_2*min(0,Q) )  )));
            
            break;
    }
    
    return 0;

}
//
//void CV_rIG_tExp::save_dyn(std::ofstream &file_, double t){
//    
//    file_ << t << " " << lambda_r << " " << lambda_t << " " << Q << endl;
//    
//};

void CV_rIG_tExp::change_par(int change){
    
    CV_rExp_tExp::change_par(change);
    
    if (change==0) {
        
        tipo_sigma=0;
        B_0= 1.64910013340609;
        
    }else {
        
        change_sigma_par();      
        
    }      
}

void CV_rIG_tExp::change_sigma_par()
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

//void CV_rIG_tExp::print_info(std::ofstream &file_save){
//    
//    CV_rExp_tExp::print_info(file_save);
//    
//    file_save << "The function sigma(Q) is: "<<endl << "     ";
//    
//    switch (tipo_sigma) 
//    {
//        case 0:
//            
//            file_save << "sigma(Q) = " << B_0 <<endl; 
//            
//            break;
//            
//        case 1:
//            
//            file_save << "sigma(Q) = "<<B_0<<"*(1-pi/2*(atan( ( "<<B_1<<"*max(0,Q)+"<<B_2<<"*min(0,Q) )  )))"<<endl;
//            
//            break;
//    }
//    
//}

void CV_rIG_tExp::reset_par(){
    
    CV_rExp_tExp::reset_par();
    
    Tipo_batterio = "CV-rIG-tExp";
    barriera_r=reset_barrier();
    B_0=1.6;
    
}
