//
//  StatToFunz.cpp
//  Ecoli_4.1.0
//
//  Created by Stefano Belloni on 22/07/15.
/*This program is free software - GNU General Public License Verison 2*/
//

//****************************************************

#include <iostream>
#include <cmath>

#include "E_Coli.h"
#include "ParameterEstimation_E_Coli.h"
#include "ParameterEstimation_CV_rIG_tExp.h"
#include "ParameterEstimation_CV_rExp_tExp.h"

void E_coli::s_F_lambda_r(vector<Q_tau_stat> vector_lambda, int n_vect){
    
    cout << "No estimation possible ... \n";
    
}

void ParameterEstimation_E_coli::s_F_lambda_r(vector<Q_tau_stat> vector_lambda, int n_vect){
    
    tau_r=vector_lambda[0].mean;

}


void ParameterEstimation_CV_rExp_tExp::s_F_lambda_r(vector<Q_tau_stat> vector_lambda, int n_vect){
    
    vector<int> index_Zero_Rec;
    double Q_,dQ_;

    s_lambda_r.lambda.resize(n_vect);
    s_lambda_r.syntetic_indeX.resize(n_vect);
    s_lambda_r.n_data.resize(n_vect);
    s_lambda_r.dQ=vector_lambda[1].Q-vector_lambda[0].Q;
    dQ_=s_lambda_r.dQ;
    s_lambda_r.Q_max=vector_lambda[n_vect-1].Q;
    s_lambda_r.Q_min=vector_lambda[0].Q;
    Q_=s_lambda_r.Q_min;
    s_lambda_r.n_records=n_vect;

    for (int i=0; i<n_vect; i++) {
        
        s_lambda_r.syntetic_indeX[i]=Q_;
        s_lambda_r.n_data[i]=vector_lambda[i].n_rec;
        
        if (vector_lambda[i].n_rec==0) {
            index_Zero_Rec.push_back(i);
            
//            s_lambda_r.lambda[i]=max((1-Q_)/0.8,0.1);
            this->Q=Q_;
            s_lambda_r.lambda[i]=CV_rExp_tExp::f_lambda(); 
            
        }else {
//            s_lambda_r.lambda[i]=1/vector_lambda[i].mean;            
//            s_lambda_r.lambda[i]=vector_lambda[i].max_tau/vector_lambda[i].n_rec;
            s_lambda_r.lambda[i]=vector_lambda[i].n_rec/vector_lambda[i].max_tau;            
        }
        
        if (Q_>=-dQ_ && Q_<=dQ_) {
            s_lambda_r.pos_steady=i;                
        }

        Q_+=dQ_;

    }
    
    tau_r = vector_lambda[s_lambda_r.pos_steady].mean;
    
    if (std::isnan(tau_r)) {
        tau_r=0.8;
    }
    
    
    
}


void ParameterEstimation_CV_rIG_tExp::s_F_lambda_r(vector<Q_tau_stat> vector_lambda, int n_vect){
    
    vector<int> index_Zero_Rec;
    double Q_,dQ_;
    
    
//    s_sigma_r.lamba[0]=1.16;
    
    s_lambda_r.lambda.resize(n_vect);
    s_lambda_r.sigma.resize(n_vect);
    s_lambda_r.syntetic_indeX.resize(n_vect);
    
    s_lambda_r.dQ=vector_lambda[1].Q-vector_lambda[0].Q;
    dQ_=s_lambda_r.dQ;
    s_lambda_r.Q_max=vector_lambda[n_vect-1].Q;
    s_lambda_r.Q_min=vector_lambda[0].Q;
    Q_=s_lambda_r.Q_min;
    s_lambda_r.n_records=n_vect;
    
    for (int i=0; i<n_vect; i++) {
        
        s_lambda_r.syntetic_indeX[i]=Q_;
        
        if (vector_lambda[i].n_rec==0) {
            index_Zero_Rec.push_back(i);
            s_lambda_r.lambda[i]=max(0.01, (1-Q_))/0.8;
            s_lambda_r.sigma[i]=1.6;
            
            
        }else {
            s_lambda_r.lambda[i]=1/vector_lambda[i].mean;
            
            if (vector_lambda[i].n_rec>3) {
                s_lambda_r.sigma[i]=vector_lambda[i].V_IG();
            }else {
                s_lambda_r.sigma[i]=1.6;
            }
            
        }
        
        if (Q_>=-dQ_ && Q_<=dQ_) {
            s_lambda_r.pos_steady=i;                
        }            
        
        Q_+=dQ_;
        
    }
    
    tau_r = vector_lambda[s_lambda_r.pos_steady].mean;
    
    if (std::isnan(tau_r)) {
        tau_r=0.8;
    }

}


