//
//  print_and_open_info.cpp
//  EColi_3.1
//
//  Created by Stefano Belloni on 23/06/15.
/*This program is free software - GNU General Public License Verison 2*/
//

#include <iostream>
#include <fstream>
#include <iomanip>

#include <ctime>

#include <cstring>

#include "GlobalVariables.h"

#include "E_Coli.h"
#include "ParameterEstimation_E_Coli.h"
#include "ParameterEstimation_CV_rExp_tExp.h"
#include "CV_rExp_tExp.h"
#include "Funz_C.h"
#include "Funz_C_Par.h"
#include "CV_rIG_tExp.h"
#include "CV_rExpIG_tExp.h"
#include "Molecular_rExp_tExp.h"
#include "Funz_C_Inter.h"
#include "EO_rExp_tExp.h"
#include "EO_rIG_tExp.h"
#include "EO_rExpIG_tExp.h"


using namespace std;

/**
 * This function produce a general summary for the LateX file. 
 * In this function the remaining information are compliting by calling the virtual function print_info in E_coli
 */

void print_and_open_info(string name, E_coli* batterio, Funz_C* f, double T_f, double *x0,  double dt,  int n_c,  double Raggio,  int delta_dist,  int num_dist,  int const_salv, int cont_gen_sim)
{
    
    time_t timer1;
    
    char buf[256];
    
    time(&timer1);
    strcpy(buf,ctime(&timer1));
    buf[strlen(buf)-1]='\0';
    
    //*************
    //  NOME FILE
    //*************
    ofstream file_info;
    
    name.erase(name.end()-4, name.end());
    
    string buffer = "_info.txt";
    
    string titolo=name+buffer;
    
    //************
    
    file_info.open(titolo.c_str());    
    
    //    titolo.erase(titolo.end()-14, titolo.end());
    //    titolo.erase(titolo.begin(), titolo.begin()+11);
    
    file_info << "\\begin{verbatim}" << endl;
    file_info << "********************************************" << endl;
    file_info << "**            E.COLI SIMULATOR            **" << endl;
    file_info << "********************************************" << endl;
    file_info << "**    Simulation of " << batterio->Tipo_batterio << endl;
    file_info << "**         n. "<< titolo << endl
              << "**       simulation number :"<<cont_gen_sim<<endl;
    file_info << "**     "<<buf << endl;
    file_info << "********************************************\n" << endl;
    file_info << "********************************************" << endl;
    file_info << "\\end{verbatim}" << endl;
    
    file_info << "The population has $"<< n_c <<"$ bacteri";
    if (n_c==1) {
        file_info <<"um. "<<endl;
    }else {
        file_info<<"a. "<<endl;
    }
    
    file_info << "The duration of the experiment is $" << T_f <<"$ seconds,"<<endl
    << "using a time step of $"<< dt << "$ seconds.\n\n"<<endl
    << "The graphs and the analysis is produce saving the data every $"<< dt*const_salv << "$ seconds.\n\n"<<endl;
    
    if (n_c==0) {
        file_info << "The bacterium starts the simulation at ";
    }else {
        file_info << "The population is distributed around the point ";
    }
    file_info << "$$(x_0,y_0) = ("<< x0[0] <<","<<x0[1] <<")$$"<<endl;
    
    if(n_c!=1){
        
        file_info << "following the distribution:"<<endl<<"\n\n";
        
        switch (num_dist) {
            case 1:
                file_info << "Delta di Dirac: "<< endl;
                file_info << "$$\\delta_{(x_0,y_0)}$$"<< endl;
                break;
            case 2:
                file_info << "Uniform: "<< endl;
                file_info << "$$\\mathcal{U}(x_0,y_0;R)$$"<< endl;                
                break;
            case 3:
                file_info << "Uniform for x, Delta di Dirac for y"<< endl;
                file_info << "$$\\mathcal{U}(x_0;R)\\otimes \\delta_{y_0}$$"<< endl;
                break;
            case 4:
                file_info << "Delta for x, Uniform for y: "<< endl;
                file_info << "$$\\delta_{x_0} \\otimes \\mathcal{U}(y_0;R)$$"<< endl;
                break;
            case 5:
                file_info << "sum of delta for x, delta di Dirac for y: "<< endl;
                file_info << "$$\\sum_{i=0}^{n_s}\\delta_{\\frac{x_0+R}{n_s}} \\otimes \\delta_{y_0}$$"<< endl;
                break;
            default:
                file_info << "Delta di Dirac: "<< endl;
                file_info << "$$\\delta_{(x_0,y_0)}$$"<< endl;
                break;
        }
        
        
        if (num_dist!=1) {
            file_info << "where the ray of the distribution is $$R = " << Raggio <<"$$"<< endl;
        }
        if (num_dist==5) {
            file_info << "And the number of sources is $$n_s = " << delta_dist <<"$$"<< endl;;
        }
        
    }
    
    file_info << "\\begin{verbatim}" << endl;
    file_info << "\n********************************************" << endl;
    file_info << "** Information about the bacterium  " << endl;
    file_info << "********************************************\n" << endl;
    file_info << "\\end{verbatim}" << endl;
    
    file_info << "Type Bacterium : " <<endl
    << "\\begin{verbatim}" << endl
    << batterio->Tipo_batterio << endl
    << "\\end{verbatim}" << endl;
    
    batterio->print_info(file_info);
    file_info << "\n" << endl;
    file_info << "\\begin{verbatim}" << endl;
    file_info << "********************************************" << endl;
    file_info << "** Information about the Ligand Concentration  " << endl;
    file_info << "********************************************\n" << endl;
    file_info << "\\end{verbatim}" << endl;
    
    f->print_info(file_info);
    
    if (f->interact==0) {
        file_info << "The production rate of the bacterium is $$K_p = " << batterio->Production_rate()<< "$$" << endl;
    }
    
    file_info.close();
    
//    if(automatic_==0){ 
//        name = "open "+name+buffer;
//        system(name.c_str());
//    }
    
}
/*   IN write LateX, da linea 42 a 53
 
 if (extension=="txt") {
 file_teX << "\\newpage" << endl;
 //        file_teX << "\\begin{verbatim}" << endl;
 
 temporary_file.open(name_file.c_str());
 while (!temporary_file.eof()) {
 getline(temporary_file, linea_file);
 file_teX << linea_file << endl;
 }
 
 //        file_teX << "\\end{verbatim}" << endl;
 }
 
 
 */


