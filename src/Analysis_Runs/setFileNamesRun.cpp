//
//  setFileNamesRun.cpp
//  Ecoli_4.1.5
//
//  Created by Stefano Belloni on 19/05/16.
//  Copyright © 2016 Stefano Belloni. All rights reserved.
//

#include "setFileNamesRun.hpp"

/*! \brief this function return the proper name for the files run
 */
std::string setFileNamesRun(int save_, int frac_, int run, int cont_sim){
    
    char buffer_sim[36];
    
    
    snprintf(buffer_sim, sizeof(char) * 36,"sim-%03d-save%d-frac%d-run%d.gnu",cont_sim,save_,frac_,run);
    
    return buffer_sim;

}