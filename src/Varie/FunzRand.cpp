//
//  FunzRand.cpp
//  E_Coli2.0
//
//  Created by Stefano Belloni on 20/05/15.

/*This program is free software - GNU General Public License Verison 2*/

//

#include <iostream>
#include "FunzRand.h"
#include <cstdlib>
#include <cmath>
#include <ctime>

// c++11
//#include <random>

//#include "GlobalVariables.h"


//#define const_1 sqrt(8/3)
//#define const_2 sqrt(6)
//#define const_beta 0.009572265238289
#include "constants.h" //#define pi 3.141592654
//#define lim_alpha 2.5327805161251
#define alpha 4.0         
#define beta 18.32
#define disp_gamma 4.6

//******************************************************************
//                      SEED
//******************************************************************

void seed()
{
    
//    unsigned int time_ui = static_cast<unsigned int>( time(NULL) );
    srand((unsigned int)time(NULL));

}


//******************************************************************
//                      GAMMA DITRIBUTION (FOR E_COLI!!!)
//******************************************************************
long double gamma_par_double()
{
    
    long double x=1.0L;
    
    for(int i=0;i<alpha;i++){ 
        x=x*unifRand();
    }
    
    return disp_gamma-log(x)*beta;    
}
//******************************************************************
//******************************************************************

//******************************************************************
//                     NORMAL DITRIBUTION 
//******************************************************************
long double rand_normal(long double stddev)
{//Box muller method
    static long double n2 = 0.0L;
    static int n2_cached = 0;
    if (!n2_cached)
    {
        long double x, y, r;
        do
        {
            x = 2.0*rand()/RAND_MAX - 1;
            y = 2.0*rand()/RAND_MAX - 1;
            
            r = x*x + y*y;
        }
        while (r == 0.0 || r > 1.0);
        {
            long double d = sqrt(-2.0*log(r)/r);
            long double n1 = x*d;
            n2 = y*d;
            long double result = n1*stddev;
            n2_cached = 1;
            return result;
        }
    }
    else
    {
        n2_cached = 0;
        return n2*stddev;
    }
}
//******************************************************************
//******************************************************************


//******************************************************************
//                     EXPONENTIAL DITRIBUTION 
//******************************************************************

long double Exp_dist(){
    
    return -log(unifRand());
    
}
//******************************************************************
//******************************************************************


//******************************************************************
//                     UNIFORM DITRIBUTION 
//******************************************************************

long double unifRand()
{
    // re-seed after 5 Mil random generators ... 
//    cont_rand++;
//  if (cont_rand>2194967295) {
//    if (cont_rand>1000000000) {
//        cout << "\n******************";
//        cout << "\n ... seed() ... ";
//        cout << "\n******************\n";
 //       cont_rand=0;
//        seed();
//    }
    
    //   void seed();
    return rand() / (RAND_MAX+1.0);
//    return rand_r(&seed_r) / long double(RAND_MAX);
    //    return 2.0*rand()/RAND_MAX - 1;
    
}
//******************************************************************
//******************************************************************

//******************************************************************
//                     INCREMENT WIENER 
//******************************************************************

long double deltaW(long double dt)
{
    
    long double dW=0.0L;
    short R=4;
    long double stdt=sqrt(dt/R);
    
    for (int j=0; j<R; j++) {
        dW+=rand_normal(stdt);
    } 
    
    return dW;
}
//******************************************************************
//******************************************************************

long double newtheta(long double theta)
{
    
    long double s=1;
    long double theta_=0;
    
    if (unifRand()<=.5) {
        s=-1;
    }
    theta_=theta;
    theta=theta+pi*s*(gamma_par_double())/180;
 
    if (std::abs(theta)>5000) {
        
        std::cout << "problem generation new_theta: given a default theta=theta+46*Unif[0,1]\n";
        
        theta=theta_+s*46*unifRand();
    }
  
    //while (theta<0){
        //theta = theta+2*pi;
    //}
    //while (theta>2*pi){
        //theta= theta-2*pi;
    //}
    
    
    return theta;
}


//******************
//  signum_f
//******************
int signum_f(long double x){
    
    if (x > 0) return 1;
    if (x < 0) return -1;
    return 0;
    
}