//**********************************************************************************************************
//    BATTETRIO PRINT INFO
//**********************************************************************************************************


void E_coli::print_info(ofstream &file_save){

    
    file_save << "The speed of the bacterium is $$v="<< v/epsilon <<"$$" << endl;
    if (epsilon!=1) {
        file_save << "In the simulation it was performed a diffusion-type rescale,i.e.";
        file_save << "$$v_{\\epsilon} = \\epsilon\\cdot v\\quad \\bar{t} = \\frac{t}{\\epsilon^2}$$";
        
        file_save << "with parameter $$\\epsilon="<< epsilon <<"$$" << endl;
        file_save << "The speed used in the simulation is therefor $$v=\\frac{v}{\\epsilon}="<< v <<"$$" << endl;
    }
//    file_save << "The speed of the bacterium is $$v="<< v/epsilon <<"$$" << endl;
    
    file_save << "In the steady state,\n\n"<<endl
    << "   - the mean time of a run is $$\\tau^0_r = " <<tau_r <<" sec.$$"  << endl
    << "   - the mean time of a tumble is $$\\tau^0_t = " <<tau_t <<" sec.$$" << endl;
    file_save << "The type of response to the Ligand concentration is: "<< endl <<"$$";
    
    switch (tipo_response_c) 
    {
        case 0:
            
            file_save << " \\phi(c) = "<<RC_0<<"*c"<<endl;
            
            break;
            
        case 1:
            
            file_save << " \\phi(c) = "<< RC_0<<"*log(1+"<<RC_1<<"*c)";
            
            break;
            
        case 2:
            
            file_save << " \\phi(c) = "<<RC_0<<"*(pi/2+atan("<<RC_1<<"*c))"<<endl;
            
            break;
            
        case 3:
            
            file_save << " \\phi(c) = "<< RC_0<<"*c^{"<<RC_q<<"}/("<<RC_1<<"^{"<<RC_q<<"}+c^{"<<RC_q<<"})"<<endl;
            
            break;
            
        default:
            
            file_save << " \\phi(c) = c "<< endl;
            
            break;
    }
    
    file_save << "$$" << endl;
    
    file_save << "The diffusion coefficient for the angle theta is $$D_\\theta = "<< D_theta <<"$$"<<endl;
    
    file_save << "The distribution of the new direction follows:"<<endl << "$$";
    
    switch (tipoNewTheta)
    {
        case 1:
            file_save << " \\theta(\\tau_r) = \\theta(\\tau_r^-)\\pm\\pi\\frac{4.6+18.2\\Gamma(4)}{180}"<<endl;
            
            break;
            
        default:
            
            file_save << " \\theta(\\tau_r) = 2\\pi\\mathcal{U}(0,1)"<< endl;
            
            break;
    }
    
    file_save << "$$" << endl;
    
};

