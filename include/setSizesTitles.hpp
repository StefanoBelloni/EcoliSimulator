//
//  setSizesTitles.hpp
//  Ecoli_4.1.5
//
//  Created by Stefano Belloni on 19/05/16.
//  Copyright © 2016 Stefano Belloni. All rights reserved.
//

#ifndef setSizesTitles_hpp
#define setSizesTitles_hpp

#include <stdio.h>
#include <iostream>
#include <string>

namespace sizeTitle {
    
    enum size{
        SAVE = 0,
        NO_SAVE = 1 
        
    };
    
    enum sizes{
        SMALL,
        MEDIUM,
        LARGE,
        HUGE_
        
    };
}


/*! \brief this function set the size of the titles of the images:
 *
 * It has to be used when writing the script for gnuplot.
 */

std::string setSizesTitles(int dim, int save_);


#endif /* setSizesTitles_hpp */
