//
//  MovingLeastSquares.cpp
//  Ecoli_4.1.1
//
//  Created by Stefano Belloni on 06/08/15.
/*This program is free software - GNU General Public License Verison 2*/
//

#include <iostream>
#include <cmath>
#include "s_lambda.h"


double w_funz(double x, double epsilon_){
    return 1/(x*x+epsilon_*epsilon_);
    return 2*exp(-x*x/4);
//    return 1.1;
}

double w_funz(int n_rec){
    
    return n_rec+1;

//    return (n_rec==0)?0:(sqrt(n_rec)*1.6);
//    return 1.1;

}

//*****************************************************************
// moving 1/r^2
//*****************************************************************

/**
 * The function produce a Moving-Least-Squares Approximation for the data given by lambda and modifies it.
 */

int MovingLeastSquares(int set_epsilon, s_lambda &lambda){
    //if set_epsilon == 0 set epsilon.
    std::cout << "Moving-Least-Squares Approximation :\n";
    
    double epsilon_=1.5;
        
//    if (set_epsilon==0) {
//        std::cout << "Which level of epsilon? ";
//        std::cin >> epsilon;
//    }
    
    std::cout << "w(r)=1/(r^2+e^2), e = " << epsilon_ << std::endl;
    double sum1=0.0, sum2=0.0, sum3=0.0, sum4=0.0, sum5=0.0;
    double x=0;
    double w_1;
    s_lambda lambda_approx;
    
    int n=(int)lambda.lambda.size();
    int pos_1=0;
    lambda_approx.Q_max=lambda.Q_max;
    lambda_approx.Q_min=lambda.Q_min;
    lambda_approx.pos_steady=lambda.pos_steady;
    lambda_approx.dQ=lambda.dQ;
    
    lambda_approx.lambda.resize(n);
    lambda_approx.syntetic_indeX.resize(n);
    lambda_approx.n_data.resize(n);
    
    pos_1=lambda.pos_steady;
    lambda_approx.lambda[pos_1]=lambda.lambda[pos_1];
    
//    lambda_approx=lambda;  
    
//    sum1=sum2=sum3=sum4=sum5=0.0;
//    
//    for (int j=0; j<n; j++) {
//        w_1=w_funz(x-lambda.syntetic_indeX[j], epsilon);
//        sum2+=w_1*lambda.syntetic_indeX[j]*lambda.syntetic_indeX[j];  // x2
//        sum3+=w_1*lambda.syntetic_indeX[j];                           // x
//        sum5+=w_1;                                                    // w     
//    }
//    
//    if(fabs(sum5*sum2-sum3*sum3)<0.0001 || fabs(n*sum2-sum3*sum3)<0.0001){
//        
//        std::cout << "MATRIX SINGULAR ... \n"; 
//        return -1;
//        
//    }
    
    
    for (int i=pos_1+1; i<n; i=i+1) {
            
        lambda_approx.syntetic_indeX[i]=lambda.syntetic_indeX[i];
        lambda_approx.n_data[i]=lambda.n_data[i];
        x=lambda_approx.syntetic_indeX[i];
        
        sum1=0.0;
        sum2=0.0;
        sum3=0.0;
        sum4=0.0;
        sum5=0.0;
        
        for (int j=pos_1; j<n; j++) {
            w_1=w_funz(x-lambda.syntetic_indeX[j], epsilon_);
            sum1+=w_1*lambda.lambda[j];                                   // y
            sum2+=w_1*lambda.syntetic_indeX[j]*lambda.syntetic_indeX[j];  // x2
            sum3+=w_1*lambda.syntetic_indeX[j];                           // x
            sum4+=w_1*lambda.syntetic_indeX[j]*lambda.lambda[j];          // xy
            sum5+=w_1;                                                    // w     
        }
        
        lambda_approx.lambda[i]= ((sum1*sum2-sum3*sum4)+(sum5*sum4-sum3*sum1)*x)/(sum5*sum2-sum3*sum3);
        
        if (lambda_approx.lambda[i]<=0) {
            lambda_approx.lambda[i] = .1;
        }
        
        if (lambda_approx.lambda[i]>=10) {
            lambda_approx.lambda[i] = 10;
        }        
    }
    
    pos_1=lambda.pos_steady;
    
    for (int i=pos_1-1; i>=0; i=i-1) {
        
        lambda_approx.syntetic_indeX[i]=lambda.syntetic_indeX[i];
        lambda_approx.n_data[i]=lambda.n_data[i];
        x=lambda_approx.syntetic_indeX[i];
        
        sum1=0.0;
        sum2=0.0;
        sum3=0.0;
        sum4=0.0;
        sum5=0.0;
        
        for (int j=pos_1; j>=0; j--) {
            w_1=w_funz(x-lambda.syntetic_indeX[j], epsilon_);
            sum1+=w_1*lambda.lambda[j];                                   // y
            sum2+=w_1*lambda.syntetic_indeX[j]*lambda.syntetic_indeX[j];  // x2
            sum3+=w_1*lambda.syntetic_indeX[j];                           // x
            sum4+=w_1*lambda.syntetic_indeX[j]*lambda.lambda[j];          // xy
            sum5+=w_1;                                                    // w     
        }
        
        lambda_approx.lambda[i]= ((sum1*sum2-sum3*sum4)+(sum5*sum4-sum3*sum1)*x)/(sum5*sum2-sum3*sum3);
        
        if (lambda_approx.lambda[i]<=0) {
            lambda_approx.lambda[i] = .1;
        }
        
        if (lambda_approx.lambda[i]>=10) {
            lambda_approx.lambda[i] = 10;
        }
        
    }
    
    lambda=lambda_approx;
    
    
    return 0;
    
}