//****************************************************************************

void CV_rExp_tExp::print_info(std::ofstream &file_save){
    
    E_coli::print_info(file_save);
    
    file_save <<"\n***************\n\n";
    file_save << "The function $\\lambda(Q)$ is\\footnote{see documentation for a clearer explanation.}: "<<endl << " $$\\lambda(Q) = ";
    
    switch (tipo_lambda) {
        case 0:
            file_save << "max("<<A_0<<",(1-("<<A_1<<"*max(0,Q)+"<<A_2<<"*min(0,Q))))/"<<tau_r << endl;                
            file_save << "$$" << endl;
            break;
            
        case 1:
            file_save << "min(5.0,(1-pi/2*(atan( ( "<<A_0<<"*max(0,Q)+"<<A_1<<"*min(0,Q) )  )))/"<<tau_r<<")"<<endl;            
            file_save << "$$" << endl;
            break;
            
        case 2:
            file_save << "min(3.3,max(0.15,(1-2/pi*atan(pi/2*(  (Q>-A_1)*(Q<A_0)*Q+(Q<=-A_1)*(A_3*Q-(1-A_3)*A_1)+(Q>=A_0)*(A_2*Q+(1-A_2)*A_0) )))/(tau_r)))"<<endl;
            file_save << "$$" << endl;
            file_save << "with parameters:\\"<<endl; 
            file_save <<"$A_0$ = "<< A_0 <<" estremo destro\\"<<endl
            <<"$A_1$ = "<<A_1  <<" estremo sinistro (<0)\\" << endl 
            <<"$A_2$ = "<<A_2  <<" moltiplocatore Q>$A_1$ \\" << endl 
            <<"$A_3$ = "<<A_3  <<" moltiplocatore Q<-$A_0$\\" << endl ;
            break;
            
        case 3:
            file_save << "( "<<A_0<<"-"<<A_1<<"*Q )/"<<tau_r<<")"<<endl;            
            file_save << "$$" << endl;
            
        default:
            
            file_save << "min(3.3,max(0.15,(1-2/pi*atan(pi/2*(  (Q>-A_1)*(Q<A_0)*Q+(Q<=-A_1)*(A_3*Q-(1-A_3)*A_1)+(Q>=A_0)*(A_2*Q+(1-A_2)*A_0) )))/(tau_r)))"<<endl;
            file_save << "$$" << endl;
            file_save << "with parameters:\\"<<endl; 
            file_save <<"$A_0$ = "<< A_0 <<" estremo destro\\"<<endl
            <<"$A_1$ = "<<A_1  <<" estremo sinistro (<0)\\" << endl 
            <<"$A_2$ = "<<A_2  <<" moltiplocatore Q>$A_1$ \\" << endl 
            <<"$A_3$ = "<<A_3  <<" moltiplocatore Q<-$A_0$\\" << endl ;
            
            break;
            
    }   
    
}

//****************************************************************************

