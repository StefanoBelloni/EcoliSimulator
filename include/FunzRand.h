//
//  FunzRand.h
//  E_Coli2.0
//
//  Created by Stefano Belloni on 18/05/15.
/*This program is free software - GNU General Public License Verison 2*/
//


#ifndef Ecoli_4_1_1_FunzRand_h
#define Ecoli_4_1_1_FunzRand_h


#include <iostream>
#include "FunzRand.h"
#include "GlobalVariables.h"
#include <cstdlib>
#include <cmath>
#include <ctime>

long double Exp_dist();
long double rand_normal(long double stddev);
long double gamma_par_double();
long double unifRand();
void seed();
long double deltaW(long double dt);
int signum_f(long double x);
long double newtheta(long double theta);


//inline long double Exp_dist();
//inline long double rand_normal(long double stddev);
//inline long double gamma_par_long double();
//inline long double unifRand();
//inline void seed();
//inline long double deltaW(long double dt);
//inline int signum_f(long double x);
//inline long double newtheta(long double theta);

//
//  FunzRand.cpp
//  E_Coli2.0
//
//  Created by Stefano Belloni on 20/05/15.
/*This program is free software - GNU General Public License Verison 2*/
//


//// c++11
////#include <random>
//
////#include "GlobalVariables.h"
//
//
////#define const_1 sqrt(8/3)
////#define const_2 sqrt(6)
////#define const_beta 0.009572265238289
//#include "constants.h" //#define pi1 3.141592654
////#define lim_alpha 2.5327805161251
//#define alpha 4.0         
//#define beta 18.32
//#define disp_gamma 4.6
//
////******************************************************************
////                      SEED
////******************************************************************
//
///**
// * put a seed for the random simulations
// */
//
//inline void seed()
//{
//    
////    unsigned int time_ui = static_cast<unsigned int>( time(NULL) );
//    //srand(time(NULL));
//    srand(seed_);
//
//}
//
//
////******************************************************************
////                      GAMMA DITRIBUTION (FOR E_COLI!!!)
////******************************************************************
///**
// * generate a rundom number distributed as a gamma(4,18.32;4.6)
// *
// */
//inline long double gamma_par_long double()
//{
//    
//    long double x=1;    
//    
//    for(int i=0;i<alpha;i++){ 
//        x=x*unifRand();
//    }
//    
//    return disp_gamma-log(x)*beta;    
//}
////******************************************************************
////******************************************************************
//
////******************************************************************
////                     NORMAL DITRIBUTION 
////******************************************************************
///**
// * generate a random number normal(0,stddev) using the Box muller method
// * @param stddev standar deviation of the distribution
// */
//inline long double rand_normal(long double stddev)
//{//Box muller method
//    static long double n2 = 0.0;
//    static int n2_cached = 0;
//    if (!n2_cached)
//    {
//        long double x, y, r;
//        do
//        {
//            x = 2.0*rand()/RAND_MAX - 1;
//            y = 2.0*rand()/RAND_MAX - 1;
//            
//            r = x*x + y*y;
//        }
//        while (r == 0.0 || r > 1.0);
//        {
//            long double d = sqrt(-2.0*log(r)/r);
//            long double n1 = x*d;
//            n2 = y*d;
//            long double result = n1*stddev;
//            n2_cached = 1;
//            return result;
//        }
//    }
//    else
//    {
//        n2_cached = 0;
//        return n2*stddev;
//    }
//}
////******************************************************************
////******************************************************************
//
//
////******************************************************************
////                     EXPONENTIAL DITRIBUTION 
////******************************************************************
//
///** generate an exponential distribution with parameter one
// */
//
//inline long double Exp_dist(){
//    
//    return -log(unifRand());
//    
//}
////******************************************************************
////******************************************************************
//
//
////******************************************************************
////                     UNIFORM DITRIBUTION 
////******************************************************************
//
///** generate an uniform distribution: it's written the possibility to reseed (now it's commented, look at it.)
// */
//
//inline long double unifRand()
//{
//    // re-seed after 5 Mil random generators ... 
////    cont_rand++;
////    std::numeric_limits<unsigned long>::max()
////  if (cont_rand>50000000000) {
//////    if (cont_rand>1000000000) {
//////        cout << "\n******************";
//////        cout << "\n ... seed() ... ";
//////        cout << "\n******************\n";
////        cont_rand=0;
////        seed();
//////    }
////  }
//    
//    //   void seed();
////    return rand() / long double(RAND_MAX+1);
//    
////    my_mutex.lock();
////    cout << "seed_r = " << seed_r << endl;
////    my_mutex.unlock();
//    
//    return rand_r(&seed_r) / long double(RAND_MAX);
//    
//    //    return 2.0*rand()/RAND_MAX - 1;
//    
//}
////******************************************************************
////******************************************************************
//
////******************************************************************
////                     INCREMENT WIENER 
////******************************************************************
//
///** calculate the increment in dt of a wiener process, dividing dt in further 4 sub-steps
// * you might want with minimum error pass the number of subdivision, for example with
// * inline long double deltaW(long double dt, int R = 4)
// * @param dt time-step
// */
//
//inline long double deltaW(long double dt)
//{
//    
//    long double dW=0.0;
//    short R=4;
//    long double stdt=sqrt(dt/R);
//    
//    for (int j=0; j<R; j++) {
//        dW+=rand_normal(stdt);
//    } 
//    
//    return dW;
//}
////******************************************************************
////******************************************************************
//
///** calculate the new direction (2D)
// * @param theta old direction.
// */
//
//inline long double newtheta(long double theta)
//{
//    
//    long double s=1;
//    long double theta_=0;
//    
//    if (unifRand()<=.5) {
//        s=-1;
//    }
//    
//    // + or - 50% probability
//    
//    theta_=theta;
//    theta=theta+pi1*s*(gamma_par_long double())/180;
// 
//    // there might be problem generating the gamma distribution (happens sometimes on Windows)
//    
//    if (fabs(theta)>5000) {
//        
//        std::cout << "problem generation new_theta: given a default theta=theta+46*Unif[0,1]\n";
//        
//        theta=theta_+s*46*unifRand();
//    }
//    
//    // go back into [0,2pi]
//  
//    while (theta<0){
//        theta = theta+2*pi1;
//    }
//    while (theta>2*pi1){
//        theta= theta-2*pi1;
//    }
//    
//    
//    return theta;
//}
//
//
////******************
////  signum_f
////******************
//
///** this function calculate the sign of a function with discrepancy from 0
//  * given by 0.00000001.
// */
//
//#define error_signum 0.00000000000001
//
//inline int signum_f(long double x){
//    
//    if (x >  error_signum) return 1;
//    if (x < -error_signum) return -1;
//    return 0;
//    
//};



#endif