//*****************************************************************
// linear
//*****************************************************************

/**
 * The function produce a Least-Squares Approximation for the data given by lambda and modifies it.
 */

int MovingLeastSquares(int set_epsilon, s_lambda &lambda, int not_moving)
{
    //if set_epsilon == 0 set epsilon.
    std::cout << "Least-Squares Approximation :\n";
    
    

    double sum1=0.0, sum2=0.0, sum3=0.0, sum4=0.0;
    double sum5=0.0;
    double x=0;
    s_lambda lambda_approx;
    
    int n=(int)lambda.lambda.size();
    int pos_1=0;
    lambda_approx.Q_max=lambda.Q_max;
    lambda_approx.Q_min=lambda.Q_min;
    lambda_approx.pos_steady=lambda.pos_steady;
    lambda_approx.dQ=lambda.dQ;
    
    lambda_approx.lambda.resize(n);
    lambda_approx.syntetic_indeX.resize(n);
    lambda_approx.n_data.resize(n);
    
    pos_1=lambda.pos_steady;
    lambda_approx.lambda[pos_1]=lambda.lambda[pos_1];
    
//    lambda_approx=lambda;  

    //sum1=0;
    //sum2=sum3=sum4=sum5=0.0;
    
    for (int j=0; j<n; j++) {
        sum2+=lambda.syntetic_indeX[j]*lambda.syntetic_indeX[j];  // x2
        sum3+=lambda.syntetic_indeX[j];                           // x
    }
    
    if(fabs(sum5*sum2-sum3*sum3)<0.0001 || fabs(n*sum2-sum3*sum3)<0.0001){
        
        std::cout << "MATRIX SINGULAR ... \n"; 
        return -1;
        
    }
    
    
    for (int i=pos_1+1; i<n; i=i+1) {
        
        lambda_approx.syntetic_indeX[i]=lambda.syntetic_indeX[i];
        lambda_approx.n_data[i]=lambda.n_data[i];
        x=lambda_approx.syntetic_indeX[i];
        
        sum1=0.0;
        sum2=0.0;
        sum3=0.0;
        sum4=0.0;
        //sum5=0.0;
        
        for (int j=pos_1; j<n; j++) {
            sum1+=lambda.lambda[j];                                   // y
            sum2+=lambda.syntetic_indeX[j]*lambda.syntetic_indeX[j];  // x2
            sum3+=lambda.syntetic_indeX[j];                           // x
            sum4+=lambda.syntetic_indeX[j]*lambda.lambda[j];          // xy                                                  
        }
        
        lambda_approx.lambda[i]= (sum1*sum2-sum3*sum4)/((n-pos_1)*sum2-sum3*sum3)+((n-pos_1)*sum4-sum1*sum3)/((n-pos_1)*sum2-sum3*sum3)*x;
        
        if (lambda_approx.lambda[i]<=0) {
            lambda_approx.lambda[i] = .1;
        }
        
        if (lambda_approx.lambda[i]>=10) {
            lambda_approx.lambda[i] = 10;
        }        
    }
    
    pos_1=lambda.pos_steady;
    
    for (int i=pos_1; i>=0; i=i-1) {
        
        lambda_approx.syntetic_indeX[i]=lambda.syntetic_indeX[i];
        lambda_approx.n_data[i]=lambda.n_data[i];
        x=lambda_approx.syntetic_indeX[i];
        
        sum1=0.0;
        sum2=0.0;
        sum3=0.0;
        sum4=0.0;
        // sum5=0.0;
        
        for (int j=pos_1+1; j>=0; j--) {
            sum1+=lambda.lambda[j];                                   // y
            sum2+=lambda.syntetic_indeX[j]*lambda.syntetic_indeX[j];  // x2
            sum3+=lambda.syntetic_indeX[j];                           // x
            sum4+=lambda.syntetic_indeX[j]*lambda.lambda[j];          // xy                                                     // w     
        }
        
        lambda_approx.lambda[i]= (sum1*sum2-sum3*sum4)/((n-pos_1)*sum2-sum3*sum3)+((n-pos_1)*sum4-sum1*sum3)/((n-pos_1)*sum2-sum3*sum3)*x;
        
        if (lambda_approx.lambda[i]<=0) {
            lambda_approx.lambda[i] = .1;
        }
        
        if (lambda_approx.lambda[i]>=10) {
            lambda_approx.lambda[i] = 10;
        }
        
    }
    
    lambda=lambda_approx;
    
    
    return 0;
    
}