void ParameterEstimation_CV_rExp_tExp::print_info(std::ofstream &file_save){
    
    E_coli::print_info(file_save);
    
    file_save <<"\n***************\n\n";
    file_save << "The function $\\lambda(Q)$ is\\footnote{see documentation for a clearer explanation.} estimated\n See picture. "<< endl;
    file_save << "The result of the Kolmogorov Test is ";
    if (GoodFit==0) {
        file_save << "positive, Good Fitness = " << GoodFit <<endl;
        file_save << "$$\\sqrt(n)D_n < K_{alpha}$$" << endl;
    }else {
        file_save << "negative, Good Fitness = " << GoodFit <<endl;
        file_save << "$$\\sqrt(n)D_n \\geq K_{alpha}$$" << endl;
    }
    file_save << "where $K_{\\alpha}$ is found from $$P(K<K_{\\alpha})=1-\\alpha$$"
    << "and The Kolmogorov distribution is the distribution of the random variable $$K=sup_{t\\in[0,1]}|B(t)|$$ where $B(t)$ is the Brownian bridge." << endl << endl;
    file_save << "The $L^\\infty$ distance between uniform distribution and empirical distribution is" 
    << "$$\\sup_{u\\in[0,1]}|\\frac{1}{n}\\sum_{i\\leq n}\\mathbf{1}_{[\\infty,u]}(X_i)-u| = " << KS_D_n << "$$" << endl;
    file_save << "The $L^1$ distance between uniform distribution and empirical distribution is" 
    << "$$\\|\\frac{1}{n}\\sum_{i\\leq n}\\mathbf{1}_{[\\infty,u]}(X_i)-u\\|_{L^1} = " << KS_L1 << "$$" << endl;
    
    
    
}

//****************************************************************************

void CV_rExpIG_tExp::print_info(std::ofstream &file_save) {
    
    CV_rExp_tExp::print_info(file_save);
    
    file_save << "The function $\\sigma(Q)$ is: "<<endl << "$$ ";
    
    switch (tipo_sigma) 
    {
        case 0:
            
            file_save << "\\sigma(Q) = " << B_0 <<endl; 
            
            break;
            
        case 1:
            
            file_save << "\\sigma(Q) = "<<B_0<<"*(1-pi/2*(atan( ( "<<B_1<<"*max(0,Q)+"<<B_2<<"*min(0,Q) )  )))"<<endl;
            
            break;
    }
    
    file_save << "$$" << endl;
    
}

//****************************************************************************

void CV_rIG_tExp::print_info(std::ofstream &file_save) {
    
    CV_rExp_tExp::print_info(file_save);
    
    file_save << "The function $\\sigma(Q)$ is: "<<endl << "$$ ";
    
    switch (tipo_sigma) 
    {
        case 0:
            
            file_save << "\\sigma(Q) = " << B_0 <<endl; 
            
            break;
            
        case 1:
            
            file_save << "\\sigma(Q) = "<<B_0<<"*(1-pi/2*(atan( ( "<<B_1<<"*max(0,Q)+"<<B_2<<"*min(0,Q) )  )))"<<endl;
            
            break;
    }
    
    file_save << "$$" << endl;
    
}

//****************************************************************************

void Molecular_rExp_tExp::print_info(std::ofstream &file_save){
    
    E_coli::print_info(file_save);
    
    file_save <<"\n***************\n\n";
    
    file_save <<"The chemotactic transduction pathway is conveniently modeled by the following set of mean-field equations."<< endl;
    file_save <<"\\begin{align*}"<< endl;
    file_save <<"a&=G(m,L),\\\\"<< endl;
    file_save <<"\\frac{d}{dt}m&=F(a,m),\\\\"<< endl;
    file_save <<"\\frac{d}{dt}y&=k_a a(1-y)-k_zy,\\\\"<< endl;
    file_save <<"\\frac{d}{dt}p_r&=\\frac{1-\\frac{p_r}{h(y)}}{\\tau_t}"<< endl;
    file_save <<"\\end{align*}"<< endl;
    
    
    file_save <<"The detailed expressions for the functions that appear above are:"<<endl;
    file_save <<"\\begin{align*}"<< endl;
    file_save <<"G(m,L)&=\\frac{1}{1+e^{f(m,L)}},\\\\"<< endl;
    file_save <<"f(m,L)&=n_a\\alpha_m(m_0-m)+n_a\\cdot log\\frac{1+\\frac{L}{K_{off}}}{1+\\frac{L}{K_{on}}}\\\\"<< endl;
    file_save <<"F(a,m)&=k_r[\\textrm{CheR}](1-a)\\frac{M-a}{M-m+K_R}-k_b[\\textrm{CheB}]a\\frac{m}{m+K_B}\\\\"<< endl;
    file_save <<"h(y)&=\\frac{1}{1+\\Big(\\frac{y}{y_0}\\Big)^H}"<< endl;
    file_save <<"\\end{align*}"<< endl;
    
    file_save << "\nThe Parameters\\footnote{see documentation for a clearer explanation} used in the simulation of the internal dynamics\n\n "<<endl;
    file_save <<"$a_m = " << a_m <<"$\\"<< endl;
    file_save <<"$m_0 = " << m_0 << "$\\"<< endl;;
    file_save <<"$K_{off} = " << K_off << "$\\"<< endl;;
    file_save <<"$K_{on} = " << K_on << "$\\"<< endl;;
    file_save <<"$n_a = " << n_a << "$\\"<< endl;;
    
    file_save <<"$M_{max} = " << M_max << "$\\"<< endl;;
    file_save <<"$A_{max} = " << A_max << "$\\"<< endl;;
    file_save <<"$L_{max} = " << L_max << "$\\"<< endl;;
    file_save <<"$y_{max} = " << y_max << "$\\"<< endl;;
    
    file_save <<"$K_R = " << K_R <<"$\\"<< endl;;
    file_save <<"$K_B = " << K_B <<"$\\"<< endl;;
    
    file_save <<"$KCheR = " << kCheR << "$\\"<< endl;;
    file_save <<"$KCheB = " << kCheB << "$\\"<< endl;;
    //    file_save <<"a_m = " << y_0;
    //    file_save <<"a_m = " << y_0;
    file_save <<"$y_0 = " << y_0 << "$\\"<< endl;;
    file_save <<"$k_a = " << k_a << "$\\"<< endl;;
    file_save <<"$k_z = " << k_z << "$\\"<< endl;;
    file_save <<"$H = " << H << "$\n\n"<< endl;;
    file_save <<"\n***************\n\n"<<endl;
    
    
}

