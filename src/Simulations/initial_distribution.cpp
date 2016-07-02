//
//  initial_distribution.cpp
//  E_Coli2.2
//
//  Created by Stefano Belloni on 26/05/15.
/*This program is free software - GNU General Public License Verison 2*/
//

#include <iostream>

int dist_iniz(double x[], double x0[], double R,unsigned int num_dist);

/**
 * This function set the initial position. What it does is: if the distribution is the n. 5, then update the new center, otherwise it calls dist_iniz(x,x0,Raggio,num_dist).
 * @param x[] position of pacterium (to be set)
 * @param x0[] initial position, set in the menu
 * @param R radius distribution
 * @param type of distribution, see menu
 * @return if the initial position change return 1, otherwise 0. If the position didn't change the initial condition for this bacterium are the same as the previous one, so we don't have to perform initial-condition calculation.
 */

int initial_position(int j,double *x, double *x0, double Raggio, int num_dist, int &cont_dist_5, int delta_dist_cont, double Delta_delta_dist)
{
    int cambiato=0;
    
    if (num_dist==5){
        
        if (j>cont_dist_5)
        {
            cont_dist_5=cont_dist_5+delta_dist_cont;
            x0[0]=x0[0]+Delta_delta_dist;
            cambiato=1;
//            std::cout << "(x,y)_"<<j<<" = " << x0[0] << " , " << x0[1] << std::endl;
            
        }
        
        x[0]=x0[0];
        x[1]=x0[1];
        
    }else{
        
        if (num_dist==1) {
            
            x[0]=x0[0];
            x[1]=x0[1];
            cambiato=0;            
            
        } else {
            return dist_iniz(x,x0,Raggio,num_dist);   
            
        }
    }
    
//    std::cout << "(x,y) = (" << x[0] << "," << x[1] << ")"<< std::endl;
    
    return cambiato;
}