//*****************************************************************
// data-weight
//*****************************************************************

/**
 * The function produce a Least-Squares Approximation for the data given by lambda and modifies it.
 */

int MovingLeastSquares(s_lambda &lambda){
    //if set_epsilon == 0 set epsilon.
    std::cout << "Moving-Least-Squares Approximation :\n";
    
    double sum1=0.0, sum2=0.0, sum3=0.0, sum4=0.0, sum5=0.0;
    double sum1s=0.0, sum4s=0.0;
    double x=0;
    double w_1;
    s_lambda lambda_approx;
    
    int n=(int)lambda.lambda.size();
    int pos_1=0;
    
//    lambda_approx=lambda;  
    
    lambda_approx.Q_max=lambda.Q_max;
    lambda_approx.Q_min=lambda.Q_min;
    lambda_approx.pos_steady=lambda.pos_steady;
    lambda_approx.dQ=lambda.dQ;
    
    lambda_approx.lambda.resize(n);
    lambda_approx.sigma.resize(n);
    lambda_approx.syntetic_indeX.resize(n);
    lambda_approx.n_data.resize(n);
    
    lambda_approx.n_records=lambda.n_records;
    
    pos_1=lambda.pos_steady;
    lambda_approx.lambda[pos_1]=lambda.lambda[pos_1];
    
//    pos_1=lambda.pos_steady;
    
    for (int i=pos_1+1; i<n; i=i+1) {
        
        lambda_approx.syntetic_indeX[i]=lambda.syntetic_indeX[i];
        lambda_approx.n_data[i]=lambda.n_data[i];
        x=lambda_approx.syntetic_indeX[i];
        
        sum1=0.0;
        sum2=0.0;
        sum3=0.0;
        sum4=0.0;
        sum5=0.0;
        
        sum1s=0.0;
        sum4s=0.0;
        
        w_1=w_funz(lambda_approx.n_data[i]);
        
        for (int j=pos_1; j<n; j++) {

            sum1+=w_1*lambda.lambda[j];                                   // y
            sum2+=w_1*lambda.syntetic_indeX[j]*lambda.syntetic_indeX[j];  // x2
            sum3+=w_1*lambda.syntetic_indeX[j];                           // x
            sum4+=w_1*lambda.syntetic_indeX[j]*lambda.lambda[j];          // xy
            sum5+=w_1;                                                    // w   
            
            sum1s+=w_1*lambda.sigma[j];
            sum4s+=w_1*lambda.syntetic_indeX[j]*lambda.sigma[j];            
        }
        
        lambda_approx.lambda[i]= ((sum1*sum2-sum3*sum4)+(sum5*sum4-sum3*sum1)*x)/(sum5*sum2-sum3*sum3);
        lambda_approx.sigma[i]= ((sum1s*sum2-sum3*sum4s)+(sum5*sum4s-sum3*sum1s)*x)/(sum5*sum2-sum3*sum3);
        
        
        if (lambda_approx.lambda[i]<=0) {
            lambda_approx.lambda[i] = .1;
        }
        
        if (lambda_approx.lambda[i]>=10) {
            lambda_approx.lambda[i] = 10;
        } 
        
        if (lambda_approx.sigma[i]<=0) {
            lambda_approx.sigma[i] = 1.6;
        }
        
        if (lambda_approx.sigma[i]>=10) {
            lambda_approx.sigma[i] = 1.6;
        }
    }
    
//    pos_1=lambda.pos_steady;
    
    for (int i=pos_1; i>=0; i=i-1) {
        
        lambda_approx.syntetic_indeX[i]=lambda.syntetic_indeX[i];
        lambda_approx.n_data[i]=lambda.n_data[i];
        x=lambda_approx.syntetic_indeX[i];
        
        sum1=0.0;
        sum2=0.0;
        sum3=0.0;
        sum4=0.0;
        sum5=0.0;
        
        sum1s=0.0;
        sum4s=0.0;
        
        w_1=w_funz(lambda_approx.n_data[i]);
        
        
        for (int j=pos_1; j>=0; j--) {
            
            sum1+=w_1*lambda.lambda[j];                                   // y
            sum2+=w_1*lambda.syntetic_indeX[j]*lambda.syntetic_indeX[j];  // x2
            sum3+=w_1*lambda.syntetic_indeX[j];                           // x
            sum4+=w_1*lambda.syntetic_indeX[j]*lambda.lambda[j];          // xy
            sum5+=w_1;                                                    // w     
            
            sum1s+=w_1*lambda.sigma[j];
            sum4s+=w_1*lambda.syntetic_indeX[j]*lambda.sigma[j]; 
            
        }
        
        lambda_approx.lambda[i]= ((sum1*sum2-sum3*sum4)+(sum5*sum4-sum3*sum1)*x)/(sum5*sum2-sum3*sum3);
        lambda_approx.sigma[i]= ((sum1s*sum2-sum3*sum4s)+(sum5*sum4s-sum3*sum1s)*x)/(sum5*sum2-sum3*sum3);
        
        if (lambda_approx.lambda[i]<=0) {
            lambda_approx.lambda[i] = .1;
        }
        
        if (lambda_approx.lambda[i]>=10) {
            lambda_approx.lambda[i] = 10;
        }
        
        if (lambda_approx.sigma[i]<=0) {
            lambda_approx.sigma[i] = 1.6;
        }
        
        if (lambda_approx.sigma[i]>=10) {
            lambda_approx.sigma[i] = 1.6;
        }
        
    }
    
    lambda=lambda_approx;
    
    
    return 0;
    
}