//**********************************************************************************************************
//    BATTETRIO PRINT INFO
//**********************************************************************************************************

void Funz_C::print_info(ofstream &file_save){
    
    file_save << "The simulation is done with the Ligand concentration dynamics ";
    if (interact==0) {
        file_save << "\ninteracting with the population of bacteria via production of ligand \nand degradation of this one"<<endl;
    }else {
        file_save << "\nindependent of the population of bacteria"<<endl;
    }
    
    file_save << "\n\nThe diffution coefficient is $$D_c = "<< D_c <<"mm^2/s$$" <<endl;
    
    if (interact==0) {
        
        file_save << "The initial distribution is: "<<endl;
    }else {
        file_save << "The Ligand concentration follows : \n\n"<<endl;
    }
    switch (num_funz) {
        case 0:
            
            file_save <<  "0- Type Function: Gaussian" << endl;
            file_save <<  " $$c(t,x):= C_10*exp(-x^2/C_00)*(R<=C_20) = 6*exp(-pow(R,2)/10)*(R<=100)$$" << endl; 
            
            break;
            
        case 1:
            
            file_save <<  "1- Type Function: smoothed Jump" << endl;
            file_save <<  " $$c(t,x):= C_01+C_11*(t>C_21) = 1+2*(t>15)$$" << endl;
            
            break;
            
        case 2:
            
            file_save <<  "2- Type Function: Dancing Sombrero" << endl;
            //--->   Come scrivere ??
            file_save <<  " $$c(t,x):= ... $$" << endl;    
            
            break;
            
        case 3:
            
            file_save <<  "3- Type Function: Jump up/down" << endl;
            file_save <<  " $$c(t,x):= 1+C_13*(t<=C_03)+C_23*(t>C_03)*(t<=C_03+1)*pow(t-C_03,2)+C_23*(t>C_03+1)$$ \n      $$ = 1+2*(t<=6)+7*(t>6)*(t<=6+1)*pow(t-6,2)+7*(t>6+1)$$" << endl;
            
            break;
            
        case 4:
            
            file_save <<  "4- Type Function:" << endl;
            //--->   Cambiare la funzione !!  
            file_save <<  " $$c(t,x):= 1+C_14*(t<C_04)+(t>=C_14)*(t<C_24)+C_34*(t>C_24)$$" << endl;   
            
            break;
            
        case 5:
            
            file_save <<  "5- Type Function: Half-plane-Linear " << endl;
            file_save <<  " $$c(t,x):= C_05*(1+max(C_15,x[0])/C_15) = 3*(1+max(R,x[0])/2)$$" << endl;
            
            break;
            
        case 6:
            file_save <<  "6- Type Function: Half-plane-Exponential " << endl;
            file_save <<  " $$c(t,x):= C_06*exp(x[0]/C_16) = 18.2*exp(10*x[0])$$" << endl;
            
            break;
            
        case 7:
            
            file_save <<  "7- Type Function: time-Exponential " << endl;
            file_save <<  " $$c(t,x):= C_07*exp(C_27*t) = 18.2*exp(0.2*t)$$" << endl;
            
            break;
            
            
        default:
            
            file_save <<  "Otherwise Type Function:" << endl;
            file_save <<  " $$c(t,x):= Const = 3$$" << endl;
            
            break;
    }
    file_save << "\n***** \n\n"<<endl;
    file_save << "The are of the experiment is "<<endl
    << "$$(x_{min},x_{max}) = ("<<min_x<<","<<max_x<<")$$"<<endl
    << "$$(y_{min},y_{max}) = ("<<min_y<<","<<max_y<<")$$"<<endl;
    
    
};

