//
//  LoadBar.hpp
//  Ecoli_4.1.3
//
//  Created by Stefano Belloni on 20/10/15.
//  Copyright © 2015 Heidelberg Universitaet. All rights reserved.
//

#ifndef LoadBar_hpp
#define LoadBar_hpp

#include <stdio.h>
#include "Colori.h"

//
//  LoadBar.cpp
//  Ecoli_4.1.3
//
//  Created by Stefano Belloni on 20/10/15.
//  Copyright © 2015 Heidelberg Universitaet. All rights reserved.
//


#include <iostream>
#include <iomanip>


//static inline void loadbar(unsigned int x, unsigned int n, unsigned int w);

/**
 * This function produced the load bar
 * @param if time_==0 I have not yet print the expected time to finish the simulation
 */

// https://www.ross.click/2011/02/creating-a-progress-bar-in-c-or-any-other-console-app/
// 
// The paramters are: i the current index we are on, n the number of indicies to process, r the number of times we want to update the display (doing it every time will cause programs with large n to slow down majorly) and w for the width of the bar.


static inline void loadbar(unsigned int x, unsigned int n, int time_ = 1, unsigned int w = 50)
// Se time_==0 non ho ancora stampato il tempo atteso ...
{
    
    if (time_==0) return;
    
    if ( (x != n) && (x % (n/100+1) != 0) ) return;
    
    float ratio  =  x/(float)n;
    unsigned int   c      =  ratio * w;
    
    std::cout << std::setw(3) << (int)(ratio*100) << "% [";
    for (unsigned int y=0; y<c; y++) std::cout << BOLDRED<< "=";
    for (unsigned int y=c; y<w; y++) std::cout << RESET << " ";
    std::cout <<RESET<< "]\r" << std::flush;
}



#endif /* LoadBar_hpp */
