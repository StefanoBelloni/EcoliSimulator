//
//  Funzioni_support_Molecular_rExp_tExp.cpp
//  E_Coli2.2
//
//  Created by Stefano Belloni on 01/06/15.
/*This program is free software - GNU General Public License Verison 2*/
//

#include <iostream>
#include <cmath>

#include "Molecular_rExp_tExp.h"

const int MAXITER    = 200;

// the accepted error
const long double error    = 0.00001L;

// the Euler constant
//const long double e        = 2.718281828459;

/**
 * Function to calculate stationary state in CV model see paper [Celani Schimizu Vergassola] E_coli "something" 2011
 */

long double F_CSV(Molecular_rExp_tExp *batterio, long double m_s, long double L_use)
{
    
    return exp(batterio->n_a*batterio->a_m*(m_s-batterio->m_0))*(batterio->kCheB*m_s*(batterio->M_max-m_s+batterio->K_R))/(batterio->kCheR*(m_s+batterio->K_B)*(batterio->M_max-m_s))-pow((1+L_use/batterio->K_off)/(1+L_use/batterio->K_on),batterio->n_a);
    
}

/**
 * Implementation of the secant method to find the zero of the equation given by long double F_CSV = 0
 */

int SecantMethodForEquation(Molecular_rExp_tExp *batterio, long double& x, long double x0, long double x1, long double c){
    
    int n = 2;
    
    while( ( fabs(F_CSV(batterio, x1,c)) > error ) && ( n <= MAXITER ) )
    {
        x = x1 - (F_CSV(batterio, x1,c) * (x1 - x0)) / (F_CSV(batterio, x1,c) - F_CSV(batterio, x0,c));
        x0 = x1;
        x1 = x;
        
        n++;
    }
    
    return n;
    
}