//****************************************************************************

void Funz_C_Par::print_info(ofstream &file_save){
    
    Funz_C::print_info(file_save);
    
    if (change_par==1) {
        file_save << "Where the parameters are :\\"<<endl;
        file_save << "$C_0 = " << C_0 <<"$\\" <<endl;
        file_save << "$C_1 = " << C_1 << "$\\" <<endl;
        file_save << "$C_2 = " << C_2 << "$\\" <<endl;
        file_save << "$C_3 = " << C_3 << "$\\" <<endl;
    }
    
    
}

//****************************************************************************

void Funz_C_Inter::print_info(ofstream &file_save){
    
    Funz_C::print_info(file_save);
    Funz_C_Par::print_info(file_save);
    
    file_save << "\n\nTo model the evolution of the Ligand concentration $c(t,x,y)$, it has been used the following equation:" <<endl;
    
    file_save << "$$\\frac{\\partial}{\\partial}c(t,x,y)=D_c\\Delta_{(x,y)}c(t,x,y)-K_c c(t,x,y)+K_p\\sum_{i=1}^{n_c}\\delta_{(t,x,y)}(p^i_b(t,x,y))$$" <<endl;
    file_save << "where $p^i_b$ is the position of the bacterium number $i$." <<endl;
    file_save << "and the degradation rate is $$K_c = " << degradation_rate << "$$" << endl;
    
    
    
    
}

//****************************************************************************

void EO_rExp_tExp::print_info(std::ofstream &file_save){
    
    E_coli::print_info(file_save);
    
    file_save <<"\n***************\n\n";
    file_save << "The cartoon model";
    file_save << "$$\\frac{d}{dt}y_1(t)=\\frac{c(x,t)-(y_1+y_2)}{t_e}$$"<< endl;
    file_save << "$$\\frac{d}{dt}y_2(t)=\\frac{c(x,t)-y_2}{t_a}$$"<< endl;
    file_save << "has the following parameters:" << endl;
    file_save << "Adaptation time $t_a$ $$t_a = " << t_a <<"$$\n";
    file_save << "Exitation time $t_e$ $$t_e = " << t_a <<"$$\n";
    
    file_save <<"\n***************\n\n";
    file_save << "The function $\\lambda(Q)$ is\\footnote{see documentation for a clearer explanation.}: "<<endl << " $$\\lambda(Q) = ";
    
    switch (tipo_lambda) {
        case 0:
            file_save << "max("<<A_0<<",(1-("<<A_1<<"*max(0,Q)+"<<A_2<<"*min(0,Q))))/"<<tau_r << endl;                
            file_save << "$$" << endl;
            break;
            
        case 1:
            file_save << "min(5.0,(1-pi/2*(atan( ( "<<A_0<<"*max(0,Q)+"<<A_1<<"*min(0,Q) )  )))/"<<tau_r<<")"<<endl;            
            file_save << "$$" << endl;
            break;
            
        case 2:
            file_save << "min(3.3,max(0.15,(1-2/pi*atan(pi/2*(  (Q>-A_1)*(Q<A_0)*Q+(Q<=-A_1)*(A_3*Q-(1-A_3)*A_1)+(Q>=A_0)*(A_2*Q+(1-A_2)*A_0) )))/(tau_r)))"<<endl;
            file_save << "$$" << endl;
            file_save << "with parameters:\\"<<endl; 
            file_save <<"$A_0$ = "<< A_0 <<" estremo destro\\"<<endl
            <<"$A_1$ = "<<A_1  <<" estremo sinistro (<0)\\" << endl 
            <<"$A_2$ = "<<A_2  <<" moltiplocatore Q>$A_1$ \\" << endl 
            <<"$A_3$ = "<<A_3  <<" moltiplocatore Q<-$A_0$\\" << endl ;
            break;
            
        case 3:
            file_save << "( "<<A_0<<"-"<<A_1<<"*Q )/"<<tau_r<<")"<<endl;            
            file_save << "$$" << endl;
            
        default:
            
            file_save << "min(3.3,max(0.15,(1-2/pi*atan(pi/2*(  (Q>-A_1)*(Q<A_0)*Q+(Q<=-A_1)*(A_3*Q-(1-A_3)*A_1)+(Q>=A_0)*(A_2*Q+(1-A_2)*A_0) )))/(tau_r)))"<<endl;
            file_save << "$$" << endl;
            file_save << "with parameters:\\"<<endl; 
            file_save <<"$A_0$ = "<< A_0 <<" estremo destro\\"<<endl
            <<"$A_1$ = "<<A_1  <<" estremo sinistro (<0)\\" << endl 
            <<"$A_2$ = "<<A_2  <<" moltiplocatore Q>$A_1$ \\" << endl 
            <<"$A_3$ = "<<A_3  <<" moltiplocatore Q<-$A_0$\\" << endl ;
            
            break;
            
    }
    
    file_save << "It is adopted a simplified cartoon description, which is minimal yet captures the essential excitation and adaptation components" << endl;
    file_save << "$$t_a = " << t_a << "$$" << endl;
    
}

