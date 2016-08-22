//
//  distr_initial_unif.cpp
//  E_Coli2.2
//
//  Created by Stefano Belloni on 26/05/15.
/*This program is free software - GNU General Public License Verison 2*/
//

#include <iostream>
#include <cmath>

#include "constants.h" //#define pi 3.141592653589793238462

long double unifRand();

/** This function set the initial position.
 * @param x[] position of pacterium (to be set) 
 * @param x0[] initial position, set in the menu
 * @param R radius distribution
 * @param type of distribution, see menu
 * @return if the initial position change return 1, otherwise 0. If the position didn't change the initial condition for this bacterium are the same as the previous one, so we don't have to perform initial-condition calculation.
 */

int dist_iniz(long double x[], long double x0[], long double R,unsigned int num_dist){
    switch (num_dist) {
        case 2:
            x[0] = x0[0]+R*sqrt(unifRand())*cos(2*pi*unifRand());
            x[1] = x0[1]+R*sqrt(unifRand())*sin(2*pi*unifRand());
            return 1;
            break;
            
        case 3:
            x[0] = x0[0]-R+2*R*unifRand();
            x[1] = x0[1];
            return 1;
            break;
            
        case 4:
            x[1] = x0[1]-R+2*R*unifRand();
            x[0] = x0[0];
            return 1;
            break;
            
        default:
            x[0]=x0[0];
            x[1]=x0[1];
            return 0;
            
            break;
    }
    
    return 0;
    
}