void EO_rIG_tExp::print_info(std::ofstream &file_save) {
    
    EO_rExp_tExp::print_info(file_save);
    
    file_save << "The function $\\sigma(Q)$ is: "<<endl << "$$ ";
    
    switch (tipo_sigma) 
    {
        case 0:
            
            file_save << "\\sigma(Q) = " << B_0 <<endl; 
            
            break;
            
        case 1:
            
            file_save << "\\sigma(Q) = "<<B_0<<"*(1-pi/2*(atan( ( "<<B_1<<"*max(0,Q)+"<<B_2<<"*min(0,Q) )  )))"<<endl;
            
            break;
    }
    
    file_save << "$$" << endl;
    
}

void EO_rExpIG_tExp::print_info(std::ofstream &file_save) {
    
    EO_rExp_tExp::print_info(file_save);
    
    file_save << "The function $\\sigma(Q)$ is: "<<endl << "$$ ";
    
    switch (tipo_sigma) 
    {
        case 0:
            
            file_save << "\\sigma(Q) = " << B_0 <<endl; 
            
            break;
            
        case 1:
            
            file_save << "\\sigma(Q) = "<<B_0<<"*(1-pi/2*(atan( ( "<<B_1<<"*max(0,Q)+"<<B_2<<"*min(0,Q) )  )))"<<endl;
            
            break;
    }
    
    file_save << "$$" << endl;
    
}


void E_coli::debugFunction(){
    cout << "E_coli:: virtual functions ..." << endl;
}

void CV_rExp_tExp::debugFunction(){
    
    
//    cout << "debug m = " << &m << endl;
//    
//    
//    cout << "\n***************************************************************************************************" << endl;
//    cout << "***************************************************************************************************" << endl;
//    
//    cout << "The speed of the bacterium is $$v="<< v/epsilon <<"$$" << endl;
//    if (epsilon!=1) {
//        cout << "In the simulation it was performed a diffusion-type rescale,i.e.";
//        cout << "$$v_{\\epsilon} = \\epsilon\\cdot v\\quad \\bar{t} = \\frac{t}{\\epsilon^2}$$";
//        
//        cout << "with parameter $$\\epsilon="<< epsilon <<"$$" << endl;
//        cout << "The speed used in the simulation is therefor $$v=\\frac{v}{\\epsilon}="<< v <<"$$" << endl;
//    }
//    //    cout << "The speed of the bacterium is $$v="<< v/epsilon <<"$$" << endl;
//    
//    cout << "In the steady state,\n\n"<<endl
//    << "   - the mean time of a run is $$\\tau^0_r = " <<tau_r <<" sec.$$"  << endl
//    << "   - the mean time of a tumble is $$\\tau^0_t = " <<tau_t <<" sec.$$" << endl;
//    cout << "The type of response to the Ligand concentration is: "<< endl <<"$$";
//    
//    switch (tipo_response_c)
//    {
//        case 0:
//            
//            cout << " \\phi(c) = "<<RC_0<<"*c"<<endl;
//            
//            break;
//            
//        case 1:
//            
//            cout << " \\phi(c) = "<< RC_0<<"*log(1+"<<RC_1<<"*c)";
//            
//            break;
//            
//        case 2:
//            
//            cout << " \\phi(c) = "<<RC_0<<"*(pi/2+atan("<<RC_1<<"*c))"<<endl;
//            
//            break;
//            
//        case 3:
//            
//            cout << " \\phi(c) = "<< RC_0<<"*c^{"<<RC_q<<"}/("<<RC_1<<"^{"<<RC_q<<"}+c^{"<<RC_q<<"})"<<endl;
//            
//            break;
//            
//        default:
//            
//            cout << " \\phi(c) = c "<< endl;
//            
//            break;
//    }
//    
//    cout << "$$" << endl;
//    
//    cout << "The diffusion coefficient for the angle theta is $$D_\\theta = "<< D_theta <<"$$"<<endl;
//    
//    cout << "CV_rExp_tExp:: virtual functions ..." << endl;
//    cout << this << endl;
//    
//    cout <<"\n***************\n\n";
//    cout << "The function $\\lambda(Q)$ is\\footnote{see documentation for a clearer explanation.}: "<<endl << " $$\\lambda(Q) = "<< endl;
//    
//    switch (tipo_lambda) {
//        case 0:
//            cout << "max("<<A_0<<",(1-("<<A_1<<"*max(0,Q)+"<<A_2<<"*min(0,Q))))/"<<tau_r << endl;
//            cout << "$$" << endl;
//            break;
//            
//        case 1:
//            cout << "min(5.0,(1-pi/2*(atan( ( "<<A_0<<"*max(0,Q)+"<<A_1<<"*min(0,Q) )  )))/"<<tau_r<<")"<<endl;
//            cout << "$$" << endl;
//            break;
//            
//        case 2:
//            cout << "min(3.3,max(0.15,(1-2/pi*atan(pi/2*(  (Q>-A_1)*(Q<A_0)*Q+(Q<=-A_1)*(A_3*Q-(1-A_3)*A_1)+(Q>=A_0)*(A_2*Q+(1-A_2)*A_0) )))/(tau_r)))"<<endl;
//            cout << "$$" << endl;
//            cout << "with parameters:\\"<<endl;
//            cout <<"$A_0$ = "<< A_0 <<" estremo destro\\"<<endl
//            <<"$A_1$ = "<<A_1  <<" estremo sinistro (<0)\\" << endl
//            <<"$A_2$ = "<<A_2  <<" moltiplocatore Q>$A_1$ \\" << endl
//            <<"$A_3$ = "<<A_3  <<" moltiplocatore Q<-$A_0$\\" << endl ;
//            break;
//            
//        case 3:
//            cout << "( "<<A_0<<"-"<<A_1<<"*Q )/"<<tau_r<<")"<<endl;
//            cout << "$$" << endl;
//            
//        default:
//            
//            cout << "min(3.3,max(0.15,(1-2/pi*atan(pi/2*(  (Q>-A_1)*(Q<A_0)*Q+(Q<=-A_1)*(A_3*Q-(1-A_3)*A_1)+(Q>=A_0)*(A_2*Q+(1-A_2)*A_0) )))/(tau_r)))"<<endl;
//            cout << "$$" << endl;
//            cout << "with parameters:\\"<<endl;
//            cout <<"$A_0$ = "<< A_0 <<" estremo destro\\"<<endl
//            <<"$A_1$ = "<<A_1  <<" estremo sinistro (<0)\\" << endl
//            <<"$A_2$ = "<<A_2  <<" moltiplocatore Q>$A_1$ \\" << endl
//            <<"$A_3$ = "<<A_3  <<" moltiplocatore Q<-$A_0$\\" << endl ;
//            
//            break;
//            
//    }
    
    
    cout << "CV_rExp_tExp:: virtual functions ..." << endl;
    
}

void CV_rIG_tExp::debugFunction(){
    cout << "CV_rIG_tExp:: virtual functions ..." << endl;
}
